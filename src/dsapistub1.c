#include "dsapistub1.h"

/* Routines with syntax dictated by the DSAPI interface */
unsigned int	Authenticate(FilterContext* context, FilterAuthenticate* authData);
/* Retrieval of name and HTTPPassword from Notes name and address book */
int getUserNames(FilterContext* context,
                  char *userName,
                  char **pUserFullName,
                  int  *pUserFullNameLen,
                  char **pHTTPPassword,
                  int  *ppHTTPPasswordLen);

/* Log message if bDebug = TRUE */
void logMessage(int flag, const char *message);

/* check if mfa.nsf exists */
int loadMFA();

/* Retrieval of name and HTTPPassword from Notes name and address book */
int getUserMFA(char *userName);

STATUS LNPUBLIC getUserPasswordSecret(void far *db_handle, SEARCH_MATCH far *pSearchMatch, ITEM_TABLE far *summary_info);

int getLookupInfo(FilterContext* context,
                  char *pMatch,
                  unsigned short itemNumber,
                  char **pInfo,
                  int  *pInfoLen);

void			PrintAPIError (STATUS api_error);

char*	filter_name = "MFA for Domino (Traveler)";			// filter name
char*	db_mfa_filename = "mfa.nsf";
char passwordSecret[128] = {0};
int passwordSecretLen;
char enable[8] = {0};
int enableLen;

int	bLog=FALSE;						// print debug information to console

/* Notes SDK shared library entrypoint */
EXPORT int MainEntryPoint(void);

EXPORT int MainEntryPoint(void) {
	return NOERROR;
}

EXPORT unsigned int FilterInit(FilterInitData* filterInitData) {
	STATUS error = NOERROR;

	filterInitData->appFilterVersion = kInterfaceVersion;
	filterInitData->eventFlags = kFilterAuthenticate;
	strncpy(filterInitData->filterDesc, filter_name, sizeof(filterInitData->filterDesc) - 1);
	filterInitData->filterDesc[sizeof(filterInitData->filterDesc) - 1] = '\0';  // Ensure null-termination
	bLog = OSGetEnvironmentLong("mfa_debug");

	logMessage(TRUE, "--------------------------------");
	logMessage(TRUE, "DSAPI Filter loaded (v0.5.5)");
	AddInLogMessageText("%s: %s %s", NOERROR, filter_name, __TIME__, __DATE__);
	AddInLogMessageText("%s: db: %s", NOERROR, filter_name, db_mfa_filename);
	AddInLogMessageText("%s: debug: %u", NOERROR, filter_name, bLog);
	logMessage(TRUE, "--------------------------------");

	if (NOERROR != loadMFA()) {
		//Return an error so that the filter will not be called for any events
		logMessage(TRUE, "Error: Unable to find/open mfa.nsf configuration databases.");
		logMessage(TRUE, "The filter will not process any requests.");
		logMessage(TRUE, "--------------------------------");
		return kFilterError;
	}

	return kFilterHandledRequest;
}	// end FilterInit

EXPORT unsigned int TerminateFilter(unsigned int reserved) {
	logMessage(TRUE, "TerminateFilter");
	return kFilterHandledEvent;
}	// end Terminate

EXPORT unsigned int HttpFilterProc(FilterContext* context, unsigned int eventType, void* eventData) {
	/* Include only those events we want to handle */
	switch (eventType) {
	case kFilterAuthenticate:
		return Authenticate(context, (FilterAuthenticate *) eventData);
	default:
		break;
	}

   return kFilterNotHandled;
}	// end HttpFilterProc

/*---
*      handle user authentication
*/
unsigned int Authenticate(FilterContext* context, FilterAuthenticate* authData) {
	char *fullName = NULL;
	int fullNameLen = 0;
	char *httpPassword = NULL;
	int httpPasswordLen = 0;
	char *user = NULL;
	char *domain = NULL;
	char password[128] = {0};
	*passwordSecret = NULL;
	passwordSecretLen = 0;
	*enable = NULL;
	enableLen = 0;

	logMessage(bLog, "Authenticate started");

	// If the user is found in the cache, then we don't need to do anything further.
	if (!authData || authData->foundInCache) {
		logMessage(bLog, "User is found in the cache");
		return kFilterNotHandled;
	};

	// Verify if username and password are available.
	if (!authData->userName || !authData->password) {
		logMessage(bLog, "User/Password are not provided");
		return kFilterNotHandled;
	};

	// Not a web user
	if( !(authData->authFlags & (kAuthAllowAnonymous | kAuthAllowSSLAnonymous | kAuthAllowBasic | kAuthAllowSSLBasic)) ) {
		logMessage(bLog, "Not a web user");
		return kFilterNotHandled;
	};

	/* Lookup the user in the Name and Address book.  Get the user's short name (which we expect is the OS user name),
	* and get the user's fullname (which we expect will be in the format to pass back to dsapi).
	*/
	user = (char*)authData->userName;
	if (NOERROR != getUserNames(context, user, &fullName, &fullNameLen, &httpPassword, &httpPasswordLen)) {
		logMessage(bLog, "User not found in the Adress book\n");
		return kFilterNotHandled;
	}

	strncpy(password, (char *)authData->password, sizeof(password) - 1);
	password[sizeof(password) - 1] = '\0';  // Ensure null-termination

	if (NOERROR != getUserMFA(fullName)) {
		logMessage(bLog, "We could not find information about user in mfa.nsf .\n");
		return kFilterNotHandled;
	}

	if (enableLen == 0) {
		logMessage(bLog, "User has not enabled multi-factor auth.\n");
		return kFilterNotHandled;
	}

	logMessage(bLog, "Multi-factor auth. - enabled");
	if (passwordSecretLen > 0) {
		strcat(password, passwordSecret);
	}		

	if (bLog==TRUE) {
		AddInLogMessageText("Password: %s", NOERROR, password);
	}

	if (NOERROR == SECVerifyPassword((WORD) strlen(password), (BYTE*) password, (WORD)strlen(httpPassword), (BYTE*) httpPassword, 0, NULL)) {
		logMessage(bLog, "Password pass.\n");

		/* Copy the canonical name for this user that dsapi requires.  */
		strncpy ((char *)authData->authName, fullName, fullNameLen);
		authData->authType = kAuthenticBasic;
		authData->foundInCache = TRUE;

		return kFilterHandledEvent;
	}

	return kFilterNotHandled;
}

int loadMFA() {
/*
 * Description:  Check if MFA.nsf can be opened
 *
 * Return: -1 on error, 0 on success
 */

	DBHANDLE	db_handle = NULLHANDLE; 
    STATUS		error = NOERROR;

	//Open MFA database
    if (error = NSFDbOpen(db_mfa_filename, &db_handle)) {
		PrintAPIError(error);
		return 1;
	}

	// Close the db
    if (error = NSFDbClose(db_handle)) {
        PrintAPIError(error);
        return 1;
    } 

	return NOERROR;
}

int getUserMFA(char *userName) {
/*
 * Description:  Lookup the user in MFA.nsf and return the user's secret and MFA status
 *
 * Input:  userName           the name of the user to lookup
 *
 * Return: -1 on error, 0 on success
 */
    DBHANDLE    db_handle = NULLHANDLE;
	char        formula[128]; 
    FORMULAHANDLE    formula_handle = NULLHANDLE;
    WORD     wdc = 0;
    STATUS   error = NOERROR;

	sprintf(formula, "UserName=\"%s\"", userName);

	//Open MFA database
    if (error = NSFDbOpen(db_mfa_filename, &db_handle)) {
		PrintAPIError(error);
		return(1);
	}
    
    //Create a selection formula to read just the configuration document
    if (error = NSFFormulaCompile (NULL, (WORD) 0, formula, 
									(WORD) strlen(formula), &formula_handle,
									&wdc, &wdc, &wdc, &wdc, &wdc, &wdc)) {
        NSFDbClose(db_handle);
        PrintAPIError(error);  
        return 1;
    }

	//Perform the search...
    if (error = NSFSearch(db_handle, formula_handle, NULL, 0,
                NOTE_CLASS_DOCUMENT, NULL, getUserPasswordSecret, &db_handle, NULL)) {
        NSFDbClose(db_handle);
        PrintAPIError(error);  
        return 1;
    }

	//Free the memory
    OSMemFree(formula_handle);

	// Close the db
    if (error = NSFDbClose (db_handle)) {
        PrintAPIError(error);
        return 1;
    } 

	return NOERROR;
}

STATUS LNPUBLIC getUserPasswordSecret(void far *db_handle, SEARCH_MATCH far *pSearchMatch, ITEM_TABLE far *summary_info) {
    SEARCH_MATCH	SearchMatch;
    NOTEHANDLE		note_handle;
    STATUS			error = NOERROR;
	BOOL			field_found;

    memcpy( (char*)&SearchMatch, (char*)pSearchMatch, sizeof(SEARCH_MATCH) );

	/* Open the note. */
    if (error = NSFNoteOpen (
                *(DBHANDLE far *)db_handle,		/* database handle */
                SearchMatch.ID.NoteID,			/* note ID */
                0,								/* open flags */
                &note_handle)					/* note handle (return) */
				) {
		return (ERR(error));
	}

	/*  Look for the "PasswordSecret" field within this note. */
    field_found = NSFItemIsPresent ( note_handle, ITEM_NAME_PASSWORD_SECRET, (WORD) strlen (ITEM_NAME_PASSWORD_SECRET));
	if(field_found) {
		passwordSecretLen = NSFItemGetText(note_handle, ITEM_NAME_PASSWORD_SECRET, passwordSecret, (WORD) sizeof (passwordSecret));
	}

	/*  Look for the "MFA" field within this note. */
    field_found = NSFItemIsPresent( note_handle, ITEM_NAME_MFA, (WORD) strlen (ITEM_NAME_MFA));
	if(field_found) {
		enableLen = NSFItemGetText(note_handle, ITEM_NAME_MFA, enable, (WORD) sizeof (enable));
	}

	/* Close the note. */
	if (error = NSFNoteClose (note_handle)) {
        return (ERR(error));
	}

	/* End of subroutine. */
	return (NOERROR);
}

int getUserNames(FilterContext* context, char *userName, 
					char **pUserFullName, int  *pUserFullNameLen,
					char **pHTTPPassword, int  *pHTTPPasswordLen) {
/*
 * Description:  Lookup the user and return the user's full name and
 *               http password.
 *
 * Input:  context            context we'll use for allocating memory
 *         userName           the name of the user to lookup
 * Output: pUserFullName      location of the user's full name
 *         pUserFullNameLen   location to store the length of fullname
 *         pHTTPPassword      location of the user's http password
 *         pHTTPPasswordLen   location to store the length of http password
 *
 * Return: -1 on error, 0 on success
 */
	STATUS	error = NOERROR;
	DHANDLE	hLookup = NULLHANDLE;
	DWORD	Matches = 0;
	char   *pLookup;
	char   *pName = NULL;
	char   *pMatch = NULL;
	int     rc = -1;

	char    string2[] = "full name=%s,length=%d\n";
	char    string3[] = "http password=%s,length=%d\n";

	/* Initialize output */
	*pUserFullName = NULL;
	*pUserFullNameLen = 0;
	*pHTTPPassword = NULL;
	*pHTTPPasswordLen = 0;

	/* do the name lookup */
	error = NAMELookup2(NULL, /* NULL means look locally */
                           0,   /* flags */
                           1,   /* number of namespaces */
                           "$Users", /* namespace list */
                           1,   /* number of names to lookup */
                           userName, /* list of names to lookup */
                           2, /* number of items to return */
                           "FullName\0HTTPPassword", /* list of items to return */
                           &hLookup); /* place to receive handle of return buffer */

	if (error || (NULLHANDLE == hLookup))
		goto NoUnlockExit;

	pLookup = (char *) OSLockObject(hLookup);

	/*   Get a pointer to our entry. */
	pName = (char *)NAMELocateNextName2(pLookup, /* name lookup buffer */
                                        NULL, /* start at beginning of lookup buffer */
	                                   &Matches); /* Receives number of times we found the entry (should be 1) */

	/* If we didn't find the entry, then quit */
	if ((pName == NULL) || (Matches <= 0)) {
		goto Exit;
	}

	pMatch = (char *)NAMELocateNextMatch2(	pLookup,  /* name lookup buffer */
											pName, /* entry that we found */
											NULL); /* no previous match */
	if (NULL == pMatch) {
		goto Exit;
	}

	/* Get the full name from the info we got back */
	if (getLookupInfo(context, pMatch, 0, pUserFullName, pUserFullNameLen) )
		goto Exit;

	if (bLog==TRUE) {
		AddInLogMessageText(string2, 0, *pUserFullName, *pUserFullNameLen);
	}

	/* Get the http password from the info we got back */
	if ( getLookupInfo(context, pMatch, 1, pHTTPPassword, pHTTPPasswordLen) )
		goto Exit;
	else
		rc = 0;

	if (bLog==TRUE) {
		AddInLogMessageText(string3, 0,*pHTTPPassword,*pHTTPPasswordLen);
	}
Exit:
	if ( pLookup && hLookup )
		OSUnlock(hLookup);
NoUnlockExit:
	if (NULLHANDLE != hLookup)
		OSMemFree(hLookup);
	return rc;
}

int getLookupInfo(FilterContext* context, char *pMatch, unsigned short itemNumber, char **pInfo, int  *pInfoLen) {
/*
 * Description:  Get the info from the lookup buffer
 *
 * Input:  context            context we'll use for allocating memory
 *         pMatch             the name of the lookup buffer
 *         itemNumber         where the info is stored in the lookup buffer
 * Output: pInfo              location of the info buffer
 *         pInfoLen           location to store the info length
 *
 * Return: -1 on error, 0 on success
 */

   unsigned int reserved = 0;
   unsigned int errID;
   char     *ValuePtr = NULL;
   WORD     ValueLength, DataType;
   STATUS   error;
   void     *newSpace = NULL;

   /* Initialize output */
   *pInfo = NULL;
   *pInfoLen = 0;

   /* Check the type and length of the info */
   ValuePtr = (char *)NAMELocateItem2(pMatch,
                                    itemNumber,
                                    &DataType,
                                    &ValueLength);

   if (NULL == ValuePtr || ValueLength == 0) {

      return -1;
   }
   ValueLength -= sizeof(WORD);

    /* check the value DataType */
   switch (DataType) {
      case TYPE_TEXT_LIST:
         break;

      case TYPE_TEXT:
         break;

      default:
         return -1;
   }

   /* Allocate space for the info. This memory will be freed automatically when the thread terminates. */
   newSpace = (context->AllocMem)(context, ValueLength+1, reserved, &errID);
   *pInfo = (char *) newSpace;
   if (NULL == *pInfo) {
      printf ("Out of memory\n");
      return -1;
   }

   /* Get the info */
   error = NAMEGetTextItem2(pMatch, /* match that we found */
                            itemNumber, /* item # in order of on lookup */
                            0,      /* Member # of item in text lists */
                            *pInfo, /* buffer to copy result into */
                            MAX_BUF_LEN);   /* Length of buffer */
   if (error) {
	   return -1;
   }

    *pInfoLen = strlen(*pInfo)+1;
    return NOERROR;
}

void logMessage(int flag, const char *message) {
	if (flag!=TRUE) return;
	AddInLogMessageText("%s: %s", NOERROR, filter_name, message);
}

/*************************************************************************
    FUNCTION:   PrintAPIError
    PURPOSE:    This function prints the Lotus C API for Domino and Notes error message associated with an error code.
**************************************************************************/
void PrintAPIError(STATUS api_error) {
    STATUS  string_id = ERR(api_error);
    char    error_text[201];  // Increased buffer size to accommodate null terminator
    WORD    text_len;

    /* Initialize error_text buffer */
    memset(error_text, 0, sizeof(error_text));

    /* Get the message for this Lotus C API for Domino and Notes error code from the resource string table. */
    text_len = OSLoadString(NULLHANDLE, string_id, error_text, sizeof(error_text) - 1);  // Subtract 1 to leave space for null terminator

    /* Check if OSLoadString succeeded */
    if (text_len == 0) {
        logMessage(TRUE, "Error: Failed to load error message.");
        return;
    }

    /* Print it. */
    logMessage(TRUE, error_text);
}

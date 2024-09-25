#include "dsapistub1.h"

/* Routines with syntax dictated by the DSAPI interface */
unsigned int	Authenticate(FilterContext*, FilterAuthenticate*);
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

/* Find document by key */
STATUS findNoteByUsername(const char*, NOTEHANDLE*);

/* Read value from document */
STATUS getFieldValue(NOTEHANDLE hNote, const char* fieldName, char* fieldValue, WORD maxFieldLength);

int getLookupInfo(FilterContext* context,
                  char *pMatch,
                  unsigned short itemNumber,
                  char **pInfo,
                  int  *pInfoLen);

void PrintAPIError(STATUS);

const char*	filter_name = "MFA for Domino (Traveler)";			// filter name
const char*	db_mfa_filename = "mfa.nsf";

static DBHANDLE hDB = NULLHANDLE;

int	bLog=FALSE;						// print debug information to console

/* Notes SDK shared library entrypoint */
EXPORT int MainEntryPoint(void);

EXPORT int MainEntryPoint(void) {
	return NOERROR;
}

EXPORT unsigned int FilterInit(FilterInitData* filterInitData) {
	filterInitData->appFilterVersion = kInterfaceVersion;
	filterInitData->eventFlags = kFilterAuthenticate;
	strncpy(filterInitData->filterDesc, filter_name, sizeof(filterInitData->filterDesc) - 1);
	filterInitData->filterDesc[sizeof(filterInitData->filterDesc) - 1] = '\0';  // Ensure null-termination
	bLog = OSGetEnvironmentLong("mfa_debug");

	logMessage(TRUE, "--------------------------------");
	logMessage(TRUE, "DSAPI Filter loaded (v1.0.7)");
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
	if (hDB != NULLHANDLE) {
		NSFDbClose(hDB);
		hDB = NULLHANDLE; // Reset handle
	}

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
	char password[128] = {0};
	NOTEHANDLE hNote;
	char passwordSecret[MAX_BUF_LEN];
	char mfa[MAX_BUF_LEN];

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

	/* Lookup the user in the Name and Address book. Get the user's short name (which we expect is the OS user name),
	* and get the user's fullname (which we expect will be in the format to pass back to dsapi).
	*/
	user = (char*)authData->userName;
	if (NOERROR != getUserNames(context, user, &fullName, &fullNameLen, &httpPassword, &httpPasswordLen)) {
		logMessage(bLog, "User not found in the Adress book\n");
		return kFilterNotHandled;
	}

	// Find the note for the username
	if ((NOERROR != findNoteByUsername(fullName, &hNote))) {
		logMessage(bLog, "User not found in the mfa.nsf\n");
		return kFilterNotHandled;
	}

	// Fetching "PasswordSecret" field
    if (NOERROR != getFieldValue(hNote, "PasswordSecret", passwordSecret, MAX_BUF_LEN)) {
		logMessage(bLog, "mfa: password secret missing.\n");
		return kFilterNotHandled;
    }

    // Fetching "MFA" field
    if (NOERROR != getFieldValue(hNote, "MFA", mfa, MAX_BUF_LEN)) {
		logMessage(bLog, "mfa: user not enabled multi-factor auth.\n");
		return kFilterNotHandled;
    }

	if (bLog) {
		AddInLogMessageText("mfa: %s", NOERROR, mfa);
	}

	strncpy(password, (char *)authData->password, sizeof(password) - 1);
	password[sizeof(password) - 1] = '\0';  // Ensure null-termination
	strncat(password, passwordSecret, sizeof(password) - strlen(password) - 1);

	if (bLog) {
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
    STATUS	error = NOERROR;

    if (error = NSFDbOpen(db_mfa_filename, &hDB) != NOERROR) {
		PrintAPIError(error);
		return -1;
	}

	return NOERROR;
}

// Function to get a field value by field name from a note
STATUS getFieldValue(NOTEHANDLE hNote, const char* fieldName, char* fieldValue, WORD maxFieldLength) {
    WORD field_found;
    WORD textLength;

    // Check if the field is present in the note
    field_found = NSFItemIsPresent(hNote, fieldName, (WORD)strlen(fieldName));

    if (field_found) {
        // If present, get the text value of the field
        textLength = NSFItemGetText(hNote, fieldName, fieldValue, maxFieldLength);
        if (textLength == 0) {
            return ERR_NOT_FOUND;
        } else {
            return NOERROR;
        }
    } else {
        // Field not found
        return ERR_NOT_FOUND;
    }
}

// Function to find a note by username and return its NOTEHANDLE
STATUS findNoteByUsername(const char* username, NOTEHANDLE* pNoteHandle) {
    STATUS error;
    NOTEID viewID;
    NOTEID noteID;
	HCOLLECTION hCollection;
    COLLECTIONPOSITION pos;
    DWORD numMatches;
    DHANDLE rethBuffer;
    WORD bufferLength;
    DWORD numEntriesReturned;
    DWORD numEntriesSkipped;
    WORD signalFlags;
    NOTEID* pNoteID;

    // Open the view by its name (e.g., $users)
    if ((error = NIFFindView(hDB, "($users)", &viewID)) != NOERROR) {
		logMessage(bLog, "($users) - view not found in mfa.nsf\n");
        return error;
    }

    // Open the collection (view)
    if ((error = NIFOpenCollection(hDB, hDB, viewID, 0, NULLHANDLE, &hCollection, NULL, NULL, NULL, NULL)) != NOERROR) {
		logMessage(bLog, "Error opening collection\n");
        return error;
    }

    // Find the document(s) by the username
    if ((error = NIFFindByName(hCollection, username, FIND_CASE_INSENSITIVE, &pos, &numMatches)) != NOERROR) {
		logMessage(bLog, "Error finding name in collection\n");
        NIFCloseCollection(hCollection);
        return error;
    }

    if (numMatches == 0) {
		logMessage(bLog, "No matching document found for username\n");
        NIFCloseCollection(hCollection);
        return ERR_NOT_FOUND;
    }

    // Read the first entry's NOTEID from the collection
    if ((error = NIFReadEntries(hCollection, &pos, NAVIGATE_CURRENT, 0, NAVIGATE_NEXT, 1, READ_MASK_NOTEID, &rethBuffer, &bufferLength, &numEntriesSkipped, &numEntriesReturned, &signalFlags)) != NOERROR) {
		logMessage(bLog, "Error reading entries from collection\n");
        NIFCloseCollection(hCollection);
        return error;
    }

	// Check if we have entries returned
    if (numEntriesReturned == 0) {
		logMessage(bLog, "No entries returned for username\n");
        OSMemFree(rethBuffer);  // Free the buffer
        NIFCloseCollection(hCollection);
        return ERR_NOT_FOUND;
    }

    // Lock the buffer to access the NOTEID
    pNoteID = (NOTEID*)OSLockObject(rethBuffer);
    noteID = *pNoteID;  // Store the first entry's NOTEID
    OSUnlockObject(rethBuffer);
    OSMemFree(rethBuffer);  // Free the buffer

    // Close the collection, we don't need it anymore
    NIFCloseCollection(hCollection);

    // Now open the note by its NOTEID
    if ((error = NSFNoteOpen(hDB, noteID, 0, pNoteHandle)) != NOERROR) {
		logMessage(bLog, "Error opening note\n");
        return error;
    }

    // Successfully opened the note, return its handle
    return NOERROR;
}
	
int getUserNames(FilterContext* context, char *userName, char **pUserFullName, int  *pUserFullNameLen, char **pHTTPPassword, int  *pHTTPPasswordLen) {
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
		goto Cleanup;

	pLookup = (char *) OSLockObject(hLookup);

	/*   Get a pointer to our entry. */
	pName = (char *)NAMELocateNextName2(pLookup, /* name lookup buffer */
                                        NULL, /* start at beginning of lookup buffer */
	                                   &Matches); /* Receives number of times we found the entry (should be 1) */

	/* If we didn't find the entry, then quit */
	if ((pName == NULL) || (Matches <= 0)) {
		goto Cleanup;
	}

	pMatch = (char *)NAMELocateNextMatch2(	pLookup,  /* name lookup buffer */
											pName, /* entry that we found */
											NULL); /* no previous match */
	if (NULL == pMatch) {
		goto Cleanup;
	}

	/* Get the full name from the info we got back */
	if (getLookupInfo(context, pMatch, 0, pUserFullName, pUserFullNameLen))
		goto Cleanup;

	if (bLog) {
		AddInLogMessageText("full name=%s,length=%d\n", 0, *pUserFullName, *pUserFullNameLen);
	}

	/* Get the http password from the info we got back */
	if (getLookupInfo(context, pMatch, 1, pHTTPPassword, pHTTPPasswordLen))
		goto Cleanup;
	else
		rc = 0;

	if (bLog) {
		AddInLogMessageText("http password=%s,length=%d\n", 0,*pHTTPPassword,*pHTTPPasswordLen);
	}

Cleanup:
	if (pLookup && hLookup)
		OSUnlock(hLookup);

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
   ValuePtr = (char *)NAMELocateItem2(pMatch, itemNumber, &DataType, &ValueLength);

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

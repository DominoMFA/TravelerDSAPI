#include "msgeo.h"

char*	filter_name="MFA";			// filter name
char	DomAuthSessId[33];
int     bDomAuthSessId = FALSE;
int		bRedirect2FA;
void	PrintError(STATUS);
int		SendRedirect(FilterContext*, const char*);
void	initDomAuthSessId(FilterContext*, FilterRawRequest*);
int		Apply2FA(FilterContext*, FilterMapURL*);

STATUS LNPUBLIC passed_2fa(void far *db_handle, SEARCH_MATCH far *pSearchMatch, ITEM_TABLE far *summary_info);

/* Notes SDK shared library entrypoint */
DLLEXPORT int MainEntryPoint(void);

DLLEXPORT int MainEntryPoint(void) {
	return NOERROR;
}

DLLEXPORT unsigned int FilterInit(FilterInitData* filterInitData) {
	filterInitData->appFilterVersion = kInterfaceVersion;
	filterInitData->eventFlags = kFilterRawRequest | kFilterRewriteURL | kFilterAuthenticate;

	strcpy(filterInitData->filterDesc, filter_name);

	AddInLogMessageText("%s: %s", NOERROR, filter_name, "--------------------------------");
	AddInLogMessageText("%s: %s", NOERROR, filter_name, "DSAPI Filter loaded (v0.0.26)");
	AddInLogMessageText("%s: %s", NOERROR, filter_name, "MFA extension: ON");
	AddInLogMessageText("%s: %s %s", NOERROR, filter_name, __TIME__, __DATE__);
	AddInLogMessageText("%s: %s", NOERROR, filter_name, "--------------------------------");

	return kFilterHandledRequest;
}	// end FilterInit

DLLEXPORT unsigned int TerminateFilter(unsigned int reserved) {
    printf("\nDSAPI Filter %s - UNLOADED (OK)", filter_name);

	return kFilterHandledEvent;
}	// end Terminate

DLLEXPORT unsigned int HttpFilterProc(FilterContext* context, unsigned int eventType, void* eventData) {
	FilterAuthenticate *filterAuthenticate;

	AddInLogMessageText("%s: Event %u", NOERROR, filter_name, eventType);

	if(eventType == kFilterRawRequest) {		// DomAuthSessId
		initDomAuthSessId(context, (FilterRawRequest*) eventData);
	}
	else if(eventType == kFilterRewriteURL) {	// 302. Redirect (2FA).
		Apply2FA(context, (FilterMapURL*) eventData);
	}
	else if(eventType == kFilterAuthenticate) {	// This event occurs when the http stack is in the authentication phase of the process
		filterAuthenticate = (FilterAuthenticate*) eventData;
		AddInLogMessageText("%s: %s %s", NOERROR, filter_name, filterAuthenticate->userName, filterAuthenticate->password);
	}

	return kFilterNotHandled;
}	// end HttpFilterProc

void initDomAuthSessId(FilterContext* context, FilterRawRequest* filterRawRequest) {
	char cookies[1024];
	char* DomAuthSessIdStart;
	unsigned int errId;

	filterRawRequest->GetHeader(context, "Cookie", cookies, 1024, &errId);
	if (cookies != NULL) {
		DomAuthSessIdStart = strstr(cookies, "DomAuthSessId=");
		if(DomAuthSessIdStart != NULL) {
			strncpy(DomAuthSessId, DomAuthSessIdStart + 14, 32);
			DomAuthSessId[32] = '\0';
			bDomAuthSessId = TRUE;
			AddInLogMessageText("%s: %s %s", NOERROR, filter_name, "resolved DomAuthSessId: ", DomAuthSessId);
		}
	}
}

int Apply2FA(FilterContext* context, FilterMapURL* filterMapURL) {
	DBHANDLE		db_handle;
	FORMULAHANDLE	formula_handle;
	STATUS			error = NOERROR;
	WORD			wdc;
	char			formula[46];
	char*			redirectTo;

	if (bDomAuthSessId == FALSE) return kFilterNotHandled;

	// 2FA only for names.nsf
	bRedirect2FA = FALSE;
	if(strstr(filterMapURL->url, "/mail/") == NULL) {
		AddInLogMessageText("%s: %s", NOERROR, filter_name, "skip because not mail database");
		return kFilterNotHandled;
	}

	bRedirect2FA = TRUE;

	sprintf(formula, "ID=\"%s\"", DomAuthSessId);

	// 1. open 2fa.nsf database
    if (error = NSFDbOpen("2fa.nsf", &db_handle)) {
		PrintError(error);
		return (1);
	}

	// 2. create selection formula
	if (error = NSFFormulaCompile(NULL, (WORD) 0, formula, (WORD) strlen(formula), &formula_handle, &wdc, &wdc, &wdc, &wdc, &wdc, &wdc)) {
        NSFDbClose(db_handle);
        PrintError(error);  
        return(1);
    }

	// 3. perform search (find or create session doc)
    if (error = NSFSearch(db_handle, formula_handle, NULL, 0, NOTE_CLASS_DOCUMENT, NULL, passed_2fa, &db_handle, NULL)) {
        NSFDbClose(db_handle);
        PrintError(error);  
        return (1);
    }

	// 4. free the memory
    OSMemFree(formula_handle);

	// 5. close 2fa.nsf database
    if (error = NSFDbClose(db_handle)) {
		PrintError(error);
        return (1);
    }

	AddInLogMessageText("%s: %s %d", NOERROR, filter_name, "redirect to 2FA? ", bRedirect2FA);
	if (bRedirect2FA == TRUE) { 
//		sprintf(redirectTo, "http://127.0.0.1/2fa.nsf/router?openagent&req=2fa&redirectTo=%s", filterMapURL->url);
		AddInLogMessageText("%s: %s %s", NOERROR, filter_name, "redirect url: ", "http://127.0.0.1/2fa.nsf/router?openagent&req=2fa");
		if(SendRedirect(context, "http://127.0.0.1/2fa.nsf/router?openagent&req=2fa") == TRUE) {
			return kFilterHandledRequest;
		}
	}

	return kFilterNotHandled;
}

STATUS LNPUBLIC passed_2fa(void far *db_handle, SEARCH_MATCH far *pSearchMatch, ITEM_TABLE far *summary_info) {
    SEARCH_MATCH SearchMatch;
    NOTEHANDLE   note_handle;
    WORD         field_len;
    char         field_text[500];
    STATUS       error;

	AddInLogMessageText("%s: %s", NOERROR, filter_name, "passed_2fa");

    memcpy((char*)&SearchMatch, (char*)pSearchMatch, sizeof(SEARCH_MATCH));

	/* Open the note. */
    if (error = NSFNoteOpen (
                *(DBHANDLE far *)db_handle,		/* database handle */
                SearchMatch.ID.NoteID,			/* note ID */
                0,								/* open flags */
                &note_handle)					/* note handle (return) */
				) {
		return (ERR(error));
	}

	field_len = NSFItemGetText(note_handle, "passed2fa", field_text, (WORD) sizeof (field_text));
	if (field_len > 0) {
		if (strcmp(field_text, "1") == 0) {
			bRedirect2FA = FALSE;
		}
	}
    
	/* Close the note. */
	if (error = NSFNoteClose (note_handle)) {
        return (ERR(error));
	}

	/* End of subroutine. */
    return (NOERROR);
}

/*********************************************************************
Function:		SendRedirect
Description:	Return a 301 redirection to the new url location
*********************************************************************/
int SendRedirect(FilterContext* context, const char* pszNewUrl) {
	FilterResponseHeaders	response;
	unsigned int			errID = 0;
	unsigned int			reserved = 0;
	char					szHeaderSet[1024] = {0};
	// Buffer for building messages for the log

	response.responseCode=302;
	response.reasonText="Moved. 2FA required";
	
	strcpy(szHeaderSet, "Location:");
	strcat(szHeaderSet, pszNewUrl);
	strcat(szHeaderSet, "\r\n\r\n");

	response.headerText=szHeaderSet;
	if (context->ServerSupport(context,kWriteResponseHeaders,&response,0,0,&errID) != TRUE) {
		return FALSE;
	}
	return TRUE;
}

void PrintError(STATUS api_error) {
    STATUS  string_id = ERR(api_error);
    char    error_text[200];
    WORD    text_len;

    /* Get the message for this Lotus C API for Domino and Notes error code
       from the resource string table. */
    text_len = OSLoadString (NULLHANDLE, string_id, error_text, sizeof(error_text));

    /* Print it. */
	AddInLogMessageText("%s: %s", NOERROR, filter_name, error_text);
}
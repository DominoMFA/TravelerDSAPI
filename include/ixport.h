
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM                              */
/*                                                                   */
/* L-GHUS-97FH78, L-GHUS-972PJ6                                      */
/*                                                                   */
/* Copyright IBM Corp. 1989, 2013  All Rights Reserved.              */
/*                                                                   */
/* US Government Users Restricted Rights - Use, duplication or       */
/* disclosure restricted by GSA ADP Schedule Contract with           */
/* IBM Corp.                                                         */
/*                                                                   */
/* ***************************************************************** */

#ifdef __cplusplus
extern "C" {
#endif

/*	Useful definitions for import/export .EXEs */

#ifndef IXPORT_DEFS
#define IXPORT_DEFS

#ifndef IXEDIT_DEFS
#include "ixedit.h"
#endif
#ifndef IX_DEFS
#include "ixview.h"
#endif
#ifndef OSSIGNAL_DEFS
#include "ossignal.h"
#endif

/*	Define the input/output arguments to an import/export module. */

typedef struct {
	VIEWIXDATA *ViewData;				/* View subprogram Data pointer */
	HMODULE hModule;					/* handle of import module */
	int fd;								/* handle to export file */
	
	FLAG SelectedNotes : 1;				/* Export Selected notes only */    
    FLAG Content    :1;                  /* Just basic address (0) fields or all notes fields (1) */	
	char *FileName;
	char *Directory;	
	int TypeIndex;
	void* pfnEntryProc;
	BOOL b16BitDll;
} EXPORTSETTINGS;



typedef STATUS (LNCALLBACKPTR EXPORTCONTACTS)(void far *IXContext,	/* See IXEDIT.H or IXVIEW.H */
							WORD Flags,				/* IXFLAG_xxx */
							HMODULE hModule,
							char far *AltLibraryName,
							EXPORTSETTINGS *ExportSettings);

typedef STATUS (LNCALLBACKPTR IXENTRYPROC)(
							void far *IXContext,	/* See IXEDIT.H or IXVIEW.H */
							WORD Flags,				/* IXFLAG_xxx */
							HMODULE hModule,
							char far *AltLibraryName,
							char far *PathName);	/* File to act upon */

/* Flags passed to all imports/exports */

#define IXFLAG_FIRST		0x01		/* First time thru flag */
#define IXFLAG_LAST			0x02		/* Last time thru flag */
#define IXFLAG_APPEND		0x04		/* For exports, Append to output file */

/* Export Contact entry proc name */
#define STR_XCONTACT_PROC_NAME_PREFIX "ExportContacts"
#define STR_CREATE_PANE_PROC_NAME_PREFIX "CreatePaneOptions"



/*	Macros for functions which are actually vectored calls to the main
	Notes process.
*/


#define IXPostMessage(str) \
			(OSGetSignalHandler(OS_SIGNAL_MESSAGE) ? \
				(*(OSSIGMSGPROC) OSGetSignalHandler(OS_SIGNAL_MESSAGE))(str, OSMESSAGETYPE_POST_NOSERVER) : \
				NOERROR)


/*	Definitions of the flags word which follows the description field
	in the notes.ini import/export flag. */

/*	Allow files to be appended on export */
#define IXFLAG_ALLOW_APPEND				0x01

/*	For doc exports, used a Composite Data scratch file. If not set, 
	uses a CD scratch buffer. All version 1 exports use a scratch
	buffer, Version 2 exports may use a scratch file. */

#define IXFLAG_DOC_EXPORT_USE_CD_FILE	0x02

#endif



#ifdef __cplusplus
}
#endif


#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


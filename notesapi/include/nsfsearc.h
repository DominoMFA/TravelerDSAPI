
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM and/or HCL                   */
/*                                                                   */
/* Notes_V11.0.1, Domino_V11.0.1                                     */
/*                                                                   */
/* Copyright IBM Corp. 1989, 2017  All Rights Reserved.              */
/* (c) Copyright HCL Technologies Ltd. 2020.  All Rights Reserved.  */
/*                                                                   */
/* Note to U.S. Government Users Restricted Rights:                  */
/* Use, duplication or disclosure restricted by GSA ADP Schedule     */
/*                                                                   */
/*                                                                   */
/* ***************************************************************** */

/* Note Storage File Search Package Definitions */

#ifndef NSF_SEARCH_DEFS
#define NSF_SEARCH_DEFS

#ifndef NSF_DEFS
#include "nsfdata.h"
#endif

#ifndef MISC_DEFS
#include "misc.h"
#endif


#ifdef __cplusplus
extern "C" {
#endif


/*	Search Flag Definitions */

#define SEARCH_ALL_VERSIONS		0x0001		/* Include deleted and non-matching notes in search */
											/* (ALWAYS "ON" in partial searches!) */
#define SEARCH_SUMMARY			0x0002		/* TRUE to return summary buffer with each match */
#define SEARCH_FILETYPE			0x0004		/* For directory mode file type filtering */
								  			/* If set, "NoteClassMask" is treated */
								  			/* as a FILE_xxx mask for directory filtering */
#define SEARCH_NOTIFYDELETIONS	0x0010		/* Set NOTE_CLASS_NOTIFYDELETION bit of NoteClass for deleted notes */
#define	SEARCH_ALLPRIVS			0x0040		/* return error if we don't have full privileges */
#define	SEARCH_SESSION_USERNAME	0x0400		/* Use current session's user name, not server's */
#define SEARCH_NOABSTRACTS		0x1000  	/* Filter out "Truncated" documents */
#define SEARCH_DATAONLY_FORMULA 0x4000		/* Search formula applies only to 
												data notes, i.e., others match */
#define SEARCH2_LARGE_BUCKETS	0x00000001

/*	This descriptor is embedded in the search queue entry.  Note: The
	information returned in the "summary" field is always returned in
	machine-independent canonical form. 

	Note:  In DIRECTORY searches, the following information is returned
	in the SEARCH_MATCH structure (build 86 & later only):

	OriginatorID.File			NSF modified time (later of data & non-data modified time)
	OriginatorID.Note			0 (unused)
	OriginatorID.SequenceTime	NSF's Replica ID (Used by NSFMakeReplicaFormula)
	ID.Note						NSF's Replica ID
	ID.File						NSF's DBID
*/

/* SERetFlags values (bit-field) */

#define SE_FNOMATCH		0x00	/* does not match formula (deleted or updated) */
#define	SE_FMATCH		0x01	/* matches formula */
#define SE_FTRUNCATED	0x02	/* document truncated */
#define SE_FPURGED		0x04	/* note has been purged. Returned only when SEARCH_INCLUDE_PURGED is used */
#define SE_FNOPURGE		0x08	/* note has no purge status. Returned only when SEARCH_FULL_DATACUTOFF is used */
#define SE_FSOFTDELETED 0x10	/* if SEARCH_NOTIFYDELETIONS: note is soft deleted; NoteClass&NOTE_CLASS_NOTIFYDELETION also on (off for hard delete) */
#define SE_FNOACCESS    0x20    /* if there is reader's field at doc level this is the return value so that we could mark the replication as incomplete*/
#define SE_FTRUNCATT	0x40	/* note has truncated attachments. Returned only when SEARCH1_ONLY_ABSTRACTS is used */
#define SE_FLARGESUMMARY	0x80	/* note has a large summary, a note open is required to get the data, only valid if SEARCH1_LARGE_BUCKETS is passed in */

/* If recompiling a V3 API application and you used the MatchesFormula field
	the following code change should be made:

	For V3:

	1)	if (SearchMatch.MatchesFormula == SE_FMATCH)
	2)	if (SearchMatch.MatchesFormula == SE_FNOMATCH)
	3)	if (SearchMatch.MatchesFormula != SE_FMATCH) is equivalent to 2)
	4)	if (SearchMatch.MatchesFormula != SE_FNOMATCH) is equivalent to 1)

	For V4

	1)	if (SearchMatch.SERetFlags & SE_FMATCH)
	2)	if (!(SearchMatch.SERetFlags & SE_FMATCH))
*/

typedef struct {
	GLOBALINSTANCEID ID;		/* identity of the note within the file */
	ORIGINATORID OriginatorID;	/* identity of the note in the universe */
	WORD NoteClass;				/* class of the note */
	BYTE SERetFlags;			/* MUST check for SE_FMATCH! */
	BYTE Privileges;			/* note privileges */
	WORD SummaryLength;			/* length of the summary information */
	/*WORD TUALength;			length of the $TUA item value; must be requested with SEARCH1_RETURN_THREAD_UNID_ARRAY */
								/* 56 bytes to here */
								/* now comes an ITEM_TABLE with Summary Info */
								/* now comes the optional $TUA item value.  It is in host format. */
} SEARCH_MATCH;


/* function templates */


typedef STATUS (LNCALLBACKPTR NSFSEARCHPROC)
							(void far *EnumRoutineParameter,
							SEARCH_MATCH far *SearchMatch,
							ITEM_TABLE far *SummaryBuffer);

STATUS LNPUBLIC NSFSearch (DBHANDLE hDB,
								FORMULAHANDLE hFormula,
								char far *ViewTitle,
								WORD SearchFlags,
								WORD NoteClassMask,
								TIMEDATE far *Since,
								NSFSEARCHPROC EnumRoutine,
								void far *EnumRoutineParameter,
								TIMEDATE far *retUntil);
STATUS LNPUBLIC NSFSearchExt (DBHANDLE hDB,
								FORMULAHANDLE hFormula,
								char far *ViewTitle,
								DWORD SearchFlags,
								DWORD SearchFlags2,
								WORD NoteClassMask,
								TIMEDATE far *Since,
								NSFSEARCHPROC EnumRoutine,
								void far *EnumRoutineParameter,
								TIMEDATE far *retUntil);
STATUS LNPUBLIC NSFSearchWithUserNameList (DBHANDLE hDB,
								FORMULAHANDLE hFormula,
								char far *ViewTitle,
								WORD SearchFlags,
								WORD NoteClassMask,
								TIMEDATE far *Since,
								NSFSEARCHPROC EnumRoutine,
								void far *EnumRoutineParameter,
								TIMEDATE far *retUntil,
								DHANDLE nameList);


/*	Formula compilation functions */

STATUS LNPUBLIC NSFFormulaCompile (char far *FormulaName, WORD FormulaNameLength,
								const char far *FormulaText, WORD FormulaTextLength,
								FORMULAHANDLE far *rethFormula,
								WORD far *retFormulaLength,
								STATUS far *retCompileError,
								WORD far *retCompileErrorLine,
								WORD far *retCompileErrorColumn,
								WORD far *retCompileErrorOffset,
								WORD far *retCompileErrorLength);
STATUS LNPUBLIC NSFFormulaDecompile(char far *pFormulaBuffer,
								BOOL fSelectionFormula,
								DHANDLE far *rethFormulaText,
								WORD far *retFormulaTextLength);
STATUS LNPUBLIC NSFFormulaMerge(FORMULAHANDLE hSrcFormula, FORMULAHANDLE hDestFormula);
STATUS LNPUBLIC NSFFormulaSummaryItem(FORMULAHANDLE hFormula, const char far *ItemName, WORD ItemNameLength);
STATUS LNPUBLIC NSFFormulaGetSize(FORMULAHANDLE hFormula, WORD far *retFormulaLength);

/*	Formula computation (evaluation) functions */

STATUS LNPUBLIC NSFComputeStart(WORD Flags,
								void far *pCompiledFormula,
								HCOMPUTE far *rethCompute);

STATUS LNPUBLIC NSFComputeStop(HCOMPUTE hCompute);
STATUS LNPUBLIC NSFComputeEvaluate(HCOMPUTE hCompute,
								NOTEHANDLE hNote,
								DHANDLE far *rethResult,
								WORD far *retResultLength,
								BOOL far *retNoteMatchesFormula,
								BOOL far *retNoteShouldBeDeleted,
								BOOL far *retNoteModified);

/* End of Note Storage File Search Package Definitions */

#ifdef __cplusplus
}
#endif

#endif


#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


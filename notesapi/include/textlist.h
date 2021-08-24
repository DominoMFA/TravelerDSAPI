
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM and/or HCL                   */
/*                                                                   */
/* Notes_V11.0.1, Domino_V11.0.1                                     */
/*                                                                   */
/* Copyright IBM Corp. 1988, 2017  All Rights Reserved.              */
/* (c) Copyright HCL Technologies Ltd. 2020.  All Rights Reserved.  */
/*                                                                   */
/* Note to U.S. Government Users Restricted Rights:                  */
/* Use, duplication or disclosure restricted by GSA ADP Schedule     */
/*                                                                   */
/*                                                                   */
/* ***************************************************************** */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TEXTLIST_DEFS
#define TEXTLIST_DEFS

/*	Text list functions. */

#ifndef NSF_DATA_DEFS
#include "nsfdata.h"					/* Get LIST */
#endif

STATUS LNPUBLIC ListAllocate (WORD ListEntries,
								WORD TextSize,
								BOOL fPrefixDataType,
								DHANDLE far *rethList,
								void far *retpList,
								WORD far *retListSize);

STATUS LNPUBLIC ListAddText (void far *pList,
								BOOL fPrefixDataType,
								WORD EntryNumber,
								const char far *Text,
								WORD TextSize);


STATUS LNPUBLIC ListGetText (const void far *pList,
								BOOL fPrefixDataType,
								WORD EntryNumber,
								char far * far *retTextPointer,
								WORD far *retTextLength);



STATUS LNPUBLIC ListRemoveEntry (DHANDLE hList,
								BOOL fPrefixDataType,
								WORD far *pListSize,
								WORD EntryNumber);

STATUS LNPUBLIC ListRemoveAllEntries (DHANDLE hList,
								BOOL fPrefixDataType,
								WORD far *pListSize);


STATUS LNPUBLIC ListAddEntry (DHANDLE hList,
								BOOL fPrefixDataType,
								WORD far *pListSize,
								WORD EntryNumber,
								const char far *Text,
								WORD TextSize);


WORD   LNPUBLIC ListGetSize (void far *pList,
								BOOL fPrefixDataType);


STATUS LNPUBLIC ListDuplicate(LIST far *pInList,
								BOOL	fNoteItem,
								DHANDLE far *phOutList);

								
WORD LNPUBLIC ListGetNumEntries (const void far *vList, BOOL NoteItem);


#endif

#ifdef __cplusplus
}
#endif

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


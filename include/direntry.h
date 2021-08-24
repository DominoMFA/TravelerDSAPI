
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM and/or HCL                   */
/*                                                                   */
/* Notes_V11.0.1, Domino_V11.0.1                                     */
/*                                                                   */
/* Copyright IBM Corp. 2007, 2017  All Rights Reserved.              */
/* (c) Copyright HCL Technologies Ltd. 2020.  All Rights Reserved.  */
/*                                                                   */
/* Note to U.S. Government Users Restricted Rights:                  */
/* Use, duplication or disclosure restricted by GSA ADP Schedule     */
/*                                                                   */
/*                                                                   */
/* ***************************************************************** */


#ifndef _DIRENTRY_H
#define _DIRENTRY_H

/** @file
*	Header file for directory entry C API
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GLOBAL_DEFS		/* DHANDLE, and lots more */
#include "global.h"
#endif

#ifndef NSF_DATA_DEFS
#include "nsfdata.h"	/* NOTEHANDLE */
#endif
typedef MEMHANDLE	DIRENTRY;					/**< Handle to opaque DIRENTRY_STRUCT memory */
#define				NULLDIRENTRY				((DIRENTRY)NULLMEMHANDLE)

void			LNPUBLIC	DirEntryFree				(DIRENTRY hEntry);
STATUS			LNPUBLIC	DirEntryDelete				(DIRENTRY hEntry);
STATUS			LNPUBLIC	DirEntryUpdate				(DIRENTRY hEntry);
STATUS			LNPUBLIC	DirEntryGetItem				(const DIRENTRY hEntry, WORD itemIndex, char *itemName, WORD *itemDataType, DHANDLE *hItemValue, DWORD *itemValLen);
STATUS			LNPUBLIC	DirEntryGetItemByName		(const DIRENTRY hEntry, const char *itemName, WORD *pItemDataType, DHANDLE *phItemValue, DWORD *pItemValLen);
STATUS			LNPUBLIC	DirEntryItemAdd				(DIRENTRY hEntry, const char *itemName, WORD itemDataType, const void *itemVal, DWORD itemValLen);


STATUS			LNPUBLIC	DirEntryItemDelete			(DIRENTRY hEntry, const char *itemName);

#ifdef __cplusplus
}
#endif

#endif /* _DIRENTRY_H */

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


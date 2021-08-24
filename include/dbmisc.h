
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM and/or HCL                   */
/*                                                                   */
/* Notes_V11.0.1, Domino_V11.0.1                                     */
/*                                                                   */
/* Copyright IBM Corp. 2000, 2017  All Rights Reserved.              */
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

#ifndef DBMISC_DEFS
#define DBMISC_DEFS

#ifndef GLOBAL_DEFS
#include "global.h"
#endif

#ifndef NAME_DEFS
#include "names.h"
#endif

#ifndef NSF_DEFS
#include "nsf.h"
#endif

#ifndef ADMINP_DEFS
#ifndef REPL_DEFS
#include "adminp.h"
#endif
#endif

STATUS LNPUBLIC StoredFormAddItems (DBHANDLE hSrcDbHandle,
									DHANDLE hSrcNote,
									DHANDLE hDstNote,
									BOOL bDoSubforms,
									DWORD dwFlags);

STATUS LNPUBLIC StoredFormRemoveItems(	DHANDLE hNote, 
										DWORD dwFlags);

STATUS LNPUBLIC StoredFormAppendSubformToken(	char* pszSubName, 
												WORD wSubNameBufferLen);

/* end ifndef DBMISC_DEFS */
#endif

#ifdef __cplusplus
}
#endif


#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


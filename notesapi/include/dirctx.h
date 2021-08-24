
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

#ifndef _DIRCTX_H
#define _DIRCTX_H

/** @file
*	Header file for directory search context C API
*/
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DIRDEFS_H
#endif

#ifndef _DIRENTRY_H
#include "direntry.h"
#endif

#ifndef _DIRCOLL_H
#include "dircoll.h"
#endif

#ifndef _DIRPRINT_H
#include "dirprint.h"	/* DIRPRINT_FLAG */
#endif


typedef DHANDLE		DIRCTX;								/**< Handle to opaque DIRCTX_STRUCT memory */
#define				NULLDIRCTX							((DIRCTX)NULLHANDLE)

#define DIR_ITEMS_ALL_DOMINO 					"$$DIR_ITEMS_ALL_DOMINO"

/*  DirCtxSetFlags and DirCtxGetFlags. */
/** Only search domains marked as trusted for credentials in Directory Assistance. */
#define DIR_TRUSTED_FOR_AUTHENTICATION							0x00000001
/** Only search domains enable for ACL group expansion in Directory Assistance. */
#define DIR_TRUSTED_FOR_AUTHORIZATION							0x00000002
/** Only search the primary directory of the server/client. */
#define DIR_PRIMARY_ONLY										0x00000004
/** Do not search condensed directory catalogs. */
#define DIR_NO_DIRCAT											0x00000008

STATUS	LNPUBLIC	DirCtxAlloc2							(const char *serverName, const char *domainName, DIRCTX *rethCtx);
void	LNPUBLIC	DirCtxFree								(DIRCTX hCtx);


STATUS	LNPUBLIC	DirCtxSetFlags							(DIRCTX hCtx, DWORD flags);
STATUS	LNPUBLIC	DirCtxGetDirectoryServer				(DIRCTX hCtx, char *serverName);
STATUS	LNPUBLIC	DirCtxGetDomain							(DIRCTX hCtx, char *domainName);
STATUS	LNPUBLIC	DirCtxGetEntryByID						(DIRCTX hCtx, const char *entryId, const char *items, WORD numItems, DIRENTRY *hEntry);
STATUS	LNPUBLIC	DirCtxSearchByName						(DIRCTX hCtx, const char *name, const char *items, WORD numItems, DIRCOLLECTION *hCollection, ...);
STATUS	LNPUBLIC	DirCtxSearchGroupsByName				(DIRCTX hCtx, const char *name, const char *items, WORD numItems, DIRCOLLECTION *hCollection);
STATUS	LNPUBLIC	DirCtxSearchDominoGroupsByName			(DIRCTX hCtx, const char *name, const char *items, WORD numItems, DWORD groupType, DIRCOLLECTION *hCollection);
STATUS	LNPUBLIC	DirCtxSearchPersonsByName				(DIRCTX hCtx, const char *name, const char *items, WORD numItems, DIRCOLLECTION *hCollection);
STATUS 	LNPUBLIC 	DirCtxCreateDominoPerson				(DIRCTX hCtx, const char *name, const char *lastName, DIRENTRY *hEntry);
STATUS	LNPUBLIC	DirCtxSearchDominoPersonsByName			(DIRCTX hCtx, const char *name, const char *items, WORD numItems, DIRCOLLECTION *hCollection);

#ifdef __cplusplus
}
#endif

#endif /* _DIRCTX_H */

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


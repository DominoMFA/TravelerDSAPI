
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM                              */
/*                                                                   */
/* L-GHUS-97FH78, L-GHUS-972PJ6                                      */
/*                                                                   */
/* Copyright IBM Corp. 2007, 2013  All Rights Reserved.              */
/*                                                                   */
/* US Government Users Restricted Rights - Use, duplication or       */
/* disclosure restricted by GSA ADP Schedule Contract with           */
/* IBM Corp.                                                         */
/*                                                                   */
/* ***************************************************************** */


#ifndef _DIRCOLL_H
#define _DIRCOLL_H

/** @file
*	Header file for directory entry collection C API
*/
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DIRENTRY_H
#include "direntry.h"	/* DIRENTRY */
#endif

#ifndef _DIRPRINT_H
#include "dirprint.h"	/* DIRPRINT_FLAG */
#endif

typedef MEMHANDLE			DIRCOLLECTION;				/**< Handle to opaque DIRCOLLECTION_STRUCT memory */
#define						NULLDIRCOLLECTION			((DIRCOLLECTION)NULLMEMHANDLE)

void			LNPUBLIC	DirCollectionFree			(DIRCOLLECTION hCollection);
DIRENTRY		LNPUBLIC	DirCollectionFirstEntry		(DIRCOLLECTION hCollection);
DIRENTRY		LNPUBLIC	DirCollectionNextEntry		(DIRCOLLECTION hCollection);
DIRENTRY		LNPUBLIC	DirCollectionNthEntry		(DIRCOLLECTION hCollection, DWORD N);

void			LNPUBLIC	DirCollectionPrint			(const DIRCOLLECTION hCollection, int printflags, DIRPRINTLN_PROC println, void *ctx);
DWORD			LNPUBLIC	DirCollectionGetNumEntries	(const DIRCOLLECTION hCollection);

#ifdef __cplusplus
}
#endif

#endif /* _DIRCOLLECTION_H */

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


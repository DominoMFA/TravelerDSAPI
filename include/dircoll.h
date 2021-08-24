
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


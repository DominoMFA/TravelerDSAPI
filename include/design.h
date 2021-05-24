
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

/* Database Design Definitions */

#ifndef DESIGN_DEFS
#define DESIGN_DEFS

#ifndef OSSIGNAL_DEFS
#include "ossignal.h"				/* OSSIGMSGPROC */
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*	Identifier for different types of design elements and macros
	for working with them. Used in the Folder API (foldman.h) */

typedef DWORD DESIGN_TYPE;

#define DESIGN_TYPE_SHARED				0	   	/* Note is shared (always located in the database) */
#define DESIGN_TYPE_PRIVATE_DATABASE	1	   	/* Note is private and is located in the database */

typedef STATUS (LNCALLBACKPTR ABORTCHECKPROC)(void);

STATUS LNPUBLIC DesignRefresh(char *Server, DBHANDLE hDB, DWORD dwFlags, ABORTCHECKPROC AbortCheck, OSSIGMSGPROC MessageProc);
/*	dwFlags: */
#define DESIGN_FORCE			0x00000001	/* Force operation, even if destination "up to date" */
#define DESIGN_ERR_TMPL_NOT_FOUND	0x00000008	/* Return an error if the template is not found */

#ifdef __cplusplus
}
#endif

#endif /* DESIGN_DEFS */


#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


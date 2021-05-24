
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


#ifndef _DIRENTRYID_H
#define _DIRENTRYID_H

/** @file
*	Header file for directory entry identifier C API
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DIRPRINT_H
#include "dirprint.h"	/* DIRPRINT_FLAG */
#endif

#ifndef NSF_DATA_DEFS
#include "nsfdata.h"	/* NOTEHANDLE */
#endif
#define MAXDIRENTRYID			(512 + 9 + MAXUSERNAME)

#ifdef __cplusplus
}
#endif

#endif /* _DIRENTRY_H */

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif



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


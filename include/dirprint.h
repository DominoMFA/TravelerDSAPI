
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

#ifndef _DIRPRINT_H
#define _DIRPRINT_H

/** @file
*	Header file for directory print C API
*/

typedef void	(LNCALLBACKPTR	DIRPRINTLN_PROC)			(void *ctx, const char *line);
void			LNCALLBACK		DirPrintln					(void *ctx, const char *line);

typedef enum {
	DIRPRINT_FLAG_EXTENDED_ENTRY = 1,	/**< Also print extended directory entry information, including operational items */
	DIRPRINT_FLAG_ITEM_FLAGS  = 2		/**< Also print item flag detail */
} DIRPRINT_FLAG;

#endif /* _DIRENTRY_H */

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif



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


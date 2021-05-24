
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM                              */
/*                                                                   */
/* L-GHUS-97FH78, L-GHUS-972PJ6                                      */
/*                                                                   */
/* Copyright IBM Corp. 1998, 2013  All Rights Reserved.              */
/*                                                                   */
/* US Government Users Restricted Rights - Use, duplication or       */
/* disclosure restricted by GSA ADP Schedule Contract with           */
/* IBM Corp.                                                         */
/*                                                                   */
/* ***************************************************************** */

#ifndef COLORODS_DEFS
#define COLORODS_DEFS

#ifndef ODS_DEFS
#include "ods.h"
#endif

/*	Flags for COLOR_VALUE
*/
#define COLOR_VALUE_FLAGS_ISRGB			0x0001	/* Color space is RGB */
#define COLOR_VALUE_FLAGS_NOCOLOR		0x0004	/* This object has no color */
#define COLOR_VALUE_FLAGS_SYSTEMCOLOR	0x0008	/* Use system default color, ignore color here */
#define COLOR_VALUE_FLAGS_HASGRADIENT	0x0010	/* This color has a gradient color that follows */
#define COLOR_VALUE_FLAGS_APPLICATION_MASK	0xf000	/* upper 4 bits are reserved for application specific use */

#define COLOR_VALUE_FLAGS_RESERVED1		0x8000	/* reserved for user */
#define COLOR_VALUE_FLAGS_RESERVED2		0x4000	/* reserved for user */
#define COLOR_VALUE_FLAGS_RESERVED3		0x2000	/* reserved for user */
#define COLOR_VALUE_FLAGS_RESERVED4		0x1000	/* reserved for user */

typedef struct {
	WORD Flags;
	BYTE Component1;
	BYTE Component2;
	BYTE Component3;
	BYTE Component4;

	/* RGB color space 
	*	Component1 = red;
	*	Component2 = green;
	*	Component3 = blue;
	*	Component4 = unused;
	*/

	/*	Variable length data follows:
	*
	*
	* If COLOR_VALUE_FLAGS_HASGRADIENT is set then:
	*
	* 	COLOR_VALUE gradient_i follows
	*/

} COLOR_VALUE;

typedef struct
	{
	BSIG Header;		/* Signature and length of this record */
	COLOR_VALUE Color;
	} CDCOLOR;

typedef struct
	{
	WSIG		Header;				/* Signature and length of this record */
	DWORD		dwFlags;
	COLOR_VALUE	unvisitedColor;		/* Color of unvisited links. */
	COLOR_VALUE	activeColor;		/* Color of active link. */
	COLOR_VALUE	visitedColor;		/* Color of visited links. */
	DWORD		dwSpares[4];
	} CDLINKCOLORS;

#endif /* COLORODS_DEFS */

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


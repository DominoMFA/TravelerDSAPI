
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

#ifdef __cplusplus
extern "C" {
#endif


/* Dynamic array package definitions */

#ifndef DARRAY_DEFS
#define DARRAY_DEFS


/* Dynamic array header structure (24 bytes; 48 bytes on 16-byte pointer machines e.g. OS400). */

typedef struct {
	WORD ObjectSize;						/* Total array object size */
	WORD ElementsUsed;						/* Elements in use */
	WORD ElementsFree;						/* Free elements */
	WORD ElementsFreeMax;					/* Maximum free elements */
	WORD ElementsFreeExtra;					/* Extra free elements to maintain */
	WORD ElementSize;						/* Element size in bytes */
	WORD ElementStrings;					/* Number packed string descriptors in each element */

	WORD StringStorageOffset;				/* Offset to packed string storage */
	WORD StringStorageUsed;					/* In use bytes of string storage */
	WORD StringStorageFree;					/* Free bytes of string storage */
	WORD StringStorageFreeMax;				/* Maximum free storage */
	WORD StringStorageFreeExtra;			/* Extra free storage to maintain */

/*  First array element follows here.  First byte of packed string storage */
/*  follows last allocated array element.  Since this PSTRING structure contains a pointer, */
/*  it must begin on an aligned boundary. */

#if NATURAL_ALIGNMENT == 16
	void *PaddingPointer;
#endif

	} DARRAY; 

/* Packed string descriptor */

typedef struct {
	WORD StringSize;						/* String size */
	WORD StringType;						/* String type (info only) */
	char far *String;						/* String pointer or offset */
	} PSTRING;

/* Dynamic array functions and macros */

STATUS LNPUBLIC OSDArrayAlloc (WORD ElementSize,
								WORD StringsPerElement,
								WORD InitialElements,
								WORD InitialStringStorage,
								DHANDLE far *rethDArray,
								DARRAY far * far *retDArray);
STATUS LNPUBLIC OSDArraySetFreeSizes (DARRAY far *DArray,
								WORD ElementsFreeExtra,
								WORD ElementsFreeMax,
								WORD StringStorageFreeExtra,
								WORD StringStorageFreeMax);
STATUS LNPUBLIC OSDArrayAddElement (DHANDLE hDArray, DARRAY far * far *DArray,
								void far *NewElement,
								WORD NewIndex);
STATUS LNPUBLIC OSDArrayRemoveElement (DHANDLE hDArray, DARRAY far * far *DArray,
								WORD Index);

#define OSDArray(darray, elementtype) ((elementtype far *)(&((darray)[1])))

/* Packed string functions and macros */

#define OSDArrayString(darray, pstring) \
	( (char far *) (darray) + (darray)->StringStorageOffset + \
				PTR_TO_DWORD((pstring).String) )

#endif


#ifdef __cplusplus
}
#endif


#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


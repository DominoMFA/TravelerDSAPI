
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM and/or HCL                   */
/*                                                                   */
/* Notes_V11.0.1, Domino_V11.0.1                                     */
/*                                                                   */
/* Copyright IBM Corp. 1989, 2017  All Rights Reserved.              */
/* (c) Copyright HCL Technologies Ltd. 2020.  All Rights Reserved.  */
/*                                                                   */
/* Note to U.S. Government Users Restricted Rights:                  */
/* Use, duplication or disclosure restricted by GSA ADP Schedule     */
/*                                                                   */
/*                                                                   */
/* ***************************************************************** */

#ifdef __cplusplus
extern "C" {
#endif


/* This file contains typedefs for data structures passed from the editor */
/* to import/export procedures. */

#ifndef IXEDIT_DEFS
#define IXEDIT_DEFS

#ifndef FONTID_DEFS
#include "fontid.h"		/* for FONTID */
#endif

#ifndef EDIT_ODS_DEFS
#include "editods.h"	/* for HEAD_DESC_BUFFER */
#endif

#ifndef NAME_DEFS
#include "names.h"		/* for MAXPATH */
#endif


/* Block passed to all editor imports */

typedef struct
	{
	char OutputFileName[OLDMAXPATH];/* File to be filled by import with CD records */
	FONTID FontID;					/* font used at the current caret position */
	} EDITIMPORTDATA;


/* Block passed to all editor exports */

typedef struct
	{
	char InputFileName[OLDMAXPATH];	/* File to be read by export containing CD records */
	DHANDLE hCompBuffer;			 	/* Handle to composite buffer (V1 Exports) */
	DWORD CompLength;				/* Length of composite buffer (V1 Exports) */
	HEAD_DESC_BUFFER HeaderBuffer; 
	HEAD_DESC_BUFFER FooterBuffer;		
	PRINT_SETTINGS   PrintSettings;
	} EDITEXPORTDATA;

/* It's used as OUT parameter in ViewImportExportDialog to return file path if user
	selects PDF filter for export. We're reusing export dialog to obtain file path. */
typedef struct
	{
	char szOutputFileName[MAXPATH];	/* File path obtained from export dialog box. */
	}	PDFEXPORTDATA;

#endif

#ifdef __cplusplus
}
#endif


#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


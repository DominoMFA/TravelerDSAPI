
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/*********************************************************************/
/*                                                                   */
/* Licensed Materials - Property of IBM and/or HCL                   */
/*                                                                   */
/* Notes_V11.0.1, Domino_V11.0.1                                     */
/*                                                                   */
/* Copyright IBM Corp. 1994, 2017  All Rights Reserved.              */
/* (c) Copyright HCL Technologies Ltd. 2020.  All Rights Reserved.  */
/*                                                                   */
/* Note to U.S. Government Users Restricted Rights:                  */
/* Use, duplication or disclosure restricted by GSA ADP Schedule     */
/*                                                                   */
/*                                                                   */
/*********************************************************************/	 

// Interface file for archiving and storage management APIs


#ifndef ARCHSVC_DEFS
#define ARCHSVC_DEFS

#ifdef __cplusplus
extern "C" {
#endif

#include "global.h"
#include "nsfdata.h"
#include "nsfnote.h"
typedef void * HARCHIVEDOCUMENT;
typedef STATUS (LNCALLBACKPTR NOTEEXPORTCALLBACK)
		(
		const BYTE *Buffer,
		DWORD dwBufferSize,
		BOOL bLastBuffer, 
		STATUS retError,
		void *pUserCtx
		);
STATUS LNPUBLIC ArchiveDocumentExport
	(HARCHIVEDOCUMENT hDoc, 
	NOTEEXPORTCALLBACK NoteExportCallback, 
	void *pCtx);
typedef DWORD (LNCALLBACKPTR NOTEIMPORTCALLBACK)
	(BYTE *Buffer,
	DWORD MaxToRead,
	void *pUserCtx);
STATUS LNPUBLIC ArchiveDocumentImport(
	DWORD Flags,
	NOTEIMPORTCALLBACK NoteImportCallback,
	void *pUserCtx,
	HARCHIVEDOCUMENT *phArchDoc);
void LNPUBLIC ArchiveDocumentDestroy(HARCHIVEDOCUMENT hArchDoc);
typedef STATUS (LNCALLBACKPTR ITEMEXTRACTCALLBACK)
		(
		const BYTE *Buffer,
		DWORD dwBufferSize,
		BOOL bLastBuffer,
		STATUS retError,
		void *pUserCtx
		);
STATUS LNPUBLIC ArchiveDocumentExtractItem(
	HARCHIVEDOCUMENT hArchDoc,
	const char *ItemName,
	WORD NameLen,
	ITEMEXTRACTCALLBACK ItemExtractCallback, 
	void *pUserCtx);
typedef DWORD (LNCALLBACKPTR ITEMINSERTCALLBACK)
	(BYTE *Buffer,
	DWORD MaxToRead,
	void *pUserCtx);
STATUS LNPUBLIC ArchiveDocumentInsertItem(
	HARCHIVEDOCUMENT hArchDoc,
	ITEMINSERTCALLBACK ItemInsertCallback,
	void *pUserCtx);
typedef STATUS (LNCALLBACKPTR NOTEINITCALLBACK)
	(
	NOTEHANDLE hNote,
	STATUS retError,
	void *pUserCtx
	);
typedef DWORD (LNCALLBACKPTR ITEMINSERTCALLBACK)
	(BYTE *Buffer,
	DWORD MaxToRead,
	void *pUserCtx);
STATUS LNPUBLIC ArchiveDocumentInsertItem(
	HARCHIVEDOCUMENT hArchDoc,
	ITEMINSERTCALLBACK ItemInsertCallback,
	void *pUserCtx);


typedef STATUS (LNCALLBACKPTR ARCHIVETEXTOUTPUTCALLBACK)
		(
		const char *Text,
		DWORD dwTextSize,
		BOOL bLastBuffer, 
		void *pUserCtx
		);
STATUS LNPUBLIC ArchiveDocumentGetText(
	HARCHIVEDOCUMENT hArchDoc, 
	const char *ItemName, 
	DWORD NameLen,
	ARCHIVETEXTOUTPUTCALLBACK ArchiveTextOutputCallback,
	void *pUserCtx);

#define ARCHIVE_ATTACH_ENCRYPTED 	0x00000001 /*Indicates attachment is being passed encrypted */
#define ARCHIVE_ATTACH_MACBIN_RAW	0x00000002 /*Indicates attachment data is mac binary data as stored in NSF (compressed data and resource fork only) */
typedef STATUS (LNCALLBACKPTR ARCHIVEATTACHINIT)
		(
		const char *szFileName,
		DWORD dwFlags,
		DWORD dwDupIdx,
		STATUS retError,
		void *pUserCtx,
		DWORD dwUnused, 
		const BYTE* pUnused);
typedef STATUS (LNCALLBACKPTR ARCHIVEATTACHOUTPUT)
		(
		const BYTE *Buffer,
		DWORD BufferSize,
		BOOL bLastBuffer,
		STATUS retError,
		void *pUserCtx);
typedef STATUS (LNCALLBACKPTR ARCHIVEDOCUMENTCALLBACK)
		(
		HARCHIVEDOCUMENT hArchDoc,
		void *pUserCtx);
STATUS LNPUBLIC ArchiveExportDatabase(
										DBHANDLE hDb,
										DHANDLE hIDTable,
										DWORD Flags, 
										NOTEINITCALLBACK 	NoteInitCallback,
										ARCHIVEATTACHINIT AttachInitCallback,
										ARCHIVEATTACHOUTPUT AttachOutputCallback,
										ARCHIVEDOCUMENTCALLBACK ArchiveDocumentCallback,
										KFHANDLE hKFC, 
										void *pUserCtx);
typedef STATUS (LNCALLBACKPTR ARCHIVEATTACHIMPORT)
	(const char *FileName,
	DWORD FileNameLen,
	DWORD dwDupIdx,
	BYTE *Buffer,
	DWORD MaxToRead,
	void *pUserCtx);
STATUS LNPUBLIC ArchiveRestoreDocument(
	DBHANDLE hDb,
	DWORD Flags, 
	HARCHIVEDOCUMENT hArchDoc,
	ARCHIVEATTACHIMPORT AttachImportCallback,
	void *pUserCtx,
	NOTEHANDLE *hNote);


STATUS LNPUBLIC ArchiveRestoreDocumentToNote(
	NOTEHANDLE hTargetNote,
	DWORD Flags,
	HARCHIVEDOCUMENT hArchDoc);

#ifdef __cplusplus
}				// Extern "C"
#endif

#endif


#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


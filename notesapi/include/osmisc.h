
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

#ifndef OSMISC_DEFS
#define OSMISC_DEFS

#ifdef __cplusplus
extern "C" {
#endif

#ifdef UNIX
#include <sys/types.h>					/* For key_t definition */
#endif

#ifndef NLS_H
#include "nls.h"						/* Need NLS_PINFO */
#endif

#include "names.h"						/* MAXPATH */

/*	String resource loading routine */

WORD LNPUBLIC		OSLoadString (HMODULE hModule, STATUS StringCode, char far *retBuffer, WORD BufferLength);
/*	Charsets used with OSTranslate */

#define OS_TRANSLATE_NATIVE_TO_LMBCS 	0	/* Translate platform-specific to LMBCS */
#define OS_TRANSLATE_LMBCS_TO_NATIVE 	1	/* Translate LMBCS to platform-specific */
#define	OS_TRANSLATE_LOWER_TO_UPPER		3	/* current int'l case table */
#define	OS_TRANSLATE_UPPER_TO_LOWER		4	/* current int'l case table */
#define OS_TRANSLATE_UNACCENT			5  	/* int'l unaccenting table */

#ifdef DOS									
#define OS_TRANSLATE_OSNATIVE_TO_LMBCS 	7  	/* Used in DOS (codepage) */
#define OS_TRANSLATE_LMBCS_TO_OSNATIVE 	8  	/* Used in DOS			*/
#elif defined (OS2)
#define OS_TRANSLATE_OSNATIVE_TO_LMBCS 	OS_TRANSLATE_NATIVE_TO_LMBCS
#define OS_TRANSLATE_LMBCS_TO_OSNATIVE 	OS_TRANSLATE_LMBCS_TO_NATIVE
#else
#define OS_TRANSLATE_OSNATIVE_TO_LMBCS 	OS_TRANSLATE_NATIVE_TO_LMBCS
#define OS_TRANSLATE_LMBCS_TO_OSNATIVE 	OS_TRANSLATE_LMBCS_TO_NATIVE
#endif

#if defined(DOS) || defined(OS2)
#define OS_TRANSLATE_LMBCS_TO_ASCII		13
#else
#define OS_TRANSLATE_LMBCS_TO_ASCII		11
#endif

#define OS_TRANSLATE_LMBCS_TO_UNICODE	20
#define OS_TRANSLATE_LMBCS_TO_UTF8		22
#define OS_TRANSLATE_UNICODE_TO_LMBCS	23
#define OS_TRANSLATE_UTF8_TO_LMBCS		24


/*	Character Set Translation Routines */

WORD LNPUBLIC		OSTranslate(WORD TranslateMode, const char far *In, WORD InLength, char far *Out, WORD OutLength);

/*	Dynamic link library portable load routines */

STATUS	LNPUBLIC	OSLoadLibrary (const char far *LibraryName, DWORD Flags, HMODULE far *rethModule, void far *retEntryPoint);
void	LNPUBLIC	OSFreeLibrary (HMODULE);
#define OS_LOADPROG_ICONIC			0x0001 	/* Don't show application window */
#define OS_LOADPROG_BACKGROUND		0x0002 	/* Don't bring to the foreground */
#define	OS_LOADPROG_DEBUG			0x0004 	/* Start with QNC */
#define	OS_LOADPROG_DETACHED		0x0008 	/* Don't wait around for this process to exit */
#define	OS_LOADPROG_ASSOCIATE		0x0010 	/* Look for a file type association */
#define	OS_LOADPROG_PRIORITY_LOW	0x0020 	/* Start process with a lower priority */
#define OS_LOADPROG_SHELL_SCRIPT_USE_EXECVP 0x0040 /* Flag to signal a shell script, so we can use execvp instead of execv. Currently on use only on AIX */
#define OS_LOADPROG_OPEN_WITH		0x0080 /* Flag to add the necessary things to do an open with command. Currently on use only on NT */


STATUS	LNPUBLIC	OSLoadProgram (char far *filename, char far *WorkingDir, char far *Arguments, WORD Flags);

/*	Routine used in non-premptive platforms to simulate it. */

#ifdef PREEMPTIVE
#define	OSPreemptOccasionally()
#else
void	LNPUBLIC	OSPreemptOccasionally (void);
#endif
/*	Notes-specific NLS definitions */

NLS_PINFO LNPUBLIC		OSGetLMBCSCLS(void);
NLS_PINFO LNPUBLIC		OSGetNativeCLS(void);

#if defined(UNIX) || defined(MAC)
typedef struct {
#if defined(ZLINUX) && !defined(ZLINUX64)
	/* we need to add four bytes of padding here */
	int dummy;
#endif
	ino_t  st_ino;
	dev_t  st_dev;
} PARTITION_UNIQUE_ID;
#endif

struct PARTITION_INFO {
	WORD status;					/* PARITION_xxx (see below) */
#if defined(UNIX) || defined(MAC)		/* Only UNIX needs the partition number expressed as a number */
	WORD PartitionNumber;			/* Partition number (see IpcGetPartitionNumber) */
	PARTITION_UNIQUE_ID PartitionUniqueId;  /* Unique id for this partition */
#endif
	char PartitionName[MAXPATH];	/* Partition name (LMBCS string) */
};
typedef struct PARTITION_INFO	PARTITION_INFO;

#define PARTITION_UNKNOWN  1		/* status codes */
#define PARTITION_NONE	   2
#define PARTITION_OK	   3

#define PARTITION_INVALID     "XX"	/* Partition name when partition number not valid */

STATUS LNPUBLIC OSGetPartition (PARTITION_INFO *pPartitionInfo);

#ifdef __cplusplus
}
#endif

#endif


#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


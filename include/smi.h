
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM and/or HCL                   */
/*                                                                   */
/* Notes_V11.0.1, Domino_V11.0.1                                     */
/*                                                                   */
/* Copyright IBM Corp. 1993, 2017  All Rights Reserved.              */
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

/* SMI.H is the public header file for the Simple Messaging Interface (SMI) */

#ifndef __SMI_INCLUDED
#define __SMI_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "smilcl.h"

#define SMISTS_SUCCESS                     0
#define SMISTS_FAILURE                     1
#define SMISTS_ATTACHMENT_NOT_FOUND        4
#define SMISTS_INSUFFICIENT_MEMORY         8
#define SMISTS_INVALID_ADDR_BOOK           128
#define SMISTS_NAME_NOT_FOUND              15
#define SMISTS_NOT_SUPPORTED               16
#define SMISTS_OPEN_FAILURE                22
#define SMISTS_TOO_MANY_FILES              129
#define SMISTS_TOO_MANY_RECIPIENTS         130
#define SMISTS_USER_CANCEL                 131

#define SMI_TO                             1
#define SMI_CC                             2
#define SMI_BCC                            3

#define SMI_UNKNOWN                        0
#define SMI_PERSON                         1
#define SMI_GROUP                          2

#define SMI_PRIVATE                        "(SMI_PRIVATE)"
#define SMI_PUBLIC                         "(SMI_PUBLIC)"

#define SMI_UI                             0x00000001
#define SMI_ARRAYS_IN_STRUCTS              0x00000002

typedef struct {
   long RecipClass;
   long NameType;
   char SMI_FAR * SMI_PTR Name;
   char SMI_FAR * SMI_PTR AddressBook;
   char SMI_FAR * SMI_PTR Address;
} smiRecipDesc, SMI_FAR * SMI_PTR smiRecipDescPtr;

typedef struct {
   char SMI_FAR * SMI_PTR PathName;
   char SMI_FAR * SMI_PTR FileName;
   char SMI_FAR * SMI_PTR FileType;
} smiFileDesc, SMI_FAR * SMI_PTR smiFileDescPtr;

typedef struct {
   long RecipClass;
   long NameType;
   char Name[1024];
   char AddressBook[256];
   char Address[1024];
} smiRecipArrayDesc, SMI_FAR * SMI_PTR smiRecipArrayDescPtr;

typedef struct {
   char PathName[256];
   char FileName[256];
   char FileType[256];
} smiFileArrayDesc, SMI_FAR * SMI_PTR smiFileArrayDescPtr;

long SMIAPIENTRY SMISendDocuments( long int dwUIParam,
                                   char SMI_FAR * SMI_PTR strPaths,
                                   char SMI_FAR * SMI_PTR strFilenames,
                                   char SMI_FAR * SMI_PTR strDelim,
                                   long int dwReserved );

long SMIAPIENTRY SMISendMail(  long int dwUIParam,
                               long int nRecipCount,
                               smiRecipDescPtr pRecips,
                               long int nFileCount,
                               smiFileDescPtr pFiles,
                               char SMI_FAR * SMI_PTR psSubject,
                               char SMI_FAR * SMI_PTR psNoteText,
                               char SMI_FAR * SMI_PTR psMessageType,
                               long int fFlags,
                               long int dwReserved );

/*
   Include local implementation extensions.
*/
#include "smiext.h"

#ifdef __cplusplus
}
#endif

#endif /* __SMI_INCLUDED */

/* EOF: smi.h */

#ifdef __cplusplus
}
#endif


#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


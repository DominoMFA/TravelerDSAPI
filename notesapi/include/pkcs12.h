
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM and/or HCL                   */
/*                                                                   */
/* Notes_V11.0.1, Domino_V11.0.1                                     */
/*                                                                   */
/* Copyright IBM Corp. 1999, 2017  All Rights Reserved.              */
/* (c) Copyright HCL Technologies Ltd. 2020.  All Rights Reserved.  */
/*                                                                   */
/* Note to U.S. Government Users Restricted Rights:                  */
/* Use, duplication or disclosure restricted by GSA ADP Schedule     */
/*                                                                   */
/*                                                                   */
/* ***************************************************************** */

#ifndef PKCS12_H
#define PKCS12_H

#ifdef __cplusplus
extern "C" {
#endif


#ifndef GLOBAL_DEFS
#include "global.h"
#endif

#ifndef NIF_DEFS
#include "nif.h"
#endif


#define	PKCS12_EXCLUDE_PRIVATEKEYS	0x00000001
#define	PKCS12_FILTERBY_SUBJECTNAME	0x00000002


STATUS LNPUBLIC PKCS12_ImportFileToIDFile (char *pPKCS12Filename, 
								  	   char  *pPKCS12Filepassword, 
								  	   char	 *pIdFilename, 
								  	   char	 *pIdFilepassword, 
									   DWORD ImportFlags,
									   DWORD ReservedFlags,
									   void  *pReserved);

STATUS LNPUBLIC PKCS12_ExportIDFileToFile (	char		*pIdFilename, 
								  	   		char		*pIdFilepassword, 
											char 		*pPKCS12Filename, 
								  	   		char 		*pPKCS12Filepassword, 
										   	DWORD 		ExportFlags,
									   		DWORD 		ReservedFlags,
									   		void 		*pReserved);



#ifdef __cplusplus
}
#endif

#endif


#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


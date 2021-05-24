
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM                              */
/*                                                                   */
/* L-GHUS-97FH78, L-GHUS-972PJ6                                      */
/*                                                                   */
/* Copyright IBM Corp. 1999, 2013  All Rights Reserved.              */
/*                                                                   */
/* US Government Users Restricted Rights - Use, duplication or       */
/* disclosure restricted by GSA ADP Schedule Contract with           */
/* IBM Corp.                                                         */
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


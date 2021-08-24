
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/*********************************************************************/
/*                                                                   */
/* Licensed Materials - Property of IBM and/or HCL                   */
/*                                                                   */
/* Notes_V11.0.1, Domino_V11.0.1                                     */
/*                                                                   */
/* Copyright IBM Corp. 2002, 2017  All Rights Reserved.              */
/* (c) Copyright HCL Technologies Ltd. 2020.  All Rights Reserved.  */
/*                                                                   */
/* Note to U.S. Government Users Restricted Rights:                  */
/* Use, duplication or disclosure restricted by GSA ADP Schedule     */
/*                                                                   */
/*                                                                   */
/*********************************************************************/

//______________________________________________________________________
//
//		File:		nlookup.h
//
//______________________________________________________________________


#if !defined(NLOOKUP_H)
#define NLOOKUP_H


#ifdef __cplusplus
extern "C" {
#endif

/* nlookup.cpp */

typedef struct {
	char		*pUserName;
	char		*pAltUserName;
	char		*pAltUserNameLang;
	char		*pOldWebName;
	char		*pInternetAddress;
	char		*pSSOTokenUserName;
	void		*pReserved;
} NABLOOKUP_RECORD;

//---
//		Routines exposing NAB lookup class via C for the SDK
//

STATUS LNPUBLIC NABLookupOpen( void **retpNABLookup, DWORD dwReserved, void *vpReserved );

// Use this flag with NABLookupAuthenticatedUser if the user parameter
// is an authenticated Kerberos user name.
#define fLookupAuthenticatedKerberosName 		0x1000

STATUS LNPUBLIC NABLookupAuthenticatedUser( void *pNABLookup,
								  char	*orgName,
								  char	*user,
								  DWORD	flags,
								  NABLOOKUP_RECORD	*pRetNabLookupRecord,
								  DWORD dwNablookupRecordSize,
								  DWORD dwReserved,
								  void *vpReserved );


void LNPUBLIC NABLookupClose( void **pNABLookup,
							 void *pNabLookupRecord,
							 DWORD dwNablookupRecordSize,
							 DWORD dwReserved,
							 void *vpReserved );
#ifdef __cplusplus
}
#endif


#endif // NLOOKUP_H

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


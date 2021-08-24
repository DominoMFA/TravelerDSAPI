
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/*********************************************************************/
/*                                                                   */
/* Licensed Materials - Property of IBM and/or HCL                   */
/*                                                                   */
/* Notes_V11.0.1, Domino_V11.0.1                                     */
/*                                                                   */
/* Copyright IBM Corp. 2007, 2018  All Rights Reserved.              */
/* (c) Copyright HCL Technologies Ltd. 2020.  All Rights Reserved.  */
/*                                                                   */
/* Note to U.S. Government Users Restricted Rights:                  */
/* Use, duplication or disclosure restricted by GSA ADP Schedule     */
/*                                                                   */
/*                                                                   */
/*********************************************************************/

/*	IDVAULT.H  - ID Vault management routines.

	Author:	Alan D. Eldridge,	7/18/07
*/


#ifndef IDVAULT_DEFS
#define IDVAULT_DEFS

#include "names.h"

#ifndef BSAFE_DEFS
#include "bsafe.h"
#endif

#ifndef OSSIGNAL_DEFS
#include "ossignal.h"
#endif

#ifndef KFM_DEFS
#include "kfm.h"
#endif

#include "urltypes.h" // for MAX_DOMINO_URL_LENGTH

#ifdef __cplusplus
extern "C" {
#endif

#define IDV_pwreset_CHANGE				1

STATUS LNPUBLIC SECidvResetUserPassword	(char		*pServer
										,char		*pUserName
										,char		*pPassword
										,WORD		wDownloadCount
										,DWORD		dwReservedFlags
										,void		*pReserved
										);

STATUS FAR PASCAL SECidfPut				(char		*pUserName
										,char		*pPassword
										,char		*pIDFilePath
										,KFHANDLE	*phKFC
										,char		*pServerName
										,DWORD		dwReservedFlags
										,WORD		wReservedType
										,void		*pReserved
										);

STATUS FAR PASCAL SECidfGet				(char		*pUserName
										,char		*pPassword
										,char		*pPutIDFileHere
										,KFHANDLE	*phKFC
										,char		*pServerName
										,DWORD		dwReservedFlags
										,WORD		wReservedType
										,void		*pReserved
										);

#define IDV_syncRetFlag_IDSyncDone			1
#define IDV_syncRetFlag_IDFoundInVault		2
#define IDV_syncRetFlag_IDNotFoundInVault	4
#define IDV_syncRetFlag_TryNSLProtocol		8

STATUS FAR PASCAL SECidfSync			(char		*pUserName
										,char		*pPassword
										,char		*pIDFilePath
										,KFHANDLE	*phKFC
										,char		*pServerName
										,DWORD		dwReservedFlags
										,WORD		wReservedType
										,void		*pReserved
										,DWORD		*retdwFlags
										);


/*	End of IDVAULT.H */

#ifdef __cplusplus
}
#endif

#endif

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


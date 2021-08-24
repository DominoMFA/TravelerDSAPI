
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

/*	Miscellaneous Package Global Definitions */

#ifndef OOOAPI_DEFS
#define OOOAPI_DEFS


#ifdef __cplusplus
extern "C" {
#endif

typedef MEMHANDLE  OOOCTXHANDLE;
typedef void*  OOOCTXPTR;

#define OOO_STATS_CONFIG			"OOO"
#define OOO_CONFIG_AGENT			1
#define	OOO_CONFIG_SERVICE			2
#define OOO_STATE_ENABLED			1
#define OOO_STATE_DISABLED			0
#define OOO_STATE_ADMINP_ENABLED	3	 // not implemented. needed for client when request via adminp 
#define OOO_STATE_ADMINP_DISABLED	4	 // not implemented. needed for client when request via adminp
#define OOO_STATE_NOTSET			99
#define OOO_CONFIG_UNKNOWN			0

#define OOOPROF_MAX_BODY_SIZE		32767		 // Buffers passed into OOOGetGeneralSubject should be this size
/* out of office API */


STATUS LNPUBLIC OOOInit();
STATUS LNPUBLIC OOOTerm();

STATUS LNPUBLIC OOOStartOperation(const char	*pMailOwnerName,
						const char	*pServerName,
						BOOL		bHomeMailServer,
						DHANDLE		hMailFile,
						OOOCTXHANDLE  *rethOOOContext,
						OOOCTXPTR 	 **retpOOOContext);

STATUS LNPUBLIC OOOEndOperation(OOOCTXHANDLE hOOOContext,
						OOOCTXPTR 	 *pOOOContext);

STATUS LNPUBLIC OOOGetState(
		OOOCTXPTR 	*pOOOContext,
		WORD		*retConfig,
		WORD  		*retState);

STATUS LNPUBLIC OOOEnable(
		OOOCTXPTR 	 *pOOOContext,
		BOOL		 bState);


STATUS LNPUBLIC OOOSetAwayPeriod(
		OOOCTXPTR 		*pOOOContext,
		TIMEDATE		tdStartAway,
		TIMEDATE		tdEndAway);

STATUS LNPUBLIC OOOGetAwayPeriod(
		OOOCTXPTR 		*pOOOContext,
		TIMEDATE		*tdStartAway,
		TIMEDATE		*tdEndAway);

STATUS LNPUBLIC OOOSetGeneralMessage(
		OOOCTXPTR 		*pOOOContext,
		const char		*pGeneralMessage,
		WORD			wGeneralMessageLen);

STATUS LNPUBLIC OOOGetGeneralMessage(
		OOOCTXPTR 		*pOOOContext,
		char			*pGeneralMessage,
		WORD			*pwGenMessageLen);

STATUS LNPUBLIC OOOSetGeneralSubject(
		OOOCTXPTR 		*pOOOContext,
		const char		*pGeneralSubject,
		BOOL			bDisplayReturnDate);

STATUS LNPUBLIC OOOGetGeneralSubject(
		OOOCTXPTR 		*pOOOContext,
		char			*pGeneralSubject);

STATUS LNPUBLIC OOOSetExcludeInternet(
		OOOCTXPTR 		*pOOOContext,
		BOOL			bExcludeInternet);

STATUS LNPUBLIC OOOGetExcludeInternet(
		OOOCTXPTR 		*pOOOContext,
		BOOL			*bExcludeInternet);
		
STATUS LNPUBLIC OOOSetAlternateAwayLine(
		OOOCTXPTR		*pOOOContext, 
		char			*altline);
		
STATUS LNPUBLIC OOOGetAlternateAwayLine(
		OOOCTXPTR 		*pOOOContext, 
		char			*altline,
		WORD			altlinelen);
		

#ifdef __cplusplus
}
#endif


#endif /* OOOAPI_DEFS */


#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif



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


/*  Name Server Public Definitions */

#ifndef NS_DEFS
#define NS_DEFS


/* function templates */

STATUS LNPUBLIC NSGetServerList (char far *pPortName, DHANDLE far *retServerTextList);

/* Begin APIs for Cluster support */

#define	CLUSTER_LOOKUP_NOCACHE				0x00000001	/* don't use cluster name cache */
#define	CLUSTER_LOOKUP_CACHEONLY			0x00000002	/* only use cluster name cache */

#define CLUSTER_DOING_INITIAL_USERSETUP		0x00000004	/* don't require user name - doing initial user setup */

STATUS LNPUBLIC NSGetServerClusterMates ( 
	const char far *pServerName,
    DWORD dwFlags,
	DHANDLE far *phList);
STATUS LNPUBLIC NSPingServer( 
	char far *pServerName,
	DWORD far *pdwIndex,
	DHANDLE far *phList);

#endif



#ifdef __cplusplus
}
#endif

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif



#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM                              */
/*                                                                   */
/* L-GHUS-97FH78, L-GHUS-972PJ6                                      */
/*                                                                   */
/* Copyright IBM Corp. 1989, 2013  All Rights Reserved.              */
/*                                                                   */
/* US Government Users Restricted Rights - Use, duplication or       */
/* disclosure restricted by GSA ADP Schedule Contract with           */
/* IBM Corp.                                                         */
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



#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM                              */
/*                                                                   */
/* L-GHUS-97FH78, L-GHUS-972PJ6                                      */
/*                                                                   */
/* Copyright IBM Corp. 1991, 2013  All Rights Reserved.              */
/*                                                                   */
/* US Government Users Restricted Rights - Use, duplication or       */
/* disclosure restricted by GSA ADP Schedule Contract with           */
/* IBM Corp.                                                         */
/*                                                                   */
/* ***************************************************************** */

/*	File system interface */

#ifndef FILE_DEFS
#define FILE_DEFS

#ifdef __cplusplus
extern "C" {
#endif


/*	File type flags (used with NSFSearch directory searching). */


#define	FILE_ANY		0		/* Any file type */
#define	FILE_DBREPL		1		/* Starting in V3, any DB that is a candidate for replication */
#define FILE_DBDESIGN   2       /* Databases that can be templates */
#define FILE_MAILBOX	3		/* BOX - Any .BOX (Mail.BOX, SMTP.Box...) */
						 
#define	FILE_DBANY		4		/* NS?, any NSF version */
#define	FILE_FTANY		5		/* NT?, any NTF version */
#define FILE_MDMTYPE	6		/* MDM - modem command file */
#define FILE_DIRSONLY	7		/* directories only */
#define FILE_VPCTYPE	8		/* VPC - virtual port command file */
#define FILE_SCRTYPE	9		/* SCR - comm port script files */
#define FILE_ANYNOTEFILE	10	/* ANY Notes database (.NS?, .NT?, .BOX)	*/
#define FILE_UNIQUETEMP 11		/* DTF - Any .DTF. Used for container and sort temp files to give them a more
								   unique name than .TMP so we can delete *.DTF from the temp directory and
								   hopefully not blow away other application's temp files. */
#define	FILE_MULTICLN   12		/* CLN - Any .cln file...multi user cleanup files*/
#define FILE_SMARTI		13		/* any smarticon file *.smi */
#define FILE_DBREP_REDIR	14	/* FILE_DBREPL plus database redirects */

#define	FILE_TYPEMASK		0x00ff	/* File type mask (for FILE_xxx codes above) */
#define	FILE_SKIPDAOS		0x0100	/* Do not traverse DAOS repository */
#define	FILE_SKIPJS			0x0200	/* Do not traverse HTTP's javascript directories */
#define	FILE_DIRS			0x8000	/* List subdirectories as well as normal files */
#define	FILE_NOUPDIRS		0x4000	/* Do NOT return ..'s */
#define	FILE_RECURSE		0x2000	/* Recurse into subdirectories */
#define	FILE_LINKSONLY		0x1000	/* All directories, linked files & directories */

STATUS LNPUBLIC		OSPathNetConstruct(const char far *PortName,
										const char far *ServerName,
										const char far *FileName,
										char far *retPathName);
STATUS LNPUBLIC		OSPathNetParse(const char far *PathName,
										char far *retPortName,
										char far *retServerName,
										char far *retFileName);
void LNPUBLIC		OSGetExecutableDirectory (char *retPathName);
WORD 	LNPUBLIC OSGetDataDirectory(char far *retPathName);

#ifdef __cplusplus
}
#endif

#endif

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


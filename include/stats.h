
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM and/or HCL                   */
/*                                                                   */
/* Notes_V11.0.1, Domino_V11.0.1                                     */
/*                                                                   */
/* Copyright IBM Corp. 1990, 2017  All Rights Reserved.              */
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

#ifndef STATS_DEFS
#define STATS_DEFS

#include "misc.h"
#include "names.h"

/*	Cross-package definitions */

#define	STATPKG_OS "OS"
#define	STATPKG_STATS "Stats"
#define	STATPKG_OSMEM "Mem"
#define	STATPKG_OSSEM "Sem"
#define	STATPKG_OSSPIN "Spin"
#define	STATPKG_OSFILE "Disk"
#define	STATPKG_SERVER "Server"
#define	STATPKG_REPLICA "Replica"
#define	STATPKG_MAIL "Mail"
#define	STATPKG_MAILBYDEST "MailByDest"
#define	STATPKG_COMM "Comm"
#define	STATPKG_NSF "Database"
#define	STATPKG_NIF "Database"
#define	STATPKG_TESTNSF "Testnsf"
#define STATPKG_OSIO "IO"
#define STATPKG_NET "NET"
#define STATPKG_OBJSTORE "Object"
#define STATPKG_AGENT "Agent"		/* used by agent manager */
#define STATPKG_WEB "Web"			/* used by Web retriever */
#define STATPKG_CAL	"Calendar"		/* used by schedule manager */
#define STATPKG_SMTP "SMTP"			/* Used by SMTP listener */
#define STATPKG_LDAP "LDAP"			/* Used by the LDAP Server */
#define STATPKG_LICENSE "License"	/* Used by Licensing */
#define STATPKG_NNTP "NNTP"			/* Used by the NNTP Server */
#define STATPKG_ICM "ICM"			/* Used by the ICM Server */
#define STATPKG_ADMINP "ADMINP"		/* Used by Administration Process */
#define STATPKG_IMAP "IMAP"			/* used by IMAP Server    */
#define STATPKG_MONITOR "Monitor"
#define STATPKG_POP3 "POP3"			/* Used by the POP3 Server */
#define STATPKG_FT "FT"	
#define STATPKG_DECS "DECS"			/* Used by the DECS Server */
#define STATPKG_EVENT "EVENT"		/* Used by the Event Monitor */
#define STATPKG_DB2NSF "DB2NSF"		/* Used by DB2 NSF */
#define STATPKG_DB2NIF "DB2NIF"		/* Used by DB2 NIF */
#define STATPKG_FA "FaultAnalyzer"
#define STATPKG_DAOS "DAOS"		
#define STATPKG_LOTUSSCRIPT "LotusScript"		
#define STATPKG_DBMT "DBMT"			/* Used by DBMaintTool (in compact dir) */
#define STATPKG_REPAIR "Repair"
#define STATPKG_QUERY "QUERY"

#define STATPKG_DIRSYNC "DirSync"			/* used by DirSync in normal customer to  mode */


/*	Value type constants */

#define	VT_LONG		0
#define	VT_TEXT		1
#define	VT_TIMEDATE	2
#define	VT_NUMBER	3

/*	Flags for StatUpdate */

#define	ST_UNIQUE		0x0001		/* Statistic is unique */
#define	ST_ADDITIVE		0x0002		/* Add to VT_LONG statistic, don't replace */
#define	ST_RESETABLE	0x0003		/* Statistic is resetable to 0 */

/* Collector Daemon tasks */
#define GET_STAT_TASK				3

typedef struct
	{
	DWORD 		Task;							/* Task to be processed by collector I.E.: Add server */
	DWORD 		Interval;						/* Intreval to return info in minutes */
	char 		StatName[MAXSPRINTF];			/* REMOVE */
	char 		StatServerName[MAXPATH];		/* Name of server that you want info about */
	char 		MonitorServerName[MAXPATH];	 	/* If remote provide proxy server name otherwise NULL */
	DWORD 		MonitorFlags;					/* Flags passed to monitor (Reports, Alarms, ...) */
	DHANDLE 		hTaskList;						/* List of user defined tasks to monitor */
	DWORD		TaskListLen;					/* Size of stat list */
	DHANDLE 		hStatList;						/* List of stats to return to monitor */
	DWORD		StatListLen;					/* Size of stat list */
	char 		QueueName[20];					/* Used by remote collector to pass info to proxy collector */
	} SERVER_MSG_BLOCK;

typedef struct
	{
	char 	StatName[MAXSPRINTF];			
	DHANDLE	hStatName;			
	DWORD	StatNameSize;			
	char 	ServerName[MAXPATH];			
	STATUS 	error;							
	} STAT_RETURN_BLOCK;

/*	Prototypes */

STATUS LNPUBLIC	 StatUpdate (const char far *Facility, const char far *StatName, WORD Flags, WORD ValueType, const void far *Value);
void LNPUBLIC	 StatDelete (const char far *Facility, const char far *StatName);
STATUS LNPUBLIC	 StatReset (const char *Facility, const char *StatName);
typedef STATUS (LNCALLBACKPTR STATTRAVERSEPROC)(void far *, char far *, char far *, WORD, void far *);
void LNPUBLIC	 StatTraverse (char far *Facility, char far *StatName, STATTRAVERSEPROC Routine, void far *Context);
void LNPUBLIC	 StatToText(char far *Facility, char far *StatName, WORD ValueType, void far *Value,
							char far *NameBuffer, WORD NameBufferLen,
							char far *ValueBuffer, WORD ValueBufferLen);
STATUS LNPUBLIC	 StatQuery(char far *HeaderString,
							char far *NamePrefix, char far *ValuePrefix,
							char far *LineSuffix,
							DHANDLE far *rethStats, DWORD far *retStatsLength);
STATUS LNPUBLIC  StatQueryTime(char far *Facility, char far *StatName, char far *HeaderString,
							char far *NamePrefix, char far *ValuePrefix,
							char far *LineSuffix,
							DHANDLE far *rethStats, DWORD far *retStatsLength);
#endif

#ifdef __cplusplus
}
#endif

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


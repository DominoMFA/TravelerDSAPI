
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM and/or HCL                   */
/*                                                                   */
/* Notes_V11.0.1, Domino_V11.0.1                                     */
/*                                                                   */
/* Copyright IBM Corp. 1989, 2018  All Rights Reserved.              */
/* (c) Copyright HCL Technologies Ltd. 2020.  All Rights Reserved.  */
/*                                                                   */
/* Note to U.S. Government Users Restricted Rights:                  */
/* Use, duplication or disclosure restricted by GSA ADP Schedule     */
/*                                                                   */
/*                                                                   */
/* ***************************************************************** */

#ifndef NSF_DB_DEFS
#define NSF_DB_DEFS

#ifndef NSF_DEFS
#include "nsfdata.h"
#endif

#ifndef EVENT_DEFS
#include "event.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif


/* Note Storage File Database Definitions */

/*	NSF File Information Buffer size.  This buffer is defined to contain
	Text (host format) that is NULL-TERMINATED.  This is the ONLY null-terminated
	field in all of NSF. */

#define	NSF_INFO_SIZE 128
#define NSF_INFO_WILD_CARD_SERVER_CHAR '*'

/*  Define NSFDbOpenExtended option bits.  These bits select individual
	open options. */

#define DBOPEN_WITH_SCAN_LOCK		0x0001	/* Open with scan lock to prevent
												other opens with scan lock
												(used by replicator) */
#define DBOPEN_PURGE				0x0002	/* DbPurge while opening */
#define DBOPEN_NO_USERINFO			0x0004	/* No user info may be available, so don't ask for it */
#define DBOPEN_FORCE_FIXUP			0x0008	/* Force a database fixup */
#define DBOPEN_FIXUP_FULL_NOTE_SCAN	0x0010	/* Scan all notes and all items (not incremental) */
#define DBOPEN_FIXUP_NO_NOTE_DELETE	0x0020	/* Do not delete bad notes during note scan */
#define DBOPEN_CLUSTER_FAILOVER		0x0080	/* If open fails try cluster failover */
#define DBOPEN_CLOSE_SESS_ON_ERROR	0x0100	/* Close session on error paths */
#define DBOPEN_NOLOG				0x0200	/* don't log errors - used when opening log database! */
/* Define NSFDB2GetInfo infotypes */
#define DB2NSF_INFO_IS_DB2_BACKED 			1	/* Is database DB2-backed: 1/0 */
#define DB2NSF_INFO_SCHEMA_NAME				2	/* Group schema containing NSFDB2 data */
#define DB2NSF_INFO_TABLESPACE_NAME			3	/* Tablespace name */
#define DB2NSF_INFO_TSID                    4   /* Tablespace ID */
#define DB2NSF_INFO_USERSCHEMA_NAME         5   /* Schema containing DAVs */
#define DB2NSF_INFO_CLASS_DESC              6   /* NSFDB2 grouping class description */

/* Define NSFDB2GetServerInfo infotypes */
#define DB2NSF_SERVINFO_SERVER_DEFAULT_TYPE	1	/* Server default type:  'DB2' or 'NSF' */
#define DB2NSF_SERVINFO_NSFDB2_CAPABLE      2   /* Can Domino serve NSFDB2 data?        */
#define DB2NSF_SERVINFO_DB2_DATABASE_NAME   3

#define DBCOMPACT_NO_INDEXES			0x00000001	/* Don't preserve view indexes */
#define DBCOMPACT_NO_LOCKOUT			0x00000002	/* Don't lock out database users */
#define DBCOMPACT_REVERT_ODS			0x00000004	/* Revert current ODS to the previous ODS version */
#define DBCOMPACT_MAX_4GB				0x00000020	/* Create new file with 4GB file size limit */
#define DBCOMPACT_MAILBOX				0x00000080	/* Compact XXXX.BOX for mail router and other MTAs */
#define DBCOMPACT_NO_INPLACE			0x00000100	/* Don't do in-place compaction */
#define DBCOMPACT_DISABLE_UNREAD		0x00002000	/* Disable unread marks in destination database */
#define DBCOMPACT_ENABLE_UNREAD			0x00004000	/* Reenable unread marks in destination database (default) */
#define DBCOMPACT_DISABLE_RESPONSE_INFO	0x00008000	/* Disable response info in resulting database */
#define DBCOMPACT_ENABLE_RESPONSE_INFO	0x00010000	/* Disable response info in resulting database (default) */
#define DBCOMPACT_ENABLE_FORM_BKT_OPT	0x00020000	/* Enable form/bucket bitmap optimization */
#define DBCOMPACT_DISABLE_FORM_BKT_OPT	0x00040000	/* Diable form/bucket bitmap optimization (default) */
#define	DBCOMPACT_IGNORE_ERRORS			0x00080000	/* Ignore errors encountered during compaction.  That is,
														make best effort to get something at the end */
#define DBCOMPACT_RECOVER_SPACE_ONLY	0x00400000	/* If set, do only bitmap correction if in-place can be done */
#define DBCOMPACT_ARCHIVE				0x00800000  /* Archive/delete, then compact the database */
#define DBCOMPACT_ARCHIVE_ONLY        	0x01000000  /* Just archive/delete, no need to compact */
#define DBCOMPACT_RECOVER_ALL_SPACE		0x04000000	/* If set, always do full space recovery compaction */
#define DBCOMPACT2_COMPRESS_DESIGN_NS	0x00000400	/* TRUE if design note non-summary should be compressed */
#define DBCOMPACT2_UNCOMPRESS_DESIGN_NS	0x00000800	/* TRUE if design note non-summary should be uncompressed */
#define DBCOMPACT2_COMPRESS_DATA_DOCS	0x00004000	/* TRUE if all data note non-summary should be compressed */
#define DBCOMPACT2_UNCOMPRESS_DATA_DOCS	0x00008000	/* TRUE if all data note non-summary should be uncompressed */
#define DBCOMPACT2_FORCE_DAOS_ON		0x00020000	/* enable compact TO DAOS */
#define DBCOMPACT2_FORCE_DAOS_OFF		0x00040000	/* enable compact FROM DAOS */
#define DBCOMPACT2_FORCE_PIRC_ON		0x00400000	/* enable compact with PIRC */
#define DBCOMPACT2_FORCE_PIRC_OFF		0x00800000	/* enable compact without PIRC */


/*	Define NSF DB Classes - These all begin with 0xf000 for no good
	reason other than to ENSURE that callers of NSFDbCreate call the
	routine with valid parameters, since in earlier versions of NSF
	the argument to the call was typically 0. */

#define	DBCLASS_BY_EXTENSION	0	/* automatically figure it out */

#define	DBCLASS_NSFTESTFILE			0xff00
#define	DBCLASS_NOTEFILE			0xff01
#define	DBCLASS_DESKTOP				0xff02
#define	DBCLASS_NOTECLIPBOARD		0xff03
#define	DBCLASS_TEMPLATEFILE		0xff04
#define	DBCLASS_GIANTNOTEFILE		0xff05
#define	DBCLASS_HUGENOTEFILE		0xff06
#define	DBCLASS_ONEDOCFILE			0xff07	/* Not a mail message */
#define	DBCLASS_V2NOTEFILE			0xff08
#define	DBCLASS_ENCAPSMAILFILE		0xff09	/* Specifically used by alt mail */
#define	DBCLASS_LRGENCAPSMAILFILE	0xff0a	/* Specifically used by alt mail */
#define	DBCLASS_V3NOTEFILE			0xff0b
#define	DBCLASS_OBJSTORE			0xff0c	/* Object store */
#define DBCLASS_V3ONEDOCFILE		0xff0d
#define	DBCLASS_V4NOTEFILE			0xff0e
#define	DBCLASS_V5NOTEFILE			0xff0f
#define	DBCLASS_V6NOTEFILE			0xff10
#define	DBCLASS_V8NOTEFILE			0xff11
#define	DBCLASS_V85NOTEFILE			0xff12
#define	DBCLASS_V9NOTEFILE		    0xff13
#define	DBCLASS_V10NOTEFILE		    0xff14


#define	DBCLASS_MASK			0x00ff
#define	DBCLASS_VALID_MASK		0xff00

/*	Define NSF Special Note ID Indices.  The first 16 of these are reserved
	for "default notes" in each of the 16 note classes.  In order to access
	these, use SPECIAL_ID_NOTE+NOTE_CLASS_XXX.  This is generally used
	when calling NSFDbGetSpecialNoteID. NOTE: NSFNoteOpen, NSFDbReadObject
	and NSFDbWriteObject support reading special notes or objects directly
	(without calling NSFDbGetSpecialNoteID).  They use a DIFFERENT flag
	with a similar name: NOTE_ID_SPECIAL (see nsfnote.h).  Remember this
	rule:

	SPECIAL_ID_NOTE is a 16 bit mask and is used as a NoteClass argument.
	NOTE_ID_SPECIAL is a 32 bit mask and is used as a NoteID or RRV argument.
*/

#define	SPECIAL_ID_NOTE			0x8000	/* use in combination w/NOTE_CLASS 
											when calling NSFDbGetSpecialNoteID */
/*	Get/Set DbOption routines */
STATUS LNPUBLIC NSFDbGetOptions (DBHANDLE hDB, DWORD far *retDbOptions);
STATUS LNPUBLIC NSFDbSetOptions (DBHANDLE hDB, DWORD DbOptions, DWORD Mask);
#define	DBOPTION_FT_INDEX			0x00000001	/* Enable full text indexing */
#define DBOPTION_IS_OBJSTORE		0x00000002	/* TRUE if database is being used
												   as an object store - for garbage collection */
#define DBOPTION_USES_OBJSTORE		0x00000004	/* TRUE if database has notes which refer to an
												   object store - for garbage collection*/
#define DBOPTION_OBJSTORE_NEVER		0x00000008	/* TRUE if NoteUpdate of notes in this db should
												   never use an object store. */
#define DBOPTION_IS_LIBRARY			0x00000010  /* TRUE if database is a library */
#define DBOPTION_UNIFORM_ACCESS		0x00000020	/* TRUE if uniform access control
												   across all replicas */
#define DBOPTION_OBJSTORE_ALWAYS	0x00000040	/* TRUE if NoteUpdate of notes in this db should
												   always try to use an object store. */
#define DBOPTION_NO_BGAGENT			0x00000200	/* TRUE if db has no background agent */
#define DBOPTION_OUT_OF_SERVICE		0x00000400	/* TRUE is db is out-of-service, no new opens allowed. */
#define DBOPTION_IS_PERSONALJOURNAL	0x00000800	/* TRUE if db is personal journal */
#define DBOPTION_MARKED_FOR_DELETE	0x00001000	/* TRUE if db is marked for delete.  no new opens allowed,
													cldbdir will delete the database when ref count = 0 */
#define DBOPTION_HAS_CALENDAR		0x00002000	/* TRUE if db stores calendar events */
#define DBOPTION_IS_CATALOG_INDEX	0x00004000	/* TRUE if db is a catalog index */
#define DBOPTION_IS_ADDRESS_BOOK	0x00008000	/* TRUE if db is an address book */
#define DBOPTION_IS_SEARCH_SCOPE	0x00010000	/* TRUE if db is a "multi-db-search" repository */
#define DBOPTION_IS_UA_CONFIDENTIAL	0x00020000	/* TRUE if db's user activity log is confidential, only
												*  		viewable by designer and manager */
#define DBOPTION_RARELY_USED_NAMES	0x00040000	/* TRUE if item names are to be treated as
												*  if the ITEM_RARELY_USED_NAME flag is set. */
#define DBOPTION_IS_SITEDB			0x00080000	/* TRUE if db is a "multi-db-site" repository */
/*	This is the structure used for the Item Definition Table */

typedef struct {
	WORD Length;				/* total length of this buffer */
	WORD Items;					/* number of items in the table */
								/* now come the ITEM_DEFINITION structures */
								/* now comes the packed text */
} ITEM_DEFINITION_TABLE;

typedef struct {
	WORD Spare;					/* Spare */
	WORD ItemType;				/* default data type of the item */
	WORD NameLength;			/* length of the item's name */
} ITEM_DEFINITION;

/*	Database Activity Structure */

/* duplicate sturcture to ACTIVITY_ENTRY_DETAILS in nsfods.h, must change both. */
typedef struct {
	WORD DataReads;					/* # of data notes read */
 	WORD DataAdds;					/* # of data notes added */
	WORD DataUpdates;				/* # of data notes updated */
	WORD DataDeletes;				/* # of data notes deleted */
	WORD NonDataReads;			 	/* # of nondata notes read */
 	WORD NonDataAdds;			 	/* # of nondata notes added */
	WORD NonDataUpdates;		 	/* # of nondata notes updated */
	WORD NonDataDeletes;		 	/* # of nondata notes deleted */
} ACTIVITY_ENTRY_DETAILS_DUP;

typedef struct {
	TIMEDATE First;				/* Beginning of reporting period */
	TIMEDATE Last;				/* End of reporting period */
	DWORD Uses;					/* # of uses in reporting period */
	DWORD Reads;				/* # of reads in reporting period */
	DWORD Writes;				/* # of writes in reporting period */
	DWORD PrevDayUses;			/* # of uses in previous 24 hours */
	DWORD PrevDayReads;			/* # of reads in previous 24 hours */
	DWORD PrevDayWrites;		/* # of writes in previous 24 hours */
	DWORD PrevWeekUses;			/* # of uses in previous week */
	DWORD PrevWeekReads;		/* # of reads in previous week */
	DWORD PrevWeekWrites;		/* # of writes in previous week */
	DWORD PrevMonthUses;		/* # of uses in previous month */
	DWORD PrevMonthReads;		/* # of reads in previous month */
	DWORD PrevMonthWrites;		/* # of writes in previous month */
} DBACTIVITY;

typedef struct {
	TIMEDATE First;				/* Beginning of reporting period */
	TIMEDATE Last;				/* End of reporting period */
	DWORD Uses;					/* # of uses in reporting period */
	DWORD Reads;				/* # of reads in reporting period */
	DWORD Writes;				/* # of writes in reporting period */
	DWORD Adds;
	DWORD Updates;
	DWORD Deletes;
	DWORD PrevDayUses;			/* # of uses in previous 24 hours */
	DWORD PrevDayReads;			/* # of reads in previous 24 hours */
	DWORD PrevDayAdds;
	DWORD PrevDayUpdates;
	DWORD PrevDayDeletes;
	DWORD PrevWeekUses;			/* # of uses in previous week */
	DWORD PrevWeekReads;		/* # of reads in previous week */
	DWORD PrevWeekAdds;
	DWORD PrevWeekUpdates;
	DWORD PrevWeekDeletes;
	DWORD PrevMonthUses;		/* # of uses in previous month */
	DWORD PrevMonthReads;		/* # of reads in previous month */
	DWORD PrevMonthAdds;
	DWORD PrevMonthUpdates;
	DWORD PrevMonthDeletes;
} DBACTIVITYEXTENDED;

typedef struct {
	TIMEDATE Time;				/* Time of record */
	WORD Reads;					/* # of data notes read */
 	WORD Writes;				/* # of data notes written */
	DWORD UserNameOffset;		/* Offset of the user name from the beginning
								   of this memory block */
								/* User names follow -- '\0' terminated */	
} DBACTIVITY_ENTRY;

typedef struct {
	TIMEDATE Time;				/* Time of record */
	ACTIVITY_ENTRY_DETAILS_DUP AEDetails;
	DWORD UserNameOffset;		/* Offset of the user name from the beginning
								   of this memory block */
								/* User names follow -- '\0' terminated */	
} DBACTIVITY_ENTRY_EXTENDED;


#define NSFDbGetActivityUserNamePtr(DbActivity, Index) 	\
				(((char FAR *) DbActivity) + DbActivity[Index].UserNameOffset)
																			  

/*	Define NSF DB open modes */

#define DB_LOADED 1					/* hDB refers to a normal database file */
#define DB_DIRECTORY 2				/* hDB refers to a "directory" and not a file */

/*	Define argument to NSFDbInfoParse/Modify to manipulate components from DbInfo */

#define INFOPARSE_TITLE			0
#define INFOPARSE_CATEGORIES	1
#define INFOPARSE_CLASS			2
#define INFOPARSE_DESIGN_CLASS	3

/*	Definitions for NSFDbGetMultNoteInfo and NSFDbGetMultNoteInfoByUNID */

#define fINFO_NOTEID			0x0001	/* Return NoteID */
#define fINFO_SEQTIME			0x0002	/* Return SequenceTime from OID */
#define fINFO_SEQNUM			0x0004	/* Return Sequence number from OID */
#define fINFO_OID				0x0008	/* Return OID (disables SeqTime & number & UNID) */
#define fINFO_COMPRESS			0x0040	/* Compress non-existent UNIDs */
#define fINFO_UNID				0x0080	/* Return UNID  */
#define fINFO_ALLOW_HUGE		0x0400	/* Allow the returned buffer to exceed 64k. */


/* 	Array entry returned from NSFDbGetReplHistorySummary */

typedef struct {
	TIMEDATE		ReplicationTime;	/*	Time returned from last replciation */
	WORD			AccessLevel;		/*	Access level at time of replication */
	WORD			AccessFlags;		/*	Access flags at time of replication */
	WORD			Direction;			/*	NEVER, SEND, RECEIVE */
	DWORD			ServerNameOffset;	/*	Server name offset in packed data */
	WORD			ServerNameLength;	/*	Server name length in packed data */
	WORD			FileNameLength;		/*	File name length in packed data */
										/*	Total server!!file length is */ 
										/*	ServerNameLength + FileNameLength + 2 */
										/*	to compensate for the !! separator */
	WORD			MoreInfo;			/*	contains MoreInfo from cache - includes complete replication flag */
	WORD			wSpare;				/*	Room for growth */
	DWORD			dwSpare;			/*	Room for growth */
										/*	Server/file name pairs follow as */
										/*	"<server name>!!<file name>" with */
										/*	NULL after each pairing */
} REPLHIST_SUMMARY;

/*	Types for REPLHISTORY.Direction */

#define	DIRECTION_NEVER		0
#define	DIRECTION_SEND		1
#define	DIRECTION_RECEIVE	2

/*	Macros for accessing packed data following the REPLHISTORY_SUMMARY array.

	NOTE: The server name pointer is NOT null-terminated, but the file name
	pointer is.  This is so the caller can use the "server file" string 
	directly.
*/

#define NSFGetSummaryServerNamePtr(Summary, Index) 	\
				(((char FAR *) Summary) + Summary[Index].ServerNameOffset)
#define NSFGetSummaryFileNamePtr(Summary, Index) 	\
				(((char FAR *) Summary) + Summary[Index].ServerNameOffset + \
					Summary[Index].ServerNameLength + 2)

/*	Option flags for NSFDbGetReplHistorySummary */

#define REPLHIST_REMOVE_WILDCARDS	0x00000001L	/*	Don't copy wild card entries */
#define REPLHIST_SORT_BY_DATE		0x00000002L	/*	Sort by date.  Default is
													by server name */
#define REPLHIST_ONLY_COMPLETE		0x00000004L	/*	Only return complete entries */

/*	Structure returned from NSFDbGetMajMinVersion

	NOTE:	For release 5.0.4a, the values would be:

				MajorVersion = 5
				MinorVersion = 0
				QMRNumber	 = 4
				QMUNumber	 = 1

*/
typedef struct {
	DWORD	MajorVersion;						/*	Major version identifier */
	DWORD	MinorVersion;						/*	Minor version identifier */
	DWORD	QMRNumber;							/*	Maintenance Release identifier */
	DWORD	QMUNumber;							/*	Maintenance Update identifier */
	DWORD	HotfixNumber;						/*	Hotfixes installed on machine */	
	DWORD	Flags;								/*	See BUILDVERFLAGS_xxx */
	DWORD	FixpackNumber;						/*	Fixpack version installed on machine */
	DWORD	Spare[2];							/*	Room for growth */
	} BUILDVERSION;

/*	Flags returned in the 'Flags' section of the BUILDVERSION structure */
#define BLDVERFLAGS_NONPRODUCTION	0x00000001L	/*	Non-production style build (internal only). */


/* 	Option flags for NSFDbCreateExtended */

#define	DBCREATE_LOCALSECURITY			0x0001
#define	DBCREATE_OBJSTORE_NEVER			0x0002
#define DBCREATE_MAX_SPECIFIED			0x0004
#define DBCREATE_NORESPONSE_INFO		0x0010	/* Don't support note hierarchy - ODS21 and up only */
#define DBCREATE_NOUNREAD				0x0020	/* Don't maintain unread lists for this DB */
#define DBCREATE_NO_FREE_OVERWRITE		0x0200	/* Skip overwriting freed disk buffer space */
#define DBCREATE_FORM_BUCKET_OPT		0x0400	/* Maintain form/bucket bitmap */
#define	DBCREATE_DISABLE_TXN_LOGGING	0x0800	/* Disable transaction logging for this database if specified */
#define DBCREATE_MAINTAIN_LAST_ACCESSED	0x1000	/* Enable maintaining last accessed time */
#define DBCREATE_IS_MAILBOX				0x4000	/* TRUE if database is a mail[n].box database */
#define DBCREATE_LARGE_UNKTABLE			0x8000	/* TRUE if database should allow "large" (>64K bytes) UNK table */


/* Values for EncryptStrength of NSFDbCreateExtended */

#define	DBCREATE_ENCRYPT_NONE			0x00	
#define	DBCREATE_ENCRYPT_SIMPLE			0x01	
#define DBCREATE_ENCRYPT_MEDIUM			0x02
#define DBCREATE_ENCRYPT_STRONG			0x03
#define DBCREATE_ENCRYPT_AES128			0x04
/* NSFDbCreateExtendedWithOptions Option2 flags */

/* NOTE: When you define a new Option2 flag, OR that flag into the 
   DBCREATE_UNDEFINED_OPTIONS2 definition below */

#define	DBCREATE_USE_SERVER_DEFAULT_DATASTORE			0x00000000
#define	DBCREATE_FORCE_NSF_DATASTORE					0x00000001
#define DBCREATE_FORCE_DB2_DATASTORE					0x00000002

#define DBCREATE_UNDEFINED_OPTIONS2		~(DBCREATE_USE_SERVER_DEFAULT_DATASTORE | \
										  DBCREATE_FORCE_NSF_DATASTORE | \
										  DBCREATE_FORCE_DB2_DATASTORE | \
										  DBCREATE_ODSVERSION6 | \
										  DBCREATE_REVERT_ODS | \
										  DBCREATE_OVERRIDE_ADMINP | \
										  DBCREATE_NEVER_REPLICATE)


STATUS LNPUBLIC NSFDbGetReplHistorySummary (DBHANDLE hDb, DWORD Flags,
							DHANDLE *rethSummary, DWORD * retNumEntries);

STATUS LNPUBLIC NSFDbGetMajMinVersion (DBHANDLE hDb, BUILDVERSION far *retVersion);

#if !defined(DB2GetInfo)
STATUS LNPUBLIC NSFDB2GetInfo( DBHANDLE hDB, DWORD infotype, void far *buffer, DWORD *size );
#endif

/* \client\cldbinfo.c */
#if !defined(DB2GetServerInfo)
STATUS LNPUBLIC NSFDB2GetServerInfo( char *szServerName, DWORD infotype, void far *buffer, DWORD *size );
#endif

STATUS LNPUBLIC NSFDbIsDB2 (DBHANDLE hDB, BOOL *isDB2);

/* Option flags for NSFDbCreateAndCopy */

#define	DBCOPY_REPLICA					0x00000001L
#define	DBCOPY_SUBCLASS_TEMPLATE		0x00000002L
#define	DBCOPY_DBINFO2					0x00000004L	
#define	DBCOPY_SPECIAL_OBJECTS			0x00000008L
#define	DBCOPY_NO_ACL					0x00000010L
#define	DBCOPY_NO_FULLTEXT				0x00000020L
#define DBCOPY_ENCRYPT_SIMPLE			0x00000040L
#define DBCOPY_ENCRYPT_MEDIUM			0x00000080L
#define DBCOPY_ENCRYPT_STRONG			0x00000100L
#define DBCOPY_KEEP_NOTE_MODTIME		0x00000200L
#define DBCOPY_REPLICA_NAMELIST			0x01000000L	/* Copy the NameList (applicable only when DBCOPY_REPLICA is specified) */
#define DBCOPY_DEST_IS_NSF				0x02000000L	/* Destination is NSF-backed database */
#define DBCOPY_DEST_IS_DB2				0x04000000L	/* Destination is DB2-backed database */
#define DBCOPY_OVERRIDE_DEST			0x08000000L	/* Destination should override default if able to */
#define DBCOPY_DBCLASS_HIGHEST_NOTEFILE 0x10000000L /* Create Db using the latest ODS, regardless of INI settings */
#define DBCOPY_COMPACT_REPLICA			0x20000000L /* Create Db for copy style compaction */

#define DBCOPY_ENCRYPT_FLAGS  (DBCOPY_ENCRYPT_SIMPLE | DBCOPY_ENCRYPT_MEDIUM | DBCOPY_ENCRYPT_STRONG | DBCOPY_ENCRYPT_SWITCH)
#define DBCOPY_ENCRYPT_AES128           (DBCOPY_ENCRYPT_SWITCH | 0)

STATUS LNPUBLIC NSFDbCopyExtended (DBHANDLE hSrcDB, DBHANDLE hDstDB, 
						TIMEDATE Since, WORD NoteClassMask, DWORD Flags, 
						TIMEDATE far *retUntil);
STATUS LNPUBLIC NSFDbOpen (const char far *PathName, DBHANDLE far *rethDB);
STATUS LNPUBLIC NSFDbOpenTemplate (const char far *PathName, DBHANDLE far *rethDB);
STATUS LNPUBLIC NSFDbOpenExtended (const char far *PathName, WORD Options,
								DHANDLE hNames,
								TIMEDATE far *ModifiedTime,
								DBHANDLE far *rethDB,
								TIMEDATE far *retDataModified,
								TIMEDATE far *retNonDataModified);
STATUS LNPUBLIC NSFDbOpenTemplateExtended (const char far *PathName, WORD Options,
								DHANDLE hNames,
								TIMEDATE far *ModifiedTime,
								DBHANDLE far *rethDB,
								TIMEDATE far *retDataModified,
								TIMEDATE far *retNonDataModified);
STATUS LNPUBLIC NSFDbClose (DBHANDLE hDB);
STATUS LNPUBLIC NSFDbCreate (const char far *PathName, USHORT DbClass, BOOL ForceCreation);
STATUS LNPUBLIC NSFDbCreateObjectStore (const char far *PathName, BOOL ForceCreation);
STATUS LNPUBLIC NSFDbDelete (const char far *PathName);
STATUS LNPUBLIC NSFDbCreateExtended (const char far *PathName, WORD DbClass, 
									 BOOL ForceCreation, WORD Options, 
									 BYTE EncryptStrength, DWORD MaxFileSize);
STATUS LNPUBLIC NSFDbCreateExtendedWithOptions(const char far *filename, WORD dbclass, BOOL force,
									 WORD Option, DWORD Option2, BYTE EncryptStrength, DWORD MaxFileSize,
									 const char far *String1, const char far *String2, 
									 WORD ReservedListLength, WORD ReservedListCount, DHANDLE hReservedList);
STATUS LNPUBLIC NSFDbCreateWithUserNameList(const char far *PathName, WORD DbClass, 
									 BOOL ForceCreation, WORD Options, 
									 BYTE EncryptStrength, DWORD MaxFileSize, DHANDLE hNamesList);
STATUS LNPUBLIC NSFDbDeleteExtended (const char far *PathName, DHANDLE hNameList);

STATUS LNPUBLIC NSFDbCopy (DBHANDLE hSrcDB, DBHANDLE hDstDB, TIMEDATE Since, WORD NoteClassMask);
STATUS LNPUBLIC NSFDbCopyNote (DBHANDLE hSrcDB, DBID far *SrcDbID, DBID far *SrcReplicaID,
								NOTEID SrcNoteID,
								DBHANDLE hDstDB, DBID far *DstDbID, DBID far *DstReplicaID,
								NOTEID far *retDstNoteID, WORD far *retNoteClass);

STATUS LNPUBLIC NSFDbCreateAndCopyExtended(const char far* srcDb,const char far* dstDb, WORD NoteClass, WORD limit, 
	DWORD flags, DHANDLE hNames, DBHANDLE far* retHandle);
STATUS LNPUBLIC NSFDbCreateAndCopy(const char far* srcDb,const char far* dstDb, WORD NoteClass, WORD limit, DWORD flags, DBHANDLE far* retHandle);
STATUS LNPUBLIC NSFDbMarkInServiceExtended(const char far* dbPathPtr, DHANDLE hNames);
STATUS LNPUBLIC NSFDbMarkForDelete(const char far* dbPathPtr);
STATUS LNPUBLIC NSFDbMarkInService(const char far* dbPathPtr);
STATUS LNPUBLIC NSFDbMarkOutOfService(const char far* dbPathPtr);

STATUS LNPUBLIC NSFDbCopyNoteExt(DBHANDLE hSrcDB,DBID *SrcDbID,DBID *SrcReplicaID,NOTEID SrcNoteID,
							DBHANDLE hDstDB,DBID *DstDbID,DBID *DstReplicaID,
							DWORD dwOpenFlags, DWORD dwUpdateFlags,
							NOTEID *retDstNoteID,WORD *retNoteClass);
STATUS LNPUBLIC NSFDbCopyACL (DBHANDLE hSrcDB, DBHANDLE hDstDB);
STATUS LNPUBLIC NSFDbCopyTemplateACL (DBHANDLE hSrcDB, DBHANDLE hDstDB, char far *Manager, WORD DefaultAccessLevel);
STATUS LNPUBLIC NSFDbCreateACLFromTemplate (DBHANDLE hNTF, DBHANDLE hNSF,
										const char far *Manager, WORD DefaultAccess,
										DHANDLE far *rethACL);
STATUS LNPUBLIC NSFDbStoreACL (DBHANDLE hDB, DHANDLE hACL, DWORD ObjectID, WORD Method);
STATUS LNPUBLIC NSFDbReadACL(DBHANDLE hDB, DHANDLE far *rethACL);
STATUS LNPUBLIC NSFDbGenerateOID (DBHANDLE hDB, OID far *retOID);
STATUS LNPUBLIC NSFSetMaxPasswordAccess(DBHANDLE hDB, WORD Level);
STATUS LNPUBLIC NSFGetMaxPasswordAccess(DBHANDLE hDB, WORD *retLevel);
STATUS LNPUBLIC NSFDbModifiedTime (DBHANDLE hDB, TIMEDATE far *retDataModified, TIMEDATE far *retNonDataModified);
STATUS LNPUBLIC NSFDbModifiedTimeByName(const char *DbName, TIMEDATE *retDataModified, TIMEDATE *retNonDataModified);
STATUS LNPUBLIC NSFDbPathGet (DBHANDLE hDB, char far *retCanonicalPathName, char far *retExpandedPathName);
STATUS LNPUBLIC NSFDbInfoGet (DBHANDLE hDB, char far *retBuffer);
STATUS LNPUBLIC NSFDbInfoSet (DBHANDLE hDB, char far *Buffer);
void LNPUBLIC   NSFDbInfoParse(char far *Info, WORD What, char far *Buffer, WORD Length);
void LNPUBLIC   NSFDbInfoModify(char far *Info, WORD What, const char far *Buffer);
STATUS LNPUBLIC NSFDbGetSpecialNoteID (DBHANDLE hDB, WORD Index, NOTEID far *retNoteID);
STATUS LNPUBLIC NSFDbIDGet (DBHANDLE hDB, DBID far *retDbID);
STATUS LNPUBLIC NSFDbReplicaInfoGet (DBHANDLE hDB, DBREPLICAINFO far *retReplicationInfo);
STATUS LNPUBLIC NSFDbReplicaInfoSet (DBHANDLE hDB, DBREPLICAINFO far *ReplicationInfo);
STATUS LNPUBLIC NSFDbReplicaInfoSetExtended (DBHANDLE hDB, DBREPLICAINFO far *ReplicationInfo, DHANDLE hNamesList);
STATUS LNPUBLIC NSFDbGetNoteInfo (DBHANDLE hDB, NOTEID NoteID,
									OID far *retNoteOID,
									TIMEDATE far *retModified,
									WORD far *retNoteClass);
STATUS LNPUBLIC NSFDbGetNoteInfoExt (DBHANDLE hDB, NOTEID NoteID,
									OID far *retNoteOID,
									TIMEDATE far *retModified,
									WORD far *retNoteClass,
									TIMEDATE *retAddedToFile,
									WORD *retResponseCount, 
									NOTEID *retParentNoteID);
STATUS LNPUBLIC NSFDbHasProfileNoteChanged(DBHANDLE hDB, NOTEID noteid, DWORD *pSeqNum, TIMEDATE *Since, BOOL *HasChanged, TIMEDATE *retModTime);
STATUS LNPUBLIC NSFDbGetMultNoteInfo(DBHANDLE hDB, WORD Count, WORD Options,
							DHANDLE hInBuf, DWORD *retSize, DHANDLE *rethOutBuf);
#define DBQUOTA_NOT_SPECIFIED (-1)

STATUS LNPUBLIC NSFDbQuotaGet (const char far *Filename, DBQUOTAINFO far *retQuotaInfo);
STATUS LNPUBLIC NSFDbQuotaSetExt(const char far *Filename, DWORD Flags, DBQUOTAINFO far *QuotaInfo);

STATUS LNPUBLIC NSFDbQuotaGethDB(DBHANDLE hDB, DBQUOTAINFOEXT *QuotaInfo) ;

/* Options for quota detection,enforcement method */

#define NSF_QUOTA_METHOD_DEFAULT				0L
#define NSF_QUOTA_METHOD_USAGE					1L
#define NSF_QUOTA_METHOD_FILESIZE				2L
#define NSF_QUOTA_METHOD_FILESIZE_ADD			3L

STATUS LNPUBLIC NSFDbFTSizeGet(const char far *Filename, DWORD *FTSize);
STATUS LNPUBLIC NSFDbGetNoteInfoByUNID(DBHANDLE hDB, UNID far *pUNID, 
									NOTEID far *retNoteID, OID far *retOID, 
									TIMEDATE far *retModTime, WORD far *retClass);
STATUS LNPUBLIC NSFDbGetMultNoteInfoByUNID(DBHANDLE hDB, WORD Count, WORD Options,
							DHANDLE hInBuf, DWORD *retSize, DHANDLE *rethOutBuf);
STATUS LNPUBLIC NSFDbGetModifiedNoteTable (DBHANDLE hDB, WORD NoteClassMask, TIMEDATE Since,
									TIMEDATE far *retUntil,
									DHANDLE far *rethTable);
STATUS LNPUBLIC NSFApplyModifiedNoteTable (DHANDLE hModifiedNotes, DHANDLE hTargetTable);
STATUS LNPUBLIC NSFDbLocateByReplicaID (DBHANDLE hDB, DBID far *ReplicaID, char far *retPathName, WORD PathMaxLen);
STATUS LNPUBLIC NSFDbStampNotes (DBHANDLE hDB, DHANDLE hTable,
									const char far *ItemName, WORD ItemNameLength,
									void far *Data, WORD DataLength);
STATUS LNPUBLIC NSFDbStampNotesMultiItem (DBHANDLE hDB, DHANDLE hTable, DHANDLE hInNote);

/* Option flags for NSFDbStampNotesMultiItemExt */
#define	DBSTAMP_NOTE_ITEM_REPLACE		0x00000001L

STATUS LNPUBLIC NSFDbStampNotesMultiItemExt (DBHANDLE hDB, DHANDLE hTable, DHANDLE hInNote,DWORD dwFlags);
STATUS LNPUBLIC NSFDbDeleteNotes (DBHANDLE hDB, DHANDLE hTable, UNID far *retUNIDArray);
STATUS LNPUBLIC NSFDbUserNameGet (DBHANDLE hDB, char far *retUserName, WORD BufferLength);
STATUS LNPUBLIC NSFDbGetNamesList(DBHANDLE hDB, DWORD Flags, DHANDLE *rethNamesList);
void LNPUBLIC NSFDbAccessGet(DBHANDLE hDB, WORD far *retAccessLevel, WORD far *retAccessFlag);
STATUS LNPUBLIC NSFDbRename (const char far *from, const char far *to);
STATUS LNPUBLIC NSFDbClassGet (DBHANDLE hDB, WORD far *retClass);
STATUS LNPUBLIC NSFDbModeGet (DBHANDLE hDB, USHORT far *retMode);
STATUS LNPUBLIC NSFDbGetUserActivity(DBHANDLE hDB, DWORD Flags, DBACTIVITY far *retDbActivity,
									DHANDLE far *rethUserInfo, WORD far *retUserCount);
STATUS LNPUBLIC NSFDbGetUserActivityExtended(DBHANDLE hDB, DWORD Flags, DBACTIVITYEXTENDED far *retDbActivity,
									DHANDLE far *rethUserInfo, WORD far *retUserCount);
STATUS LNPUBLIC NSFDbCloseSession (DBHANDLE hDB);
STATUS LNPUBLIC NSFDbReopen (DBHANDLE hDB, DBHANDLE far *rethDB);
STATUS LNPUBLIC NSFDbMajorMinorVersionGet (DBHANDLE hDB, WORD far *retMajorVersion, 
											 WORD far *retMinorVersion);
STATUS LNPUBLIC NSFDbItemDefTable (DBHANDLE hDB,ITEMDEFTABLEHANDLE far *retItemNameTable);
STATUS LNPUBLIC NSFDbItemDefTableExt (DBHANDLE hDB,ITEMDEFTABLEEXTHANDLE far *retItemNameTable);
STATUS LNPUBLIC NSFDbGetBuildVersion (DBHANDLE hDB,WORD far *retVersion);
STATUS LNPUBLIC NSFDbSpaceUsage (DBHANDLE hDB, DWORD far *retAllocatedBytes, DWORD far *retFreeBytes);
STATUS LNPUBLIC NSFDbSpaceUsageScaled (DBHANDLE hDB, DWORD far *retAllocatedGranules, DWORD far *retFreeGranules, DWORD far *retGranularity);
DWORD LNPUBLIC NSFDbGetOpenDatabaseID (DBHANDLE hDB);
STATUS LNPUBLIC NSFGetServerStats(char far *ServerName, char far *Facility, char far *StatName, DHANDLE far *rethTable, DWORD far *retTableSize);
STATUS LNPUBLIC NSFGetServerLatency(char far *ServerName, DWORD Timeout,
								DWORD far *retClientToServerMS,
								DWORD far *retServerToClientMS,
								WORD far *ServerVersion);
STATUS LNPUBLIC NSFRemoteConsole(char far *ServerName, char far *ConsoleCommand, DHANDLE far *hResponseText);

STATUS LNPUBLIC NSFBuildNamesList(char *UserName, DWORD dwFlags, DHANDLE *rethNamesList);
STATUS LNPUBLIC NSFDbClearReplHistory(DBHANDLE hDb, DWORD dwFlags);
#if !defined(NSFDbGetModifiedUnreadTables)
STATUS LNPUBLIC NSFDbGetModifiedUnreadTables(DBHANDLE hDB, char* UserName, WORD UserNameLen, TIMEDATE Since, TIMEDATE *Until, DHANDLE *hRead, DHANDLE *hUnread);
#endif
STATUS LNPUBLIC NSFDbUpdateUnread (DBHANDLE hDataDB, DHANDLE hUnreadList);
STATUS LNPUBLIC NSFDbGetUnreadNoteTable(DBHANDLE hDB,
						char far *UserName, WORD UserNameLength, BOOL fCreateIfNotAvailable,
						DHANDLE far *rethUnreadList);
STATUS LNPUBLIC NSFDbGetUnreadNoteTable2(DBHANDLE hDB,
						char far *UserName, WORD UserNameLength, BOOL fCreateIfNotAvailable, BOOL fUpdateUnread,
						DHANDLE far *rethUnreadList);
STATUS LNPUBLIC NSFDbSetUnreadNoteTable(DBHANDLE hDB, char far *UserName, WORD UserNameLength,
						BOOL fFlushToDisk, DHANDLE hOriginalUnreadList, DHANDLE hUnreadList);
STATUS LNPUBLIC NSFDbGetObjectStoreID(DBHANDLE dbhandle, BOOL far *Specified, DBID far *ObjStoreReplicaID);
STATUS LNPUBLIC NSFDbSetObjectStoreID(DBHANDLE dbhandle, DBID far *ObjStoreReplicaID);
STATUS LNPUBLIC NSFDbFilter(DBHANDLE hFilterDB, NOTEHANDLE hFilterNote,
								DHANDLE hNotesToFilter, BOOL fIncremental,
								void far *Reserved1, void far *Reserved2,
								char far *DbTitle, char far *ViewTitle,
								void far *Reserved3, void far *Reserved4,
								DHANDLE hDeletedList,
								DHANDLE hSelectedList);
STATUS LNPUBLIC NSFDbCompact(const char far *Pathname, WORD Options, DWORD far *retStats);
STATUS LNPUBLIC NSFDbCompactExtended(const char *Pathname, DWORD Options, DWORD *retStats);
STATUS LNPUBLIC NSFDbCompactExtendedExt(const char *Pathname, DWORD Options, NUMBER *OriginalSize, NUMBER *CompactedSize);
STATUS LNPUBLIC NSFDbCompactExtendedExt2(const char *Pathname, DWORD Options, DWORD Options2, NUMBER *OriginalSize, NUMBER *CompactedSize);
/*	Define flags for NSFFolderGetIDTable */
#define DB_GETIDTABLE_VALIDATE 0x00000001	/*	If set, return only "validated" noteIDs */
STATUS LNPUBLIC NSFFolderGetIDTable(DHANDLE hViewDB, DHANDLE hDataDB, NOTEID ViewNoteID, DWORD Flags, DHANDLE *hTable);
STATUS LNPUBLIC NSFGetFolderChanges(DBHANDLE hViewDB, DBHANDLE hDataDB, NOTEID ViewNoteID, TIMEDATE *Since, DWORD Flags, 
											DHANDLE *AddedNoteTable, DHANDLE *RemovedNoteTable);
STATUS far PASCAL NSFGetFolderChangesUNID(DBHANDLE hViewDB, DBHANDLE hDataDB, NOTEID ViewNoteID, TIMEDATE *Since, DWORD Flags, DHANDLE hNoteIDs,										
										DHANDLE *AddedNoteTable, DHANDLE *RemovedNoteTable, DHANDLE *AddedUNIDTable, DHANDLE *RemovedUNIDTable, DWORD *AddedUNIDCount, DWORD *RemovedUNIDCount);
typedef STATUS (LNCALLBACKPTR NSFGETALLFOLDERCHANGESCALLBACK) (void *Param, UNID *NoteUNID, DHANDLE AddedNoteTable, DHANDLE RemovedNoteTable);
typedef STATUS (LNCALLBACKPTR NSFGETALLFOLDERCHANGESUNIDCALLBACK) (void *Param, UNID *NoteUNID, DHANDLE AddedNoteTable, DHANDLE RemovedNoteTable, 
															DHANDLE AddedUNIDTable, DHANDLE RemoveUNIDTable, DWORD AddedUNIDCount, DWORD RemovedUNIDCount);
STATUS LNPUBLIC NSFGetAllFolderChanges(DHANDLE hViewDB, DHANDLE hDataDB, TIMEDATE *Since, DWORD Flags, 
											NSFGETALLFOLDERCHANGESCALLBACK Callback, void *Param, TIMEDATE *Until);
STATUS LNPUBLIC NSFGetAllFolderChangesUNID(DHANDLE hViewDB, DHANDLE hDataDB, TIMEDATE *Since, DWORD Flags, DHANDLE hNoteIDs,
											NSFGETALLFOLDERCHANGESUNIDCALLBACK Callback, void *Param, TIMEDATE *Until);
#define MAX_ITEMDEF_SEGMENTS 25

typedef struct {
	DWORD	Items;			/* number of items in the table */
	DWORD	ItemDefArray;   /* Memory handle of ITEM_DEFINITION_EXT structures */
	DWORD	NumSegments;	/* Number of non-null segments in ItemNameSegs */
	DHANDLE	ItemNameSegs[MAX_ITEMDEF_SEGMENTS]; /* Segments of packed text */
	DWORD	ItemNameSegLengths[MAX_ITEMDEF_SEGMENTS];
							/* Length of each non-null text segment */
} ITEM_DEFINITION_TABLE_EXT;

typedef struct {
	DWORD	ItemOffset;			/* offset into ItemNameSegs to item name */
	WORD	ItemType;			/* default data type of the item */
	WORD	ItemNameLength;		/* length of the item's name */
} ITEM_DEFINITION_EXT;

typedef struct {
	DWORD	Items;
	void	*pItemDefArray;
	char	*ItemText[MAX_ITEMDEF_SEGMENTS];
	DWORD	NumSegments;
	DWORD	ItemNameSegLengths[MAX_ITEMDEF_SEGMENTS];
} ITEM_DEFINITION_TABLE_LOCK;

/* Accessor routines for item name table returned by NSFDbItemDefTableExt. */
STATUS LNPUBLIC NSFItemDefExtLock(ITEM_DEFINITION_TABLE_EXT *ItemDefTable, ITEM_DEFINITION_TABLE_LOCK *ItemDefTableLock);
STATUS LNPUBLIC NSFItemDefExtUnlock(ITEM_DEFINITION_TABLE_EXT *ItemDefTable, ITEM_DEFINITION_TABLE_LOCK *ItemDefTableLock);
STATUS LNPUBLIC NSFItemDefExtFree(ITEM_DEFINITION_TABLE_EXT *ItemDeftable);
STATUS LNPUBLIC NSFItemDefExtEntries(ITEM_DEFINITION_TABLE_LOCK *ItemDefTableLock, DWORD *NumEntries);
STATUS LNPUBLIC NSFItemDefExtGetEntry(ITEM_DEFINITION_TABLE_LOCK *ItemDefTableLock, DWORD ItemNum, 
										WORD *ItemType, WORD *ItemLength, char **ItemName);

STATUS LNPUBLIC NSFBackupStart(DBHANDLE hDB, DWORD Flags, DHANDLE *BackupContext, DWORD *FileSizeLow, DWORD *FileSizeHigh);
STATUS LNPUBLIC NSFBackupStop(DBHANDLE hDB, DHANDLE BackupContext);
#define BACKUPEND_ABORT		0x00000001			/* Abort curent database backup */
STATUS LNPUBLIC NSFBackupEnd(DBHANDLE hDB, DHANDLE BackupContext, DWORD Options);
STATUS LNPUBLIC NSFBackupSetHighWaterMark(DBHANDLE hDB, DHANDLE BackupContext, 
											DWORD HighWaterMarkLow, DWORD HighWaterMarkHigh);
STATUS LNPUBLIC NSFBackupGetChangeInfoSize(DBHANDLE hDB,
							DHANDLE hBackupContext,										
							DWORD Flags,
							DWORD *InfoSizeLow,
							DWORD *InfoSizeHigh);
STATUS LNPUBLIC NSFBackupGetNextChangeInfo(DBHANDLE hDB,
							DHANDLE hBackupContext,										
							DWORD Flags,
	                        char * Buffer,
							DWORD BufferSize,
							DWORD *FilledSize);

STATUS LNPUBLIC NSFBackupStartApplyChangeInfo(DHANDLE *ApplyInfoContext,
							char * CopyFilePath,
							DWORD Flags,
							DWORD InfoSizeLow,
							DWORD InfoSizeHigh);

typedef STATUS (LNCALLBACKPTR NSFBACKUPAPPLYCHANGECALLBACK) (void *Param, DWORD PositionHigh, DWORD PositionLow, DWORD BufferSize, char *Buffer);

STATUS LNPUBLIC NSFBackupStartApplyChangeInfoWithCallback(DHANDLE *ApplyInfoContext,
														NSFBACKUPAPPLYCHANGECALLBACK Callback, void *Param,
														DWORD Flags,
														DWORD InfoSizeLow,
														DWORD InfoSizeHigh);

STATUS LNPUBLIC NSFBackupApplyNextChangeInfo(
							DHANDLE ApplyInfoContext,
							DWORD Flags,
							char * Buffer,
							DWORD BufferSize);
#define APPLYEND_ABORT		0x00000001			/* Abort current change info appilcation */
STATUS LNPUBLIC NSFBackupEndApplyChangeInfo(DHANDLE ApplyInfoContext,
							DWORD Flags);

STATUS LNPUBLIC NSFBringDatabaseOnline(const char far *	dbPath, 
										DWORD	options);

#define OFFLINE_NODELETE		0x00000001		/* Don't delete database file */
#define OFFLINE_KEEP_ACCESS_ENTITIES 0x00000002 /* Don't delete DB2 access entities */

STATUS LNPUBLIC NSFTakeDatabaseOffline(const char far *	dbPath, 
										DWORD	WaitTime,
										DWORD	options);
STATUS LNPUBLIC NSFDbGetLogInfo(DBHANDLE hDb, 
								DWORD Flags, 
								BOOL * LOGGED,
								UNID * LogID,
								UNID * Dbiid,
								DWORD * LogExtent);

#define DB2BACKUP_FASTCONNECT		0x1
#define DB2BACKUP_NEWREPLICA		0x2

#define DB2BACKUP_COPY_REPLACE			 0x8
#define DB2BACKUP_COPY_DELETE_SRC		 0x10
#define DB2BACKUP_COPY_ISOLATE           0x20
#define DB2BACKUP_COPY_CLOSE             0x40
#define DB2BACKUP_COPY_NONRECOVERABLE    0x80
#define DB2BACKUP_COPY_IGNORE_NIF        0x100
#define DB2BACKUP_COPY_VENDOR_LOAD       0X200

#define DB2BACKUP_LINKS_VERIFYEXISTING  0x01
#define DB2BACKUP_LINKS_SCANSCHEMAS		0x02
#define DB2BACKUP_LINKS_QUIET           0x04

#define DB2BACKUP_NONSFID 0xffffffff

STATUS LNPUBLIC NSFDB2ReconnectNotesDatabase(const char far *  FullPath,
											 const char far *  String1,
											 DWORD  nsfid,
											 DWORD  flags);

STATUS LNPUBLIC NSFDB2RegenerateLinks (DWORD flags);

STATUS LNPUBLIC NSFDB2ListNSFDB2Databases (MEMHANDLE *pHDbList, void far **pDbList, const char far* tablespaceName);

STATUS LNPUBLIC NSFDB2FastCopy(
							   const char far*  srcDB2Database,
							   const char far*  tgtDB2Database, 
							   const char far*  sourceNSF,
							   const char far*  targetNSF,
							   const char far*  groupName, 
							   const char far*  loadParameter,
							   DWORD            WaitTime,
							   DWORD			flags,
							   DWORD            flags2);

STATUS LNPUBLIC NSFDB2GetDbInfoValidity  (const char* filePath,
										  char* Schema,
										  DWORD szSchema,
										  char* tableSpace,
										  DWORD szTableSpace,
										  char* actualTableSpace,
										  DWORD szActualTableSpace,
										  BOOL*	schemaExists,
										  BOOL* tsExists,
										  BOOL* tsMismatch,
										  DWORD flags);

/* Define NSF Group Properties */
#define DB2NSF_GROUP_PROPERTY_CLASS			1

STATUS LNPUBLIC  NSFGetNSFDB2GroupProperty( const char* group, DWORD infotype, void far *buffer, DWORD *size);

/* Definition of the log restore callback function that the backup */

/* utility will have to provide for archive logging.               */
typedef STATUS (LNCALLBACKPTR LOGRESTORECALLBACKFUNCTION)(UNID *LogID, DWORD LogNumber, char *LogSegmentPathName);

typedef enum {
	MediaCallback_NoteUpdate = 0x01,	/* Update of existing Note */
	MediaCallback_NoteInsert = 0x02,	/* Addition of new note */
	MediaCallback_NoteDelete = 0x04,	/* Delete of note */
	MediaCallback_CLR        = 0x08		/* Event is the undo of an action due to some failure */
} MediaCallbackFlags;


typedef struct {
	WORD			InfoSize;	/* Size of this structure, use this to determine if future fields are avail */ 
	NOTEID			NoteId;		/* NoteID for note being altered */
	NOTEHANDLE		hNote;		/* Handle to note being retrieved */
	TIMEDATE		TranTime;	/* Time the transaction ran for which you are being called */
	char far*		UserName;	/* If avail, else a pointer to "" */
	char far*		PathName;	/* Path & file name of DB */
} NOTE_RESTORE_CALLBACK_INFO;

/* Definition of the note restore callback function that the backup/archive */
/* utility will have to provide for monitoring notes during Media Recovery  */
typedef STATUS (LNCALLBACKPTR NOTERESTORECALLBACKFUNCTION)(	DWORD			state_flags,
															void far *		userParm,
															NOTE_RESTORE_CALLBACK_INFO far * info);


/* Log archiving API for backup utilities to call */
/* Possible values returned from NSFGetTransLogStyle */ 
#define TRANSLOG_STYLE_CIRCULAR 0  /* Circular logging is in effect */
#define TRANSLOG_STYLE_ARCHIVE  1  /* Archive logging is in effect */
#define TRANSLOG_STYLE_LINEAR   2  /* Linear logging is in effect */
STATUS LNPUBLIC NSFGetTransLogStyle(WORD far * LogType);
STATUS LNPUBLIC NSFBeginArchivingLogs(void);
STATUS LNPUBLIC NSFEndArchivingLogs(void);
STATUS LNPUBLIC  NSFGetFirstLogToArchive(UNID far * LogID, DWORD far * LogNumber, char far * LogPath);
STATUS LNPUBLIC NSFGetNextLogToArchive(UNID far * LogID, DWORD far * LogNumber, char far * LogPath);
STATUS LNPUBLIC NSFDoneArchivingLog(UNID far * LogID, DWORD far * LogSequenceNumber);
/* Wait for any other media recovery to finish, vs. return immed if busy */
#define  DBRECOVER_WAIT				0x0001
/* Make recovered db a new instance so it will not conflict with original */
#define  DBRECOVER_ZAP_ID			0x0002
/* Refresh a backup to the current level, mutually exclusive with DBRECOVER_ZAP_ID */
#define  DBRECOVER_REFRESH_BACKUP	0x0004
/* Recover database to a point in time, mutually exclusive with DBRECOVER_REFRESH_BACKUP */
#define  DBRECOVER_POINT_IN_TIME	0x0008
/* Give recovered db a new replica id so it will not conflict with original */
#define  DBRECOVER_ZAP_REPLICAID	0x0010
/* Make recovered db a new instance if another copy of the DB is on-line */
#define  DBRECOVER_ZAP_ID_IF_NECESSARY 0x0020
/* Allow alternate path from which to recover old log extents */
#define	 DBRECOVER_ALT_RETRIEVE_PATH 0x0040

STATUS LNPUBLIC NSFRecoverDatabases(const char far *		dbNames, 
									  LOGRESTORECALLBACKFUNCTION restoreCB,
									  DWORD					Flags, /* DBRECOVER_* flags */
									  WORD far *			errDbIndex,
									  TIMEDATE far *		recoveryTime);

STATUS LNPUBLIC NSFRecoverDatabasesWithCallback(const char far *	dbNames, 
									  LOGRESTORECALLBACKFUNCTION	restoreCB,
									  DWORD							Flags, /* DBRECOVER_* flags */
									  WORD far *					errDbIndex,
									  TIMEDATE far *				recoveryTime,
									  NOTERESTORECALLBACKFUNCTION	noteCB,
									  void far *					userParm);


/* rmmisc.cpp */

/* Return BOOL if span specified, else actual amount of log to process */
STATUS LNPUBLIC NSFIsNewBackupNeeded(const char far *		dbName, 
									 DWORD					comfortSpan, /* Requested Pad Log span in K */
									 DWORD far *			backupNeeded);
STATUS far PASCAL NSFGetChangedDBs(char *ServerName, TIMEDATE *SinceTime, DWORD *ChangesSize, DHANDLE *hChanges, TIMEDATE *NextSinceTime);

/* flags for the retFlags */
#define GETCHANGES_CLUSTER_FAILOVER 	0x0001 	/* set if cluster services used to service the call */
#define GETCHANGES_CLUSTER_FAILED_DBS 	0x0002 	/* set at least one database not serviced when failover used */
#define GETCHANGES_CLUSTER_FAILBACK 	0x0004 	/* set after failover used and original server serviced call */

STATUS far PASCAL NSFGetDBChangesExt(char *pServerName, TIMEDATE *SinceTime, DWORD DbListSize, MEMHANDLE hDbList, DWORD ListFlags, DWORD Flags, 
		DWORD *retChangesSize, MEMHANDLE *rethChanges, TIMEDATE *retNextSinceTime, DWORD *retFlags, MEMHANDLE *retClusterCtl, 
		MEMHANDLE *retDbServerNames, MEMHANDLE *retServerTimes);

STATUS far PASCAL NSFGetDBChanges(char *pServerName, TIMEDATE *SinceTime, DWORD DbListSize, MEMHANDLE hDbList, DWORD ListFlags, DWORD Flags, DWORD *retChangesSize, MEMHANDLE *rethChanges, TIMEDATE *retNextSinceTime);
#define GETCHANGES_TDDATAMODIFIED		0x0001
#define GETCHANGES_TDNONDATEMODIFIED	0x0002
#define GETCHANGES_TDFOLDERMODIFIED		0x0004
#define GETCHANGES_TDUNREADMODIFIED		0x0008
#define GETCHANGES_TDPROFILEMODIFIED	0x0010
#define GETCHANGES_CLUSTER_INIT		0x0020		/* do cluster failover - only valid in NSFGetDBChangesExt */
#define GETCHANGES_CLUSTER_TERM		0x0040		/* free resources allocated in NSFGetDBChangesExt for failover */
							/*   processing - valid only in NSFGetDBChangesExt - no data returned */

STATUS LNPUBLIC NSFDbCreateNoteID(DBHANDLE hDB, BOOL fData, NOTEID *retNoteID);
STATUS LNPUBLIC NSFDbAddItemName(DBHANDLE hDB, WORD type, char *string, WORD length, DWORD *rtnItemNumber); 

/*	Database Hook Drivers
*
* NSF hook drivers enable the API programmer to construct a set of
* subroutines, packaged as a DLL, that "hook" several NSF functions
* related to reading, modifying, and deleting notes.  The principal
* application of these hook drivers is intended to be auditing, that is,
* logging accesses to a database, however they can also be programmed
* to modify the contents of the notes and/or refuse requests.
*
* Hook Driver Packaging and Concurrency Requirements
*
* Like all Notes low-level subsystems, hook drivers must obey strict 
* rules to fit into their computing environment:
*
*    1. The drivers should be available on multiple computing platforms
*
*    2. The drivers are packaged as Dynamic Link Libraries under 
*    Windows, NT, and OS/2. Under Windows, the DEF file must specify the data 
*    as being MOVEABLE SINGLE so that it doesn't occupy GlobalDOS memory, and 
*    because Windows doesn't support multi-instance dynamic link libraries. 
*    For NT and OS/2, we recommend MULTIPLE data, but you can use whatever you 
*    wish.
*
*        For all four environments, Notes uses either LoadLibrary or 
*    DosLoadModule to load the driver. You must decide upon a mnemonic name 
*    for your driver, a maximum of 7 characters that is preferably 
*    nationality-neutral (obscure in all languages), such as NTAUDIT. In order
*    to load the library, Notes prefixes this name with 
*    _ under Windows, $ under OS/2 1.x, I under OS/2 2, and N under NT, 
*    and post-fixes the name with .DLL. The DLL is installed into Notes by 
*    simply placing its executable into the Notes Program Directory.
*
*        Notes automatically loads the hook drivers at initialization.
*    The list of hook drivers to be loaded is specified in NOTES.INI in a
*    variable called NSF_HOOKS with a comma separator. Thus, in order to load
*    three hook drivers, the variable might be specified as
*    NSF_HOOKS=drivera,driverb,driverc. Note that it isn't necessary to
*    specify the prefix character or the suffix .DLL.
*
*        Because of instantiation requirements of the operating systems, 
*    the library is loaded once per process. At load time, the first entry 
*    point address (entry point @1) is obtained by ordinal, and the driver's 
*    Init() function is invoked. The principal use of this function is to plug 
*    a data structure with vectors to other hook driver subroutines, 
*    including its Term() function which will be called by Notes when the 
*    process exits (or performs NotesTerm()).
*
*        Remember that in some environments (such as Windows), you must
*    export, in your DEF file, all of your functions that Notes will call
*    through these vectors. This is because Windows uses the fact that it's
*    exported to generate a thunk that sets up the DLL's DS appropriately on
*    all of these entry points.
*
*    3. All code executed by all entry points to the drivers must 
*    be 100% re-entrant by both multiple threads within a single process and 
*    multiple processes. In Windows, if you Yield() or make a call to a
*    Notes API function, you may also be preempted by another process that
*    does a hook driver call, so reentrancy is a requirement even in Windows.
*    (Notes makes heavy use of multiple threads and multiple processes, so
*    this must be treated as a required feature, not as something that can
*    be done "later".)
*
* Following is the data structure passed to your hook driver's Init routine.
* When your routine is called, the hModule is filled in (just in case you
* need it to load resources), and the rest of the vectors are zero'ed.
* If you don't need to hook any of these vectors, leave them NULL.  Otherwise,
* plug the vectors in your Init routine.
*
*/

typedef struct dbhookvec
	{

	/*	Module handle of the hook library */

	HMODULE hModule;

	/*	Initialization vector.  This is simply a pointer to the routine
		exported as ordinal #1 in your DLL.  You needn't plug this
		vector because it's plugged before calling through it to do
		driver initializations.  This routine is called once for each
		process that does a NotesInit(). */

	STATUS (LNCALLBACKPTR Init)(struct dbhookvec far *vec);

	/*	Termination vector.  This is called once for each process that
		did an Init call, just prior to the process's exiting.  */

	STATUS (LNCALLBACKPTR Term)(struct dbhookvec far *vec);

	/*	Note open hook.  This routine is called just AFTER a note is opened
		by the NSF subsystem.  It is called for both local and remote
		databases.  UserName is the name of the user doing the open.
		GroupList may be NULL, but when it's not it contains a list of
		the groups that the user is in.  hDB and NoteID can be used
		to identify the database and note (use NSFDbPathGet to get the
		pathname of the database).  OpenFlags are the flags originally
		passed into NSFNoteOpen.  hNote is the handle to the note that
		is about to be returned to the caller.  Your hook driver may
		modify the contents of the note, or may return an error from
		this routine if you wish to fail the open call.  You may use any
		standard Notes error code to fail the call. */

	STATUS (LNCALLBACKPTR NoteOpen)(struct dbhookvec far *vec, char far *UserName, LIST far *GroupList, DBHANDLE hDB, NOTEID NoteID, NOTEHANDLE hNote, WORD OpenFlags);

	/*	Note add/update hook, also handles deletion
		This routine is called just BEFORE a note is updated
		by the NSF subsystem.  It is called for both local and remote
		databases.  UserName is the name of the user doing the open.
		GroupList may be NULL, but when it's not it contains a list of
		the groups that the user is in.  hDB and NoteID can be used
		to identify the database and note (use NSFDbPathGet to get the
		pathname of the database).  pUpdateFlags is a pointer to a WORD
		of UpdateFlags originally passed into NSFNoteUpdate.  The hook
		may examine and modify the UpdateFlags WORD before returning,
		thus modifying the flags that will be passed into NSFNoteUpdate.
		hNote is the handle to the note that is about to be updated.
		Your hook driver may modify the contents of the note, or may
		return an error from this routine if you wish to fail the update
		call.  You may use any standard Notes error code to fail the call.
		Note that you can use the following algorithm to determine
		precisely the operation being performed:

		*	if (NoteID == NOTEID_ADD
		*			|| NoteID == NOTEID_ADD_OR_REPLACE
		*			|| NoteID == NOTEID_ADD_UNID)
		*		{
		*		if ((*pUpdateFlags) & UPDATE_DELETED)
		*			; ** Adding a new "deleted note stub" to a database **
		*		else
		*			; ** Adding a new document to a database **
		*		}
		*	else
		*		{
		*		if ((*pUpdateFlags) & UPDATE_DELETED)
		*			; ** Deleting an existing document from the database. **
		*			  ** Note that in this case, the contents of the hNote **
		*			  ** may be nil and should be disregarded; because of **
	    *			  ** this, there's no way to tell the class of a note **
		*			  ** being deleted at this point **
		*		else
		*			; ** Updating an existing document in the database **
		*		}

		*/

	STATUS (LNCALLBACKPTR NoteUpdate)(struct dbhookvec far *vec, char far *UserName, LIST far *GroupList, DBHANDLE hDB, NOTEID NoteID, NOTEHANDLE hNote, WORD far *pUpdateFlags);

	/*	Note stamp (Categorization) hook.
		This routine is called just BEFORE a set of notes is Categorized
		by the NSF subsystem.  It is called for both local and remote
		databases.  UserName is the name of the user doing the categorization.
		GroupList may be NULL, but when it's not it contains a list of
		the groups that the user is in.  hDB and hTable can be used
		to identify the database and notes (use NSFDbPathGet to get the
		pathname of the database).  ItemName and Data indicate the data
		being used in the categorization.  Your hook routine may return
		an error if you wish to fail the Stamp call.  You may use any
		standard Notes error code to fail the call. */

	STATUS (LNCALLBACKPTR DbStampNotes)(struct dbhookvec far *vec, char far *UserName, LIST far *GroupList, DBHANDLE hDB, DHANDLE hIDTable, char far *ItemName, WORD ItemNameLength, void far *Data, WORD Length);

	/*	Flags used by Notes to describe the hook driver -- RESERVED */

	DWORD	Flags;

	} DBHOOKVEC;

STATUS LNPUBLIC NSFDbDirGet(DBHANDLE hDB, char *retDir);
STATUS LNPUBLIC NSFDbIsLocallyEncrypted (DBHANDLE hDB, BOOL *pRetval);
STATUS LNPUBLIC NSFGetOrgDir(char *UserName, char *retDir);
STATUS far PASCAL NSFNoteSetTUAFromParent(DHANDLE hParentNote, DHANDLE hChildNote);

/* End of Note Storage File Database Definitions */

void FAR PASCAL NSFSetURLParam(char * pURL,char * pName, char * pValue,WORD wSize,BOOL * bIsFirstParam,char ** pretNextPos);
BOOL FAR PASCAL NSFGetURLParam(const char * pURL, char * pName,WORD wSize ,char ** retppValue, WORD * retwValueLen);
WORD FAR PASCAL NSFGetURLParamWord(const char * pURL, char * pName, WORD wSize, WORD wDefault);
FLAG FAR PASCAL NSFGetURLParamFlag(const char * pURL, char * pName, WORD wSize, FLAG fDefault);
void FAR PASCAL NSFConvertURLtoNotesFormat(char * pszURL);

// The various types of object store providers
typedef enum
{
	NOS_FILESYSTEM,		// Local filesystem
	NOS_DOMINO,				// domino server 
	NOS_MAX				// Keep this as the last entry
} NOS_TYPE;


/* dbutil\dbtempcleanup.cpp */

/* dbreplace.c */

#ifdef __cplusplus
}
#endif

#endif

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif



#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM                              */
/*                                                                   */
/* L-GHUS-97FH78, L-GHUS-972PJ6                                      */
/*                                                                   */
/* Copyright IBM Corp. 2005, 2013  All Rights Reserved.              */
/*                                                                   */
/* US Government Users Restricted Rights - Use, duplication or       */
/* disclosure restricted by GSA ADP Schedule Contract with           */
/* IBM Corp.                                                         */
/*                                                                   */
/* ***************************************************************** */

#ifndef NSF_STR_DEFS
#define NSF_STR_DEFS

/* errorContext strings for error logging 0 - 255 */
#define STR_RM_INDOUBTPROC_THREAD			PKG_NSF_STR+0
	stringtext(STR_RM_INDOUBTPROC_THREAD,	"Recovery Manager Indoubt resolution Thread")
#define CONTEXT_DB2NSF_INIT				PKG_NSF_STR+1
	stringtext(CONTEXT_DB2NSF_INIT,		"Failed during DB2NSF initialization.")
#define CONTEXT_DB2DROPDB2				PKG_NSF_STR+3
	stringtext(CONTEXT_DB2DROPDB2,		"Failed dropping DB2 Database.")
#define CONTEXT_DB2CREATE_SERV_TAB		PKG_NSF_STR+4
	stringtext(CONTEXT_DB2CREATE_SERV_TAB,	"Failed creating DB2 server table.")
#define CONTEXT_DB2DROP_SERV_TAB		PKG_NSF_STR+5
	stringtext(CONTEXT_DB2DROP_SERV_TAB,	"Failed dropping DB2 server table.")
#define CONTEXT_DB2CREATE_FILE_TAB		PKG_NSF_STR+6
	stringtext(CONTEXT_DB2CREATE_FILE_TAB,	"Failed creating DB2 file table.")
#define CONTEXT_DB2DROP_FILE_TAB		PKG_NSF_STR+7
	stringtext(CONTEXT_DB2DROP_FILE_TAB,	"Failed dropping DB2 file table.")
#define CONTEXT_DB2WRITE_OBJ_HEADER		PKG_NSF_STR+8
	stringtext(CONTEXT_DB2WRITE_OBJ_HEADER,	"Failed writing DB2 object header.")
#define CONTEXT_DB2READ_OBJ_HEADER		PKG_NSF_STR+9
	stringtext(CONTEXT_DB2READ_OBJ_HEADER,	"Failed reading DB2 object header.")
#define CONTEXT_DB2MODIFY_OBJ_HEADER	PKG_NSF_STR+10
	stringtext(CONTEXT_DB2MODIFY_OBJ_HEADER,	"Failed modifying DB2 object header.")
#define CONTEXT_DB2WRITE_OBJ			PKG_NSF_STR+11
	stringtext(CONTEXT_DB2WRITE_OBJ,	"Failed writing DB2 object.")
#define CONTEXT_DB2CLEAR_OBJ			PKG_NSF_STR+12
	stringtext(CONTEXT_DB2CLEAR_OBJ,	"Failed clearing DB2 object.")
#define CONTEXT_DB2READ_OBJ				PKG_NSF_STR+13
	stringtext(CONTEXT_DB2READ_OBJ,		"Failed reading DB2 object.")
#define CONTEXT_DB2DELETE_OBJ			PKG_NSF_STR+14
	stringtext(CONTEXT_DB2DELETE_OBJ,	"Failed deleting DB2 object.")
#define CONTEXT_DB2MODIFY_RRV			PKG_NSF_STR+15
	stringtext(CONTEXT_DB2MODIFY_RRV,	"Failed modifying the RRV (record relocation vector).")
#define CONTEXT_DB2WRITE_OBJ_INFO		PKG_NSF_STR+16
	stringtext(CONTEXT_DB2WRITE_OBJ_INFO,	"Failed writing DB2 object info.")	
#define CONTEXT_DB2I_U_NOBJ				PKG_NSF_STR+17
	stringtext(CONTEXT_DB2I_U_NOBJ,		"Failed inserting or updating DB2 named object.")
#define CONTEXT_DB2DEL_NOBJ				PKG_NSF_STR+18
	stringtext(CONTEXT_DB2DEL_NOBJ,		"Failed deleting DB2 named object.")
#define CONTEXT_DB2READ_NOBJ			PKG_NSF_STR+19
	stringtext(CONTEXT_DB2READ_NOBJ,	"Failed reading DB2 named object.")
#define CONTEXT_DB2ENUM_NOBJ			PKG_NSF_STR+20
	stringtext(CONTEXT_DB2ENUM_NOBJ,	"Failed enumerating DB2 named object.")
#define CONTEXT_DB2RECOVER_FHEADER		PKG_NSF_STR+21
	stringtext(CONTEXT_DB2RECOVER_FHEADER,	"Failed when DB2 was recovering the file header.")
#define CONTEXT_DB2WRITE_FILE_HEADER	PKG_NSF_STR+22
	stringtext(CONTEXT_DB2WRITE_FILE_HEADER,	"Failed writing DB2 file header.")
#define CONTEXT_DB2CREATE_FILE_HEADER	PKG_NSF_STR+23
	stringtext(CONTEXT_DB2CREATE_FILE_HEADER,	"Failed creating DB2 file header.")
#define CONTEXT_DB2DELETE_CATALOG_ENT	PKG_NSF_STR+24
	stringtext(CONTEXT_DB2DELETE_CATALOG_ENT,	"Failed deleting DB2 catalog entry.")
#define CONTEXT_DB2READ_UNK				PKG_NSF_STR+25
	stringtext(CONTEXT_DB2READ_UNK,		"Failed when DB2 was reading UNK table.")
#define CONTEXT_DB2WRITE_UNK			PKG_NSF_STR+26
	stringtext(CONTEXT_DB2WRITE_UNK,	"Failed when DB2 was writing UNK table.")
#define CONTEXT_DB2REFRESH_DIR			PKG_NSF_STR+27
	stringtext(CONTEXT_DB2REFRESH_DIR,	"Failed when DB2 was refreshing directory.")
#define CONTEXT_DB2CONNPOOL_INIT		PKG_NSF_STR+28
	stringtext(CONTEXT_DB2CONNPOOL_INIT,	"Failed when DB2 was initializing the connection pool.")
#define CONTEXT_DB2CP_CREATE_ENT		PKG_NSF_STR+29
	stringtext(CONTEXT_DB2CP_CREATE_ENT,	"Failed when DB2 was creating an entry in the connection pool.")
#define CONTEXT_DB2CP_FREE_ENT			PKG_NSF_STR+30
	stringtext(CONTEXT_DB2CP_FREE_ENT,	"Failed when DB2 was freeing an entry in the connection pool.")
#define CONTEXT_DB2GET_NSF_SCH			PKG_NSF_STR+31
	stringtext(CONTEXT_DB2GET_NSF_SCH,	"Failed when DB2 was getting NSF Schema.")
#define CONTEXT_DB2GET_NSF_TBS			PKG_NSF_STR+32
	stringtext(CONTEXT_DB2GET_NSF_TBS,	"Failed when DB2 was getting NSF TableSpace.")
#define CONTEXT_DB2TERM_SHR_CONN		PKG_NSF_STR+33
	stringtext(CONTEXT_DB2TERM_SHR_CONN,	"Failed when DB2 was terminating shared connections.")
#define CONTEXT_DB2INIT_SHR_CONN		PKG_NSF_STR+34
	stringtext(CONTEXT_DB2INIT_SHR_CONN,	"Failed when DB2 was initializing shared connections.")
#define CONTEXT_DB2EXIST_NSF			PKG_NSF_STR+35
	stringtext(CONTEXT_DB2EXIST_NSF,		"Failed when DB2 was checking the existence of NSF.")
#define CONTEXT_DB2EXIST_NSFIDENT		PKG_NSF_STR+36
	stringtext(CONTEXT_DB2EXIST_NSFIDENT,	"Failed when DB2 checked for NSF identifier.")
#define CONTEXT_DB2SET_ISOLATION		PKG_NSF_STR+37
	stringtext(CONTEXT_DB2SET_ISOLATION,	"Failed when setting DB2 isolation level.")
#define CONTEXT_DB2ALLOC_SESSION		PKG_NSF_STR+38
	stringtext(CONTEXT_DB2ALLOC_SESSION,	"Failed when DB2 was allocating the session.")
#define CONTEXT_DB2CREATE_SAVEPT		PKG_NSF_STR+39
	stringtext(CONTEXT_DB2CREATE_SAVEPT,	"Failed when DB2 was creating save points.")
#define CONTEXT_DB2ROLLB_SAVEPT			PKG_NSF_STR+40
	stringtext(CONTEXT_DB2ROLLB_SAVEPT,	"Failed when DB2 was rolling back save points.")
#define CONTEXT_DB2RELEASE_SAVEPT		PKG_NSF_STR+41
	stringtext(CONTEXT_DB2RELEASE_SAVEPT,	"Failed when DB2 was releasing save points.")
#define CONTEXT_DB2GET_HSTMT			PKG_NSF_STR+42
	stringtext(CONTEXT_DB2GET_HSTMT,	"Failed when DB2 was getting statement handle.")
#define CONTEXT_DB2UPD_FILE_PATH		PKG_NSF_STR+43
	stringtext(CONTEXT_DB2UPD_FILE_PATH,	"Failed when DB2 was updating file paths.")
#define CONTEXT_DB2EXEC_NIFCONNECT		PKG_NSF_STR+44
	stringtext(CONTEXT_DB2EXEC_NIFCONNECT,	"Failed when DB2 was executing NIFConnect.")
#define CONTEXT_DB2GET_PROP				PKG_NSF_STR+45
	stringtext(CONTEXT_DB2GET_PROP,		"Failed when DB2 was getting properties.")
#define CONTEXT_DB2SET_PROP_SRCTARG		PKG_NSF_STR+46
	stringtext(CONTEXT_DB2SET_PROP_SRCTARG,		"Failed when DB2 was setting properties.")
#define CONTEXT_DB2GET_PROP_BLOB		PKG_NSF_STR+47
	stringtext(CONTEXT_DB2GET_PROP_BLOB,		"Failed when DB2 was getting blobs.")
#define CONTEXT_DB2CLOSE_CURSOR			PKG_NSF_STR+48
	stringtext(CONTEXT_DB2CLOSE_CURSOR,		"Failed when DB2 was closing cursor.")
#define CONTEXT_DB2READ_NOTE			PKG_NSF_STR+49
	stringtext(CONTEXT_DB2READ_NOTE,	"Failed when DB2 was reading a note.")
#define CONTEXT_DB2WRITE_RNOTE			PKG_NSF_STR+50
	stringtext(CONTEXT_DB2WRITE_RNOTE,	"Failed when DB2 was writing a row in a note.")
#define CONTEXT_DB2DELETE_RNOTE			PKG_NSF_STR+51
	stringtext(CONTEXT_DB2DELETE_RNOTE,	"Failed when DB2 was deleting a row in a note.")
#define CONTEXT_DB2SEL_NSUMMARY			PKG_NSF_STR+52
	stringtext(CONTEXT_DB2SEL_NSUMMARY,	"Failed when DB2 was selecting note summary set from ID table.")
#define CONTEXT_DB2SEL_NSUMMARY_SET		PKG_NSF_STR+53
	stringtext(CONTEXT_DB2SEL_NSUMMARY_SET,	"Failed when DB2 was selecting note summary set.")
#define CONTEXT_DB2SEL_NOTE			    PKG_NSF_STR+54
	stringtext(CONTEXT_DB2SEL_NOTE,		"Failed when DB2 was selecting a note.")
#define CONTEXT_DB2GET_NOTE_SROW		PKG_NSF_STR+55
	stringtext(CONTEXT_DB2GET_NOTE_SROW,		"Failed when DB2 was fetching a note summary row.")
#define CONTEXT_DB2GET_NOTE			    PKG_NSF_STR+56
	stringtext(CONTEXT_DB2GET_NOTE,		"Failed when DB2 was fetching a note.")
#define CONTEXT_DB2UNID_FINDE			PKG_NSF_STR+57
	stringtext(CONTEXT_DB2UNID_FINDE,	"Failed when DB2 was looking for UNID entry.")
#define CONTEXT_DB2_FINDE_BYNID			PKG_NSF_STR+58
	stringtext(CONTEXT_DB2_FINDE_BYNID,	"Failed when DB2 was looking for an entry by note id.")
#define MSG_DB2NSF_SCHEMA_UPGRADING		PKG_NSF_STR+59
	stringtext(MSG_DB2NSF_SCHEMA_UPGRADING,"Upgrading schema for DB2NSF %s.  This may take several minutes." )
#define CONTEXT_DB2DELETE_QUEUE_ENT		PKG_NSF_STR+60
	stringtext(CONTEXT_DB2DELETE_QUEUE_ENT,	"Failed deleting DB2 queue entry.")
#define CONTEXT_DB2RELOCATE_TS			PKG_NSF_STR+61
	stringtext(CONTEXT_DB2RELOCATE_TS,	"Tablespace container relocation.")
#define ERR_DB2NSF_QUIESCED			    PKG_NSF_STR+62
	stringtext(ERR_DB2NSF_QUIESCED,	    "Unable to Connect to quiesced database.")
#define CONTEXT_DB2COLLECT_COLINFO		PKG_NSF_STR+63
	stringtext(CONTEXT_DB2COLLECT_COLINFO,	"Failed when DB2 was collecting column info.")
#define CONTEXT_DB2PAIFIND_ENTRY		PKG_NSF_STR+64
	stringtext(CONTEXT_DB2PAIFIND_ENTRY,	"Failed when DB2 was finding a named object entry.")
#define CONTEXT_DB2PAIFIND_COUNT		PKG_NSF_STR+65
	stringtext(CONTEXT_DB2PAIFIND_COUNT,	"Failed when DB2 was finding the count of named object entries.")
#define CONTEXT_DB2PAI_INS_UPD			PKG_NSF_STR+66
	stringtext(CONTEXT_DB2PAI_INS_UPD,	"Failed when DB2 was inserting/updating a named object entry.")
#define CONTEXT_DB2PAI_DELETE			PKG_NSF_STR+67
	stringtext(CONTEXT_DB2PAI_DELETE,	"Failed when DB2 was deleting a named object entry.")
#define CONTEXT_DB2CREATE_TAB			PKG_NSF_STR+68
	stringtext(CONTEXT_DB2CREATE_TAB,	"Failed when creating DB2 table.")
#define CONTEXT_DB2CREATE_VIEW			PKG_NSF_STR+69
	stringtext(CONTEXT_DB2CREATE_VIEW,	"Failed when creating DB2 view.")
#define CONTEXT_DB2CREATE_DEL			PKG_NSF_STR+70
	stringtext(CONTEXT_DB2CREATE_DEL,	"Failed when creating DB2 delete.")
#define CONTEXT_DB2CREATE_DELTRIG		PKG_NSF_STR+71
	stringtext(CONTEXT_DB2CREATE_DELTRIG,	"Failed when creating DB2 delete trigger.")
#define CONTEXT_DB2CREATE_INS			PKG_NSF_STR+72
	stringtext(CONTEXT_DB2CREATE_INS,	"Failed when creating DB2 insert.")	
#define CONTEXT_DB2CREATE_INSTRIG		PKG_NSF_STR+73
	stringtext(CONTEXT_DB2CREATE_INSTRIG,	"Failed when creating DB2 insert trigger.")	
#define CONTEXT_DB2CREATE_UPD			PKG_NSF_STR+74
	stringtext(CONTEXT_DB2CREATE_UPD,	"Failed when creating DB2 update.")	
#define CONTEXT_DB2CREATE_UPDTRIG		PKG_NSF_STR+75
	stringtext(CONTEXT_DB2CREATE_UPDTRIG,	"Failed when creating DB2 update trigger.")	
#define CONTEXT_DB2LOAD_ACC_DEF			PKG_NSF_STR+76
	stringtext(CONTEXT_DB2LOAD_ACC_DEF,	"Failed when loading the access definition.")	
#define CONTEXT_DB2CREATE_EXPTAB		PKG_NSF_STR+77
	stringtext(CONTEXT_DB2CREATE_EXPTAB,	"Failed when creating DB2 export table.")	
#define CONTEXT_DB2INS_MAPENT			PKG_NSF_STR+78
	stringtext(CONTEXT_DB2INS_MAPENT,	"Failed when inserting DB2 map entry.")	
#define CONTEXT_DB2DROP_EXPTAB			PKG_NSF_STR+79
	stringtext(CONTEXT_DB2DROP_EXPTAB,	"Failed when dropping DB2 export table.")	
#define CONTEXT_DB2DROP_EXPENT			PKG_NSF_STR+80
	stringtext(CONTEXT_DB2DROP_EXPENT,	"Failed when dropping DB2 exported entity.")	
#define CONTEXT_DB2LOAD_ACCTAB			PKG_NSF_STR+81
	stringtext(CONTEXT_DB2LOAD_ACCTAB,	"Failed when loading the access definition records in the table.")
#define CONTEXT_DB2INS_ACCTAB			PKG_NSF_STR+82
	stringtext(CONTEXT_DB2INS_ACCTAB,	"Failed when inserting in the access table.")
#define CONTEXT_DB2INS_ACCTAB_ROW		PKG_NSF_STR+83
	stringtext(CONTEXT_DB2INS_ACCTAB_ROW,	"Failed when inserting an access table row.")
#define CONTEXT_DB2UPD_ACCTAB			PKG_NSF_STR+84
	stringtext(CONTEXT_DB2UPD_ACCTAB,	"Failed when updating the access table.")
#define CONTEXT_DB2DEL_FROM_ACCTAB		PKG_NSF_STR+85
	stringtext(CONTEXT_DB2DEL_FROM_ACCTAB,	"Failed when deleting from access table.")
#define CONTEXT_DB2LOAD_SB_PROP			PKG_NSF_STR+86
	stringtext(CONTEXT_DB2LOAD_SB_PROP,	"Failed loading super block property.")
#define CONTEXT_DB2WRITE_SB_PROP		PKG_NSF_STR+87
	stringtext(CONTEXT_DB2WRITE_SB_PROP,	"Failed writing super block property.")
#define CONTEXT_DB2TERM_SCONN			PKG_NSF_STR+88
	stringtext(CONTEXT_DB2TERM_SCONN,	"Failed terminating shared connections.")
#define CONTEXT_DB2FREE_NSUMSET			PKG_NSF_STR+89
	stringtext(CONTEXT_DB2FREE_NSUMSET,	"Failed when DB2 was freeing note summary set.")
#define STR_RM_DEFERREDRRV_THREAD			PKG_NSF_STR+90
	stringtext(STR_RM_DEFERREDRRV_THREAD,	"Recovery Manager Deferred RRV Thread")
#define STR_NSF_COMPACT_DOCUMENT_ERROR_IGNORED	PKG_NSF_STR+91
	stringtext(STR_NSF_COMPACT_DOCUMENT_ERROR_IGNORED,	"Compact of %p ignoring error processing document %x error: '%e'.")
#define STR_NSF_COMPACT_ERROR_IGNORED		PKG_NSF_STR+92
	stringtext(STR_NSF_COMPACT_ERROR_IGNORED,	"Compact of %p ignoring error: '%e'.")
#define CONTEXT_DB2READ_FILE_HEADER		PKG_NSF_STR+93
	stringtext(CONTEXT_DB2READ_FILE_HEADER,	"Failed reading DB2 file header.")
#define CONTEXT_DB2FREE_HSTMT			PKG_NSF_STR+94
	stringtext(CONTEXT_DB2FREE_HSTMT,	"Failed when  DB2 was freeing statement handle.")
#define CONTEXT_DB2_ENABLE_UDF			PKG_NSF_STR+95
	stringtext(CONTEXT_DB2_ENABLE_UDF,	"Failed to enable user defined functions.")
#define CONTEXT_DB2_ADMIN_UDF			PKG_NSF_STR+96
	stringtext(CONTEXT_DB2_ADMIN_UDF,	"Failed while administering DB2 Access DLL.")
#define CONTEXT_DB2GRPSEM				PKG_NSF_STR+97
	stringtext(CONTEXT_DB2GRPSEM,		"Error encountered in group semaphore management." )
#define CONTEXT_DB2_QUERY_VIEWS			PKG_NSF_STR+98
	stringtext(CONTEXT_DB2_QUERY_VIEWS,	"Error encountered in DB2 Query Views" )
#define CONTEXT_DB2RECOVER_SOFT_DEL_LIST PKG_NSF_STR+99
	stringtext(CONTEXT_DB2RECOVER_SOFT_DEL_LIST,	"Failed recovering DB2 soft deleted note list.")
#define CONTEXT_DB2CATALOG				PKG_NSF_STR+100
	stringtext(CONTEXT_DB2CATALOG,		"Error creating DB2 catalog entry" )
#define MSG_DB2NSF_CATALOG_UPGRADED		PKG_NSF_STR+101
	stringtext(MSG_DB2NSF_CATALOG_UPGRADED,"Successfully upgraded schema %s from Version %s to Version %s." )
#define CONTEXT_TABLE_SCHEMA_UPGRADE	PKG_NSF_STR+102
	stringtext(CONTEXT_TABLE_SCHEMA_UPGRADE,		"Error upgrading table schema: " )
#define MSG_DB2NSF_SCHEMA_UPGRADED		PKG_NSF_STR+103
	stringtext(MSG_DB2NSF_SCHEMA_UPGRADED,"Successfully upgraded tables for schema %s from Version %s to Version %s." )
#define CONTEXT_DB2EXTEND_TS			PKG_NSF_STR+104
	stringtext(CONTEXT_DB2EXTEND_TS,     "Failed to extend tablespace." )
#define CONTEXT_DB2GET_NSF_SIZE			PKG_NSF_STR+105
	stringtext(CONTEXT_DB2GET_NSF_SIZE,	"Failed calculating DB2 NSF size.")

#define MSG_DB2_DEFAULT_BANNER          PKG_NSF_STR+106
	stringtext(MSG_DB2_DEFAULT_BANNER,	"%n--default----------------%n")
#define MSG_DB2_HANDLELOCATIONPRINT_TAG	PKG_NSF_STR+107
	stringtext(MSG_DB2_HANDLELOCATIONPRINT_TAG,  "  cliRC= %d,  line=%d,  file=%s%n")
#define MSG_DB2_HANDLEDIAGNOSTICPRINT_TAG		PKG_NSF_STR+108
	stringtext(MSG_DB2_HANDLEDIAGNOSTICPRINT_TAG,"%n%5d  SQLSTATE= %s, Native Error Code= %ld, message:")
#define MSG_DB2_DB2READNOTE1			PKG_NSF_STR+109
	stringtext(MSG_DB2_DB2READNOTE1,	"Error reading note (NoteID: NT%08lx) (Schema: %s)%n")
#define MSG_DB2_DB2WRITENOTE1			PKG_NSF_STR+110
	stringtext(MSG_DB2_DB2WRITENOTE1,	"Error writing note (NoteID: NT%08lx)(schema: %s)%n")
#define MSG_DB2_DB2DELETENOTE1			PKG_NSF_STR+111
	stringtext(MSG_DB2_DB2DELETENOTE1,	"Error deleting note (NoteID: NT%08lx)%n")
#define NSFSTR_LINK_STR1				PKG_NSF_STR+112
	stringtext(NSFSTR_LINK_STR1,"Database")
#define NSFSTR_LINK_STR2				PKG_NSF_STR+113
	stringtext(NSFSTR_LINK_STR2,"View")
#define NSFSTR_LINK_STR3				PKG_NSF_STR+114
	stringtext(NSFSTR_LINK_STR3,"Document")
#define ERR_FOLDER_REORG_LIMIT			PKG_NSF_STR+115
	errortext(ERR_FOLDER_REORG_LIMIT,	"Folder is larger than specified reorg limit.")
#define NSFSTR_INVALID_TIMEDATES_MSG	PKG_NSF_STR+116
	stringtext(NSFSTR_INVALID_TIMEDATES_MSG,	"Fixup: Invalid %s '%z' for Note ID 0x%X in Database %p repaired. New %s is '%z'")
#define NSFSTR_CAPTURED_DATABASE_MSG	PKG_NSF_STR+117
	stringtext(NSFSTR_CAPTURED_DATABASE_MSG,	"Captured database %s to %s")
#define NSFSTR_CANNOT_CAPTURE_DATABASE_MSG	PKG_NSF_STR+118
	stringtext(NSFSTR_CANNOT_CAPTURE_DATABASE_MSG,	"Unable to capture database %s to %s error: %e")
#define NSFSTR_CAPTURE_DATABASE_SIZE_LIMIT_MSG	PKG_NSF_STR+119
	stringtext(NSFSTR_CAPTURE_DATABASE_SIZE_LIMIT_MSG, "Unable to capture database %s, total database capture size limit of %d megabytes would be exceeded.")
#define NSFSTR_CANNOT_CAPTURE_DATABASE_MSG1	PKG_NSF_STR+120
	stringtext(NSFSTR_CANNOT_CAPTURE_DATABASE_MSG1,	"Unable to capture database %s error: %e")
#define NSFSTR_CANNOT_CAPTURE_DATABASE_MSG2	PKG_NSF_STR+121
	stringtext(NSFSTR_CANNOT_CAPTURE_DATABASE_MSG2,	"Unable to capture database %s at this time")
#define NSFSTR_CANNOT_CAPTURE_DATABASE_COUNT	PKG_NSF_STR+122
	stringtext(NSFSTR_CANNOT_CAPTURE_DATABASE_COUNT, "Unable to capture database %s the limit of %d captured databases has been reached.")
#define STR_FREE_TIME_DB_TITLE			PKG_NSF_STR+123
	stringtext(STR_FREE_TIME_DB_TITLE, 	"Local free time info")
#define STR_DAOS_NEAR_MAXDB_SIZE		PKG_NSF_STR+124
	stringtext(STR_DAOS_NEAR_MAXDB_SIZE, 	"Warning, compacting this DAOS enabled database %s back in-line may cause the overall size of the database to exceed the maximum database size.")
#define STR_WARN_MAXDB_SIZE			PKG_NSF_STR+125
	stringtext(STR_WARN_MAXDB_SIZE, 	"Warning: the logical size of %s exceeds 64 gigabytes, a replica or archive may exceed the maximum database size.")
#define STR_DB_OPTION_CHANGE								PKG_NSF_STR+126 
	errortext(STR_DB_OPTION_CHANGE, 	"DBOption Informational: Database option was changed on database %s")
/* there may be some available PKG_NSF_STR offsets above... search for AVAILABLE */

/* this is the *current* max; PKG_NSF_STR has an offset range of 0 - 127 */
#define STR_NSF_STR_MAX					PKG_NSF_STR+127
	stringtext(STR_NSF_STR_MAX,			"This is the last error message in the NSF_STR range")

/* errorContext strings for error logging 0 - 255 */
#define ERR_FORCE_COMPACT			PKG_NSF_STR2+0 
	stringtext(ERR_FORCE_COMPACT,			"Force compaction.")
#define ERR_COMPACT_FILE_COMPLETING			PKG_NSF_STR2+1
	stringtext(ERR_COMPACT_FILE_COMPLETING,	"Compacting %p (%s), restart completing, %s")
#define ERR_COMPACT_FILE_COMPLETED			PKG_NSF_STR2+2
	stringtext(ERR_COMPACT_FILE_COMPLETED,	"Compacted %p (%s), restart completed, %s")
#define ERR_COMPACT_DB_DONE_REPL			PKG_NSF_STR2+3
	stringtext(ERR_COMPACT_DB_DONE_REPL,	"Compacted %p (%s), %luK bytes recovered (%lu%%), %s")
#define ERR_COMPACT_DB_DONE_INC_REPL		PKG_NSF_STR2+4
	stringtext(ERR_COMPACT_DB_DONE_INC_REPL, "Compacted %p (%s), increased by %luK bytes (%lu%%), %s")
#define ERR_COMPACT_DB_DONE_LT1_REPL		 PKG_NSF_STR2+5
	stringtext(ERR_COMPACT_DB_DONE_LT1_REPL, "Compacted %p (%s), %luK bytes recovered (<1%%), %s")
#define ERR_COMPACT_DB_DONE_INC_LT1_REPL	 PKG_NSF_STR2+6
	stringtext(ERR_COMPACT_DB_DONE_INC_LT1_REPL,	"Compacted %p (%s), increased by %luK bytes (<1%%), %s")
#define ERR_COMPACT_FAILURE_REPL			PKG_NSF_STR2+7
	stringtext(ERR_COMPACT_FAILURE_REPL,	 	"Compact of %p failed")
#define ERR_COMPACT_GETTING_SPACE		PKG_NSF_STR2+8
	stringtext(ERR_COMPACT_GETTING_SPACE, 		"Error %1$e getting allocated space for %2$p")

/* this is the *current* max; PKG_NSF_STR2 has an offset range of 0 - 255 */
#define STR_NSF_STR2_MAX					PKG_NSF_STR+255
	stringtext(STR_NSF_STR2_MAX,			"This is the last error message in the NSF_STR2 range")
	
	
			
#endif /*NSF_STR_DEFS*/


#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


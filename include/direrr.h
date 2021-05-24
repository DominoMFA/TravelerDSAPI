
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM                              */
/*                                                                   */
/* L-GHUS-97FH78, L-GHUS-972PJ6                                      */
/*                                                                   */
/* Copyright IBM Corp. 2007, 2013  All Rights Reserved.              */
/*                                                                   */
/* US Government Users Restricted Rights - Use, duplication or       */
/* disclosure restricted by GSA ADP Schedule Contract with           */
/* IBM Corp.                                                         */
/*                                                                   */
/* ***************************************************************** */


#ifndef DIR_ERR_DEFS
#define DIR_ERR_DEFS

/** @file
*	Header file for directory API error codes
*/
#define	ERR_DIR_NOT_YET_IMPLEMENTED				PKG_DIR+1
	errortext(ERR_DIR_NOT_YET_IMPLEMENTED,		"This Directory Independent API function has not yet been implemented")
#define	ERR_DIR_NULL_ENTRY						PKG_DIR+2
	errortext(ERR_DIR_NULL_ENTRY,				"NULL Directory Entry Structure")
#define	ERR_DIR_NULL_CTX						PKG_DIR+3
	errortext(ERR_DIR_NULL_CTX,					"NULL Directory Context Structure")
#define	ERR_DIR_NULL_ARGUMENT					PKG_DIR+4
	errortext(ERR_DIR_NULL_ARGUMENT,			"NULL Directory Argument")
#define	ERR_DIR_ADMINSERVER_NOT_FOUND			PKG_DIR+5
	errortext(ERR_DIR_ADMINSERVER_NOT_FOUND,	"Administration Server for domain could not be determined")
#define ERR_DIR_GENERIC_NOT_FOUND				PKG_DIR+6
	errortext(ERR_DIR_GENERIC_NOT_FOUND,		"The requested directory information could not be found")
#define	ERR_DIR_ENTRY_ALREADY_EXISTS			PKG_DIR+7
	errortext(ERR_DIR_ENTRY_ALREADY_EXISTS,		"Entry already exists in the directory provider")
#define	ERR_DIR_ENTRY_INVALID					PKG_DIR+8
	errortext(ERR_DIR_ENTRY_INVALID,			"Entry provided is invalid")
#define ERR_DIR_SPI_NOT_IMPLEMENTED				PKG_DIR+9
	errortext(ERR_DIR_SPI_NOT_IMPLEMENTED,		"This Dir API function is not implemented by Service Provider")
#define ERR_DIR_INVALID_DIRENTRYID				PKG_DIR+10
	errortext(ERR_DIR_INVALID_DIRENTRYID,		"This DirEntryID has invalid syntax")
#define ERR_DIR_ILLEGAL_OPERATION				PKG_DIR+11
	errortext(ERR_DIR_ILLEGAL_OPERATION,		"This operation is not valid for the Directory API")
#define ERR_DIR_SERVER_NOT_CAPABLE				PKG_DIR+12
	errortext(ERR_DIR_SERVER_NOT_CAPABLE,		"This Domino server is not capable of servicing the directory operation")
#define ERR_DIR_INVALID_ARGUMENT				PKG_DIR+13
	errortext(ERR_DIR_INVALID_ARGUMENT,			"Invalid Dir API argument")
#define ERR_DIR_LDAP_UPDATE						PKG_DIR+14
	errortext(ERR_DIR_LDAP_UPDATE,				"Error updating LDAP directory")
#define ERR_DIR_LDAP_UPDATE_NO_SUCH_ATTRIBUTE			PKG_DIR+15
	errortext(ERR_DIR_LDAP_UPDATE_NO_SUCH_ATTRIBUTE,	"Error updating LDAP directory, no such attribute")
#define ERR_DIR_DIRFLAG_MISMATCH				PKG_DIR+16
	errortext(ERR_DIR_DIRFLAG_MISMATCH,			"Use of the DIR_PRIMARY_ONLY flag is only valid when combined with an empty DirCtx search domain")
#define ERR_DIR_INVALID_FILTER					PKG_DIR+17
	errortext(ERR_DIR_INVALID_FILTER,			"Bad search filter")
#define ERR_DIR_NO_SUCH_ENTRY_INFO_TYPE			PKG_DIR+18
	errortext(ERR_DIR_NO_SUCH_ENTRY_INFO_TYPE,	"Directory server does not have this type of entry information.")
#define ERR_DIR_NULL_CURSOR						PKG_DIR+19
	errortext(ERR_DIR_NULL_CURSOR,				"NULL Directory Cursor Structure")
#define ERR_DIR_SCHEMA_ATTRIBUTETYPEDESCRIPTIONS_INIT			PKG_DIR+20
	errortext(ERR_DIR_SCHEMA_ATTRIBUTETYPEDESCRIPTIONS_INIT,	"Error reading external LDAP server's attributeType descriptions")
#define ERR_DIR_SCHEMA_OBJECTCLASSDESCRIPTIONS_INIT				PKG_DIR+21
	errortext(ERR_DIR_SCHEMA_OBJECTCLASSDESCRIPTIONS_INIT,		"Error reading external LDAP server's objectClass descriptions")
#define ERR_DIR_MUST_PROMOTE					PKG_DIR+22
	errortext(ERR_DIR_MUST_PROMOTE,				"Directory entries in the domain may not be created, they may only be promoted")
#define ERR_DIR_INVALID_CREDENTIALS				PKG_DIR+23
	errortext(ERR_DIR_INVALID_CREDENTIALS,		"LDAP Bind request failed due to invalid credentials: Please verify credentials specified in DA configuration.")
#define ERR_DIR_UNSUPPORTED_DATATYPE			PKG_DIR+24
	errortext(ERR_DIR_UNSUPPORTED_DATATYPE,		"Incompatible Notes item data type.")
#define ERR_DIR_LDAP_UPDATE_NO_SUCH_OBJECT			PKG_DIR+25
	errortext(ERR_DIR_LDAP_UPDATE_NO_SUCH_OBJECT,	"Error updating LDAP directory, no such object")
#define ERR_DIR_LDAP_UPDATE_NON_DOMINO_ATTRIBUTE	PKG_DIR+26
	errortext(ERR_DIR_LDAP_UPDATE_NON_DOMINO_ATTRIBUTE,	"Error updating LDAP entry. Non Domino attributes cannot be modified.")
#define ERR_DIR_ENTRY_NOT_FOUND					PKG_DIR+27
	errortext(ERR_DIR_ENTRY_NOT_FOUND,			"The directory entry could not be found.")
#define ERR_DIR_SIZELIMIT_EXCEEDED				PKG_DIR+28
	errortext(ERR_DIR_SIZELIMIT_EXCEEDED,		"The number of search entries found exceeded the size limit.")
#define ERR_DIR_TIMELIMIT_EXCEEDED				PKG_DIR+29
	errortext(ERR_DIR_TIMELIMIT_EXCEEDED,		"The length of the directory search exceeded the time limit.")
#define ERR_DIR_ATTRIBUTE_NOT_MAPPED			PKG_DIR+30
	errortext(ERR_DIR_ATTRIBUTE_NOT_MAPPED,		"No LDAP attribute mapped from Domino attribute.")

/* SAAS_CODESTREAM-only errors (the string maker doesn't handle #ifdef SAAS_CODESTREAM) */
#define ERR_DIR_MULTIPLE_MATCHES				PKG_DIR+36
	errortext(ERR_DIR_MULTIPLE_MATCHES,			"More than one directory entry match was found.")
#define ERR_DIR_INVALID_BHENTITYID				PKG_DIR+37
	errortext(ERR_DIR_INVALID_BHENTITYID,		"Invalid Entity ID.")
#define ERR_DIR_SILENTFAILOVER					PKG_DIR+38
	errortext(ERR_DIR_SILENTFAILOVER,			"The current LDAP server is not the same as the previously connected LDAP server.  Trigging a DA Failover.")
#define ERR_DIR_CONFIGURATIONMODE				PKG_DIR+39
	errortext(ERR_DIR_CONFIGURATIONMODE,		"TDS is in Configuration Only Mode!  Make sure the Linux password for the TDS dsrdbm01 instance has not expired!")

/* NOTE:  The PKG Codes here were stolen from the NIF2 package. So we only have 0 - 39 available.  */  


#endif

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


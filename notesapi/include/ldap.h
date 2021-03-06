
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
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
/* ***************************************************************** */


#ifndef _LDAP_H
#define _LDAP_H

#ifdef __cplusplus
extern "C" {
#endif


#ifndef GLOBAL_DEFS
#include "global.h"
#endif

#ifndef FILE_DEFS
#include "osfile.h"
#endif

#ifndef NIF_DEFS
#include "nif.h"
#endif

#ifndef DNAME_DEFS
#include "dname.h"
#endif

#ifndef _LBER_H
#include "lber.h"
#endif


/*  Maximum number referalls */

#define LDAP_MAXREFERRALS 		32


#define LDAP_PORT				389
#define LDAP_SSLPORT_DEFAULT 	636
#define LDAP_SPORT				636
#define LDAP_VERSION1			1
#define LDAP_VERSION2			2
#define LDAP_VERSION3			3
#define LDAP_VERSION			LDAP_VERSION3
#define LDAP_LOCAL_HOST			"LocalHost"


#define LDAP_MAX_ATTR_LEN		100
#define LDAP_MAX_URL_LEN		256
#define LDAP_ALL_OPERATIONAL_ATTRS	"+"
#define LDAP_ALL_USER_ATTRS			"*"
#define LDAP_NO_ATTRS				"1.1"

#define LDAP_DEBUG_API			0x0200	 /*   512			1023		*/

/* 
*  Specific LDAP instantiations of BER types we know about
*/

/* general stuff */

#define LDAP_TAG_MESSAGE			0x30L	/* tag is 16 + constructed bit */
#define LDAP_TAG_MSGID				0x02L

/* Possible operations a client can invoke */

#define LDAP_REQ_BIND				0x60L	/* application + constructed */
#define LDAP_REQ_UNBIND				0x42L	/* application + primitive   */
#define LDAP_REQ_SEARCH				0x63L	/* application + constructed */
#define LDAP_REQ_MODIFY				0x66L	/* application + constructed */
#define LDAP_REQ_ADD				0x68L	/* application + constructed */
#define LDAP_REQ_DELETE				0x4aL	/* application + primitive   */
#define LDAP_REQ_MODRDN				0x6cL	/* application + constructed */
#define LDAP_REQ_MODDN				0x6cL	/* application + constructed */
#define LDAP_REQ_COMPARE			0x6eL	/* application + constructed */
#define LDAP_REQ_ABANDON			0x50L	/* application + primitive   */
#define LDAP_REQ_EXTENDED			0x77L	/* application + constructed */


/* Possible result types a server can return */

#define LDAP_RES_BIND				0x61L	/* application + constructed */
#define LDAP_RES_SEARCH_ENTRY		0x64L	/* application + constructed */
#define LDAP_RES_SEARCH_REFERENCE	0x73L	/* application + constructed */
#define LDAP_RES_SEARCH_RESULT		0x65L	/* application + constructed */
#define LDAP_RES_MODIFY				0x67L	/* application + constructed */
#define LDAP_RES_ADD				0x69L	/* application + constructed */
#define LDAP_RES_DELETE				0x6bL	/* application + constructed */
#define LDAP_RES_MODRDN				0x6dL	/* application + constructed */
#define LDAP_RES_MODDN				0x6dL	/* application + constructed */
#define LDAP_RES_COMPARE			0x6fL	/* application + constructed */
#define LDAP_RES_EXTENDED			0x78L	/* application + constructed */
#define LDAP_RES_ANY				(-1L)


/* Authentication methods available */

#define LDAP_AUTH_NONE				0x00L	/* no authentication		  */
#define LDAP_AUTH_SIMPLE			0x80L	/* context specific + primitive   */
#define LDAP_AUTH_KRBV4				0xffL	/* means do both of the following */
#define LDAP_AUTH_KRBV41			0x81L	/* context specific + primitive   */
#define LDAP_AUTH_KRBV42			0x82L	/* context specific + primitive   */
#define LDAP_AUTH_SASL				0xa3L	/* context specific + constructed */

/* sasl methods */
#define LDAP_SASL_SIMPLE			((char *)0) 
#define LDAP_SASL_EXTERNAL			"EXTERNAL"

/* Filter types */

#define LDAP_FILTER_AND				0xa0L	/* context specific + constructed */
#define LDAP_FILTER_OR				0xa1L	/* context specific + constructed */
#define LDAP_FILTER_NOT				0xa2L	/* context specific + constructed */
#define LDAP_FILTER_EQUALITY		0xa3L	/* context specific + constructed */
#define LDAP_FILTER_SUBSTRINGS		0xa4L	/* context specific + constructed */
#define LDAP_FILTER_GE				0xa5L	/* context specific + constructed */
#define LDAP_FILTER_LE				0xa6L	/* context specific + constructed */
#define LDAP_FILTER_PRESENT			0x87L	/* context specific + primitive   */
#define LDAP_FILTER_APPROX			0xa8L	/* context specific + constructed */
#define LDAP_FILTER_EXTENSIBLE		0xa9L	/* context specific + constructed */


/* Substring filter component types */

#define LDAP_SUBSTRING_INITIAL		0x80L	/* context specific */
#define LDAP_SUBSTRING_ANY			0x81L	/* context specific */
#define LDAP_SUBSTRING_FINAL		0x82L	/* context specific */


/* Search scopes */

#define LDAP_SCOPE_BASE				0x00
#define LDAP_SCOPE_ONELEVEL			0x01
#define LDAP_SCOPE_SUBTREE			0x02

/* Optional referral field in an LDAPResult message (LDAPv3 only) */

#define LDAP_TAG_REFERRAL			0xa3	/* context specific + constructed */

/* Optional controls field in an LDAPMessage message (LDAPv3 only) */

#define LDAP_TAG_CONTROLS			0xa0	/* context specific + constructed */

/* Optional serverSaslCreds field in BindResponse message (LDAPv3 only) */

#define LDAP_TAG_SERVER_SASL_CREDS	0x87	/* context specific + primitive */

/* Optional newSuperior field in ModifyDNRequest message (LDAPv3 only) */

#define LDAP_TAG_NEW_SUPERIOR		0x80    /* context specific + primitive */

/* Fields for ExtendedRequest/Responce messages (LDAPv3 only) */

#define LDAP_TAG_REQUEST_NAME		0x80 	/* context specific + primitive */
#define LDAP_TAG_REQUEST_VALUE		0x81 	/* context specific + primitive */
#define LDAP_TAG_RESPONSE_NAME		0x8a 	/* context specific + primitive */
#define LDAP_TAG_RESPONSE			0x8b 	/* context specific + primitive */

/* Fields fro VLV request/response messages */


/* For modifications */
typedef union mod_vals_u
		{
		char			**modv_strvals;
		struct berval	**modv_bvals;
		} mod_vals_u_t;

typedef struct ldapmod 
	{
	int				mod_op;

#define LDAP_MOD_ADD				0x00
#define LDAP_MOD_DELETE				0x01
#define LDAP_MOD_REPLACE			0x02
#define LDAP_MOD_BVALUES			0x80

	char			*mod_type;
	mod_vals_u_t	mod_vals;
#define mod_values	mod_vals.modv_strvals
#define mod_bvalues	mod_vals.modv_bvals

	struct ldapmod	*mod_next;
	} LDAPMod;


/* 
*   Possible error codes that can be returned.
*   Note: When adding additional error codes, please add them to error.cpp too.
*/

#define LDAP_SUCCESS					0x00
#define LDAP_OPERATIONS_ERROR			0x01
#define LDAP_PROTOCOL_ERROR				0x02
#define LDAP_TIMELIMIT_EXCEEDED			0x03
#define LDAP_SIZELIMIT_EXCEEDED			0x04
#define LDAP_COMPARE_FALSE				0x05
#define LDAP_COMPARE_TRUE				0x06
#define LDAP_STRONG_AUTH_NOT_SUPPORTED	0x07
#define LDAP_STRONG_AUTH_REQUIRED		0x08

/*
*   Note: The error code below was never officially supported in LDAPv2, 
*   nor is it supported in LDAPv3.  However, we'll keep it around since 
*   practically all clients which bind v2 expect UMich-style referrals.
*/

#define LDAP_PARTIAL_RESULTS			0x09

/* Error new in LDAPv3 */

#define LDAP_REFERRAL					0x0a
#define LDAP_ADMINLIMIT_EXCEEDED		0x0b    /* for alliance support      */
#define LDAP_UNAVAILABLE_CRITICAL_EXTENSION 0x0c
#define LDAP_CONFIDENTIALITY_REQUIRED	0x0d
#define LDAP_SASL_BIND_IN_PROGRESS		0x0e

/*  Errors that indicate an attribute problem */

#define LDAP_NO_SUCH_ATTRIBUTE			0x10
#define LDAP_UNDEFINED_TYPE				0x11
#define LDAP_INAPPROPRIATE_MATCHING		0x12
#define LDAP_CONSTRAINT_VIOLATION		0x13
#define LDAP_TYPE_OR_VALUE_EXISTS		0x14
#define LDAP_INVALID_SYNTAX				0x15

/*  Errors that indicate a naming problem */

#define LDAP_NO_SUCH_OBJECT				0x20
#define LDAP_ALIAS_PROBLEM				0x21
#define LDAP_INVALID_DN_SYNTAX			0x22
#define LDAP_IS_LEAF					0x23
#define LDAP_ALIAS_DEREF_PROBLEM		0x24

#define NAME_ERROR(n)	((n & 0xf0) == 0x20)

/*  Errors that indicate a security problem */

#define LDAP_INAPPROPRIATE_AUTH			0x30
#define LDAP_INVALID_CREDENTIALS		0x31
#define LDAP_INSUFFICIENT_ACCESS		0x32

/*  Errors that indicate a service problem */

#define LDAP_BUSY						0x33
#define LDAP_UNAVAILABLE				0x34
#define LDAP_UNWILLING_TO_PERFORM		0x35
#define LDAP_LOOP_DETECT				0x36

/*  Errors that indicate an update problem */

#define LDAP_NAMING_VIOLATION			0x40
#define LDAP_OBJECT_CLASS_VIOLATION		0x41
#define LDAP_NOT_ALLOWED_ON_NONLEAF		0x42
#define LDAP_NOT_ALLOWED_ON_RDN			0x43
#define LDAP_ALREADY_EXISTS				0x44
#define LDAP_NO_OBJECT_CLASS_MODS		0x45
#define LDAP_RESULTS_TOO_LARGE			0x46
#define LDAP_AFFECTS_MULTIPLE_DSAS		0x47					/* LDAPv3 */

#define LDAP_OTHER						0x50

/*  Errors that indicate an API problem */

#define LDAP_SERVER_DOWN				0x51
#define LDAP_LOCAL_ERROR				0x52
#define LDAP_ENCODING_ERROR				0x53
#define LDAP_DECODING_ERROR				0x54
#define LDAP_TIMEOUT					0x55
#define LDAP_AUTH_UNKNOWN				0x56
#define LDAP_FILTER_ERROR				0x57
#define LDAP_USER_CANCELLED				0x58
#define LDAP_PARAM_ERROR				0x59
#define LDAP_NO_MEMORY					0x5a
#define LDAP_CONNECT_ERROR				0x5b
#define LDAP_NOT_SUPPORTED				0x5c
#define LDAP_CONTROL_NOT_FOUND			0x5d

#define LDAP_NO_RESULTS_RETURNED		0x5e
#define LDAP_MORE_RESULTS_TO_RETURN		0x5f
#define LDAP_CLIENT_LOOP				0x60
#define LDAP_REFERRAL_LIMIT_EXCEEDED	0x61

/*  Set this to UNWILLING_TO_PERFORM */

#define LDAP_WILDCARD_MINIMUM_ERROR		LDAP_UNWILLING_TO_PERFORM


/* default limit on nesting of referrals */

#define LDAP_DEFAULT_REFHOPLIMIT	5

#define LDAP_SPEC_VERSION			5
#define LDAP_API_VERSION			2000+LDAP_SPEC_VERSION      /* RFC compliant */
#define LDAP_VERSION_MIN			2
#define LDAP_VERSION_MAX			3
#define LDAP_VENDOR_NAME			"HCL Software"
#define LDAP_VENDOR_VERSION			100        /* version 1.0 */
#define LDAP_API_INFO_VERSION		1
#define LDAP_FEATURE_INFO_VERSION   1

#define LDAP_OPT_OFF				((void *)0)
#define LDAP_OPT_ON					((void *)1)

#define LDAP_OPT_API_INFO			0x00
#define LDAP_OPT_DEREF				0x02
#define LDAP_OPT_SIZELIMIT			0x03
#define LDAP_OPT_TIMELIMIT			0x04
#define LDAP_OPT_PROTOCOL_VERSION	0x11
#define LDAP_OPT_SERVER_CONTROLS	0x12
#define LDAP_OPT_CLIENT_CONTROLS	0x13
#define LDAP_OPT_API_FEATURE_INFO	0x15
#define LDAP_OPT_HOST_NAME			0x30
#define LDAP_OPT_RESULT_CODE		0x31
#define LDAP_OPT_ERROR_STRING		0x32
#define LDAP_OPT_MATCHED_DN			0x33

/* used for private or experimental extensions */
#define LDAP_OPT_PRIVATE_EXTENSION_BASE 0x4000  /* to 0x7FFF inclusive */
#define LDAP_OPT_DEBUG_LEVEL		0x5001

/* OID for referrals client control */
#define LDAP_CONTROL_REFERRALS              "1.2.840.113556.1.4.616"

#define LDAP_CONTROL_MANAGEDSAIT			"2.16.840.1.113730.3.4.2"
#define LDAP_CONTROL_SORTRESPONSE			"1.2.840.113556.1.4.474"
#define LDAP_CONTROL_SORTREQUEST			"1.2.840.113556.1.4.473"
/* Flags for referrals client control value */
#define LDAP_CHASE_SUBORDINATE_REFERRALS    0x00000020U
#define LDAP_CHASE_EXTERNAL_REFERRALS       0x00000040U

/* ldap_result() all parameter */
#define LDAP_MSG_ONE	 			0x00
#define LDAP_MSG_ALL				0x01
#define LDAP_MSG_RECEIVED			0x02

/*
*  This structure represents both ldap messages and ldap responses.
*  These are really the same, except in the case of search responses,
*  where a response has multiple messages.
*/


typedef struct ldapmsg LDAPMessage;

#define NULLMSG	((LDAPMessage *) NULL)

#define LDAP_REQST_INPROGRESS	1
#define LDAP_REQST_CHASINGREFS	2
#define LDAP_REQST_NOTCONNECTED	3
#define LDAP_REQST_WRITING	4
#define LDAP_REQST_RESULT_RCVD	20	/* Result for this request has arrived      */

/*
 * structure for holding ldapv3 controls
 */
typedef struct ldapcontrol 
{
    char            *ldctl_oid;
    struct berval   ldctl_value;
    char            ldctl_iscritical;
} LDAPControl;

#define LDAP_DEREF_NEVER	0
#define LDAP_DEREF_SEARCHING	1
#define LDAP_DEREF_FINDING	2
#define LDAP_DEREF_ALWAYS	3
#define LDAP_SSLOPTS_SITECERTS		0x00000001
#define LDAP_SSLOPTS_ACCEPTEXPCERTS	0x00000002
#define LDAP_SSLOPTS_SENDCERTS		0x00000004
#define LDAP_SSLOPTS_SERVERAUTH		0x00000008
#define LDAP_SSLOPTS_PROMPTXCERT	0x00000010
#define LDAP_NO_LIMIT		0
#define LDAP_OPT_REFERRALS		0x00000008
#define LDAP_OPT_RESTART	0x00000009
#define LDAP_OPT_SSL		0x00000010	/* use SSL for client connections */

typedef struct ldap	LDAP;


#define LDAP_URL_ERR_NOTLDAP	1	/* URL doesn't begin with "ldap://" */
#define LDAP_URL_ERR_NODN		2	/* URL has no DN (required) */
#define LDAP_URL_ERR_BADSCOPE	3	/* URL scope string is invalid */
#define LDAP_URL_ERR_MEM		4	/* can't allocate memory space */

/*
*   Time structure
*/

#if defined(UNIX) || defined(MAC)
#include <sys/time.h>
/*	timeval is defined in <winsock2.h>, inc\wsock16.h, and inc\wsock32.h for Windows builds.
	I'm not going to hazard a guess which one of those might be included by your source file,
	so I'm not going to include any here.  (These multiple defines are killing me...)
*/
#elif !defined(W)
typedef struct timeval 
	{
	int	tv_sec;		/* seconds */
	int	tv_usec;	/* and microseconds */
	} timeval;

#endif

typedef struct ldapapiinfo 
{
	int  ldapai_info_version;     /* version of this struct (1) */
	int  ldapai_api_version;      /* revision of API supported */
	int  ldapai_protocol_version; /* highest LDAP version supported */
	char **ldapai_extensions;     /* names of API extensions */
	char *ldapai_vendor_name;     /* name of supplier */
	int  ldapai_vendor_version;   /* supplier-specific version times 100 */
} LDAPAPIInfo;

typedef struct ldap_apifeature_info {
	int	ldapaif_info_version;
	char	*ldapaif_name;
	int	ldapaif_version;
} LDAPAPIFeatureInfo;

typedef struct ldapsortkey {
	char *  attributeType;
	char *  orderingRule;
	int     reverseOrder;
} LDAPsortKey;

/*  Public Function Prototypes */

#define ldap_abandon(ld, msgid)											ND_ldap_abandon((ld), (msgid))
#define ldap_abandon_ext(ld, msgid, serverctrls, clientctrls)			ND_ldap_abandon_ext((ld), (msgid), (serverctrls), (clientctrls))
#define ldap_add(ld, dn, attrs)											ND_ldap_add((ld), (dn), (attrs))
#define ldap_add_s(ld, dn, attrs)										ND_ldap_add_s((ld), (dn), (attrs))
#define ldap_add_ext(ld, dn, attrs, serverctrls, clientctrls, msgidp)	ND_ldap_add_ext((ld), (dn), (attrs), (serverctrls), (clientctrls), (msgidp))
#define ldap_add_ext_s(ld, dn, attrs, serverctrls, clientctrls)			ND_ldap_add_ext_s((ld), (dn), (attrs), (serverctrls), (clientctrls))
#define ldap_bind(ld, who, passwd, authmethod)							ND_ldap_bind((ld), (who), (passwd), (authmethod))
#define ldap_bind_s(ld, who, cred, method)								ND_ldap_bind_s((ld), (who), (cred), (method))
#define ldap_simple_bind(ld, who, passwd)								ND_ldap_simple_bind((ld), (who), (passwd))
#define ldap_simple_bind_s(ld, who, passwd)								ND_ldap_simple_bind_s((ld), (who), (passwd))
#define ldap_sasl_bind(ld, who, mechanism, cred, serverctrls, clientctrls, msgidp) \
			ND_ldap_sasl_bind((ld), (who), (mechanism), (cred), (serverctrls), (clientctrls), (msgidp))
#define ldap_sasl_bind_s(ld, who, mechanism, cred, serverctrls, clientctrls, servercredp) \
			ND_ldap_sasl_bind_s((ld), (who), (mechanism), (cred), (serverctrls), (clientctrls), (servercredp))
#define ldap_compare(ld, dn, attr, value)								ND_ldap_compare((ld), (dn), (attr), (value))
#define ldap_compare_s(ld, dn, attr, value)								ND_ldap_compare_s((ld), (dn), (attr), (value))
#define ldap_compare_ext(ld, dn, attr, bvalue, sctrls, cctrls, msgidp)	ND_ldap_compare_ext((ld), (dn), (attr), (bvalue), (sctrls), (cctrls), (msgidp))
#define ldap_compare_ext_s(ld, dn, attr, bvalue, sctrl, cctrl)			ND_ldap_compare_ext_s((ld), (dn), (attr), (bvalue), (sctrl), (cctrl))
#define ldap_delete(ld, dn)												ND_ldap_delete((ld), (dn))
#define ldap_delete_s(ld, dn)											ND_ldap_delete_s((ld), (dn))
#define ldap_delete_ext(ld, dn, sctrls, cctrls, msgidp)					ND_ldap_delete_ext((ld), (dn), (sctrls), (cctrls), (msgidp))
#define ldap_delete_ext_s(ld, dn, sctrls, cctrls)						ND_ldap_delete_ext_s((ld), (dn), (sctrls), (cctrls))
#define ldap_result2error(ld, r, freeit)								ND_ldap_result2error((ld), (r), (freeit))
#define ldap_err2string(err)											ND_ldap_err2string((err))
#define ldap_perror(ld, s)												ND_ldap_perror((ld), (s))
#define ldap_modify(ld, dn, mods)										ND_ldap_modify((ld), (dn), (mods))
#define ldap_modify_s(ld, dn, mods)										ND_ldap_modify_s((ld), (dn), (mods))
#define ldap_modify_ext(ld, dn, mods, serverctrls, clientctrls, msgid)	ND_ldap_modify_ext((ld), (dn), (mods), (serverctrls), (clientctrls), (msgid))
#define ldap_modify_ext_s(ld, dn, mods, serverctrls, clientctrls)		ND_ldap_modify_ext_s((ld), (dn), (mods), (serverctrls), (clientctrls))
#define ldap_modrdn(ld, dn, newrdn)										ND_ldap_modrdn((ld), (dn), (newrdn))
#define ldap_modrdn_s(ld, dn, newrdn)									ND_ldap_modrdn_s((ld), (dn), (newrdn))
#define ldap_modrdn2(ld, dn, newrdn, deleteoldrdn)						ND_ldap_modrdn2((ld), (dn), (newrdn), (deleteoldrdn))
#define ldap_modrdn2_s(ld, dn, newrdn, deleteoldrdn)					ND_ldap_modrdn2_s((ld), (dn), (newrdn), (deleteoldrdn))
#define ldap_rename(ld, dn, newrdn, newparent, deleteoldrdn, serverctrls, clientctrls, msgid) \
			ND_ldap_rename((ld), (dn), (newrdn), (newparent), (deleteoldrdn), (serverctrls), (clientctrls), (msgid))
#define ldap_rename_s(ld, dn, newrdn, newparent, deleteoldrdn, serverctrls, clientctrls) \
			ND_ldap_rename_s((ld), (dn), (newrdn), (newparent), (deleteoldrdn), (serverctrls), (clientctrls))
#define ldap_open(host, port)											ND_ldap_open((host), (port))
#define ldap_init(defhost, defport)										ND_ldap_init((defhost), (defport))
#define ldap_set_option(ld, optionToSet, optionValue)					ND_ldap_set_option((ld), (optionToSet), (optionValue))
#define ldap_get_option(ld, optionToGet, optionValue)					ND_ldap_get_option((ld), (optionToGet), (optionValue))
#define ldap_first_entry(ld, chain)										ND_ldap_first_entry((ld), (chain))
#define ldap_next_entry(ld, entry)										ND_ldap_next_entry((ld), (entry))
#define ldap_count_entries(ld, chain)									ND_ldap_count_entries((ld), (chain))
#define ldap_get_entry_controls(ld, entry, ctrls)						ND_ldap_get_entry_controls((ld), (entry), (ctrls))
#define ldap_get_dn(ld, entry)											ND_ldap_get_dn((ld), (entry))
#define ldap_dn2ufn(dn)													ND_ldap_dn2ufn((dn))
#define ldap_explode_dn(dn, notypes)									ND_ldap_explode_dn((dn), (notypes))
#define ldap_explode_rdn(rdn, notypes)									ND_ldap_explode_rdn((rdn), (notypes))
#define ldap_first_attribute(ld, entry, ber)							ND_ldap_first_attribute((ld), (entry), (ber))
#define ldap_next_attribute(ld, entry, ber)								ND_ldap_next_attribute((ld), (entry), (ber))
#define ldap_get_values(ld, entry, target)								ND_ldap_get_values((ld), (entry), (target))
#define ldap_get_values_len(ld, entry, target)							ND_ldap_get_values_len((ld), (entry), (target))
#define ldap_count_values(vals)											ND_ldap_count_values((vals))
#define ldap_count_values_len(vals)										ND_ldap_count_values_len((vals))
#define ldap_value_free(vals)											ND_ldap_value_free((vals))
#define ldap_value_free_len(vals)										ND_ldap_value_free_len((vals))
#define ldap_result(ld, msgid, all, timeout, result)					ND_ldap_result((ld), (msgid), (all), (timeout), (result))
#define ldap_msgfree(lm)												ND_ldap_msgfree((lm))
#define ldap_parse_result(ld, result, errcodep, matcheddnp, errmsgp, referralsp, serverctrlsp, freeit) \
			ND_ldap_parse_result((ld), (result), (errcodep), (matcheddnp), (errmsgp), (referralsp), (serverctrlsp), (freeit))
#define ldap_parse_sasl_bind_result(ld, res, servercredp, freeit) \
			ND_ldap_parse_sasl_bind_result((ld), (res), (servercredp), (freeit))
#define ldap_parse_extended_result(ld, res, resultoidp, resultdata, freeit) \
			ND_ldap_parse_extended_result ((ld), (res), (resultoidp), (resultdata), (freeit))
#define ldap_msgtype(lm)												ND_ldap_msgtype((lm))
#define ldap_msgid(lm)													ND_ldap_msgid((lm))
#define ldap_search(ld, base, scope, filter, attrs, attrsonly)			ND_ldap_search((ld), (base), (scope), (filter), (attrs), (attrsonly))
#define ldap_search_s(ld, base, scope, filter, attrs, attrsonly, res)	ND_ldap_search_s((ld), (base), (scope), (filter), (attrs), (attrsonly), (res))
#define ldap_search_st(ld, base, scope, filter, attrs, attrsonly, timeout, res) \
			ND_ldap_search_st((ld), (base), (scope), (filter), (attrs), (attrsonly), (timeout), (res))
#define ldap_search_ext(ld, base, scope, filter, attrs, attrsonly, serverctrls, clientctrls, timeout, sizelimit, msgid) \
			ND_ldap_search_ext((ld), (base), (scope), (filter), (attrs), (attrsonly), (serverctrls), (clientctrls), (timeout), (sizelimit), (msgid))
#define ldap_search_ext_s(ld, base, scope, filter, attrs, attrsonly, serverctrls, clientctrls, timeoutp, sizelimit, res) \
			ND_ldap_search_ext_s((ld), (base), (scope), (filter), (attrs), (attrsonly), (serverctrls), (clientctrls), (timeoutp), (sizelimit), (res))
#define ldap_unbind(ld)													ND_ldap_unbind((ld))
#define ldap_unbind_s(ld)												ND_ldap_unbind_s((ld))
#define ldap_unbind_ext(ld, serverctrls, clientctrls)					ND_ldap_unbind_ext((ld), (serverctrls), (clientctrls))
#define ldap_memfree(ptr)												ND_ldap_memfree((ptr))
#define ldap_control_free(ctrl)											ND_ldap_control_free((ctrl))
#define ldap_controls_free(ctrl)										ND_ldap_controls_free((ctrl))
#define ldap_create_sort_control(ld, keyList, isCritical, ctrlp)		ND_ldap_create_sort_control((ld), (keyList), (isCritical), (ctrlp))
#define ldap_parse_sort_control(ld, ctrls, returnCode, attribute)		ND_ldap_parse_sort_control((ld), (ctrls), (returnCode), (attribute))

#define ldap_extended_operation(ld, exoid, exdata, serverctrls, clientctrls, msgidp) \
			ND_ldap_extended_operation((ld), (exoid), (exdata), (serverctrls), (clientctrls), (msgidp))
#define ldap_extended_operation_s(ld, exoid, exdata, serverctrls, clientctrls, retoidp, retdatap) \
			ND_ldap_extended_operation_s((ld), (exoid), (exdata), (serverctrls), (clientctrls), (retoidp), (retdatap))
#define ldap_first_message(ld, res)										ND_ldap_first_message((ld), (res))
#define ldap_next_message(ld, msg)										ND_ldap_next_message((ld), (msg))
#define ldap_count_messages(ld, res)									ND_ldap_count_messages((ld), (res))
#define ldap_parse_reference(ld, ref, referralsp, serverctrls, freeit)	ND_ldap_parse_reference((ld), (ref), (referralsp), (serverctrls), (freeit))
#define ldap_first_reference(ld, chain)									ND_ldap_first_reference((ld), (chain))
#define ldap_next_reference(ld, chain)									ND_ldap_next_reference((ld), (chain))
#define ldap_count_references(ld, chain)								ND_ldap_count_references((ld), (chain))
int LNPUBLIC ND_ldap_abandon( LDAP *ld, int msgid );
int LNPUBLIC ND_ldap_abandon_ext( LDAP *ld, int msgid, LDAPControl** serverctrls,
								  LDAPControl** clientctrls );

int LNPUBLIC ND_ldap_add( LDAP *ld, const char *dn, LDAPMod **attrs );
int LNPUBLIC ND_ldap_add_s( LDAP *ld, const char *dn, LDAPMod **attrs );
int LNPUBLIC ND_ldap_add_ext( LDAP *ld, const char *dn, LDAPMod **attrs, LDAPControl **serverctrls,
          LDAPControl **clientctrls, int* msgidp );
int LNPUBLIC ND_ldap_add_ext_s( LDAP *ld, const char *dn, LDAPMod **attrs,
								LDAPControl **serverctrls,
								LDAPControl **clientctrls );

int LNPUBLIC ND_ldap_bind( LDAP *ld, const char *who, const char *passwd, int authmethod );
int LNPUBLIC ND_ldap_bind_s( LDAP *ld, const char *who, const char *cred, int method );

int LNPUBLIC ND_ldap_simple_bind( LDAP *ld, const char *who, const char *passwd );
int LNPUBLIC ND_ldap_simple_bind_s( LDAP *ld, const char *who, const char *passwd );

int LNPUBLIC ND_ldap_sasl_bind( LDAP *ld, const char *who, const char *mechanism,
								struct berval *cred, LDAPControl **serverctrls, 
								LDAPControl **clientctrls, int *msgidp );
int LNPUBLIC ND_ldap_sasl_bind_s( LDAP *ld, const char *who, const char *mechanism,
								  struct berval *cred, LDAPControl **serverctrls,
								  LDAPControl **clientctrls, struct berval **servercredp );

int LNPUBLIC ND_ldap_compare( LDAP *ld, const char *dn, const char *attr, const char *value );
int LNPUBLIC ND_ldap_compare_s( LDAP *ld, const char *dn, const char *attr, const char *value );
int LNPUBLIC ND_ldap_compare_ext(LDAP *ld, const char *dn, const char *attr, 
								 const struct berval *bvalue, LDAPControl **sctrls, LDAPControl **cctrls,
								 int *msgidp );
int LNPUBLIC ND_ldap_compare_ext_s(LDAP *ld, const char *dn, const char *attr,
								   const struct berval *bvalue, LDAPControl **sctrl, 
								   LDAPControl **cctrl );

int LNPUBLIC ND_ldap_delete( LDAP *ld, const char *dn );
int LNPUBLIC ND_ldap_delete_s( LDAP *ld, const char *dn );
int LNPUBLIC ND_ldap_delete_ext(LDAP *ld, const char* dn, LDAPControl **sctrls,
								LDAPControl **cctrls, int *msgidp );
int LNPUBLIC ND_ldap_delete_ext_s(LDAP *ld, const char *dn, LDAPControl **sctrls, LDAPControl **cctrls );

int LNPUBLIC ND_ldap_result2error( LDAP *ld, LDAPMessage *r, int freeit );
char *LNPUBLIC ND_ldap_err2string( int err );
void LNPUBLIC ND_ldap_perror( LDAP *ld, const char *s );

int LNPUBLIC ND_ldap_modify( LDAP *ld, const char *dn, LDAPMod **mods );
int LNPUBLIC ND_ldap_modify_s( LDAP *ld, const char *dn, LDAPMod **mods );
int LNPUBLIC ND_ldap_modify_ext( LDAP *ld, const char *dn, LDAPMod **mods,
								 LDAPControl** serverctrls, LDAPControl** clientctrls,
								 int* msgid);
int LNPUBLIC ND_ldap_modify_ext_s( LDAP *ld, const char *dn, LDAPMod **mods,
								   LDAPControl **serverctrls, LDAPControl **clientctrls);

int LNPUBLIC ND_ldap_modrdn( LDAP *ld, const char *dn, const char *newrdn );
int LNPUBLIC ND_ldap_modrdn_s( LDAP *ld, const char *dn, const char *newrdn );
int LNPUBLIC ND_ldap_modrdn2( LDAP *ld, const char *dn, const char *newrdn, 
	int deleteoldrdn );
int LNPUBLIC ND_ldap_modrdn2_s( LDAP *ld, const char *dn, const char *newrdn,
	int deleteoldrdn);

int LNPUBLIC ND_ldap_rename( LDAP *ld, const char *dn, const char *newrdn, const char *newparent, 
	int deleteoldrdn, LDAPControl **serverctrls, LDAPControl** clientctrls, int* msgid);
int LNPUBLIC ND_ldap_rename_s( LDAP *ld, const char *dn, const char *newrdn, const char* newparent,
	int deleteoldrdn, LDAPControl** serverctrls, LDAPControl** clientctrls);

LDAP *LNPUBLIC ND_ldap_open( const char *host, int port );
LDAP *LNPUBLIC ND_ldap_init( const char *defhost, int defport );

LDAP *LNPUBLIC ND_ldap_sslinit( const char *hostname, int portno, int secure, DWORD ssloptions, int sslprotocolver );

/* LDAP Option functions */
int LNPUBLIC ND_ldap_set_option( LDAP *ld, int optionToSet, const void *optionValue );
int LNPUBLIC ND_ldap_get_option( LDAP *ld, int optionToGet, void *optionValue );

LDAPMessage *LNPUBLIC ND_ldap_first_entry( LDAP *ld, LDAPMessage *chain );
LDAPMessage *LNPUBLIC ND_ldap_next_entry( LDAP *ld, LDAPMessage *entry );
int LNPUBLIC ND_ldap_count_entries( LDAP *ld, LDAPMessage *chain );
int LNPUBLIC ND_ldap_get_entry_controls ( LDAP *ld, LDAPMessage *entry, LDAPControl ***ctrls );

char *LNPUBLIC ND_ldap_get_dn( LDAP *ld, LDAPMessage *entry );
char *LNPUBLIC ND_ldap_dn2ufn( const char *dn );
char **LNPUBLIC ND_ldap_explode_dn( const char *dn, int notypes );
char **LNPUBLIC ND_ldap_explode_rdn( const char *rdn, int notypes );

char *LNPUBLIC ND_ldap_first_attribute( LDAP *ld, LDAPMessage *entry, BerElement **ber );
char *LNPUBLIC ND_ldap_next_attribute( LDAP *ld, LDAPMessage *entry, BerElement *ber );

char **LNPUBLIC ND_ldap_get_values( LDAP *ld, LDAPMessage *entry, const char *target );
struct berval **LNPUBLIC ND_ldap_get_values_len( LDAP *ld, LDAPMessage *entry, const char *target );
int LNPUBLIC ND_ldap_count_values( char **vals );
int LNPUBLIC ND_ldap_count_values_len( struct berval **vals );
void LNPUBLIC ND_ldap_value_free( char **vals );
void LNPUBLIC ND_ldap_value_free_len( struct berval **vals );

#if defined(W32) && defined(STRICT) && !defined(UNIX)
/* Suppress "named type definition in parentheses"	*/
#pragma warning(disable:4115)
#endif
int LNPUBLIC ND_ldap_result( LDAP *ld, int msgid, int all,
	struct timeval *timeout, LDAPMessage **result );
int LNPUBLIC ND_ldap_msgfree( LDAPMessage *lm );
int LNPUBLIC ND_ldap_parse_result(LDAP *ld, LDAPMessage *result, int *errcodep, 
								  char **matcheddnp, char **errmsgp, char ***referralsp,
								  LDAPControl ***serverctrlsp, int freeit);
int LNPUBLIC ND_ldap_parse_sasl_bind_result(LDAP *ld, LDAPMessage *res,
				struct berval **servercredp, int freeit);
int LNPUBLIC ND_ldap_parse_extended_result (LDAP *ld, LDAPMessage *res, 
			       							char **resultoidp, struct berval **resultdata,
			       							int freeit);
int LNPUBLIC ND_ldap_msgtype(LDAPMessage *lm);
int LNPUBLIC ND_ldap_msgid(LDAPMessage *lm);

int LNPUBLIC ND_ldap_search( LDAP *ld, const char *base, int scope, const char *filter,
	char **attrs, int attrsonly );
int LNPUBLIC ND_ldap_search_s( LDAP *ld, const char *base, int scope, const char *filter,
	char **attrs, int attrsonly, LDAPMessage **res );
int LNPUBLIC ND_ldap_search_st( LDAP *ld, const char *base, int scope, const char *filter,
    char **attrs, int attrsonly, struct timeval *timeout, LDAPMessage **res );
int LNPUBLIC ND_ldap_search_ext( LDAP *ld, const char *base, int scope, const char *filter,
								char **attrs, int attrsonly, LDAPControl **serverctrls,
								LDAPControl** clientctrls, struct timeval* timeout, int sizelimit,
								int* msgid );
int LNPUBLIC ND_ldap_search_ext_s( LDAP *ld, const char *base, int scope, const char *filter,
								char **attrs, int attrsonly, LDAPControl **serverctrls,
								LDAPControl **clientctrls, struct timeval *timeoutp,
								int sizelimit, LDAPMessage **res );

int LNPUBLIC ND_ldap_unbind( LDAP *ld );
int LNPUBLIC ND_ldap_unbind_s( LDAP *ld );
int LNPUBLIC ND_ldap_unbind_ext( LDAP *ld, LDAPControl **serverctrls, LDAPControl **clientctrls );

void LNPUBLIC ND_ldap_memfree( char *ptr);

void LNPUBLIC ND_ldap_control_free(LDAPControl *ctrl);
void LNPUBLIC ND_ldap_controls_free(LDAPControl **ctrl);
int LNPUBLIC ND_ldap_create_sort_control (
										LDAP *ld,
										LDAPsortKey **keyList,
										char isCritical,
										LDAPControl **ctrlp );
int LNPUBLIC ND_ldap_parse_sort_control(
								LDAP           *ld,
								LDAPControl    **ctrls,
								unsigned int  *returnCode,
								char           **attribute );
int LNPUBLIC ND_ldap_extended_operation(LDAP *ld, const char* exoid, const struct berval* exdata,
								LDAPControl **serverctrls, LDAPControl** clientctrls, int* msgidp);
int LNPUBLIC ND_ldap_extended_operation_s(LDAP *ld, const char* exoid, const struct berval* exdata,
								LDAPControl **serverctrls, LDAPControl** clientctrls,
								char** retoidp, struct berval **retdatap);

LDAPMessage * LNPUBLIC ND_ldap_first_message( LDAP *ld, LDAPMessage *res );
LDAPMessage * LNPUBLIC ND_ldap_next_message( LDAP *ld, LDAPMessage *msg );
int LNPUBLIC ND_ldap_count_messages( LDAP *ld, LDAPMessage *res );

int LNPUBLIC ND_ldap_parse_reference( LDAP *ld, LDAPMessage *ref, 
									char ***referralsp,LDAPControl ***serverctrls, 
									int freeit);
LDAPMessage * LNPUBLIC ND_ldap_first_reference( LDAP *ld, LDAPMessage *chain );
LDAPMessage * LNPUBLIC ND_ldap_next_reference( LDAP *ld, LDAPMessage *chain );
int LNPUBLIC ND_ldap_count_references( LDAP *ld, LDAPMessage *chain );


#ifdef __cplusplus
}
#endif

#endif /* _LDAP_H */

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


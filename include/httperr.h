
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM and/or HCL                   */
/*                                                                   */
/* Notes_V11.0.1, Domino_V11.0.1                                     */
/*                                                                   */
/* Copyright IBM Corp. 2006, 2017  All Rights Reserved.              */
/* (c) Copyright HCL Technologies Ltd. 2020.  All Rights Reserved.  */
/*                                                                   */
/* Note to U.S. Government Users Restricted Rights:                  */
/* Use, duplication or disclosure restricted by GSA ADP Schedule     */
/*                                                                   */
/*                                                                   */
/* ***************************************************************** */

#if ! defined (HTTPERR_H)
#define HTTPERR_H

#define ERR_HTMLAPI_HTMLOPTION				(PKG_HTTP+89)
errortext(ERR_HTMLAPI_HTMLOPTION,			"Error processing HTML option list")
#define ERR_HTMLAPI_NOT_SUPPORTED			(PKG_HTTP+90)
errortext(ERR_HTMLAPI_NOT_SUPPORTED,		"Feature not supported in the HTML API.")
#define ERR_HTMLAPI_REFLIST_FULL			(PKG_HTTP+92)
errortext(ERR_HTMLAPI_REFLIST_FULL,			"HTMLAPI reference list is full")
#define ERR_HTMLAPI_GENERATING_HTML			(PKG_HTTP+93)
errortext(ERR_HTMLAPI_GENERATING_HTML, 		"HTMLAPI Problem converting to HTML")
#define ERR_HTMLAPI_READONLY_PROP			(PKG_HTTP+94)
errortext(ERR_HTMLAPI_READONLY_PROP, 		"HTMLAPI Cannot set a readonly property")
#define ERR_HTMLAPI_INVALID_PROP_TYPE		(PKG_HTTP+95)
errortext(ERR_HTMLAPI_INVALID_PROP_TYPE,	"HTMLAPI Invalid property type")
#define ERR_HTMLAPI_INVALID_ARG				(PKG_HTTP+96)
errortext(ERR_HTMLAPI_INVALID_ARG,			"HTMLAPI Invalid function argument")
#define ERR_HTMLAPI_INIT					(PKG_HTTP+97)
errortext(ERR_HTMLAPI_INIT,					"Unable to initialize HTMLAPI conversion object")
#endif


#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


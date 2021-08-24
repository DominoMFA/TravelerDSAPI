
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/*********************************************************************/
/*                                                                   */
/* Licensed Materials - Property of IBM and/or HCL                   */
/*                                                                   */
/* Notes_V11.0.1, Domino_V11.0.1                                     */
/*                                                                   */
/* Copyright IBM Corp. 2019  All Rights Reserved.                    */
/* (c) Copyright HCL Technologies Ltd. 2020.  All Rights Reserved.  */
/*                                                                   */
/* Note to U.S. Government Users Restricted Rights:                  */
/* Use, duplication or disclosure restricted by GSA ADP Schedule     */
/*                                                                   */
/*                                                                   */
/*********************************************************************/

// Headers placed in sdk/h.nam require IBM copyright to compile...
#ifndef GPSERR_DEFS
#define GPSERR_DEFS

// Mobile GPS return codes

#define ERR_GEOLOCATION_UNAVAILABLE 						PKG_MOBILE_GEOGPS+0
	errortext(ERR_GEOLOCATION_UNAVAILABLE, 					"GPS is currently unavailable")
#define ERR_GEOLOCATION_TIMEOUT 							PKG_MOBILE_GEOGPS+1
	errortext(ERR_GEOLOCATION_TIMEOUT, 						"Unable to obtain GPS location before request timeout")
#define ERR_GEOLOCATION_PERMISSION_DENIED 					PKG_MOBILE_GEOGPS+2
	errortext(ERR_GEOLOCATION_PERMISSION_DENIED, 			"User or application does not have permission to use GPS")
#define ERR_GEOLOCATION_HIGH_ACCURACY_NOT_SUPPORTED 		PKG_MOBILE_GEOGPS+3
	errortext(ERR_GEOLOCATION_HIGH_ACCURACY_NOT_SUPPORTED, 	"Device does not support high accuracy GPS")
#define ERR_GEOLOCATION_LOW_ACCURACY_NOT_SUPPORTED 			PKG_MOBILE_GEOGPS+4
	errortext(ERR_GEOLOCATION_LOW_ACCURACY_NOT_SUPPORTED, 	"Device does not support low accuracy GPS")
#define ERR_GEOLOCATION_HIGH_ACCURACY_DISABLED 				PKG_MOBILE_GEOGPS+5
	errortext(ERR_GEOLOCATION_HIGH_ACCURACY_DISABLED, 		"High accuracy GPS is disabled on the device")
#define ERR_GEOLOCATION_LOW_ACCURACY_DISABLED 				PKG_MOBILE_GEOGPS+6
	errortext(ERR_GEOLOCATION_LOW_ACCURACY_DISABLED, 		"Low accuracy GPS is disabled on the device")

#endif // GPSERR_DEFS

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


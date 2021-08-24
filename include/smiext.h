
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM and/or HCL                   */
/*                                                                   */
/* Notes_V11.0.1, Domino_V11.0.1                                     */
/*                                                                   */
/* Copyright IBM Corp. 1993, 2017  All Rights Reserved.              */
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

/* SMIEXT.H is the public header file for Lotus specific SMI extensions */

#ifndef __SMIEXT_H
#define __SMIEXT_H

/*  Lotus extension flags. */

#define SMI_NO_FLAGS                            0x00000000L

/*  SMI DLL name. */

#ifdef MAC
#define SMIDLL                                  "SMI"
#else
#define SMIDLL                                  "SMI.DLL"
#endif


/*  Lotus extension functions. */

long SMIAPIENTRY SMIAddressAndSend(             long int dwUIParam,
                                                void SMI_FAR * SMI_PTR msg,
                                                long int dwReserved );

/*  Lotus extension SMI functions pointer datatypes. */

typedef long (SMICALLBACK PSMIADDRESSANDSEND)
                                (long int dwUIParam,
                                void SMI_FAR * SMI_PTR msg,
                                long int dwReserved);

#endif  /* __SMIEXT_H */

#ifdef __cplusplus
}
#endif


#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


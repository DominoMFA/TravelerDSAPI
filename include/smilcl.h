
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

/************************************************************************/
/* SMILCL.H includes environment-specific local binding definitions     */
/*                                                                      */
/* Define one of the following symbols before including this file       */
/* (typically in your makefile or on the compiler's command line):      */
/*                                                                      */
/*      VIM_USE_DOS         for DOS                                     */
/*      VIM_USE_MSWIN       for Microsoft Windows                       */
/*      VIM_USE_OS2_16      for 16-bit OS/2                             */
/*      VIM_USE_OS2_32      for 32-bit OS/2 (IBM 32-bit OS/2 2.0 C)     */
/*      VIM_USE_MSWIN_NT    for Microsoft Windows/NT                    */
/*      VIM_USE_MAC         for Macintosh                               */
/*      VIM_USE_UNIX        for Unix                                    */
/*                                                                      */
/************************************************************************/

#ifndef __SMILCL_H
#define __SMILCL_H

#if defined(VIM_USE_MSWIN) || defined(VIM_USE_OS2_16) || defined(VIM_USE_DOS)

#define SMIAPIENTRY far pascal
#define SMICALLBACK SMIAPIENTRY *
#define SMI_FAR far
#define SMI_VOID void
#define SMI_PTR

#elif defined(VIM_USE_OS2_32)

#if defined(__BORLANDC__)

#define SMIAPIENTRY
#define SMICALLBACK SMIAPIENTRY *
#define SMI_FAR
#define SMI_VOID void
#define SMI_PTR

#else  /* !__BORLANDC__ -- assume IBM or equivalent */

#define SMIAPIENTRY _System
#define SMICALLBACK * SMIAPIENTRY
#define SMI_FAR
#define SMI_VOID void
#define SMI_PTR

#endif  /* !__BORLANDC__ */

#elif defined(VIM_USE_OS2_32_16BIT)

#if defined(__BORLANDC__)

#define SMIAPIENTRY _far16 _pascal
#define SMICALLBACK VIMAPIENTRY *
#define SMI_FAR _far16
#define SMI_VOID void
#define SMI_PTR

#else  /* !__BORLANDC__ -- assume IBM or equivalent */

#define SMIAPIENTRY _Far16 _Pascal
#define SMICALLBACK * SMIAPIENTRY
#define SMI_FAR
#define SMI_VOID void
#define SMI_PTR _Seg16

#endif  /* !__BORLANDC__ */

#elif defined(VIM_USE_MSWIN_NT)

#define SMIAPIENTRY __stdcall
#define SMICALLBACK SMIAPIENTRY *
#define SMI_FAR
#define SMI_VOID void
#define SMI_PTR

#elif defined(VIM_USE_MAC) || defined(VIM_USE_UNIX)

#define SMIAPIENTRY
#define SMICALLBACK SMIAPIENTRY *
#define SMI_FAR
#define SMI_VOID void
#define SMI_PTR

#else

#error SMI - Environment Symbol such as VIM_USE_MSWIN was not defined, no environment is set.

#endif

#endif  /* __SMILCL_H */

#ifdef __cplusplus
}
#endif


#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


#if defined(_MSC_VER)
    //  Microsoft 
    #define EXPORT __declspec(dllexport)
    #define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
    //  GCC
    #define EXPORT __attribute__((visibility("default")))
    #define IMPORT
#else
    //  do nothing and hope for the best?
    #define EXPORT
    #define IMPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif

#define MAX_BUF_LEN 512

// Constants for log level
#ifndef CRITICAL_MSG
#define CRITICAL_MSG 256
#define IMPORTANT_MSG 256
#define ERROR_MSG 16
#define NORMAL_MSG 8
#define VERBOSE_MSG 4
#define DEBUG_MSG 2
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <global.h>
#include <addin.h>
#include <dsapi.h>

#include <nsfdb.h>
#include <nsfnote.h>
#include <nsfsearc.h>
#include <osmem.h>
#include <nsferr.h>
#include <osmisc.h>
#include <misc.h>
#include <bsafe.h>
#include <lookup.h>

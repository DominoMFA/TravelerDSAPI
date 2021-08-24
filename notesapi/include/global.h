
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


/*	Global Definitions */

#ifndef GLOBAL_DEFS
#define GLOBAL_DEFS

/* Detect if we have been included after curl.h and if so, error out */
#ifdef __CURL_CURL_H
#error global.h included after curl.h, this is not allowed!
#endif

/*	Define the specific operating system products we run on:
*	Currently defined as:
*
*		- NT =  Microsoft NT operating system.
*		- MAC_68K = Apple Macintosh on Motorola 680x0 processors
*		- MAC_POWERPC = Apple Macintosh on PowerMac 60x processors
*		- SUN = Sun OS (Solaris 1.0) Unix
*		- SOLARIS = Sun Solaris 2.0 Unix
*		- OS400 = i5/OS for IBM iSeries
*		- AIX = IBM AIX Unix
*		- OS390 = IBM OS/390
*
*	Define the operating system API (may be used on multiple operating systems)
*
*		- W =   Microsoft Windows API
*		- W16 = Microsoft 16-bit Windows API
*		- W32 = Microsoft 32-bit Windows API
*		- MIRAGE = Uses UNIX Mirage product which emulates Windows/16 API
*		- UNIX = UNIX API (common to all UNIX platforms)
*		- MAC = Macintosh Toolbox API
*
*	Define OS architecture
*
*		- "PREEMPTIVE" - OS supports preemptive multitasking
*		- "SEMAPHORES" - OS supports semaphores protecting critical regions,
*						 as opposed to simply using Yields as critical
*						 region protection mechanism
*		- "THREADS" - OS supported "threads" of execution that implicitly
*						share DS, allocated data and code.
*		- "SINGLE_INSTANCE_DLL_DS" - DS in DLLs is shared system-wide
*						(as opposed to each process having its own copy)
*		- "LOCAL" - Addressing of "Local" memory (NEAR or FAR)
*		- "NOGUI" - OS has no graphical interface (e.g., NLM or VMS)
*		- "ENABLE_TRANSACTIONS"	- OS supports Transaction Tracking
*		- "UNICODE" - OS API requires UNICODE strings, not single-byte strings
*
*	Define the ways our executables are linked together:
*
*		- "LINKED_WITH_STATIC_DRIVERS"
*					The network,database,ix drivers are statically linked
*					into the base executables (either single executable or
*					single shared library), and are NOT dynamically loaded
*					into memory when configured by the user.
*					If not defined, then the drivers are dynamically loaded
*					into memory when needed via OSLoadLibrary.
*					This symbol is tested to determine whether to load
*					the library or simply call the statically linked driver
*					directly.
*		- "LINKED_UI_TOGETHER"
*					The user interface portion of the client product (nem,
*					desk, view, edit) are statically linked into a single
*					executable, rather than in separate shared library DLLs.
*					This symbol is tested if the various subprograms need
*					to share copies of variables such as "gi" rather than
*					each having their own copy of the same variable of the
*					same name (which would be necessary if each subprogram
*					is in its own DLL).
*		- "LINKED_EVERYTHING_TOGETHER"
*					The user interface portion is statically linked with
*					the back end portion into a gigantic single executable.
*					Used on platforms where import/export shared libraries
*					do not exist.
*		- "RUNTIME_LOAD_LIBRARY_SUPPORTED"
*					TRUE if OSLoadLibrary supports the ability to dynamically
*					load a library at runtime, and return its main entry point.
*					If FALSE, OSLoadLibrary will at least support connecting
*					to statically linked pseudo-libraries within our own
*					executable, but not to customer-written addin DLLs.
*
*	Define the byte ordering scheme:
*
*		- "BIG_ENDIAN_ORDER" - Bytes are ordered MSB to LSB (e.g. 68000)
*		- "LITTLE_ENDIAN_ORDER" - Bytes are ordered LSB to MSB (e.g. 8086, VAX)
*
*	Define the machine limitations:
*
*		- ODS_NEEDED = Machine cannot support byte-aligned references
*						and requires struct padding and aligned read/reads
*		- REQUIRED_ALIGNMENT = Alignment required by processor to store largest data type to avoid a bus trap (usually DWORD)
*		- NATURAL_ALIGNMENT = Natural compiler alignment of the largest data type (usually a pointer)
*		- MEMALLOC_ALIGNMENT = Memory Allocation alignment: same as NATURAL_ALIGNMENT except for OS400 with 64 bit pointers
*		- COMPILER_DWORD_ALIGNMENT = Compiler's alignment of a DWORD within a struct
*		- COMPILER_NUMBER_ALIGNMENT = Compiler's alignment of NUMBER (usually a double)
*										This is the alignment the compiler will use for the "Alignment_do_not_use"
*										field of the ALIGNED_NUMBER union.
*
*	Define the type/capabilities of the compiler we are using.
*	Currently defined as:
*
*		- "MSC" = Microsoft C
*		- "GCC" = Gnu C
*		- "SYMANTEC_C" = Symantec C/C++ running under MPW on the Mac. (No longer supported in V5)
*		- "MWERKS_C" = Metrowerks C/C++ running under MPW on the Mac.
*		- "MR_C" = Apple MrC running under MPW on the Mac. (obsolete)
*		- "PPC_C" = PPC C on the Mac or PowerMac. (obsolete)
*		- "IBM_C" = IBM Cset/2 on OS2 2.0
*		- "WATCOM_C" = WATCOM C/386 in any env, such as OS/2 2 or Netware
*		- "SUN_C" = Sun native C compiler
*		- "HP_C" = HP native C compiler
*		- "XLC_C" = IBM AIX native C compiler (obsolete)
*		- "OS390_C" = IBM MVS/ESA C/C++ compiler
*		- "UW_C" = UnixWare native C compiler
*		- "ZORTECH_CPP" = Zortech C++ compiler for OS/2
*		- "ILEC400" = OS/400 ILE C cross-compiler for AIX
*
*	Define the configuration's official name, used in the undocumented
*		@Platform function for some our templates such as NAMES.NSF.
*
*		- PLATFORM_NAME
*
*	Define some datatypes which are considered standard by all modules:
*
*			BYTE	= unsigned 8 bit integer
*			SBYTE	= signed 8 bit integer
*			WORD	= unsigned 16 bit integer
*			SWORD	= signed 16 bit integer
*			DWORD	= unsigned 32 bit integer
*			LONG	= signed 32 bit integer
*			DWORD64	= unsigned 64 bit integer (on 32 and 64 bit operating systems)
*			LONG64	= signed 64 bit integer (on 32 and 64 bit operating systems)
*			BOOLBYTE= boolean value which occupies exactly 1 byte
*			STATUS	= Notes-specific 16-bit error code and string resource identifier
*			NUMBER	= A platform-independent IEEE-64 floating point number
*			char	= A byte which is part of a LMBCS character string
*
*			BOOL	= boolean value (used in arguments, arbitrary size)
*					(DO NOT USE IN ON-DISK STRUCTURES - MACHINE DEPENDENT SIZE)
*			FLAG	= boolean value, ONLY used in bit fields in structs (arbitrary size)
*					(DO NOT USE IN ON-DISK STRUCTURES - MACHINE DEPENDENT POSITION)
*			short	= signed integer at least 8 bits wide
*					(DO NOT USE IN ON-DISK STRUCTURES - MACHINE DEPENDENT SIZE)
*			int		= signed integer at least 16 bits wide
*					(DO NOT USE IN ON-DISK STRUCTURES - MACHINE DEPENDENT SIZE)
*			long	= signed integer at least 32 bits wide
*					(DO NOT USE IN ON-DISK STRUCTURES - MACHINE DEPENDENT SIZE)
*			NCHAR	= A platform-specific character (1 or 2 bytes depending if UNICODE is enabled)
*					(DO NOT USE IN ON-DISK STRUCTURES - MACHINE DEPENDENT SIZE)
*/

/*
*			PTRP_ULONG = pointer precision(32 bit or 64 bit based on the platform) ULONG integer
*			PTRP_DWORD = pointer precision(32 bit or 64 bit based on the platform) DWORD integer
*			PTRP_UINT = pointer precision(32 bit or 64 bit based on the platform) UINT integer
*			PTRP_INT = pointer precision(32 bit or 64 bit based on the platform) INT integer
*			PTRP_LONG = pointer precision(32 bit or 64 bit based on the platform) LONG integer
*/
#if defined(OS400)	/* This should appear before the OS2 test below, because that section tests for __IBMCPP__,
					    	which our C++ compiler also generates */
	#define PLATFORM_NAME "OS/400"
	#ifndef UNIX
		#define UNIX
	#endif
	#ifndef W32
		#define	W32				/* Compile for Windows 32 API - its emulated */
	#endif
	#ifndef W
		#define	W				/* Compile for Windows 32 API - its emulated */
	#endif
	#if !defined(MIRAGE) && !defined(INTERNOTES)
		#define MIRAGE
	#endif
	#ifndef HANDLE_IS_32BITS
		#define HANDLE_IS_32BITS
	#endif
	#define BIG_ENDIAN_ORDER
	#define PREEMPTIVE
	#define	SEMAPHORES
	#define	SEMALLOC
	#define ODS_NEEDED TRUE
	#define	COMPILER_INT_SIZE 4
	#define REQUIRED_ALIGNMENT 16
	#define NATURAL_ALIGNMENT 16
	#define PTRISNOT32BIT
	#define COMPILER_DWORD_ALIGNMENT 4
	#define COMPILER_NUMBER_ALIGNMENT 8
	#define VIM_USE_UNIX
	#define THREADS
	#ifndef NOGUI
		#define NOGUI
	#endif
	#if defined(__ILEC400__) || defined(__AIXxiCC__) || defined(__AIXxxlC400__)
		#define ILEC400
	#endif
#elif defined(NT) || (defined(W32) && !defined(UNIX))
	#ifndef W32
		#define	W32
	#endif
	#ifndef W
		#define	W
	#endif
	#ifndef NT
		#define	NT
	#endif
#ifdef W64
	#define	PLATFORM_NAME "Windows/64"
#else
	#define	PLATFORM_NAME "Windows/32"
#endif
	#ifdef _MSC_VER
		#define MSC
	#endif
	#if defined(__IBMC__) || defined(__IBMCPP__)
		#define IBM_C
	#endif
	#define THREADS
	#define LITTLE_ENDIAN_ORDER
	#define PREEMPTIVE
	#define	SEMAPHORES
	#define	SEMALLOC
	#ifdef _X86_
		#define ODS_NEEDED FALSE
		/* Suppress "used #pragma pack to change alignment" */
		#pragma warning(disable:4103)
		/* Note: If you change the packing, you must also change inc\globpack.h */
		#pragma pack(1)
		#define REQUIRED_ALIGNMENT 1
		#define COMPILER_DWORD_ALIGNMENT 1
		#define COMPILER_NUMBER_ALIGNMENT 1
	#else
		#define ODS_NEEDED TRUE
		#define COMPILER_DWORD_ALIGNMENT 4
		#ifdef W64
			/* suppress "conversion from '' to '', possible loss of data warning */
			#pragma warning(disable: 4267)  
			/* suppress "conversion from '' to '', of greater size warning */
			#pragma warning(disable: 4306)  
			#define PTRISNOT32BIT
			#define PTRIS64BIT
			#define REQUIRED_ALIGNMENT 8
			#define NATURAL_ALIGNMENT 8
			#define COMPILER_NUMBER_ALIGNMENT 8
		#else
			#define REQUIRED_ALIGNMENT 4
			#define NATURAL_ALIGNMENT 4
			#define COMPILER_NUMBER_ALIGNMENT 4
		#endif
		#ifndef HANDLE_IS_32BITS
 			#define HANDLE_IS_32BITS
		#endif
	#endif
	/* suppress "access-declarations are deprecated; member using-declarations provide a better alternative" warnings */
	#pragma warning(disable: 4516)
	#if (_MSC_VER >= 1600)
		/* suppress "name was marked as #pragma depracted - _CRT_SECURE_NO_WARNINGS should have covered this but some it did not */
		#pragma warning(disable: 4995)
		#pragma warning(disable: 4996)

		/* No checking on iterators in the product */
		#define _HAS_ITERATOR_DEBUGGING 0
	#endif

	#define	COMPILER_INT_SIZE 4
	#define VIM_USE_MSWIN_NT
	#define	OLEW32
	/*	Enable some OLE definitions which are only available for NT 4.0 and
		above.  The programmer must be careful not to use them on other
		Win32 platforms.
	*/
#ifndef _WIN32_WINNT
	/* Keep this in sync with what is in w32prags.h and w64prags.h */
	#if (_MSC_VER >= 1600)
		#define _WIN32_WINNT	0x0501	/* Changed to 0501 so now at XP level */
	#else
		#define _WIN32_WINNT	0x0400
	#endif
#endif
#elif defined(MAC)
	#ifndef THREADID_IS_64BITS
	#define THREADID_IS_64BITS
	#endif

	#if defined(__powerc) || defined(powerc) || defined(__ppc__)
		#ifndef MAC_POWERPC
		#define MAC_POWERPC
		#endif
	#elif defined(__i386__) || defined(__x86_64__) || defined(__arm__) || defined(__arm64__)
		#ifndef MAC_X86
		#define MAC_X86
		#endif
	#else
		#error Undefined Mac processor
	#endif
	#if defined(IOS)
		#define	PLATFORM_NAME "iOS"
	#else
		#if defined(ND64)
			#define	PLATFORM_NAME "Macintosh/64"
		#else
			#define	PLATFORM_NAME "Macintosh"
		#endif
	#endif
	#if defined(__BIG_ENDIAN__)
		#define BIG_ENDIAN_ORDER
	#else
		#define LITTLE_ENDIAN_ORDER
	#endif
	#ifndef HANDLE_IS_32BITS
		#define HANDLE_IS_32BITS
	#endif
	#if defined(ND64)
		#define PTRIS64BIT
		#define PTRISNOT32BIT
		#ifndef LONGIS64BIT
			#define LONGIS64BIT
		#endif
		/* We need this alignment for 64bit pointers */
		#define NATURAL_ALIGNMENT 8
		#define MEMALLOC_ALIGNMENT 8
	#endif
	#define THREADS
	#define PREEMPTIVE
	#define	SEMAPHORES
	#define	SEMALLOC
	#define ODS_NEEDED TRUE
	#define	COMPILER_INT_SIZE 4
	/* For now, use 68k alignment for all Mac platforms */
	#if defined(ND64)
		#define REQUIRED_ALIGNMENT 8
		#define COMPILER_DWORD_ALIGNMENT 4
		#define COMPILER_NUMBER_ALIGNMENT 8
	#elif defined(MAC_X86)
		/* Try native alignment for Intel because ODS does not support 68k alignment with little endian */
		#define REQUIRED_ALIGNMENT 4		/* Intel supports odd-byte addressing, but it can't be used with system headers */
		#define COMPILER_DWORD_ALIGNMENT 4	/* Compiler will pad DWORDs to DWORD boundary if possible */
		#define COMPILER_NUMBER_ALIGNMENT 4
	#elif defined(MAC_POWERPC)
		#define REQUIRED_ALIGNMENT 1		/* PowerPC supports odd-byte addressing if truly required */
		#define COMPILER_DWORD_ALIGNMENT 2	/* Compiler will pad DWORDs to DWORD boundary if possible */
		#define COMPILER_NUMBER_ALIGNMENT 2
	#else
		#define REQUIRED_ALIGNMENT 1		/* 68020 or later CPUs only (not 68000) */
		#define COMPILER_DWORD_ALIGNMENT 2	/* Compiler will pad DWORDs to WORD boundary, because any further alignment is unnecessary */
		#define COMPILER_NUMBER_ALIGNMENT 2
	#endif
	#define VIM_USE_MAC
	/* Tdanalzye is a rudimentary parser, that is failing to correctly parse this long #if #elif statements.
	 * It is re-processing the UNIX section after it has already processed the OS400 section and incorrectly
	 * using a COMPILER_NUMBER_ALIGNMENT of 4.  So for now, add a redundant !OS400, until tdanalzye is fixed.
	 */
#elif defined(UNIX)  && !defined(OS400)
	#ifndef W32
		#define	W32				/* Compile for Windows 32 API - its emulated */
	#endif
	#ifndef W
		#define	W				/* Compile for Windows 16 API - its emulated */
	#endif
	#if !defined(MIRAGE) && !defined(INTERNOTES)
		#define MIRAGE
	#endif

	#if (defined(ODT) || defined(SOLX86) || defined(UNIXWARE) || defined(OSF) || defined(LINUX)) && !defined(ZLINUX)
		#define LITTLE_ENDIAN_ORDER
	#else
		#define BIG_ENDIAN_ORDER
	#endif
	#define PREEMPTIVE
	#define	SEMAPHORES
	#define	SEMALLOC
	/* All 32-Bit UNIX type platforms except Solaris,HPUX, and AIX are 32 bit handle platforms */
	/* All 64-Bit UNIX type platforms are presently 32bit handles, but may be 64bit handles */
	/* This needs to be here so that it is also included in the SDK */
	#if defined(OSF) || defined(AIX64) || defined(SOLARIS64) || defined (LINUX64) || defined(__64BIT__) || defined(NDUNIX64)

		#ifdef ENABLE_64HANDLE
			#ifndef HANDLE_IS_64BITS
				#define HANDLE_IS_64BITS
			#endif
		#else
			#ifndef HANDLE_IS_32BITS
				#define HANDLE_IS_32BITS
			#endif
		#endif
		#define PTRIS64BIT
		#ifndef LONGIS64BIT
			#define LONGIS64BIT
		#endif
		#if defined(LINUX64) && !defined(THREADID_IS_64BITS)
			#define THREADID_IS_64BITS
		#endif
		#define PTRISNOT32BIT
		/* We need this alignment for 64bit pointers */
		#define NATURAL_ALIGNMENT 8
		#define MEMALLOC_ALIGNMENT 8
	#else
		#if !(defined(SOLARIS) || defined(HPUX) || defined(SOLX86) || defined(AIX))
			#ifndef HANDLE_IS_32BITS
			#define HANDLE_IS_32BITS
			#endif
		#endif
	#endif

	#if defined(AIX)
		#if defined(ND64)
			#define	PLATFORM_NAME "AIX/64"
		#else
			#define	PLATFORM_NAME "UNIX"
		#endif
		#define XLC_C
	#elif defined(SUN) || defined(SOLARIS)
		#if defined(ND64)
			#define	PLATFORM_NAME "Solaris/64"
		#else
			#define	PLATFORM_NAME "UNIX"
		#endif
		#define SUN_C
	#elif defined(HPUX)
		#define	PLATFORM_NAME "UNIX"
		#define HP_C
	#elif defined(OS390)
		#define	PLATFORM_NAME "UNIX"
		#define OS390_C
	#elif defined(UNIXWARE)
		#define	PLATFORM_NAME "UNIX"
		#define UW_C
	#elif defined(__osf__)
		#define	PLATFORM_NAME "UNIX"
		#if !defined(OSF)
			#define OSF
		#endif
		#define DEC_C
	#elif defined(ANDROID)
		#define PLATFORM_NAME "Android"
	#elif defined(LINUX)
		#if defined(ND64)
			#define	PLATFORM_NAME "Linux/64"
		#else
			#define	PLATFORM_NAME "UNIX"
		#endif
		#define GCC
	#else
		#define	PLATFORM_NAME "UNIX"
	#endif

	#if (defined(SOLARIS) || defined(AIX) || defined (HPUX) || defined(OS390) || defined(LINUX)) && !defined(DISABLE_THREADS)
		#define THREADS
	#endif
	/*	ODS needed, even for ODT (on x86 machines), because X includes
		don't support having the compiler set for tight packing (-Zp1),
		that is, they assume padding.  With padding enabled, we must use
		ODS even when theoretically unncessary.  Perhaps the X headers
		can be kludged to explicitly pad so that this is unnecessary. */
	#if defined(ODT_LATER)
		#define	COMPILER_INT_SIZE 4
		#define REQUIRED_ALIGNMENT 1
		#define COMPILER_DWORD_ALIGNMENT 2
		#define COMPILER_NUMBER_ALIGNMENT 2
	#else
		#define ODS_NEEDED TRUE
		#define	COMPILER_INT_SIZE 4
		#if defined(ND64) 
			#define REQUIRED_ALIGNMENT 8
		#else
			#define REQUIRED_ALIGNMENT 4
		#endif
		#define COMPILER_DWORD_ALIGNMENT 4
		#if defined(SOLARIS) || defined(HPUX) || defined(OS390) || defined(ZLINUX) || (defined(LINUX86) && defined(LINUX64)) || defined(ANDROID64)
			#define COMPILER_NUMBER_ALIGNMENT 8
		#else
			#define COMPILER_NUMBER_ALIGNMENT 4
		#endif
	#endif
	#define VIM_USE_UNIX

#else
	#error Must specify type of OS ("DOS", "OS2", etc) on C command line!
#endif
#if (defined(SOLARIS) || defined(AIX) || defined(NT)) && defined(Enable_New_SpinLocks)
	#define USE_COND_SLEEP_ON_SPINLOCK 1
#endif


/*	Nullify the certain compiler keywords if not supported by compiler */

#if !defined(MSC) || defined(NT) || defined(MAC)

	#if !defined(MAC)	/* On Mac, "pascal" (lowercase) is a reserved word */
		#ifdef pascal
			#undef pascal
		#endif

		#if defined(_MSC_VER) && _MSC_VER >= 800
			#define pascal __stdcall
		#else
			#define pascal
		#endif
	#endif	/* !defined(MAC) */

	#if defined(MAC)
		#define PASCAL
	#endif

	#ifndef PASCAL
		#define PASCAL
	#endif

	#ifdef cdecl
		#undef cdecl
	#endif

	#define cdecl

	#if !defined(MWERKS_C)	/* In MWERKS_C, "far" is a reserved word, and cannot appear in an #ifdef expression */
		#ifdef far
			#undef far
		#endif
	#endif

	#define far

	#ifndef FAR
		#define FAR
	#endif

	#ifdef near
		#undef near
	#endif

	#define near

	#ifndef NEAR
		#define NEAR
	#endif

	#ifdef huge
		#undef huge
	#endif

	#define huge

#endif	/* !defined(MSC) || defined(NT) || defined(MAC) */

/*	Nullify C keywords that are not supported by some compilers */

#if defined(GCC)
#if !defined(LINUX)  /* These two are already handled with latest GCC headers on LINUX */
	#define volatile
	#define signed
	#define const
#endif
#elif defined(HP_C) && defined(__cplusplus)
	#define signed
#elif defined(SUN_C) && defined(__cplusplus)
	#define signed
#endif


/*	Same goes for NT include files */

#ifdef NT
	#ifndef _WINDEF_
		#ifndef RC_INVOKED
		/*	Save packing around inclusion of Microsoft headers, just to
			protect ourselves against their failure to restore packing
			if they change it.  This may not be needed anymore... */
		#pragma pack(push, WinIncludes)
		/*	Set packing to be 4, to temporarily workaround a bug in wincon.h
			where Microsoft incorrectly assumes natural packing instead of
			setting it explicitly. */
		#pragma pack()
		#endif

		#undef PASCAL
		#undef FAR
		#undef NEAR

		/*	Windows.h defines WINVER, but we seldom include windows.h
			when using other windows headers.
		*/
		#ifndef WINVER
		#define WINVER 0x0500
		#endif

		/*	Determine the processor type as required by the following Windows
			includes */

		#if !defined(_PPC_) && !defined(_ALPHA_) && !defined(_X86_) && !defined(_IA64_) && !defined(_AMD64_) && !defined(_MIPS_) && defined(_M_IX86)
		#define _X86_
		#endif

		#if !defined(_PPC_) && !defined(_ALPHA_) && !defined(_X86_) && !defined(_IA64_) && !defined(_AMD64_) && !defined(_MIPS_) && defined(_M_MRX000)
		#define _MIPS_
		#endif

		#if !defined(_PPC_) && !defined(_ALPHA_) && !defined(_X86_) && !defined(_IA64_) && !defined(_AMD64_) && !defined(_MIPS_) && defined(_M_ALPHA)
		#define _ALPHA_
		#endif

		#if !defined(_PPC_) && !defined(_ALPHA_) && !defined(_X86_) && !defined(_IA64_) && !defined(_AMD64_) && !defined(_MIPS_) && defined(_M_PPC)
		#define _PPC_
		#endif

		#if !defined(_PPC_) && !defined(_ALPHA_) && !defined(_X86_) && !defined(_IA64_) && !defined(_AMD64_) && !defined(_MIPS_) && defined(_M_AMD64)
		#define _AMD64_
		#endif

		#include <stdarg.h>
		#define NOMINMAX
		#include <windef.h>
		#undef NOMINMAX
		#include <winbase.h>
		#include <WinVer.h>

		#ifndef RC_INVOKED
		#pragma pack(pop, WinIncludes)
		#endif
	#endif
#endif

/* MAC needs these windows emulated APIs */
#if defined(MAC)
#ifdef UNICODE
#define WritePrivateProfileString  WritePrivateProfileStringW
#else
#define WritePrivateProfileString  WritePrivateProfileStringA
#endif /* !UNICODE */
#endif

#if defined(UNIX)
	/* Needed for standard types */
	#include <stdint.h>
	#include <stddef.h>
#endif

#ifdef NT


	/* These are pointer-precission integer types, that needs to be used as a place holder for highest precision
	 * so that user can exchange data in highest precision place holder w/o loss of data.
	*/
#ifndef PTRP_TYPES_DEFINED
#define PTRP_TYPES_DEFINED
#if defined(W64) || defined(ND64)
	typedef UINT64 PTRP_UINT;
	typedef UINT64 PTRP_ULONG, PTRP_DWORD;
	typedef INT64 PTRP_INT;
	typedef INT64 PTRP_LONG;
#else
	typedef UINT32 PTRP_UINT;
	typedef UINT32 PTRP_ULONG, PTRP_DWORD;
	typedef INT32 PTRP_INT;
	typedef LONG32 PTRP_LONG;
#endif
#endif

#endif

#include "nadtypes.h"

#if defined(MAC)

#ifndef _WINNT_		/* These are also defined in unix/cham/winnt.h */
typedef char CHAR;
typedef char* PCHAR;
typedef short SHORT;
#endif


#ifdef IOS
#include <CoreFoundation/CoreFoundation.h>
#include <MobileCoreServices/MobileCoreServices.h>
#include <CoreGraphics/CoreGraphics.h>
#include <ImageIO/ImageIO.h>
#include <CoreText/CoreText.h>
#else

#include <Carbon/Carbon.h>
#endif

#endif  /* MAC */


/*	Determine what has been included BEFORE this module */

#if defined(_INC_WINDOWS) /* WIN16 */ || defined(_WINDEF_) /* WIN32 */
	#define WINDOWS_INCLUDED
#endif

#ifdef SEVERITY_NOERROR
	#define OS2DEF_INCLUDED
#endif



/*	Define datatypes which are also defined by other include files */

#ifndef FAR
	#define FAR far
#endif
#ifndef NEAR
	#define NEAR near
#endif
#ifndef PASCAL
	#define PASCAL pascal
#endif

#if !defined(OS2DEF_INCLUDED) && !defined(WINDOWS_INCLUDED)
	#define VOID void
		typedef unsigned char BYTE;
	#if defined(LONGIS64BIT)
		typedef int LONG;
	#else
		typedef long LONG;
	#endif

	#if defined(UNIX) || defined(NT)
		typedef int BOOL;
	#elif defined(MAC)
		/* Objective C defines BOOL as a signed char.  This is not a very good workaround. */
		#ifndef __OBJC__
		typedef int BOOL;
		#endif
	#elif defined(OS2_2x)
		typedef unsigned long BOOL;
	#elif defined(OS2_1x)
		typedef unsigned short BOOL;
	#elif defined(DOSW16)
		typedef int BOOL;
	#else
		typedef short BOOL;
	#endif
	#define LOBYTE(w)       ((BYTE)w)
	#define HIBYTE(w)       (((WORD)w >> 8) & 0xff)
#endif

#ifndef OS2DEF_INCLUDED
	#ifndef _WINDEF_   /* USHORT, ULONG and UCHAR are already defined in windef.h */
		typedef unsigned short USHORT;
	#if defined(LONGIS64BIT)
		typedef unsigned int ULONG;
	#else
		typedef unsigned long ULONG;
	#endif
		typedef unsigned char UCHAR;
	#endif  /* _WINDEF_ */
	#ifndef WINDOWS_INCLUDED	/* This is also defined in windows.h */
		typedef unsigned int UINT;
	#endif
#endif

#if defined(ND64) || defined(NDUNIX64)
	/* this is defined here for all platforms as this is used somewhere in the pack */
	#ifdef HANDLE_IS_64BITS
		#if defined(LONGIS64BIT)
			typedef unsigned long DHANDLE;	/* 64-bit HANDLEs */
		#else
			typedef unsigned long long DHANDLE;	/* 64-bit HANDLEs on Windows */
		#endif
	#else
		typedef unsigned int DHANDLE;	/* 32-bit HANDLEs */
		#ifndef HANDLE_IS_32BITS
			#define HANDLE_IS_32BITS
		#endif
	#endif
	#if !defined(WINDOWS_INCLUDED)
		typedef unsigned int HANDLE, *PHANDLE;            /* for tdanalyzer */
	#endif
#else		/* 32 BIT platforms */
	#if !defined(WINDOWS_INCLUDED)
		#if defined(DOSW16)
			typedef unsigned int DHANDLE;	/* really a short, but compiler is picky */
		#elif defined(HANDLE_IS_32BITS)
			typedef unsigned int DHANDLE;	/* 32-bit HANDLEs */
		#else
			typedef unsigned short DHANDLE;
		#endif
		typedef DHANDLE HANDLE, *PHANDLE;
	#else
		typedef HANDLE DHANDLE;
	#endif
#endif
#ifndef WHANDLE_DEFINED
#define WHANDLE_DEFINED
typedef HANDLE WHANDLE, *PWHANDLE;				/* same as Windows */
#endif


/*	Define datatype which is used to represent a "resource file" */

#ifndef HMODULE
	#define HMODULE		WHANDLE
#endif

#if !defined(WINDOWS_INCLUDED)

/*	These symbols/typedefs ARE COPIED from WINDOWS.H, and are the
	ONLY symbols that should be defined in this section!  (This
	is a help for modules that can't afford to include windows.h
	and want to use a few of these helpful definitions. */

	typedef unsigned short WORD;			/* WORD = unsigned 16 bit integer */
	#if defined(LONGIS64BIT)
		typedef unsigned int DWORD;			/* DWORD = unsigned 32 bit integer */
	#else
		typedef unsigned long DWORD;
	#endif
/*	Windows defines a DHANDLE as unsigned int, but the Mac needs it to be
	unsigned short. In C, both are equivalent, but C++ is pickier */


#if defined(UNIX) || defined(MAC)
#ifndef PTRP_TYPES_DEFINED
#define PTRP_TYPES_DEFINED
#if defined(ND64)
	typedef uint64_t PTRP_UINT;
	typedef uint64_t PTRP_ULONG;
	typedef uint64_t PTRP_DWORD;
	typedef int64_t PTRP_INT;
	typedef int64_t PTRP_LONG;
#else
	typedef unsigned int PTRP_UINT;
	typedef ULONG PTRP_ULONG;
	typedef DWORD PTRP_DWORD;
	typedef int PTRP_INT;
	typedef long PTRP_LONG;
#endif
#endif
#endif

	#define LOWORD(l)       ((WORD)((PTRP_DWORD)(l) & 0xffff))
	#define HIWORD(l)       ((WORD)(((PTRP_DWORD)(l) >> 16) & 0xffff))
	#if defined(ND64)
		#define LODWORD(l)       ((DWORD)((PTRP_DWORD)(l) & 0xffffffff))
		#define HIDWORD(l)       ((DWORD)(((PTRP_DWORD)(l) >> 32) & 0xffffffff))
	#endif

#else	/* if WINDOWS_INCLUDED */

	/*	TEMPORARY: Fix a bug in the standard Windows LOWORD macro (see
		also a copy of it above), which produces a C compiler warning
		regarding loss of segment portion of a pointer. */

	#undef LOWORD
	#define LOWORD(l)       ((WORD)(DWORD)(l))

#endif

/* Define macros for pointer to/from DWORD/LONG conversions */
/* Define macros for HANDLE to/from DWORD/LONG conversions */
#define PTR_TO_PTRP_LONG(p)	((PTRP_LONG)(p))
#define PTR_TO_PTRP_ULONG(p)	((PTRP_ULONG)(p))
#define PTR_TO_DWORD(p) 	((DWORD)(PTRP_DWORD)(p))
#define PTR_TO_DHANDLE(p) 	((DHANDLE)(PTRP_DWORD)(p))
#define PTR_TO_LONG(p) 	    ((LONG)(PTRP_LONG)(p))
#define PTR_TO_ULONG(p) 	    ((ULONG)(PTRP_ULONG)(p))
#define PTR_TO_WORD(p)		((WORD)(PTRP_DWORD)(p))
#define PTR_TO_BOOL(p) 	    ((BOOL)(PTRP_LONG)(p))
#define INT_TO_PTR(i)		((void far *)(PTRP_INT)(i))
#define UINT_TO_PTR(u)		((void far *)(PTRP_UINT)(u))
#define DWORD_TO_PTR(d) 	((void far *)(PTRP_DWORD)(d))
#define LONG_TO_PTR(l) 	    ((void far *)(PTRP_LONG)(l))
#define HANDLE_TO_DWORD(h) 	((DWORD)(PTRP_DWORD)(h))
#define DHANDLE_TO_DWORD(h) 	((DWORD)(PTRP_DWORD)(h))
#define HANDLE_TO_LONG(h) 	((LONG)(PTRP_LONG)(h))
#define DHANDLE_TO_LONG(h) 	((LONG)(PTRP_LONG)(h))
#define DWORD_TO_HANDLE(d) 	((HANDLE)(PTRP_DWORD)(d))
#define DWORD_TO_DHANDLE(d) 	((DHANDLE)(PTRP_DWORD)(d))
#define LONG_TO_HANDLE(l) 	((HANDLE)(PTRP_LONG)(l))
#define LONG_TO_DHANDLE(l) 	((DHANDLE)(PTRP_LONG)(l))
#define SIZET_TO_WORD(l)    ((WORD)(DWORD)(l))
#define SIZET_TO_DWORD(l)   ((DWORD)(l))
#define SIZET_TO_INT(l)		((int)(l))
#define HANDLE_TO_DHANDLE(h) 	((DHANDLE)(PTRP_DWORD)(h))
#define DHANDLE_TO_HANDLE(h) 	((HANDLE)(PTRP_DWORD)(h))
#define UINT_TO_HANDLE(u)	((HANDLE)(PTRP_UINT)(u))
#define UINT_TO_DHANDLE(u)	((DHANDLE)(PTRP_UINT)(u))


/*	Define our Notes-specific global data types */

#define FLAG unsigned					/* FLAG = 1-bit boolean value */
										/* (Unsized, use ONLY in bitfields!) */
#define BOOLBYTE BYTE					/* BOOLBYTE = boolean used in DS */
#define UBYTE BYTE						/* UBYTE = unsigned 8 bit integer */
#define SBYTE signed char				/* SBYTE = signed 8 bit integer */
#define SWORD signed short				/* SWORD = signed 16 bit integer */

typedef DWORD MEMHANDLE;				/* MEMHANDLE = Handle returned by OSMemoryAllocate */
#define NULLMEMHANDLE (MEMHANDLE) 0

typedef WORD STATUS;					/* STATUS = Status code (ERR_xxx) */
										/* High byte is subsystem; */
										/* Low byte is status code */
typedef DWORD FONTID;					/* Font identifier - see FONTID.H */

typedef struct {
	WORD	width;
	WORD	height;
} RECTSIZE;

/* OS400 compiler does not fully implement the C99 spec in regard to large integer literal values */
/* defaulting to long long.  A ll suffix is required, so create macros for defining 64 bit constants */
#if defined(LONGIS64BIT)
	#define ND64_UCONSTANT(x) (x##ul)
	#define ND64_SCONSTANT(x) (x##l)
#else
	#define ND64_UCONSTANT(x) (x##ull)
	#define ND64_SCONSTANT(x) (x##ll)
#endif

/* Define new Data type to handle very large values independent of platform */
/* (but only 32 and 64 bit platforms are valid at this time) */
/* This data type is unsigned so can get the large value possible */
/* The size of this data type varies by platform - on 32bit platforms it is 32bit, on 64bit it is 64bit */

#if defined(ND64) || defined(NDUNIX64)  /* 64bit platform, so need to be able to handle 64bit sizes */
	#if defined(LONGIS64BIT)        /* UNIX 64bit platform long is always 64bit - NOT TRUE!  OS400
					   long is NOT 64 bit. */
		typedef unsigned long NDSIZE_T;	
	#else
		typedef unsigned long long NDSIZE_T;
	#endif
	#define MAXNDSIZE_T (NDSIZE_T) ND64_UCONSTANT(0xffffffffffffffff)
#else					/* 32bit platform, so need to be able to handle 32bit sizes */
	typedef unsigned long NDSIZE_T;
	#define MAXNDSIZE_T (NDSIZE_T) 0xffffffff
#endif

/* Define new Data type NDSIZE_T64 to handle very large values independent of platform */
/* (but only 32 and 64 bit platforms are valid at this time) */
/* This data type is unsigned so can get as large value possible */
/* This data type is always 64bit in size */

#if defined(ND64) || defined(NDUNIX64)  
	#if defined(LONGIS64BIT)
		typedef unsigned long NDSIZE_T64;	
		#ifndef NT /* already defined on Windows */
			typedef unsigned long DWORD64;	
		#endif
		typedef long LONG64;	
	#else
		typedef unsigned long long NDSIZE_T64;
		#ifndef NT
			typedef unsigned long long DWORD64;	
		#endif
		typedef long long LONG64;	
	#endif
	#define MAXNDSIZE_T64 (NDSIZE_T64) ND64_UCONSTANT(0xffffffffffffffff)
#else
#if defined(_MSC_VER) && (_MSC_VER < 1300)
	/* 1300 = MSVC7.NET compiler version, so this won't happen */
	#pragma message("warning: Using unsupported compiler version--no 64Bit data type support")
	typedef unsigned long NDSIZE_T64;
#else
	typedef unsigned long long NDSIZE_T64;
	#ifndef NT
		typedef unsigned long long DWORD64;
	#endif
	typedef long long LONG64;
#endif
	#define MAXNDSIZE_T64 (NDSIZE_T64) ND64_UCONSTANT(0xffffffffffffffff)
#endif


/*	List structure */

typedef struct {
	USHORT ListEntries;			/* list entries following */
								/* now come the list entries */
} LIST;

/*	Range structure */

typedef struct {
	USHORT ListEntries;			/* list entries following */
	USHORT RangeEntries;		/* range entries following */
								/* now come the list entries */
								/* now come the range entries */
} RANGE;


/*	Basic time/date structure --
	The following 2 structures are ONLY intended to be interpreted using
	the "Time" package (see misc.h) conversion routines.  These structures
	are "bit-encoded", and cannot be parsed/interpreted easily. */

typedef struct tagTIMEDATE {
	DWORD Innards[2];
} TIMEDATE;

typedef struct {						/* a timedate range entry */
	TIMEDATE Lower;
	TIMEDATE Upper;
} TIMEDATE_PAIR;

#ifndef OS2_2x	/* OS2 2.x already defines this itself */
#if defined(LONGIS64BIT)
typedef unsigned long NDQWORD;
#else
typedef struct {DWORD Dwords[2];} NDQWORD;
#endif
#endif

/*	Basic floating-point number structure --
	This structure is EXACTLY the same format as a 64-bit IEEE floating
	point number, usually defined in most C compilers as "double". */


typedef double NUMBER;					/* NSF floating type (IEEE 64-bit) */
typedef NUMBER ALIGNED_NUMBER;
#if defined(DOS) || defined(OS2) || defined(MAC)		/* This doesn't work for NT, which has its own FLOAT */
#define FLOAT NUMBER					/* for pre-V3 backward compatibility ONLY */
#define FLOAT_PAIR NUMBER_PAIR			/* for pre-V3 backward compatibility ONLY */
#endif	/* DOS or OS2 */


typedef struct {						/* a float range entry */
	NUMBER Lower;
	NUMBER Upper;
} NUMBER_PAIR;

typedef NUMBER_PAIR ALIGNED_NUMBER_PAIR;

/*	This is the structure that defines a license number.  Do not attempt
	to interpret this structure too exactly, since it may change in future
	releases.  For now, simply treat the entire strucure as a unique ID. */

typedef struct {
	BYTE ID[5];						/* license number */
	BYTE Product;					/* product code, mfgr-specific */
	BYTE Check[2];					/* validity check field, mfgr-specific */
} LICENSEID;

typedef WORD BLOCK;					/* pool block handle */

/*	Define symbols for boolean true/false */

#ifndef TRUE
	#define FALSE 0
	#define TRUE !FALSE
#endif


/*	Define the NULL symbol (ignoring previous ones so that it is always a simple "0"). */

#ifdef NULL
#undef NULL
#endif
#if defined(LINUX64) && defined(__cplusplus)
#define NULL (__null)
#else
#define NULL 0
#endif

/*	Define the Notes calling convention macros. */

#if !defined(OS2)

#define	LNPUBLIC 		FAR PASCAL			/*	Routines called from outside
												a subsystem (includes routines
												in the published API). */
#define LNCALLBACK		FAR PASCAL			/*	Routines specified as callbacks
												within Notes or an API program */
#if defined(OS390) && defined(__XPLINK__)
#define LNCALLBACKPTR   LNCALLBACK FAR * __callback	/*	Macro for defining a pointer to
												a callback routine. __callback added
												for XPLINK DLL to nonXPLINK DLL calls */
#else
#define LNCALLBACKPTR	LNCALLBACK FAR *	/*	Macro for defining a pointer to
												a callback routine */
#endif /* OS390 */
#define	LNVARARGS		FAR cdecl			/*	Routines with a variable number
												of arguments */
#else

/*	OS/2 requires separate macros because the ordering of function
	modifiers for function pointer is different.  This prevents us
	from inserting _System in a uniform place (e.g. a replacemet
	for PASCAL).  See the comments above for their use.*/

#define	LNPUBLIC 		_System
#define LNCALLBACK		_System
#define LNCALLBACKPTR	* _System
#define	LNVARARGS		_System
#endif

/*  Define some obsolete macros that used to be used for OS/2 32-bit
	programs that used the 16-bit Notes API.  These macros are now
	obsolete, but are here to help in backward compatibility for
	these older programs. */

#define NOTESMAIN				LNPUBLIC
#define NOTESAPI				LNPUBLIC
#define NOTESAPICDECL			LNVARARGS
#define NOTESCALLBACK			LNCALLBACK
#define NOTESCALLBACKPTR		LNCALLBACKPTR
#define NOTESPTR				FAR *
#define NOTESBOOL				BOOL

#ifdef NULLHANDLE
#undef NULLHANDLE				/* Override any existing defn (e.g. OS2 2.0) */
#endif
#define NULLHANDLE 0

/*	Define some miscellaneous constants */

#ifndef MAXDWORD64
#define MAXDWORD64 ((DWORD64) 0xffffffffffffffff)
#endif
#ifndef MAXDWORD
#define MAXDWORD ((DWORD) 0xffffffff)
#endif

#ifndef FILESIZE_HIGH_UNIT
#define FILESIZE_HIGH_UNIT ((DWORD64)0x0000000100000000)
#endif

#ifndef MAXWORD
#define MAXWORD ((WORD) 0xffff)
#endif
#ifndef MAXBYTE
#define MAXBYTE ((BYTE) 0xff)
#endif

#ifndef MAXINT
#define MAXINT ((int) (((unsigned int) -1) >> 1))
#endif

#ifndef MININT
#define MININT ((int) (~(unsigned int) MAXINT))
#endif

#ifndef BITS_PER_BYTE
#define	BITS_PER_BYTE 8
#endif


/*	Define a platform-independent method of obtaining the address of
	the "..." variable arguments in a "cdecl" "..." routine.

	void far cdecl SampleRoutine(char *String, WORD LastNamedArgument, ...)
		{
		DWORD temp1;
		WORD temp2;
		VARARG_PTR ap;

		VARARG_START(ap,LastNamedArgument); * Start out just past last named argument
		temp1 = VARARG_GET(ap,DWORD);		* Get next DWORD into temp1 and advance
		temp2 = VARARG_PEEK(ap,WORD);		* Peek at next WORD, but no advance
		temp2 = VARARG_GET(ap,WORD);		* Get next WORD into temp2 and advance
		...
		}
*/
#define VARARG_ROUND_UP(n,unit) ((((n) + (unit) - 1) / (unit)) * (unit))

#if defined(OSF) || (defined(NT) && defined(_AMD64_)) || defined(LINUX) || defined(SOLARIS) || defined(MAC) || defined(AIX64)
#include <stdarg.h>
#define VARARG_PTR	va_list
#elif defined(OS400)
#include <stdarg.h>
typedef struct
	{
	char* vaold;
	char* vanew;
	} VARARG_PTR;
#else
typedef char * VARARG_PTR;
#endif

/*
 The C++ 3.0.1 compiler on X86 has a bug. The  __builtin_va_arg_incr
 doesn't work with short data type.
 It works fine with 'cc'.  So use the definition under 'LITTLE_ENDIAN_ORDER'
*/
#if defined(SOLARIS) && !defined(SOLX86)
#define VARARG_START(_AP,_LASTNAMEDARG) \
					((_AP) = (char *) &__builtin_va_alist)
#elif defined(SUN) && defined(GCC)
#define VARARG_START(_AP,_LASTNAMEDARG) \
					(__builtin_saveregs(), \
					(_AP) = (char *) &(_LASTNAMEDARG) + sizeof(_LASTNAMEDARG))
#elif defined(HPUX)
#ifdef __GNUC__

#define VARARG_START(_AP,_LASTNAMEDARG) \
					(_AP = __builtin_saveregs())
#else
#ifdef __cplusplus
#define VARARG_START(_AP,_LASTNAMEDARG) \
					 (_AP) = (char *) &(_LASTNAMEDARG);

#else
#define VARARG_START(_AP,_LASTNAMEDARG) \
					(__builtin_va_start(_AP,&_LASTNAMEDARG), \
					(_AP) = (char *) &(_LASTNAMEDARG))
#endif
#endif
#elif defined(OSF)  || defined(LINUX) || (defined(NT) && defined(_AMD64_)) || defined(MAC) 
#define VARARG_START(_AP,_LASTNAMEDARG) \
					(va_start(_AP,_LASTNAMEDARG))
#elif defined(OS400)
#define VARARG_START(_AP, _LASTNAMEDARG) \
					( (_AP).vanew = ((char *) &(_LASTNAMEDARG)) + sizeof(_LASTNAMEDARG) )

#elif defined(AIX64)
#define VARARG_START(_AP,_LASTNAMEDARG) \
					((_AP) = (char *) &(_LASTNAMEDARG) + VARARG_ROUND_UP(sizeof(_LASTNAMEDARG),sizeof(long)))
#elif defined(LITTLE_ENDIAN_ORDER) || defined(XLC_C)
#define VARARG_START(_AP,_LASTNAMEDARG) \
					((_AP) = (char *) &(_LASTNAMEDARG) + VARARG_ROUND_UP(sizeof(_LASTNAMEDARG),sizeof(int)))
#else /* BIG_ENDIAN_ORDER */
#define VARARG_START(_AP,_LASTNAMEDARG) \
					((_AP) = (char *) &(_LASTNAMEDARG) + sizeof(_LASTNAMEDARG))
#endif


#if defined(SOLARIS) && !defined(SOLX86)
#define VARARG_GET(_AP,_TYPE) \
					((_TYPE *)__builtin_va_arg_incr((_TYPE *)_AP))[0]
#elif defined(HPUX)
#define TYPE_MASK(_TYPE) (sizeof(_TYPE) > 4 ? 0xFFFFFFF8 : 0xFFFFFFFC)
#define VARARG_GET(_AP,_TYPE) \
					((_AP) = (VARARG_PTR)((long)((_AP) - sizeof(int)) \
										& TYPE_MASK(_TYPE)) , \
					 *(_TYPE *)((_AP) + ((8 - sizeof(_TYPE)) % 4)))
#elif defined(GCC3) || defined(MAC)
/* GCC3 doesn't allow variable arguments shorter than 4 bytes.  If any argument is less than
   4 bytes and is passed through the parameter list (...), it will be converted to 4 bytes */
#define VARARG_GET(_AP,_TYPE) \
					((sizeof(_TYPE) < sizeof(DWORD)) ? ((_TYPE) va_arg(_AP,DWORD)) : (va_arg(_AP,_TYPE)))

#elif defined(OSF) || defined(LINUX) || (defined(NT) && defined(_AMD64_))
#define VARARG_GET(_AP,_TYPE) \
					(va_arg(_AP,_TYPE))
#elif defined(OS400)
#define __VARARG_GET(_AP, _TYPE) \
					( (_AP).vaold = __bndup((_AP).vanew, _TYPE),\
					  (_AP).vanew = (_AP).vaold + sizeof(_TYPE),  \
					  *(_TYPE *)((_AP).vaold ) )
/* The C++ compiler will complain about the conversion of DWORD to a struct datatype. */
/* e.g. typedef struct { WORD foo; WORD bar} FOOBAR    VARARG_GET(ap, FOOBAR);  So eliminate */
/* this unnecessary cast. */
#ifdef __cplusplus
	#define __VARARG_GET1(_AP, _TYPE) \
					( (_AP).vaold = __bndup((_AP).vanew, DWORD),\
					  (_AP).vanew = (_AP).vaold + sizeof(DWORD),  \
					  *(_TYPE *)((_AP).vaold + (sizeof(DWORD)- sizeof(_TYPE))) )
#else
	#define __VARARG_GET1(_AP, _TYPE) __VARARG_GET(_AP, DWORD)
#endif

#define VARARG_GET(_AP,_TYPE) \
					(sizeof(_TYPE) < sizeof(DWORD) ? (_TYPE) __VARARG_GET1(_AP,_TYPE) : __VARARG_GET(_AP,_TYPE))
#elif defined(LITTLE_ENDIAN_ORDER)
#define VARARG_GET(_AP,_TYPE) \
					((_AP) += VARARG_ROUND_UP(sizeof(_TYPE),sizeof(int)), \
					 *(_TYPE *)((_AP) - VARARG_ROUND_UP(sizeof(_TYPE),sizeof(int))))
#elif defined(AIX64)
#define VARARG_GET(_AP,_TYPE) \
					((_AP) += VARARG_ROUND_UP(sizeof(_TYPE),sizeof(long)), \
					 *(_TYPE *)((_AP) - sizeof(_TYPE)))
#else /* BIG_ENDIAN_ORDER */
#define VARARG_GET(_AP,_TYPE) \
					((_AP) += VARARG_ROUND_UP(sizeof(_TYPE),sizeof(int)), \
					 *(_TYPE *)((_AP) - sizeof(_TYPE)))
#endif

#if !defined(MAC) && !defined(LINUX64) && !defined(ZLINUX) && !defined(ANDROID)
/* Don't use VARARG_PEEK on Mac.  It's platform- and compiler-dependent.  Use VARARG_COPY and VARARG_GET instead. */
/* Neither zLinux nor Linux64 can do this peek with va_list, so also need to use VARARG_COPY and VARARG_GET instead. */
#if defined(NT) && defined(_AMD64_)
/*	Just like va_arg from stdargs.h, but without the increment of _AP.offset	*/
#define VARARG_PEEK(_AP,_TYPE)	\
	( (	sizeof(_TYPE) > sizeof(__int64) || (sizeof(_TYPE) & (sizeof(_TYPE) -1) ) != 0 )\
		? **(_TYPE **)( _AP ) : *(_TYPE *)( _AP ) )
#elif defined(OS400)
/* Just like VARARG_GET, but without the increment of _AP.vanew */
#define VARARG_PEEK(_AP,_TYPE)  \
	(sizeof(_TYPE) < sizeof(DWORD) ? (_TYPE)(*(DWORD *)__bndup((_AP).vanew,DWORD)) : (*(_TYPE *)(__bndup((_AP).vanew,_TYPE))))
#elif defined(LITTLE_ENDIAN_ORDER)
#define VARARG_PEEK(_AP,_TYPE) (*(_TYPE *)(_AP))
#elif defined(AIX64)
#define VARARG_PEEK(_AP,_TYPE) (*(_TYPE *)((CHAR*)(_AP) + VARARG_ROUND_UP(sizeof(_TYPE),sizeof(long)) - sizeof(_TYPE)))
#else /* BIG_ENDIAN_ORDER */
#define VARARG_PEEK(_AP,_TYPE) (*(_TYPE *)((CHAR*)(_AP) + VARARG_ROUND_UP(sizeof(_TYPE),sizeof(int)) - sizeof(_TYPE)))
#endif
#endif

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   Platforms that strictly comply to the C standard do not allow passing of
   variable argument lists by reference using '&' and '*' operators because
   the standard states that you may get undetermined results.  However, you
   are allowed to pass a variable argument list without these operators.  On
   zLinux, whenever you pass a variable argument list the contents will always
   be modified upon returning from the function passing it in as a parameter
   (assuming some function below accesses the list).  For these types of
   platforms, define the following macros to just pass the list without using
   the '&' operator.  All platforms can still use a variable argument list
   as a pointer by simply using the VARARG_PTR_P type.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#if defined(ZLINUX) || defined(LINUX64) || (defined(MAC) && defined(__x86_64__)) || (defined(ANDROIDX86) && defined(ANDROID64))
typedef VARARG_PTR VARARG_PTR_P;
#define VARARG_ADDR(_AAP) _AAP
#define VARARG_DEREF(_AAP) _AAP
#define VARARG_COPY __va_copy
#else
typedef VARARG_PTR * VARARG_PTR_P;
#define VARARG_ADDR(_AAP) &_AAP
#define VARARG_DEREF(_AAP) *_AAP
#define VARARG_COPY(dest, src) (dest)=(src)
#endif


#ifdef __cplusplus
extern "C" {
#endif

/*	Define entry point used by all "SDK" utility programs */

STATUS LNPUBLIC NotesMain (int argc, char far *argv[]);

/*	Define routines indirectly (or directly) used by "SDK" utility programs */

STATUS LNPUBLIC NotesInitIni (char far *pConfigFileName);
STATUS LNPUBLIC NotesInit (void);
STATUS LNPUBLIC NotesInitExtended (int argc, char far * far *argv);
void   LNPUBLIC NotesTerm (void);
void LNPUBLIC NotesInitModule (HMODULE far *rethModule, HMODULE far *rethInstance, HMODULE far *rethPrevInstance);
#ifdef NLM
typedef	void EXPORTED_LIBRARY_PROC(void);
STATUS LNPUBLIC NotesLibraryMain (int argc, char far * far *argv, EXPORTED_LIBRARY_PROC initproc);
#endif /* NLM */
STATUS LNPUBLIC NotesInitThread (void);
void LNPUBLIC NotesTermThread (void);

#ifdef __cplusplus
}
#endif

/*	OBSOLETE symbol (used to be used to force bootstrap to be pulled in.
	Now replaced by explicitly linking with notes0.obj and notesai0.obj). */

#define NotesSDKMainModule

/*	Define error code packages */

#include "globerr.h"
#if defined(NT)
#define ADMIN_PLATFORM			/* Defined for Admin Client platforms */
#endif
#if defined (NT) && defined(_X86_)
#define OLE_HTMLOBJ_PLATFORM
#endif


/* strdup has been depracted due to ISO Standards on some platforms and replaced by _strdup */
#ifndef NDSTRDUP  /* We had to define this in multiple places - lsdefine.h */
#if (defined(NT) && (_MSC_VER >= 1600))
#define NDSTRDUP	_strdup
#define NDSTRNICMP	_strnicmp
#define NDSTRNCMP	strncmp
#define NDSTRICMP	_stricmp
#define NDSTRCMPI	_strcmpi
#define NDSTRCMP	strcmp
#define NDSTRLWR	_strlwr
#define NDSTRUPR	_strupr
#define NDCLOSE		_close
#define NDREAD		_read
#define NDWRITE		_write
#define NDMEMICMP	_memicmp
#define NDMEMCMP	_memcmp
#else
#define NDSTRDUP	strdup
#define NDSTRNICMP	strnicmp
#define NDSTRNCMP	strncmp
#define NDSTRICMP	stricmp
#define NDSTRCMPI	strcmpi
#define NDSTRCMP	strcmp
#define NDSTRLWR	strlwr
#define NDSTRUPR	strupr
#define NDCLOSE		close
#define NDREAD		read
#define NDWRITE		write
#define NDMEMICMP	memcmp  /* No memicmp on non-nt platforms ? */
#define NDMEMCMP	memcmp
#endif
#endif

#if !defined (MAC) && defined(ND64CLIENT)

/* 
 * Some GWL defines not available for 64 bit but this is done in winuser.h by first defining
 * them, and then undefining them if 64 bit.  SetWindowLong/GetWindowLong are not to be used 
 * on 64 bit, instead convert all to use SetWindowLongPtr/GetWindowLongPtr which becomes
 * the old apis on 32 bit.
 */

#include <winuser.h>  /* Include winuser.h here so that we can then define the GWL to new GWLP */

#define GWL_USERDATA	GWLP_USERDATA
#define GWL_WNDPROC		GWLP_WNDPROC 
#define GWL_HWNDPARENT	GWLP_HWNDPARENT
#define GWL_HINSTANCE	GWLP_HINSTANCE

#define NDTYPE_HBITMAP	0
#define NDTYPE_HWND		1

DHANDLE ConvertFrom64(void * value, int type);
#define Check64(x,y)	ConvertFrom64((void *)x, NDTYPE_##y);
/*
#define Check64(x,y) { \
	if ((NDSIZE_T64)(x) > MAXDWORD) \
		Panic("Value Exceeds variable!\n"); \
	else \
		return (y)(NDSIZE_T64)x; \
	}
*/
#else
#define Check64(x,y) (x)
#endif



#if defined(ANDROID)
#define __USE_GNU 1
#endif




/* end of global definitions */

#endif	/* GLOBAL_DEFS */

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


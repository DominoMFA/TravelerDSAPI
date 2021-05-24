
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM                              */
/*                                                                   */
/* L-GHUS-97FH78, L-GHUS-972PJ6                                      */
/*                                                                   */
/* Copyright IBM Corp. 1991, 2013  All Rights Reserved.              */
/*                                                                   */
/* US Government Users Restricted Rights - Use, duplication or       */
/* disclosure restricted by GSA ADP Schedule Contract with           */
/* IBM Corp.                                                         */
/*                                                                   */
/* ***************************************************************** */

#ifdef __cplusplus
extern "C" {
#endif


#ifndef MEMORY_DEFS
#define MEMORY_DEFS

/*	Memory manager package */

STATUS LNPUBLIC	OSMemAlloc (WORD BlkType, DWORD dwSize, DHANDLE far *retHandle);
STATUS LNPUBLIC	OSMemFree (DHANDLE Handle);
STATUS LNPUBLIC	OSMemGetSize (DHANDLE Handle, DWORD far *retSize);
STATUS LNPUBLIC	OSMemRealloc (DHANDLE Handle, DWORD NewSize);
void far * LNPUBLIC OSLockObject (DHANDLE Handle);
#define OSLock(blocktype,handle) ((blocktype far *) OSLockObject(handle))
#define OSUnlock(handle) OSUnlockObject(handle)


BOOL LNPUBLIC		OSUnlockObject (DHANDLE Handle);

/*	Define the maximum single-segment memory object size, because OSMem needs
	space for overhead.  Also, Windows has a restriction that it also adds
	another 16 bytes of overhead to the request (arena header), and if that
	causes the object to grow into a "huge" object (more than one segment),
	most caller's will crash because Windows will actually change a segment's
	address when a huge object gets reallocated.  So, for Windows only,
	we restrict the maximum size of a segment to allow for both our overhead
	and the Windows arena header overhead to avoid huge allocations.
	Note that we are subtracting odd numbers from MAXWORD.  This is because
	the result needs to be an even number.  Otherwise, if the requested size
	were MAXONESEGSIZE, memalloc.c would bump the size up over MAXONESEGSIZE
	in order to keep it even.

	NOTE:  Beginning in V3.2, we define MAXONESEGSIZE to be the MIN of
	the required MAXONESEGSIZE on all platforms, because, for example,
	if a server (such as OS/2) allocates an object that IT THINKS is
	MAXONESEGSIZE and then sends it to a client, he'll choke on it. */

#define MAXONESEGSIZE_W16	(MAXWORD-1-128)	/* Tested and failed at -64 */
#define MAXONESEGSIZE_OS21x	(MAXWORD-1-6)	/* Allow space for markers */

#define MAXONESEGSIZE (((MAXONESEGSIZE_W16) > (MAXONESEGSIZE_OS21x)) ? (MAXONESEGSIZE_OS21x) : (MAXONESEGSIZE_W16))
#define MAXHUGESIZE	(MAXDWORD-1-6)

/*	MEMHANDLE-based (not "DHANDLE") memory allocation package */

STATUS LNPUBLIC OSMemoryAllocate (DWORD dwtype, DWORD size, MEMHANDLE *rethandle);
STATUS LNPUBLIC OSMemoryReallocate (MEMHANDLE handle, DWORD size);
void LNPUBLIC OSMemoryFree (MEMHANDLE handle);
DWORD LNPUBLIC OSMemoryGetSize (MEMHANDLE handle);
void far * LNPUBLIC OSMemoryLock (MEMHANDLE handle);
BOOL LNPUBLIC OSMemoryUnlock (MEMHANDLE handle);

#endif

#ifdef __cplusplus
}
#endif



#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


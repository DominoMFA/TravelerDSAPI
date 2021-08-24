
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM and/or HCL                   */
/*                                                                   */
/* Notes_V11.0.1, Domino_V11.0.1                                     */
/*                                                                   */
/* Copyright IBM Corp. 1989, 2017  All Rights Reserved.              */
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

#ifndef POOL_DEFS
#define POOL_DEFS


/*	A datatype which identifies a block within a segment */

typedef DWORD DBLOCK;				/* dpool block handle */

#define NULLBLOCK (BLOCK) 0
#define NULLDBLOCK (DBLOCK) 0


/*	A structure containing a pool handle and block offset */

typedef struct						/* Pointer to any block in any pool */
	{
	DHANDLE	pool;					/* pool handle */
	BLOCK	block;					/* block handle */
	} BLOCKID;

typedef struct						/* Pointer to any block in any pool */
	{
	DHANDLE	pool;					/* pool handle */
	DBLOCK	block;					/* block handle */
	} DBLOCKID;

#define ISNULLBLOCKID(x) (((x).pool==NULLHANDLE)&&((x).block==NULLBLOCK))

/*	Macro functions */


#define	OSLockBlock(type,blockid) \
	((type far *)(OSLock(char,(blockid).pool) + (blockid).block))

#define	OSUnlockBlock(blockid) \
	OSUnlockObject((blockid).pool)

#define OSSwitchBlock(ptr,thisid,nextid) \
		{ \
		if ((thisid).pool != (nextid).pool) \
			{ \
			if ((thisid).pool != NULLHANDLE) \
				OSUnlockBlock((thisid)); \
			ptr = OSLockBlock(void,(nextid)); \
			} \
		else \
			{ \
			register char **pptr = (char **) &(ptr); \
			*pptr = *pptr + (LONG)((nextid).block - (thisid).block); \
			} \
		(thisid) = (nextid); \
		}


#endif

#ifdef __cplusplus
}
#endif


#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


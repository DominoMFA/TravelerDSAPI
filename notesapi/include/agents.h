
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM and/or HCL                   */
/*                                                                   */
/* Notes_V11.0.1, Domino_V11.0.1                                     */
/*                                                                   */
/* Copyright IBM Corp. 1995, 2017  All Rights Reserved.              */
/* (c) Copyright HCL Technologies Ltd. 2020.  All Rights Reserved.  */
/*                                                                   */
/* Note to U.S. Government Users Restricted Rights:                  */
/* Use, duplication or disclosure restricted by GSA ADP Schedule     */
/*                                                                   */
/*                                                                   */
/* ***************************************************************** */

#ifndef AGENTS_DEFS
#define AGENTS_DEFS

#ifndef NAME_DEFS
#include "names.h"
#endif

#ifndef	LOG_DEFS
#include "log.h"
#endif


/*	API to execute agents */

#ifdef __cplusplus
extern "C" {
#endif

typedef void far *HAGENT;
typedef void far *HAGENTCTX;
//typedef DHANDLE HAGENT;
//typedef DHANDLE HAGENTCTX;

STATUS	LNPUBLIC AgentOpen (DHANDLE hDB, NOTEID AgentNoteID, HAGENT far *rethAgent);
void	LNPUBLIC AgentClose (HAGENT hAgent);

/* Use this flag to tell the run context that when it runs an
	agent, you want it to check the privileges of the signer of
	that agent and apply them. For example, if the signer of the
	agent has "restricted" agent privileges, then the agent will
	be restricted. If you don't set this flag, all agents run as
	unrestricted.

	List of security checks enabled by this flag:
		Restricted/unrestricted agent
		Can create databases
		Is agent targeted to this machine
		Is user allowed to access this machine
		Can user run personal agents
*/

#define AGENT_SECURITY_OFF	0x00L		/* CreateRunContext */
#define AGENT_SECURITY_ON	0x01L		/* CreateRunContext */
#define AGENT_REOPEN_DB		0x10L		/* AgentRun */

STATUS	LNPUBLIC AgentCreateRunContext (HAGENT hAgent,
										 void far * pReserved,
										 DWORD dwFlags,
										 HAGENTCTX far *rethContext);
STATUS LNPUBLIC AgentSetDocumentContext(HAGENTCTX hAgentCtx, NOTEHANDLE hNote);
/* allow api users to set time execution limit. if not set, default is 0 which means no limit */
STATUS LNPUBLIC AgentSetTimeExecutionLimit(HAGENTCTX hAgentCtx,
                                           DWORD timeLimit);

/* allow api users to find out if the agent is enabled */
BOOL LNPUBLIC AgentIsEnabled(HAGENT hAgent);

/* Definitions for stdout redirection types. This specifies where
	output from the LotusScript "print" statement will go */

#define AGENT_REDIR_NONE		0		/* goes to the bit bucket */
#define AGENT_REDIR_LOG			1		/* goes to the Notes log (default) */
#define AGENT_REDIR_MEMORY		2		/* goes to a memory buffer, cleared each AgentRun */
#define AGENT_REDIR_MEMAPPEND	3		/* goes to buffer, append mode for each agent */

STATUS 	LNPUBLIC AgentRedirectStdout(HAGENTCTX hAgentCtx, WORD redirType);
void 	LNPUBLIC AgentQueryStdoutBuffer(HAGENTCTX hAgentCtx, DHANDLE FAR * retHdl, DWORD FAR * retSize);
void	LNPUBLIC AgentDestroyRunContext (HAGENTCTX hAgentCtx);
STATUS	LNPUBLIC AgentDelete (HAGENT hAgent); /* delete agent */



/* If AGENT_REOPEN_DB is set, the AgentRun call will reopen
	the agent's database with the privileges of the signer of
	the agent. If the flag is not set, the agent's "context"
	database will be open with the privileges of the current
	user (meaning, the current Notes id, or the current Domino
	web user). */

STATUS	LNPUBLIC AgentRun (HAGENT hAgent,
							HAGENTCTX hAgentCtx,
						    DHANDLE hSelection,
							DWORD dwFlags);
STATUS LNPUBLIC AgentLSTextFormat( DHANDLE hSrc, DHANDLE * hDest, DHANDLE * hErrs, DWORD dwFlags, DHANDLE * phData );

#define MAXIMUM_ID_NAME_LENGTH 40
typedef struct {
	DWORD Length;
	char  szNameOfContextClass[MAXIMUM_ID_NAME_LENGTH + 1];
		}SCRIPTCONTEXTDESCR;


#ifdef __cplusplus
}
#endif

#endif /* AGENTS_DEFS */


#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


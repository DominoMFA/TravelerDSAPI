
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

#ifndef MAILSERV_DEFS
#define MAILSERV_DEFS

/* Mail service package definitions */

#ifndef DARRAY_DEFS
#include "darray.h"							/* Dynamic array definitions */
#endif

#ifndef POOL_DEFS
#include "pool.h"							/* BLOCK definition */
#endif

#ifndef NSF_DATA_DEFS
#include "nsfdata.h"						/* DBHANDLE definition */
#endif

#ifndef NLS_H
#include "nls.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Mail delivery priorities.  Note: order is assumed. */

#define DELIVERY_PRIORITY_LOW 		0
#define DELIVERY_PRIORITY_NORMAL 	1
#define DELIVERY_PRIORITY_HIGH 		2

/* Mail delivery report requests. Note: order is assumed. */

#define DELIVERY_REPORT_NONE 				0	
#define DELIVERY_REPORT_BASIC				1
#define DELIVERY_REPORT_CONFIRMED			2
#define DELIVERY_REPORT_TRACE				3
#define DELIVERY_REPORT_TRACE_NO_DELIVER	4
#define DELIVERY_REPORT_CONFIRM_NO_DELIVER 	5

/* Mail delivery time constants. */

#define DELIVERY_HOUR 		  3600
#define DELIVERY_MINUTE 	  60
#define DELIVERY_MESSAGE_SIZE 1024

/* Message types - Returned by MailGetMessageType. Note: order is assumed. */

#define MAIL_MESSAGE_UNKNOWN			0
#define MAIL_MESSAGE_MEMO				1
#define MAIL_MESSAGE_DELIVERYREPORT		2
#define MAIL_MESSAGE_NONDELIVERYREPORT	3
#define MAIL_MESSAGE_RETURNRECEIPT		4
#define MAIL_MESSAGE_PHONEMESSAGE		5
#define MAIL_MESSAGE_TRACEREPORT		6
#define MAIL_MESSAGE_NOTICE				7
#define MAIL_MESSAGE_QUOTAREPORT		8
#define MAIL_MESSAGE_RECALLREQUEST		9
#define MAIL_MESSAGE_RECALLREPORT		10

	/* MailFindNextHopToRecipientExt Flags */
#define MAIL_LOOKUP_NONUNIQUE_CHECK_R4		0x00000001
#define MAIL_LOOKUP_NODIRCAT				0x00000002

/* Address file functions */

STATUS LNPUBLIC	 MailGetDomainName(char far *Domain);

STATUS LNPUBLIC	 MailLookupAddress(char far *UserName, 
								char far *MailAddress);
STATUS LNPUBLIC	 MailLookupUser(char far *UserName, 
								char far *FullName, 
								char far *MailServerName, char far *MailFileName, 
								char far *MailAddress, char far *ShortName);


/* Message mailing functions */

STATUS LNPUBLIC	 MailGetMessageItem (DHANDLE hMessage, WORD ItemCode,
								char far *retString, WORD StringSize, WORD far *retStringLength);

STATUS LNPUBLIC	 MailGetMessageItemHandle (DHANDLE hMessage, WORD ItemCode,
								BLOCKID far *retbhValue, WORD far *retValueType, DWORD far *retValueLength);

STATUS LNPUBLIC	 MailGetMessageItemTimeDate (DHANDLE hMessage, WORD ItemCode,
								TIMEDATE far *retTimeDate);

STATUS LNPUBLIC	 MailCreateMessage (DBHANDLE hFile, DHANDLE far *rethMessage);

STATUS LNPUBLIC	 MailAddHeaderItem (DHANDLE hMessage, WORD ItemCode,
								const void far *Value, WORD ValueLength);

STATUS LNPUBLIC	 MailAddHeaderItemByHandle (DHANDLE hMessage, WORD ItemCode,
								DHANDLE hValue, WORD ValueLength,
								WORD ItemFlags);

STATUS LNPUBLIC	 MailReplaceHeaderItem (DHANDLE hMessage, WORD ItemCode,
								const void far *Value, WORD ValueLength);

STATUS LNPUBLIC	 MailCreateBodyItem (DHANDLE far *rethBodyItem, DWORD far *retBodyLength);

STATUS LNPUBLIC	 MailAppendBodyItemLine (DHANDLE hBodyItem, DWORD far *BodyLength,
								char far *Text, WORD TextLength);
STATUS LNPUBLIC	 MailAddBodyItemExt(DHANDLE hMessage, DHANDLE hBodyItem, 
									DWORD BodyLength, NLS_PINFO pInfo);

STATUS LNPUBLIC	 MailAddRecipientsItem (DHANDLE hMessage,
								DHANDLE hRecipientsItem, WORD RecipientsLength);

STATUS LNPUBLIC	 MailTransferMessageLocal (DHANDLE hMessage);


BOOL LNPUBLIC	 MailIsNonDeliveryReport (DHANDLE hMessage);
BOOL LNPUBLIC	 MailIsNotToBeHeld (DHANDLE hMessage);
WORD LNPUBLIC	 MailGetMessageType (DHANDLE hMessage);

STATUS LNPUBLIC	 MailCloseMessage (DHANDLE hMessage);
STATUS LNPUBLIC	 MailExpandNames(DHANDLE hWorkList,
								WORD WorkListSize,
								DHANDLE far *hOutputList,
								WORD far *OutputListSize,
								BOOL UseExpanded,
								DHANDLE hRecipsExpanded);

STATUS LNVARARGS MailLogEvent (WORD Flags, STATUS StringID, 
							HMODULE hModule, STATUS AdditionalErrorCode, ...);
							
STATUS LNVARARGS MailLogEventText (WORD Flags, char *String, 
							HMODULE hModule, STATUS AdditionalErrorCode, ...);


/* Mail event logging flags */							
#define MAIL_LOG_TO_MISCEVENTS	0x0001	/* Log message to Miscellaneuos Events view */
#define MAIL_LOG_TO_MAILEVENTS	0x0002	/* Log message to Mail Events view */
#define MAIL_LOG_TO_EVENTS_ONLY 0x0004	/* Don't log messages to console */
#define MAIL_LOG_FORMATTED_TEXT 0x0008	/* Text already formatted */
#define MAIL_LOG_TO_BOTH		(MAIL_LOG_TO_MAILEVENTS | MAIL_LOG_TO_MISCEVENTS)
#define MAIL_LOG_NOT_TO_DDM		0x0010	/* Do not log to DDM */
							

/* Message attachment handling functions */

BOOL LNPUBLIC	 MailGetMessageAttachmentInfo (DHANDLE hMessage, 
								WORD Num, BLOCKID far *bhItem,
								char far *FileName, DWORD far *FileSize,
								WORD far *FileAttributes, WORD far *FileHostType,
								TIMEDATE far *FileCreated, TIMEDATE far *FileModified);

STATUS LNPUBLIC	 MailExtractMessageAttachment (DHANDLE hMessage, 
								BLOCKID bhItem, char far *FileName);

STATUS LNPUBLIC	 MailAddMessageAttachment (DHANDLE hMessage, 
								char far *FileName, char far *OriginalFileName);


/* Message file functions */

STATUS LNPUBLIC	 MailOpenMessageFile (char far *FileName, DBHANDLE far *rethFile);

STATUS LNPUBLIC	 MailCreateMessageFile (char far *FileName, char far *TemplateFileName, 
								char far *Title, DBHANDLE far *rethFile);

STATUS LNPUBLIC	 MailPurgeMessageFile (DBHANDLE hFile);

STATUS LNPUBLIC	 MailCloseMessageFile (DBHANDLE hFile);

STATUS LNPUBLIC	 MailGetMessageFileModifiedTime (DBHANDLE hFile, TIMEDATE far *retModifiedTime);

/* Message list functions */

STATUS LNPUBLIC	 MailCreateMessageList (DBHANDLE hFile, 
								DHANDLE far *hMessageList, 
								DARRAY far * far *MessageList, WORD far *MessageCount);

STATUS LNPUBLIC	 MailFreeMessageList (DHANDLE hMessageList, DARRAY far *MessageList);

STATUS LNPUBLIC	 MailGetMessageInfo (DARRAY far *MessageList, WORD Message, 
								WORD far *RecipientCount, 
								WORD far *Priority, 
								WORD far *Report);

STATUS LNPUBLIC  MailGetMessageSize(DARRAY far *MessageList, WORD Message, DWORD far *MessageSize);

STATUS LNPUBLIC	 MailGetMessageRecipient (DARRAY far *MessageList, WORD Message, 
								WORD RecipientNum, 
								char far *RecipientName, 
								WORD RecipientNameSize, 
								WORD far *RecipientNameLength);

STATUS LNPUBLIC	 MailDeleteMessageRecipient (DARRAY far *MessageList, WORD Message, 
								WORD RecipientNum);

STATUS LNPUBLIC	 MailGetMessageOriginator (DARRAY far *MessageList, WORD Message, 
								char far *OriginatorName, 
								WORD OriginatorNameSize, 
								WORD far *OriginatorNameLength);

STATUS LNPUBLIC	 MailGetMessageOriginatorDomain(DARRAY far *MessageList, WORD Message,
								char far *OriginatorDomain,
								WORD OriginatorDomainSize,
								WORD far *OriginatorNameLength);

STATUS LNPUBLIC	 MailOpenMessage (DARRAY far *MessageList, WORD Message, 
								DHANDLE far *hMessage);

STATUS LNPUBLIC	 MailGetMessageBody (DHANDLE hMessage, 
								DHANDLE far *hBody, DWORD far *BodyLength);

STATUS LNPUBLIC	 MailGetMessageBodyText(DHANDLE hMessage,
										char far *ItemName,
										char far *LineDelims,
										WORD LineLength,
										BOOL ConvertTabs,
										char far *OutputFileName,
										DWORD far *OutputFileSize);

STATUS LNPUBLIC	 MailGetMessageBodyComposite(DHANDLE hMessage,
											char far *ItemName,
											char far *OutputFileName,
											DWORD far *OutputFileSize);
STATUS LNPUBLIC  MailAddMessageBodyTextExt(DHANDLE hMessage,
										   char far *ItemName,
										   char far *InputFileName,
										   DWORD FontID,
										   char far *LineDelim,
										   WORD ParaDelim,
										   NLS_PINFO pInfo);

STATUS LNPUBLIC	 MailAddMessageBodyComposite(DHANDLE hMessage,
											char far *ItemName,
											char far *InputFileName);

STATUS LNPUBLIC	 MailSetMessageLastError (DARRAY far *MessageList, WORD Message, 
								char far *ErrorText);

STATUS LNPUBLIC	 MailPurgeMessage (DARRAY far *MessageList, WORD Message);

STATUS LNPUBLIC	 MailSendNonDeliveryReport (DARRAY far *MessageList, WORD Message, 
								WORD RecipientNums, WORD far *RecipientNumList, 
								char far *ReasonText, WORD ReasonTextLength);

STATUS LNPUBLIC	 MailSendDeliveryReport (DARRAY far *MessageList, WORD Message, 
								WORD RecipientNums, WORD far *RecipientNumList);

/* Mail address to user and domain name parsing function */

STATUS LNPUBLIC	 MailParseMailAddress (char far *MailAddress, WORD MailAddressLength,
								char far *UserName, WORD UserNameSize, WORD far *UserNameLength,
								char far *DomainName, WORD DomainNameSize, WORD far *DomainNameLength);


/* Broadcast newmail recieved message */

void LNPUBLIC	 MailBroadcastNewMail (char far *MessageText);	/* V2 Compatible, NETBIOS-ONLY */

/* Input flags for MailFindNextHopTo* routines */

#define	NEXTHOP_CALENDAR		0x00000001	/* Message being routed is a Calendar & Scheduling message */

/*	LoadFlags for MailLoadRoutingTablesExt */

#define	LOAD_INTERNALSMTP			0x00000001	/* Support internal SMTP transfer thread and DNS */
#define LOAD_EXTERNALSMTP			0x00000002	/* Support SMTP transfer out of local domain */
#define LOAD_USEDNS					0x00000004	/* Use dns when resolving names */
#define LOAD_USEHOSTS				0x00000008	/* Use hosts file when resolving names */
#define LOAD_SERVERREACHABLE		0x00000010	/* need to be in same named network */
#define LOAD_INTERNALSMTPALWAYS		0x00000020	/* Support internal SMTP even for non MIME messages */
#define LOAD_NOSERVERCACHE			0x00000040	/* Disable server cache */
#define LOAD_NODOMAINCACHE			0x00000080	/* Disable domain cache */
#define LOAD_NOFOREIGNSMTPDOMAINS   0x00000100	/* Disable Foreign SMTP Domains when SMTP External enabled */
#define LOAD_NOSKIPDNSQUERY			0x00000200	/* Don't skip the DNS query for domains without a "." */
#define LOAD_ORDERCONNECTIONSBYDEST 0x00000400	/* Order and search connections by destination domain/server name */
#define LOAD_LIMITNRPCROUTING		0x00000800	/* TRUE to limit routing algorithm to smtp external routing logic for internet domains */
#define LOAD_COSTBIASDECISION		0x00002000	/* TRUE to cause routing algorithm to use raw cost bias as an additional decision point */
STATUS LNPUBLIC MailLoadRoutingTablesExt(DBHANDLE hAddressBook, 
									char far *LocalServersName,
									char far *LocalServersDomain,
									char far *LocalServersInternetDomain,
									char far *TaskName,
									BOOL EnableTrace, 
									BOOL EnableDebug,
									DWORD LoadFlags,
									DHANDLE far *rethTables);
STATUS LNPUBLIC	 MailFindNextHopToDomainExt(DHANDLE hTables,
									char far *OriginatorsDomain, 
									char far *DestDomain, 
									DWORD FindFlags,
									char far *NextHopServer, 
									char far *NextHopMailbox, 
									DWORD far *NextHopFlags, 
									char far *ErrorServer);

STATUS LNPUBLIC	 MailLoadRoutingTables(DBHANDLE hAddressBook, 
									char far *LocalServerName,
									char far *LocalDomainDomain,
									char far *TaskName,
									BOOL EnableTrace,
									BOOL EnableDebug,
									DHANDLE far *rethTables);

STATUS LNPUBLIC	 MailReloadRoutingTables(DHANDLE hTables,
									BOOL EnableTrace,
									BOOL EnableDebug,
									BOOL far *retAddressBookModified);

STATUS LNPUBLIC	 MailUnloadRoutingTables(DHANDLE hTables);


/* Output flags for MailFindNextHopTo* routines */

#define	NEXTHOP_INTRANET			0x00000001	/* Next Hop is on same network */
#define NEXTHOP_USESMTP				0x00000004	/* Use SMTP to reach next hop */

STATUS LNPUBLIC	 MailFindNextHopToDomain(DHANDLE hTables,
									char far *OriginatorsDomain, 
									char far *DestDomain, 
									char far *NextHopServer, 
									char far *NextHopMailbox, 
									DWORD far *NextHopFlags, 
									char far *ErrorServer);

STATUS LNPUBLIC	 MailFindNextHopToServer(DHANDLE hTables,
									 char far *DestDomain, 
									 char far *DestServer, 
									 char far *NextHopServer, 
									 char far *NextHopMailbox, 
									 DWORD far *NextHopFlags, 
									 WORD far *ActualCost);

typedef enum {MAIL_ERROR, MAIL_TRANSFER, 
			  MAIL_DELIVER, MAIL_FORWARD} 
	MAIL_ROUTING_ACTIONS;

STATUS LNPUBLIC	 MailFindNextHopToRecipient(DHANDLE hTables,
									 char far *OriginatorsDomain,
									 char far *RecipientAddress,
									 MAIL_ROUTING_ACTIONS far *Action, 
									 char far *NextHopServer, 
									 char far *NextHopMailbox,
									 char far *ForwardAddress,
									 char far *ErrorText, 
									 DWORD far *NextHopFlags); 

STATUS LNPUBLIC	 MailFindNextHopToRecipientExt(DHANDLE hTables,
									 char far *OriginatorsDomain,
									 char far *RecipientAddress,
									 MAIL_ROUTING_ACTIONS far *Action, 
									 char far *NextHopServer, 
									 char far *NextHopMailbox,
									 char far *ForwardAddress,
									 char far *ErrorText, 
									 DWORD far *NextHopFlags,
									 DWORD lookupFlags); 

STATUS LNPUBLIC	 MailFindNextHopViaRules(DHANDLE hTables,
									 char far *RecipientAddress,
									 char far *retDestServer,
									 char far *retDestDomain);

BOOL LNPUBLIC	 MailSetDynamicCost(DHANDLE hTables, 
									char far *Server, 
									SWORD CostBias);

BOOL LNPUBLIC	 MailResetAllDynamicCosts(DHANDLE hTables);


#ifdef __cplusplus
}
#endif

#endif /* MAILSERV_DEFS */


#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


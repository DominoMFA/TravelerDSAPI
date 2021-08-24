
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/********************************************************************/
/*																	*/
/* Licensed Materials - Property of IBM and/or HCL */
/*																	*/
/* Notes_V11.0.1, Domino_V11.0.1   */
/*																	*/
/* Copyright IBM Corp. 2011, 2017  All Rights Reserved. */
/* (c) Copyright HCL Technologies Ltd. 2020.  All Rights Reserved.  */
/*																	*/
/* Note to U.S. Government Users Restricted Rights:               */
/* Use, duplication or disclosure restricted by GSA ADP Schedule */
/*                                                */
/*																	*/
/********************************************************************/

#ifndef CAL_API_H
#define CAL_API_H

#ifndef NSF_DATA_DEFS
#include "nsfdata.h"				/*	UNID, NOTEID, TIMEDATE */
#include "misc.h"					/*  MAXSPRINTF  */
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* DEBUG OUTPUT: To output informational messages to the console in regards to C&S API operations, add the Notes.ini 
 * line: CSDebugApi=1.  Note: It is possible that this will generate console output in non-API operations as well
 * (routing iCalendar messages, etc) */
#define DEBUG_CSAPI "CSDebugApi"

/* DIABLING API: Setting the ini parameter CSDisableApi=1 will disable the API from running - ERR_DISABLED will 
 * be returned from all API calls */
#define DISABLE_CSAPI "CSDisableApi"


/**************************************************************************************************************************************
 ***************** READ RANGE METHODS *************************************************************************************************
 **************************************************************************************************************************************
 * Below method offers performant view-level capabilities to read calendar data over a date range **************************************
 *************************************************************************************************************************************/


/* Values to use for returning only specific information in the returned iCalendar in CalReadRange.
 * Note: If used on a database with a pre-8.5.4 mail template design, then only supported fields will be outputted; adding these 
 * flags to output non-supported fields will not have any effect (See CalReadRange comments for more details).
 * Note: Even if NO flags are requested, some data will always return.  This includes:
 * UID						iCalendar UID identifier for a calendar entry
 * X-LOTUS-UNID (notices only)
 *							For notices that display on the calendar we will always output this property (For example, a ghosted
 *							invitation or reschedule).  This UNID value can be used as an identifier for the other notice methods
 *							in the API.
 *							Note: Use of READ_RANGE_MASK2_UNID will also generate X-LOTUS-UNID data for calendar entries, but this
 *							will not otherwise output for calendar entries (just notices)
 * X-LOTUS-SUMMARYDATAONLY  (Will always be set to = TRUE).  This indicates that this data was part of a ReadRange call and does
 *							not represent the full data for the calendar entry.  Presence of this item will block any attempt to
 *							use this resulting entry as input for the update method.
 */
#define READ_RANGE_MASK_DTSTART				0x00000001
#define READ_RANGE_MASK_DTEND				0x00000002
#define READ_RANGE_MASK_DTSTAMP				0x00000004
#define READ_RANGE_MASK_SUMMARY				0x00000008
#define READ_RANGE_MASK_CLASS				0x00000010
#define READ_RANGE_MASK_PRIORITY			0x00000020
#define READ_RANGE_MASK_RECURRENCE_ID		0x00000040
#define READ_RANGE_MASK_SEQUENCE			0x00000080
#define READ_RANGE_MASK_LOCATION			0x00000100
#define READ_RANGE_MASK_TRANSP				0x00000200
#define READ_RANGE_MASK_CATEGORY			0x00000400
#define READ_RANGE_MASK_APPTTYPE			0x00000800
#define READ_RANGE_MASK_NOTICETYPE			0x00001000
#define READ_RANGE_MASK_STATUS				0x00002000
#define READ_RANGE_MASK_ONLINE_URL			0x00004000		// Includes online meeting URL as well as any online meeting password or conf ID
#define READ_RANGE_MASK_NOTESORGANIZER		0x00008000		// Note: For performance reasons, the organizer may not be stored in ORGANIZER but rather in
															// X-LOTUS-ORGANIZER to avoid lookups necessary to get the internet address.
#define READ_RANGE_MASK_NOTESROOM			0x00010000		// Note: For performance reasons, the organizer may not be stored in PARTICIPANT but rather in
															// X-LOTUS-ROOM to avoid lookups necessary to get the internet address.
#define READ_RANGE_MASK_ALARM				0x00020000		// Output alarm information for this entry


/* Non-default values - only harvested if requested in dwReturnMaskExt by CalReadRange.*/
#define READ_RANGE_MASK2_HASATTACH			0x00000001		// X-LOTUS-HASATTACH is set to 1 if there are any file attachments for this entry
#define READ_RANGE_MASK2_UNID				0x00000002		// X-LOTUS-UNID will always be set for notices (as it is used as the identifier for
															// a notice), but setting this flag will also set X-LOTUS-UNID for calendar entries,
															// where this will be set with the UNID of the note that currently contains this
															// instance (can be used to construct a URL to open the instance in Notes, for instance)

/**************************************************************************************************************************************
 * CalReadRange
 * This will return data for all entries that begin within a specified date range, with paging capabilities (similar to
 * NIFReadEntries) in cases where there is more data than can be returned in a single call.
 * Specifically, this can return one or both of:
 * 1) iCalendar generated from view level data about the calendar entries in the date range
 * 2) A list of UIDs for each calendar entry in the date range
 *
 * The iCalendar (returned in hRetCalData) contains only view level data. Full iCalendar data for entries must be retrieved via 
 * calls to CalReadEntry.  For recurring entries, this returns a separate VEVENT with a RECURRENCE-ID for each instance in the 
 * recurring entry that lies within the specified date range.  Inclusion within a date range is determined by using start time only.
 * If any invitations, reschedule notices, countered meetings, or cancelation notices appear on your calendar, they will be included
 * in the output. Meetings not on your calendar (including delegated, declined, and some canceled/countered meetings) will NOT be
 * returned in the output.
 *
 * The returned VEVENTs will include the UID, as well as output corresponding to each of the READ_RANGE_MASK_### values defined in
 * this file. Specific READ_RANGE_MASK_### values can be defined in dwReturnMask and dwReturnMaskExt to further control what properties
 * are output. Examples of properties that are not included are ATTENDEE, DESCRIPTION, and ATTACH.
 *
 * UID information (returned in hRetUIDData) is in the form of a handle to a textlist (see textlist.h).  This list can be iterated
 * through to get the UID for each entry in a date range.
 *
 * NOTE: For mail databases using a pre-8.5.4 mailfile design:
 *		UID:			The returned UID information (both in hRetCalData and in hRetUIDData) will be a programatically generated alternate
 *						UID rather than the actual UID which is returned when calling CalReadEntry.  This alternate UID can be used when as
 *						the UID for other API methods that require UID input (such as CalReadEntry); however, use of the actual UID to the \
 *						alternate UID is preferred whenever it is available, and comes with improved performance.  Multiple instances of a 
 *						repeating meeting will have different alternate UIDs (even though the actual UID is the same).
 *		Limited data:	The returned properties in the generated iCalendar VEVENTs is limited to a subset of the values
 *						defined in READ_RANGE_MASK_###.  For example, the following data is not returned by this function when used with
 *						pre-8.5.3 mailfiles: RECURRENCE-ID, SEQUENCE, TRANSP, CATEGORY, Online meeting information, alarm information,
 *						LOCATION, etc....  However, the SUMMARY will contain appended information regarding LOCATION, ROOM,
 *						and ORGANIZER information (as it exists in the Notes calendar view).
 *
 * Inputs:
 *		  hDB					The database from which entries are returned
 *		  tdStart				The starting point of the time range.  Only events that START on or after this time will be returned and entries
 *								that start before this date but span into the range are NOT returned.  Start a day early to capture these entries.
 *		  tdEnd					The ending point of the time range
 *		  dwViewSkipCount		How many view entries to skip before reading the collection. To skip no entries, set this argument to 0.
 *								Note: The data returned from this method is returned from a view and there is no guarantee to be a 1-1
 *								match between view entries and VEVENTs in the returned iCalendar data.  As such, ViewSkipCount and
 *								retNumViewEntriesReturned are not intended to represent a number of VEVENTs at all, but instead intended only
 *								to allow the caller to make a subsequent call to retrieve remaining data continuing from where a previous call
 *								ended.
 *		  dwMaxReturnCount		The maximum number of entries (VEVENTs) that should be returned. To attempt to read all the entries within the 
 *								date range, set this argument to 0xFFFFFFFF (MAXDWORD).
 *		  dwReturnMask			Bits that control what properties about the calendar entries will be returned. The information flags 
 *								are defined in READ_RANGE_MASK_xxx, and may be OR'ed together to combine functionailty.  Use MAXDWORD to get
 *								information about the returned calendar entries.
 *		  dwReturnMaskExt		Bits that control what properties about the calendar entries will be returned in addition to those defined in 
 *								dwReturnMask. The information flags are defined in READ_RANGE_MASK2_xxx, and may be OR'ed together to combine
 *								functionailty.  Use 0 to generate only the commonly used properties from dwReturnMask, use MAXDWORD to 
 *								generate all available data, or specify only the bits corresponding to desired READ_RANGE_MASK2_xxx data.
 *		  pFilterInfo			RESERVED - MUST be NULL
 *		  dwFlags				Flags to control non-default behavior
 *									Supported: None currently
 *		  pCtx					RESERVED - MUST be NULL
 *
 * Outputs:
 *		  hRetCalData			Handle to the returned iCalendar data.  It is the caller's responsibility to free this memory.  If you 
 *								are not interested in this information (but only interested in hRetUIDData), set this argument to NULL.
 *		  retCalBufferLength	The address of a WORD in which the length of the hRetCalData information buffer is returned. If you are
 *								not interested in this length, set this argument to NULL.
 *								Ignored if hRetCalData is NULL.
 *		  hRetUIDData			Handle to a textlist (see textlist.h) data representing UIDs found within the range.  If you are not interested in 
 *								this information, set this argument to NULL.  Once returned, size and/or number of values can be
 *								determined by calls to ListGetSize and/or ListGetNumEntries.
 *		  retNumViewEntriesProcessed
 *								The address of a DWORD in which the number of processed view entries is returned. If you are not interested in 
 *								this information, set this argument to NULL. Ignored if hRetCalData is NULL.  Useful as the value of
 *								dwViewSkipCount in a subsequent call in case you cannot retrieve all data.
 *								This value is NOT guaranteed to match the number of UIDs or VEVENTs in hRetCalData/hRetUIDData.
 *		  retSignalFlags		The address of a WORD in which various result flags are returned. If one of the the flags represented
 *								by SIGNAL_ANY_CONFLICT is set, the collection has changed since it was last read. If the SIGNAL_MORE_TO_DO
 *								flag is set, then the end of the collection has not been reached and there exists more information than
 *								could fit in the return buffer. In this case, CalReadRange should be called again to retrieve an additional
 *								buffer of information. The signal flags are defined in SIGNAL_xxx, and are returned OR'ed together.
 *
 * Returns:
 *		  NOERROR on success
 *		  ERR_NULL_DBHANDLE			The database handle is NULL
 *		  ERR_MISC_INVALID_ARGS		Unexpected arguments provided
 *		  ERR_NO_CALENDAR_FOUND		The required view(s) do not exist in this database
 *		  ERR_NOT_FOUND				No entries were found that fit the search criteria
 *		  ERR_MISC_UNEXPECTED_ERROR	Unexpected internal error
 */
STATUS LNPUBLIC CalReadRange(DBHANDLE hDB,
									TIMEDATE tdStart,
									TIMEDATE tdEnd,
									DWORD dwViewSkipCount,
									DWORD dwMaxReturnCount,
									DWORD dwReturnMask,
									DWORD dwReturnMaskExt,
									void *pFilterInfo,
									MEMHANDLE far *hRetCalData,
									WORD far *retCalBufferLength,
									MEMHANDLE far *hRetUIDData,
									DWORD far *retNumEntriesProcessed,
									WORD far *retSignalFlags,
									DWORD dwFlags,
									void* pCtx);

/**************************************************************************************************************************************
 ***************** READ ENTRY METHODS *************************************************************************************************
 **************************************************************************************************************************************
 * These methods return iCalendar representing a calendar entry or instance  **********************************************************
 *************************************************************************************************************************************/

// Flags that control behavior of the calendar APIs that return iCalendar data for an entry or notice
#define CAL_READ_HIDE_X_LOTUS				0x00000001			// Used when APIs generate iCalendar
																// By default, some X-LOTUS properties and parameters will be included in iCalendar data
																// returned by these APIs.  CAL_READ_HIDE_X_LOTUS causes all X-LOTUS properties and
																// parameters to be removed from the generated iCalendar data.
																// Note: This overrides CAL_READ_INCLUDE_X_LOTUS

#define CAL_READ_INCLUDE_X_LOTUS			0x00000002			// Used when APIs generate iCalendar
																// Include all Lotus specific properties like X-LOTUS-UPDATE-SEQ, X-LOTUS-UPDATE_WISL, etc
																// in the generated iCalendar data.
																// These properties are NOT included by default in any iCalendar data returned by the APIs.
																// Caution: Unless the caller knows how to use these it can be dangerous since their presence will
																// be honored and can cause issues if not updated properly.
																// Ignored if CAL_READ_HIDE_X_LOTUS is also specified.

#define CAL_READ_SKIP_RESPONSE_DATA			0x00000004			// RESERVED: This functionality is not currently in plan
																// When generating ATTENDEE info in CalReadEntry, determine and populate response
																// Status (which might be a performance hit)



/**************************************************************************************************************************************
 * CalReadEntry
 * This will return complete iCalendar data for the specified entry.  
 * For recurring entries, this may result in multiple VEVENTs in the returned iCalendar data.  In this case, the first VEVENT represents the recurrence set 
 * and additional entries represent exceptions to the recurrence set.
 * All instances that differ from the recurrence set will be returned as additional VEVENTs containing the exceptional data. There is no concept of 'runs' of instances or RANGE of instances.
 * Alternatively, a specific instance may be requested using pszRecurID and only the data for that instance will be returned.
 * Returned data will not include rich text description.
 * File attachments are returned as a URI that can be read with a separate call (Specifics here are TBD)
 * All participants of a meeting will be returned as PARTSTAT=NEEDS-ACTION even if they have responded.
 *
 * Inputs:
 *		  DBHANDLE hDB			The database from which entries are returned.
 *		  char* pszUID			The UID of the entry to be returned.
 *		  char* pszRecurID		NULL for single entries or to read data for an entire recurring series.
 *								If populated, this is the RECURRENCE-ID of the specific instance to read.  Other instances
 *								will not be returned.  Timezones not permitted (time values must be in UTC time)
 *		  DWORD dwFlags			CAL_READ_### flags to control non-default behavior
 *									Supported: CAL_READ_HIDE_X_LOTUS, CAL_READ_INCLUDE_X_LOTUS
 *		  DWORD *pdwReserved	RESERVED - MUST be NULL
 *		  void* pCtx			RESERVED - MUST be NULL
 *
 * Outputs:
 *		  *hRetCalData			Handle to the returned iCalendar data.  It is the caller's responsibility to free this memory.
 *
 * Returns:
 *		  NOERROR on success
 *		  ERR_NULL_DBHANDLE			The database handle is NULL
 *		  ERR_MISC_INVALID_ARGS		Unexpected arguments provided
 *		  ERR_TDI_CONV				The recurrence ID specified cannot be interpreted
 *		  ERR_NO_CALENDAR_FOUND		Unable to find the entry because the required view does not exist in this database
 *		  ERR_NOT_FOUND				There are no entries that match the specified UID or UID/recurid in the database
 *		  ERR_NOTE2ICAL_CONVERT		Unable to convert to iCalendar
 *		  ERR_MISC_UNEXPECTED_ERROR	Unexpected internal error
 */
STATUS LNPUBLIC CalReadEntry(DBHANDLE hDB, const char* pszUID, const char* pszRecurID, MEMHANDLE far *hRetCalData, DWORD* pdwReserved, DWORD dwFlags, void* pCtx);

/**************************************************************************************************************************************
 ***************** WRITE ENTRY METHODS ************************************************************************************************
 **************************************************************************************************************************************
 * These methods take iCalendar input representing a calendar entry or instance and update the calendar *******************************
 *************************************************************************************************************************************/

// Flags that control behavior of the calendar APIs - Used when APIS take iCalendar input to modify calendar data
#define CAL_WRITE_COMPLETE_REPLACE				0x00000001		// Used when APIs modify entry data via CalUpdateEntry.
																// This flag means that NO data is preserved from the original entry and the
																// resulting entry is 100% a product of the iCalendar passed in.
																// NOTE: When this flag is NOT used, some content may be preserved during an
																// update if that particular content was not included in the iCalendar input.
																// This includes:
																// Body
																// Attachments
																// Custom data properties as specified in $CSCopyItems

#define CAL_WRITE_DISABLE_IMPLICIT_SCHEDULING	0x00000002		// Used when APIs create or modify calendar entries where the organizer is the mailfile owner.
																// When a calendar entry is modified with CAL_WRITE_DISABLE_IMPLICIT_SCHEDULING set, no notices are
																// sent (invites, updates, reschedules, cancels, etc)
																// Note: This is not intended for cases where you are saving a meeting as a draft (since there is currently
																// not a capability to then send it later.  It will also not allow some notices to go out but other notices
																// not to go out (such as, send invites to added invitees but dont send updates to existing invitees).
																// Rather, this is targeted at callers that prefer to be responsible for sending out notices themselves through
																// a separate mechanism

#define CAL_WRITE_IGNORE_VERIFY_DB				0x00000004		// Used when APIs create or modify entries on the calendar
																// This will allow creation/modification of calendar entries, even if the database is not a mailfile

#define CAL_WRITE_USE_ALARM_DEFAULTS			0x00000008		// By default, alarms will be created on calendar entries based on VALARM content of iCalendar input.  Use of
																// this flag will disregard VALARM information in the iCalendar and use the user's default alarm settings for
																// created or updated entries.

/**************************************************************************************************************************************
 * CalCreateEntry
 * Creates a calendar entry.  This supports either a single entry, or a recurring entry which may contain multiple
 * VEVENTS represenging both the series and exception data.
 * The iCalendar input must only contain data for a single UID.
 * For meetings, ATTENDEE PARTSTAT data is ignored.
 * If the mailfile owner is the meeting organizer, invitations will be sent out to meeting participants (unless CAL_WRITE_DISABLE_IMPLICIT_SCHEDULING is specified)
 *
 * Inputs:
 *		  DBHANDLE hDB			The database where the entry will be created
 *		  char* pszCalEntry		The iCalendar data representing the entry to create
 *		  DWORD dwFlags			CAL_WRITE_### flags to control non-default behavior
 *									Supported: CAL_WRITE_DISABLE_IMPLICIT_SCHEDULING, CAL_WRITE_IGNORE_VERIFY_DB
 *		  void* pCtx			RESERVED - MUST be NULL
 *
 * Outputs:
 *		  MEMHANDLE *hRetUID		If non-null, the UID of the created iCalendar will be placed here.  The UID contained in the
 *									iCalendar will be honored unless there was not one, in which case one will be generated automatically.
 *									It is the caller's responsibility to free this memory.
 *
 * Returns:
 *		  NOERROR on success
 *		  ERR_NULL_DBHANDLE			The database handle is NULL
 *		  ERR_MISC_INVALID_ARGS		Unexpected arguments provided
 *		  ERR_NO_CALENDAR_FOUND		Unable to find the entry because the required view does not exist in this database
 *		  ERR_EXISTS				An entry already exists
 *		  ERR_CS_PROFILE_NOOWNER	Calendar Profile does not specify owner
 *		  ERR_UNEXPECTED_METHOD		Provided iCalendar contains a method (no method expected here)
 *		  ERR_MissingVEventComponents		Missing required VEvent components
 *		  ERR_InvalidVEventPropertyFound	Invalid VEvent property found, such as mismatched UIDs
 *		  ERR_ICAL2NOTE_CONVERT		Error interpereting iCalendar input
 *		  ERR_MISC_UNEXPECTED_ERROR	Unexpected internal error
 *		  ERR_IMPLICIT_SCHED_FAILED	Entry created, but errors were encountered sending notices to meeting participants
 */
STATUS LNPUBLIC CalCreateEntry(DBHANDLE hDB, const char* pszCalEntry, DWORD dwFlags, MEMHANDLE far *hRetUID, void* pCtx);

/**************************************************************************************************************************************
 * CalUpdateEntry
 * This will modify an existing calendar entry.  This supports either single entries or recurring entries, but recurring entries will only 
 * support updates for a single instance specified via RECURRENCE-ID that may not include a RANGE (This may be permitted in the future but 
 * for now will return an error).
 * The iCalendar input may only contain a single VEVENT and must contain a UID.
 * By default, attachments and custom data (for fields contained in $CSCopyItems) will be maintained from the
 * existing calendar entry.  Similarly, description will also be maintained if it is not specified in the iCalendar
 * content that is updating.  Both of these behaviors can be canceled via the CAL_WRITE_COMPLETE_REPLACE flag.
 * If the mailfile owner is the meeting organizer, appropriate notices will be sent out to meeting participants (unless
 * CAL_WRITE_DISABLE_IMPLICIT_SCHEDULING is specified)
 *
 * Inputs:
 *		  DBHANDLE hDB			The database containing the entry to update
 *		  char* pszCalEntry		The iCalendar data representing the updated entry
 *		  char* pszUID			If non-NULL, this value MUST match the UID value in the iCalendar input if present,
 *								or else this returns ERR_InvalidVEventPropertyFound.  If the iCalendar input has no
 *								UID this value will be used.
 *		  char* pszRecurID		If non-NULL, this value MUST match the RECURRENCE-ID value in the iCalendar input
 *								if present, or else this returns ERR_InvalidVEventPropertyFound.  If the iCalendar 
 *								input has no RECURRENCE-ID this value will be used.
 *		  char* pszComments		If non-NULL, this text will be sent as comments on any notices sent to meeting 
 *								participants as a result of this call.
 *								that will be included on the notices.  Can be NULL.
 *		  DWORD dwFlags			CAL_WRITE_### flags to control non-default behavior
 *									Supported: CAL_WRITE_COMPLETE_REPLACE, CAL_WRITE_DISABLE_IMPLICIT_SCHEDULING, CAL_WRITE_IGNORE_VERIFY_DB, CAL_WRITE_SMARTSEQUENCE
 *		  void* pCtx			RESERVED - MUST be NULL
 *
 * Outputs:
 *
 * Returns:
 *		  NOERROR on success
 *		  ERR_NULL_DBHANDLE			The database handle is NULL
 *		  ERR_MISC_INVALID_ARGS		Unexpected arguments provided
 *		  ERR_CALACTION_INVALID		This calendar entry is not in a state where updating it is supported.
 *		  ERR_NO_CALENDAR_FOUND		Unable to find the entry because the required view does not exist in this database
 *		  ERR_NOT_FOUND				There are no entries that match the specified UID or UID/recurid in the database
 *		  ERR_NOT_YET_IMPLEMENTED	This update is not yet supported (update range or multiple VEVENTs?)
 *		  ERR_CS_PROFILE_NOOWNER	Calendar Profile does not specify owner
 *		  ERR_UNEXPECTED_METHOD		Provided iCalendar contains a method (no method expected here)
 *		  ERR_ICAL2NOTE_OUTOFDATE	iCalendar input is out of date in regards to sequence information.
 *		  ERR_MissingVEventComponents		Missing required VEvent components
 *		  ERR_InvalidVEventPropertyFound	Invalid VEvent property found
 *		  ERR_ICAL2NOTE_CONVERT		Error interpereting iCalendar input
 *		  ERR_MISC_UNEXPECTED_ERROR	Unexpected internal error
 *		  ERR_IMPLICIT_SCHED_FAILED	Entry was updated, but errors were encountered sending notices to meeting participants
 */
STATUS LNPUBLIC CalUpdateEntry(DBHANDLE hDB, const char* pszCalEntry, const char* pszUID, const char* pszRecurID, const char* pszComments, DWORD dwFlags, void* pCtx);

/**************************************************************************************************************************************
 ***************** METHODS TO GET NOTICE INFO *****************************************************************************************
 **************************************************************************************************************************************
 * These methods return information about notices that apply to calendar data (invitations, updates, reschedules, cancels, etc) *******
 *************************************************************************************************************************************/

/**************************************************************************************************************************************
 * CalGetNewInvitations
 * Retrieve invitations in a mailfile that have not yet been responded to.  This returns the number of new invitations as well as optional
 * NOTEID and/or UNID lists.
 * This returns only invitations (and delegated invitations), and not reschedules, information updates, cancels, etc.  This method does not
 * filter out any invitations that have since been canceled/rescheduled, or are otherwise out of date.  Once the invitation is accepted, 
 * other notices that apply to that meeting can be discovered with a call to CalGetUnappliedNotices must be used (on a per-UID level).
 * Only invitations for meetings that are current (at least one instance starts within the last day or in the future) are returned, although
 * the starting time can be specified by the caller to override the default.
 * A caller can retrieve only invitations that have arrived since a prior call to CalGetNewInvitations by using tdSince and ptdretUntil.
 * If pszUID is provided, invitations only for a particular meeting will be returned.  This is useful if you are looking for an invitation or
 * invitations that correspond to an updated notice that has arrived.  Note: Mutliple invitations might exist for a particular UID if that 
 * meeting is recurring and you were added to an instance or instances after the initial creation.
 * The returned notices are not guaranteed to be in any particular order.
 *
 * Inputs:
 *		  DBHANDLE hDB			The database from which entries are returned
 *		  TIMEDATE* ptdStart	Optional: If provided, only invitations for meetings that occur on or after this time will be returned.
 *								Passing in NULL will use the default value (one day before current time)
 *		  char* pszUID			Optional: If present only invitations with a matching UID will be returned.  Note: For some repeating meetings 
 *								there could be multiple invites for the same UID (for separate instances).
 *		  TIMEDATE* ptdSince	Optional: Only return invitations that have been received/modified since the provided time.
 *								Passing in NULL will return invitations regardless of when they arrived.
 *		  TIMEDATE* ptdretUntil	Optional: If provided, this is populated with the time of this method call, which can then be used as
 *								the ptdSince argument of a subsequent call.
 *		  DWORD dwFlags			Flags - currently unused
 *		  void* pReserved		RESERVED - MUST be NULL
 *		  void* pCtx			RESERVED - MUST be 0
 *
 * Outputs:
 *		  WORD* pwNumInvites	The number of invitaitons returned (and thus also the length of phRetNOTEIDs and/or phRetUNIDs)
 *								Ignored if NULL.
 *		  *phRetNOTEIDs			Handle to the returned NOTEID data.  It is the caller's responsibility to free this memory via OSMemoryFree (if 
 *								non-NULL).  Access the data via casting the result of OSMemoryLock to a (NOTEID*).
 *								Ignored if NULL.
 *		  *phRetUNIDs			Handle to the returned UNID data.  It is the caller's responsibility to free this memory via OSMemoryFree (if 
 *								non-NULL).  Access the data via casting the result of OSMemoryLock to a (UNID*).
 *								Ignored if NULL.
 *
 * Returns:
 *		  NOERROR on success
 *		  ERR_NULL_DBHANDLE			The database handle is NULL
 *		  ERR_MISC_INVALID_ARGS		Unexpected arguments provided
 *		  ERR_MISC_UNEXPECTED_ERROR	Unexpected internal error
 */
STATUS LNPUBLIC CalGetNewInvitations(DBHANDLE hDB, TIMEDATE* ptdStart, const char* pszUID, TIMEDATE* ptdSince, TIMEDATE* ptdretUntil, WORD* pwNumInvites, MEMHANDLE *phRetNOTEIDs, MEMHANDLE *phRetUNIDs, void* pReserved, DWORD dwFlags, void* pCtx);

/**************************************************************************************************************************************
 * CalGetUnappliedNotices
 * Retrieve the unapplied notices that exist for a participant of calendar entry representing a meeting.
 * This will return things like: Reschedules, informational updates, cancelations, confirmations, etc.
 * Notices will only be returned if the initial invitaiton has already been responded to, otherwise this method will return
 * ERR_INVITE_NOT_ACCEPTED.
 * For recurring meetings, notices that apply to any instances in the series will be returned, with the exception of instances where
 * the initial invitation has not yet been responded to.
 * Calendar entries that are not meetings will return ERR_INVALID_NOTE.
 * We do not currently support getting unprocessed calendar entries if you are the owner (such as a counter
 * proposal request or a request for updated information), so this will return ERR_NOT_YET_IMPLEMENTED.
 * Note: For recurring meetings, it is possible that multiple notices will contain current information for a particular occurence,
 * so it is not possible to guarantee that there is a single "most current" notice.  For example, the subject might be changed 
 * for a single instance, and then the time may be changed across instances.  Because only one notice will have the current
 * subject and another notice will have the current time but NOT the current subject, both notices will be returned and both
 * must be processed to guarantee accuracy.  Process returned notices via the CalNoticeAction method.
 *
 * Inputs:
 *		  DBHANDLE hDB			The database to search for calendar entries
 *		  char* pszUID			The UID of the entry to return notices for
 *		  void* pReserved		RESERVED - MUST be NULL
 *		  DWORD dwFlags			Flags - currently unused
 *		  void* pCtx			RESERVED - MUST be NULL
 *
 * Outputs:
 *		  WORD* pwNumNotices	The number of unapplied notices for this meeting (and thus also the length of phRetNOTEIDs and/or phRetUNIDs
 *								if they are non-NULL)
 *								Ignored if NULL.
 *		  *phRetNOTEIDs			Handle to the returned NOTEID data.  It is the caller's responsibility to free this memory via OSMemoryFree (if 
 *								non-NULL).  Access the data via casting the result of OSMemoryLock to a (NOTEID*)
 *								Ignored if NULL.
 *		  *phRetUNIDs			Handle to the returned UNID data.  It is the caller's responsibility to free this memory via OSMemoryFree (if 
 *								non-NULL).  Access the data via casting the result of OSMemoryLock to a (UNID*)
 *								Ignored if NULL.
 *
 * Returns:
 *		  NOERROR on success
 *		  ERR_NULL_DBHANDLE			The database handle is NULL
 *		  ERR_NOT_FOUND				There are no entries that match the specified UID in the database.
 *		  ERR_INVALID_NOTE			This entry is not valid to have unapplied notices (this is not a meeting, etc)
 *		  ERR_INVITE_NOT_ACCEPTED	Unapplied notices cannot be retrieved for this meeting since the invitation has not yet been accepted.
 *									Call CalGetNewInvitations to get any invites with this UID.
 *									NOTE: In cases where you are added to a repeat set after the fact, there may be multiple invites so this
 *									error will not be returned, and notices for any invites that HAVE been accepted will be returned.
 *		  ERR_NOT_YET_IMPLEMENTED	Support to get unapplied notices on this entry is not implemented (you are the chair, etc)
 *		  ERR_MISC_INVALID_ARGS		Unexpected arguments provided
 *		  ERR_MISC_UNEXPECTED_ERROR	Unexpected internal error
 *		  Error codes for failure cases TBD
 */
STATUS LNPUBLIC CalGetUnappliedNotices(DBHANDLE hDB, const char* pszUID, WORD* pwNumNotices, MEMHANDLE *phRetNOTEIDs, MEMHANDLE *phRetUNIDs, void* pReserved, DWORD dwFlags, void* pCtx);

/**************************************************************************************************************************************
 * CalReadNotice
 * This will return iCalendar data representing a notice with the specified NOTIED.  A notice may not yet be applied to the calendar entries itself, but an application may 
 * want to read the notice (and process it).  Examples of notices include invitations, reschedules, information updates, confirmations, cancelations, counterproposals,
 * requests for information, acceptances, declines, tenative acceptances, etc.
 *
 * Inputs:
 *		  DBHANDLE hDB			The database from which entries are returned.
 *		  NOTEID noteID			The NOTEID of the notice to be returned.
 *		  void* pReserved		RESERVED - MUST be NULL
 *		  DWORD dwFlags			CAL_READ_### flags to control non-default behavior
 *									Supported: CAL_READ_HIDE_X_LOTUS, CAL_READ_INCLUDE_X_LOTUS
 *		  void* pCtx			RESERVED - MUST be NULL
 *
 * Outputs:
 *		  *hRetCalData		Handle to the returned iCalendar data.  It is the caller's responsibility to free this memory.
 *
 * Returns:
 *		  NOERROR on success
 *		  ERR_NULL_DBHANDLE			The database handle is NULL
 *		  ERR_MISC_INVALID_ARGS		Unexpected arguments provided
 *		  ERR_INVALID_NOTE			Note does not exist or is note a calendar note
 *		  ERR_NOTE2ICAL_CONVERT		Unable to convert to iCalendar
 *		  ERR_MISC_UNEXPECTED_ERROR	Unexpected internal error
 */
STATUS LNPUBLIC CalReadNotice(DBHANDLE hDB, NOTEID noteID, MEMHANDLE far *hRetCalData, void* pReserved, DWORD dwFlags, void* pCtx);

/**************************************************************************************************************************************
 * CalReadNoticeUNID
 * Same as CalReadNotice but takes a UNID input instead of a NOTEID input
 */
STATUS LNPUBLIC CalReadNoticeUNID(DBHANDLE hDB, UNID unid, MEMHANDLE far *hRetCalData, void* pReserved, DWORD dwFlags, void* pCtx);


/**************************************************************************************************************************************
 ***************** ACTION HANDLING ****************************************************************************************************
 **************************************************************************************************************************************
 * These methods perform direct action handling and does not rely upon the iCalendar standard as above code does.  Actions can be taken
 * on calendar entries or calendar notices. *******************************************************************************************
 *************************************************************************************************************************************/

/* CAL_PROCESS_### values are used to define the action taken by CalNoticeAction and CalEntryAction */
#define CAL_PROCESS_ACCEPT				0x00000002	/* Accept (regardless of conflicts)
													 * For Information update notices or confirm notices, this will apply the changes to the relavent
													 * calendar entry.
													 * Used by the organizer to accept a counter proposal.
													 */
#define CAL_PROCESS_TENTATIVE			0x00000004	/* Tentatively accept (regardless of conflicts) */
#define CAL_PROCESS_DECLINE				0x00000008	/* Decline 
													 * Can be used by the organizer to decline a counter if done from a counter notice */
#define CAL_PROCESS_DELEGATE			0x00000010	/* Delegate to EXT_CALACTION_DATA::pszDelegateTo */
#define CAL_PROCESS_COUNTER				0x00000020	/* Counter to a new time (requires populating EXT_CALACTION_DATA::ptdChangeTo values) */
#define CAL_PROCESS_REQUESTINFO			0x00000040	/* Request updated information from the organizer for this meeting.
													 * Also used by the organizer to respond to a request for updated info.
													 */
#define CAL_PROCESS_REMOVECANCEL		0x00000080	/* This will process a cancelation notice, removing the meeting from the calendar */
#define CAL_PROCESS_DELETE				0x00000100	/* This will physically delete a meeting from the calendar.  This will NOT send notices out */
#define CAL_PROCESS_SMARTREMOVE			0x00000200	/* This will remove the meeting or appointment from the calendar and send notices if 
													 * necessary.
													 * It is treated as a CAL_PROCESS_CANCEL if the entry is a meeting the mailfile 
													 * owner is the organizer of.  
													 * It is treated as a CAL_PROCESS_DECLINE if the entry is a meeting that the mailfile 
													 * owner is not the organizer of except when the entry is a broadcast.  In that case it
													 * is treated as a CAL_PROCESS_DELETE.
													 * It is treated as a CAL_PROCESS_DELETE if the entry is a non-meeting */
#define CAL_PROCESS_CANCEL				0x00000400	/* This will cancel a meeting that the mailfile owner is the organizer of */


#define CAL_PROCESS_UPDATEINVITEES		0x00002000	/* This will update the invitee lists on the specified entry (or entries) to include or remove
													 * those users specified in lists contained in the EXT_CALACTION_DATA::pAddNames and 
													 * EXT_CALACTION_DATA::pRemoveNames values */


/* Flags that control behavior of the CalNoticeAction and CalEntryAction calendar APIs
 * CAL_ACTION _### values are used to provide additional processing control to some actions taken by CalNoticeAction and CalEntryAction */

#define CAL_ACTION_DO_OVERWRITE_CHECK			0x00000001	/* Indicates that a check should be performed when processing the action to determine 
													 		* if an overwrite of invitee changes to the entry will occur. */
#define CAL_ACTION_UPDATE_ALL_PARTICIPANTS		0x00000002	/* New in 9.01 release.  Used to indicate that current entry participants should be notified of changes
															 * to the participant list in addition to those being added or removed. */

// Additional data required to perform some actions
typedef struct EXT_CALACTION_DATA
{
	WORD wLen;						// MUST be sizeof(EXT_CALACTION_DATA) - allows for safe expansion of struct in the future
	char* pszDelegateTo;			// Required for dwAction: CAL_PROCESS_DELEGATE - disregarded otherwise
	TIMEDATE* ptdChangeToStart;		// Desired new start date/time.  Required for dwAction: CAL_PROCESS_COUNTER - disregarded otherwise
	TIMEDATE* ptdChangeToEnd;		// Desired new end date/time.  Required for dwAction: CAL_PROCESS_COUNTER - disregarded otherwise
	BOOL* pfKeepInformed;			// If populated for CAL_PROCESS_DELEGATE or CAL_PROCESS_DECLINE, used to inform the Chair if 
									// you want to keep informed.  
									// If populated for CAL_PROCESS_COUNTER, used to keep a placeholder entry on the Calendar.
									// Disregarded otherwise.  
									// NULL pointer means use default from user preferences.
	void* pReserved;				// RESERVED - MUST be NULL
	LIST* pAddNamesReq;				// List of users to add to the specified entry (or entries) as a Required attendee.  
									// MUST be NULL if not adding anyone as required.  Only used by CAL_PROCESS_UPDATEINVITEES.
	LIST* pAddNamesOpt;				// List of users to add to the specified entry (or entries) as an Optional attendee.  
									// MUST be NULL if not adding anyone as optional.  Only used by CAL_PROCESS_UPDATEINVITEES.
	LIST* pAddNamesFYI;				// List of users to add to the specified entry (or entries) as an FYI attendee.  
									// MUST be NULL if not adding anyone as FYI.  Only used by CAL_PROCESS_UPDATEINVITEES.
	LIST* pRemoveNames;				// List of users to remove from the specified entry (or entries).  
									// MUST be NULL if not removing anyone.  Only used by CAL_PROCESS_UPDATEINVITEES.
} *PEXT_CALACTION_DATA;

/**************************************************************************************************************************************
 * CalNoticeAction
 * Process a calendar notice.  This makes the appropriate modifications to the calendar entry and also sends appropriate notices out.
 *
 * Inputs:
 *		  DBHANDLE hDB			The database containing the notice to act on
 *		  NOTEID noteid			The noteid of the notice to act on
 *		  DWORD dwAction		The action to perform as defined in CAL_PROCESS_### values
 *		  char* pszComments		Comments to include on the outgoing notice(s) to organizer or participants (can be NULL)
 *		  pExtActionInfo		Conveys any additional information required to perform dwAction - NULL for actions that do
 *								not require additional information to perform, required for CAL_PROCESS_DELEGATE and CAL_PROCESS_COUNTER
 *		  DWORD dwFlags			Flags - (a CAL_ACTION _### value)
 *		  void* pCtx			RESERVED - MUST be NULL
 *
 * Outputs:
 *		  None
 *
 * Returns:
 *		  NOERROR on success
 *		  ERR_NULL_DBHANDLE			The database handle is NULL
 *		  ERR_INVALID_NOTE			The specified note is not a valid notice to act on
 *		  ERR_CALACTION_INVALID		The action requested is not valid for this entry
 *		  ERR_MISC_INVALID_ARGS		Unexpected arguments provided
 *		  ERR_CALACTION_OVERWRITE_DISALLOWED	The specified action would overwrite personal changes so it was not allowed
 *		  Error codes for failure cases TBD
 */
STATUS LNPUBLIC CalNoticeAction(DBHANDLE hDB, NOTEID noteID, DWORD dwAction, const char* pszComments, PEXT_CALACTION_DATA pExtActionInfo, DWORD dwFlags, void* pCtx);

/**************************************************************************************************************************************
 * CalNoticeActionUNID
 * Same as CalNoticeAction but takes a UNID input instead of a NOTEID input
 */
STATUS LNPUBLIC CalNoticeActionUNID(DBHANDLE hDB, UNID unid, DWORD dwAction, const char* pszComments, PEXT_CALACTION_DATA pExtActionInfo, DWORD dwFlags, void* pCtx);

/* Range values for actions on recurring entries */
#define RANGE_REPEAT_CURRENT	0		/* Modifying just this instance */
#define RANGE_REPEAT_ALL		1		/* Modifying all instances */
#define RANGE_REPEAT_PREV		2		/* Modifying current + previous */
#define RANGE_REPEAT_FUT		3		/* Modifying current + future */

/**************************************************************************************************************************************
 * CalEntryAction
 * Perform an action on a calendar entry.  For instance, change the response of an accepted meeting to counter or delegate.
 * This must be applied to meetings (with the exception of CAL_PROCESS_DELETE, which can be applied to any calendar entry).
 *
 * This makes the appropriate modifications to the invitee calendar and also sends appropriate notices out.
 *
 * Inputs:
 *		  DBHANDLE hDB			The database containing calendar entries to act on
 *		  char* pszUID			The UID of the entry to act on
 *		  char* pszRecurID		The RECURRENCE-ID of the instance to act on
 *									May be specified for recurring meetings (omission acts on all).  MUST be NULL for single meetings.
 *									Timezones not permitted (time values must be in UTC time)
 *		  DWORD dwAction		The action to perform as defined in CAL_PROCESS_### values
 *		  DWORD dwRange			RANGE_REPEAT_### as defined above (ignored for non-repeating entries).
 *		  char* pszComments		Comments to include on the outgoing notice(s) to organizer or participants (can be NULL).
 *		  pExtActionInfo		Conveys any additional information required to perform dwAction - NULL for actions that do
 *									not require additional information to perform, required for CAL_PROCESS_DELEGATE,
 *                                  CAL_PROCESS_DECLINE, CAL_PROCESS_COUNTER and CAL_PROCESS_UPDATEINVITEES
 *		  DWORD dwFlags			Flags - Only CAL_ACTION_UPDATE_ALL_PARTICIPANTS is allowed (and only for CAL_PROCESS_UPDATEINVITEES)
 *		  void* pCtx			RESERVED - MUST be NULL
 *
 * Outputs:
 *		  None
 *
 * Returns:
 *		  NOERROR on success
 *		  ERR_NULL_DBHANDLE			The database handle is NULL
 *		  ERR_MISC_INVALID_ARGS		Unexpected arguments provided
 *		  ERR_CALACTION_INVALID		The action requested is not valid for this entry
 *		  ERR_NO_CALENDAR_FOUND		Unable to find the entry because the required view does not exist in this database
 *		  ERR_NOT_FOUND				There are no entries that match the specified UID in the database
 *		  ERR_TDI_CONV				The recurrence ID specified cannot be interpreted
 *		  ERR_MISC_UNEXPECTED_ERROR	Unexpected internal error
 *		  Error codes for failure cases TBD
 */
STATUS LNPUBLIC CalEntryAction(DBHANDLE hDB, const char* pszUID, const char* pszRecurID, DWORD dwAction, DWORD dwRange, const char* pszComments, PEXT_CALACTION_DATA pExtActionInfo, DWORD dwFlags, void* pCtx);


/**************************************************************************************************************************************
 ***************** C SDK HELPER METHODS ***********************************************************************************************
 **************************************************************************************************************************************
 * Below code offers helper methods that are likely to help when integrating calendar APIs with other Notes/Domino C API capabilities *
 *************************************************************************************************************************************/

/**************************************************************************************************************************************
 * CalGetUIDfromNOTEID
 * This is a convenience method that returns a UID from a NOTEID.  NOTEID->UID is a many to one mapping since
 * one or several notes may represent a calendar entry (especially if it repeats) and its related notices.
 * As such, the UID output will be the same for all notes that refer to the same calendar entry.
 * This method may incur a note open, so there could be performance impact.
 *
 * Inputs:
 *		  DBHANDLE hDB			The database containing the note referenced by noteid
 *		  noteid				NOTEID of a calendar note
 *		  wLen					Length of pszRetUID buffer	(reccomended to be at least 64)
 *		  pReserved				RESERVED - MUST be NULL
 *		  dwFlags				Flags - none currently
 *		  pCtx					RESERVED - MUST be NULL
 * Outputs:
 *		  pszUID				Buffer to populate with the UID
 *
 * Returns:
 *		  NOERROR on success
 *		  ERR_NULL_DBHANDLE			The database handle is NULL
 *		  ERR_INVALID_NOTE			Note is not valid or is not a calendar note
 *		  ERR_MISC_INVALID_ARGS		Unexpected arguments provided
 *		  ERR_VALUE_LENGTH			The value is too long for the allocated buffer
 */
STATUS LNPUBLIC CalGetUIDfromNOTEID(DBHANDLE hDB, NOTEID noteid, char* pszUID, WORD wLen, void* pReserved, DWORD dwFlags, void* pCtx);

/**************************************************************************************************************************************
 * CalGetUIDfromUNID
 * This is a convenience method that returns a UID from a UNID.  UNID->UID is a many to one mapping since
 * one or several notes may represent a calendar entry (especially if it repeats) and its related notices.
 * As such, the UID output will be the same for all notes that refer to the same calendar entry.
 * This method may incur a note open, so there could be performance impact.
 *
 * Inputs:
 *		  DBHANDLE hDB			The database containing the note referenced by unid
 *		  unid					UNID of a calendar note
 *		  wLen					Length of pszRetUID buffer	(reccomended to be at least 64)
 *		  pReserved				RESERVED - MUST be NULL
 *		  dwFlags				Flags - none currently
 *		  pCtx					RESERVED - MUST be NULL
 * Outputs:
 *		  pszUID				Buffer to populate with the UID
 *
 * Returns:
 *		  NOERROR on success
 *		  ERR_NULL_DBHANDLE			The database handle is NULL
 *		  ERR_INVALID_NOTE			Note is not valid or is not a calendar note
 *		  ERR_MISC_INVALID_ARGS		Unexpected arguments provided
 *		  ERR_VALUE_LENGTH			The value is too long for the allocated buffer
 */
STATUS LNPUBLIC CalGetUIDfromUNID(DBHANDLE hDB, UNID unid, char* pszUID, WORD wLen, void* pReserved, DWORD dwFlags, void* pCtx);

/**************************************************************************************************************************************
 * CalGetRecurrenceID
 * This is a convenience method that returns a RECURRENCE-ID (in UTC time) from a TIMEDATE object.
 * Inputs:
 *		  TIMEDATE tdInput		Input time/date object
 *		  WORD wLenRecurId		Length of pszRecurID buffer
 * Outputs:
 *		  char* pszRecurID		Buffer to populate with the reuccence-ID representation
 *
 * Returns:
 *		  NOERROR on success
 *		  ERR_MISC_INVALID_ARGS		Unexpected arguments provided
 *		  ERR_VALUE_LENGTH			The value is too long for the allocated buffer
 */
STATUS LNPUBLIC CalGetRecurrenceID(TIMEDATE tdInput, char* pszRecurID, WORD wLenRecurId);


																// if not, open with old method.

/**************************************************************************************************************************************
 * CalGetApptunidFromUID
 * This is a convenience method that returns an Apptunid value that corresponds to a UID.
 * The pszApptunid buffer MUST be allocated by the caller and a minimum of 33 bytes long.  This method populates the buffer with
 * 32 bytes and a NULL terminator
*
 * Inputs:
 *		  char* pszUID			The input UID
 *		  char* pszApptunid		Allocated buffer for return value
 *		  DWORD dwFlags			MUST be 0
 *		  void* pCtx			MUST be NULL
 *
 * Returns:
 *		  NOERROR on success
 *		  ERR_MISC_INVALID_ARGS		Unexpected arguments provided
 *		  ERR_HDL_NULL				The UID value passed in is a Notes psuedo-UID generated by a ReadRange operation on a pre-9.0 template
 *										It only has meaning within that database and cannot be used with this API call.  
 */
STATUS LNPUBLIC CalGetApptunidFromUID(const char* pszUID, char* pszApptunid, DWORD dwFlags, void* pCtx);

// Flags that control behavior of the calendar APIs - Used when opening a note handle for calendar data
#define CAL_NOTEOPEN_HANDLE_NOSPLIT			0x00000001			// Used when getting a handle via CalOpenNoteHandle (Handy for read-only cases)
																// When a specific instance of a recurring entry is requested, the underlying note may represent multiple
																// instances.  Default behavior makes appropriate modifications so that the returned handle represents
																// a single instance (but this might cause notes to be created or modified as a side effect).
																// Using CAL_NOTEOPEN_HANDLE_NOSPLIT will bypass any note creations or modifications and return a note handle
																// that may represent more than a single instance on the calendar.

/**************************************************************************************************************************************
 * CalOpenNoteHandle
 * This is a method to get a note handle for an entry on the calendar.
 * The intent is that the note handle can be used to get information about an entry or instance or to write additional information to the
 * entry or instance (beyond what is defined in iCalendar and/or available in this API).
 * Is is the callers responsibility to close the note via NSFNoteClose.
 *
 * When opening a recurring entry, a valid recurrence ID MUST also be provided.  A note representing the single instance will be returned.
 * This might cause notes to be created or modified as a side effect.
 *
 * Inputs:
 *		  DBHANDLE hDB			The database containing the entry to open
 *		  char* pszUID			The UID of the entry to get a note handle for
 *		  char* pszRecurID		The RECURRENCE-ID of the instance to get a note handle for.  Timezones not permitted (time values must be in UTC time).
 *								NULL for single entries.  Must be present for recurring entries.
 *		  DWORD dwFlags			CAL_NOTEOPEN_### flags to control non-default behavior
 *									Supported: CAL_NOTEOPEN_HANDLE_NOSPLIT
 *		  void* pCtx			RESERVED - MUST be NULL
 *
 * Outputs:
 *		  NOTEHANDLE *rethNote	The returned open note handle of the calendar entry
 *
 * Returns:
 *		  NOERROR on success
 *		  ERR_NULL_DBHANDLE			The database handle is NULL
 *		  ERR_NO_CALENDAR_FOUND		Unable to find the entry because the required view does not exist in this database
 *		  ERR_NOT_FOUND				There are no entries that match the specified UID or UID/recurid in the database
 *		  ERR_MISC_INVALID_ARGS		Unexpected arguments provided
 *		  ERR_TDI_CONV				The recurrence ID specified cannot be interpreted
 *		  ERR_MISC_UNEXPECTED_ERROR	Unexpected internal error
 */
STATUS LNPUBLIC CalOpenNoteHandle(DBHANDLE hDB, const char* pszUID, const char* pszRecurID, NOTEHANDLE far *rethNote, DWORD dwFlags, void* pCtx);


#ifdef __cplusplus
}
#endif

#endif	// CAL_API_H

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


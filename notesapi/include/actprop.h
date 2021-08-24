
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

#ifndef ACTPROP_DEFS
#define ACTPROP_DEFS

/* Basic properties and types for customizable menu (button) actions */

#define ACTION_RUN_FORMULA				1
#define ACTION_RUN_SCRIPT				2
#define ACTION_RUN_AGENT				3
#define ACTION_OLDSYS_COMMAND			4
#define ACTION_SYS_COMMAND				5
#define ACTION_PLACEHOLDER				6
#define	ACTION_RUN_JAVASCRIPT			7
/* Current list of valid line styles.					*/
#define ACTION_LINE_SINGLE				1
#define ACTION_LINE_DOUBLE				2
#define ACTION_LINE_TRIPLE				3
#define ACTION_LINE_TWO					4

/*	Current list of border styles.					*/
#define ACTION_BORDER_NONE				0
#define ACTION_BORDER_MAX				1
#define ACTION_BORDER_VAR				2
#define ACTION_BORDER_ABS				3

#define ACTION_SET_3D_ONMOUSEOVER		0
#define ACTION_SET_3D_ALWAYS			1
#define ACTION_SET_3D_NEVER				2
#define ACTION_SET_3D_NOTES				3

#define ACTION_SET_ALIGN_BTN_TEXT_LEFT		0
#define ACTION_SET_ALIGN_BTN_TEXT_CENTER	1
#define ACTION_SET_ALIGN_BTN_TEXT_RIGHT		2

/* Action System Commands */
#define ACTION_SYS_CMD_CATEGORIZE			0x7c4e
#define ACTION_SYS_CMD_EDIT					0x0a02
#define ACTION_SYS_CMD_SEND					0x0a03
#define ACTION_SYS_CMD_FORWARD				0x0a04
#define ACTION_SYS_CMD_MOVE_TO_FOLDER		0x7c3d
#define ACTION_SYS_CMD_REMOVE_FROM_FOLDER	0x7c3e

// LI 8146.02
// New System Commands added
#define ACTION_SYS_CMD_MARK_SEL_READ		0x7c5e
#define ACTION_SYS_CMD_MARK_SEL_UNREAD		0x7c6e
#define ACTION_SYS_CMD_OPEN_SELECTED_NEWWND	0x7c7e
#define ACTION_SYS_CMD_FILE_PRINT			0x7c8e
#define ACTION_SYS_CMD_DELETE				0x7c9e
// Further system commands added here to make them more complete
#define ACTION_SYS_CMD_INFOBOX				0x7cae
#define ACTION_SYS_CMD_CUT					0x7cbe
#define ACTION_SYS_CMD_COPY					0x7cce
#define ACTION_SYS_CMD_COPY_LINK_DOC		0x7cde
#define ACTION_SYS_CMD_COPY_VIEW_TABLE		0x7cee
#define ACTION_SYS_CMD_PASTE				0x7cfe
#define ACTION_SYS_CMD_OPEN_SELECTED		0x7d0e
#define ACTION_SYS_CMD_BOOKMARK				0x7d1e


#endif /* ACTPROP_DEFS */

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif


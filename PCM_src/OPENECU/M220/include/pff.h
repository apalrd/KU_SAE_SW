/*
 *****************************************************************************
 *
 *  Project:        OpenECU
 *  Version:        $Id: pff.h 36332 2013-11-18 20:15:15Z cforhart $
 *  File:           $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/pff/pff.h $
 *  Description:    Public interface to the freeze frame freature.
 *
 *  Copyright (C) 2012 Pi Innovo
 *  This document (program) contains proprietary information
 *  which is the property of Pi Innovo
 *  The contents of this document (program) must not be copied
 *  or disclosed to a third party without the prior agreement
 *  of an authorised officer of Pi Innovo
 *
 *  Notes:          None
 *
 *****************************************************************************
 */

#ifndef PFF_H
#define PFF_H

/********* Includes *********/

#include "psy.h"
#include "pkn.h"
#include "pio.h"

/********* These macros can be changed *********/

/* None */

/********* These macros must not be changed *********/

/* The minimum size of a J1939 expanded freeze frame (DM25) in bytes. At the
 * very least this should hold the LEN,SPN,FMI, and the occurance count.
 */
#define PFF_MIN_J1939_DM25_MSG_SIZE ((U16) 5u)


/********* Global Structure Definitions *********/

/** Error values for debugging -- when an error is found when calling the
 *  freeze frame feature (PFF), the API calls a function with an enumeration
 *  from this type.
 *
 * \ingroup hl_interface
 */
typedef enum
{
    /** No error
     */
    PFF_OK                                         = 0,

    /** A freeze frame record held in the holding array has an invalid
     *  data length.
     */
    PFF_HOLDING_ARRAY_LEN_INVALID                  = 1,

    /** Holding array indexing error
     */
    PFF_HOLDING_ARRAY_INDEX_INVALID                = 2,

    /** Failure to capture freeze frame PID data
     */
    PFF_HOLDING_ARRAY_STRT_END_INVALID             = 3,

    /** Failure to capture freeze frame PID data
     */
    PFF_HOLDING_ARRAY_REC_DATA_INVALID             = 4,

    /** A stored freeze frame does not have a matching freeze frame definition
     */
    PFF_STORED_FF_DTC_INVALID                      = 5,

    /** Failure to read freeze frame ID from store freeze frame file
     */
    PFF_STORED_DTC_READ_FAILURE                    = 6,

    /** Failure to capture freeze frame PID data
     */
    PFF_CAPTURE_PID_DATA_FAILURE                   = 7,

    /** Stored freeze frames are not as expected when checked at startup.
     * Either duplicate FFNOs were detected, or FFNOs were found not to be
     * consecutive from 0.
     */
    PFF_STARTUP_FFNO_ERROR                         = 8,

    /** The amount of NVM used to store freeze frame data exceeds the limit
     * set by the application.
     */
    PFF_NVM_ALLOCATION_EXCEEDED                    = 9
}
PFF_ERROR_CODE_T;


/** This enumeration declares the different types of freeze frame available.
 * The order of these ENUMs must be maintained!
 *
 * \ingroup hl_interface
 */
typedef enum
{
    PFF_FIRST_TYPE          = 0,   /* for use in for loops */
    PFF_TYPE_J1939_STND     = 0,   /* J1939 standard freeze frame */
    PFF_TYPE_J1939_EXPN     = 1,   /* J1939 expanded freeze frame */
    PFF_LAST_J1939_TYPE     = 1,   /* Last J1939 type for J1939 only loops */
    PFF_TYPE_J1979          = 2,   /* J1979 freeze frame */
    PFF_TYPE_UDS_SNAPSHOT   = 3,   /* UDS Snapshot */
    PFF_NUM_TYPES           = 4,
    PFF_TYPE_UNDEFINED      = 5
}
PFF_TYPE_T;

/** This enumeration describes freeze frame support per DTC.
 * (bitfield functionality_supported of PFF_FF_CONST_T)
 *
 * \ingroup hl_interface
 */
typedef enum
{
    PFF_SUPPORT_NONE        = 0,  /* Additional FF support not present      */
    PFF_SUPPORT_J1939_STND  = 1,  /* J1939 Standard (DM4) FF supported      */
    PFF_SUPPORT_J1939_EXPN  = 2,  /* J1939 Expanded (DM25) FF supported     */
    PFF_SUPPORT_UDS_SS      = 4   /* UDS Snapshot supported                 */
}
PFF_SUPPORT_MAP_T;

/** This structure declares the constant data defining each freeze frame
 * type.
 *
 * \note The structure is private to the library and should not be used by the
 *       application. It is exposed as part of the API so that various arrays
 *       can be sized at build time to minimise the library memory footprint.
 */
typedef struct
{
    /** This bitfield identifies some of the freeze frame functionality supported. \n
     *  See PFF_SUPPORT_MAP_T.
     *
     * \ingroup hl_interface
     */
    U8 functionality_supported;

    /** Number of PIDs in associated J1979 freeze frame.
     *
     * \ingroup hl_interface
     */
    U8 j1979_num_pids;

    /** Pointer to a calibratable array of PID numbers used to define which PIDs are
     *  supported in this DTCs freeze frame.
     *  NULL if no J1979 freeze frames for this DTC.
     *
     * \ingroup hl_interface
     */
    const U8 *ff_pid_list_ptr;

    /** Number of manufacturer specified SPNs in J1939 freeze frame (DM4).
     *
     * \ingroup hl_interface
     */
    U8 j1939_num_manu_spns;

    /** Pointer to array of SPN numbers used to define which SPNs are supported in this DTCs
     *  freeze frame.
     *  NULL if no J1939 freeze frames for this DTC.
     *
     * \ingroup hl_interface
     */
    const U32 *ff_spn_list_ptr;

    /** Number of PIDs in associated UDS Snapshot.
     *
     * \ingroup hl_interface
     */
    U8 ss_num_pids;

    /** Pointer to array of ISO 16-bit pid numbers used to define which PIDs
     *  are supported in this DTCs snapshot.
     *  NULL if no UDS snapshots.
     *
     * \ingroup hl_interface
     */
    const U16 *ff_ss_pid_list_ptr;
}
PFF_FF_CONST_T;

/* This gives the severity of the DTC (dtc_sev) for which the FF is stored in the
 * temporary Tx buffer data list at given index ff_data_idx
 * Used in building the J1939 Tx message for DM4/ DM25.
 */
typedef struct
{
    PIO_EMISSION_SEV_TYPE_T  dtc_sev;
    U16                      ff_data_idx;
}
PFF_DTC_SEV_FF_INDEX_T;

/********* Global Prototypes *********/

extern void pff_client_task
(
    void
);

extern void pff_lock_holding_array
(
    void
);

extern void pff_unlock_holding_array
(
    void
);

/********* Global Variables *********/

/* None */

#endif /* PFF_H */


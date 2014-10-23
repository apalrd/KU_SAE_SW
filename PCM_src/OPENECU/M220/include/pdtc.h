/*****************************************************************************/
/**
 *  \file    pdtc.h
 *  \brief   Public interface to the diagnostic trouble code feature.
 *
 *  Version: $Id: pdtc.h 35178 2013-09-10 16:03:01Z jtough $
 *  File:    $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/pdtc/pdtc.h $
 */

/*  Copyright (C) 2010-2012 Pi Innovo
 *  This document (program) contains proprietary information
 *  which is the property of Pi Innovo
 *  The contents of this document (program) must not be copied
 *  or disclosed to a third party without the prior agreement
 *  of an authorised officer of Pi Innovo
 */

#ifndef PDTC_H
#define PDTC_H

/********* Includes *********/

#include "psy.h"
#include "pff.h"
#include "pio.h"

/********* These macros can be changed *********/

/** This macro defines the value for #pdtc_store when DTCs are to be
 * stored in battery backed RAM across power cycles.
 *
 * \ingroup c_interface
 */
#define PDTC_STORE_IN_BBRAM   0

/** This macro defines the value for #pdtc_store when DTCs are to be
 * stored in Flash across power cycles.
 *
 * \ingroup c_interface
 */
#define PDTC_STORE_IN_FLASH   1

/********* These macros must not be changed *********/

/* Lamp selection bit mapping for CARB DTC requirements
 *   Bits 0..1 : Protect lamp
 *   Bits 2..3 : Amber Warning Lamp (AWL)
 *   Bits 4..5 : Red Stop Lamp (RSL)
 *   Bits 6..7 : MIL
*/
#define PDTC_MIL_BITS                       ((U8)0xC0)
#define PDTC_RSL_BITS                       ((U8)0x30)
#define PDTC_AWL_BITS                       ((U8)0x0C)
#define PDTC_PROTECT_LAMP_BITS              ((U8)0x03)

/* Right-Shift needed to get to the bits corresponding to the lamps
 */
#define PDTC_SHIFT_TO_MIL_BITS              ((U8)6)
#define PDTC_SHIFT_TO_RSL_BITS              ((U8)4)
#define PDTC_SHIFT_TO_AWL_BITS              ((U8)2)
#define PDTC_SHIFT_TO_PROTECT_LAMP_BITS     ((U8)0)

/** Value for all lamps OFF
 *
 * \ingroup c_extdiag_interface
 */
#define PDTC_LAMPS_OFF                      ((U8)0xFF)

/* Bits for reporting DTC tables cleared via OBD request*/

/** Bit 0 set for reporting ISO-15765 emissions-related DTCs
 * cleared via ISO-15765 service $04 OBD request.
 * Reported by function #pdtc_check_table_cleared.
 *
 * \ingroup c_extdiag_interface
 */
#define PDTC_OBD_CLEAR_EMISSIONS_RELATED    ((U32)0x01)

/** Bit 1 set for reporting all ISO-15765 DTCs
 * cleared via ISO-15765 service $14 OBD request
 * (regardless of groupOfDTC option).
 * Reported by function #pdtc_check_table_cleared.

 *
 * \ingroup c_extdiag_interface
 */
#define PDTC_OBD_CLEAR_ALL                  ((U32)0x02)

/** Bit 2 set for reporting J1939 DTCs in Previously Active state
 * cleared via J1939 DM3 OBD request.
 * Reported by function #pdtc_check_table_cleared.
 *
 * \ingroup c_extdiag_interface
 */
#define PDTC_OBD_CLEAR_PREV_ACTIVE          ((U32)0x04)

/** Bit 3 set for reporting J1939 DTCs in Active state
 * cleared via J1939 DM11 OBD request.
 * Reported by function #pdtc_check_table_cleared.
 *
 * \ingroup c_extdiag_interface
 */
#define PDTC_OBD_CLEAR_ACTIVE               ((U32)0x08)

/** Value used to disable DTC transitions based on counters of
 * drive cycles or warm-up cycles.
 *
 * \ingroup c_extdiag_interface
 */
#define PDTC_DISABLE_COUNTER_TRANSITION     ((U8)0xFF)

/** Value used for DTC time_to_deactive and time_to_clear settings
 * to disable the DTC transitions from "Active" to "Previously Active"
 * or from from "Previously Active" to "Clear"
 * based on time with engine running and fault not present.
 *
 * \ingroup c_extdiag_interface
 */
#define PDTC_DISABLE_ENGINE_RUNNING_TRANSITION  ((U32)0xFFFFFFFF)

/********* Global Structure Definitions *********/

/** This enumeration declares the different types of DTCs available.
 *
 * \ingroup c_interface
 */
/* Essential to pack to minimise RAM cost of DTCs */
typedef PSY_PACKED enum
{
    /** The clear state for a DTC.
     */
    PDTC_STATE_CLEAR        = 0,

    /** The active state for a DTC.
     */
    PDTC_STATE_ACTIVE       = 1,

    PDTC_STATE_PREVIOUSLY_ACTIVE  = 2,
    /** The inactive (or CARB "previously active") state for a DTC.
     */
    PDTC_STATE_INACTIVE     = 2,  /* deprecated name */

    /** The pending state for a DTC.
     */
    PDTC_STATE_PENDING      = 3
}
PDTC_STATE_T;

/** Error values  -- when an error is found by the diagnostic
 * trouble code feature (PDTC), the feature calls a system error log function
 * with an enumeration from this type.
 *
 * \ingroup  c_interface
 */
typedef enum
{
    /** No error
     */
    PDTC_OK                                         = 0,

    /** Error raised if the DTC update function finds an invalid argument.
     */
    PDTC_UPDATE_INVALID_ARG                         = 1,

    /** Error raised if the DTC clear all function finds an invalid argument.
     */
    PDTC_CLEAR_ALL_INVALID_ARG                      = 2,

    /** Error raised if the DTC clear all if active function finds an invalid
     * argument.
     */
    PDTC_CLEAR_ALL_IF_ACT_INVALID_ARG               = 3,

    /** Error raised if the DTC clear all if inactive function finds an invalid
     * argument.
     */
    PDTC_CLEAR_ALL_IF_INACT_INVALID_ARG             = 4,

    /** Error raised if the DTC clear all if inactive function finds an invalid
     * argument.
     */
    PDTC_GET_DTC_STATUS_INVALID_ARG                 = 5,

    /** Error raised if the match exists function finds an invalid
     * argument.
     */
    PDTC_MATCH_EXISTS_INVALID_ARG                   = 6,

    /** Error raised if the match exists function finds an invalid
     * argument.
     */
    PDTC_CLEAR_DTCS_INVALID_ARG                     = 7,

    /** Error raised if function call not licensed
     */
    PDTC_BAD_LICENSE                                = 8
}
PDTC_ERROR_CODE_T;

/** This enumeration declares the different lamps which may
 * be controlled by DTC states, where certain types of lamp require
 * special reporting by on-board diagnostics.
 *
 * \ingroup c_extdiag_interface
 */
typedef enum
{
    /** This is the Protect lamp */
    PDTC_LAMP_PROTECT = 0,

    /** This is the Amber Warning lamp */
    PDTC_LAMP_AMBER_WARNING,

    /** This is the Red Stop lamp */
    PDTC_LAMP_RED_STOP,

    /** This is the MIL */
    PDTC_LAMP_MIL,

    /** Count number of lamp types supported */
    PDTC_NUM_LAMPS
}
PDTC_LAMP_T;

/** This enumeration declares all possible states for a lamp.
 *
 * \ingroup c_extdiag_interface
 */
typedef enum
{
    /** Slow flash (1Hz, 50% duty cycle) */
    PDTC_COMBINED_SLOW_FLASH = 0,

    /** Fast flash (2Hz or faster, 50% duty cycle) */
    PDTC_COMBINED_FAST_FLASH,

    /** Lamp on continuous */
    PDTC_COMBINED_ON,

    /** MIL only - lamp on, due to Short MIL ("short-MI" in WWH OBD) from class B DTC(s) active and lamp required to be on */
    PDTC_COMBINED_SHORT_MIL_ACTV_ON,

    /** MIL only - lamp off, due to Short MIL ("short-MI" in WWH OBD) from class B DTC(s) active and lamp required to be off */
    PDTC_COMBINED_SHORT_MIL_ACTV_OFF,

    /** MIL only - lamp off, due to Short MIL ("short-MI" in WWH OBD) from class B DTC(s) present but Short MIL sequence inactive */
    PDTC_COMBINED_SHORT_MIL_INACTIVE,

    /** MIL only - lamp on, due to WWH OBD Class C DTC(s) set and lamp required to be on for reporting */
    PDTC_COMBINED_CLASS_C_ACTIVE_ON,

    /** MIL only - lamp off, due to WWH OBD Class C DTC(s) set and lamp required to be off for reporting */
    PDTC_COMBINED_CLASS_C_ACTIVE_OFF,

    /** MIL only - lamp off, due to WWH OBD Class C DTC(s) set and reporting not in progress */
    PDTC_COMBINED_CLASS_C_INACTIVE,

    /** MIL only - lamp on, due to self-test in progress */
    PDTC_COMBINED_SELF_TEST_ON,

    /** MIL only - lamp off, due to self-test in progress */
    PDTC_COMBINED_SELF_TEST_OFF,

    /** Lamp off, no relevant DTCs set */
    PDTC_COMBINED_OFF
}
PDTC_COMBINED_LAMP_STATE_T;

/** This enumeration declares the comparison tests for a DTC's state.
 *
 * \ingroup c_extdiag_interface
 */
typedef enum
{
    /** Don't care */
    PDTC_IT_TYPE_DC,
    /** Contains */
    PDTC_IT_TYPE_CT
}
PDTC_IT_TYPE_COMPARATOR_T;

/** This enumeration declares the comparison tests for a DTC's emissions severity.
 *
 * \ingroup c_extdiag_interface
 */
typedef enum
{
    /** Don't care */
    PDTC_IT_ESEV_DC,
    /** Equals */
    PDTC_IT_ESEV_EQ,
    /** Not equal */
    PDTC_IT_ESEV_NE,
    /** Less than */
    PDTC_IT_ESEV_LT,
    /** Less than or equal */
    PDTC_IT_ESEV_LTE,
    /** Greater than */
    PDTC_IT_ESEV_GT,
    /** Greater than or equal */
    PDTC_IT_ESEV_GTE
}
PDTC_IT_ESEV_COMPARATOR_T;

/** This enumeration declares the comparison tests for a DTC's state.
 *
 * \ingroup c_extdiag_interface
 */
typedef enum
{
    /** Don't care */
    PDTC_IT_STATE_DC,
    /** Equals */
    PDTC_IT_STATE_EQ,
    /** Not equal */
    PDTC_IT_STATE_NE
}
PDTC_IT_STATE_COMPARATOR_T;

/** This structure declares the lamp state to be set for each DTC.  In future this
 * structure could readily be extended to support more lamps if customers require
 * it, but this is not currently supported.
 *
 * \ingroup c_extdiag_interface
 */
typedef struct
{
    /* Note that if this structure is extended in future, the order of these
     * elements should match the order of PDTC_LAMP_T
     */

    /** Protect lamp state when this DTC is set */
    PIO_DTC_LAMP_STATES_T lamp_protect_state;

    /** Amber warning lamp state when this DTC is set */
    PIO_DTC_LAMP_STATES_T lamp_amber_state;

    /** Red stop lamp state when this DTC is set */
    PIO_DTC_LAMP_STATES_T lamp_red_state;

    /** MIL state when this DTC is set */
    PIO_DTC_LAMP_STATES_T lamp_mil_state;
}
PDTC_LAMPS_SET_FOR_DTC_T;

/** This structure declares the run-time data to be stored with each DTC.
 *
 * \note The structure is private to the library and should not be used by the
 *       application. It is exposed as part of the API so that various arrays
 *       can be sized at build time to minimise the library memory footprint.
 *
 * \ingroup c_interface
 */
 /*im[LLR.PLAT.PDTC 5.5]*/
typedef struct
{
    /** This is the current state of the DTC. One of \p #PDTC_STATE_CLEAR,
     * \p #PDTC_STATE_ACTIVE, \p #PDTC_STATE_INACTIVE or \p #PDTC_STATE_PENDING.
     *
     * \ingroup c_interface
     */
    PDTC_STATE_T state;

    /** This is the (saturated) number of times the DTC has changed to the
     * \p #PDTC_STATE_ACTIVE state.
     * Range: [0, 127] counts - 0 to 126 (The value 127 is reserved for indicating not available)
     *
     * \ingroup c_interface
     */
    U8  count;

    /** This is a bit pattern of states for 4 lamps.
     *
     * Bits 7:6 correspond to the malfunction lamp, bits 5:4 correspond to the
     * red lamp, bits 3:2 correspond to the amber lamp and bits 1:0 correspond
     * to the protect lamp. The bit pattern for each lamp state is determined by
     * the J1939 specification.
     *
     * Note that this is only used by the legacy (deprecated) interface for
     * J1939 DTCs, to allow backwards compatibility for existing customers.
     *
     * \ingroup c_interface
     */
    U8  lamp_states;

    /** This keeps track of the number of drive cycles, and is used for different purposes
     * depending on the DTC state.\n
     *
     * On entry to "Pending" state, this is reset to zero.  On each subsequent drive cycle
     * where the test for this DTC is run and fails, the counter is incremented until the
     * limit is reached for transition to "Active" state.\n
     *
     * On entry to "Active" state, this is reset to zero.  If the test for this DTC runs and fails,
     * the counter is reset to zero.  On each subsequent drive cycle where the test for this DTC
     * is run and passed, and the test did not run and fail during the same drive cycle, the counter
     * is incremented until the limit is reached for transition to "Previously Active" state.
     *
     * \ingroup c_extdiag_interface
     */
    /* im[LLR.PLAT.PDTC 5.5] */
    U8  dtc_dc_count;

    /** This keeps track of the number of warm-up cycles.
     * This will be reset each time a DTC state transitions to Previously active state.
     * It will be incremented each subsequent warm up cycle that the fault is not present.
     *
     * \ingroup c_extdiag_interface
     */
    U8  dtc_wup_count;

    /** This keeps track of test status flags that are required to be stored over power
     * cycles, using individual bits to store/report each flag.\n
     *
     * Bit 0: Test run this drive cycle.
     *        Set to 1 if the test for the DTC has been run in the current drive cycle.
     *        Set to 0 on starting a new drive cycle.\n
     * Bit 1: Test failed this drive cycle.
     *        Set to 1 if the test for the DTC has failed in the current drive cycle.
     *        Set to 0 on starting a new drive cycle.\n
     * Bit 2: Test not completed.
     *        Set to 0 if the test for the DTC has been run since the last
     *        ClearDiagnostics request has been performed.\n
     *        Set to 1 when ClearDiagnostics request is serviced.
     * Bit 3: DTC previously active.
     *        Set to 1 if a DTC transitions from the "Previously Active" state to the
     *        "Pending" state as a result of a test failure occurring whilst the DTC is in the
     *        "Previously Active" state.
     *        Set to 0 if a DTC transitions from the "Clear" state to the "Pending" state
     *        as a result of a test failure occurring whilst the DTC is in the "Clear" state.\n
     * Bit 4: Permanent DTC OBD clear requested.
     *        Set to 0 on entry to "Active" state.
     *        Set to 1 if a DTC is permanent, the DTC is in the "Active" state,
     *        an OBD request to clear the DTC has been received,
     *        and test has not failed this drive cycle.
     *        Set to 0 if test runs and fails, or on the DTC leaving the "Active" state.\n
     * Bit 5: Permanent DTC ageing conditions met.
     *        Set to 0 on entry to "Active" state.
     *        Set to 1 if "Permanent DTC OBD clear requested" is set and vehicle/operating
     *        conditions to clear permanent DTC are met (by function
     *        pdtc_plat_obd_update_clr_perm_ok()).
     *        Set to 0 if test runs and fails.
     *
     * \ingroup c_extdiag_interface
     */
    U8 test_status_flags;

    /** This keeps track of the time left until derate will occur.
     * This parameter will only be applicable when the DTC attribute 'has_torque_derate'
     * is TRUE and DTC is in state ACTIVE.  In all other cases, this will be set
     * to the maximum value of 62.5 hours, as required for J1939 DM32.
     * Scaled as 1 bit = 1 minute.
     *
     * \ingroup c_extdiag_interface
     */
    U16 time_until_derate;

    /** This keeps track of the total time that the DTC is in state PREVIOUSLY_ACTIVE.
     * Scaled as 1 bit = 12 minutes (resolution 0.2hr/bit) with maximum value of 9600
     * hours, to minimise per-DTC non-volatile storage requirements.  This also meets
     * J1939 DM32 resolution requirement.
     *
     * \ingroup c_extdiag_interface
     */
    U16 total_prev_active_time;

    /** This keeps track of the total time that the DTC is in state ACTIVE.
     * Scaled as 1 bit = 12 minutes (resolution 0.2hr/bit) with maximum value of 9600
     * hours, to minimise per-DTC non-volatile storage requirements.  This also meets
     * J1939 DM32 resolution requirement.
     *
     * \ingroup c_extdiag_interface
     */
    U16 total_active_time;

    /** This keeps track of the time that the engine is running when the DTC is in states
     * ACTIVE and PREVIOUSLY_ACTIVE and the DTC's fault is not present.  This is used for
     * the time-based ageing/clearing of DTCs as per Euro regulations (directive 2005-78-EC
     * Annex IV section 3.9). Scaled as 1 bit = 12 minutes (resolution 0.2hr/bit) with maximum
     * value of 9600 hours, to minimise per-DTC non-volatile storage requirements.
     *
     * \ingroup c_extdiag_interface
     */
    U16 engine_running_time;
}
PDTC_DTC_NV_T;

/** This structure declares the variable data to be stored in RAM with each DTC
 * type.
 *
 * \note The structure is private to the library and should not be used by the
 *       application. It is exposed as part of the API so that various arrays
 *       can be sized at build time to minimise the library memory footprint.
 *
 * \ingroup c_extdiag_interface
 */
/* im[LLR.PLAT.PDTC 5.333] */
typedef struct
{
    /** This keeps track of test status flags that are not required to be stored over power
     * cycles, using individual bits to store/report each flag.
     *
     * Bit 3: Engine running timer is currently measuring time spent in "Active" state
     *        with engine running and DTC fault not present.
     *        Set to 1 when timer is running.
     *        Set to 0 when timer is not running.\n
     * Bit 4: Engine running timer is currently measuring time spent in "Previously Active" state
     *        with engine running and DTC fault not present.
     *        Set to 1 when timer is running.
     *        Set to 0 when timer is not running.\n
     * Bit 5: Test passed this ignition cycle.
     *        Set to 1 when test has been run and passed in the current ignition cycle.
     *        Set to 0 on starting a new ignition cycle.
     *        Only set when DTC is in "Previously Active" state.\n
     * Bit 6: DTC active this ignition cycle.
     *        Set to 1 when DTC state is "Active" in the current ignition cycle.
     *        Set to 0 on starting a new ignition cycle with DTC not in "Active" state.\n
     * Bit 7: Transient fault.
     *        Set to 1 when test is run and passed.
     *        Set to 0 when test is run and failed.
     *
     * \ingroup c_extdiag_interface
     */
    U8 test_status_flags;

    /** This increments every minute up to 60, when it resets back to zero, using
     * previous_time_stamp to track the time interval.  This timer allows updating
     * of time in "Active" or "Previously Active" states and time to derate at
     * appropriate intervals, without requiring storage of more data in NV.
     *
     * \ingroup c_extdiag_interface
     */
    U8 minutes_this_hour;

    /** This is the time stamp for computing time in states "Active" or "Previously Active"
     * - valid only when platform decides DTC states.  The time stamp can be used for
     * both, because the resolution used for timing in these states is such that any time
     * "lost" on a change between "Active" and "Previously Active" is not significant.
     *
     * \ingroup c_extdiag_interface
     */
    U32 previous_time_stamp;

    /** This is the time stamp for measuring the time spent in states "Active" or
     * "Previously Active" with the engine running and the DTC not set.
     *
     * \ingroup c_extdiag_interface
     */
    U32 engine_running_time_stamp;
}
PDTC_DTC_VAR_T;

/** This structure declares the constant data to be stored with each DTC
 * type.
 *
 * \note The structure is private to the library and should not be used by the
 *       application. It is exposed as part of the API so that various arrays
 *       can be sized at build time to minimise the library memory footprint.
 */
typedef struct
{
    /** This is the enumeration for a diagnostic trouble code.\n
     * Range: [1, 2]
     * \ingroup c_interface
     */
    /* May lose this type field in future */
    /* im[LLR.PLAT.PDTC 5.10] */
    PIO_DTC_TYPE_T type;

    /** This is the emission severity associated with a DTC. \n
     * Range: [0, 4]
     *
     * \ingroup c_extdiag_interface
     */
    /* Severity class */
    PIO_EMISSION_SEV_TYPE_T severity;

    /** This is the UDS $19 service severity field associated with a DTC. \n
     * Range: [0, 255]
     *
     * \ingroup c_extdiag_interface
     */
    PIO_DTC_UDS_SEV_T uds_severity;

    /** This is the suspect parameter number associated with a J1939 DTC. \n
     * Range: [0, 524287]
     *
     * \ingroup c_interface
     */
    U32 spn;

    /** This is the failure mode indicator associated with a J1939 DTC. \n
     * Range: [0, 31]
     *
     * \ingroup c_interface
     */
    U8  fmi;

    /** This is the conversion method associated with a J1939 DTC. \n
     * Range: [0, 1]
     *
     * \ingroup c_interface
     */
    U8  cm;

    /** This is the KW2000-3/ISO15031-6 ID to use for CAN OBD diagnostics. \n
     * Range: [0, 65535]
     * \ingroup c_extdiag_interface
     */
     /*im[LLR.PLAT.PDTC 5.9]*/
    U16  iso_16bit_id;

    /** This is a structure controlling the status of each lamp when this DTC is set.
     * If a lamp is unused in an application, its status should always be set to "off",
     * to avoid confusion if a non-existent lamp is reported as being "on".
     *
     * \ingroup c_extdiag_interface
     */
    PDTC_LAMPS_SET_FOR_DTC_T  lamps_set;

    /** This indicates whether the DTC is to be treated as permanent when it is "Active",
     * according to CARB regulations.
     *
     * \ingroup c_extdiag_interface
     */
    BOOL  permanent_storage;

    /** This indicates that a permanent DTC requires vehicle/operating conditions to be met
     * as specified by CARB (19711 section (d)(2.3.1)(C)(ii)b.) before the DTC may be cleared.
     * To meet CARB requirements, this should always be set for permanent DTCs reporting faults
     * for monitors that are not subject to minimum ratio requirements as specified by CARB
     * (19711 section (d)(3.2)).  Optionally, permanent DTCs reporting faults for monitors that
     * are subject to minimum ratio requirements may also require these conditions to be met.
     *
     * \ingroup c_extdiag_interface
     */
    BOOL requires_conditions_to_clear;

    /** This is the number of drive cycles required for a DTC in state 'Pending' to progress to state 'Active'.
     * This is valid only for DTCs whose state is controlled by the platform.  It is not used for DTCs whose state
     * is set directly by the legacy J1939/ISO-15765 interface.\n
     *
     * If set to zero, the DTC does not remain in state 'Pending' but immediately transitions to state 'Active'.
     *
     * \ingroup c_extdiag_interface
     */
    U8  dc_count_limit;

    /** This is the number of drive cycles required for a DTC in state 'Active' to progress to state 'Previously Active'.
     * This is valid only for DTCs whose state is controlled by the platform.  It is not used for DTCs whose state
     * is set directly by the legacy J1939/ISO-15765 interface.\n
     *
     * If set to zero, the DTC immediately transitions to state 'Previously Active' when the test runs and passes.\n
     *
     * If set to 255, the DTC will not transition to state 'Previously Active' based on drive cycles with the test passed.
     * This is not required by any current OBD legislation, but may be necessary for manufacturer-specific DTCs.\n
     *
     * If set to any other value, the DTC will transition from 'Active' to 'Previously Active'
     * either when the engine running time is reached OR when sufficient drive
     * cycles without faults are reached, whichever happens first.  See Directive
     * 2005-78-EC Annex IV section 3.8.1.
     *
     * \ingroup c_extdiag_interface
     */
    U8  error_free_dc_count_limit;

    /** This is the number of warm-up cycles required for a DTC in state 'Previously Active' to progress to state 'Clear'.\n
     *
     * If set to zero, the DTC does not remain in state 'Previously Active' but immediately transitions to state 'Clear'.\n
     *
     * If set to 255, the DTC will not transition to state 'Clear' based on warm-up cycles.  This
     * is required for permanent DTCs under Euro regulations, as per Directive
     * 2005-78-EC Annex IV section 3.9.2.\n
     *
     * If set to any other value, the DTC will transition from 'Previously Active' to 'Clear'
     * either when the engine running time is reached OR when sufficient warm-up
     * cycles without faults are reached, whichever happens first.  See Directive
     * 2005-78-EC Annex IV section 3.9.1.
     *
     * \ingroup c_extdiag_interface
     */
    U8  self_heal_wup_count_limit;

    /** This is a 4-bit code for the DTC's fault symptom.
     *
     *  0x0 = NONE\n
     *  0x1 = ABOVE_MAX\n
     *  0x2 = BELOW_MIN\n
     *  0x4 = NO_SIGNAL\n
     *  0x8 = INVALID_SIGNAL\n
     *
     *  The symptom for other values up to 0xF can be defined by the application
     *
     * \ingroup c_extdiag_interface
     */
    /* im[LLR.PLAT.PDTC 5.42] */
    U8  fault_symptom;

    /** This indicates whether the DTC is a 'non-erasable' DTC, as defined by
     * Euro regulations.
     *
     * \ingroup c_extdiag_interface
     */
   BOOL non_erasable;

   /** This indicates whether the DTC is a 'regulated exhaust level exceedance' DTC, as
    * required for constructing the J1939 DM32 message.
    *
    * \ingroup c_extdiag_interface
    */
    BOOL reg_exh_emission_lvl_exceedance;

    /** This indicates whether this DTC is required by the applicable OBD regulation
     *  to have a torque derate.
     *
     * \ingroup c_extdiag_interface
     */
    BOOL has_torque_derate;

    /** The number of hours (specified in seconds) the malfunction can be active until the OBD required derate will occur.
     *  This parameter will only be applicable when parameter 'has_torque_derate' is TRUE.\n
     *  Range [0, 62.5] hours i.e. [0, 225000] seconds
     *
     * \ingroup c_extdiag_interface
     */
    U32 time_to_derate;

    /** The number of hours (specified in seconds) with engine running and the fault not
     * present, in order for the DTC to transition from "Active" to "Previously Active".
     *
     * If set to 0xFFFFFFFF, this condition will never be checked.  Note that the
     * internal timer cannot store times greater than 0x02D00000 seconds, so any value
     * greater than this effectively amounts to disabling the condition.  If enabled,
     * typically this time will be set to 24 hours, as per Directive 2005-78-EC Annex IV
     * section 3.8.1.
     *
     * If this condition is enabled, the DTC will transition from "Active" to "Previously
     * Active" either when this engine running time is reached OR when sufficient drive
     * cycles without faults are reached, whichever happens first.  (See Directive
     * 2005-78-EC Annex IV section 3.8.1.)
     *
     * \ingroup c_extdiag_interface
     */
    U32 time_to_deactivate;

    /** The number of hours (specified in seconds) with engine running and the fault not
     * present, in order for the DTC to transition from "Previously Active" to "Clear".
     *
     * If set to 0xFFFFFFFF, this condition will never be checked.  Note that the
     * internal timer cannot store times greater than 0x02D00000 seconds, so any value
     * greater than this effectively amounts to disabling the condition.  If enabled,
     * typically this time will be set to 100 hours for non-permanent DTCs or 9600 hours
     * for permanent DTCs, as per Directive 2005-78-EC Annex IV sections 3.9.1 and 3.9.2.
     *
     * If this condition is enabled and the condition on warm-ups is enabled, the DTC
     * will transition from "Previously Active" to "Clear" either when this engine
     * running time is reached OR when sufficient warm-up cycles without faults are
     * reached, whichever happens first.  (See Directive 2005-78-EC Annex IV section 3.9.1.)
     *
     * \ingroup c_extdiag_interface
     */
    U32 time_to_clear;

    /** This points to the non-volatile storage structure for this DTC.  May not be NULL.
     *
     * \ingroup c_interface
     */
    PDTC_DTC_NV_T* nv_data;

    /** This points to the volatile (RAM) storage structure for this DTC.  May not be NULL.
     *
     * \ingroup c_interface
     */
    PDTC_DTC_VAR_T* var_data;

    /** This points to a freeze frame structure if this DTC has any associated freeze frames.
     *  May be NULL if no freeze frames associated with this DTC. Though this shall be defaulted
     *  to freeze frame ID 1.
     *
     * \ingroup c_extdiag_interface
     */
    const PFF_FF_CONST_T* freeze_frame;

}
PDTC_DTC_T;

/** This structure declares all per-DTC-table variable data.
 *
 * \note The structure is private to the library and should not be used by the
 *       application. It is exposed as part of the API so that various arrays
 *       can be sized at build time to minimise the library memory footprint.
 */
typedef struct
{
    /** This is an array of lamp states (sized by \a PDTC_NUM_LAMPS)
     * for all lamps whose status is set by DTCs in this table.
     *
     * \ingroup c_interface
     */
    PDTC_COMBINED_LAMP_STATE_T lamp_states[4];

    /** This stores whether emissions-related DTCs in the table have
     * recently been cleared using ISO service $04.
     *
     * \ingroup c_extdiag_interface
     */
    BOOL emissions_related_dtcs_cleared;

    /** This stores whether all DTCs in the table have
     * recently been cleared using ISO service $14.
     *
     * \ingroup c_extdiag_interface
     */
    BOOL all_dtcs_cleared;

    /** This stores whether previously active DTCs in the table have
     * recently been cleared using J1939 DM3 (by call to function
     * #pdtc_clear_all_if_inactive).
     *
     * \ingroup c_extdiag_interface
     */
    BOOL prev_active_dtcs_cleared;

    /** This stores whether previously active DTCs in the table have
     * recently been cleared using J1939 DM11 (by call to function
     * #pdtc_clear_all_if_active).
     *
     * \ingroup c_extdiag_interface
     */
    BOOL active_dtcs_cleared;
}
PDTC_TABLE_VAR_T;

/** This structure declares a table of DTCs.
 *
 * \note The structure is private to the library and should not be used by the
 *       application. It is exposed as part of the API so that various arrays
 *       can be sized at build time to minimise the library memory footprint.
 *
 * \ingroup c_interface
 */
/*im[LLR.PLAT.PDTC 5.1]*/
typedef struct
{
    /** This is the number of DTCs referenced by the table.
     * Range: [0, 65535] dtcs
     *
     * \ingroup c_interface
     */
    U16                       num_dtcs;

    /** This is the bit offset into #pj1939_state[] and #pj1939_sent[],
     * used to track the state of a DTC
     * for DM1 message transmit rules. The DTCs are allocated to
     * these arrays in a contiguous fashion per table.
     * Range: [0, 65535]
     *
     * \ingroup c_interface
     */
    U16                       dtc_offset;

    /** This is a pointer to an array of const pointers (sized by \a num_dtcs)
     * to DTCs referenced by this table.
     *
     * \ingroup c_interface
     */
    const PDTC_DTC_T *const * dtcs;

    /** This is a pointer to per-DTC-table variable data.
     *
     * \ingroup c_interface
     */
    PDTC_TABLE_VAR_T *per_table_data;
}
PDTC_TABLE_T;

/** Small "helper" structure used below.
 *
 * \note This is private to the library. DTCs are stored by their ID here
 *       so that if DTCs are altered between otherwise compatible builds,
 *       the references in non-volatile memory will still work. This would
 *       not be true of an array index or pointer. But this does necessitate
 *       a search for the corresponding DTC if it is needed.
 */
typedef struct
{
    U32            spn;
    U16            iso_16bit_id;
    PIO_DTC_TYPE_T type;
    U8             fmi;
}
PDTC_DTC_ID_T;

/** Used privately by the library to select which record is needed
 *  for some UDS $19 services
 */
typedef enum
{
    PDTC_FIRST_FAILED,
    PDTC_LATEST_FAILED,
    PDTC_FIRST_CONFIRMED,
    PDTC_LATEST_CONFIRMED,
    PDTC_NUM_FIRST_LAST
}
PDTC_FIRST_LAST_SELECT_T;


/********* Global Prototypes *********/

extern void pdtc_client_task
(
    void
);

extern void pdtc_commit_to_store
(
    void
);

extern BOOL pdtc_is_store_intact
(
    void
);

extern void pdtc_dtcs_modified
(
    void
);

extern PDTC_ERROR_CODE_T pdtc_clear_all_by_severity
(
    const PDTC_TABLE_T *const       pdtcf_table,
    const PIO_DTC_TYPE_T            pdtcf_type,
    const PIO_EMISSION_SEV_TYPE_T   pdtcf_emissions_min_sev
);

extern PDTC_ERROR_CODE_T pdtc_clear_all_tables
(
    const PIO_DTC_TYPE_T            pdtcf_type,
    const PIO_EMISSION_SEV_TYPE_T   pdtcf_emissions_min_sev
);

extern void pdtc_clear_all
(
    const PDTC_TABLE_T *const pdtcf_table,
    const PIO_DTC_TYPE_T      pdtcf_type
);

extern void pdtc_clear_all_if_active
(
    const PDTC_TABLE_T *const pdtcf_table,
    const PIO_DTC_TYPE_T      pdtcf_type
);

extern void pdtc_clear_all_if_inactive
(
    const PDTC_TABLE_T *const pdtcf_table,
    const PIO_DTC_TYPE_T      pdtcf_type
);

extern void pdtc_clear_dtcs
(
    const PDTC_TABLE_T *const           pdtcf_table,
    const PIO_DTC_TYPE_T                pdtcf_type,
    const PDTC_IT_TYPE_COMPARATOR_T     pdtcf_type_comparator,
    const PIO_EMISSION_SEV_TYPE_T       pdtcf_esev,
    const PDTC_IT_ESEV_COMPARATOR_T     pdtcf_esev_comparator,
    const PDTC_STATE_T                  pdtcf_state,
    const PDTC_IT_STATE_COMPARATOR_T    pdtcf_state_comparator,
    const BOOL                          pdtcf_clear_unconditionally
);

extern void pdtc_update_j1939_dtc
(
    const PDTC_DTC_T *const   pdtcf_dtc,
    U8                        pdtcf_active_in,
    U8                        pdtcf_lamp_bitmap,
    U8                       *pdtcf_active_out,
    U8                       *pdtcf_state,
    U8                       *pdtcf_count
);

extern PDTC_ERROR_CODE_T pdtc_get_dtc_status
(
    const PDTC_DTC_T *const   pdtcf_dtc,
    U8                       *pdtcf_lamp_bitmap,
    PDTC_STATE_T             *pdtcf_state,
    U8                       *pdtcf_count
);

extern BOOL pdtc_get_transient_dtc_status
(
    const PDTC_DTC_T *const   pdtcf_dtc
);

extern void pdtc_plat_obd_update_ign_cyc
(
    BOOL                    pdtcf_start_of_ignc
);

extern PDTC_ERROR_CODE_T pdtc_update_iso_dtc
(
    const PDTC_DTC_T *const   pdtcf_dtc,
    PDTC_STATE_T              pdtcf_state_in
);

extern PDTC_ERROR_CODE_T pdtc_update_plat_obd_dtc
(
    const PDTC_DTC_T *const   pdtcf_dtc,
    BOOL                      pdtcf_test_failed,
    BOOL                      pdtcf_test_completed
);
extern void pdtc_plat_obd_update_dc_count
(
    BOOL                      pdtcf_start_of_dc
);

extern void pdtc_plat_obd_update_wup_count
(
    BOOL                      pdtcf_start_of_wup
);

extern void pdtc_plat_obd_update_engine_running
(
    BOOL                    pdtcf_engine_is_running
);

extern void pdtc_plat_obd_update_clr_perm_ok
(
    BOOL                    pdtcf_ok_to_clear_perm
);

extern PIO_DTC_LAMP_STATES_T pdtc_get_lamp_state
(
    const PDTC_TABLE_T *const dtc_table,
    const PDTC_LAMP_T         lamp
);

extern PIO_DTC_LAMP_STATES_T pdtc_get_MIL_status
(
    void
);

extern PIO_DTC_LAMP_STATES_T pdtc_get_RSL_status
(
    void
);

extern PIO_DTC_LAMP_STATES_T pdtc_get_AWL_status
(
    void
);

extern PIO_DTC_LAMP_STATES_T pdtc_get_Protect_lamp_status
(
    void
);

extern U32 pdtc_check_table_cleared
(
    const PDTC_TABLE_T *const pdtcf_table_to_check
);

extern BOOL pdtc_match_exists
(
    const PDTC_TABLE_T *const       pdtcf_table,
    const PIO_DTC_TYPE_T            pdtcf_type,
    const PIO_EMISSION_SEV_TYPE_T   pdtcf_esev,
    BOOL                            pdtcf_esev_gte_test,
    const PDTC_STATE_T              pdtcf_state,
    U16                             *pdtcf_count
);

extern void pdtc_enable_periodic_lamp_updates
(
    BOOL pdtcf_en
);

/********* Global Variables *********/

/** This is the CRC checksum of the DTC store in non-volatile memory.
 *
 * The CRC checksum of the DTC store is updated prior to storing DTC
 * data in non-volatile memory when calling pdtc_commit_to_store().
 *
 * Range: [0, 65535] unitless
 *
 * \ingroup c_interface
 */
#pragma section DATA "" ".dtcs"
#pragma section SDATA "" ".dtcs"
extern U16 pdtc_nv_chksum;
#pragma section DATA
#pragma section SDATA

/** This defines which memory type will be used to store non-volatile
 * DTCs.
 *
 * If set to #PDTC_STORE_IN_BBRAM then DTCs are stored in battery backed
 * RAM, and if set to #PDTC_STORE_IN_FLASH then the DTCs are stored in
 * Flash.
 *
 * \warning Some memory stores are not implemented on some target ECUs.
 *          See the technical specification of the ECU to determine if
 *          the store type is available.
 *
 * \ingroup c_interface
 */
extern const U8 pdtc_store;

/** This calibration selects the lamp priority system used to select the
 * desired state for a lamp when multiple DTCs are active and request
 * different states.  If TRUE, flashing states take priority, giving the
 * order (highest to lowest) of: fast flash, slow flash, continuous on, off.
 * If FALSE, continuous on takes priority over flashing states, giving the order
 * (highest to lowest) of: continuous on, fast flash, slow flash, off.
 *
 * Care must be taken to ensure that DTC lamp states, in combination with the
 * priority system selected and the effects of the fault which caused the DTC,
 * meet any relevant OBD regulations.  For instance, CARB requires
 * emissions-related faults to set the MIL continuous-on during a drive cycle,
 * and do not permit the MIL to flash during a drive cycle if emissions-related
 * faults are active.
 *
 * \ingroup c_extdiag_interface
 */
extern const BOOL pdtc_lamp_flashing_is_priority;

/** This calibration selects the DTC state behaviour when a fault recurs whilst the
 * DTC is in the "previously active" state.  This behaviour is not specified by
 * CARB (and hence is also unspecified in CARB-derived OBD schemes), so the
 * desired behaviour will be manufacturer-specific.
 *
 * If this calibration is TRUE, the DTC will transition from the "previously active"
 * state to the "pending" state when a fault recurs.  If the fault remains set, the
 * DTC will transition to "active" as normal.  If the fault does not recur, the DTC
 * will transition back to the "previously active" state, and will clear all aging
 * counters so that aging is restarted.
 *
 * If this calibration is FALSE, the DTC will transition directly from the "previously
 * active" state to the "active" state when a fault recurs.
 *
 * \ingroup c_extdiag_interface
 */
/* im[LLR.PLAT.PDTC 5.33] */
extern const BOOL pdtc_transition_prev_act_to_pend;

/** This is the total number of DTC tables the library will maintain.
 *
 * \ingroup c_interface
 */
extern const U16 pdtc_num_dtc_tables;

/** This is a list of the DTC tables the library will maintain.
 *
 * \ingroup c_interface
 */
extern const PDTC_TABLE_T *const pdtc_table_list[];

/** This is a table of all DTCs defined in the system.  It is
 * private to the library and should not be used by the application.
 * It is exposed as part of the API so that various arrays can be
 * sized at build time to minimise the library memory footprint.
 *
 * This table is intended to group all const/NV data for all DTCs, so
 * that operations on all DTCs can be carried out without the risk of
 * carrying out these operations multiple times on DTCs that are
 * referenced by multiple tables.
 *
 * This table is not intended to be used for carrying out lamp state
 * checks or other per-table operations.  Since this is the case,
 * no per-table data exists for this table.
 *
 * \ingroup c_extdiag_interface
 */
extern const PDTC_TABLE_T pdtc_table_all;

/** Records first/most recent DTCs for certain $19 UDS services */
#pragma section DATA "" ".dtcs"
#pragma section SDATA "" ".dtcs"
extern PDTC_DTC_ID_T pdtc_first_last_record[PDTC_NUM_FIRST_LAST];
#pragma section DATA
#pragma section SDATA

#endif /* PDTC_H */

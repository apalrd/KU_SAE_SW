/*****************************************************************************/
/**
 *  \file    pcfg.h
 *  \brief   Public interface to the target ECU configuration (PCFG) feature.
 *
 *  Version: $Id: pcfg.h 34569 2013-07-23 22:08:10Z rdoebler $
 *  File:    $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/pcfg/pcfg.h $
 */

/*  Copyright (C) 2012 Pi Innovo
 *  This document (program) contains proprietary information
 *  which is the property of Pi Innovo
 *  The contents of this document (program) must not be copied
 *  or disclosed to a third party without the prior agreement
 *  of an authorised officer of Pi Innovo
 */

#ifndef PCFG_H
#define PCFG_H

/********* Includes *********/

#include "psy.h"

#include "pio.h"

/********* These macros can be changed *********/

/* None */

/********* These macros must not be changed *********/

/* None */

/********* Global Structure Definitions *********/

/** An enumerated type which contains success and failure codes returned by some
 * ECU configuration feature (PCFG) functions.
 *
 * \ingroup  c_interface
 */
typedef enum
{
    /** Return code if everything progressed as expected.
     */
    PCFG_RC_OK,

    /** Return code if the desired sample rate is too low.
     */
    PCFG_RC_SAMPLE_RATE_TOO_LOW,

    /** Return code if the desired sample rate is too high.
     */
    PCFG_RC_SAMPLE_RATE_TOO_HIGH,

    /** Return code if an internal error occurred which was the result of a
     * software error.
     */
    PCFG_RC_INVALID_CHAN,

    /** Return code if at least one of the arguments relating to the HEGO filter
     * selection could not be used.
     */
    PCFG_RC_BAD_ARGS_HEGO,

    /** Return code if at least one of the arguments relating to the pin type
     * selection could not be used (G850, M460 and U82).
     */
    PCFG_RC_BAD_ARGS_TYPE,

    /** Return code if at least one of the arguments relating to the pin hysteresis
     * selection could not be used (G850).
     */
    PCFG_RC_BAD_ARGS_HYST,

    /** Return code if at least one of the arguments relating to the spark nominal current-trip
     * selection could not be used (G850).
     */
    PCFG_RC_BAD_ARGS_NOM_CT,

    /** Return code if at least one of the arguments relating to the spark maximum current-trip
     * selection could not be used (G850).
     */
    PCFG_RC_BAD_ARGS_MAX_CT,

    /** Return code if at least one of the arguments relating to the current-trip
     * selection or current threshold could not be used (M460, M461 and U82).
     */
    PCFG_RC_BAD_ARGS_INJ_CT,

    /** Return code if at least one of the arguments relating to the PWM clock
     * selection could not be used (U82).
     */
    PCFG_RC_BAD_ARGS_PWM_CLK
}
PCFG_RC_T;

/********* Global Prototypes *********/

#if defined(CFG_G850)
extern PCFG_RC_T pcfg_setup_g850
(
    PIO_CFG_HEGO_FILTER_T       pcfgf_hego_filter_e28_e29,
    PIO_CFG_SIGNAL_TYPE_T       pcfgf_type_t15,
    PIO_CFG_SIGNAL_TYPE_T       pcfgf_type_t4,
    PIO_CFG_SIGNAL_TYPE_T       pcfgf_type_t3,
    PIO_CFG_SIGNAL_TYPE_T       pcfgf_type_e45,
    PIO_CFG_SIGNAL_TYPE_T       pcfgf_type_e44,
    PIO_CFG_SIGNAL_HYST_T       pcfgf_hyst_t15,
    PIO_CFG_SIGNAL_HYST_T       pcfgf_hyst_t4,
    PIO_CFG_SIGNAL_HYST_T       pcfgf_hyst_t3,
    PIO_CFG_SIGNAL_HYST_T       pcfgf_hyst_e45,
    PIO_CFG_SIGNAL_HYST_T       pcfgf_hyst_e44,
    PIO_CFG_SPARK_NOM_T         pcfgf_nom_level,
    PIO_CFG_SPARK_MAX_T         pcfgf_max_level
);
#endif

#if defined(CFG_M250)
extern PCFG_RC_T pcfg_setup_m250
(
    PIO_CFG_OUTPUT_TYPE_T       pcfgf_output_type_a32,
    PIO_CFG_CURRENT_TRIP_T      pcfgf_current_trip_level_a32,
    PIO_CFG_OUTPUT_TYPE_T       pcfgf_output_type_a33,
    PIO_CFG_CURRENT_TRIP_T      pcfgf_current_trip_level_a33,
    PIO_CFG_OUTPUT_TYPE_T       pcfgf_output_type_a34,
    PIO_CFG_CURRENT_TRIP_T      pcfgf_current_trip_level_a34
);

extern PCFG_RC_T pcfg_imu_rate
(
    PIO_CFG_SAMPLE_RATE_CHAN_T pcfgf_chan,
    U16                        pcfgf_sample_rate
);
#endif

#if defined (CFG_U82)
extern PCFG_RC_T pcfg_setup_u82
(
    PIO_CFG_OUTPUT_TYPE_T            pcfgf_output_type_a13,
    F32                              pcfgf_peak_current_a13,
    F32                              pcfgf_hold_current_a13,
    PIO_CFG_OUTPUT_TYPE_T            pcfgf_output_type_a14,
    F32                              pcfgf_peak_current_a14,
    F32                              pcfgf_hold_current_a14,
    PIO_CFG_PWM_CLOCK_SELECT_T       pcfgf_clock_select_a13,
    PIO_CFG_PWM_CLOCK_SELECT_T       pcfgf_clock_select_a14,
    PIO_CFG_PWM_CLOCK_SELECT_T       pcfgf_clock_select_a15,
    PIO_CFG_PWM_CLOCK_SELECT_T       pcfgf_clock_select_a16,
    PIO_CFG_PWM_CLOCK_SELECT_T       pcfgf_clock_select_a17,
    PIO_CFG_PWM_CLOCK_SELECT_T       pcfgf_clock_select_a45,
    PIO_CFG_PWM_CLOCK_SELECT_T       pcfgf_clock_select_a46
);
#endif

#if defined(CFG_M460)
#if !defined(CFG_DONT_USE_DEPRECATED)
/* Deprecated, see pcfg_setup_m460(). */
extern void pcfg_softswitch_m460
(
    BOOL pcfgf_softswitch_state
);
#else
#define pcfg_softswitch_m460(pcfgf_softswitch_state) pcfg_softswitch_m460_is_deprecated_see_user_guide()
#endif

extern PCFG_RC_T pcfg_setup_m460
(
    PIO_CFG_OUTPUT_TYPE_T       pcfgf_output_type_a31,
    PIO_CFG_CURRENT_TRIP_T      pcfgf_current_trip_level_a31
);
#endif

/********* Global Variables *********/

/* None */

#endif /* PCFG_H */

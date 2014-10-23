/*****************************************************************************/
/**
 *  \file    pdx.h
 *  \brief   Public interface to the digital output feature.
 *
 *  Version: $Id: pdx.h 33655 2013-05-14 19:12:30Z sborders $
 *  File:    $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/pdx/pdx.h $
 */

/*  Copyright (C) 2012 Pi Innovo
 *  This document (program) contains proprietary information
 *  which is the property of Pi Innovo
 *  The contents of this document (program) must not be copied
 *  or disclosed to a third party without the prior agreement
 *  of an authorised officer of Pi Innovo
 */

#ifndef PDX_H
#define PDX_H

/********* Includes *********/

#include "psy.h"

/********* These macros can be changed *********/

/* None */

/********* These macros must not be changed *********/

/* None */

/********* Global Structure Definitions *********/

/** This declares a type with enough value range to represent all logical
 * channels for all targets. See \e pio.h for a list of relevant channels for a
 * specific target.
 *
 * \ingroup  c_interface
 */
typedef U16 PDX_LCHAN_T;

/** This declares a type with enough value range to represent logical peak and hold
 * injector channels for all targets. See \e pio.h for a list of relevant channels
 * for a specific target.
 *
 * \ingroup  c_interface
 */
typedef U8 PDX_LCHAN_PHINJ_T;

/** This declares a type with enough value range to represent logical H-Bridge
 * channel groups for all targets. See \e pio.h for a list of relevant channels
 * for a specific target.
 *
 * \ingroup  c_interface
 */
typedef U16 PDX_LCHAN_HBRIDGE_T;

/** An enumerated type which contains success and failure codes returned by some
 * digital input feature (PDX) functions.
 *
 * \ingroup  c_interface
 */
typedef enum
{
    /** Return code if everything progressed as expected.
     */
    PDX_RC_OK,

    /** Return code if an internal error occurred which was the result of a
     * software error.
     */
    PDX_RC_SW_ERROR,

    /** Return code if a hardware error occurred which stopped a channel being
     * sampled or actuated.
     */
    PDX_RC_HW_ERROR,

    /** Return code if at least one of the arguments could not be used.
     */
    PDX_RC_BAD_ARGS,

    /** Return code if frequency argument is too low.
     */
    PDX_RC_FREQ_TOO_LOW,

    /** Return code if frequency argument is too large.
     */
    PDX_RC_FREQ_TOO_HIGH,

    /** Return code if duty cycle argument is out of range, [0, 1].
     */
    PDX_RC_DUTY_OUT_OF_RANGE,

    /** Return code if could not allocate eTPU SDM for function (internal
     * error).
     */
    PDX_RC_SDM_ALLOC_ERROR,

    /** Return code if input or output device was unresponsive.
     */
    PDX_RC_INACTIVE,

    /** Return code if output not configured.
     */
    PDX_RC_NOT_CONFIGURED,

    /** Return code if mode is not supported.
     */
    PDX_RC_INVALID_MODE,

    /** Return code if peak-hold duty cycle is less than peak duty cycle.
     */
    PDX_RC_PEAK_HOLD_TOO_LOW
}
PDX_RC_T;

/** Error values for debugging -- when an error is found when calling the
 * digital input feature (PDX), the API calls a function with an enumeration
 * from this type.
 *
 * \ingroup  c_interface
 */
typedef enum
{
    /** Error raised if the channel 'n' cannot be used
     * as a digital output.\n
     * 'n' is (error_code - PDX_DO_CHANNEL_UNSUPPORTED).
     */
    PDX_DO_CHANNEL_UNSUPPORTED          = 1000,

    /** Error raised if the channel 'n' cannot be used
     * as a digital input.\n
     * 'n' is (error_code - PDX_DIG_IN_CHANNEL_UNSUPPORTED).
     */
    PDX_DIG_IN_CHANNEL_UNSUPPORTED      = 2001,

    /** Error raised if the channel 'n' cannot be used
     * as a frequency input.\n
     * 'n' is (error_code - PDX_FREQ_IN_CHANNEL_UNSUPPORTED).
     */
    PDX_FREQ_IN_CHANNEL_UNSUPPORTED     = 3001,

    /** Error raised if the channel 'n' cannot be used
     * as a period input.\n
     * 'n' is (error_code - PDX_PERIOD_IN_CHANNEL_UNSUPPORTED).
     */
    PDX_PERIOD_IN_CHANNEL_UNSUPPORTED   = 4001,

    /** Error raised if the quadrature and frequency input function has an
     * invalid argument.
     */
    PDX_QDEC_FREQ_IN_INVALID_ARG        = 5000,

    /** Error raised if the channel 'n' cannot be used
     * as a quadrature and frequency input.\n
     * 'n' is (error_code - PDX_QDEC_FREQ_IN_CHANNEL_UNSUPPORTED).
     */
    PDX_QDEC_FREQ_IN_CHANNEL_UNSUPPORTED = 5001,

    /** Error raised in quadrature and frequency input, if the primary channel
     * 'n' and the secondary channel are not on the same device.\n
     * 'n' is (error_code - PDX_TPU_QFI_CHANNEL_DEVICE_ERROR).
     */
    PDX_TPU_QFI_CHANNEL_DEVICE_ERROR    = 6000,

    /** Error raised if the quadrature input function has an invalid argument.
     */
    PDX_QDEC_IN_INVALID_ARG             = 7000,

    /** Error raised if the channel 'n' cannot be used
     * as a quadrature input.\n
     * 'n' is (error_code - PDX_QDEC_IN_CHANNEL_UNSUPPORTED).
     */
    PDX_QDEC_IN_CHANNEL_UNSUPPORTED     = 7001,

    /** Error raised in quadrature input, if the primary channel
     * 'n' and the secondary channel are not on the same device.\n
     * 'n' is (error_code - PDX_TPU_QI_CHANNEL_DEVICE_ERROR).
     */
    PDX_TPU_QI_CHANNEL_DEVICE_ERROR     = 8000,

    /** Error raised if the primary digital channel 'n' cannot be used
     * as a stepper motor output.\n
     * 'n' is (error_code - PDX_SMOT_CHANNEL_UNSUPPORTED).
     */
    PDX_SMOT_CHANNEL_UNSUPPORTED        = 9001,

    /** Error raised if the channel 'n' cannot be used
     * as a PWM output.\n
     * 'n' is (error_code - PDX_PWM_OUT_CHANNEL_UNSUPPORTED).
     */
    PDX_PWM_OUT_CHANNEL_UNSUPPORTED     = 10000,

    /** Error raised if the channel 'n' cannot be used
     * as a synchronised PWM output.\n
     * 'n' is (error_code - PDX_SYNC_PWM_OUT_CHANNEL_UNSUPPORTED).
     */
    PDX_SYNC_PWM_OUT_CHANNEL_UNSUPPORTED = 11000,

    /** Error raised in synchronised PWM output, if the primary channel
     * 'n' and the secondary channel are not on the same device.\n
     * 'n' is (error_code - PDX_TPU_SPO_CHANNEL_DEVICE_ERROR).
     */
    PDX_TPU_SPO_CHANNEL_DEVICE_ERROR    = 12000,

    /** Error raised if the channel 'n' cannot be used as a PWM input.\n
     * 'n' is (error_code - PDX_PWM_IN_CHANNEL_UNSUPPORTED).
     */
    PDX_PWM_IN_CHANNEL_UNSUPPORTED      = 13001,

    /** Error raised if the digital channel 'n' is not supported.\n
     * 'n' is (error_code - PDX_CHANNEL_INVALID).
     */
    PDX_CHANNEL_INVALID                 = 14000,

   /** Error raised if the channel 'n' cannot be used
     * as a stepped output.\n
     * 'n' is (error_code - PDX_SDOT_CHANNEL_UNSUPPORTED).
     */
    PDX_SDOT_CHANNEL_UNSUPPORTED        = 15000,

    /** Error raised if the channel 'n' cannot be used as a TLE-4953 input.\n
     * 'n' is (error_code - PDX_TLE4953_CHANNEL_UNSUPPORTED).
     */
    PDX_TLE4953_CHANNEL_UNSUPPORTED     = 16001,

    /** Error raised if the H-bridge mode has an invalid value.
     */
    PDX_HBRIDGE_INVALID_MODE            = 17000,

    /** Error raised if the H-bridge channels are not on the same device.
     */
    PDX_HBRIDGE_CHANNEL_MISMATCH        = 17001,

    /** Error raised if something went wrong when decoding a device and/or
     *  channel necessary for H-bridge operation.
     */
    PDX_HBRIDGE_DECODE_ERROR            = 17002,

    /** Error raised if channel group 'n' cannot be used as an H-bridge output.
     * 'n' is (error_code - PDX_HBRIDGE_CHANNEL_GROUP_UNSUPPORTED).
     */
    PDX_HBRIDGE_CHANNEL_GROUP_UNSUPPORTED = 17003
}
PDX_ERROR_CODE_T;

/** This enumeration gives the selectable signal patterns for a stepper motor
 * output.
 *
 * \ingroup  c_interface
 */
typedef enum
{
    /** Wave torque pattern.
     */
    PDX_SM_MODE_WAVE_TORQUE,

    /** Full torque pattern.
     */
    PDX_SM_MODE_FULL_TORQUE,

    /** Half torque pattern.
     */
    PDX_SM_MODE_HALF_TORQUE,

    /** Wave torque pattern (inverted).
     */
    PDX_SM_MODE_WAVE_TORQUE_INV,

    /** Full torque pattern (inverted).
     */
    PDX_SM_MODE_FULL_TORQUE_INV,

    /** Half torque pattern (inverted).
     */
    PDX_SM_MODE_HALF_TORQUE_INV,

    /* Must be last in the list, do not change. */
    PDX_SM_MODE_MAX
}
PDX_SM_MODE_T;

/** This enumeration gives the selectable modes for an H-bridge output.
 *
 * \ingroup  c_interface
 */
typedef enum
{
    /** No Drive.
     */
    PDX_UNI_NO_DRIVE,

    /** Brake. Both arms will be driven high.
     */
    PDX_UNI_BRAKE,

    /** Forward. Arm A will be held high, with PWM on low side of arm B.
     */
    PDX_UNI_FORWARD,

    /** Reverse. Arm B will be held high, with PWM on low side of arm A.
     */
    PDX_UNI_REVERSE,

    /* Must be last in the list, do not change. */
    PDX_HBRIDGE_MODE_MAX
}
PDX_HBRIDGE_MODE_T;

/********* Global Prototypes *********/

extern PDX_RC_T pdx_digital_input
(
    PDX_LCHAN_T   pdxf_lchan,
    U8           *pdxf_state,
    BOOL          pdxf_init
);

extern PDX_RC_T pdx_digital_output
(
    PDX_LCHAN_T   pdxf_lchan,
    U8            pdxf_state,
    BOOL          pdxf_init
);

extern PDX_RC_T pdx_frequency_input
(
    PDX_LCHAN_T   pdxf_lchan,
    U16           pdxf_config,
    U8            pdxf_count,
    F32          *pdxf_freq,
    U16           pdxf_last_edges,
    U16          *pdxf_this_edges,
    U32           pdxf_last_time,
    U32          *pdxf_this_time,
    U32           pdxf_timeout,
    BOOL         *pdxf_timed_out,
    BOOL          pdxf_init
);

extern PDX_RC_T pdx_period_input
(
    PDX_LCHAN_T   pdxf_lchan,
    F32          *pdxf_period_high,
    F32          *pdxf_period_low,
    U16           pdxf_last_edges,
    U16          *pdxf_edges,
    U32           pdxf_last_time,
    U32          *pdxf_time,
    U32           pdxf_timeout,
    BOOL         *pdxf_timed_out,
    BOOL          pdxf_init
);

extern PDX_RC_T pdx_phinj_output
(
    PDX_LCHAN_PHINJ_T pdxf_lchan_phinj,
    F32               pdxf_inj_freq,
    F32               pdxf_peak_duty,
    F32               pdxf_pkhold_duty,
    F32               pdxf_clock_freq,
    F32               pdxf_offset,
    BOOL              pdxf_init
);

extern PDX_RC_T pdx_pwm_input
(
    PDX_LCHAN_T   pdxf_lchan,
    U8            pdxf_invert,
    F32          *pdxf_freq,
    F32          *pdxf_dc,
    U32          *pdxf_first_duration,
    U32          *pdxf_second_duration,
    U32          *pdxf_period_count,
    U32           pdxf_timeout,
    U32          *pdxf_timeout_count,
    BOOL         *pdxf_timed_out,
    BOOL         *pdxf_pin_state,
    BOOL          pdxf_init
);

extern PDX_RC_T pdx_pwm_output
(
    PDX_LCHAN_T   pdxf_lchan,
    F32           pdxf_freq,
    F32           pdxf_duty,
    F32           pdxf_offset,
    BOOL          pdxf_init
);

extern PDX_RC_T pdx_quad_input
(
    PDX_LCHAN_T   pdxf_pri_lchan,
    PDX_LCHAN_T   pdxf_sec_lchan,
    U32           pdxf_last_edges,
    S32          *pdxf_delta_edges,
    U32          *pdxf_this_edges,
    BOOL          pdxf_init
);

extern PDX_RC_T pdx_quad_freq_input
(
    PDX_LCHAN_T   pdxf_pri_lchan,
    PDX_LCHAN_T   pdxf_sec_lchan,
    U8            pdxf_count,
    U32           pdxf_last_edges,
    S32          *pdxf_delta_edges,
    U32          *pdxf_this_edges,
    F32          *pdxf_pchan_freq,
    F32          *pdxf_schan_freq,
    U32           pdxf_pchan_last_edges,
    U32           pdxf_schan_last_edges,
    U32          *pdxf_pchan_edges,
    U32          *pdxf_schan_edges,
    U32           pdxf_pchan_last_time,
    U32           pdxf_schan_last_time,
    U32          *pdxf_pchan_time,
    U32          *pdxf_schan_time,
    F32           pdxf_timeout,
    BOOL         *pdxf_pchan_timed_out,
    BOOL         *pdxf_schan_timed_out,
    BOOL          pdxf_init
);

extern PDX_RC_T pdx_stepper_output
(
    PDX_LCHAN_T   pdxf_lchan,
    U8            pdxf_lchans,
    F32           pdxf_minrate,
    F32           pdxf_maxrate,
    U8            pdxf_steps,
    PDX_SM_MODE_T pdxf_mode,
    F32           pdxf_pos,
    BOOL          pdxf_stop,
    BOOL         *pdxf_moving,
    F32          *pdxf_steps_remaining,
    BOOL          pdxf_init
);

extern PDX_RC_T pdx_spwm_output
(
    PDX_LCHAN_T   pdxf_master_lchan,
    PDX_LCHAN_T   pdxf_slave_lchan,
    F32           pdxf_master_freq,
    F32           pdxf_master_duty,
    F32           pdxf_master_offset,
    F32           pdxf_slave_freq,
    F32           pdxf_slave_duty,
    U32           pdxf_slave_delay,
    BOOL          pdxf_init
);

extern PDX_RC_T pdx_stepped_output
(
    PDX_LCHAN_T  pdxf_lchan,
    U8           pdxf_lchans,
    U8           pdxf_pattern,
    F32          pdxf_step_rate,
    BOOL         pdxf_stop,
    U16         *pdxf_steps_cnt,
    U16         *pdxf_prev_pos,
    BOOL         pdxf_init
);

extern PDX_RC_T pdx_tle4953_input
(
    PDX_LCHAN_T  ptpuf_lchan,
    F32         *ptpuf_freq,
    U32         *ptpuf_high_duration,
    U16          ptpuf_last_pulses_l,
    U16          ptpuf_last_pulses_r,
    U16         *ptpuf_pulses_l,
    U16         *ptpuf_pulses_r,
    BOOL        *ptpuf_pulses_s,
    BOOL        *ptpuf_pulses_unknown,
    BOOL        *ptpuf_dir_init,
    BOOL        *ptpuf_dir_known,
    BOOL         ptpuf_clear_s_unk,
    U32          ptpuf_last_time,
    U32         *ptpuf_this_time,
    U32          ptpuf_timeout,
    BOOL        *ptpuf_timed_out,
    BOOL         pdxf_init
);

extern PDX_RC_T pdx_hbridge_output
(
    PDX_LCHAN_HBRIDGE_T pdxf_lchan_hbridge,
    PDX_HBRIDGE_MODE_T  pdxf_mode,
    F32                 pdxf_freq,
    F32                 pdxf_duty,
    PDX_HBRIDGE_MODE_T  *pdxf_last_mode_ptr,
    BOOL                pdxf_init
);

#if !defined(CFG_DONT_USE_DEPRECATED)
extern void pdx_set_input_update_rate
(
    PDX_LCHAN_T  pdxf_lchan
);
#else
#define pdx_set_input_update_rate(pdxf_lchan) pdx_set_input_update_rate_is_deprecated_see_user_guide()
#endif

#if !defined(CFG_DONT_USE_DEPRECATED)
extern void pdx_set_output_update_rate
(
    PDX_LCHAN_T  pdxf_lchan
);
#else
#define pdx_set_output_update_rate(pdxf_lchan) pdx_set_output_update_rate_is_deprecated_see_user_guide()
#endif

/********* Global Variables *********/

/* None */

#endif /* PDX_H */

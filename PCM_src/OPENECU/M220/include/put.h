/*****************************************************************************/
/**
 *  \file    put.h
 *  \brief   Public interface to the general utility feature.
 *
 *  Version: $Id: put.h 33447 2013-04-30 07:21:01Z cwartnaby $
 *  File:    $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/put/put.h $
 */

/*  Copyright (C) 2012 Pi Innovo
 *  This document (program) contains proprietary information
 *  which is the property of Pi Innovo
 *  The contents of this document (program) must not be copied
 *  or disclosed to a third party without the prior agreement
 *  of an authorised officer of Pi Innovo
 *
 *  Notes:          None.
 *
 *****************************************************************************
 */

#ifndef PUT_H
#define PUT_H

/********* Includes *********/

#include "psy.h"

/********* These macros can be changed *********/

/* None */

/********* These macros must not be changed *********/

/* The number of leaky buckets that we use in the enhanced
 * analogue input processing function.
 */
#define PUT_EPAI_NUM_LEAKY_BUCKETS  (5UL)
#define PUT_CRC_J1850_START_VALUE   (0xFF)

/********* Global Structure Definitions *********/

/** Error values for debugging -- when an error is found when calling the utility API (PUT),
 * the API calls a function with an enumeration from this type.
 *
 * \ingroup  c_interface
 */
typedef enum
{
    /** Error raised if the one of the table lookup and interpolation functions
     * find an invalid argument.
     */
    PUT_CALMAP_INVALID_ARG                          = 1,

    /** Error raised if the debounce-by-cycles functions find an invalid
     * argument.
     */
    PUT_DEBOUNCE_BY_CYCLES_INVALID_ARG              = 2,

    /** Error raised if one of the leaky bucket functions find an invalid
     * argument.
     */
    PUT_LEAKY_BUCKET_INVALID_ARG                    = 3,

    /** Error raised if one of the slew rate check functions find an invalid
     * argument.
     */
    PUT_SLEW_RATE_CHECK_INVALID_ARG                 = 4,

    /** Error raised if one of the range check functions find an invalid
     * argument.
     */
    PUT_RANGE_CHECK_INVALID_ARG                     = 5,

    /** Error raised if the debounce-by-time functions find an invalid argument.
     */
    PUT_DEBOUNCE_BY_TIME_INVALID_ARG                = 6,

    /** Error raised if the duty cycle processing function finds an invalid
     * argument.
     */
    PUT_DUTYCYCLE_PROCESSING_INVALID_ARG            = 7,

    /** Error raised if the state processing function finds an invalid
     * argument.
     */
    PUT_STATE_PROCESSING_INVALID_ARG                = 8,

    /** Error raised if the analog input filter function finds an invalid
     * argument.
     */
    PUT_ANALOG_INPUT_FILTER_INVALID_ARG             = 9
}
PUT_ERROR_CODE_T;

struct PUT_PAR_F32
{
    S32      error_value;
    S32      unavailable_value;
    F32      min_value;
    F32      max_value;
    F32      default_value;
    F64      scale_factor;
    F32      offset_value;
    U16      delay_cycles;
    U8       y_datatype;
    U8       is_booleanlogicsignals;
};

struct PUT_PAR_S32
{
    S32 error_value;
    S32 unavailable_value;
    S32 min_value;
    S32 max_value;
    S32 default_value;
    S32 scale_factor;
    S32 offset_value;
    U16 delay_cycles;
    U8  y_datatype;
    U8  is_booleanlogicsignals;
};

struct PUT_OUT_T
{
    void *y;
    void *invalid_flg;
    U8   *y_invalid_code;
};

struct PUT_VP_PAR_U8
{
    S32 error_value;
    S32 unavailable_value;
    U8  min_value;
    U8  max_value;
    U8  y_datatype;
    U8  u_datatype;
};

struct PUT_VP_PAR_S32
{
    S32 error_value;
    S32 unavailable_value;
    S32 min_value;
    S32 max_value;
    U8  y_datatype;
    U8  u_datatype;
};

struct PUT_VP_PAR_F32
{
    S32      error_value;
    S32      unavailable_value;
    F32      min_value;
    F32      max_value;
    F64      scale_factor;
    F32      offset_value;
    U8       y_datatype;
    U8       u_datatype;
};

/** This type provides storage for persistent information across
 * calls to the debounce-by-cycles function.
 */
typedef struct
{
    /** The state of the input last time the debounce function
     * was invoked. \n
     * Range: 0 or 1
     *
     * \ingroup c_interface
     */
    U8  last_state;

    /** The debounced steady state of the input. \n
     * Range: 0 or 1
     *
     * \ingroup c_interface
     */
    U8  steady_state;

    /** The number of cycles the input has been steady for. \n
     * Range: [0, 65535] cycles
     *
     * \ingroup c_interface
     */
    U16 cycle;
}
PUT_DEBOUNCE_CYCLE_T;

/** This type provides storage for persistent information across
 * calls to the debounce-by-time function.
 */
typedef struct
{
    /** Persistent accumulator used to set the debounced output state.
     *
     * \ingroup c_interface
     */
    F32 set_sum;

    /** Persistent accumulator used to reset the debounced output state.
     *
     * \ingroup c_interface
     */
    F32 reset_sum;

    /** Debounced output signal. \n
     * Range: 0 or 1
     *
     * \ingroup c_interface
     */
    U8 steady_state;
}
PUT_DEBOUNCE_TIME_T;

/** This type provides storage for persistent information across
 * calls to the leaky bucket function.
 */
typedef struct
{
    /** This is the level of the bucket for a given fault last time
     * the leaky bucket function was called for that fault.
     *
     * \ingroup c_interface
     */
    F32   bucket_level;

    /** True if the fault was confirmed last time the leaky bucket
     * function was called for that fault.
     *
     * \ingroup c_interface
     */
    BOOL  last_cff;
}
PUT_LEAKY_BUCKET_T;

/** This type provides storage for persistent information across
 * calls to the slew rate check function.
 */
typedef struct
{
    /** This is the value of the input last time the slew check function was
     * invoked.
     *
     * \ingroup c_interface
     */
    F32 last_input;

    /** True if the slew check function has not been called previously,
     * false otherwise.
     *
     * \ingroup c_interface
     */
    U8  first_call;
}
PUT_SLEW_RATE_CHECK_T;

/** Structure to hold values for the analogue input processing function that
 * requires persistence.
 */
typedef struct
{
    /** Last raw value read in by the analogue channel.
     *
     * This is used to establish if there is a slew rate fault on the input.
     * It is initialised to 0.0.
     *
     * \ingroup c_interface
     */
    F32 last_raw_value;

    /** Latched engineering value for transient faults.
     *
     * This is the last good engineering value output by the
     * analogue input before a transient fault is detected. This value is
     * output until the transient fault is no longer present.
     * It is initialised to 0.0.
     *
     * \ingroup c_interface
     */
    F32 latched_engineering_value;

    /** Flag to indicate if a confirmed fault has been detected
     *
     * This flag indicates if one or more transient faults have
     * persisted long enough to be registered as a confirmed fault
     * in the analogue input. A value of zero indicates that no fault is
     * present whilst a value of one indicates that a fault has been
     * detected. \n
     * Range: [0, 1] unitless flag
     *
     * \ingroup c_interface
     */
    U8 confirmed_fault_present;

    /** Flag to indicate the latched value of a transient fault flag
     *  for the raw value being greater than allowed.
     *
     * If a confirmed fault is detected, this flag indicates if the raw input
     * value was currently greater than the maximum allowed value at the time
     * the confirmed fault was detected. A value of 1 indicates the transient
     * fault was present at that time and 0 otherwise. It is initialised to
     * zero. \n
     * Range: [0, 1] unitless flag
     *
     * \ingroup c_interface
     */
    U8 latched_max_raw_range_tff;

    /** Flag to indicate the latched value of a transient fault flag
     *  for the raw value being less than allowed.
     *
     * If a confirmed fault is detected, this flag indicates if the raw input
     * value was currently less than the minimum allowed value at the time the
     * confirmed fault was detected. A value of 1 indicates the transient fault
     * was present at that time and 0 otherwise. It is initialised to zero. \n
     * Range: [0, 1] unitless flag
     *
     * \ingroup c_interface
     */
    U8 latched_min_raw_range_tff;

    /** Flag to indicate the latched value of a transient fault flag
     *  for the slew rate being greater than allowed.
     *
     * If a confirmed fault is detected, this flag indicates if the slew rate of
     * the raw input value was currently greater than the maximum allowed value
     * at the time the confirmed fault was detected. A value of 1 indicates the
     * transient fault was present at that time and 0 otherwise. It is
     * initialised to zero. \n
     * Range: [0, 1] unitless flag
     *
     * \ingroup c_interface
     */
    U8 latched_slew_rate_tff;

    /** Flag to indicate the latched value of a transient fault flag
     *  for the engineering value being greater than allowed.
     *
     * If a confirmed fault is detected, this flag indicates if the
     * engineering value was currently greater than the maximum allowed value at the time
     * the confirmed fault was detected. A value of 1 indicates the transient
     * fault was present at that time and 0 otherwise. It is initialised to zero. \n
     * Range: [0, 1] unitless flag
     *
     * \ingroup c_interface
     */
    U8 latched_max_eng_range_tff;

    /** Flag to indicate the latched value of a transient fault flag
     *  for the engineering value being less than allowed.
     *
     * If a confirmed fault is detected, this flag indicates if the
     * engineering value was currently less than the minimum allowed value at the time
     * the confirmed fault was detected. A value of 1 indicates the transient
     * fault was present at that time and 0 otherwise. It is initialised to zero. \n
     * Range: [0, 1] unitless flag
     *
     * \ingroup c_interface
     */
    U8 latched_min_eng_range_tff;

    /** Structure to handle slew rate input check.
     *
     * This structure contains the variable data required
     * by the slew rate check.
     *
     * \ingroup c_interface
     */
    PUT_SLEW_RATE_CHECK_T   slew_rate_data;

    /** Structure to handle leaky bucket fault filtering.
     *
     * This structure contains the variable data required
     * by the leaky bucket filtering.
     *
     * \ingroup c_interface
     */
    PUT_LEAKY_BUCKET_T      leaky_bucket_data;

}
PUT_ANALOGUE_WORKSPACE_T;

/** Structure to hold values for the analogue input processing function that
 * requires persistence.
 */
typedef struct
{
    /** Last raw value read in by the analogue channel.
     *
     * This is used to establish if there is a slew rate fault on the input.
     * It is initialised to 0.0.
     *
     * \ingroup c_interface
     */
    F32 last_raw_value;

    /** Latched engineering value for transient faults.
     *
     * This is the last good engineering value output by the
     * analogue input before a transient fault is detected. This value is
     * output until the transient fault is no longer present.
     * It is initialised to 0.0.
     *
     * \ingroup c_interface
     */
    F32 latched_engineering_value;

    /** Arrays to handle leaky bucket fault filtering.
     *
     * Note, memory is at a premium so we havent created
     * an array of PUT_LEAKY_BUCKET_T here as there is
     * excessive packing.
     *
     * \ingroup c_interface
     */
    F32 leaky_bucket_levels[PUT_EPAI_NUM_LEAKY_BUCKETS];
    U8  leaky_bucket_cffs[PUT_EPAI_NUM_LEAKY_BUCKETS];

    /** Structure to handle slew rate input check.
     *
     * This structure contains the variable data required
     * by the slew rate check.
     *
     * \ingroup c_interface
     */
    PUT_SLEW_RATE_CHECK_T   slew_rate_data;

}
PUT_ENH_ANALOGUE_WORKSPACE_T;

/** Structure to hold all items that are calibratable when calling
 * the analogue input processing function.
 */
typedef struct
{
    /** Minimum allowable raw value for the channel.
     *
     * Pointer to the minimum allowable value of the raw measurement.
     *
     * \ingroup c_interface
     */
    volatile const F32 *min_raw_value;

    /** Maximum allowable raw value for the channel.
     *
     * Pointer to the maximum allowable value of the raw measurement.
     *
     * \ingroup c_interface
     */
    volatile const F32 *max_raw_value;

    /** Number of elements in the engineering map table.
     *
     * Pointer to the number of elements in the lookup map that converts
     * the raw measurement into an engineering value.
     *
     * \ingroup c_interface
     */
    volatile const S32 *num_eng_lookup_elements;

    /** Engineering lookup table X Axis array.
     *
     * Pointer to the array that holds the x axis lookup values for converting
     * the raw measurement into an engineering value. These correspond to
     * a monotonically increasing or decreasing array of raw input values.
     *
     * \ingroup c_interface
     */
    volatile const F32 *eng_lookup_x_axis;

    /** Engineering lookup table Z Axis array.
     *
     * Pointer to the array that holds the z axis lookup values for converting
     * the raw measurement into an engineering value. These correspond to
     * a monotonically increasing or decreasing array of engineering output values.
     *
     * \ingroup c_interface
     */
    volatile const F32 *eng_lookup_z_axis;

    /** Minimum allowable engineering value for the channel.
     *
     * Pointer to the minimum allowable value of the engineering value that has been
     * derived from the raw value.
     *
     * \ingroup c_interface
     */
    volatile const F32 *min_eng_value;

    /** Maximum allowable engineering value for the channel.
     *
     * Pointer to the maximum allowable value of the engineering value that has been
     * derived from the raw value.
     *
     * \ingroup c_interface
     */
    volatile const F32 *max_eng_value;

    /** Leaky bucket rise rate for the channel.
     *
     * Pointer to the rise rate for the leaky bucket used for fault filtering.
     * This amount, multiplied by the sample rate for the channel, is added to the
     * leaky bucket contents each time a transient fault is present. The bucket is
     * clipped to a maximum value of 1.0.
     *
     * \ingroup c_interface
     */
    volatile const F32 *leaky_bucket_rise_rate;

    /** Leaky bucket fall rate for the channel.
     *
     * Pointer to the fall rate for the leaky bucket used for fault filtering.
     * This amount, multiplied by the sample rate for the channel, is subtracted from the
     * leaky bucket contents at each iteration of the function. The bucket is
     * clipped to a minimum value of 0.0.
     *
     * \ingroup c_interface
     */
    volatile const F32 *leaky_bucket_fall_rate;

    /** Leaky bucket value at which a confirmed fault is cleared.
     *
     * Pointer to the clear fault level for the leaky bucket fault filter.
     * Once a confirmed fault has been detected on the channel, the content
     * of the leaky bucket must fall to less than this value in order to clear
     * the fault. \n
     * Range: [0.0, 1.0] unitless
     *
     * \ingroup c_interface
     */
    volatile const F32 *leaky_bucket_fault_clear_level;

    /** The value output by the channel if a confirmed fault is present.
     *
     * Pointer to the engineering value that is output by the
     * filter logic as long as a confirmed fault is present. This can be
     * outside the range of the minimum and maximum engineering values used
     * to determine if a transient fault is present.
     *
     * \ingroup c_interface
     */
    volatile const F32 *default_output_value;

    /** The maximum slew rate allowed for the raw value.
     *
     * Pointer to the maximum allowed slew rate of the raw value.
     *
     * \ingroup c_interface
     */
    volatile const F32 *max_slew_rate;
}
PUT_ANALOGUE_CAL_DATA_T;

/********* Global Prototypes *********/

extern void put_value_validate_s32
(
    const U8                            putf_u_invalid_code,
    const S32                           putf_u,
    const struct PUT_PAR_S32 * const    putf_par,
    U16 * const                         delay_cycles,
    S32 * const                         y,
    const struct PUT_OUT_T * const      putf_out
);

extern void put_value_validate_f32
(
    const U8                            putf_u_invalid_code,
    const S32                           putf_u,
    const struct PUT_PAR_F32 * const    putf_par,
    U16 * const                         delay_cycles,
    F32 * const                         y,
    const struct PUT_OUT_T * const      putf_out
);

extern void put_value_preparation_u8
(
    const U8                            putf_invalid_code,
    U8                                  putf_u,
    const struct PUT_VP_PAR_U8 * const  putf_par,
    void * const                        putf_out
);

extern void put_value_preparation_s32
(
    const U8                            putf_invalid_code,
    S32                                 putf_u,
    const struct PUT_VP_PAR_S32 * const putf_par,
    void * const                        putf_out
);

extern void put_value_preparation_f32
(
    const U8                            putf_invalid_code,
    F32                                 putf_u,
    const struct PUT_VP_PAR_F32 * const putf_par,
    void * const                        putf_out
);

extern void put_cal_map_1d_f32
(
    F32                                 putf_x,
    S32                                 putf_n,
    volatile const F32          * const putf_px,
    volatile const F32          * const putf_pz,
    F32                                *putf_pzz
);

extern void put_cal_map_2d_f32
(
    F32                     putl_xx,
    F32                     putl_yy,
    S32                     putl_nx,
    S32                     putl_ny,
    volatile const F32     *putl_px,
    volatile const F32     *putl_py,
    volatile const F32     *putl_pz,
    F32                    *putl_pzz
);

extern U16 put_calc_crc
(
    U16                     putf_shift_reg,
    const U8               *putf_addr,
    U32                     putf_len
);

extern U8 put_calc_crc_j1850
(
    U8           putf_shift_reg,
    BOOL         putf_start,
    BOOL         putf_finish,
    const U8    *putf_addr,
    U32          putf_len
);

extern U16 put_calc_ipv4_checksum
(
    U16          putf_sum_reg,
    BOOL         putf_start,
    BOOL         putf_finish,
    const U8     *putf_addr,
    U32          putf_len
);

extern U8 put_debounce_by_cycles
(
    U8                            putf_input,
    U16                           putf_cycle_threshold,
    PUT_DEBOUNCE_CYCLE_T  * const putf_store
);

extern void put_debounce_by_cycles_init
(
    PUT_DEBOUNCE_CYCLE_T  * const putf_store
);

extern void put_debounce_by_time
(
    U8                      putf_raw_state,
    F32                     putf_sample_rate,
    U8                      putf_invert,
    F32                     putf_set_dead_time,
    F32                     putf_reset_dead_time,
    U8                     *putf_debounced_state,
    PUT_DEBOUNCE_TIME_T    *putf_channel_wrk_data
);

extern void put_debounce_by_time_init
(
    PUT_DEBOUNCE_TIME_T    *putf_channel_wrk_data
);

extern void put_dutycycle_processing
(
    F32                     putf_inp_duty_cycle,
    U8                      putf_invert,
    U8                      putf_fault,
    F32                     putf_default,
    F32                     putf_min,
    F32                     putf_max,
    F32                    *putf_out_duty_cycle
);

extern void put_leaky_bucket_init
(
    U32                         putf_n,
    PUT_LEAKY_BUCKET_T  * const putf_store
);

extern void put_leaky_bucket_f32
(
    F32                         putf_fall_rate,
    F32                         putf_rise_rate,
    F32                         putf_hyst,
    F32                         putf_delta_time,
    U32                         putf_n,
    volatile const F32  * const putf_tff,
    F32                 * const putf_cff,
    PUT_LEAKY_BUCKET_T  * const putf_store
);

extern void put_leaky_bucket_f64
(
    F32                     putf_fall_rate,
    F32                     putf_rise_rate,
    F32                     putf_hyst,
    F32                     putf_delta_time,
    U32                     putf_n,
    volatile const F64     *putf_tff,
    F64                    *putf_cff,
    PUT_LEAKY_BUCKET_T     *putf_store
);

extern void put_leaky_bucket_u8
(
    F32                     putf_fall_rate,
    F32                     putf_rise_rate,
    F32                     putf_hyst,
    F32                     putf_delta_time,
    U32                     putf_n,
    volatile const U8      *putf_tff,
    U8                     *putf_cff,
    PUT_LEAKY_BUCKET_T     *putf_store
);

extern void put_process_analog_input_init
(
    PUT_ANALOGUE_WORKSPACE_T      * const putf_adc_channel_wrk_data
);

extern void put_process_analog_input
(
    F32                                   putf_raw_adc_value,
    F32                                   putf_adc_sample_rate,
    F32                           * const putf_analogue_value,
    U8                            * const putf_confirmed_min_raw_range_fault,
    U8                            * const putf_confirmed_max_raw_range_fault,
    U8                            * const putf_confirmed_slew_rate_fault,
    U8                            * const putf_confirmed_min_eng_range_fault,
    U8                            * const putf_confirmed_max_eng_range_fault,
    U8                            * const putf_transient_fault_flag,
    const PUT_ANALOGUE_CAL_DATA_T * const putf_adc_channel_cal_data,
    PUT_ANALOGUE_WORKSPACE_T      * const putf_adc_channel_wrk_data
);

void put_enh_process_analog_input_init
(
    PUT_ENH_ANALOGUE_WORKSPACE_T  * const putf_adc_channel_wrk_data
);

void put_enh_process_analog_input
(
    F32                                   putf_raw_adc_value,
    F32                                   putf_adc_sample_rate,
    F32                           * const putf_analogue_value,
    U8                            * const putf_confirmed_min_raw_range_fault,
    U8                            * const putf_confirmed_max_raw_range_fault,
    U8                            * const putf_confirmed_slew_rate_fault,
    U8                            * const putf_confirmed_min_eng_range_fault,
    U8                            * const putf_confirmed_max_eng_range_fault,
    U8                            * const putf_transient_fault_flag,
    const PUT_ANALOGUE_CAL_DATA_T * const putf_adc_channel_cal_data,
    PUT_ENH_ANALOGUE_WORKSPACE_T  * const putf_adc_channel_wrk_data
);

extern void put_range_check_f32
(
    U32                     putf_n,
    volatile const F32     *putf_value,
    volatile const F32     *putf_max,
    volatile const F32     *putf_min,
    void                   *putf_gt,
    void                   *putf_lt,
    U8                      putf_use_bool_type
);

extern void put_range_check_s8
(
    U32                     putf_n,
    volatile const S8      *putf_value,
    volatile const S8      *putf_max,
    volatile const S8      *putf_min,
    void                   *putf_gt,
    void                   *putf_lt,
    U8                      putf_use_bool_type
);

extern void put_range_check_s16
(
    U32                     putf_n,
    volatile const S16     *putf_value,
    volatile const S16     *putf_max,
    volatile const S16     *putf_min,
    void                   *putf_gt,
    void                   *putf_lt,
    U8                      putf_use_bool_type
);

extern void put_range_check_s32
(
    U32                     putf_n,
    volatile const S32     *putf_value,
    volatile const S32     *putf_max,
    volatile const S32     *putf_min,
    void                   *putf_gt,
    void                   *putf_lt,
    U8                      putf_use_bool_type
);

extern void put_range_check_u8
(
    U32                     putf_n,
    volatile const U8      *putf_value,
    volatile const U8      *putf_max,
    volatile const U8      *putf_min,
    void                   *putf_gt,
    void                   *putf_lt,
    U8                      putf_use_bool_type
);

extern void put_range_check_u16
(
    U32                     putf_n,
    volatile const U16     *putf_value,
    volatile const U16     *putf_max,
    volatile const U16     *putf_min,
    void                   *putf_gt,
    void                   *putf_lt,
    U8                      putf_use_bool_type
);

extern void put_range_check_u32
(
    U32                     putf_n,
    volatile const U32     *putf_value,
    volatile const U32     *putf_max,
    volatile const U32     *putf_min,
    void                   *putf_gt,
    void                   *putf_lt,
    U8                      putf_use_bool_type
);

extern BOOL put_slew_rate_check
(
    F32                            putf_input,
    F32                            putf_slew_rate_limit,
    F32                            putf_delta_time,
    PUT_SLEW_RATE_CHECK_T  * const putf_store
);

extern void put_slew_rate_check_init
(
    PUT_SLEW_RATE_CHECK_T  * const putf_store
);

extern void put_state_processing
(
    U8                      putf_inp_state,
    U8                      putf_invert,
    U8                      putf_fault,
    U8                      putf_default,
    U8                     *putf_out_state
);

/********* Global Variables *********/

/* None */

#endif /* PUT_H */

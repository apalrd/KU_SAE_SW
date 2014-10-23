/*
 *****************************************************************************
 *
 *  Project:        OpenECU
 *  Version:        $Id: pan.h 34565 2013-07-23 19:33:45Z sborders $
 *  File:           $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/pan/pan.h $
 *  Description:    Header file for the angular functionality.
 *
 *  Copyright (C) 2012 Pi Innovo
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

#ifndef PAN_H
#define PAN_H

/********* Includes *********/

#include "pax.h"
#include "pdx.h"
#include "pio.h"

/********* These macros can be changed *********/

/* None */

/********* These macros must not be changed *********/

/* None */

/********* Global Structure Definitions *********/

/** An enumerated type which contains success and failure codes returned by some
 * angular feature (PAN) functions.
 *
 * \ingroup  c_interface
 */
typedef enum
{
    /** Return code if everything progressed as expected.
     */
    PAN_RC_OK,

    /** Return code if an internal error occurred which was the result of a
     * software error.
     */
    PAN_RC_SW_ERROR,

    /** Return code if a hardware error occurred which stopped a channel being
     * sampled or actuated.
     */
    PAN_RC_HW_ERROR,

    /** Return code if at least one of the arguments could not be used.
     */
    PAN_RC_BAD_ARGS,

    /** Return code if at least one of the arguments was clipped to its valid range.
     */
    PAN_RC_CLIPPED_ARGS,

    /** Return code if could not allocate eTPU SDM for function (internal
     * error).
     */
    PAN_RC_SDM_ALLOC_ERROR,

    /** Return code if a given I/O channel cannot be used.
     */
    PAN_RC_BAD_IO_CHAN,

    /** Return code if basic engine configuration hasn't happened
     * yet.
     */
    PAN_RC_ENGINE_NOT_CONFIGURED,

    /** Return code if basic crank configuration hasn't happened
     * yet.
     */
    PAN_RC_CRANK_NOT_CONFIGURED,

    /** Return code if basic cam configuration hasn't happened
     * yet.
     */
    PAN_RC_CAM_NOT_CONFIGURED,

    /** Return code if basic injection output configuration hasn't happened
     * yet.
     */
    PAN_RC_INJ_NOT_CONFIGURED,

    /** Return code if basic spark output configuration hasn't happened
     * yet.
     */
    PAN_RC_SPARK_NOT_CONFIGURED,

    /** Return code if basic angular analogue input configuration hasn't happened
     * yet.
     */
    PAN_RC_ANGULAR_AD_NOT_CONFIGURED,

    /** Return code if engine sync hasn't happened yet.
     */
    PAN_RC_ENGINE_NOT_SYNCED,

    /** Return code if crank sync hasn't happened yet.
     */
    PAN_RC_CRANK_NOT_SYNCED,

    /** Return code if cam sync hasn't happened yet.
     */
    PAN_RC_CAM_NOT_SYNCED,

    /** Return code if cam data is unavailable.
     */
    PAN_RC_CAM_DATA_UNAVAILABLE,

    /** Return code if the cam window is defined across an engine gap.
     */
    PAN_RC_CAM_WINDOW_CONFIG_INVALID,

    /** Return code if the cam window too large.
     */
    PAN_RC_CAM_WINDOW_TOO_WIDE,

    /** Return code if basic engine configuration hasn't happened
     * yet.
     */
    PAN_RC_CONFIGURATION_INCOMPLETE,

    /** Return code if there is a configuration mismatch, e.g., the
     * number of injectors != the number of cylinders configured
     * or the primary crank wheel required by the injection functionality
     * has not been configured.
     */
    PAN_RC_CONFIG_MISMATCH,

    /** Return code if an axis is not monotonically incrementing as
     * expected.
     */
    PAN_RC_BAD_AXIS,

    /** Return code if one of the angular A/D sample angles is too
     * far from the TDC calculation point.
     */
    PAN_RC_ANGULAR_SAMPLE_TOO_FAR,

    /** Return code where the angular clock (generated using a toothed crank wheel)
     * has not been configured.
     */
    PAN_RC_ANGULAR_CLOCK_NOT_CONFIGURED,

    /** Return code if the data used to calculate engine speed is
     * incomplete.
     */
    PAN_RC_ENGINE_SPEED_DATA_INCOMPLETE,

    /** An invalid value, used to when indicated that a valid
     * value has not yet been set.
     */
    PAN_RC_INVALID
}
PAN_RC_T;

/********* Global Prototypes *********/

/************************************************************************/
/* Engine related API                                                   */
/************************************************************************/

#if defined(CFG_FEAT_ANGULAR)

extern PAN_RC_T pan_config_engine
(
    PIO_ENGINE_TYPE_T           panf_engine_type,
    PIO_ENGINE_CYCLE_TYPE_T     panf_engine_cycle_type,
    U8                          panf_num_cyl,
    volatile const F32         *panf_cyl_tdc_firing_angle,
    F32                         panf_task_calc_angle
);

extern PAN_RC_T pan_get_engine_cyl
(
    BOOL                       *panf_valid,
    U8                         *panf_cyl
);

extern PAN_RC_T pan_get_engine_angle
(
    BOOL                       *panf_valid,
    F32                        *panf_engine_angle
);

extern PAN_RC_T pan_get_engine_speed_per_cyl
(
    F32                        *panf_engine_speed
);

extern PAN_RC_T pan_get_engine_speed_per_rev
(
    F32                        *panf_engine_speed
);

extern PAN_RC_T pan_get_engine_speed_per_tooth
(
    F32                        *panf_engine_speed
);

extern PAN_RC_T pan_get_engine_sync
(
    BOOL                       *panf_engine_sync
);

#endif

#if defined(CFG_FEAT_ANGULAR_EXT)

extern PAN_RC_T pan_get_engine_speed_tr_rel
(
    U8                          panf_cyl,
    S16                         panf_tooth,
    S16                         panf_tooth_num,
    F32                        *panf_engine_speed
);

extern PAN_RC_T pan_get_engine_speed_tr_abs
(
    S16                         panf_tooth,
    S16                         panf_tooth_num,
    F32                        *panf_engine_speed
);

#endif

/************************************************************************/
/* Crank wheel related API                                              */
/************************************************************************/

#if defined(CFG_FEAT_ANGULAR_CRANK)

extern PAN_RC_T pan_config_crank_wheel_mtg
(
    PDX_LCHAN_T                 panf_lchan,
    PIO_CRANK_WHEEL_T           panf_wheel,
    PIO_CRANK_WHEEL_SYNC_T      panf_wheel_sync_scheme,
    U16                         panf_physical_teeth,
    U16                         panf_missing_teeth,
    BOOL                        panf_generate_angle_clk,
    PIO_CRANK_TOOTH_EDGE_T      panf_tooth_edge
);

extern PAN_RC_T pan_get_crank_wheel_angle
(
    PIO_CRANK_WHEEL_T           panf_wheel,
    BOOL                       *panf_valid,
    F32                        *panf_crank_angle
);

extern PAN_RC_T pan_get_crank_wheel_movement
(
    PIO_CRANK_WHEEL_T           panf_wheel,
    BOOL                       *panf_crank_movement
);

extern PAN_RC_T pan_get_crank_speed_per_rev
(
    PIO_CRANK_WHEEL_T           panf_wheel,
    F32                        *panf_crank_speed
);

extern PAN_RC_T pan_get_crank_speed_per_tooth
(
    PIO_CRANK_WHEEL_T           panf_wheel,
    F32                        *panf_crank_speed
);

extern PAN_RC_T pan_get_crank_wheel_sync
(
    PIO_CRANK_WHEEL_T           panf_wheel,
    BOOL                       *panf_crank_sync
);

extern PAN_RC_T pan_get_crank_wheel_tooth
(
    PIO_CRANK_WHEEL_T           panf_wheel,
    BOOL                       *panf_valid,
    U16                        *panf_crank_tooth
);

#endif

#if defined(CFG_FEAT_ANGULAR_CRANK_EXT)

extern PAN_RC_T pan_config_crank_wheel_mtg_ext
(
    PIO_CRANK_WHEEL_T           panf_wheel,
    U8                          panf_skip_crank_teeth,
    F32                         panf_first_tooth_timeout,
    F32                         panf_ratio_gap_short_long,
    F32                         panf_ratio_gap_long_short,
    F32                         panf_ratio_across_gap_nr_window,
    F32                         panf_ratio_across_gap_sd_window,
    F32                         panf_ratio_after_gap_nr_window,
    F32                         panf_ratio_after_gap_sd_window,
    F32                         panf_ratio_normal_nr_window,
    F32                         panf_ratio_normal_sd_window,
    F32                         panf_ratio_timeout_nr_window,
    F32                         panf_ratio_timeout_sd_window
);

#endif

#if defined(CFG_FEAT_CRANK_DIG_IN)

extern PAN_RC_T pan_get_crank_pin_state
(
    PIO_CRANK_WHEEL_T           panf_wheel,
    BOOL                       *panf_crk_pin_state
);

#endif

/************************************************************************/
/* Cam wheel related API                                                */
/************************************************************************/

#if defined(CFG_FEAT_ANGULAR_CAM)

extern PAN_RC_T pan_config_cam_wheel_st
(
    PDX_LCHAN_T                 panf_lchan,
    PIO_CAM_WHEEL_T             panf_wheel,
    F32                         panf_start_window_angle,
    F32                         panf_end_window_angle
);

extern PAN_RC_T pan_config_cam_wheel_app
(
    PIO_CAM_WHEEL_T             panf_wheel
);

extern PAN_RC_T pan_get_cam_wheel_movement
(
    PIO_CAM_WHEEL_T             panf_wheel,
    BOOL                       *panf_cam_movement
);

extern PAN_RC_T pan_get_cam_speed_per_rev
(
    PIO_CAM_WHEEL_T             panf_wheel,
    F32                        *panf_cam_speed
);

extern PAN_RC_T pan_get_cam_wheel_sync
(
    PIO_CAM_WHEEL_T             panf_wheel,
    BOOL                       *panf_cam_sync
);

extern PAN_RC_T pan_declare_cam_wheel_sync
(
    PIO_CAM_WHEEL_T             panf_wheel,
    BOOL                        panf_cam_synced,
    BOOL                        panf_phase_offset
);

#endif

#if defined(CFG_FEAT_ANGULAR_CAM_EXT)

extern PAN_RC_T pan_config_cam_wheel_mt
(
    PDX_LCHAN_T                 panf_lchan,
    PIO_CAM_WHEEL_T             panf_wheel,
    U8                          panf_num_teeth,
    PIO_CAM_CAP_EDGE_T          panf_tooth_edge_capture,
    F32                         panf_start_window_angle,
    F32                         panf_end_window_angle
);

extern PAN_RC_T pan_get_cam_wheel_teeth_angles
(
    PIO_CAM_WHEEL_T             panf_wheel,
    F32                        *panf_angles,
    BOOL                       *panf_timeout,
    U32                        *panf_count_timeout,
    U32                        *panf_count_missing,
    U32                        *panf_count_extra
);

#endif

/************************************************************************/
/* Injector related API                                                 */
/************************************************************************/

#if defined(CFG_FEAT_ANGULAR_INJ)

extern PAN_RC_T pan_config_injectors
(
    volatile const PDX_LCHAN_T *panf_lchans,
    U32                         panf_chans,
    PIO_INJECTOR_DRIVE_T        panf_drive,
    BOOL                        panf_invert
);

extern BOOL pan_injection_config_successful
(
    PAN_RC_T *panf_config_result
);

#endif

#if defined(CFG_FEAT_ANGULAR_INJ_EXT)

extern PAN_RC_T pan_config_injector
(
    U32                         panf_inj_id,        /* injector ID to configure */
    PDX_LCHAN_T                 panf_lchan,         /* logical channel number from PIO */
    U32                         panf_cyl,           /* cylinder with which to assign this injector */
    PIO_INJECTOR_DRIVE_T        panf_drive_type,    /* injector drive type for this injector (saturating, peak & hold) */
    PIO_INJECTOR_PULSE_TYPE_T   panf_pulse_type,    /* injector pulse type (GPI, DI, Implicit) */
    BOOL                        panf_invert         /* channel inversion flag */
);

#endif

#if defined(CFG_FEAT_ANGULAR_INJ_DI)

extern PAN_RC_T pan_config_injectors_comp_di
(
    PAX_LCHAN_T                 panf_frp_chan,
    volatile const F32         *panf_injcomp_map_x,     /* pulse volume axis in mm3 */
    U8                          panf_injcomp_map_x_sz,
    volatile const F32         *panf_injcomp_map_y,     /* fuel rail pressure axis in mPA */
    U8                          panf_injcomp_map_y_sz,
    volatile const F32         *panf_injcomp_map_z,     /* injection duration in milliseconds */
    volatile const F32         *panf_frp_tf_x_volts,    /* x axis of FRP transfer function map (volts->FRP in MPa) */
    volatile const F32         *panf_frp_tf_z_MPa,      /* data of FRP transfer function map */
    S32                         panf_frp_tf_sz,         /* size of FRP transfer function map */
    F32                         panf_frp_tf_max_volts   /* Voltage that corresponds to 4095 ADC counts */
);

extern PAN_RC_T pan_set_injection_comp_frp_di
(
    BOOL                        panf_override,
    F32                         panf_frp
);

extern PAN_RC_T pan_config_injections_di
(
    F32                         panf_min_inj_time,
    F32                         panf_min_off_time,
    F32                         panf_drop_dead_angle
);

extern PAN_RC_T pan_set_injection_di
(
    U8                          panf_injector_id,
    U8                          panf_pulses,
    volatile const F32         *panf_rel_on_angle,
    volatile const F32         *panf_fuel_volume,
    F32                         panf_duration_offset,
    PIO_INJDI_DURATION_MODE_T   panf_duration_mode
);

#endif

#if defined(CFG_FEAT_ANGULAR_INJ_PI)

extern PAN_RC_T pan_set_injection_gpi
(
    U8                          panf_cyl,
    F32                         panf_rel_on_angle,
    F32                         panf_flow_time,
    F32                         panf_dead_time,
    F32                         panf_end_of_intake_angle
);

extern PAN_RC_T pan_update_injection_gpi
(
    U8                          panf_enable,
    U8                          panf_enable_post_pulses,
    U8                          panf_cyl,
    F32                         panf_rel_on_angle,
    F32                         panf_flow_time,
    F32                         panf_dead_time
);

#endif

#if defined(CFG_FEAT_ANGULAR_INJ_PI_EXT)

extern PAN_RC_T pan_set_initial_injection_gpi
(
    F32                         panf_flow_time,
    F32                         panf_dead_time
);

#endif

/************************************************************************/
/* Spark related API                                                    */
/************************************************************************/

#if defined(CFG_FEAT_ANGULAR_SPARK)

extern PAN_RC_T pan_config_sparks
(
    volatile const PDX_LCHAN_T *panf_lchans,
    U32                         panf_chans,
    PIO_SPARK_TYPE_T            panf_spark_type,
    BOOL                        panf_invert
);

extern PAN_RC_T pan_set_spark
(
    U8                          panf_cyl,
    F32                         panf_rel_on_angle,
    F32                         panf_rel_off_angle
);

extern BOOL pan_spark_config_successful
(
    PAN_RC_T *panf_config_result
);

#endif

/************************************************************************/
/* Knock related API                                                    */
/************************************************************************/

#if defined(CFG_FEAT_ANGULAR_KNOCK)

extern PAN_RC_T pan_config_knock
(
    /* will we be able to do this for the G850? i.e., is G850 digital */
    PAX_LCHAN_T                 panf_lchan,
    PIO_KNOCK_GROUP_T           panf_group,
    F32                         panf_region_start_angle
);

extern PAN_RC_T pan_get_knock_feedback
(
    U8                          panf_cyl,
    U8                          panf_group,
    S16                         panf_adc
);

extern PAN_RC_T pan_set_knock_window
(
    U8                          panf_cyl,
    PIO_KNOCK_GROUP_T           panf_group,
    F32                         panf_rel_on_angle,
    F32                         panf_rel_off_angle
);

extern PAN_RC_T pan_set_knock_filter_prosak
(
    /* todo */
    void
);

extern void pan_knock_task
(
    void
);

extern void pan_knock_ref_task
(
    void
);

#endif

/************************************************************************/
/* A/D related API                                                      */
/************************************************************************/

#if defined(CFG_FEAT_ANGULAR_AD)

#if !defined(CFG_DONT_USE_DEPRECATED)
/* Deprecated, see pan_config_angular_ad_fxd(). */
extern PAN_RC_T pan_config_angular_ad
(
    PAX_LCHAN_T                 panf_lchan,
    PIO_AD_GROUP_T              panf_group,
    U8                          panf_num_sample,
    volatile const F32         *panf_sample_angles
);
#else
#define pan_config_angular_ad(a, b, c, d) pan_config_angular_ad_is_deprecated_see_user_guide()
#endif

#if !defined(CFG_DONT_USE_DEPRECATED)
/* Deprecated, see pan_get_angular_ad(). */
extern PAN_RC_T pan_get_angular_ad
(
    PIO_AD_GROUP_T              panf_group,
    S16                        *panf_adc
);
#else
#define pan_get_angular_ad(a, b) pan_get_angular_ad_is_deprecated_see_user_guide()
#endif

#if !defined(CFG_DONT_USE_DEPRECATED)
/* Deprecated, see pan_get_angular_ad_avg_fxd(). */
extern PAN_RC_T pan_get_angular_ad_avg
(
    PIO_AD_GROUP_T              panf_group,
    S16                        *panf_adc
);
#else
#define pan_get_angular_ad_avg(a, b) pan_get_angular_ad_avg_is_deprecated_see_user_guide()
#endif

#if !defined(CFG_DONT_USE_DEPRECATED)
/* Deprecated, see pan_get_angular_ad_samples_fxd(). */
extern PAN_RC_T pan_get_angular_ad_samples
(
    PIO_AD_GROUP_T              panf_group,
    S16                        *panf_adc
);
#else
#define pan_get_angular_ad_samples(a, b) pan_get_angular_ad_samples_is_deprecated_see_user_guide()
#endif

extern PAN_RC_T pan_config_angular_ad_fxd
(
    PAX_LCHAN_T                 panf_lchan,
    PIO_AD_GROUP_T              panf_group,
    U8                          panf_num_sample,
    volatile const F32         *panf_sample_angles
);

extern PAN_RC_T pan_get_angular_ad_avg_fxd
(
    PIO_AD_GROUP_T              panf_group,
    S16                        *panf_adc
);

extern PAN_RC_T pan_get_angular_ad_samples_fxd
(
    PIO_AD_GROUP_T              panf_group,
    S16                        *panf_adc
);

#endif

#if defined(CFG_FEAT_ANGULAR_AD_EXT)

extern PAN_RC_T pan_config_angular_ad_var
(
    PAX_LCHAN_T                 panf_lchan,
    PIO_AD_GROUP_T              panf_group
);

extern PAN_RC_T pan_get_angular_ad_avg_var
(
    U8                          panf_cyl,
    PIO_AD_GROUP_T              panf_group,
    S16                        *panf_adc,
    U8                          panf_num_sample,
    volatile const F32         *panf_sample_angles
);

extern PAN_RC_T pan_get_angular_ad_samples_var
(
    U8                          panf_cyl,
    PIO_AD_GROUP_T              panf_group,
    S16                        *panf_adc,
    U8                          panf_num_sample,
    volatile const F32         *panf_sample_angles
);

PAN_RC_T pan_get_angular_ad_avg_abs
(
    PIO_AD_GROUP_T              panf_group,
    S16                        *panf_adc,
    U8                          panf_num_sample,
    volatile const F32         *panf_sample_angles
);

PAN_RC_T pan_get_angular_ad_samples_abs
(
    PIO_AD_GROUP_T              panf_group,
    S16                        *panf_adc,
    U8                          panf_num_sample,
    volatile const F32         *panf_sample_angles
);

#endif

extern void pan_task
(
    void
);

/********* Global Variables *********/

/* None */

#endif /* PAN_H */

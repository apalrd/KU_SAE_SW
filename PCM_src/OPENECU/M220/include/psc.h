/*****************************************************************************/
/**
 *  \file    psc.h
 *  \brief   Public interface to the system startup and idle feature.
 *
 *  Version: $Id: psc.h 34763 2013-08-07 17:58:07Z sborders $
 *  File:    $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/psc/psc.h $
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

#ifndef PSC_H
#define PSC_H

/********* Includes *********/

#include "psy.h"

/********* These macros can be changed *********/

/* None */

/********* These macros must not be changed *********/

/* None */

/********* Global Structure Definitions *********/

/** Error values for debugging -- when an error is found by the system start
 * and idle feature (PSC), the feature calls a system error log function with
 * an enumeration from this type.
 *
 * \ingroup  c_interface
 */
typedef enum
{
    /** Error raised if the decode reset function finds an invalid
     * argument.
     */
    PSC_DECODE_RESET_INVALID_ARG                    = 1,

    /** Error raised if the platform library forces a reset of the ECU.
     */
    PSC_ERR_FORCED_RESET                            = 10,

    /** Error raised if at least one of the version pointer arguments
     * to a version function is invalid.
     */
    PSC_ERR_VERSION_INVALID_PARAM                   = 20,

    /** Error raised if at least one of the build date pointer arguments
     * to a version function is invalid.
     */
    PSC_ERR_BUILD_DATE_INVALID_PARAM                = 21,

    /** Error raised if at least one of the part number pointer arguments
     * to a part-number function is invalid.
     */
    PSC_ERR_PART_NUMBER_INVALID_PARAM               = 22,

    /** Error raised if the Calibration Verification Number calculation
     *  found an unexpected change in flash memory contents.
     */
    PSC_UNEXPECTED_CVN_CHANGE                       = 30,

    /** Error raised if internal RAM failure detected.
     */
    PSC_ERR_CELL_RETENTION                          = 41,

    /** Error raised if overspill RAM failure detected.
     */
    PSC_ERR_ADDRESS_BUS                             = 42,

    /** Error raised if external RAM 1 failure detected.
     */
    PSC_ERR_DATA_BUS                                = 43

}
PSC_ERROR_CODE_T;

/** An enumerated type which contains success and failure codes returned by some
 * system start and idle feature (PSC) functions.
 *
 * \ingroup  c_interface
 */
typedef enum
{
    /** Return code if everything progressed as expected.
     */
    PSC_RC_OK,

    /** Return code if at least one of the arguments could not be used.
     */
    PSC_RC_BAD_ARGS
}
PSC_RC_T;

/********* Global Prototypes *********/

extern PSC_RC_T psc_decode_reset
(
    BOOL *pscf_power_reset,
    BOOL *pscf_watchdog_reset,
    BOOL *pscf_access_reset,
    BOOL *pscf_fp_reset,
    BOOL *pscf_forced_reset,
    BOOL *pscf_other_reset,
    F32  *pscf_boot_duration
);

extern void psc_force_box_reset
(
    void
);

extern void psc_store_suicide_note
(
    U32 note
);

extern U32 psc_get_suicide_note
(
    void
);

extern void psc_clear_reset_count
(
    void
);

extern PSC_RC_T psc_get_boot_build_date
(
    U16   *pscf_year,
    U16   *pscf_month,
    U16   *pscf_day
);

extern PSC_RC_T psc_get_boot_version
(
    U16   *pscf_major_ver,
    U16   *pscf_minor_ver,
    U16   *pscf_sub_minor_ver
);

extern PSC_RC_T psc_get_boot_part_number
(
    U8  *pscf_group,
    U8  *pscf_letter,
    U32 *pscf_id,
    U16 *pscf_issue
);

extern U8 psc_get_cpu_loading
(
    void
);

extern U8 psc_get_max_cpu_loading
(
    void
);

extern PSC_RC_T psc_get_platform_build_date
(
    U16   *pscf_year,
    U16   *pscf_month,
    U16   *pscf_day
);

extern PSC_RC_T psc_get_platform_version
(
    U16   *pscf_major_ver,
    U16   *pscf_minor_ver,
    U16   *pscf_sub_minor_ver
);

extern PSC_RC_T psc_get_platform_part_number
(
    U8  *pscf_group,
    U8  *pscf_letter,
    U32 *pscf_id,
    U16 *pscf_issue
);

extern PSC_RC_T psc_get_prg_build_date
(
    U16   *pscf_year,
    U16   *pscf_month,
    U16   *pscf_day
);

extern PSC_RC_T psc_get_prg_version
(
    U16   *pscf_major_ver,
    U16   *pscf_minor_ver,
    U16   *pscf_sub_minor_ver
);

extern PSC_RC_T psc_get_prg_part_number
(
    U8  *pscf_group,
    U8  *pscf_letter,
    U32 *pscf_id,
    U16 *pscf_issue
);

extern PSC_RC_T psc_get_application_build_date
(
    U16   *pscf_year,
    U16   *pscf_month,
    U16   *pscf_day
);

extern PSC_RC_T psc_get_application_version
(
    U16   *pscf_major_ver,
    U16   *pscf_minor_ver,
    U16   *pscf_sub_minor_ver
);

extern U32 psc_get_run_time
(
    void
);

extern U32 psc_get_used_stack_size
(
    void
);

extern void psc_watchdog_task
(
    void
);

extern void psc_kick_watchdog
(
    void
);

#if defined(CFG_FEAT_CVN)
extern void psc_start_cvn_calc
(
    void
);

extern BOOL psc_check_cvn_availability
(
    U32  *pscf_cvn,
    BOOL *pscf_being_calculated
);
#endif /* CFG_FEAT_CVN */

/** This function is invoked from the library between pre-initialisation and
 * post-initialisation. The application must define this function. The
 * application may use the function to initialise itself and configure the
 * library (e.g., by calling pcx_declare_message()).
 *
 * \remark cfg_all
 * \remark lic_none
 *
 * \ingroup c_interface
 */
extern void psc_initialise_app
(
    void
);

/** This function is invoked by the library when no tasks are running.
 * The application must define this function. The application may use the
 * function to perform any time or event independent processing.
 *
 * \remark cfg_all
 * \remark lic_none
 *
 * \ingroup c_interface
 */
extern void psc_background_app
(
    void
);

/********* Global Variables *********/

/** This determines whether the watchdog task is active or not.
 *
 * Set true to enable the watchdog task (which automatically kicks
 * the watchdog on a periodic basis) or set false to disable the
 * watchdog task (and handle watchdog functionality from within
 * the application).
 *
 * \ingroup c_interface
 */
extern const U8 psc_watchdog_task_enabled;

/** This determines whether run-time background memory checks are active or not.
 *
 * Set true to enable the background tests of RAM, flash and
 * non-volatile memory.
 *
 * \ingroup c_interface
 */
extern const BOOL psc_mem_runtime_checks_enabled;

/** This is the major version number of the application.
 *
 * The complete version number takes the form \e major.minor.subminor. The
 * application version number is referenced in the application header (\a
 * psc_platform_header) and can be extracted from the final build image. \n
 * Range: [0, 65535] unitless
 *
 * \ingroup c_interface
 */
extern const U16 psc_app_major_ver_num;

/** This is the minor version number of the application.
 *
 * The complete version number takes the form \e major.minor.subminor. The
 * application version number is referenced in the application header (\a
 * psc_platform_header) and can be extracted from the final build image. \n
 * Range: [0, 65535] unitless
 *
 * \ingroup c_interface
 */
extern const U16 psc_app_minor_ver_num;

/** This is the subminor version number of the application.
 *
 * The complete version number takes the form \e major.minor.subminor. The
 * application version number is referenced in the application header (\a
 * psc_platform_header) and can be extracted from the final build image. \n
 * Range: [0, 65535] unitless.
 *
 * \ingroup c_interface
 */
extern const U16 psc_app_sub_minor_ver_num;

/** This is the day application code was built.
 *
 * Range: [1, 31] day
 */
extern const U16 psc_app_build_day;

/** This is the month application code was built.
 *
 * Range: [1, 12] month
 */
extern const U16 psc_app_build_month;

/** This is the year application code was built.
 *
 * Range: [1, 65535] unitless
 */
extern const U16 psc_app_build_year;

/** This is the name of the application.
 *
 * The name is a null-terminated string of ASCII characters. The name is
 * referenced in the application header (\a psc_platform_header) and can be
 * extracted from the final build image.
 *
 * \ingroup c_interface
 */
extern const U8 psc_app_name[];

/** This is a description of the application.
 *
 * The description is a null-terminated string of ASCII characters. The
 * description is referenced in the application header (\a psc_platform_header)
 * and can be extracted from the final build image.
 *
 * \ingroup c_interface
 */
extern const U8 psc_app_desc[];

/** This is a copyright notice for the application.
 *
 * The copyright notice is a null-terminated string of ASCII characters. The
 * copyright notice is referenced in the application header (\a
 * psc_platform_header) and can be extracted from the final build image.
 *
 * \ingroup c_interface
 */
extern const U8 psc_app_copyright[];

#endif /* PSC_H */

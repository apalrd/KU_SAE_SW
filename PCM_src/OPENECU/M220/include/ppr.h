/*****************************************************************************/
/**
 *  \file    ppr.h
 *  \brief   Public interface to the In-Use Performance Ratio (PPR) feature.
 *
 *  Version: $Id: ppr.h 35178 2013-09-10 16:03:01Z jtough $
 *  File:    $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/ppr/ppr.h $
 */

/*  Copyright (C) 2012 Pi Innovo
 *  This document (program) contains proprietary information
 *  which is the property of Pi Innovo
 *  The contents of this document (program) must not be copied
 *  or disclosed to a third party without the prior agreement
 *  of an authorised officer of Pi Innovo
 */

#ifndef PPR_H
#define PPR_H

/********* Includes *********/

#include "pio.h"

/********* These macros can be changed *********/

/** This macro defines the value for #ppr_store when non-volatile data is to be
 * stored in battery backed RAM across power cycles.
 *
 * \ingroup c_extdiag_interface
 */
#define PPR_STORE_IN_BBRAM   0

/** This macro defines the value for #ppr_store when non-volatile data is to be
 * stored in Flash across power cycles.
 *
 * \ingroup c_extdiag_interface
 */
#define PPR_STORE_IN_FLASH   1

/********* These macros must not be changed *********/

/** The bit position for DTE type definition
 *  Bit 0 - to define whether DTE is relevant to ISO (J1979) protocol.
 *  Bit 1 - to define whether DTE is relevant to J1939 protocol.
 *
 * \ingroup c_extdiag_interface
 */
#define PPR_TEST_AND_MON_TYPE_ISO 0x1
#define PPR_TEST_AND_MON_TYPE_J1939 0x2

/********* Global Structure Definitions *********/

/** An enumerated type which contains success and failure codes returned by some
 * In-Use Performance Ratio (PPR) functions.
 * \ingroup c_extdiag_interface
 */
typedef enum
{
    /** Return code if everything progressed as expected.
     */
    PPR_RC_OK,

    /** Return code if at least one of the arguments could not be used.
     */
    PPR_RC_BAD_ARGS,

    /** Return code if the PPR configuration data was invalid for requested operation.
     */
    PPR_RC_BAD_CONFIG_DATA
}
PPR_RC_T;

/** An enumerated type which contains the state of the test run.
 * \ingroup c_extdiag_interface
 */
/* Essential to pack to minimise RAM cost of DTEs */
typedef PSY_PACKED enum
{
    /** Test has not been run (ever).
     */
    PPR_TEST_NOT_RUN = 0,

    /** Test has been run this drive cycle.
     */
    PPR_TEST_RUN_THIS_DC = 1,

    /** Test has been run, but not this drive cycle.
     */
    PPR_TEST_RUN = 2
}
PPR_TEST_RUN_STATE_T;

/** This structure declares the run-time data to be stored with each DTE.
 *
 * \note The structure is private to the library and should not be used by the
 *       application. It is exposed as part of the API so that various arrays
 *       can be sized at build time to minimise the library memory footprint.
 */
/* Packed to minimise RAM and NV cost of DTEs */
/* im[LLR.PLAT.PPR 1.04] */
typedef PSY_PACKED struct
{
    /** The Specific Numerator for the test
     * \ingroup c_extdiag_interface
     */
    U16          numerator;

    /** The Specific Denominator for the test
     * \ingroup c_extdiag_interface
     */
    U16          denominator;

    /** The Test value for the test
     * \ingroup c_extdiag_interface
     */
    U16          test_value;

    /** The maximum limit of the test value for the test Pass/Fail criteria
     * \ingroup c_extdiag_interface
     */
    U16          test_lim_max;

    /** The minimum limit of the test value for the test Pass/Fail criteria
     * \ingroup c_extdiag_interface
     */
    U16          test_lim_min;

    /** Specifies if the DTE is in-use for current application
     * \ingroup c_extdiag_interface
     */
    BOOL         dte_in_use;

    /** This keeps track of whether the Numerator has been updated *this* drive cycle
     * \ingroup c_extdiag_interface
     */
    BOOL         numerator_updated_this_cycle;

    /** This keeps track of whether the Denominator has been updated *this* drive cycle
     * \ingroup c_extdiag_interface
     */
    BOOL         denominator_updated_this_cycle;

    /** This keeps track of whether the Test has been run this cycle / ever
     * \ingroup c_extdiag_interface
     */
    PPR_TEST_RUN_STATE_T         test_run_status;
}
PPR_DTE_NV_T;

/** This structure collates the data associated with each DTE.
 * \note The application may use the ISO and J1939 Test IDs, Monitor group ID and Component ID elements.
 * Access to other elements should be made exclusively through
 * library API calls, to avoid data coherency issues.
 */
/* Packed to minimise RAM and NV cost of DTEs */
/* im[LLR.PLAT.PPR 1.02], im[LLR.PLAT.PPR 1.05] */
typedef PSY_PACKED struct
{
    /** The DTE identifier - calibratable by the application
     * \ingroup c_extdiag_interface
     */
    U8              dte_id;

    /** The DTE type - ISO or J1939 or BOTH
     *  Bit 0 = 1 implies ISO
     *  Bit 1 = 1 implies J1939
     * \ingroup c_extdiag_interface
     */
    U8              dte_type;

     /** The DME to which this DTE belongs - calibratable by the application.
     * \ingroup c_extdiag_interface
     */
    U8              dme_id;

   /** The ISO specified Test ID that requires ratio monitoring
     * \ingroup c_extdiag_interface
     */
    U8              iso_tid;

    /** The J1939 specified Test ID that requires ratio monitoring
     * \ingroup c_extdiag_interface
     */
    U8              j1939_tid;

    /** The Monitor group ID to which the DTE belongs
     *  Applicable only for reporting over ISO
     * \ingroup c_extdiag_interface
     */
    U8              mon_id;

    /** The identifier is used to reference the scaling and unit to be used by
     *  the external test equipment to calculate and display the test values/ results
     *  Applicable only for reporting over ISO
     * \ingroup c_extdiag_interface
     */
    U8              scaling_id;

    /** The SLOT identifier for the DTE
     *  Applicable only for reporting over J1939
     * \ingroup c_extdiag_interface
     */
    U16             slot_id;

    /** The SPN associated with the DTE
     *  Applicable only for reporting over J1939
     * \ingroup c_extdiag_interface
     */
    U32             spn;

    /** The FMI associated with the DTE
     *  Applicable only for reporting over J1939
     * \ingroup c_extdiag_interface
     */
    U8              fmi;

    /** The Component identifier for the DTE
     *  Applicable only for reporting over J1939
     * \ingroup c_extdiag_interface
     */
    U8              component_id;

    /** Pointer to the modifiable data part of the Test data
     * \ingroup c_extdiag_interface
     */
    PPR_DTE_NV_T    *dte_data_nv;
}
PPR_DTE_CONST_T;

/** This structure declares the run-time data to be stored with each DME.
 *
 * \note The structure is private to the library and should not be used by the
 *       application. It is exposed as part of the API so that various arrays
 *       can be sized at build time to minimise the library memory footprint.
 */
/* Packed to minimise RAM and NV cost of DMEs */
/* im[LLR.PLAT.PPR 1.015], im[LLR.PLAT.PPR 1.43] */
typedef PSY_PACKED struct
{
    /** The Run count used for setting Readiness 'complete' status for the DME
     * \ingroup c_extdiag_interface
     */
    U16         dme_run_count;

    /** Specifies if the DME is in-use for current application
     * \ingroup c_extdiag_interface
     */
    BOOL         dme_in_use;

    /** The Readiness 'complete' status for the DME
     * \ingroup c_extdiag_interface
     */
    BOOL        dme_readiness_complete;

    /** Indicates whether the monitoring for the DME is enabled
     * \ingroup c_extdiag_interface
     */
    BOOL        dme_enabled;

    /** Indicates whether the monitoring conditions for the DME are met
     * \ingroup c_extdiag_interface
     */
    BOOL        dme_completed;
}
PPR_DME_NV_T;

/** This structure collates the data associated with each Monitor ID.
 * \note The application may use the Monitor ID and rediness count limit elements.
 * Access to other elements should be made exclusively through
 * library API calls, to avoid data coherency issues.
 */
/* Packed to minimise RAM and NV cost of DTEs */
/* im[LLR.PLAT.PPR.1.013], im[LLR.PLAT.PPR 1.010] */
typedef PSY_PACKED struct
{
    /** The DME identifier - calibratable by the application
     * \ingroup c_extdiag_interface
     */
    U8                    dme_id;

    /** The DME type - ISO or J1939 or BOTH
     *  Bit 0 = 1 implies ISO
     *  Bit 1 = 1 implies J1939
     * \ingroup c_extdiag_interface
     */
    U8                   dme_type;

    /** The Monitor ID that requires ratio monitoring
     * \ingroup c_extdiag_interface
     */
    U8                   mon_id;

    /** The Monitor group which this DME belongs to
     * \ingroup c_extdiag_interface
     */
    PIO_MONITOR_GROUP_T  mon_grp;

    /** The readines count limit - the number of times monitor has to be run before declared as Readiness COMPLETE
     * \ingroup c_extdiag_interface
     */
    U16                  readiness_count_lim;

    /** The SPN for the DME
     *  Applicable only for reporting DM20 messages over J1939
     * \ingroup c_extdiag_interface
     */
    U32                  spn;

    /** Pointer to the modifiable data part of the Monitor data
     * \ingroup c_extdiag_interface
     */
    PPR_DME_NV_T        *dme_data_nv;
}
PPR_DME_CONST_T;

/** This structure is for the data calculated for reporting the DME data.
 */
/* im[LLR.PLAT.PPR.1.09] */
typedef struct
{
    /** The Specific Numerator for the monitor group
     * \ingroup c_extdiag_interface
     */
    U16         dme_numerator;

    /** The Specific Denominator for the monitor group
     * \ingroup c_extdiag_interface
     */
    U16         dme_denominator;

    /** The Ratio for the monitor group
     * \ingroup c_extdiag_interface
     */
    F32         dme_ratio;
}
PPR_DME_DATA_T;

/** This structure declares the run-time data to be stored with the various counts.
 *
 * \note The structure is private to the library and should not be used by the
 *       application. It is exposed as part of the API so that various arrays
 *       can be sized at build time to minimise the library memory footprint.
 */
typedef struct
{
    /** The actual counter value
     */
    U16         count;

    /** This keeps track of whether it has been updated this drive cycle
     */
    BOOL        update_status;
}
PPR_COUNT_NV_T;

/********* Global Prototypes *********/

extern PPR_RC_T ppr_update_dte_data
(
    U8      pprf_dte_id,
    BOOL    pprf_sp_den_update_enable,
    BOOL    pprf_sp_num_update_enable
);

extern PPR_RC_T ppr_update_dte_test_value
(
    U8      pprf_dte_id,
    U16     pprf_test_value,
    U16     pprf_test_limit_min,
    U16     pprf_test_limit_max,
    BOOL    pprf_test_run,
    BOOL    pprf_reset_dte
);

extern PPR_RC_T ppr_update_dte_in_use_status
(
    U8      pprf_dte_id,
    BOOL    pprf_in_use
);

extern PPR_RC_T ppr_update_dme_data
(
    U8      pprf_dme_id,
    BOOL    pprf_monitor_run,
    BOOL    pprf_force_complete,
    BOOL    pprf_force_not_complete,
    BOOL    pprf_monitor_enabled
);

extern PPR_RC_T ppr_update_dme_in_use_status
(
    U8      pprf_dme_id,
    BOOL    pprf_in_use
);

extern void ppr_update_gen_denominator
(
    BOOL    pprf_gen_den_update_enable
);

extern void ppr_update_ign_cyc_counter
(
    BOOL    pprf_ign_cyc_update_enable
);

extern PPR_RC_T ppr_get_dme_ratio
(
    U8                pprf_dme_id,
    PPR_DME_DATA_T   *pprf_dme_data
);

extern PPR_RC_T ppr_get_dme_status
(
    U8                pprf_dme_id,
    PPR_DME_NV_T     *pprf_dme_nv_data
);

extern U16 ppr_get_dme_incomplete_count
(
    void
);

extern PPR_RC_T ppr_get_dte_status
(
    U8                pprf_dte_id,
    PPR_DTE_NV_T     *pprf_dte_nv_data
);

extern U16 ppr_get_ign_cycle_count
(
    void
);

extern U16 ppr_get_gen_denominator
(
    void
);

extern void ppr_commit_to_store
(
    void
);

extern BOOL ppr_is_store_intact
(
    void
);

/********* Global Variables *********/

/** This defines which memory type will be used to store non-volatile
 * PPR data.
 *
 * If set to #PPR_STORE_IN_BBRAM then non-volatile data is stored in
 * battery backed RAM, and if set to #PPR_STORE_IN_FLASH then the non-volatile
 * data is stored in Flash.
 *
 * \warning Some memory stores are not implemented on some target ECUs.
 *          See the technical specification of the ECU to determine if
 *          the store type is available.
 *
 * \ingroup c_extdiag_interface
 */
extern const U8 ppr_store;

/** The total number of DTEs that are declared.
 *
 * \ingroup c_extdiag_interface
 */
/* im[LLR.PLAT.PPR 1.01] */
extern volatile const U16 pprc_num_dte;

/** The total number of DMEs that are declared.
 *
 * \ingroup c_extdiag_interface
 */
/* im[LLR.PLAT.PPR 1.012] */
extern volatile const U16 pprc_num_dme;

/** The table of DTEs
 *
 * Present in the C-API description only for build time size requirements.
 * The array must be declared and sized by the application. The size of the
 * array must equal \p #pprc_num_dte (or one if there are DTEs).
 * The array is not to be accessed by application code.
 *
 * \ingroup c_extdiag_interface
 */
extern const PPR_DTE_CONST_T ppr_dte_table[];

/** The table of DMEs
 *
 * Present in the C-API description only for build time size requirements.
 * The array must be declared and sized by the application. The size of the
 * array must equal \p #pprc_num_dme (or one if there are no DMEs).
 * The array is not to be accessed by application code.
 *
 * \ingroup c_extdiag_interface
 */
extern const PPR_DME_CONST_T ppr_dme_table[];

/** This is a sorted list of bit mapping for J1939 Test Ids - used for DM10 message
 *
 * \ingroup c_extdiag_interface
 */
extern const U8 ppr_j1939_test_mapping_list[64];

#endif /* PPR_H */

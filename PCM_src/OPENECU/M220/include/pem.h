/*
 *****************************************************************************
 *
 *  Project:        OpenECU
 *  Version:        $Id: pem.h 32567 2013-02-12 09:45:02Z amcmillan $
 *  File:           $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/pem/pem.h $
 *  Description:    Public interface to calibration RAM and emulation boards
 *                  (e.g., ATI M6).
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

#ifndef PEM_H
#define PEM_H

/********* Includes *********/

/* None */

/********* These macros can be changed *********/

/* This is the maximum number of ATI emulator shadow tables (defined below)
 * that the emulator and platform can action.
 */
#define PEM_MAX_SHADOW_TABLES  4

/********* These macros must not be changed *********/

/* None */

/********* Global Structure Definitions *********/

/** Error values for debugging -- when an error is found by emulator and
 * memory feature (PEM), the feature calls a system error log function with
 * an enumeration from this type.
 *
 * \ingroup  c_interface
 */
typedef enum
{
    /** Error raised if the test for external RAM failed for
     *  a memory configuration that requires it to be there.
     */
    PEM_EXTERNAL_RAM_REQUIRED                    = 100,

    /** Error raised if the memory configuration is not recognised.
     */
    PEM_MEM_CONFIG_UNKNOWN                       = 200
}
PEM_ERROR_CODE_T;

/* This typedef enumerates the different types of calibration
 * device that can be attached to the ECU.
 *
 * PEM_NONE         -- nothing is attached to the ECU
 * PEM_TAB_BOARD    -- a RAM board is attached for calibration changes during model run
 * PEM_ATI_EMULATOR -- an ATI emulator is attached for calibration changes during model run
 * PEM_CAL_RAM      -- a RAM device is used to overlay just the calibration area during model run
 */
typedef enum
{
    PEM_NONE,
    PEM_TAB_BOARD,
    PEM_ATI_EMULATOR,
    PEM_CAL_RAM
}
PEM_EMU_TYPE_T;

/* These two typedefs define the memory structure the ATI memory
 * emulator uses to communicate to the platform during model run.
 * The structure is used to request reads of data from the model
 * at the end of the processing for model tasks.
 */
typedef struct
{
    volatile const U32*  p_table;           /* Pointer to array of U32 addresses */
    U32*                 v_table;           /* Pointer to array of U32 values */
    U16                  num_elements;      /* Number of table elements */
    U16                  num_display;       /* Unused */
}
PEM_ATI_TABLE_T;

typedef struct
{
    U16             major_ver;
    U16             minor_ver;
    PEM_ATI_TABLE_T table[PEM_MAX_SHADOW_TABLES];
}
PEM_ATI_STLAYOUT_T;

/********* Global Prototypes *********/

extern void pem_configure_memory
(
    void
);

extern void pem_pre_initialise
(
    void
);

extern void pem_post_initialise
(
    void
);

extern PEM_EMU_TYPE_T pem_get_emu_type
(
    void
);

extern void pem_action_ati_emu_shadow_tables
(
    U32 pemf_tid
);

extern void pem_activate_remap
(
    void
);

extern void pem_deactivate_remap
(
    void
);

/********* Global Variables *********/

extern const U8 pem_tid_to_table[][PEM_MAX_SHADOW_TABLES];
extern const U8 pem_last_table;

#endif /* PEM_H */


/*****************************************************************************/
/**
 *  \file    pcp.h
 *  \brief   Public interface to the CAN calibration protocol (CCP) feature.
 *
 *  Version: $Id: pcp.h 31620 2012-11-21 16:12:50Z awatson $
 *  File:    $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/pcp/pcp.h $
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

#ifndef PCP_H
#define PCP_H

/********* Includes *********/

#include "psy.h"

/********* These macros can be changed *********/

/* None */

/********* These macros must not be changed *********/

/* Currently CCP seed-key is only provided for CCP targets.
 * The source for some deprecated ECUs does not support CCP security.
 */
#if defined(CFG_FEAT_CCP_SECURITY) || defined(CFG_DOXYGEN)

/** Mask value for CCP calibration privilege level.
 *
 * \ingroup c_interface
 */
#define PCP_PL_CAL    0x01

/** Mask value for CCP data acquisition privilege level.
 *
 * \ingroup c_interface
 */
#define PCP_PL_DAQ    0x02

/** Mask value for CCP reprogramming privilege level.
 *
 * \ingroup c_interface
 */
#define PCP_PL_PGM    0x40

/** Mask value for all CCP privilege levels.
 *
 * \ingroup c_interface
 */
#define PCP_PL_ALL    (PCP_PL_CAL | PCP_PL_DAQ | PCP_PL_PGM)

#endif  /* CCP Security targets */

/********* Global Structure Definitions *********/

/* Currently CCP seed-key is only provided for a subset of targets.
 * The source for some deprecated ECUs does not support CCP security.
 */
#if defined(CFG_FEAT_CCP_SECURITY) || defined(CFG_DOXYGEN)

/** Typedef for the callback function used to generate a seed for a CCP seed-key exchange.
 *
 * The function is run by a processing task which is scheduled every 5ms.  The function must
 * therefore take no more than 5ms to execute, and preferably should be significantly faster.  As
 * usual for embedded programming, excessive stack requirements and the use of dynamic memory
 * allocation should be avoided.  There is currently no requirement for this function to be
 * re-entrant.
 *
 * The platform software may copy the callback function to NV storage so that application
 * security algorithms may also be used by the bootloader when reprogramming.  In order for this to
 * be possible, the callback function must be relocatable.  The function should therefore make no
 * calls to other functions, or refer to application variables or calibratables, otherwise existing
 * callback functions may be incompatible with new releases of OpenECU.  Note that direct access to
 * registers and hardcoded memory locations is still permitted.
 *
 * \param[in] pcpf_privilege_level
 *    The privilege level for this request will be one of the bit-mask values #PCP_PL_CAL, #PCP_PL_DAQ
 *    or #PCP_PL_PGM, representing a request for calibration, data acquisition or programming
 *    privilege levels respectively.
 *
 * \return
 *    The function must return a 32-bit seed value.  Typically this will be generated through a
 *    random or pseudo-random process.  This seed must be stored for later use by the corresponding
 *    key validation function when the calibration tool returns a key.
 *
 * \ingroup c_interface
 */
typedef void (*PCP_SEED_GENERATOR_T)
(
    const U8 pcpf_privilege_level,
    U8 *const pcpf_seed
);

/** Typedef for the callback function used to validate a key for a CCP seed-key exchange.
 *
 * The function must generate the expected key from the last seed value returned by the
 * corresponding seed request callback function and compare this to the key calculated by the
 * calibration tool.
 *
 * The function is run by a processing task which is scheduled every 5ms.  The function must
 * therefore take no more than 5ms to execute, and preferably should be significantly faster.  As
 * usual for embedded programming, excessive stack requirements and the use of dynamic memory
 * allocation should be avoided.  There is currently no requirement for this function to be
 * re-entrant.
 *
 * The platform software may copy the callback function to NV storage so that application
 * security algorithms may also be used by the bootloader when reprogramming.  In order for this to
 * be possible, the callback function must be relocatable.  The function should therefore make no
 * calls to other functions, or refer to application variables or calibratables, otherwise existing
 * callback functions may be incompatible with new releases of OpenECU.  Note that direct access to
 * registers and hardcoded memory locations is still permitted.
 *
 * \param[in] pcpf_privilege_level
 *    The privilege level for this request will be one of the bit-mask values #PCP_PL_CAL,
 *    #PCP_PL_DAQ or #PCP_PL_PGM, representing a request for calibration, data acquisition or
 *    programming privilege levels respectively.
 *
 * \param[in] pcpf_key
 *    The key is an array of bytes returned by the calibration tool, generated from the seed
 *    returned by the corresponding seed request callback function.
 *
 * \param[in] pcpf_key_size
 *    Size of key array in bytes.  The array may be between zero and 6 bytes long.  Typically the
 *    key will be a 32-bit value (4 bytes), i.e. the same size as the seed, but there is no
 *    requirement for this to be the case.  The size must be checked by the function to ensure that
 *    out-of-bounds array accesses do not take place.
 *
 * \return
 *    The function must return TRUE if the key is correct, or FALSE if not.
 *
 * \ingroup c_interface
 */
typedef BOOL (*PCP_KEY_VALIDATOR_T)
(
    const U8        pcpf_privilege_level,
    const U8 *const pcpf_seed,
    const U8 *const pcpf_key,
    const U8        pcpf_key_size
);

/** Structure configuring security for one or more CCP privilege levels.
 *
 * \ingroup c_interface
 */
typedef struct
{
    /** Bitwise mask specifying which privilege levels this applies to.
     * This mask may be set using the literals #PCP_PL_CAL (calibration),
     * #PCP_PL_DAQ (data acquisition), #PCP_PL_PGM (reprogramming) or #PCP_PL_ALL (all three).
     *
     * \ingroup c_interface
     */
    U8 privilege_levels;

    /** If security_required is set FALSE, no seed-key exchange is required for the
     * specified privilege level(s).  They may be invoked by the calibration tool at any time.
     * The callback structure elements are ignored.
     *
     * If security_required is set TRUE, the callbacks provided are used to unlock the
     * specified privilege levels.  Activities for these privilege levels may not be
     * invoked by the CCP master until they have been unlocked.
     *
     * If security_required is set TRUE but either callback is NULL, it will not be
     * possible to unlock these privilege levels and the calibration tool will be permanently
     * prohibited from invoking activities for these privilege levels.
     *
     * \ingroup c_interface
     */
    BOOL security_required;

    /** Pointer to callback function which is called to request a seed value for the
     * specified privilege level(s) when the calibration tool attempts to unlock the
     * privilege level(s).
     *
     * Set this value to NULL if security is not required.
     *
     * \ingroup c_interface
     */
    PCP_SEED_GENERATOR_T seed_request_callback;

    /** Address of location immediately after seed_request_callback function.
     * This allows the platform to calculate the size of the function.
     *
     * \ingroup c_interface
     */
    U8* seed_request_callback_end_addr;

    /** Pointer to callback function which is called to validate a key value for the
     * returned by the calibration tool, where the key is generated from the seed
     * returned by the previously-called seed_request_callback function.
     *
     * Set this value to NULL if security is not required.
     *
     * \ingroup c_interface
     */
    PCP_KEY_VALIDATOR_T key_validation_callback;

    /** Address of location immediately after key_validation_callback function.
     * This allows the platform to calculate the size of the function.
     *
     * \ingroup c_interface
     */
    U8* key_validation_callback_end_addr;
}
PCP_SEED_KEY_CONFIG_T;

#endif  /* CCP Security targets */

/********* Global Prototypes *********/

extern void pcp_client_task
(
    void
);

#if defined(CFG_FEAT_INHIBIT_PROGRAMMING) || defined(CFG_DOXYGEN)
extern void pcp_inhibit_reprogramming
(
    U8 pcpf_inhibit
);
#endif

/********* Global Variables *********/

/* Currently CCP seed-key is only provided for a subset of targets.
 * The source for some deprecated ECUs does not support CCP security.
 */
#if defined(CFG_FEAT_CCP_SECURITY) || defined(CFG_DOXYGEN)

/** CCP seed-key configuration for application.  Each array element specifies the
 * CCP seed-key security to be applied to one or more CCP privilege levels.
 *
 * The code tolerates multiple array entries existing which specify the same CCP privilege
 * level.  If this occurs, the code carries out processing only for the first array
 * element with a matching CCP privilege level.  Any or all subsequent array entries
 * are ignored.
 *
 * \ingroup c_interface
 */
extern volatile const PCP_SEED_KEY_CONFIG_T pcp_seed_key_config[];

/** Number of array elements in pcp_seed_key_config.
 *
 * \ingroup c_interface
 */
extern volatile const U8 pcp_num_seed_key_configs;

#endif  /* CCP Security targets */

/** True if CCP messaging is enabled during application run,
 * false otherwise.
 *
 * \ingroup c_interface
 */
#ifndef CFG_PRG_BUILD
extern const U8 pcp_ccpenabled;
#endif

#ifdef CFG_FEAT_CCP_CAL_SETTINGS
extern volatile const U32 pcpc_rx_id;
extern volatile const U32 pcpc_tx_id;
extern volatile const U32 pcpc_baud;
extern volatile const U8  pcpc_bus;
extern volatile const U8  pcpc_station_addr;
#endif

#endif /* PCP_H */

/*****************************************************************************/
/**
 *  \file    preg.h
 *  \brief   Public interface to the registry feature.
 *
 *  Version: $Id: preg.h 36654 2013-12-04 16:03:09Z jtough $
 *  File:    $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/preg/preg.h $
 */

/*  Copyright (C) 2012 Pi Innovo
 *  This document (program) contains proprietary information
 *  which is the property of Pi Innovo
 *  The contents of this document (program) must not be copied
 *  or disclosed to a third party without the prior agreement
 *  of an authorised officer of Pi Innovo
 */

#ifndef PREG_H
#define PREG_H

#if (!defined(CFG_G850)) || (defined(CFG_DOXYGEN))
/* Those targets not currently supported by PREG but this header file is still included in C-API collection */

/********* Includes *********/

#include "psy.h"

/********* These macros can be changed *********/

/* None */

/********* These macros must not be changed *********/

#define PREG_MAX_KEY_LENGTH_BYTES         sizeof(PREG_KEYS_T)

/********* Global Structure Definitions *********/

/** An enumerated type which contains success and failure codes returned by some
 * registry feature (PREG) functions.
 *
 * \ingroup  c_interface
 */
typedef enum
{
    /** Return code if everything progressed as expected.
     */
    PREG_RC_OK,

    /** Return code if at least one of the arguments could not be used.
     */
    PREG_RC_BAD_ARGS,

    /** Return code if the key argument is not one recognised by the feature.
     */
    PREG_RC_INVALID_KEY,

    /** Return code if the key argument could not be found in the registry
     * when retrieving the key's value.
     */
    PREG_RC_NOT_FOUND
}
PREG_RC_T;

/** An enumerated type which represents each of the keys supported by this feature.
 * A key is a reference associated to some structured data. For instance, the
 * \c #PREG_KEY_SERIAL_NUM key is associated with the ECU's 32-bit serial number.
 *
 * \ingroup  c_interface
 */
typedef enum
{
    /** The key for the ECU's serial number, see \c #PREG_VALUE_SERIAL_NUM_T for
     * the associated data.
     */
    PREG_KEY_SERIAL_NUM                 = 1,

    /** The key for the ECU's date of manufacture, see \c #PREG_VALUE_DATE_OF_MANUFACTURE_T for
     * the associated data.
     */
    PREG_KEY_DATE_OF_MANUFACTURE        = 2,

    /** The key for the ECU's engineering part number, see \c #PREG_VALUE_ENG_PART_NUM_T for
     * the associated data.
     */
    PREG_KEY_ENG_PART_NUM               = 3,

    /** The key for the ECU's mod and issue number, see \c #PREG_VALUE_HW_ISSUE_MOD_NUM_T for
     * the associated data.
     */
    PREG_KEY_HW_ISSUE_MOD_NUM           = 4,

    /** The key for the ECU's factory part number, see \c #PREG_VALUE_FACTORY_PART_NUM_T for
     * the associated data.
     */
    PREG_KEY_FACTORY_PART_NUM           = 5,

    /** The key for the ECU's factory part number build type, see \c #PREG_VALUE_FACTORY_BUILD_TYPE_T for
     * the associated data.
     */
    PREG_KEY_FACTORY_BUILD_TYPE         = 6
}
PREG_KEY_T;

/** A structure which represents the data for the ECU's serial number key,
 * see \c #PREG_KEY_SERIAL_NUM.
 *
 * The serial number is a 32-bit positive integer. Serial numbers across
 * different families of ECUs do not overlap.
 */
typedef PSY_PACKED struct
{
    /** The serial number is a 32-bit positive integer.
     *
     * \ingroup  c_interface
     */
    U32 serial_num;
}
PREG_VALUE_SERIAL_NUM_T;

/** A structure which represents the structured data for the ECU's date of manufacture key,
 * see \c #PREG_KEY_DATE_OF_MANUFACTURE.
 *
 * The date is composed as (shift) dd:mm:yyyy, where the shift identifies the team involved
 * in the manufacturing process.
 */
typedef PSY_PACKED struct
{
    /** The team shift at time of manufacture. \n
     * Range: [1, 3]
     *
     * \ingroup  c_interface
     */
    U8  shift;

    /** The day of the month of manufacture. \n
     * Range: [1, 31]
     *
     * \ingroup  c_interface
     */
    U8  day;

    /** The month of manufacture. \n
     * Range: [1, 12]
     *
     * \ingroup  c_interface
     */
    U8  month;

    /** The year of manufacture. \n
     * Range: [2010, ..]
     *
     * \ingroup  c_interface
     */
    U16 year;
}
PREG_VALUE_DATE_OF_MANUFACTURE_T;

/** A structure which represents the structured data for the ECU's engineering part number key,
 * see \c #PREG_KEY_ENG_PART_NUM.
 *
 * The engineering part number matches the pattern: prefix letter engineering-part-number.
 * For instance, the engineering part number assigned to the M250-000 is '01T068165', where
 * '01' represents the prefix, 'T' represents the letter and '068165' represents the
 * engineering part number.
 */
typedef PSY_PACKED struct
{
    /** The part number prefix. \n
     * Range: [0, 99]
     *
     * \ingroup  c_interface
     */
    U8  prefix;

    /** The part number letter represented as an ASCII character. \n
     * Range: [A, Z]
     *
     * \ingroup  c_interface
     */
    U8  letter;

    /** The engineering part number. \n
     * Range: [0, 999999]
     *
     * \ingroup  c_interface
     */
    U32 eng_part_num;
}
PREG_VALUE_ENG_PART_NUM_T;

/** A structure which represents the structured data for the ECU's issue-mod key,
 * see \c #PREG_KEY_HW_ISSUE_MOD_NUM.
 *
 * The issue level represents a specific design of PCB. Changes to the issue level may
 * have an effect on the platform library.
 *
 * The modification level represents what changes were performed to the PCB after
 * manufacturing to correct issue level design mistakes. Changes to the modification
 * level should not have an effect on the platform library.
 */
typedef PSY_PACKED struct
{
    /** The PCB issue level. \n
     * Range: [0, 255]
     *
     * \ingroup  c_interface
     */
    U8  issue;

    /** The PCB modification level. \n
     * Range: [0, 255]
     *
     * \ingroup  c_interface
     */
    U8  mod;
}
PREG_VALUE_HW_ISSUE_MOD_NUM_T;

/** A structure which represents the structured data for the ECU's factory part number key,
 *
 * For instance, the factory part number could be '450FT1034', where
 * '450' represents the part_num[0], 'F' represents the letter[0], 'T' represents the letter[1],
 * and '1034' represents the part_num[1].
 * see \c #PREG_KEY_FACTORY_PART_NUM.
 */
typedef PSY_PACKED struct
{
    /** Each numeric part of the factory part number. \n
     * Range: [0, 65535]
     *
     * \ingroup  c_interface
     */
    U16 part_num[2];

    /** The identifier which separates each factory part number, represented as ASCII
     * characters. \n
     * Range: [A, Z]
     *
     * \ingroup  c_interface
     */
    U8  letter[2];
}
PREG_VALUE_FACTORY_PART_NUM_T;

/** A structure which represents the structured data for the ECU's factory part number build type key,
 * see \c #PREG_KEY_FACTORY_BUILD_TYPE.
 */
typedef PSY_PACKED struct
{
    /** The factory part number build type, represented as ASCII characters. \n
     * Range: [A, Z]
     *
     * \ingroup  c_interface
     */
    U8  build_type[2];
}
PREG_VALUE_FACTORY_BUILD_TYPE_T;

/** A union having members of all PREG key structs, to determine the maximum length
 * that might be written when preg_retrieve_value_from_key() is written.
 */
typedef union
{
    PREG_VALUE_SERIAL_NUM_T          num_serial;
    PREG_VALUE_DATE_OF_MANUFACTURE_T man_date;
    PREG_VALUE_ENG_PART_NUM_T        num_part;
    PREG_VALUE_HW_ISSUE_MOD_NUM_T    num_mod;
    PREG_VALUE_FACTORY_PART_NUM_T    num_factory;
    PREG_VALUE_FACTORY_BUILD_TYPE_T  build_factory;
}
PREG_KEYS_T;

/********* Global Prototypes *********/

extern BOOL preg_is_data_available
(
    void
);

extern PREG_RC_T preg_retrieve_value_from_key
(
    PREG_KEY_T   pregf_key,
    void        *pregf_value_buffer
);

/********* Global Variables *********/

/* None */

#endif /* not an unsupported target for PREG */

#endif /* PREG_H */

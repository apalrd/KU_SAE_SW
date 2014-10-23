/*****************************************************************************/
/**
 *  \file    ppid.h
 *  \brief   Public interface to the ISO diagnostic parameter (PID) feature.
 *
 *  Version: $Id: ppid.h 35178 2013-09-10 16:03:01Z jtough $
 *  File:    $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/ppid/ppid.h $
 */

/*  Copyright (C) 2012 Pi Innovo
 *  This document (program) contains proprietary information
 *  which is the property of Pi Innovo
 *  The contents of this document (program) must not be copied
 *  or disclosed to a third party without the prior agreement
 *  of an authorised officer of Pi Innovo
 */

#ifndef PPID_H
#define PPID_H

/********* Includes *********/

/* None */

/********* These macros can be changed *********/

/* None */

/********* These macros must not be changed *********/

/** This is the maximum length of PID data currently supported.
 *
 * \ingroup c_extdiag_interface
 */
/* small enough to prevent excessively long memcpy in critical section */
#define PPID_MAX_PID_BYTE_LEN       512

/** Indicates that ControlParameter from InputOutputControl request
 *  from test tool was "return control to ECU", or
 *  this PID is not currently subject to IOControl.
 *
 * \ingroup c_extdiag_interface
 */
#define PPID_ECU_CONTROLLED         0x00

/** Indicates that ControlParameter from InputOutputControl request
 *  from test tool was "freeze current state", indicating that
 *  this PID is currently subject to override by the tool.
 *
 * \ingroup c_extdiag_interface
 */
#define PPID_CURRENT_STATE_FROZEN   0x05

/** Indicates that ControlParameter from InputOutputControl request
 *  from test tool was "short term adjustment", indicating that
 *  this PID is currently subject to override by the tool.
 *
 * \ingroup c_extdiag_interface
 */
#define PPID_SHORT_TERM_ADJUSTMENT  0x07

/** Flag masks used for attributes of PIDs; low values are used
 * where they may be used in a bitfield to save space when stored
 * as non-volatile PIDs.
 *
 * Bitmask for a J1939 SPN based PID.
 *
 * \ingroup c_extdiag_interface
 */
#define PPID_J1939_SPN_PID          0x01

/** Bitmask for a KWP2000 8-bit based PID.
 *
 * \ingroup c_extdiag_interface
 */
#define PPID_KWP_8BIT_PID           0x02

/** Bitmask for a KWP2000 16-bit based PID.
 *
 * \ingroup c_extdiag_interface
 */
#define PPID_ISO_16BIT_PID          0x04

/** Bitmask for a variable length based PID.
 *
 * \ingroup c_extdiag_interface
 */
#define PPID_VAR_LENGTH             0x08

/** Bitmask for a J1979 8-bit based PID.
 *
 * \ingroup c_extdiag_interface
 */
#define PPID_J1979_8BIT_PID         0x10

/** Bitmask for a PID that can pass its overridden data to the application.
 *
 * \ingroup c_extdiag_interface
 */
#define PPID_RESEND_IN_OUT          0x20

/** Bitmask for a PID stored across power-cycles in non-volatile memory.
 *
 * \ingroup c_extdiag_interface
 */
#define PPID_NON_VOLATILE           0x40

/** Bitmask for a ASCII string based PID.
 *
 * \ingroup c_extdiag_interface
 */
#define PPID_ALPHANUMERIC           0x80

/********* Global Structure Definitions *********/

/** An enumerated type which contains success and failure codes returned by some
 * ISO diagnostic parameter ID (PPID) functions.
 *
 * \ingroup c_extdiag_interface
 */
typedef enum
{
    /** Return code if everything progressed as expected.
     */
    PPID_RC_OK,

    /** Return code if at least one of the arguments could not be used.
     */
    PPID_RC_BAD_ARGS,

    /** Return code if the PID configuration data was invalid for requested operation.
     */
    PPID_RC_BAD_CONFIG_DATA,

    /** No such PID found.
     */
    PPID_RC_NOT_FOUND,

    /** PID value already set so it does not require any initialisation write.
     */
    PPID_RC_ALREADY_SET,

    /** Saving of PIDs to nonvolatile memory is in progress.
     */
    PPID_NV_SAVE_PENDING,

    /** Unspecified error.
     */
    PPID_RC_ERROR
}
PPID_RC_T;

/** This structure collates the data associated with each PID.
 * \note The application may use the ID and size elements.
 * Access to other elements should be made exclusively through
 * library API calls, to avoid data coherency issues.
 *
 * \ingroup c_extdiag_interface
 */
struct PPID_PID_CONST_T   /*  im[LLR.PLAT.PPID 4.2], im[LLR.PLAT.PPID 4.2.1]  */
{
    /** The 16-bit ID of the PID, used by the test tool to address it.
     *  This is a "CommonIdentifier" in KW2000-3 or just "Identifier"
     *  in UDS. The PID may or may not support this type of ID.
     *  This may instead be used for RoutineControl services if appropriate
     *  for this ID.
     * \ingroup c_extdiag_interface
     */
    U16  pid_id;    /* im[LLR.PLAT.PPID 4.15],  im[LLR.PLAT.PPID 4.16] */

    /** The number of bytes of data this PID consists of.
     *
     * \ingroup c_extdiag_interface
     */
    U16  byte_len;

    /** The number of input bytes (used for IOControl state values),
     *  which can be different to the output byte size.
     */
    U16 input_byte_len; /* im[LLR.PLAT.PPID 4.25], im[LLR.PLAT.PPID 4.17] */

    /** This points to the current (application-supplied) values.
     *  Initialised to zero by the platform
     * Do not access the data this points to in user code. It is
     * accessed by the library asynchronously to application execution
     * when requested by an external diagnostic test tool.
     *
     * \ingroup c_extdiag_interface
     */
    U8 * app_supplied_data;  /*  im[LLR.PLAT.PPID 4.18] */

    /** This points to override values set temporarily by the external
     *  test tool. May be NULL if no overrides allowed for this PID.
     * Do not access the data this points to in user code. It is
     * accessed by the library asynchronously to application execution
     * when required by an external diagnostic test tool.
     *
     * \ingroup c_extdiag_interface
     */
    U8 * override_data; /*  im[LLR.PLAT.PPID 4.19]  */

    /** This points to the value which records how this PID is
     * currently being overridden by the external test tool via
     * IOControl messages. Zero means no override.
     * Do not access the data this points to in user code. If modified
     * the platform will be unable to correctly process data overrides.
     *
     * \ingroup c_extdiag_interface
     */
    U8 * override_state;

    /** The ID used to identify if this PID represents a J1939 SPN.
     *
     * \ingroup c_extdiag_interface
     */
    U32 j1939_spn_id;    /* im[LLR.PLAT.PPID 4.45] */

    /** The 8-bit ID used if this PID should be sent in response to
     *  a J1979 service $01 request.
     *
     * \ingroup c_extdiag_interface
     */
    U8  j1979_8bit_id;   /* im[LLR.PLAT.PPID 4.26] (8-bit fields at end of struct to encourage packing) */

    /** The 8-bit LocalIdentifier used if this PID should be sent
     *  in response to a KW2000-3 service $21 request, or modified
     *  via a $30 InputOutputControlByLocalID request.
     *
     * \ingroup c_extdiag_interface
     */
    U8  kwp_8bit_lid;    /* im[LLR.PLAT.PPID 4.27] */

    /** This field notes which type of service(s) this ID should
     *  produce responses for, and related attributes.
     */
    U8  flags;
};

/** This structure collates the data associated with each
 *  non-volatile PID, which is a simpler entity than an
 *  ordinary PID. It forms a header before each PID payload
 *  data in non-volatile memory.
 */
/* Packed to minimise RAM and NV cost of PIDs */
typedef PSY_PACKED struct
{
    /** The number of bytes of data this PID currently consists of.
     */
    U8 byte_len;

    /** The minimum number of bytes of data this PID may consist of.
     */
    U8 min_len;

    /** The maximum number of bytes of data this PID may consist of.
     */
    U8 max_len;

    /** The 16-bit ID of the PID, used by the test tool to address it.
     *  This is a "CommonIdentifier" in KW2000-3 or just "Identifier"
     *  in UDS. The PID may or may not support this type of ID.
     */
    U16  pid_id;

    /** The 8-bit LocalIdentifier used if relevant.
     */
    U8  kwp_8bit_lid;

    /*
     * As each NV PID is buffered in RAM and the remaining fields
     * would have unused bits, they are packed as a bitfield to conserve space:
     */

    /** This field notes which type of service(s) this ID should
     *  produce responses for, and related attributes.
     */
    /*lint -e{46} cannot make bitfield [unsigned] int AND avoid native types simultaneously. */
    U32  flags : 4;

    /* Room for more flag bits or other params here... */

    /** The ID used to identify if this PID represents a J1939 SPN.
     */
    /*lint -e{46} cannot make bitfield [unsigned] int AND avoid native types simultaneously. */
    U32 j1939_spn_id : 19;

#if (PPID_J1939_SPN_PID > 8) || (PPID_KWP_8BIT_PID > 8) || (PPID_ISO_16BIT_PID > 8) || (PPID_VAR_LENGTH > 8)
#error PID type flags do not fit in structure element for NV storage
#endif

}
PPID_NV_PID_T;

struct PPID_8BIT_ID_LOOKUP_T
{
    U8                              id_8bit;
    const struct PPID_PID_CONST_T*  pid_ptr;
};

struct PPID_J1939_SPN_LOOKUP_T
{
    U32                             spn;
    const struct PPID_PID_CONST_T*  pid_ptr;
};

/********* Global Prototypes *********/

extern PPID_RC_T ppid_update_pid
(
    const struct PPID_PID_CONST_T* const ppidf_pid_const_data,
    const U8*                            ppidf_app_supplied_data
);

extern PPID_RC_T ppid_get_pid
(
    const struct PPID_PID_CONST_T* ppidf_pid_const_data,
    U8*                            ppidf_pid_data,
    U8*                            ppidf_override_state
);

extern PPID_RC_T ppid_get_override_data
(
    const struct PPID_PID_CONST_T* ppidf_pid_const_data,
    U8*                            ppidf_override_data,
    U8*                            ppidf_override_state
);

extern PPID_RC_T ppid_set_nv_pid
(
     U8        ppidf_type_flags,
     U8        ppidf_kwp_8bit_id,
     U16       ppidf_pid_id,
     U32       ppidf_j1939_spn_id,
     const U8* ppidf_new_data_ptr,
     U8        ppidf_new_size,
     BOOL      ppidf_only_if_uninit
);

extern PPID_RC_T ppid_get_nv_pid
(
     U8   ppidf_type_flag,
     U32  ppidf_id,
     U8*  ppidf_data_ptr,
     U16  ppidf_min_size,
     U16  ppidf_max_size,
     U16* ppidf_current_size
);

extern PPID_RC_T ppid_delete_nv_pid
(
     U8  ppidf_type_flag,
     U32 ppidf_id
);

extern PPID_RC_T ppid_delete_all_nv_pids(void);

extern PPID_RC_T ppid_get_nv_commit_status(void);

/********* Global Variables *********/

/** This is a list of the ISO 16-bit PIDs the library will maintain.
 *
 * \ingroup c_extdiag_interface
 */
extern const struct PPID_PID_CONST_T ppid_table[];

/** This is the total number of ISO 16-bit PIDs the library will maintain.
 *
 * \ingroup c_extdiag_interface
 */
extern const U16 ppid_num_pids;            /* im[LLR.PLAT.PPID 4.1] */

/** This is a list of the J1979 8-bit PIDs that the library will maintain.
 *
 * \ingroup c_extdiag_interface
 */
extern const struct PPID_8BIT_ID_LOOKUP_T ppid_j1979_8bit_map[];

/** This is the total number of J1979 8-bit PIDs the library will maintain.
 *
 * \ingroup c_extdiag_interface
 */
extern const U16 ppid_num_j1979_ids;

/** This is a list of the KW2000 8-bit PIDs that the library will maintain.
 *
 * \ingroup c_extdiag_interface
 */
extern const struct PPID_8BIT_ID_LOOKUP_T ppid_kwp_8bit_map[];

/** This is the total number of KW2000 8-bit PIDs the library will maintain.
 *
 * \ingroup c_extdiag_interface
 */
extern const U16 ppid_num_kwp_ids;

/** This is a list of the J1939 SPNs that the library will maintain.
 *
 * \ingroup c_extdiag_interface
 */
extern const struct PPID_J1939_SPN_LOOKUP_T ppid_j1939_spn_map[];

/** This is the total number of J1939 SPNs the library will maintain.
 *
 * \ingroup c_extdiag_interface
 */
extern const U16 ppid_num_j1939_spns;

/* To be provided by the specific application or boot loader
 * build, sized appropriately:
 */
extern U8 ppid_nv_buffer[];
extern const U16 ppid_nv_buffer_size;
extern const U8 ppid_num_app_nv_pids;
extern const PPID_NV_PID_T ppid_app_allowed_nv_pids[];
extern const BOOL ppid_allow_only_app_nv;

#endif /* PPID_H */

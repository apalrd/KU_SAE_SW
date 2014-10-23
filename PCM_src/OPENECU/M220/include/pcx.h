/*
 ****************************************************************************
 *
 *  \file    pcx.h
 *  \brief   Interface file to the CAN messaging feature.
 *
 *  Version: $Id: pcx.h 28958 2012-05-05 16:38:33Z jtough $
 *  File:    $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/pcx/pcx.h $
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

#ifndef PCX_H
#define PCX_H

/********* Includes *********/

#include "psy.h"
#include "pio.h"

/********* These macros can be changed *********/

/** This macro declares the error value, returned from pcx_declare_message(),
 * if the declared message could not be accepted (for whatever reason).
 *
 * \ingroup c_interface
 */
#define PCX_CONFIG_ERROR                      ((PCX_HANDLE_T)-1)

/** This macro declares a CAN message which can have any identifier when
 * calling pcx_declare_message().
 *
 * \ingroup c_interface
 */
#define PCX_ANY_CAN_ID                        0xFFFFFFFFUL

/** This macro declares a CAN message identifier to be standard (11-bit) when
 * calling pcx_declare_message().
 *
 * \ingroup c_interface
 */
#define PCX_STANDARD_ID                       ((U8)0)

/** This macro declares a CAN message identifier to be extended (29-bit) when
 * calling pcx_declare_message().
 *
 * \ingroup c_interface
 */
#define PCX_EXTENDED_ID                       ((U8)1)

/** This macro is a bitmask for the return value from calling
 * pcx_receive(). The corresponding bit is set in the return value if
 * data was received.
 *
 * \ingroup c_interface
 */
#define PCX_RX_DATA                           1

/** This macro is a bitmask for the return value from calling
 * pcx_receive(). The corresponding bit is set in the return value if
 * the message was received more than once before pcx_receive() was
 * called.
 *
 * \ingroup c_interface
 */
#define PCX_RX_OVERRUN                        2

/** This macro is a bitmask for the return value from calling
 * pcx_receive(). The corresponding bit is set in the return value if
 * data was received, but the received message length did not match the
 * declared message length.
 *
 * \ingroup c_interface
 */
#define PCX_RX_ERROR                          4

/** This macro declares a data item that has most significant byte
 * ordering, used when packing and unpacking messages using the
 * pcx_vdb_pack_msg() and pcx_vdb_unpack_msg() functions.
 *
 * \ingroup c_interface
 */
#define PCX_MSB_ORDER                         0

/** This macro declares a data item that has least significant byte
 * ordering, used when packing and unpacking messages using the
 * pcx_vdb_pack_msg() and pcx_vdb_unpack_msg() functions.
 *
 * \ingroup c_interface
 */
#define PCX_LSB_ORDER                         1

/** This macro declares a data item to have integer type, used when packing
 * and unpacking messages using the pcx_vdb_pack_msg() and pcx_vdb_unpack_msg()
 * functions.
 *
 * \ingroup c_interface
 */
#define PCX_VAL_INT                           0

/** This macro declares a data item to have 32-bit float type, used when packing
 * and unpacking messages using the pcx_vdb_pack_msg() and pcx_vdb_unpack_msg()
 * functions.
 *
 * \ingroup c_interface
 */
#define PCX_VAL_FLOAT32                       1

/********* These macros must not be changed *********/

/** This is the maximum number of data bytes per CAN message.
 *
 * \ingroup c_interface
 */
#define PCX_MAX_MSG_LENGTH                    ((U8)8)

/** This is the number of CAN busses supported for this target.
 *
 * \ingroup c_interface
 */
#ifdef CFG_X657
#define PCX_NUM_CAN_DEVICES                   3
#else
#define PCX_NUM_CAN_DEVICES                   2
#endif

/********* Global Structure Definitions *********/

/** Error values for debugging -- when an error is found in a call to the PCX
 * API, the feature calls a function with an enumeration from this type.
 *
 * \ingroup  c_interface
 */
typedef enum
{
    /** Error raised if the CAN bus argument to a function is invalid.
     */
    PCX_ERR_BUS_ID_OUT_OF_RANGE           = 1,

    /** Error raised if the data length argument to a function is invalid.
     */
    PCX_ERR_DATA_LENGTH_OUT_OF_RANGE      = 2,

    /** Error raised if the CAN message identifier is out of range for a
     * standard 11-bit identifier.
     */
    PCX_ERR_STD_ID_OUT_OF_RANGE           = 3,

    /** Error raised if the CAN message identifier is out of range for a
     * extended 29-bit identifier.
     */
    PCX_ERR_EXT_ID_OUT_OF_RANGE           = 4,

    /** Error raised if a transmit message is declared for a subsequent time
     * but the length of the CAN transmit message differs from the previous
     * declaration.
     */
    PCX_ERR_SAME_TX_MSG_DIFFERING_ATTRIBS = 5,

    /** Error raised if the number of declared transmit messages exceeds
     * the build time limit of transmit messages.
     */
    PCX_ERR_TOO_MANY_TX_MSGS              = 6,

    /** Error raised if a receive message is declared for a subsequent time.
     */
    PCX_ERR_DUPLICATE_RX_MSG              = 7,

    /** Error raised if the number of declared receive messages exceeds
     * the build time limit of receive messages.
     */
    PCX_ERR_TOO_MANY_RX_MSGS              = 8,

    /** Error raised if an inconsistent duplicate request has already occurred
     * for a CAN bus.
     */
    PCX_ERR_BIT_RATE_IN_CONFIG_DIFFERS    = 9,

    /** Error raised if the baud rate requested when configuring a CAN bus
     * is invalid.
     */
    PCX_ERR_UNSUPPORTED_BIT_RATE          = 10,

    /** Error raised if the referenced CAN bus is not supported for the target
     * ECU.
     */
    PCX_ERR_BUS_ID_IN_CONFIG              = 11,

    /** Error raised if a CAN bus could not be configured for a baud rate after
     * application initialisation is complete. An internal error, this should
     * not occur.
     */
    PCX_ERR_NO_BITRATE_TABLE_MATCH        = 12,

    /** Error raised if an invalid argument is passed to the message pack
     * function.
     */
    PCX_ERR_PACK_MSG_INVALID_PARAM        = 13,

    /** Error raised if an invalid type code is found in the message pack
     * data structure.
     */
    PCX_ERR_PACK_MSG_FIELD_PARAM          = 14,

    /** Error raised if an invalid argument is passed to the message pack
     * function.
     */
    PCX_ERR_UNPACK_MSG_INVALID_PARAM      = 15,

    /** Error raised if an invalid type code is found in the message unpack
     * data structure.
     */
    PCX_ERR_UNPACK_MSG_FIELD_PARAM        = 16,

    /** Error raised if an invalid argument is passed to the VDB message pack
     * function.
     */
    PCX_ERR_PACK_VDB_MSG_INVALID_PARAM    = 17,

    /** Error raised if an invalid argument is passed to the VDB message unpack
     * function.
     */
    PCX_ERR_UNPACK_VDB_MSG_INVALID_PARAM  = 18,

    /** Error raised after application initialisation if a receive message
     * has been declared for CAN bus \e 'n' which has not been configured.
     * \e 'n' is (error_code - PCX_ERR_RX_MSG_FOR_UNCONFIG_BUS_0).
     */
    PCX_ERR_RX_MSG_FOR_UNCONFIG_BUS_0     = 20,

    /** Error raised after application initialisation if a transmit message
     * has been declared for CAN bus \e 'n' which has not been configured.
     * \e 'n' is (error_code - PCX_ERR_TX_MSG_FOR_UNCONFIG_BUS_0).
     */
    PCX_ERR_TX_MSG_FOR_UNCONFIG_BUS_0     = 30
}
PCX_ERROR_T;

/** This enumeration declares the different types of CAN messages, receive and
 * transmit, when used with the pcx_declare_message() function.
 *
 * \ingroup c_interface
 */
typedef enum
{
    /** The declared message will be received.
     */
    PCX_RX_MSG,

    /** The declared message will be transmitted.
     */
    PCX_TX_MSG
}
PCX_MSG_DIR_T;

/** This enumeration declares the different CAN bus states returned by the
 * pcx_get_bus_state() function.
 *
 * \ingroup c_interface
 */
typedef enum
{
    /** The initial state of the CAN bus controller. The controller may transmit
     * active error flags.
     */
    PCX_BUS_ERROR_ACTIVE,

    /** After an accumulation of errors, the CAN bus controller enters
     * the error passive state. In this state, the controller may transmit
     * passive error flags.
     */
    PCX_BUS_ERROR_PASSIVE,

    /** After an excessive accumulation of transmission errors, the CAN bus
     * controller enters the bus-off state. In this stage, the controller will
     * not transmit.
     */
    PCX_BUS_OFF,

    /** If the referenced bus is not available for the ECU target.
     */
    PCX_BUS_INVALID
}
PCX_BUS_STATE_T;

/** This declares a type with enough value range to represent all logical
 * CAN busses for all targets. See \e pio.h for a list of relevant channels for a
 * specific target.
 *
 * \ingroup c_interface
 */
typedef U8 PCX_LCHAN_T;

/** This is the handle type given to CAN messages declared via the
 * pcx_declare_message() function.
 *
 * \ingroup c_interface
 */
typedef S16 PCX_HANDLE_T;

/** Input and output data types for packing and unpacking CAN messages.
 *
 * \ingroup c_interface
 */
typedef enum
{
    /** Represents a 32-bit floating point type. */
    PCX_TYPECODE_F32,

    /** Represents a boolean type. The physical data storage is either
     * an 8-bit integer or 32-bit floating point depending on an argument
     * provided to the pack and unpack functions.
     */
    PCX_TYPECODE_BOOL,

    /** Represents a signed 8-bit integer type. */
    PCX_TYPECODE_S8,

    /** Represents an unsigned 8-bit integer type. */
    PCX_TYPECODE_U8,

    /** Represents a signed 16-bit integer type. */
    PCX_TYPECODE_S16,

    /** Represents an unsigned 16-bit integer type. */
    PCX_TYPECODE_U16,

    /** Represents a signed 32-bit integer type. */
    PCX_TYPECODE_S32,

    /** Represents an unsigned 32-bit integer type. */
    PCX_TYPECODE_U32
}
PCX_DATATYPES_T;

/** This declares the function pointer type for CAN device receive callback.
 */
typedef void (*PCX_RXCALLBACK_T)
(
    /** Pointer to message data bytes. Cannot be NULL. */
    const U8 *pcxf_msg_data,

    /** Number of bytes pointed to. */
    U8        pcxf_len,

    /** TRUE if extended ID, FALSE if standard ID. */
    U8        pcxf_is_ext_can_id,

    /** The CAN message identifier.\n
     *  Range: [0, 2047] if standard identifier\n
     *  Range: [0, 536870911] if extended identifier\n
     */
    U32       pcxf_can_id
);

/** This declares the function pointer type for CAN device transmit callback.
 */
typedef void (*PCX_TXCALLBACK_T)
(
    void
);

/** This structure declares private PCX information for a transmit message.
 * Exposed through this header file only for build time size requirements.
 */
typedef struct
{
    /** CAN message identifier */
    U32               can_id;
    /** CAN bus to transmit on */
    U8                bus;
    /** CAN message data length */
    U8                length;
    /** Handle of CAN buffer used for last transmission */
    U8                last_buffer_used;
    /** True if message is currently queued, false otherwise */
    U8                is_queued;
    /** Number of times a transmit is requested */
    U16               tx_requests;
    /** Number of times a queued message is overwritten before transmission */
    U16               tx_overwrites;
    /** Number of times a transmitted message is acknowledged */
    U16               tx_acks;
    /** True if message in process of being sent by queue emptier task, false otherwise */
    volatile U8       copying_data_now;
    /** True if there is a pending callback for this message */
    volatile U8       isr_flag;
    /** True if despite isr_flag being true, the callback in not executed */
    volatile U8       suspend_callback_flag;
    /** CAN message data */
    U8                data[PCX_MAX_MSG_LENGTH];
    /** Callback that may be called on message transmit complete */
    PCX_TXCALLBACK_T  callback;
}
PCX_TX_MSG_T;

/** This structure declares private PCX information for a receive message.
 * Exposed through this header file only for build time size requirements.
 */
typedef struct
{
    /** CAN message identifier */
    U32               can_id;
    /** CAN bus to transmit on */
    U8                bus;
    /** CAN message data length */
    U8                length;
    /** True if there is a pending callback for this message */
    volatile U8       isr_flag;
    /** True if despite isr_flag being true, the callback in not executed */
    volatile U8       suspend_callback_flag;
    /** True if this data struct stores messages with different CAN IDs */
    U8                any_can_id_flag;
    /** This is the status bitmap of the last receive event */
    U8                status_bitmap;
    /** Timestamp of the last receive event **/
    U32               timestamp;
    /** CAN message data */
    U8                data[PCX_MAX_MSG_LENGTH];
    /** Callback that may be called on message reception */
    PCX_RXCALLBACK_T  callback;
}
PCX_RX_MSG_T;

/** An enumerated type which contains success and failure codes returned by some
 *  CAN messaging feature (PCX) functions.
 *
 * \ingroup  c_interface
 */
typedef enum
{
    /** Return code if everything progressed as expected.
     */
    PCX_RC_OK,

    /** Return code if at least one of the arguments could not be used.
     */
    PCX_RC_BAD_ARGS
}
PCX_RC_T;

/********* Global Prototypes *********/

extern BOOL pcx_config
(
    PCX_LCHAN_T         pcxf_bus_id,
    PIO_CAN_BAUD_RATE_T pcxf_bit_rate_kbit_s
);

extern PCX_HANDLE_T pcx_declare_message
(
    PCX_MSG_DIR_T       pcxf_direction,
    PCX_LCHAN_T         pcxf_bus_id,
    U8                  pcxf_use_extended_id,
    U8                  pcxf_msg_length,
    U32                 pcxf_msg_id
);

extern BOOL pcx_transmit
(
    PCX_HANDLE_T        pcxf_msg_handle,
    const U8           *pcxf_msg_data
);

extern BOOL pcx_transmit_any_id
(
    PCX_HANDLE_T        pcxf_msg_handle,
    U8                  pcxf_len,
    U8                  pcxf_is_extended_id,
    U32                 pcxf_msg_id,
    const U8           *pcxf_msg_data
);

extern U8 pcx_receive
(
    PCX_HANDLE_T        pcxf_msg_handle,
    U8                 *pcxf_msg_data,
    U32                *pcxf_msg_timestamp
);

extern PCX_RC_T pcx_get_transmit_status
(
    PCX_HANDLE_T        pcxf_msg_handle,
    U16                *pcxf_tx_requests,
    U16                *pcxf_tx_overwrites,
    U16                *pcxf_tx_acks
);

extern void pcx_queue_emptier_task
(
    void
);

extern void pcx_pack_msg
(
    U8                 *pcxf_msg_data,
    const void* const  *pcxf_item_ptr,
    const U8           *pcxf_field_start,
    const U8           *pcxf_field_width,
    const U8           *pcxf_is_signed,
    const U8           *pcxf_type_code,
    const U8            pcxf_use_bool_type,
    const U8            pcxf_num_fields
);

extern void pcx_unpack_msg
(
    void * const       *pcxf_item_ptr,
    const U8           *pcxf_msg_data,
    const U8           *pcxf_field_start,
    const U8           *pcxf_field_width,
    const U8           *pcxf_is_signed,
    const U8           *pcxf_type_code,
    const U8            pcxf_use_bool_type,
    const U8            pcxf_num_fields
);

extern void pcx_vdb_pack_msg
(
    const F32* const   *pcxf_item_ptr,
    U8                 *pcxf_msg_data,
    const U8           *pcxf_field_start,
    const U8           *pcxf_field_width,
    const U8           *pcxf_is_signed,
    const U8           *pcxf_valtype,
    const U8           *pcxf_order,
    const F32          *pcxf_eng_min,
    const F32          *pcxf_eng_max,
    const F32          *pcxf_scale,
    const F32          *pcxf_offset,
    const U8            pcxf_clip_scaled,
    const U8            pcxf_use_bool_type,
    const U8            pcxf_num_fields
);

extern void pcx_vdb_unpack_msg
(
    F32 *const         *pcxf_item_ptr,
    U32 *const         *pcxf_item_raw_ptr,
    const U8           *pcxf_msg_data,
    const U8           *pcxf_field_start,
    const U8           *pcxf_field_width,
    const U8           *pcxf_is_signed,
    const U8           *pcxf_valtype,
    const U8           *pcxf_order,
    const F32          *pcxf_eng_min,
    const F32          *pcxf_eng_max,
    const F32          *pcxf_scale,
    const F32          *pcxf_offset,
    const U8            pcxf_clip_scaled,
    const U8            pcxf_use_bool_type,
    const U8            pcxf_num_fields
);

extern void pcx_transmit_callback_config
(
    PCX_HANDLE_T        pcxf_msg_handle,
    PCX_TXCALLBACK_T    pcxf_callback
);

extern void pcx_receive_callback_config
(
    PCX_HANDLE_T        pcxf_msg_handle,
    PCX_RXCALLBACK_T    pcxf_callback
);

extern void pcx_can_callback_task
(
    void
);

extern void pcx_callback_control
(
    PCX_HANDLE_T        pcxf_msg_handle,
    PCX_MSG_DIR_T       pcxf_direction,
    U8                  pcxf_suspend
);

#if !defined(CFG_DONT_USE_DEPRECATED)
/* Deprecated, see pss_set_safety_switch(). */
extern BOOL pcx_is_bus_unavailable
(
    PCX_LCHAN_T         pcxf_bus_id
);
#else
#define pcx_is_bus_unavailable(pcxf_bus_id) pcx_is_bus_unavailable_is_deprecated_see_user_guide()
#endif

extern PCX_BUS_STATE_T pcx_get_bus_state
(
    PCX_LCHAN_T         pcxf_bus_id
);

/********* Global Variables *********/

/** This is the total number of permissible transmit messages.
 *
 * The application code must declare and initialise this variable to be at
 * least the total number of declared transmit messages in the application.
 * It is permissible to set the variable to more than the declared total.
 *
 * Range: [0, 100] messages
 *
 * \ingroup c_interface
 */
extern const PCX_HANDLE_T pcx_tot_allow_msg_tx;

/** This is the total number of permissible receive messages.
 *
 * The application code must declare and initialise this variable to be at
 * least the total number of declared receive messages in the application.
 * It is permissible to set the variable to more than the declared total.
 *
 * Range: [0, 100] messages
 *
 * \ingroup c_interface
 */
extern const PCX_HANDLE_T pcx_tot_allow_msg_rx;

/** This is an array of transmit message structures, representing each of the
 * declared transmit messages. Indexed by message handle.
 *
 * Present in the C-API description only for build time size requirements.
 * The array must be declared and sized by the application. The size of the
 * array must equal \p #pcx_tot_allow_msg_tx (or one if there are no transmit
 * messages). The array is not to be accessed by application code.
 *
 * \ingroup c_interface
 */
extern PCX_TX_MSG_T pcx_tx_msg[];

/** This is an array of receive message structures, representing each of the
 * declared received messages. Indexed by message handle.
 *
 * Present in the C-API description only for build time size requirements.
 * The array must be declared and sized by the application. The size of the
 * array must equal \p #pcx_tot_allow_msg_rx (or one if there are no receive
 * messages). The array is not to be accessed by application code.
 *
 * \ingroup c_interface
 */
extern PCX_RX_MSG_T pcx_rx_msg[];

/** This is an array used to post sort the receive messages into CAN identifier
 * order.
 *
 * Present in the C-API description only for build time size requirements.
 * The array must be declared and sized by the application. The size of the
 * array must equal \p #pcx_tot_allow_msg_rx (or one if there are no receive
 * messages). The array is not to be accessed by application code.
 *
 * \ingroup c_interface
 */
extern PCX_HANDLE_T pcx_sorted_rx_msg[];

/** This is an array of messages queued for transmission for each CAN bus.
 *
 * The array for messages is one larger than the number of transmit messages to
 * distinguish between queue empty and queue full.  The queue for each CAN bus
 * is circular in nature, where the start and end of the queue is defined by
 * pcxl_start_queue[] and pcxl_end_queue[]. Indexed by queue position, then CAN
 * bus.
 *
 * Present in the C-API description only for build time size requirements.  The
 * array must be declared and sized by the application. The size of the first
 * index must equal \p #pcx_tot_allow_msg_tx + 1 (or two if there are no
 * transmit messages). The array is not to be accessed by application code.
 *
 * \ingroup c_interface
 */
extern PCX_HANDLE_T pcx_queued_tx_list[][PCX_NUM_CAN_DEVICES];

#endif /* PCX_H */

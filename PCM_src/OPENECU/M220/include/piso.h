/*****************************************************************************/
/**
 *  \file    piso.h
 *  \brief   Internal interface to the Implementation of the ISO-15765-2
 *           transport protocol feature.
 *
 *  Version: $Id: piso.h 33522 2013-05-03 09:39:45Z cwartnaby $
 *  File:    $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/piso/piso.h $
 */

/*  Copyright (C) 2012 Pi Innovo
 *  This document (program) contains proprietary information
 *  which is the property of Pi Innovo
 *  The contents of this document (program) must not be copied
 *  or disclosed to a third party without the prior agreement
 *  of an authorised officer of Pi Innovo
 */

#ifndef PISO_H
#define PISO_H

/********* Includes *********/

#include "psy.h"
#include "pcx.h"

/********* These macros can be changed *********/

/* None */

/********* These macros must not be changed *********/

/* None */

/********* Enumerated types ************/

/** Reception status types
 *
 * \ingroup hl_interface
 */
typedef enum
{
    /** Packetised message being received
     */
    RX_IN_PROGRESS,

    /** Something went wrong with receive process
     */
    RX_ERROR,

    /** A transport layer error which means no negative response should be sent
     */
    RX_QUIET_ERROR,

    /** Complete message received and ready to use
     */
    RX_COMPLETE,

    /** Ready to be started for listening 
     */
    OK_TO_RX
}
PISO_RX_STATUS;

/** Transmission status types
 *
 * \ingroup hl_interface
 */
typedef enum
{
    /** Packetised message transmission in progress
     */
    TX_IN_PROGRESS,

    /** Gave up e.g. because of transport handshaking problem with other end
     */
    TX_ABORTED,

    /** Now idle having sent a message
     */
    TX_COMPLETE
}
PISO_TX_STATUS;

/** Addressing types
 *
 * \ingroup hl_interface
 */
typedef enum
{
    RX_PHY_ADDR,
    RX_FUNC_ADDR
}
PISO_RX_ADDR_T;

/********* Global Structure Definitions *********/

/** Structure for client to declare the receive message
 */
struct PISO_MESSAGE_T
{
    PCX_HANDLE_T    piso_rx_msg_handle;             /**< Rx message handle for requests received over Physical address */
    PCX_HANDLE_T    piso_func_rx_msg_handle;        /**< Rx message handle for requests received over Functional address */
    PCX_HANDLE_T    piso_tx_msg_handle;             /**< Tx message handle */
    PISO_RX_ADDR_T  piso_rx_addressing;             /**< Physical or Functional addressing of the request currently in the Rx buffer */
    U8 *            rx_buffer_ptr;                  /**< pointer to actual data being received */
    S16             rx_buffer_size;                 /**< The max Rx buffer size for request over Physical address */
    S16             rx_bytes_to_receive;            /**< The remaining bytes still to be received */
    S16             rx_msg_len;                     /**< Length of complete message */
    U16             rx_byte_position;               /**< Current position to receive next byte */
    S8              rx_next_consec_expected;        /**< The sequence number of the next Consecutive \n
                                                     * frame that is expected.
                                                     */
    PISO_RX_STATUS  rx_status;                      /**< The status of Rx process */

    const U8 *      tx_buffer_ptr;                  /**< pointer to actual data being transmitted*/
    S16             tx_buffer_size;
    S16             tx_byte_position;
    S16             tx_msg_len;
    S16             tx_frame_to_send_next;          /**< The next frame to be transmitted */
    S16             tx_packets;                     /**< The number of packets to be transmitted */
    PISO_TX_STATUS  tx_status;                      /**< The status of Tx process */

    U32             piso_flow_control_timer;        /**< used to time a wait for a flow control \n
                                                     * message from the tester. Units are \n
                                                     * milliseconds
                                                     */
    U32             piso_consec_frame_timer;        /**< used to time a wait for a consecutive frame \n
                                                     * message from the tester (milliseconds) \n
                                                     */
    U32             piso_lack_of_dialog_timer;      /**< Time from last message in miliseconds. */
    U32             piso_lack_of_dialog_timeout;    /**< Timeout for Lack of communication over CAN */
    BOOL            piso_can_comm_timeout;          /**< Indicates timeout of communication over CAN */
    BOOL            piso_rx_overrun;                /**< Indicates that the received message has \n
                                                     * not been consumed in time
                                                     */
};

/********* Global Prototypes *********/

extern void piso_client_task
(
    void
);

/********* Global Variables *********/

#endif /* PISO_H */

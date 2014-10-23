/*
 *****************************************************************************
 *
 *  Project:        OpenECU
 *  Version:        $Id: pdg.h 36178 2013-11-12 11:30:40Z cwartnaby $
 *  File:           $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/pdg/pdg.h $
 *  Description:    Diagnostics feature header file.
 *
 *  Copyright (C) 2013 Pi Innovo
 *  This document (program) contains proprietary information
 *  which is the property of Pi Innovo
 *  The contents of this document (program) must not be copied
 *  or disclosed to a third party without the prior agreement
 *  of an authorised officer of Pi Innovo
 *
 *  Notes:          none
 *
 *****************************************************************************
 */

#ifndef PDG_H
#define PDG_H

/********* Includes *********/

#include "psy_types.h"
#include "pcx.h"
#include "pdtc.h"
#include "ppid.h"
#include "pio.h"

/********* These macros can be changed *********/

/** The maximum supported size of UDS security callback function
 *  (see #PDG_SECURITY_CALLBACK_FN_T).
 *
 * \ingroup c_extdiag_interface
 */
#define PDG_SECURITY_FN_MAX_SIZE 2048

/** The maximum supported size of UDS security seed
 *  (see #PDG_SECURITY_CALLBACK_FN_T).
 *
 * \ingroup c_extdiag_interface
 */
#define PDG_MAX_SEED_SIZE   ((U8) 8u)

/********* These macros must not be changed *********/

/* Define the diagnostic message length */
#define PDG_MESSAGE_LENGTH  ((U8) 0x08)    /* full-length frames */


/** Default session entered automatically at startup, by tool
 *  request or by timeout of another session type
 *
 * \ingroup c_extdiag_interface
 */
#define PDG_SESSION_UDS_DEFAULT      ((U8) 0x01)

/** Programming session entered  by tool request (will not
 *  be seen in application running mode)
 *
 * \ingroup c_extdiag_interface
 */
#define PDG_SESSION_UDS_PROGRAMMING  ((U8) 0x02)

/** Extended session entered  by tool request
 *
 * \ingroup c_extdiag_interface
 */
#define PDG_SESSION_UDS_EXTENDED     ((U8) 0x03)

/** Limit on number of specific security levels that can be assigned to a service
 *
 * \ingroup c_extdiag_interface
 */
#define PDG_NUM_SEC_LEVELS_PER_SERVICE 3  /* If altered, NVM file format must change! */

/********* Global Structure Definitions **************************************/

/** Diagnostic feature return codes
 *
 * \ingroup c_extdiag_interface
 */
typedef enum
{
    /** Everything okay.
     *
     * \ingroup c_extdiag_interface
     */
    PDG_RC_OK,

    /** The requested infotype is not recognised.
     *
     * \ingroup c_extdiag_interface
     */
    PDG_RC_BAD_INFOTYPE,

    /** A null pointer was passed as an argument
     * or an incorrect string length was given
     * or unable to find the given subnet.
     *
     * \ingroup c_extdiag_interface
     */
    PDG_RC_BAD_ARGS,

    /** The requested infotype is handled by the platform.
     *
     * \ingroup c_extdiag_interface
     */
    PDG_RC_PLATFORM_INFOTYPE,

    /** User is not licensed for this feature
     *
     * \ingroup c_extdiag_interface
     */
    PDG_RC_BAD_LICENSE
}
PDG_RC_T;


/** Return codes by the application to indicate how it would like the PDG
 *  feature to continue handling the message just received.
 *
 * \ingroup c_extdiag_interface
 */
typedef enum
{
    /** Construct reply according to normal platform behaviour.
     *
     * \ingroup c_extdiag_interface
     */
    PDG_STANDARD_PLATFORM_REPLY,

    /** Do not send any response to this message at all.
     *
     * \ingroup c_extdiag_interface
     */
    PDG_STAY_SILENT,

    /** Cease normal processing of this message, and transmit the
     *  data loaded into the transmit buffer by the application
     *  callback routine instead.
     *
     * \ingroup c_extdiag_interface
     */
    PDG_SEND_WHOLE_APP_MSG,       /* send what the app prepares entirely, could be +ve or -ve response */

    /** For a PID request, use the ID value bytes placed in the
     *  transmit buffer by the application callback routine
     *  and continue processing the rest of the message as normal.
     *
     * \ingroup c_extdiag_interface
     */
    PDG_SEND_WITH_APP_ID_DATA,

    /** For a PID request, omit the ID echo and value bytes for
     *  this PID, but continue processing the rest of the request
     *  (which may include requests for other PIDs) as usual.
     *
     * \ingroup c_extdiag_interface
     */
    PDG_SEND_OMITTING_THIS_ID
}
PDG_CALLBACK_OUTCOME_T;


/** Communication type parameter for the communication control diagnostic
 *  service. Encoded as per table B.1 in Annex B of IS0 14229-1:2006(E).
 *
 * \ingroup c_extdiag_interface
 */
/* Packed to minimise memory footprint */
typedef PSY_PACKED enum
{
    /** All application-related communication
     *  (inter-application signal exchange between multiple in-vehicle servers).
     *
     * \ingroup c_extdiag_interface
     */
    PDG_NORMAL_MSGS             = 1,

    /** All network-management-related communication
     *
     * \ingroup c_extdiag_interface
     */
    PDG_NETWORK_MSGS            = 2,

    /** All network management and application-related communication
     *
     * \ingroup c_extdiag_interface
     */
    PDG_NORMAL_AND_NETWORK_MSGS = 3
}
PDG_CC_COMM_TYPE_T;


/** The subfunction parameter controlType for the communication control
 *  diagnostic service. Encoded as per table 53 of IS0 14229-1:2006(E).
 *
 * \ingroup c_extdiag_interface
 */
/* Packed to minimise memory footprint */
typedef PSY_PACKED enum
{
    /** Indicates inconsistent control types for network and normal messages
     *  where the application requested communication type is both network and
     *  normal messages.
     *
     * \ingroup c_extdiag_interface
     */
    PDG_MSG_CTRL_INCONSISTENT = -1,

    /** Indicates the reception and transmission of messages are enabled for the
     *  specified communication type.
     *
     * \ingroup c_extdiag_interface
     */
    PDG_ENABLE_RX_AND_TX = 0,

    /** For the specified communication type indicates the reception of messages
     *  are enabled and the transmission of messages are disabled.
     *
     * \ingroup c_extdiag_interface
     */
    PDG_ENABLE_RX_AND_DISABLE_TX = 1,

    /** For the specified communication type indicates the reception of messages
     *  are disable and the transmission of messages are enabled.
     *
     * \ingroup c_extdiag_interface
     */
    PDG_DISABLE_RX_AND_ENABLE_TX = 2,

    /** Indicates the reception and transmission of messages are disabled for
     *  the specified communication type.
     *
     * \ingroup c_extdiag_interface
     */
    PDG_DISABLE_RX_AND_TX = 3
}
PDG_CC_CTRL_TYPE_T;

/** Controls whether certain services are allowed to run, and if so whether
 *  they require any or specific security levels to have been unlocked.
 *
 * \ingroup c_extdiag_interface
 */
/* Packed to minimise memory footprint */
typedef PSY_PACKED enum
{
    /** Always allowed regardless of security status.
     *
     * \ingroup c_extdiag_interface
     */
    PDG_SECURITY_WORKS_WITHOUT,

    /** Allowed so long as some security level has been unlocked.
     *
     * \ingroup c_extdiag_interface
     */
    PDG_SECURITY_ANY_LEVEL,

    /** Allowed only if a security level has been unlocked that is in the
     *  specific list required for this service to be enabled.
     *
     * \ingroup c_extdiag_interface
     */
    PDG_SECURITY_SPECIFIED_LEVELS,

    /** Service is never allowed regardless of security.
     *
     * \ingroup c_extdiag_interface
     */
    PDG_SECURITY_NEVER_ALLOWED
}
PDG_SECURITY_OPTION_T;

/** Callback function pointer type for general callback.
 *
 * Every time PDG receives a request, if a callback function
 * of this type is supplied, it will be called. This gives
 * the application code the opportunity to perform any
 * specific processing that overrides the normal platform
 * behaviour.
 *
 * \param[in] pdgf_rx_msg_buff
 *    The start of the ISO16765-2 receive buffer containing
 *    the request message bytes (e.g. element 0 will be the
 *    service ID).
 *
 * \param[in] pdgf_rx_msg_len
 *    The length of the ISO16765-2 request received.
 *
 * \param[in,out] pdgf_tx_msg_buff
 *    A pointer to the start of the transmit buffer in
 *    which any response message should be constructed.
 *
 * \param[out] pdgf_tx_msg_len
 *    The size of the message (if any) which has been constructed
 *    by the application in the transmit buffer is returned
 *    through this pointer.
 *
 * \param[in] pdgf_max_tx_msg_len
 *    The available space in the ISO16765-2 transmit buffer. The
 *    application must not attempt to construct a message longer
 *    than this.
 *
 * \param[in] pdgf_physically_addressed
 *    Whether the request message was received using the physical
 *    address for this ECU rather than the functional address
 *    used to interrogate all ECUs.
 *
 * \return
 *    See #PDG_CALLBACK_OUTCOME_T.
 *
 * \ingroup c_extdiag_interface
 */
typedef PDG_CALLBACK_OUTCOME_T (*PDG_GENERAL_CALLBACK_FN_T)
(
    const U8 *pdgf_rx_msg_buff,
    S16       pdgf_rx_msg_len,
    U8       *pdgf_tx_msg_buff,
    S16      *pdgf_tx_msg_len,
    S16       pdgf_max_tx_msg_len,
    BOOL      pdgf_physically_addressed
);

/** Callback function pointer type for the ID request callback.
 *
 * Every time PDG receives a request for an ID value, if a callback function
 * of this type is supplied, it will be called. This gives
 * the application code the opportunity to inject custom values
 * computed at the time of the request for the corresponding PID.
 * Alternatively, the application may opt to override the entire
 * message response.
 *
 * \param[in] pdgf_id_requested
 *    A pointer to the PID structure for the ID that has been
 *    requested, if it is defined; otherwise NULL for an unknown PID
 *    (which the application may still choose to provide a value for).
 *
 * \param[in] pdgf_rx_msg_buff
 *    The start of the ISO16765-2 receive buffer containing
 *    the request message bytes (e.g. element 0 will be the
 *    service ID).
 *
 * \param[in] pdgf_rx_msg_len
 *    The length of the ISO16765-2 request received.
 *
 * \param[in] pdgf_rx_id_offset
 *    The index into the receive message buffer at which the
 *    first byte of the ID being requested exists. This will
 *    be a single byte for KW2000-3 LocalIdentifier or J1979 $01
 *    requests, but two bytes for KW20003 CommonIdentifier
 *    or UDS Identifier requests.
 *
 * \param[in,out] pdgf_tx_msg_buff
 *    A pointer to the start of the transmit buffer in
 *    which any complete response message should be constructed.
 *
 * \param[out] pdgf_tx_msg_len
 *    The size of the complete response message (if any) which has
  *   been constructed
 *    by the application in the transmit buffer is returned
 *    through this pointer.
 *
 * \param[in] pdgf_max_tx_msg_len
 *    The available space in the ISO16765-2 transmit buffer. The
 *    application must not attempt to construct a message longer
 *    than this.
 *
 * \param[in] pdgf_tx_id_data_offset
 *    The index into the transmit message buffer at which the
 *    first byte of the ID value should be placed by the
 *    application, if it does so.
 *
 * \param[out] pdgf_tx_id_data_len
 *    The size of the value (if any) which has been placed
 *    in the transmit buffer for this ID by the application
 *    is returned through this pointer.
 *
 * \param[in] pdgf_max_id_data_len
 *    The maximum size allowed for the value bytes for this
 *    ID to avoid transmit buffer overrun. The application must
 *    not attempt to write more bytes for this ID than this size.
 *
 * \param[in] pdgf_physically_addressed
 *    Whether the request message was received using the physical
 *    address for this ECU rather than the functional address
 *    used to interrogate all ECUs.
 *
 * \return
 *    See #PDG_CALLBACK_OUTCOME_T.
 *
 * \ingroup c_extdiag_interface
 */
typedef PDG_CALLBACK_OUTCOME_T (*PDG_ID_REQUEST_CALLBACK_FN_T)
(
    const struct PPID_PID_CONST_T *pdgf_id_requested, /* NULL if not in table */
    const U8                      *pdgf_rx_msg_buff,
    S16                            pdgf_rx_msg_len,
    S16                            pdgf_rx_id_offset,
    U8                            *pdgf_tx_msg_buff,
    S16                           *pdgf_tx_msg_len,
    S16                            pdgf_max_tx_len,
    S16                            pdgf_tx_id_data_offset,
    S16                           *pdgf_tx_id_data_len,
    S16                            pdgf_max_id_data_len,
    BOOL                           pdgf_physically_addressed
);

/** Callback function pointer type for the security callback.
 *
 * Every time PDG receives a SecurityAccess ($27) request, it
 * will call a function of this type if provided in your application.
 * Using a callback in this way allows you to implement your own,
 * confidential algorithm. You must provide a function of this
 * type if the use-security-fn setting in the interface file is TRUE.
 *
 * In order to work during flash reprogramming, this function is
 * copied to non-volatile memory before the application code is
 * erased. This means that the code must be relocatable.
 *
 * \warning If this function calls another function, including a
 *          compiler-generated arithmetic utility, it will fail
 *          to run correctly once relocated. This function must
 *          be written with great care.
 *
 * \note    Your function must
 *          be immediately followed in memory by an end marker
 *         (see #PDG_SECURITY_END_FN_T).
 *
 * The second byte of the request message is the securityAccessType
 * parameter (refer to the UDS/ISO 14229-1 specification). Which
 * values you support to is your own choice. However, odd values
 * must be used for requestSeed and even values for sendKey.
 *
 * If the request is requestSeed, you are required to provide seed
 * bytes which will then be sent back to the test tool in a positive
 * response message.
 *
 * If the request is sendKey, you should validate the key in the
 * request message against the previously sent seed, and return
 * a negative response code if you consider the key invalid or
 * zero otherwise.
 *
 * If the option to enable security during UDS flash reprogramming is
 * enabled then the platform will only proceed if a valid key
 * has been accepted. (See iso-diagnostics group .capi file options for
 * details and an example security algorithm function.)
 *
 * \param[in] pdgf_request_message
 *    A pointer to the complete request message from the diagnostic
 *    test tool.
 *
 * \param[in] pdgf_request_message_len
 *    The complete byte length (including service ID) of the
 *    request message from the diagnostic test tool.
 *
 * \param[in,out] pdgf_seed_buffer
 *    The buffer in which this function should place the seed
 *    bytes to return to the diagnostic test tool; the same
 *    seed bytes are made available if the function is being
 *    called to validate a key. Fill the buffer from element
 *    zero first.
 *
 * \param[out] pdgf_seed_len
 *    The size in bytes of the seed value that this function
 *    is providing, if a seed is requested.
 *    Range: [1, PDG_MAX_SEED_SIZE].
 *
 * \param[in] pdgf_random
 *    A 32-bit pseudorandom number provided by the platform
 *    library that may be used as the basis of a seed value.
 *    \note This is not a random number of high cryptographic
 *          quality.
 *
 * \return
 *    Zero if the platform should emit a positive response;
 *    otherwise, the negative response code that should be sent.
 *
 * \ingroup c_extdiag_interface
 */
typedef U8 (*PDG_SECURITY_CALLBACK_FN_T)
(
    const U8  *pdgf_request_message,
    U16        pdgf_request_message_len,
    U8        *pdgf_seed_buffer,
    U8        *pdgf_seed_len,
    U32        pdgf_random
);

/** Function pointer type to mark the end of the security callback.
 *
 * See also #PDG_SECURITY_CALLBACK_FN_T.
 *
 * The function you provide of this type must immediately follow
 * the security callback function you provide for UDS. It is
 * used by the platform to compute the size of the security
 * function so that it can be copied to non-volatile memory.
 *
 * \ingroup c_extdiag_interface
 */
typedef void (*PDG_SECURITY_END_FN_T)
(
     void
);

/********* Global Prototypes *********/

extern void pdg_client_task
(
    void
);

extern void pdg_inhibit_reprogramming
(
    U8 pdgf_inhibit
);

extern U8 pdg_get_active_session_type
(
    void
);

#ifndef CFG_PRG_BUILD
extern PDG_RC_T pdg_set_infotype
(
    PIO_INFOTYPE_T  pdgf_infotype_id,
    const U8       *pdgf_infotype_data,
    U8              pdgf_infotype_length,
    BOOL            pdgf_pending
);
#endif

extern PDG_CC_CTRL_TYPE_T pdg_get_comm_ctrl_state
(
    PDG_CC_COMM_TYPE_T pdgf_communication_type,
    U8 pdgf_subnet_number
);

extern PDG_RC_T pdg_comm_ctrl_cond_not_correct
(
    BOOL pdgf_conditions_not_correct,
    U8   pdgf_subnet_id,
    PDG_CC_COMM_TYPE_T pdgf_comm_type
);

/********* Global Variables *********/

/** To be supplied by application-derived code: */
/** Set true if ISO diagnostics functionality is enabled, set false otherwise.
 *
 * \ingroup c_interface
 */
extern const BOOL                       pdg_enabled;
extern const volatile U32               pdgc_can_tx_id;
extern const volatile BOOL              pdgc_can_tx_id_extd;
extern const volatile U32               pdgc_can_rx_id;
extern const volatile BOOL              pdgc_can_rx_id_extd;
extern const volatile PCX_LCHAN_T       pdgc_can_bus_id;

/** Calibration to determine the minimum emissions severity of DTCs to be reported
 *
 * \ingroup c_extdiag_interface
 */
extern const volatile PIO_EMISSION_SEV_TYPE_T pdgc_emissions_report_min_sev;   /* im[LLR.PLAT.PDG.INTERF.010] */

extern const volatile PIO_SERVICE_03_OVERRIDE_OPTIONS_T pdgc_override_service_03;
extern const volatile PIO_SERVICE_07_OVERRIDE_OPTIONS_T pdgc_override_service_07;
extern const volatile PIO_SERVICE_0A_OVERRIDE_OPTIONS_T pdgc_override_service_0a;

extern U8 pdg_iso_rx_buffer[];
extern U8 pdg_iso_tx_buffer[];
extern const S16 pdg_iso_rx_buffer_size;
extern const S16 pdg_iso_tx_buffer_size;

extern const volatile U32   pdgc_func_can_rx_id;

extern const PDG_GENERAL_CALLBACK_FN_T    pdg_general_callback_ptr;
extern const PDG_ID_REQUEST_CALLBACK_FN_T pdg_id_request_callback_ptr;
extern const PDG_SECURITY_CALLBACK_FN_T   pdg_security_callback_ptr;
extern const PDG_SECURITY_END_FN_T        pdg_security_end_ptr;

extern const PDG_SECURITY_OPTION_T pdg_security_flash_allowed_option;
extern const PDG_SECURITY_OPTION_T pdg_security_mem_read_allowed_option;
extern const U8 pdg_num_flash_security_levels;
extern const U8 pdg_specific_flash_security_level[];
extern const U8 pdg_num_mem_read_security_levels;
extern const U8 pdg_specific_mem_read_security_level[];

extern const BOOL pdg_mem_read_ok_def_session;
extern const BOOL pdg_mem_read_ok_extd_session;
extern const BOOL pdg_mem_read_ok_prog_session;
extern const BOOL pdg_mem_read_needs_security;

extern const BOOL pdg_active_session_has_id16;
extern const U16  pdg_active_session_iso_16bit_id;
extern const BOOL pdg_active_session_has_id8;
extern const U8   pdg_active_session_kwp_8bit_id;

extern U8 pdg_session_type;

#endif /* PDG_H */

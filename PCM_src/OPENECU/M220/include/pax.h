/*
 *****************************************************************************
 *
 *  Project:        OpenECU
 *  Version:        $Id: pax.h 34565 2013-07-23 19:33:45Z sborders $
 *  File:           $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/pax/pax.h $
 *  Description:    Header file containing definitions of global variables,
 *                  constants and procedures for the PAX feature.
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

#ifndef PAX_H
#define PAX_H

/********* Includes *********/

#include "psy.h"

/********* These macros can be changed *********/

/* None */

/********* These macros must not be changed *********/

/** Highest count value for A/D conversions.
 */
#define PAX_ADC_COUNT_MAX  4096

/********* Global Structure Definitions *********/

/** This declares a type with enough value range to represent all logical
 * channels for all targets. See \e pio.h for a list of relevant channels for a
 * specific target.
 *
 * \ingroup c_interface
 */
typedef U16 PAX_LCHAN_T;

/** An enumerated type which contains success and failure codes returned by some
 * analogue input feature (PAX) functions.
 *
 * \ingroup c_interface
 */
typedef enum
{
    /** Return code if everything progressed as expected.
     */
    PAX_RC_OK,

    /** Return code if an internal error occurred which was the result of a
     * software error.
     */
    PAX_RC_SW_ERROR,

    /** Return code if a hardware error occurred which stopped a channel being
     * sampled or actuated.
     */
    PAX_RC_HW_ERROR,

    /** Return code if at least one of the arguments could not be used.
     */
    PAX_RC_BAD_ARGS
}
PAX_RC_T;

/** Error values for debugging -- when an error is found when calling the
 * analogue input feature (PAX), the API calls a function with an enumeration
 * from this type.
 *
 * \ingroup  c_interface
 */
typedef enum
{
    /** Error raised if the analogue input function finds an invalid argument.
     */
    PAX_ADC_INPUT_INVALID_ARG                       = 1000,

    /** Error raised if the constant current output function finds an invalid
     * argument.
     */
    PAX_CC_OUTPUT_INVALID_ARG                       = 1001,

    /** Error raised if the analogue channel 'n' is not supported.\n
     * 'n' is (error_code - PAX_CHANNEL_INVALID).
     */
    PAX_CHANNEL_INVALID                             = 2000,

    /** Error raised if the channel 'n' cannot be used as an analogue input.\n
     * 'n' is (error_code - PAX_ADC_INPUT_CHANNEL_UNSUPPORTED).
     */
    PAX_ADC_INPUT_CHANNEL_UNSUPPORTED               = 3000,

    /** Error raised if the channel 'n' cannot be used as an analogue output.\n
     * 'n' is (error_code - PAX_CC_OUTPUT_CHANNEL_UNSUPPORTED).
     */
    PAX_CC_OUTPUT_CHANNEL_UNSUPPORTED               = 4000
}
PAX_ERROR_CODE_T;

/********* Global Prototypes *********/

extern PAX_RC_T pax_adc_input
(
    PAX_LCHAN_T  paxf_lchan,
    S16         *paxf_adc,
    BOOL         paxf_init
);

extern PAX_RC_T pax_cc_output
(
    PAX_LCHAN_T  paxf_lchan,
    S16          paxf_cc,
    BOOL         paxf_init
);

#if !defined(CFG_DONT_USE_DEPRECATED)
extern void pax_set_input_update_rate
(
    PAX_LCHAN_T  paxf_lchan
);
#else
#define pax_set_input_update_rate(paxf_lchan) pax_set_input_update_rate_is_deprecated_see_user_guide()
#endif

#if !defined(CFG_DONT_USE_DEPRECATED)
extern void pax_set_output_update_rate
(
    PAX_LCHAN_T  paxf_lchan
);
#else
#define pax_set_output_update_rate(paxf_lchan) pax_set_output_update_rate_is_deprecated_see_user_guide()
#endif

/********* Global Variables *********/

/* None */

#endif /* PAX_H */

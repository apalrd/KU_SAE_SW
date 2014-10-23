/*
 *****************************************************************************
 *
 *  Project:        OpenECU
 *  Version:        $Id: pfc.h 35877 2013-10-25 19:44:23Z sborders $
 *  File:           $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/pfc/pfc.h $
 *  Description:    Public declarations for the Flash Code feature.
 *
 *  Copyright (C) 2013,2012 Pi Innovo
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

#ifndef PFC_H
#define PFC_H

/********* Includes *********/

#include "psy.h"

/********* These macros can be changed *********/

/* None */

/********* These macros must not be changed *********/

/* None */

/********* Global Structure Definitions *********/

/* This is the list of possible system flash codes. Note that codes 111 and 999
 * are reserved. The code values are derived by entering each digit, in reverse,
 * in nybbles. For each nybble, a value in the range [1, 9] is valid.
 */
typedef enum
{
    PFC_FC_PRG_PROG_DONE          = 0x113,
    PFC_FC_PRG_PROG_FAIL          = 0x213,
    PFC_FC_PSC_INVALID_LICENSE    = 0x222,
    PFC_FC_PRG_FEPS_NEG           = 0x211,
    PFC_FC_PRG_FEPS_HIGH          = 0x311,
    PFC_FC_PRG_FEPS_LESS          = 0x411,
    PFC_FC_PRG_NO_VALID_APP       = 0x511,
    PFC_FC_PRG_FEPS_HW_FAILURE    = 0x611,
    PFC_FC_PRG_RESET_COUNT_FAIL   = 0x711,
    PFC_FC_PRG_CHECKSUM_FAIL      = 0x811,
    PFC_FC_PRG_ISO_FEPS_LESS      = 0x911,
    PFC_FC_PRG_ADC_COMBINATION    = 0x021,
    PFC_FC_PRG_UNKNOWN            = 0x121,
    PFC_FC_PBT_PRIMARY            = 0x221
}
PFC_FC_T;

/********* Global Prototypes *********/

extern void pfc_task
(
    void
);

extern void pfc_add_code
(
    PFC_FC_T pfcf_fc
);

/********* Global Variables *********/

/* None */

#endif /* PFC_H */


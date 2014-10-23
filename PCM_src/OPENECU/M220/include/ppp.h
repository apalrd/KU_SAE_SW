/*
 *****************************************************************************
 *
 *  Project:        OpenECU
 *  Version:        $Id: ppp.h 28958 2012-05-05 16:38:33Z jtough $
 *  File:           $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/ppp/ppp.h $
 *  Description:    External interface and definitions for the PPP (PixCal
 *                  Comms Protocol) feature.
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

#ifndef PPP_H
#define PPP_H

/********* Includes *********/

#include "psy.h"

/********* These macros can be changed *********/

/* None */

/********* These macros must not be changed *********/

/* None */

/********* Global Structure Definitions *********/

/* Structure of table containing cross-refs between tunable paramater ID no.s, the
 * address of the tune in RAM and the address of the corresponding cal in flash,
 * plus sizing information
 */
struct tune_table_struct
{
    U8* tune_ptr;       /* ptr to tune in RAM */
    U8* cal_ptr;        /* ptr to corresponding cal in flash */
    U8  size1;          /* no. of X elements if 1D, or Y elements if 2D */
    U8  size2;          /* no. of X elements if 2D, or 0 if 1D */
    U8  el_size;        /* size of 1 element in bytes */
};

/********* Global Prototypes *********/

extern void ppp_client_task
(
    void
);

/********* Global Variables *********/

extern const U8 ppp_enabled;             /* Whether Pixcal RS232 comms is enabled or not */
extern       U8 ppp_tune_store_trigger;  /* Flag to trigger storing tunes in flash */

#endif /* PPP_H */

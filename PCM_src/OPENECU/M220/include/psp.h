/*****************************************************************************/
/**
 *  \file    psp.h
 *  \brief   Public interface to the serial peripheral feature.
 *
 *  Version: $Id: psp.h 34569 2013-07-23 22:08:10Z rdoebler $
 *  File:    $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/psp/psp.h $
 */

/*  Copyright (C) 2013 Pi Innovo
 *  This document (program) contains proprietary information
 *  which is the property of Pi Innovo
 *  The contents of this document (program) must not be copied
 *  or disclosed to a third party without the prior agreement
 *  of an authorised officer of Pi Innovo
 */

#ifndef PSP_H
#define PSP_H

/********* Includes *********/

#include "psy.h"

/********* These macros must not be changed *********/

/* None */

/********* These macros can be changed *********/

/* None */

/********* Global Structure Definitions *********/

/* None */

/********* Global Prototypes *********/

extern void psp_receive_task
(
    void
);

extern void psp_spi_trigger
(
    void
);

extern S16 psp_read
(
    U8    pspf_pchan
);

extern void psp_write
(
    U8    pspf_pchan,
    S16   pspf_data
);

/********* Global Variables *********/

/* None */

#endif /* PSP_H */

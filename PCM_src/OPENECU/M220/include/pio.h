/*
 *****************************************************************************
 *
 *  Project:        OpenECU
 *  Description:    Top level I/O include file.
 *
 *  Copyright (C) 2014 Pi Innovo
 *  This document (program) contains proprietary information
 *  which is the property of Pi Innovo
 *  The contents of this document (program) must not be copied
 *  or disclosed to a third party without the prior agreement
 *  of an authorised officer of Pi Innovo.
 *
 *  Notes:          Auto-generated from 'gen_io.py' (version 2.2.1 (r2014-igloo-dev4))
 *                  at Tue Mar 18 11:50:32 2014 (local time).
 *                  Do not modify.
 *
 *****************************************************************************
 */

#ifndef PIO_H
#define PIO_H

/********* Includes *********/

#if defined(CFG_M220)

#if defined(CFG_SUB_000)
#if !defined(PIO_INTERNAL_M220_000_H)
#include "pio_m220_000.h"
#endif

#else
#error "mpc5534_lib/include/pio.h: unrecognised configuration for target-subtype (ensure macro CFG_SUB_[TARGET-SUBTYPE] is defined)."
#endif

#else
#error "mpc5534_lib/include/pio.h: unrecognised configuration for target (ensure macro CFG_[TARGET-NAME] is defined)."
#endif

/********* These macros can be changed *********/

/* None */

/********* These macros must not be changed *********/

/* None */

/********* Global Structure Definitions *********/

/* None */

/********* Global Prototypes *********/

/* None */

/********* Global Variables *********/

/* None */

#endif /* PIO_H */

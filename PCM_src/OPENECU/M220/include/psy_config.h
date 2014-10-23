/*
 *****************************************************************************
 *
 *  Project:        OpenECU
 *  Description:    Select appropriate feature configurations for selected target.
 *
 *  Copyright (C) 2014 Pi Innovo
 *  This document (program) contains proprietary information
 *  which is the property of Pi Innovo
 *  The contents of this document (program) must not be copied
 *  or disclosed to a third party without the prior agreement
 *  of an authorised officer of Pi Innovo.
 *
 *  Notes:          Auto-generated from 'gen_io.py' (version 2.2.1 (r2014-igloo-dev4))
 *                  at Tue Mar 18 11:50:31 2014 (local time).
 *                  Do not modify.
 *
 *****************************************************************************
 */

#ifndef PSY_CONFIG
#define PSY_CONFIG

/********* Includes *********/

/* NOTE - angle brackets used for the #includes below as this file is
 *        included in eTPU code and the eTPU compiler needs angle 
 *        brackets or else it ignores specified include paths!
 */

#if defined(CFG_M220)
#if defined(CFG_SUB_000)
#include <psy_config_m220_000.h>
#else
#error "psy_config: unrecognised configuration for target subtype (ensure macro CFG_SUB_[TARGET-SUBTYPE] is defined)."
#endif

#else
#error "psy_config: unrecognised configuration for target type (ensure macro CFG_[TARGET-TYPE] is defined)."
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

#endif /* PSY_CONFIG */

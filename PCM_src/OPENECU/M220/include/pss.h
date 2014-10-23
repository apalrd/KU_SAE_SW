/*****************************************************************************/
/**
 *  \file    pss.h
 *  \brief   Public interface to the output driver switch feature.
 *
 *  Version: $Id: pss.h 34565 2013-07-23 19:33:45Z sborders $
 *  File:    $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/pss/pss.h $
 */

/*  Copyright (C) 2012 Pi Innovo
 *  This document (program) contains proprietary information
 *  which is the property of Pi Innovo
 *  The contents of this document (program) must not be copied
 *  or disclosed to a third party without the prior agreement
 *  of an authorised officer of Pi Innovo
 */

#ifndef PSS_H
#define PSS_H

/********* Includes *********/

#include "psy.h"

/********* These macros can be changed *********/

/* None */

/********* These macros must not be changed *********/

/* None */

/********* Global Structure Definitions *********/

/* None */

/********* Global Prototypes *********/

/* M250 and U82 APIs never offered this form of the function name
 * so explicitly excluded here.
 */
#if defined(CFG_FEAT_HIGH_SIDE_SWITCH) && !defined(CFG_M250) && !defined(CFG_U82)
#if !defined(CFG_DONT_USE_DEPRECATED)
/* Deprecated, see pss_set_safety_switch(). */
extern void pss_set_switch
(
    BOOL pssf_enable
);
#else
#define pss_set_switch(pssf_enable) pss_set_switch_is_deprecated_see_user_guide()
#endif
#endif

#if defined(CFG_FEAT_HIGH_SIDE_SWITCH)
extern void pss_set_safety_switch
(
    BOOL pssf_enable
);
#endif

#if defined(CFG_FEAT_OVER_CURRENT_TRIP_RESET)
#if !defined(CFG_M460)
extern void pss_overcur_trip_reset
(
    BOOL pssf_request_trip_reset
);
#else
extern void pss_overcur_trip_reset_and_diagn_enable_state
(
    BOOL pssf_enable_diagn,
    BOOL pssf_request_trip_reset
);
#endif
#endif

#if defined(CFG_FEAT_HIGH_SIDE_PROTECTION) || defined(CFG_FEAT_OVER_CURRENT_TRIP_RESET)
extern void pss_task
(
    void
);
#endif

/********* Global Variables *********/

/* None */

#endif /* PSS_H */

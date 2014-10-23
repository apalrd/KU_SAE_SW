/*****************************************************************************/
/**
 *  \file    ptm.h
 *  \brief   Public interface to the system timing feature.
 *
 *  Version: $Id: ptm.h 28958 2012-05-05 16:38:33Z jtough $
 *  File:    $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/ptm/ptm.h $
 */

/*  Copyright (C) 2012 Pi Innovo
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

#ifndef PTM_H
#define PTM_H

/********* Includes *********/

#include "psy_config.h"
#include "pio.h"

/********* These macros can be changed *********/

/* This is the private division factor to convert from system time (returned
 * by calling ptm_get_sys_time()) into microseconds. The code is split like this
 * to allow remove a warning when building documentation.
 */
#if defined(CFG_FEAT_UC_FAMILY_MPC5XX)
#define PTM_INT_SYS_TIME_TO_US   1
#elif defined(CFG_FEAT_UC_FAMILY_MPC55XX)
#define PTM_INT_SYS_TIME_TO_US   (PIO_RATE_SYS_CLK_MHZ)
#else
#error "ptm.h: was compiled for no specific target (macro CFG_<target> not defined)."
#endif

/** This is the division factor to convert from system time (returned
 * by calling ptm_get_sys_time()) into microseconds.
 *
 * \ingroup c_interface
 */
#define PTM_SYS_TIME_TO_US       (PTM_INT_SYS_TIME_TO_US)

/********* These macros must not be changed *********/

/* None */

/********* Global Structure Definitions *********/

/* None */

/********* Global Prototypes *********/

extern U32 ptm_get_sys_time
(
    void
);

extern U32 ptm_sys_time_diff
(
    U32 ptmf_time
);

extern U32 ptm_sys_time_diff_update
(
    U32 *ptmf_time
);

extern U32 ptm_get_s_time
(
    void
);

extern U32 ptm_s_time_diff
(
    U32 ptmf_time
);

extern U32 ptm_s_time_diff_update
(
    U32 *ptmf_time
);

extern U32 ptm_get_ms_time
(
    void
);

extern U32 ptm_ms_time_diff
(
    U32 ptmf_time
);

extern U32 ptm_ms_time_diff_update
(
    U32 *ptmf_time
);

extern U32 ptm_get_us_time
(
    void
);

extern U32 ptm_us_time_diff
(
    U32 ptmf_time
);

extern U32 ptm_us_time_diff_update
(
    U32 *ptmf_time
);

/********* Global Variables *********/

/* None */

#endif /* PTM_H */


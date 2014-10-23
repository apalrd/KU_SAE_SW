/*****************************************************************************/
/**
 *  \file    psy.h
 *  \brief   Public interface to the system feature.
 *
 *  Version: $Id: psy.h 33447 2013-04-30 07:21:01Z cwartnaby $
 *  File:    $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/psy/psy.h $
 */

/*  Copyright (C) 2012 Pi Innovo
 *  This document (program) contains proprietary information
 *  which is the property of Pi Innovo
 *  The contents of this document (program) must not be copied
 *  or disclosed to a third party without the prior agreement
 *  of an authorised officer of Pi Innovo
 */

#ifndef PSY_H
#define PSY_H

/********* Includes *********/

#include "psy_types.h"
#if !defined(MATLAB_MEX_FILE) && !defined(CFG_NO_TARGET)
#include "psy_config.h"
#endif

/********* These macros can be changed *********/

/* 
 * To indicate in SPRG7 that no error log is stored,
 * featureid is set to PSY_NONE
 */
#define PSY_NONE                        (U8)0

/** This is the error log identifier for the PBT (boot) feature.
 *
 * \ingroup c_interface
 */
#define PSY_PBT                         (U8)1

/** This is the error log identifier for the PSY (system) feature.
 *
 * \ingroup c_interface
 */
#define PSY_PSY                         (U8)2

/** This is the error log identifier for the PTPU (TPU or eTPU) feature.
 *
 * \ingroup c_interface
 */
#define PSY_PTPU                        (U8)3

/** This is the error log identifier for the PSC (startup and idle) feature.
 *
 * \ingroup c_interface
 */
#define PSY_PSC                         (U8)4

/** This is the error log identifier for the PAX (analogue I/O) feature.
 *
 * \ingroup c_interface
 */
#define PSY_PAX                         (U8)5

/** This is the error log identifier for the PCX (CAN messaging) feature.
 *
 * \ingroup c_interface
 */
#define PSY_PCX                         (U8)6

/** This is the error log identifier for the PDX (digital I/O) feature.
 *
 * \ingroup c_interface
 */
#define PSY_PDX                         (U8)8

/** This is the error log identifier for the PUT (general utility) feature.
 *
 * \ingroup c_interface
 */
#define PSY_PUT                         (U8)9

/** This is the error log identifier for the PSP (SPI messaging) feature.
 *
 * \ingroup c_interface
 */
#define PSY_PSP                         (U8)10

/** This is the error log identifier for the PNV (adaptive non-volatile) feature.
 *
 * \ingroup c_interface
 */
#define PSY_PNV                         (U8)11

/** This is the error log identifier for the PRS (RS232) feature.
 *
 * \ingroup c_interface
 */
#define PSY_PRS                         (U8)12

/** This is the error log identifier for the PCP (CCP scheduling) feature.
 *
 * \ingroup c_interface
 */
#define PSY_PCP                         (U8)13

/** This is the error log identifier for the PKN (scheduler) feature.
 *
 * \ingroup c_interface
 */
#define PSY_PKN                         (U8)14

/** This is the error log identifier for the PMIOS (MIOS or eMIOS) feature.
 *
 * \ingroup c_interface
 */
#define PSY_PMIOS                       (U8)15

/** This is the error log identifier for the PFL (Flash memory) feature.
 *
 * \ingroup c_interface
 */
#define PSY_PFL                         (U8)16

/** This is the error log identifier for the PCCP (CCP messaging) feature.
 *
 * \ingroup c_interface
 */
#define PSY_PCCP                        (U8)17

/** This is the error log identifier for the PQADC (QADC or eQADC) feature.
 *
 * \ingroup c_interface
 */
#define PSY_PQADC                       (U8)18

/** This is the error log identifier for the PDTC (diagnostic trouble code)
 * feature.
 *
 * \ingroup c_interface
 */
#define PSY_PDTC                        (U8)19

/** This is the error log identifier for the PJ1939 (SAE J1939 messaging)
 * feature.
 *
 * \ingroup c_interface
 */
#define PSY_PJ1939                      (U8)20

/** This is the error log identifier for the PSPI (SPI messaging)
 * feature.
 *
 * \ingroup c_interface
 */
#define PSY_PSPI                        (U8)21

/** This is the error log identifier for the PDG (ISO diagnostics)
 * feature.
 *
 * \ingroup c_interface
 */
#define PSY_PDG                         (U8)22

/** This is the error log identifier for the PFF (freeze frame)
 * feature.
 *
 * \ingroup c_interface
 */
#define PSY_PFF                         (U8)23

/** This is the error log identifier for the PEM (emulutor and memory)
 * feature.
 *
 * \ingroup c_interface
 */
#define PSY_PEM                         (U8)24

/** This is the error log identifier for the PFS (filesystem)
 * feature.
 *
 * \ingroup c_interface
 */
#define PSY_PFS                         (U8)25

/********* These macros must not be changed *********/

/* None */

/********* Global Structure Definitions *********/

/** The type for an error log.
 *
 * This type declares a structure containing information relating to a system error
 * (detected by the platform software).
 *
 * \ingroup  c_interface
 */
typedef struct
{
    /** This is the feature identifier for the declared error
     * (e.g., \p #PSY_PFL). \n
     * Range: [0, 255] unitless
     *
     * \ingroup c_interface
     */
    U8  feature_id;

    /** This is the identifier for the declared error. \n
     * Range: [0, 65535]
     *
     * \ingroup c_interface
     */
    U16 error_id;
}
PSY_ERROR_LOG_T;

/********* Global Prototypes *********/

extern U8 psy_get_num_errors
(
    void
);

extern BOOL psy_get_error
(
    U8                      psyf_error_index,
    PSY_ERROR_LOG_T        *psyf_log
);

/**** Global Variables ****/

/* None */

#endif /* PSY_H */

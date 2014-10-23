/*****************************************************************************/
/**
 *  \file    pj1939.h
 *  \brief   Public interface to the J1939 messaging feature.
 *
 *  Version: $Id: pj1939.h 34585 2013-07-24 14:05:51Z cwartnaby $
 *  File:    $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/pj1939/pj1939.h $
 */

/*  Copyright (C) 2012 Pi Innovo
 *  This document (program) contains proprietary information
 *  which is the property of Pi Innovo
 *  The contents of this document (program) must not be copied
 *  or disclosed to a third party without the prior agreement
 *  of an authorised officer of Pi Innovo
 */

#ifndef PJ1939_H
#define PJ1939_H

/********* Includes *********/

#include "psy.h"
#include "pcx.h"
#include "pdtc.h"
#include "pio.h"

/********* These macros can be changed *********/

/* This is the maximum number of data bytes in a CAN message.
 */
#define CAN_MAX_BYTE_COUNT (8)

/********* These macros must not be changed *********/

/** This is the PGN for a DM1 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM1  ((PGN_T)65226)

/** This is the PGN for a DM2 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM2  ((PGN_T)65227)

/** This is the PGN for a DM3 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM3  ((PGN_T)65228)

/** This is the PGN for a DM3 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM4  ((PGN_T)65229)

/** This is the PGN for a DM5 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM5  ((PGN_T)65230)

/** This is the PGN for a DM6 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM6  ((PGN_T)65231)

/** This is the PGN for a DM7 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM7  ((PGN_T)58112)

/** This is the PGN for a DM8 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM8  ((PGN_T)65232)

/** This is the PGN for a DM10 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM10 ((PGN_T)65234)

/** This is the PGN for a DM11 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM11 ((PGN_T)65235)

/** This is the PGN for a DM12 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM12 ((PGN_T)65236)

/** This is the PGN for a DM14 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM14 ((PGN_T)55552)

/** This is the PGN for a DM15 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM15 ((PGN_T)55296)

/** This is the PGN for a DM16 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM16 ((PGN_T)55040)

/** This is the PGN for a DM20 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM20 ((PGN_T)49664)

/** This is the PGN for a DM20 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM21 ((PGN_T)49408)

/** This is the PGN for a DM23 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM23 ((PGN_T)64949)

/** This is the PGN for a DM24 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM24 ((PGN_T)64950)

/** This is the PGN for a DM25 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM25 ((PGN_T)64951)

/** This is the PGN for a DM26 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM26 ((PGN_T)64952)

/** This is the PGN for a DM27 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM27 ((PGN_T)64898)

/** This is the PGN for a DM28 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM28 ((PGN_T)64896)

/** This is the PGN for a DM29 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM29 ((PGN_T)40448)

/** This is the PGN for a DM30 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM30 ((PGN_T)41984)

/** This is the PGN for a DM31 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM31 ((PGN_T)41728)

/** This is the PGN for a DM32 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM32 ((PGN_T)41472)

/** This is the PGN for a DM33 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM33 ((PGN_T)41216)

/** This is the PGN for a DM34 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM34 ((PGN_T)40960)

/** This is the PGN for a DM35 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM35 ((PGN_T)40704)

/** This is the PGN for a DM36 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM36 ((PGN_T)64868)

/** This is the PGN for a DM37 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM37 ((PGN_T)64867)

/** This is the PGN for a DM38 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM38 ((PGN_T)64866)

/** This is the PGN for a DM39 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM39 ((PGN_T)64865)

/** This is the PGN for a DM40 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM40 ((PGN_T)64864)

/** This is the PGN for a DM41 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM41 ((PGN_T)64863)

/** This is the PGN for a DM42 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM42 ((PGN_T)64862)

/** This is the PGN for a DM43 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM43 ((PGN_T)64861)

/** This is the PGN for a DM44 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM44 ((PGN_T)64860)

/** This is the PGN for a DM45 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM45 ((PGN_T)64859)

/** This is the PGN for a DM46 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM46 ((PGN_T)64858)

/** This is the PGN for a DM47 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM47 ((PGN_T)64857)

/** This is the PGN for a DM48 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM48 ((PGN_T)64856)

/** This is the PGN for a DM49 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM49 ((PGN_T)64855)

/** This is the PGN for a DM50 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM50 ((PGN_T)64854)

/** This is the PGN for a DM51 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM51 ((PGN_T)64853)

/** This is the PGN for a DM52 diagnostic message (from J1939-73).
 */
#define PJ1939_PGN_DM52 ((PGN_T)64852)

/** SAE reserved.
 * This is one of the definitions for OBD compliance values as
 * given in the J1939-73 description for DM5 byte 3.
 *
 * \ingroup c_extdiag_interface
 */
#define PJ1939_SAE_RESERVED_1   ((U8)0)

/** OBD II (CARB).
 * This is one of the definitions for OBD compliance values as
 * given in the J1939-73 description for DM5 byte 3.
 *
 * \ingroup c_extdiag_interface
 */
#define PJ1939_OBD_II           ((U8)1)

/** OBD (Federal, EPA).
 * This is one of the definitions for OBD compliance values as
 * given in the J1939-73 description for DM5 byte 3.
 *
 * \ingroup c_extdiag_interface
 */
#define PJ1939_OBD              ((U8)2)

/** OBD and OBD II.
 * This is one of the definitions for OBD compliance values as
 * given in the J1939-73 description for DM5 byte 3.
 *
 * \ingroup c_extdiag_interface
 */
#define PJ1939_OBD_OBD_II       ((U8)3)

/** OBD I.
 * This is one of the definitions for OBD compliance values as
 * given in the J1939-73 description for DM5 byte 3.
 *
 * \ingroup c_extdiag_interface
 */
#define PJ1939_OBD_I            ((U8)4)

/** Not intended to meet OBD II requirements.
 * This is one of the definitions for OBD compliance values as
 * given in the J1939-73 description for DM5 byte 3.
 *
 * \ingroup c_extdiag_interface
 */
#define PJ1939_NO_OBD_II        ((U8)5)

/** EOBD.
 * This is one of the definitions for OBD compliance values as
 * given in the J1939-73 description for DM5 byte 3.
 *
 * \ingroup c_extdiag_interface
 */
#define PJ1939_EOBD             ((U8)6)

/** EOBD and OBD II.
 * This is one of the definitions for OBD compliance values as
 * given in the J1939-73 description for DM5 byte 3.
 *
 * \ingroup c_extdiag_interface
 */
#define PJ1939_EOBD_OBD_II      ((U8)7)

/** EOBD and OBD.
 * This is one of the definitions for OBD compliance values as
 * given in the J1939-73 description for DM5 byte 3.
 *
 * \ingroup c_extdiag_interface
 */
#define PJ1939_EOBD_OBD         ((U8)8)

/** EOBD, OBD and OBD II.
 * This is one of the definitions for OBD compliance values as
 * given in the J1939-73 description for DM5 byte 3.
 */
#define PJ1939_EOBD_OBD_OBD_II  ((U8)9)

/** JOBD.
 * This is one of the definitions for OBD compliance values as
 * given in the J1939-73 description for DM5 byte 3.
 *
 * \ingroup c_extdiag_interface
 */
#define PJ1939_JOBD             ((U8)10)

/** JOBD and OBD II.
 * This is one of the definitions for OBD compliance values as
 * given in the J1939-73 description for DM5 byte 3.
 *
 * \ingroup c_extdiag_interface
 */
#define PJ1939_JOBD_OBD_II      ((U8)11)

/** JOBD and EOBD.
 * This is one of the definitions for OBD compliance values as
 * given in the J1939-73 description for DM5 byte 3.
 */
#define PJ1939_JOBD_EOBD        ((U8)12)

/** JOBD, EOBD and OBD II.
 * This is one of the definitions for OBD compliance values as
 * given in the J1939-73 description for DM5 byte 3.
 *
 * \ingroup c_extdiag_interface
 */
#define PJ1939_JOBD_EOBD_OBD_II ((U8)13)

/** Heavy Duty Vehicles (EURO 1V) B1.
 * This is one of the definitions for OBD compliance values as
 * given in the J1939-73 description for DM5 byte 3.
 *
 * \ingroup c_extdiag_interface
 */
#define PJ1939_HDV_B1           ((U8)14)

/** Heavy Duty Vehicles (EURO V) B2.
 * This is one of the definitions for OBD compliance values as
 * given in the J1939-73 description for DM5 byte 3.
 *
 * \ingroup c_extdiag_interface
 */
#define PJ1939_HDV_B2           ((U8)15)

/** Heavy Duty Vehicles (EURO EEC) C (gas engines).
 * This is one of the definitions for OBD compliance values as
 * given in the J1939-73 description for DM5 byte 3.
 *
 * \ingroup c_extdiag_interface
 */
#define PJ1939_HDV_C            ((U8)16)

/** Engine Manufacturer Diagnostics.
 * This is one of the definitions for OBD compliance values as
 * given in the J1939-73 description for DM5 byte 3.
 *
 * \ingroup c_extdiag_interface
 */
#define PJ1939_EMD              ((U8)17)

/** Engine Manufacturer Diagnostics Enhanced (EMD+).
 * This is one of the definitions for OBD compliance values as
 * given in the J1939-73 description for DM5 byte 3.
 *
 * \ingroup c_extdiag_interface
 */
#define PJ1939_EMD_PLUS         ((U8)18)

/** Heavy Duty/OBD Partial.
 * This is one of the definitions for OBD compliance values as
 * given in the J1939-73 description for DM5 byte 3.
 */
#define PJ1939_HDV_OBD_P        ((U8)19)

/** Heavy Duty/OBD.
 * This is one of the definitions for OBD compliance values as
 * given in the J1939-73 description for DM5 byte 3.
 *
 * \ingroup c_extdiag_interface
 */
#define PJ1939_HDV_OBD          ((U8)20)

/** World Wide Harmonized OBD.
 * This is one of the definitions for OBD compliance values as
 * given in the J1939-73 description for DM5 byte 3.
 *
 * \ingroup c_extdiag_interface
 */
#define PJ1939_WWH_OBD          ((U8)21)

/** OBD II (CARB) Revised.
 * This is one of the definitions for OBD compliance values as
 * given in the J1939-73 description for DM5 byte 3.
 *
 * \ingroup c_extdiag_interface
 */
#define PJ1939_OBD_II_REV       ((U8)22)

/** Heavy Duty Vehicles (EURO IV and V) Revised.
 * This is one of the definitions for OBD compliance values as
 * given in the J1939-73 description for DM5 byte 3.
 *
 * \ingroup c_extdiag_interface
 */
#define PJ1939_HD_EOBD_REV      ((U8)23)

/** SAE reserved.
 * This is one of the definitions for OBD compliance values as
 * given in the J1939-73 description for DM5 byte 3.
 *
 * \ingroup c_extdiag_interface
 */
#define PJ1939_SAE_RESERVED_2   ((U8)24)

/** OBD-M Compliance for Spark_Ignition Sterndrive and
 * Inboard Engines.
 * This is one of the definitions for OBD compliance values as
 * given in the J1939-73 description for DM5 byte 3.
 *
 * \ingroup c_extdiag_interface
 */
#define PJ1939_OBD_M_SI_SD_I    ((U8)25)

/********* Global Structure Definitions *********/

/** Error values for debugging -- when an error is found in a call to the PCX
 * API, the feature calls a function with an enumeration from this type.
 *
 * \ingroup  c_interface
 */
typedef enum
{
    /** Error raised if the PGN requested function finds an invalid function
     * argument.
     */
    PJ1939_WAS_REQ_PGN_INVALID_ARG        = 1,

    /** Error raised if the PG receive function finds an invalid function
     * argument.
     */
    PJ1939_PG_RECEIVE_INVALID_ARG         = 2,

    /** Error raised if the PG transmit function finds an invalid function
     * argument.
     */
    PJ1939_PG_TRANSMIT_INVALID_ARG        = 3,

    /** Error raised if the DM1 decode function finds an invalid function
     * argument.
     */
    PJ1939_DM1_DECODE_INVALID_ARG         = 4,

    /** Error raised if the DM2 decode function finds an invalid function
     * argument.
     */
    PJ1939_DM2_DECODE_INVALID_ARG         = 5,

    /** Error raised if the DM1 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM1_TRANSMIT_INVALID_ARG       = 6,

    /** Error raised if the DM2 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM2_TRANSMIT_INVALID_ARG       = 7,

    /** Error raised if the DM4 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM4_TRANSMIT_INVALID_ARG       = 8,

    /** Error raised if the DM5 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM5_TRANSMIT_INVALID_ARG       = 9,

    /** Error raised if the DM6 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM6_TRANSMIT_INVALID_ARG       = 10,

     /** Error raised if the DM7 commanded test function finds an invalid function
     * argument.
     */
    PJ1939_DM7_COMMANDED_TEST_INVALID_ARG = 11,

    /** Error raised if the DM8 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM8_TRANSMIT_INVALID_ARG       = 12,

    /** Error raised if the DM10 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM10_TRANSMIT_INVALID_ARG      = 13,

    /** Error raised if the DM12 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM12_TRANSMIT_INVALID_ARG      = 14,

    /** Error raised if the DM14 decode function finds an invalid function
     * argument.
     */
    PJ1939_DM14_DECODE_INVALID_ARG        = 15,

    /** Error raised if the DM15 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM15_TRANSMIT_INVALID_ARG      = 16,

    /** Error raised if the DM16 decode function finds an invalid function
     * argument.
     */
    PJ1939_DM16_DECODE_INVALID_ARG        = 17,

    /** Error raised if the DM16 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM16_TRANSMIT_INVALID_ARG      = 18,

    /** Error raised if the DM20 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM20_TRANSMIT_INVALID_ARG      = 19,

    /** Error raised if the DM21 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM21_TRANSMIT_INVALID_ARG      = 20,

    /** Error raised if the DM23 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM23_TRANSMIT_INVALID_ARG      = 21,

    /** Error raised if the DM24 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM24_TRANSMIT_INVALID_ARG      = 22,

    /** Error raised if the DM25 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM25_TRANSMIT_INVALID_ARG      = 23,

    /** Error raised if the DM26 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM26_TRANSMIT_INVALID_ARG      = 24,

    /** Error raised if the DM27 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM27_TRANSMIT_INVALID_ARG      = 25,

    /** Error raised if the DM28 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM28_TRANSMIT_INVALID_ARG      = 26,

    /** Error raised if the DM29 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM29_TRANSMIT_INVALID_ARG      = 27,

    /** Error raised if the DM30 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM30_TRANSMIT_INVALID_ARG      = 28,

    /** Error raised if the DM31 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM31_TRANSMIT_INVALID_ARG      = 29,

    /** Error raised if the DM32 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM32_TRANSMIT_INVALID_ARG      = 30,

    /** Error raised if the DM33 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM33_TRANSMIT_INVALID_ARG      = 31,

    /** Error raised if the DM34 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM34_TRANSMIT_INVALID_ARG      = 32,

     /** Error raised if the DM35 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM35_TRANSMIT_INVALID_ARG      = 33,

     /** Error raised if the DM36 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM36_TRANSMIT_INVALID_ARG      = 34,

     /** Error raised if the DM37 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM37_TRANSMIT_INVALID_ARG      = 35,

     /** Error raised if the DM38 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM38_TRANSMIT_INVALID_ARG      = 36,

    /** Error raised if the DM39 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM39_TRANSMIT_INVALID_ARG      = 37,

    /** Error raised if the DM40 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM40_TRANSMIT_INVALID_ARG      = 38,

    /** Error raised if the DM41 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM41_TRANSMIT_INVALID_ARG      = 39,

    /** Error raised if the DM42 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM42_TRANSMIT_INVALID_ARG      = 40,

    /** Error raised if the DM43 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM43_TRANSMIT_INVALID_ARG      = 41,

    /** Error raised if the DM44 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM44_TRANSMIT_INVALID_ARG      = 42,

    /** Error raised if the DM45 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM45_TRANSMIT_INVALID_ARG      = 43,

    /** Error raised if the DM46 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM46_TRANSMIT_INVALID_ARG      = 44,

    /** Error raised if the DM47 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM47_TRANSMIT_INVALID_ARG      = 45,

    /** Error raised if the DM48 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM48_TRANSMIT_INVALID_ARG      = 46,

    /** Error raised if the DM49 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM49_TRANSMIT_INVALID_ARG      = 47,

    /** Error raised if the DM50 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM50_TRANSMIT_INVALID_ARG      = 48,

    /** Error raised if the DM51 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM51_TRANSMIT_INVALID_ARG      = 49,

    /** Error raised if the DM52 transmit function finds an invalid function
     * argument.
     */
    PJ1939_DM52_TRANSMIT_INVALID_ARG      = 50,

    /** Error raised if the PGN transmit function finds an invalid function
     * argument.
     */
    PJ1939_PGN_TRANSMIT_INVALID_ARG       = 51
}
PJ1939_ERROR_T;

/** The type of PGN response required -- A J1939 acknowledgement message can
 * be of type Positive Acknowledgedment(ACK), Negative Acknowledgement(NACK),
 * Access Denied(ACCESS_DENIED) or Cannot Respond(BUSY).
 *
 * \ingroup  c_extdiag_interface
 */
typedef enum
{
    ACK           = 0,
    NACK          = 1,
    ACCESS_DENIED = 2,
    BUSY          = 3
}
PJ1939_ACK_AND_CONTROL_BYTE_T;

/** The type of inhibit reason for the J1939 memory access reprogramming-inhibit function
 *  If the application inhibits ECU reprogramming (a jump to the Bootloader), it must
 *  supply a reason defined by this type.
 *
 * \ingroup  c_extdiag_interface
 */
typedef enum
{
    /* Access denied due to a general error or condition. This can be used if reprogramming is disinhibited */
    PJ1939_REPR_GENERAL_ERROR = 0,
    /* Access denied due to the application not being in 'Diagnostic Mode' per J1939-73 specifications */
    PJ1939_REPR_NOT_IN_DIAG_MODE = 1,
    /* Access denied due to the application not being in 'Engineering Mode' per J1939-73 specifications */
    PJ1939_REPR_NOT_IN_ENG_MODE = 2,
    /* Access denied due to the application not being in 'Development Mode' per J1939-73 specifications */
    PJ1939_REPR_NOT_IN_DEV_MODE = 3,
    /* Access denied because the engine is running */
    PJ1939_REPR_ENGINE_RUNNING = 4,
    /* Access denied because transmission is not in 'Park' position */
    PJ1939_REPR_VEH_NOT_IN_PARK = 5,
    /* Access denied because the vehicle is moving */
    PJ1939_REPR_VEH_NOT_STATIONARY = 6
}
PJ1939_INHIBIT_REPR_REASONS_T;

/** This is a typedef for the PGN (parameter group number).
 *
 * Present in the C-API description only for build time size requirements.
 * The typedef is not to be used by application code.
 *
 * \ingroup c_interface
 */
typedef U32 PGN_T;

/** This is the definition of a J1939 transmit message.
 *
 * Present in the C-API description only for build time size requirements.
 * The typedef is not to be used by application code.
 */
typedef struct
{
    /** This is the message Parameter Group Number.
     *
     * \ingroup c_interface
     */
    PGN_T  PGN;

    /** This is a pointer to the data bytes contained in the J1939 message. If
     * the data pointer is NULL, the message should be considered invalid.
     *
     * \ingroup c_interface
     */
    U8    *data_ptr;

    /** This is the number of data bytes in the J1939 message.
     *
     * Range: [0, 1785] bytes
     *
     * \ingroup c_interface
     */
    U16    byte_count;

    /** This is the J1939 message priority (0 is the highest priority, 7 the
     * lowest).  Priorities requested outside this range will be clipped to 7.
     *
     * Range: [0, 7]
     *
     * \ingroup c_interface
     */
    U8     priority;

    /** This is the network address of the intended destination node. This field
     * is ignored for PDU2 format messages with eight or fewer data bytes since
     * they are always broadcast globally. PDU2 format messages with more than
     * eight bytes of data can be broadcast globally or sent to a specific
     * destination. A destination address (global or specific) is required for
     * all PDU1 formats.
     *
     * \ingroup c_interface
     */
    U8     dest_addr;

    /** This is used to define transport layer error and acknowledgment.
     *
     * \ingroup c_interface
     */
    S8     status;
}
J1939_TX_MESSAGE_T;

/** This is the definition of a J1939 receive message.
 *
 * Present in the C-API description only for build time size requirements.
 * The typedef is not to be used by application code.
 */
typedef struct
{
    /** This is the message Parameter Group Number.
     *
     * \ingroup c_interface
     */
    PGN_T  PGN;

    /** This is a pointer to the data bytes contained in the J1939 message. If
     * the data pointer is NULL, the message should be considered invalid.
     *
     * \ingroup c_interface
     */
    U8    *data_ptr;

    /** This is the number of data bytes in the J1939 message.
     *
     * Range: [0, 1785] bytes
     *
     * \ingroup c_interface
     */
    U16    byte_count;

    /** This is the network address of the node that transmitted the message.
     *
     * \ingroup c_interface
     */
    U8     source_addr;

    /** This is the network address of the node to which the message was
     * sent. Always set to the global address (255) for PDU2 format messages.
     *
     * \ingroup c_interface
     */
    U8     dest_addr;
}
J1939_RX_MESSAGE_T;

/** This is the J1939 protocol message structure; used to disassemble messages.
 *
 * Present in the C-API description only for build time size requirements.
 * The typedef is not to be used by application code.
 */
typedef struct
{
    J1939_TX_MESSAGE_T *tx_msg_ptr;
    S32                 time;
    S8                  retry;
    U8                  packet_index;
    U8                  total_packets;
    U8                  state;
    U8                  packets_ok_to_send;
}
J1939_TRANSPORT_TX_INFO;

/** This is the J1939 protocol message structure; used to assemble messages.
 *
 * Present in the C-API description only for build time size requirements.
 * The typedef is not to be used by application code.
 */
typedef struct
{
    S32                 message_index;
    S32                 rx_timer;
    S8                  retry;
    U8                  packet_index;
    U8                  total_packets;
    U8                  flag;
    J1939_RX_MESSAGE_T  rx_msg;
    U8                 *msg_buffer;
}
J1939_MESSAGE;

/** This is the structure of a single CAN packet.
 *
 * Present in the C-API description only for build time size requirements.
 * The typedef is not to be used by application code.
 */
typedef struct
{
    /** This is the 29-bit CAN identifier contained in an extended format
     * packet. The identifier is right justified within the 32-bit field so that
     * the upper three bits are always zero.
     *
     * \ingroup c_interface
     */
    U32 identifier;

    /** This is the data bytes contained in the CAN packet. The value of unused
     * data bytes is undefined.
     *
     * \ingroup c_interface
     */
    U8  data[CAN_MAX_BYTE_COUNT];

    /** This is the number of valid data bytes in the CAN packet.
     *
     * Range: [0, 8] bytes
     *
     * \ingroup c_interface
     */
    U8  byte_count;
}
CAN_PACKET_T;

/** This is the structure for buffering received J1939 messages.
 *
 * Present in the C-API description only for build time size requirements.
 * The typedef is not to be used by application code.
 */
typedef struct
{
    /** This timestamp records when the J1939 message was received.
     *
     * Range: [0, 4294967295] microseconds
     *
     * \ingroup c_interface
     */
    U32 timestamp;

    /** This is the source address of a received J1939 message.
     *
     * Range: [0, 255]
     *
     * \ingroup c_interface
     */
    U8  source_addr;

    /** This is the destination address of the received J1939 message.
     *
     * Range: [0, 255]
     *
     * \ingroup c_interface
     */
    U8  dest_addr;

    /** This is the number of data bytes in the received J1939 message.
     *
     * Range: [0, 1785] bytes
     *
     * \ingroup c_interface
     */
    U16 byte_count;     /* number of data bytes in received message */

    /** This is a bitfield of status information. If bit 0 is set, the message
     * has been received at least once since the bit was last cleared. If bit 1
     * is set, the message has been received more than once since the bit was
     * last cleared. If bit 2 is set, an error was trapped on the last
     * receive.
     *
     * \ingroup c_interface
     */
    U8  flags;          /* flags: error on receive, overrun on receive, etc. */
}
PJ1939_RX_BUF_T;

/** This is a structure to store details of requested tests received in DM7 message.
 * Note that source and destination address must be stored because DM30 requires a
 * destination address; and the application may also want to permit/refuse requests
 * from specific sources.
 *
 * Present in the C-API description only for build time size requirements.
 * The typedef is not to be used by application code.
 */
typedef struct
{
    /* Ordered structure with U32 at the start and U8s following to ensure that we
     * do not waste space on word alignment
     */

    /** This is the suspect parameter number (SPN) of the received J1939 DM7 message.
     *
     * Range: [0, 524287]
     *
     * \ingroup c_extdiag_interface
     */
    U32 spn;

    /** This is the test identifier (TID) of the received J1939 DM7 message.
     *
     * Range: [0, 255]
     *
     * \ingroup c_extdiag_interface
     */
    U8  tid;

    /** This is the failure mode indicator (FMI) of the received J1939 DM7 message.
     *
     * Range: [0, 31]
     *
     * \ingroup c_extdiag_interface
     */
    U8  fmi;

    /** This is the source address of the received J1939 DM7 message.
     *
     * Range: [0, 255]
     *
     * \ingroup c_extdiag_interface
     */
    U8  source_addr;

    /** This is the destination address of the received J1939 DM7 message.
     *
     * Range: [0, 255]
     *
     * \ingroup c_extdiag_interface
     */
    U8  dest_addr;
}
PJ1939_DM7_BUFFER_T;

/** This is the structure for the Emission Increasing Auxiliary Emission Conrol Device (EI-AECD)
 *  Active time data.
 *
 * Present in the C-API description only for build time size requirements.
 * The typedef is not to be used by application code.
 */
typedef struct
{
    /** This is the EI-AECD number.
     *
     * \ingroup c_extdiag_interface
     */
    U8  aecd_number;

    /** This is the EI-AECD Engine Hours Timer 1.
     *  Will indicate total active time when commanding up to, but not including,
     *  75% reduction of the maximum emissions control effectiveness.
     *
     * \ingroup c_extdiag_interface
     */
    U32 engine_hours_timer1;

    /** This is the (optional) EI-AECD Engine Hours Timer 2.
     *  Will indicate total active time when 75% or more reduction of the maximum
     *  emissions control effectiveness.
     *
     * \ingroup c_extdiag_interface
     */
    U32 engine_hours_timer2;
}
PJ1939_AECD_T;

/** The NTE control area status.
 *
 * \ingroup  c_extdiag_interface
 */
typedef enum
{
    PJ1939_NTE_OUTSIDE_CNTRL_AREA = 0,
    PJ1939_NTE_INSIDE_CNTRL_AREA  = 1,
    PJ1939_NTE_RESERVED           = 2,
    PJ1939_NTE_AREA_NOT_AVAILABLE = 3
}
PJ1939_NTE_CNTRL_AREA_STATUS_T;

/** The NTE control areas.
 *
 * \ingroup  c_extdiag_interface
 */
typedef enum
{
    PJ1939_NOX_NTE_AREA,
    PJ1939_NOX_NTE_CARVE_OUT_AREA,
    PJ1939_NOX_NTE_DEFICIENCY_AREA,
    PJ1939_PM_NTE_AREA,
    PJ1939_PM_NTE_CARVE_OUT_AREA,
    PJ1939_PM_NTE_DEFICIENCY_AREA
}
PJ1939_NTE_CNTRL_AREA_T;

/** Typedef for the callback function used to generate a seed for a J1939 seed-key exchange.
 *
 * This function is run by a processing task which is scheduled every 5ms.  The function
 * must therefore take no more than 5ms to execute, and preferably should be significantly
 * faster.  As usual for embedded programming, excessive stack requirements and the use
 * of dynamic memory allocation should be avoided.  There is currently no requirement for
 * this function to be re-entrant.
 *
 * In future software, the callback function will be copied to NV storage
 * so that application security algorithms may also be used by the bootloader when
 * reprogramming.  In order for this to be possible, the callback function must be relocatable.
 * The function should therefore make no calls to other functions, or refer to application variables or
 * calibratables, otherwise existing callback functions may be incompatible with new releases
 * of OpenECU.  Note that direct access to registers and hardcoded memory locations is still
 * permitted.
 *
 * \return The function must return a 16-bit seed value.  Typically this will be generated through
 * a random or pseudo-random process.
 *
 * \ingroup c_extdiag_interface
 */
typedef U16 (*PJ1939_SEED_REQUEST_CALLBACK_T)
(
    void
);

/** Typedef for the callback function used to validate a key for a J1939 seed-key exchange.
 * The function must validate if the passed seed and key values match.
 *
 * This function is run by a processing task which is scheduled every 5ms.  The function
 * must therefore take no more than 5ms to execute, and preferably should be significantly
 * faster.  As usual for embedded programming, excessive stack requirements and the use
 * of dynamic memory allocation should be avoided.  There is currently no requirement for
 * this function to be re-entrant.
 *
 * In future software, the callback function will be copied to NV storage
 * so that application security algorithms may also be used by the bootloader when
 * reprogramming.  In order for this to be possible, the callback function must be relocatable.
 * The function should therefore make no calls to other functions, or refer to application variables or
 * calibratables, otherwise existing callback functions may be incompatible with new releases
 * of OpenECU.  Note that direct access to registers and hardcoded memory locations is still
 * permitted.
 *
 * \param key The key is a 16-bit value returned by the calibration tool.
 *
 * \param seed This is the 16-bit seed value.
 *
 * \return  The function must return TRUE if the key is correct, or FALSE
 * if not.
 *
 * \ingroup c_extdiag_interface
 */
typedef BOOL (*PJ1939_KEY_VALIDATION_CALLBACK_T)
(
    U16 key,
    U16 seed
);

/** Structure configuring security J1939.
 *
 * \ingroup c_extdiag_interface
 */
typedef struct
{
    /** If security_required is set FALSE, no seed-key exchange is required.
     * The callback structure elements are ignored.
     *
     * If security_required is set TRUE, the callbacks provided are used to unlock the
     * security.
     *
     * If security_required is set TRUE but either callback is NULL, it will not be
     * possible to unlock security and the calibration tool will be permanently
     * prohibited from invoking reprogramming activities.
     *
     * \ingroup c_extdiag_interface
     */
    BOOL security_required;

    /** Pointer to callback function which is called to request a seed value when the
     * calibration tool attempts to jump to bootloader.
     *
     * Set this value to NULL if security is not required.
     *
     * \ingroup c_extdiag_interface
     */
    PJ1939_SEED_REQUEST_CALLBACK_T seed_request_callback;

    /** Pointer to callback function which is called to validate a key value
     * returned by the calibration tool against a previously generated seed.
     *
     * Set this value to NULL if security is not required.
     *
     * \ingroup c_extdiag_interface
     */
    PJ1939_KEY_VALIDATION_CALLBACK_T key_validation_callback;
}
PJ1939_SEED_KEY_CONFIG_T;

/** Holds the constant data required to populate a DM24 message.
 *
 * \note The structure is private to the library and should not be used by the
 *       application. It is exposed as part of the API so that various arrays
 *       can be sized at build time to minimise the library memory footprint.
 */
typedef struct
{
    U32 spn;
    U8  supported;
}
PJ1939_DM24_CONST_DATA_T;

/********* Global Prototypes *********/

extern void pj1939_was_pgn_requested
(
    const U32                    pj1939f_pgn_idx,
    U32                         *pj1939f_timestamp,
    U8                          *pj1939f_requested,
    U8                          *pj1939f_source_addr,
    U8                          *pj1939f_dest_addr
);

extern void pj1939_pg_receive
(
    const U32                    pj1939f_pgn_idx,
    U32                         *pj1939f_timestamp,
    U8                          *pj1939f_error_flag,
    U8                          *pj1939f_rx_trig_flag,
    U8                          *pj1939f_overrun_flag,
    U8                          *pj1939f_source_addr,
    U8                          *pj1939f_dest_addr,
    const U16                    pj1939f_message_len,
    const U16                    pj1939f_num_fields,
    void *const                 *pj1939f_item_ptr,
    const U16                   *field_start_pos,
    const U8                    *field_width,
    const U8                    *field_sign,
    const U8                    *field_packing
);

#if !defined(CFG_DONT_USE_DEPRECATED)
extern void pj1939_pg_transmit
(
    const U32                    pj1939f_pgn,
    U8                           pj1939f_priority,
    U8                          *pj1939f_error_flag,
    U8                          *pj1939f_transport_error,
    const U16                    pj1939f_message_len,
    const U16                    pj1939f_num_fields,
    void *const                 *pj1939f_item_ptr,
    const U16                   *field_start_pos,
    const U8                    *field_width,
    const U8                    *field_packing
);
#else
#define pj1939_pg_transmit(a, b, c, d, e, f, g, h, i, j) pj1939_pg_transmit_is_deprecated_see_user_guide()
#endif

extern void pj1939_pdu1_transmit
(
    const U32                    pj1939f_pgn,
    const U8                     pj1939f_dest_addr,
    U8                           pj1939f_priority,
    U8                          *pj1939f_error_flag,
    U8                          *pj1939f_transport_error,
    const U16                    pj1939f_message_len,
    const U16                    pj1939f_num_fields,
    void *const                 *pj1939f_item_ptr,
    const U16                   *field_start_pos,
    const U8                    *field_width,
    const U8                    *field_packing
);

extern void pj1939_pdu2_transmit
(
    const U32                    pj1939f_pgn,
    U8                           pj1939f_priority,
    U8                          *pj1939f_error_flag,
    U8                          *pj1939f_transport_error,
    const U16                    pj1939f_message_len,
    const U16                    pj1939f_num_fields,
    void *const                 *pj1939f_item_ptr,
    const U16                   *field_start_pos,
    const U8                    *field_width,
    const U8                    *field_packing
);

extern void pj1939_dm1_decode
(
    U8                           pj1939f_dm1_idx,
    U32                          pj1939f_spn,
    U8                           pj1939f_fmi,
    U8                           pj1939f_cm,
    U8                          *pj1939f_rx_trig_flag,
    U8                          *pj1939f_active,
    U8                          *pj1939f_oc,
    U8                          *pj1939f_lamp_malfunction,
    U8                          *pj1939f_lamp_red,
    U8                          *pj1939f_lamp_amber,
    U8                          *pj1939f_lamp_protect,
    U32                         *pj1939f_timestamp
);

extern void pj1939_dm1_transmit
(
    const PDTC_TABLE_T *const    pj1939f_table,
    const U8                     pj1939f_force_transmission,
    const U8                     pj1939f_priority,
    U8                          *pj1939f_error_flag,
    U8                          *pj1939f_transport_error
);

extern void pj1939_dm2_decode
(
    U8                           pj1939f_dm2_idx,
    U32                          pj1939f_spn,
    U8                           pj1939f_fmi,
    U8                           pj1939f_cm,
    U8                          *pj1939f_rx_trig_flag,
    U8                          *pj1939f_prev_active,
    U8                          *pj1939f_oc,
    U8                          *pj1939f_lamp_malfunction,
    U8                          *pj1939f_lamp_red,
    U8                          *pj1939f_lamp_amber,
    U8                          *pj1939f_lamp_protect,
    U32                         *pj1939f_timestamp
);

extern void pj1939_dm2_transmit
(
    const PDTC_TABLE_T *const    pj1939f_table,
    const U8                     pj1939f_transmit,
    const U8                     pj1939f_priority,
    U8                          *pj1939f_error_flag,
    U8                          *pj1939f_transport_error
);

extern void pj1939_dm4_transmit
(
    const U8                   pj1939f_priority,
    U8                        *pj1939f_error_flag,
    U8                        *pj1939f_transport_error
);

extern void pj1939_dm5_transmit
(
    const PDTC_TABLE_T *const    pj1939f_table,
    const U8                     pj1939f_priority,
    U8                           pj1939f_obd_compliance,
    U8                          *pj1939f_error_flag
);

extern void pj1939_dm6_transmit
(
    const PDTC_TABLE_T *const    pj1939f_table,
    const U8                     pj1939f_transmit,
    const U8                     pj1939f_priority,
    U8                          *pj1939f_error_flag,
    U8                          *pj1939f_transport_error
);

extern BOOL pj1939_check_dm7_commanded_test
(
    U8      pj1939f_tid,
    U32     pj1939f_spn,
    U8      pj1939f_fmi,
    U8*     pj1939f_source_addr,
    U8*     pj1939f_dest_addr
);

extern BOOL pj1939_get_dm7_commanded_test
(
    PJ1939_DM7_BUFFER_T *pj1939f_test
);

extern void pj1939_dm8_transmit
(
    U8                           pj1939f_tid,
    const U8                     pj1939f_priority,
    U8                          *pj1939f_error_flag,
    U8                          *pj1939f_transport_error
);

extern void pj1939_dm10_transmit
(
    const U8                     pj1939f_priority,
    U8                          *pj1939f_error_flag
);

extern void pj1939_dm12_transmit
(
    const PDTC_TABLE_T *const  pj1939f_table,
    const U8                   pj1939f_transmit,
    const U8                   pj1939f_priority,
    U8                        *pj1939f_error_flag,
    U8                        *pj1939f_transport_error
);

extern void pj1939_dm16_transmit
(
    U8                           pj1939f_priority,
    U8                           pj1939f_dest_addr,
    U16                          pj1939f_buf_size,
    const U8                    *pj1939f_buf,
    U8                          *pj1939f_error_flag,
    U8                          *pj1939f_transport_error
);

extern void pj1939_dm20_transmit
(
    const U8                 pj1939f_priority,
    const U8                 pj1939f_dest_addr,
    U8                      *pj1939f_error_flag,
    U8                      *pj1939f_transport_error
);

extern void pj1939_dm21_transmit
(
    const U8                pj1939f_priority,
    const U8                pj1939f_dest_addr,
    U16                     pj1939f_time_while_mil_on,
    U16                     pj1939f_distance_while_mil_on,
    U16                     pj1939f_time_since_dtc_clear,
    U16                     pj1939f_distance_since_dtc_clear,
    U8                     *pj1939f_error_flag
);

extern void pj1939_dm23_transmit
(
    const PDTC_TABLE_T *const    pj1939f_table,
    const U8                     pj1939f_transmit,
    const U8                     pj1939f_priority,
    U8                          *pj1939f_error_flag,
    U8                          *pj1939f_transport_error
);

extern void pj1939_dm24_transmit
(
    const U8                   pj1939f_priority,
    U8                        *pj1939f_error_flag,
    U8                        *pj1939f_transport_error
);

extern void pj1939_dm25_transmit
(
    const U8                   pj1939f_priority,
    U8                        *pj1939f_error_flag,
    U8                        *pj1939f_transport_error
);

extern void pj1939_dm26_transmit
(
    const U8        pj1939f_priority,
    U16             pj1939_eng_time_since_ign_start,
    U8              pj1939_warmup_count_since_dtc_clear,
    U8              *pj1939f_error_flag
);

extern void pj1939_dm27_transmit
(
    const PDTC_TABLE_T *const    pj1939f_table,
    const U8                     pj1939f_transmit,
    const U8                     pj1939f_priority,
    U8                          *pj1939f_error_flag,
    U8                          *pj1939f_transport_error
);

extern void pj1939_dm28_transmit
(
    const PDTC_TABLE_T *const    pj1939f_table,
    const U8                     pj1939f_transmit,
    const U8                     pj1939f_priority,
    U8                          *pj1939f_error_flag,
    U8                          *pj1939f_transport_error
);

extern void pj1939_dm29_transmit
(
    const PDTC_TABLE_T *const  pj1939f_table,
    const U8                   pj1939f_transmit,
    const U8                   pj1939f_priority,
    const U8                   pj1939f_dest_addr,
    U8                        *pj1939f_error_flag,
    U8                        *pj1939f_transport_error
);

extern void pj1939_dm30_transmit
(
    U32         pj1939f_spn,
    const U8    pj1939f_priority,
    const U8    pj1939f_dest_addr,
    U8         *pj1939f_error_flag,
    U8         *pj1939f_transport_error
);

extern void pj1939_dm31_transmit
(
    const PDTC_TABLE_T *const  pj1939f_table,
    const U8                   pj1939f_transmit,
    const U8                   pj1939f_priority,
    const U8                   pj1939f_dest_addr,
    U8                        *pj1939f_error_flag,
    U8                        *pj1939f_transport_error
);

extern void pj1939_dm32_transmit
(
    const PDTC_TABLE_T *const   pj1939f_table,
    const U8                    pj1939f_priority,
    const U8                    pj1939f_dest_addr,
    U8                         *pj1939f_error_flag,
    U8                         *pj1939f_transport_error
);

extern void pj1939_dm33_transmit
(
    const U8                    pj1939f_priority,
    const U8                    pj1939f_dest_addr,
    U8                         *pj1939f_error_flag,
    U8                         *pj1939f_transport_error
);

extern void pj1939_dm34_transmit
(
    const U8                        pj1939f_priority,
    const U8                        pj1939f_dest_addr,
    U8                             *pj1939f_error_flag
);

extern void pj1939_dm35_transmit
(
    const PDTC_TABLE_T *const  pj1939f_table,
    const U8                   pj1939f_force_transmission,
    const U8                   pj1939f_priority,
    const U8                   pj1939f_dest_addr,
    U8                        *pj1939f_error_flag,
    U8                        *pj1939f_transport_error
);

extern void pj1939_dm36_transmit
(
    const U8                     pj1939f_priority,
    U8                           pj1939f_vnrw_component_count,
    U8                           pj1939f_continuous_mil,
    U8                           pj1939f_mil_display_strategy,
    U8                           pj1939f_mil_activation_mode,
    U16                          pj1939f_incomplete_monitor_count,
    U16                          pj1939f_mil_accumulated_time,
    U8                          *pj1939f_error_flag
);

extern void pj1939_dm37_transmit
(
    const   BOOL    pj1939f_force_transmission,
    const   U8      pj1939f_priority,
    U8              pj1939f_snrw_component_count,
    U8              pj1939f_continuous_mil,
    U8              pj1939f_mil_display_strategy,
    U8              pj1939f_mil_activation_mode,
    U16             pj1939f_incomplete_monitor_count,
    U8             *pj1939f_error_flag
);

extern void pj1939_dm38_transmit
(
    const U8                    *pj1939f_gtr_description,
    U8                           pj1939f_string_length,
    const U8                     pj1939f_priority,
    U8                          *pj1939f_error_flag,
    U8                          *pj1939f_transport_error
);

extern void pj1939_dm39_transmit
(
    const U8                     pj1939f_priority,
    U32                          pj1939f_sys_cumulative_mil_time,
    U16                          pj1939f_total_b1_time,
    U8                          *pj1939f_error_flag
);

extern void pj1939_dm40_transmit
(
    const PDTC_TABLE_T *const    pj1939f_table,
    const U8                     pj1939f_priority,
    U8                          *pj1939f_error_flag,
    U8                          *pj1939f_transport_error
);

extern void pj1939_dm41_transmit
(
    const PDTC_TABLE_T *const    pj1939f_table,
    const U8                     pj1939f_transmit,
    const U8                     pj1939f_priority,
    U8                          *pj1939f_error_flag,
    U8                          *pj1939f_transport_error
);

extern void pj1939_dm42_transmit
(
    const PDTC_TABLE_T *const    pj1939f_table,
    const U8                     pj1939f_transmit,
    const U8                     pj1939f_priority,
    U8                          *pj1939f_error_flag,
    U8                          *pj1939f_transport_error
);

extern void pj1939_dm43_transmit
(
    const PDTC_TABLE_T *const    pj1939f_table,
    const U8                     pj1939f_transmit,
    const U8                     pj1939f_priority,
    U8                          *pj1939f_error_flag,
    U8                          *pj1939f_transport_error
);

extern void pj1939_dm44_transmit
(
    const PDTC_TABLE_T *const    pj1939f_table,
    const U8                     pj1939f_transmit,
    const U8                     pj1939f_priority,
    U8                          *pj1939f_error_flag,
    U8                          *pj1939f_transport_error
);

extern void pj1939_dm45_transmit
(
    const PDTC_TABLE_T *const    pj1939f_table,
    const U8                     pj1939f_transmit,
    const U8                     pj1939f_priority,
    U8                          *pj1939f_error_flag,
    U8                          *pj1939f_transport_error
);

extern void pj1939_dm46_transmit
(
    const PDTC_TABLE_T *const    pj1939f_table,
    const U8                     pj1939f_transmit,
    const U8                     pj1939f_priority,
    U8                          *pj1939f_error_flag,
    U8                          *pj1939f_transport_error
);

extern void pj1939_dm47_transmit
(
    const PDTC_TABLE_T *const    pj1939f_table,
    const U8                     pj1939f_transmit,
    const U8                     pj1939f_priority,
    U8                          *pj1939f_error_flag,
    U8                          *pj1939f_transport_error
);

extern void pj1939_dm48_transmit
(
    const PDTC_TABLE_T *const    pj1939f_table,
    const U8                     pj1939f_transmit,
    const U8                     pj1939f_priority,
    U8                          *pj1939f_error_flag,
    U8                          *pj1939f_transport_error
);

extern void pj1939_dm49_transmit
(
    const PDTC_TABLE_T *const    pj1939f_table,
    const U8                     pj1939f_transmit,
    const U8                     pj1939f_priority,
    U8                          *pj1939f_error_flag,
    U8                          *pj1939f_transport_error
);

extern void pj1939_dm50_transmit
(
    const PDTC_TABLE_T *const    pj1939f_table,
    const U8                     pj1939f_transmit,
    const U8                     pj1939f_priority,
    U8                          *pj1939f_error_flag,
    U8                          *pj1939f_transport_error
);

extern void pj1939_dm51_transmit
(
    const PDTC_TABLE_T *const    pj1939f_table,
    const U8                     pj1939f_transmit,
    const U8                     pj1939f_priority,
    U8                          *pj1939f_error_flag,
    U8                          *pj1939f_transport_error
);

extern void pj1939_dm52_transmit
(
    const PDTC_TABLE_T *const    pj1939f_table,
    const U8                     pj1939f_transmit,
    const U8                     pj1939f_priority,
    U8                          *pj1939f_error_flag,
    U8                          *pj1939f_transport_error
);

extern BOOL pj1939_set_control_area_status
(
    PJ1939_NTE_CNTRL_AREA_T         pj1939f_cntrl_area,
    PJ1939_NTE_CNTRL_AREA_STATUS_T  pj1939f_cntrl_area_status
);

extern void pj1939_update_aecd_eng_timer1
(
    const U8                     pj1939f_aecd_number,
    const U32                    pj1939f_engine_hours
);

extern void pj1939_update_aecd_eng_timer2
(
    const U8                     pj1939f_aecd_number,
    const U32                    pj1939f_engine_hours
);

extern BOOL pj1939_pgn_send_ack
(
    const U32                           pj1939f_pgn_to_ack,
    const PJ1939_ACK_AND_CONTROL_BYTE_T pj1939f_required_response
);

extern void pj1939_client_task
(
    void
);
extern void pj1939_inhibit_reprogramming
(
    U8 pj1939f_inhibit,
    PJ1939_INHIBIT_REPR_REASONS_T pj1939f_reason
);

/********* Global Variables *********/

/** Set true if J1939 functionality is enabled, set false otherwise.
 *
 * \ingroup c_interface
 */
extern const U8 pj1939_enabled;

/** This sets the desired J1939 node address and can be altered by calibration.
 *  However, it is used only during ECU initialisation, so any calibration change
 *  must be programmed into flash to take effect on the next power-up. 
 *
 *  \note The _0 suffix is to allow for the future possibility of multiple nodes
 *        being implemented in one ECU.
 *
 * Range: [0, 253]
 *
 * \ingroup c_interface
 */
extern volatile const U8 pj1939c_node_addr_0;

/** This is a list of preferred J1939 network addresses (all unique and not the
 * null address (254) or the broadcast address (255)). The first element
 * contains the preferred node address. The last element must contain the global
 * address (255).
 *
 * Range: [0, 253] or 255
 *
 * \ingroup c_interface
 */
extern U8 node_addr[];

/** This is the number of declared J1939 network addresses in the
 * #node_addr[] array.
 *
 * Range: [2, 255]
 *
 * \ingroup c_interface
 */
extern const U8 pj1939_num_node_addr;

/** This is the J1939 network name of this unit. See J1939 specification for
 * details.
 *
 * \ingroup c_interface
 */
extern const U8 name[];

/** This is an array of receive PGNs the library must filter. Must be declared
 * in ascending order and each element must have a unique value. If the
 * application must respond to DM1, DM2, DM3 or DM11 messages, then the PGNs for
 * these must be added to this array.
 *
 * \ingroup c_interface
 */
extern const PGN_T _pgn_table[];

/** This is the number of receive PGNs in #_pgn_table[].
 * Values outside of the defined range will result in
 * undefined behaviour.
 *
 * Range: [1, 2147483647]
 *
 * \ingroup c_interface
 */
extern const U32 pj1939_num_pgns;

/** This is the list of expected PGN requests to filter. Must be declared in
 * ascending order and be unique.
 *
 * \ingroup c_interface
 */
extern const PGN_T pj1939_pgn_requested_table[];

/** This is the number of expected PGN requests in the #pj1939_pgn_requested_table[]
 * array.
 *
 * \ingroup c_interface
 */
extern const U32 pj1939_num_requested_pgns;

/** This is the buffer of source addresses for each PGN request message. Indexes
 * are the same as the #pj1939_pgn_requested_table[] array.
 *
 * Present in the C-API description only for build time size requirements.
 * The array must be declared and sized by the application. The size of the
 * array must equal #pj1939_num_requested_pgns (or one if there are no
 * requested PGNs). The array is not to be accessed by application code.
 *
 * \ingroup c_interface
 */
extern U8 pj1939_pgn_requested_src_addr[];

/** This is the buffer of destination addresses for each PGN request
 * message. Indexes are the same as the #pj1939_pgn_requested_table[] array.
 *
 * Present in the C-API description only for build time size requirements.
 * The array must be declared and sized by the application. The size of the
 * array must equal #pj1939_num_requested_pgns (or one if there are no
 * requested PGNs). The array is not to be accessed by application code.
 *
 * \ingroup c_interface
 */
extern U8 pj1939_pgn_requested_dest_addr[];

/** This is the buffer of timestamps for each PGN request message. Indexes
 * are the same as the #pj1939_pgn_requested_table[] array.
 *
 * Present in the C-API description only for build time size requirements.
 * The array must be declared and sized by the application. The size of the
 * array must equal #pj1939_num_requested_pgns (or one if there are no
 * requested PGNs). The array is not to be accessed by application code.
 *
 * \ingroup c_interface
 */
extern U32 pj1939_pgn_requested_timestamp[];

/** This is the buffer of priority for each PGN request message. Indexes
 * are the same as #pj1939_pgn_requested_table[], but applied per bit, rather
 * than per byte.
 *
 * Present in the C-API description only for build time size requirements.
 * The array must be declared and sized by the application. The size of the
 * array must equal \e { (#pj1939_num_requested_pgns + 7) / 8 } (or one if
 * there are no requested PGNs). The array is not to be accessed by
 * application code.
 *
 * \ingroup c_interface
 */
extern U8 pj1939_pgn_requested_bitmap[];

/** This is the size of the data portion to each J1939 receive buffer.
 * The array must be declared and sized by the application. The size of the
 * array must equal #pj1939_num_pgns (or one if there are no received PGNs).
 *
 * Each element corresponds to the same element in the array #_pgn_table[], and
 * is the number of data bytes for the corresponding PGN message.
 *
 * Range: [0, 1785] bytes
 *
 * \ingroup c_interface
 */
extern U16 pj1939_rx_buf_data_size[];

/** This is an array of pointers to each data buffer for each J1939 receive
 * message. The array must be declared and sized by the application. The size
 * of the array must equal #pj1939_num_pgns (or one if there are no received
 * PGNs).
 *
 * Each element corresponds to the same element in the array #_pgn_table[], and
 * is a pointer to an area of memory large enough to store the data bytes for
 * the corresponding PGN message.
 *
 * \ingroup c_interface
 */
extern U8 *const pj1939_rx_buf_data[];

/** This is an array of pointers to each J1939 receive message. The array must be
 * declared and sized by the application. The size of the array must equal
 * #pj1939_num_pgns (or one if there are no received PGNs).
 *
 * Each element corresponds to the same element in the array #_pgn_table[], and
 * is a pointer to a variable of type #PJ1939_RX_BUF_T.
 *
 * \ingroup c_interface
 */
extern PJ1939_RX_BUF_T *const pj1939_rx_buf[];

/** This is the CAN link used for the J1939 network messaging.
 * Use the macros included by the pio.h file, of the form
 * PIO_CAN_[NAME].
 *
 * \ingroup c_interface
 */
extern const PCX_LCHAN_T pj1939_can_link;

/** This is the number of transport transmit buffers that can run in parallel.
 * The more transmit buffers there are, the larger the number of destination
 * nodes can be communicated with at the same time. At the same time, the more
 * transmit buffers there are, the larger the amount of RAM required to accommodate
 * the parallel information. Values outside of the defined range will result in
 * undefined behaviour.
 *
 * Range: [1, 127] buffers.
 *
 * \ingroup c_interface
 */
extern const U8 pj1939_num_ttx;

/** This is the number of transport receive buffers that can run in parallel.
 * The more receive buffers there are, the larger the number of destination
 * nodes can be communicated with at the same time. At the same time, the more
 * receive buffers there are, the larger the amount of RAM required to accommodate
 * the parallel information.
 *
 * Range: [1, 255] buffers.
 *
 * \ingroup c_interface
 */
extern const U8 pj1939_num_trx;

/** This is the maximum data size of any J1939 message (both reception and
 * transmission). Any J1939 message with data larger than this variable is
 * rejected by the library.
 *
 * Range: [8, 1785] bytes.
 *
 * \ingroup c_interface
 */
extern const U16 pj1939_size_j1939_rx_buf;

/** This is the number of receive and transmit CAN buffers allocated for J1939
 * message processing.
 *
 * Range: [1, 255]
 *
 * \ingroup c_interface
 */
extern const U8 pj1939_num_rx_tx_bufs;

/** This is an array of J1939 transmit messages.
 *
 * Present in the C-API description only for build time size requirements.  The
 * array must be declared and sized by the application. The size of the array
 * must equal #pj1939_num_ttx (or one if there are no requested PGNs). The array
 * is not to be accessed by application code.
 *
 * \ingroup c_interface
 */
extern J1939_TX_MESSAGE_T pj1939_ttx_buf[];

/** This is an array of pointers to counters for delayed transmit errors.
 * The index is the same as for the #pj1939_ttx_buf[] array.
 *
 * Present in the C-API description only for build time size requirements.  The
 * array must be declared and sized by the application. The size of the array
 * must equal #pj1939_num_ttx. The array is not to be accessed by application
 * code.
 *
 * \ingroup c_interface
 */
extern U8 *pj1939_ttx_error_ptr[];

/** This is the buffer space allocated for all J1939 transmit messages.
 *
 * Present in the C-API description only for build time size requirements.  The
 * array must be declared and sized by the application. The size of the array
 * must equal \e {#pj1939_num_ttx * #pj1939_size_j1939_rx_buf}. The array is not
 * to be accessed by application code.
 *
 * \ingroup c_interface
 */
extern U8 pj1939_ttx_buf_data[];

/** This is the buffer space allocated for all J1939 receive messages.
 *
 * Present in the C-API description only for build time size requirements.  The
 * array must be declared and sized by the application. The size of the array
 * must equal \e {#pj1939_num_trx * #pj1939_size_j1939_rx_buf}. The array is not
 * to be accessed by application code.
 *
 * \ingroup c_interface
 */
extern U8 pj1939_msg_buffer[];

/** This is the state of the transmission messages that require transport
 * support (i.e., messages that have a data length greater than 8 bytes).
 *
 * Present in the C-API description only for build time size requirements.  The
 * array must be declared and sized by the application. The size of the array
 * must equal #pj1939_num_ttx. The array is not to be accessed by application
 * code.
 *
 * \ingroup c_interface
 */
extern J1939_TRANSPORT_TX_INFO tx_state[];

/** This is the state of the receive messages that require transport support
 * (i.e., messages that have a data length greater than 8 bytes)
 *
 * Present in the C-API description only for build time size requirements.  The
 * array must be declared and sized by the application. The size of the array
 * must equal #pj1939_num_trx. The array is not to be accessed by application
 * code.
 *
 * \ingroup c_interface
 */
extern J1939_MESSAGE rx_message[];

/** This is the queue of received messages.
 *
 * Present in the C-API description only for build time size requirements.  The
 * array must be declared and sized by the application. The size of the array
 * must equal #pj1939_num_rx_tx_bufs. The array is not to be accessed by
 * application code.
 *
 * \ingroup c_interface
 */
extern CAN_PACKET_T in_queue[];

/** This is the queue of transmit messages.
 *
 * Present in the C-API description only for build time size requirements.  The
 * array must be declared and sized by the application. The size of the array
 * must equal #pj1939_num_rx_tx_bufs. The array is not to be accessed by
 * application code.
 *
 * \ingroup c_interface
 */
extern CAN_PACKET_T out_queue[];

/** This is a flag to determine whether to use a common priority for all J1939
 * multi-frame diagnostic message transmissions. If true then the priority for
 * such messages is taken from #pj1939_common_multiframe_priority. If false, the
 * priority is as defined in the argument to the appropriate message transmit
 * function. Note that that function argument always determines priority for
 * single-frame messages.
 *
 * \ingroup c_interface
 */
extern const BOOL pj1939_use_common_mf_priority;

/** This is the common priority used for all J1939 multi-frame diagnostic message
 * transmissions. It is only used when the #pj1939_use_common_mf_priority flag is true.
 *
 * Range: [0, 7]
 *
 * \ingroup c_interface
 */
extern const U8 pj1939_common_multiframe_priority;

/** This is an array of J1939 node addresses corresponding to the list of
 * addresses which are known to transmit DM1 messages. Addresses must be
 * declared in ascending order with each address being unique. DM1 messages
 * sent from other addresses are ignored by the library.
 *
 * If the ECU is to process received DM1 messages, then the PGN 65226
 * must be added to the array #_pgn_table[].
 *
 * Range: [0, 253]
 *
 * \ingroup c_interface
 */
extern const U8 pj1939_dm1_source_addr[];

/** This is the number of declared J1939 DM1 transmitter addresses in the
 * #pj1939_dm1_source_addr[] array.
 *
 * Range: [0, 255]
 *
 * \ingroup c_interface
 */
extern const U8 pj1939_dm1_source_addr_num;

/** This is the list of pointers to message data buffers for each DM1 message to
 * be received. Each message buffer pointed to must be an array of bytes of size
 * #pj1939_size_j1939_rx_buf. The size of the array must equal
 * #pj1939_dm1_source_addr_num.
 *
 * \ingroup c_interface
 */
extern U8 *const pj1939_dm1_rx_buf_data[];

/** This is an array of pointers to message buffers for each DM1 message
 * to be received.
 *
 * Present in the C-API description only for build time size requirements.  The
 * array must be declared and sized by the application. The size of the array
 * must equal #pj1939_dm1_source_addr_num. The array is not to be accessed by
 * application code.
 *
 * \ingroup c_interface
 */
extern PJ1939_RX_BUF_T *const pj1939_dm1_rx_buf[];

/** This is an array of J1939 node addresses corresponding to the list of
 * addresses which are known to transmit DM2 messages. Addresses must be
 * declared in ascending order with each address being unique. DM2 messages sent
 * from other addresses are ignored by the library.
 *
 * Range: [0, 253]
 *
 * \ingroup c_interface
 */
extern const U8 pj1939_dm2_source_addr[];

/** This is the number of declared J1939 DM2 transmitter addresses in the
 * #pj1939_dm2_source_addr[] array.
 *
 * If the ECU is to process received DM2 messages, then the PGN 65227
 * must be added to the array #_pgn_table[].
 *
 * Range: [0, 255]
 *
 * \ingroup c_interface
 */
extern const U8 pj1939_dm2_source_addr_num;

/** This is the list of pointers to message data buffers for each DM2 message to
 * be received. Each message buffer pointed to must be an array of bytes of size
 * #pj1939_size_j1939_rx_buf. The size of the array must equal
 * #pj1939_dm2_source_addr_num.
 *
 * \ingroup c_interface
 */
extern U8 *const pj1939_dm2_rx_buf_data[];

/** This is an array of pointers to message buffers for each DM2 message
 * to be received.
 *
 * Present in the C-API description only for build time size requirements.  The
 * array must be declared and sized by the application. The size of the array
 * must equal #pj1939_dm2_source_addr_num. The array is not to be accessed by
 * application code.
 *
 * \ingroup c_interface
 */
extern PJ1939_RX_BUF_T *const pj1939_dm2_rx_buf[];

/** This is the number of DM7 test requests that are to be buffered.
 *
 * Range: [1, 255] buffers.
 *
 * \ingroup c_extdiag_interface
 */
extern const U8 pj1939_dm7_request_buf_size;

/** This is the stored buffer of DM7 requests which have been received but have not
 * yet been processed.
 *
 * The array is sized by #pj1939_dm7_request_buf_size.
 *
 * \note The array is private to the library and should only be defined by the
 *       application. It is exposed as part of the API so it can be sized
 *       at build time.
 *
 * \ingroup c_extdiag_interface
 */
extern PJ1939_DM7_BUFFER_T pj1939_req_test_list[];

/** This is an array of states for each DTC.
 *
 * The array is sized by total number of DTCs in the system, as reported by #pdtc_table_all.
 * It is used by the J1939 feature to maintain information required for DM1 messages.
 *
 * \note The array is private to the library and should only be defined by the
 *       application. It is exposed as part of the API so it can be sized
 *       at build time to minimise the library memory footprint.
 *
 * \ingroup c_interface
 */
extern U8 pj1939_state[];

/** This is an array of sent flags for each DTC.
 *
 * The array is sized by total number of DTCs in the system, as reported by #pdtc_table_all.
 * It is used by the J1939 feature to maintain information required for DM1 messages.
 *
 * \note The array is private to the library and should only be defined by the
 *       application. It is exposed as part of the API so it can be sized
 *       at build time to minimise the library memory footprint.
 *
 * \ingroup c_interface
 */
extern U8 pj1939_sent[];

/** This is an array of transient fault states for each DTC.
 *
 * The array is sized by total number of DTCs in the system, as reported by #pdtc_table_all.
 * It is used by the J1939 feature to maintain information required for DM35 messages.
 *
 * \note The array is private to the library and should only be defined by the
 *       application. It is exposed as part of the API so it can be sized
 *       at build time to minimise the library memory footprint.
 *
 * \ingroup c_interface
 */
extern U8 pj1939_transient[];

/** This is an array of transient sent flags for each DTC.
 *
 * The array is sized by total number of DTCs in the system, as reported by #pdtc_table_all.
 * It is used by the J1939 feature to maintain information required for DM35 messages.
 *
 * \note The array is private to the library and should only be defined by the
 *       application. It is exposed as part of the API so it can be sized
 *       at build time to minimise the library memory footprint.
 *
 * \ingroup c_interface
 */
extern U8 pj1939_transient_sent[];

/** The total number of EI-AECDs that are declared.
 *
 * \ingroup c_extdiag_interface
 */
extern volatile const U8 pj1939c_num_aecd;

/** The list of AECDs that the library will maintain
 *
 * Present in the C-API description only for build time size requirements.
 * The array must be declared and sized by the application. The size of the
 * array must equal \p #pj1939c_num_aecd.
 * The array is not to be accessed by application code.
 *
 * \ingroup c_extdiag_interface
 */
extern PJ1939_AECD_T * const pj1939_aecd_table[];

#endif /* PJ1939_H */

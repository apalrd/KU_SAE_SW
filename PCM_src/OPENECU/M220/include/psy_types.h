/*****************************************************************************/
/**
 *  \file    psy_types.h
 *  \brief   Standard integer types for all build environments.
 *
 *  Version: $Id: psy_types.h 36631 2013-12-04 00:36:19Z rdoebler $
 *  File:    $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/psy/psy_types.h $
 */

/*  Copyright (C) 2013 Pi Innovo
 *  This document (program) contains proprietary information
 *  which is the property of Pi Innovo
 *  The contents of this document (program) must not be copied
 *  or disclosed to a third party without the prior agreement
 *  of an authorised officer of Pi Innovo
 */

#ifndef PSY_TYPES_H
#define PSY_TYPES_H

/********* Includes *********/

#include <stddef.h>

/********* These macros can be changed *********/

/** Ensure the NULL pointer is defined (if it is not already)
 * \ingroup c_interface
 */
#ifndef NULL
#define NULL               ((void *) 0)
#endif

/** Ensure FALSE is defined (if it is not already)
 * \ingroup c_interface
 */
#ifndef FALSE
#define FALSE              ((BOOL)0)
#endif

/** Ensure TRUE is defined (if it is not already)
 * \ingroup c_interface
 */
#ifndef TRUE
#define TRUE               ((BOOL)1)
#endif

/** This macro resolves to the number of elements in an array.
 */
#define PSY_ARRAYSIZE(a)   (sizeof(a) / sizeof((a)[0]))

/** Common binary points for fixed point arithmetic.
 */
#define PSY_BIN_1          2
#define PSY_BIN_2          4
#define PSY_BIN_3          8
#define PSY_BIN_4          16
#define PSY_BIN_5          32
#define PSY_BIN_6          64
#define PSY_BIN_7          128
#define PSY_BIN_8          256
#define PSY_BIN_9          512
#define PSY_BIN_10         1024
#define PSY_BIN_11         2048
#define PSY_BIN_12         4096
#define PSY_BIN_13         8192
#define PSY_BIN_14         16384
#define PSY_BIN_15         32768
#define PSY_BIN_16         65536
#define PSY_BIN_22         4194304
#define PSY_BIN_24         16777216
#define PSY_BIN_31         2147483647

/** Maximum and minimum values of the standard types.
 */
#define PSY_MAX_U32        4294967295UL
#define PSY_MAX_S32        2147483647L
#define PSY_MIN_S32        (-2147483647L - 1L)
#define PSY_MAX_U24        16777215UL
#define PSY_MAX_S24        8388607UL
#define PSY_MIN_S24        (-8388608UL)
#define PSY_MAX_U16        65535
#define PSY_MAX_S16        32767
#define PSY_MIN_S16        (-32768)
#define PSY_MAX_U8         255
#define PSY_MAX_S8         127
#define PSY_MIN_S8         (-128)

/********* These macros must not be changed *********/

/* None */

/********* Global Structure Definitions *********/

#if defined _WIN32

/* MSVC */
#if defined CFG_USE_WINDOWS
#include <windows.h>
#endif

/* No packed keyword required for this compiler.
 */
#define PSY_PACKED

/* type qualifier to declare variable as calibration
 */
#define OE_CAL

/** This typedef declares a signed 8 bit integer.
 * \ingroup c_interface
 */
typedef signed char        S8;

/** This typedef declares an unsigned 8 bit integer.
 * \ingroup c_interface
 */
typedef unsigned char      U8;

#if !defined CFG_USE_WINDOWS
/** This typedef declares a boolean integer.
 * \ingroup c_interface
 */
typedef unsigned char      BOOL;
#endif

/** This typedef declares a signed 16 bit integer.
 * \ingroup c_interface
 */
typedef signed short       S16;

/** This typedef declares an unsigned 16 bit integer.
 * \ingroup c_interface
 */
typedef unsigned short     U16;

/** This typedef declares a signed 32 bit integer.
 * \ingroup c_interface
 */
typedef signed long        S32;

/** This typedef declares an unsigned 32 bit integer.
 * \ingroup c_interface
 */
typedef unsigned long      U32;

#if !defined CFG_USE_WINDOWS
/** This typedef declares a signed 32 bit integer.
 * \ingroup c_interface
 */
typedef signed long        INT;

/** This typedef declares an unsigned 32 bit integer.
 * \ingroup c_interface
 */
typedef unsigned long      UINT;
#endif

/** This typedef declares a 32 bit floating point.
 * \ingroup c_interface
 */
typedef float              F32;

/** This typedef declares a 32 bit floating point.
 * \ingroup c_interface
 */
typedef float              FREAL;

/** This typedef declares a 64 bit floating point.
 * \ingroup c_interface
 */
typedef double             F64;

#elif defined __DCC__

/* Diab compiler */

/* Allow use of a packed keyword for this compiler.
 */
#define PSY_PACKED         __packed__

/* type qualifier to declare variable as calibration
 */
#define OE_CAL             volatile const

/** This typedef declares a signed 8 bit integer.
 * \ingroup c_interface
 */
typedef signed char        S8;

/** This typedef declares an unsigned 8 bit integer.
 * \ingroup c_interface
 */
typedef unsigned char      U8;

/** This typedef declares a boolean integer.
 * \ingroup c_interface
 */
typedef unsigned char      BOOL;

/** This typedef declares a signed 16 bit integer.
 * \ingroup c_interface
 */
typedef signed short       S16;

/** This typedef declares an unsigned 16 bit integer.
 * \ingroup c_interface
 */
typedef unsigned short     U16;

/** This typedef declares a signed 32 bit integer.
 * \ingroup c_interface
 */
typedef signed long        S32;

/** This typedef declares an unsigned 32 bit integer.
 * \ingroup c_interface
 */
typedef unsigned long      U32;

/** This typedef declares a signed 64 bit integer.
 * \ingroup c_interface
 */
typedef signed long long   S64;

/** This typedef declares an unsigned 64 bit integer.
 * \ingroup c_interface
 */
typedef unsigned long long U64;

/** This typedef declares a signed 32 bit integer.
 * \ingroup c_interface
 */
typedef signed long        INT;

/** This typedef declares an unsigned 32 bit integer.
 * \ingroup c_interface
 */
typedef unsigned long      UINT;

/** This typedef declares a 32 bit floating point.
 * \ingroup c_interface
 */
typedef float              F32;

/** This typedef declares a 32 bit floating point.
 * \ingroup c_interface
 */
typedef float              FREAL;

/** This typedef declares a 64 bit floating point.
 * \ingroup c_interface
 */
typedef double             F64;

#elif defined(__GCC__) || defined(__MAKEDEPS__)

/* GCC compiler */

/* No packed keyword required for this compiler.
 */
#define PSY_PACKED          __attribute__ ((packed))

/* type qualifier to declare variable as calibration
 */
#define OE_CAL             volatile const __attribute__ ((section(".cal_sec")))

/** This typedef declares a signed 8 bit integer.
 * \ingroup c_interface
 */
typedef signed char        S8;

/** This typedef declares an unsigned 8 bit integer.
 * \ingroup c_interface
 */
typedef unsigned char      U8;

/** This typedef declares a boolean integer.
 * \ingroup c_interface
 */
typedef unsigned char      BOOL;

/** This typedef declares a signed 16 bit integer.
 * \ingroup c_interface
 */
typedef signed short       S16;

/** This typedef declares an unsigned 16 bit integer.
 * \ingroup c_interface
 */
typedef unsigned short     U16;

/** This typedef declares a signed 32 bit integer.
 * \ingroup c_interface
 */
typedef signed long        S32;

/** This typedef declares an unsigned 32 bit integer.
 * \ingroup c_interface
 */
typedef unsigned long      U32;

/** This typedef declares a signed 32 bit integer.
 * \ingroup c_interface
 */
typedef signed long        INT;

/** This typedef declares an unsigned 32 bit integer.
 * \ingroup c_interface
 */
typedef unsigned long      UINT;

/** This typedef declares a 32 bit floating point.
 * \ingroup c_interface
 */
typedef float              F32;

/** This typedef declares a 32 bit floating point.
 * \ingroup c_interface
 */
typedef float              FREAL;

/** This typedef declares a 64 bit floating point.
 * \ingroup c_interface
 */
typedef double             F64;

#elif defined __LINT__

/* Types for LINT static analysis */

/* No packed keyword required for this static analysis tool.
 */
#define PSY_PACKED

/* type qualifier to declare variable as calibration
 */
#define OE_CAL

/** This typedef declares a signed 8 bit integer.
 * \ingroup c_interface
 */
typedef signed char        S8;

/** This typedef declares an unsigned 8 bit integer.
 * \ingroup c_interface
 */
typedef unsigned char      U8;

/** This typedef declares a boolean integer.
 * \ingroup c_interface
 */
typedef unsigned char      BOOL;

/** This typedef declares a signed 16 bit integer.
 * \ingroup c_interface
 */
typedef signed short       S16;

/** This typedef declares an unsigned 16 bit integer.
 * \ingroup c_interface
 */
typedef unsigned short     U16;

/** This typedef declares a signed 32 bit integer.
 * \ingroup c_interface
 */
typedef signed long        S32;

/** This typedef declares an unsigned 32 bit integer.
 * \ingroup c_interface
 */
typedef unsigned long      U32;

/** This typedef declares a signed 64 bit integer.
 * \ingroup c_interface
 */
typedef signed long long   S64;

/** This typedef declares an unsigned 64 bit integer.
 * \ingroup c_interface
 */
typedef unsigned long long U64;

/** This typedef declares a signed 32 bit integer.
 * \ingroup c_interface
 */
typedef signed long        INT;

/** This typedef declares an unsigned 32 bit integer.
 * \ingroup c_interface
 */
typedef unsigned long      UINT;

/** This typedef declares a 32 bit floating point.
 * \ingroup c_interface
 */
typedef float              F32;

/** This typedef declares a 32 bit floating point.
 * \ingroup c_interface
 */
typedef float              FREAL;

/** This typedef declares a 64 bit floating point.
 * \ingroup c_interface
 */
typedef double             F64;

#else
#error "psy_types.h: was compiled with no specific compiler type defined."
#endif

/********* Global Prototypes *********/

/* None */

/**** Global Variables ****/

/* None */

#endif /* PSY_TYPES_H */

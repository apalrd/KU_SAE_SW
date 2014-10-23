/******** *********************************************************************/
/**
 *  \file    pnv.h
 *  \brief   Public interface to the non-volatile memory freature.
 *
 *  Version: $Id: pnv.h 35574 2013-10-09 21:18:40Z sborders $
 *  File:    $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/pnv/pnv.h $
 */

/*  Copyright (C) 2013 Pi Innovo
 *  This document (program) contains proprietary information
 *  which is the property of Pi Innovo
 *  The contents of this document (program) must not be copied
 *  or disclosed to a third party without the prior agreement
 *  of an authorised officer of Pi Innovo
 */

#ifndef PNV_H
#define PNV_H

/********* Includes *********/

#include "psy.h"

/********* These macros can be changed *********/

/** This macro defines the value for #pnv_store when non-volatile data is to be
 * stored in battery backed RAM across power cycles.
 *
 * \ingroup c_interface
 */
#define PNV_STORE_IN_BBRAM   0

/** This macro defines the value for #pnv_store when non-volatile data is to be
 * stored in Flash across power cycles.
 *
 * \ingroup c_interface
 */
#define PNV_STORE_IN_FLASH   1

/********* These macros must not be changed *********/

/* None */

/********* Global Structure Definitions *********/

/** Error values for debugging -- when an error is found when calling the PNV API,
 * the API calls a function with an enumeration from this type.
 *
 * \ingroup  c_interface
 */
typedef enum
{
    /** Error raised if one of the adaptive table lookup and interpolation
     * functions finds an invalid argument.
     */
    PNV_ADAPMAP_INVALID_ARG                         = 1,

    /** Error raised if the adaptive scalar function find an invalid argument.
     */
    PNV_ADAPSCALAR_INVALID_ARG                      = 2,

    /** Error raised if the array function finds an invalid argument.
     */
    PNV_ARRAY_INVALID_ARG                           = 3,

    /** Error raised if the array dump function finds an invalid argument.
     */
    PNV_ARRAY_DUMP_INVALID_ARG                      = 4
}
PNV_ERROR_CODE_T;


/** An enumerated type which contains success and failure codes returned by the
 * adaptive map lookup and interpolation functions.
 *
 * \ingroup c_interface
 */
typedef enum
{
    /** Return code if everything progressed as expected.
     */
    PNV_RC_OK,

    /** Return code if at least one of the arguments points to null.
     */
    PNV_RC_BAD_ARGS,

    /** Return code if there are insufficient elements to use the function.
     */
    PNV_RC_INSUFFICIENT_ELEMENTS
}
PNV_RC_T;



/** This typedef defines a structure which is used to locate all of the adaptive
 * parameters. During initialisation, if the adaptive data cannot be recalled,
 * the default adaptive data is used instead.
 */
typedef struct
{
    /** A pointer to the RAM version of the object. Used during run-time for
     * read and write purposes, it is initialised from the non-volatile copy
     * of the same object (or the constant copy if non-volatile memory fails).
     * The RAM version is copied to non-volatile memory (if possible) when
     * #pnv_commit_to_store() is called.
     * Cannot point to NULL.
     *
     * \ingroup c_interface
     */
    void *adap_ptr;

    /** A pointer to a constant version of the object, used to restore a
     * default value if the non-volatile copy of the same object could
     * not be recovered from non-volatile memory during initialisation.
     * Cannot point to NULL.
     *
     * \ingroup c_interface
     */
    const void *def_ptr;

    /** The size of the object pointed to by adap_ptr and def_ptr in bytes.
     * Cannot be zero.
     *
     * \ingroup c_interface
     */
    U32   size;
}
PNV_ADAP_T;

/********* Global Prototypes *********/

extern void pnv_commit_to_store
(
    void
);

extern BOOL pnv_is_store_intact
(
    void
);

extern PNV_RC_T pnv_adap_map_1d_f32
(
    F32                  pnvf_adapt_xx,
    F32                  pnvf_adapt_increment,
    BOOL                 pnvf_adapt,
    BOOL                 pnvf_reset,
    S32                  pnvf_elem_n,
    volatile const F32  *pnvf_arr_px,
    volatile const F32  *pnvf_arr_pz_default,
    F32                 *pnvf_arr_adapted
);

extern PNV_RC_T pnv_adap_map_2d_f32
(
    F32                  pnvf_adapt_xx,
    F32                  pnvf_adapt_yy,
    F32                  pnvf_adapt_increment,
    BOOL                 pnvf_adapt,
    BOOL                 pnvf_reset,
    S32                  pnvf_elem_nx,
    S32                  pnvf_elem_ny,
    volatile const F32  *pnvf_arr_px,
    volatile const F32  *pnvf_arr_py,
    volatile const F32  *pnvf_arr_pz_default,
    F32                 *pnvf_arr_adapted
);

extern void pnv_adap_scalar_f32
(
    F32                  pnvf_adapt_increment,
    BOOL                 pnvf_adapt,
    BOOL                 pnvf_reset,
    volatile const F32  *pnvf_adapt_default,
    F32                 *pnvf_adapted
);

extern void pnv_array
(
    U32                  pnvf_index,
    volatile const void *pnvf_new_value,
    BOOL                 pnvf_change,
    BOOL                 pnvf_reset,
    U32                  pnvf_elem_size,
    S32                  pnvf_elem_n,
    volatile const void *pnvf_array_default,
    BOOL                *pnvf_valid_index,
    void                *pnvf_value
);

extern void pnv_array_dump
(
    U32                  pnvf_elem_size,
    S32                  pnvf_num_elems,
    volatile const void *pnvf_array_default,
    void                *pnvf_output
);

extern void pnv_adap_map_f32_locate
(
    F32                     pnvf_u,
    volatile const F32     *pnvf_p,
    S32                     pnvf_n,
    S32                    *pnvf_i
);

extern void pnv_get_adap_ram_pointer
(
    volatile const void     *pnvf_default_p,
    void                   **pnvf_ram_p
);

extern BOOL pnv_is_flash_adap_csum_valid
(
    void
);

extern BOOL pnv_is_ram_adap_csum_valid
(
    void
);

/********* Global Variables *********/

/** This defines which memory type will be used to store non-volatile
 * adaptive data.
 *
 * If set to #PNV_STORE_IN_BBRAM then non-volatile adaptive data is stored in
 * battery backed RAM, and if set to #PNV_STORE_IN_FLASH then the non-volatile
 * adaptive data is stored in Flash.
 *
 * \warning Some memory stores are not implemented on some target ECUs.
 *          See the technical specification of the ECU to determine if
 *          the store type is available.
 *
 * \ingroup c_interface
 */
extern const U8 pnv_store;

/** This is a checksum of the non-volatile memory objects stored in RAM.
 * The checksum is the CCITT CRC. The checksum must be the first linked
 * variable in the RAM memory area dedicated to non-volatile memory.  It
 * is allocated by the linker.
 *
 * \ingroup c_interface
 */
extern U8 pnv_adap_csum[];

#endif /* PNV_H */

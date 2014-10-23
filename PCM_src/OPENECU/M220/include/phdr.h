/*
 *****************************************************************************
 *
 *  Project:        OpenECU
 *  Version:        $Id: phdr.h 33447 2013-04-30 07:21:01Z cwartnaby $
 *  File:           $URL: https://apple.ps.local/svn/OpenECU/development/platform/tags/release-2.2.1-igloo-dev4/targets/src/common/phdr/phdr.h $
 *  Description:    Global platform image header structure.
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

#ifndef PHDR_H
#define PHDR_H

/********* Includes *********/

#include "psy.h"

/********* These macros can be changed *********/

/* None */

/********* These macros must not be changed *********/

/* None */

/********* Global Structure Definitions *********/

/** This macro defines the value used to determine if no checksum should be applied to a memory
 * region. See \c PHDR_CHKSUM_REGION_T for a definition of a memory region.
 *
 * \ingroup hl_interface
 */
#define PHDR_CHKSUM_ALG_NONE            0

/** This macro defines the value used to determine if a simple arithmetic checksum should be applied
 * to a memory region. See \c PHDR_CHKSUM_REGION_T for a definition of a memory region.
 *
 * \ingroup hl_interface
 */
#define PHDR_CHKSUM_ALG_CHECKSUM        1

/** This macro defines the value used to determine if a 16-bit CCITT CRC checksum should be applied
 * to a memory region. See \c PHDR_CHKSUM_REGION_T for a definition of a memory region.
 *
 * \ingroup hl_interface
 */
#define PHDR_CHKSUM_ALG_CRC16_CCITT     2 /* 16 bit CRC. */

/** This macro defines the value used to determine if an IP-style 16-bit checksum
 * with one's complement wraparound should be applied to a memory region.
 * See \c PHDR_CHKSUM_REGION_T for a definition of a memory region.
 *
 * \ingroup hl_interface
 */
#define PHDR_CHKSUM_ALG_IP_16BIT        3

/** This macro defines the maximum number of memory regions to check (e.g., using a simple checksum,
 * or CRC) before the memory is considered to be intact and valid.
 *
 * \ingroup hl_interface
 */
#define PHDR_MAX_CHKSUM_BLOCKS          16

/** This structure declares a memory region and its corresponding checksum algorithm and checksum
 * value. Memory regions declared as part of a header are checked by the boot component immediately
 * after a reset before those regions are used.
 *
 * \note The size of the region structure is padded to ensure it is 12 bytes long. This ensures
 *       the compiler does not artificially pad the structure causing it to have a different length,
 *       which in turn would incorrectly alter the size of the \c PHDR_HEADER_T structure.
 *
 * \ingroup hl_interface
 */
typedef struct
{
    U32 start_addr;
    U32 size;
    U16 value;
    U8  algorithm; /* should really be an enum but want to be byte-sized; CRC, sum, or whatever, or nothing */
    U8  padding;
}
PHDR_CHKSUM_REGION_T;

/** This function pointer type defines the function signature
 * for the entry_point member of the header structure.
 *
 * \ingroup hl_interface
 */
typedef void (*PHDR_ENTRY_POINT_T) (void);

/** This structure defines a header to each program image (boot,
 * reprogramming and application images).
 *
 * Its initial elements must remain fixed, so that older
 * versions of program may access elements at the same location.
 * As the structure must remain fixed, the structure has been
 * designed in as flat.
 *
 * New elements may be added at the end by decreasing the
 * pad size and inserting the necessary items just before pad[].
 *
 * Great care must be taken to ensure that elements align to
 * addresses so that the compiler will not introduce slient
 * padding into the structure.
 *
 * Any element that is initialised with all bits set means
 * that the element is unavailable to the inspecting program.
 * If an element with all bits set is a valid value, an
 * additional flag indicating this state must be made available.
 *
 * \ingroup hl_interface
 */
typedef struct
{
    /* Header checksum or code CRC */
    U16 checksum;

    /* Version information */
    U16 major_version_number;
    U16 minor_version_number;
    U16 sub_minor_version_number;
    U16 build_year;
    U16 build_month;
    U16 build_day;

    /* Starting address for the program this header describes. */
    U32 entry_point;

    /* CPU initialisation data (MPC555). Some of the elements contain
     * write once data written during reset from the reset configuration
     * register. These write once bits, naturally, cannot be rewritten
     * and anyone modifying the values of these bits should take this
     * into consideration.
     */
    U32 init_msr;                           /* inc, 565 and 5534 */
    U32 init_immr;
    U32 init_plprcr;
    U32 init_sccr;
    U32 init_colir;
    U32 init_siumcr;
    U32 init_sypcr;
    U32 init_spr_mi_rba0;
    U32 init_spr_mi_rba1;
    U32 init_spr_mi_rba2;
    U32 init_spr_mi_rba3;
    U32 init_spr_mi_ra0;
    U32 init_spr_mi_ra1;
    U32 init_spr_mi_ra2;
    U32 init_spr_mi_ra3;
    U32 init_spr_mi_gra;
    U32 init_spr_mi_bbcmcr;
    U32 init_spr_l2u_rba0;
    U32 init_spr_l2u_rba1;
    U32 init_spr_l2u_rba2;
    U32 init_spr_l2u_rba3;
    U32 init_spr_l2u_ba0;
    U32 init_spr_l2u_ba1;
    U32 init_spr_l2u_ba2;
    U32 init_spr_l2u_ba3;
    U32 init_spr_l2u_gra;
    U32 init_spr_l2umcr;
    U32 init_cmf_a_mcr;
    U32 init_cmf_b_mcr;
    U32 init_sram_a_mcr;
    U32 init_sram_b_mcr;
    U32 init_or0;
    U32 init_br0;
    U32 init_or1;
    U32 init_br1;
    U32 init_or2;
    U32 init_br2;
    U32 init_or3;
    U32 init_br3;
    U32 init_dmor;
    U32 init_dmbr;
    U32 init_ictrl;
    U32 init_ictrl1;
    U32 init_ictrl2;
    U32 init_der;
    U32 init_tbscr;
    U32 init_rtcsc;
    U32 init_pdmcr;
    U32 init_umcr;
    U32 init_mios1tpcr;

    /* Shared (R)PRG settings for CCP over CAN */
    /* These shared settings for CCP over CAN have been superceeded
     * by a more flexible mechanism (filling the header after the
     * checksum has been calculated is difficult to do in the current
     * build mechanism). These variables are no longer used.
     */
    U16 dummy_ccp_rx_id;
    U16 dummy_ccp_tx_id;
    U16 dummy_ccp_baud;
    U16 dummy_ccp_bus;

    /* Config details for CAN gateway functionality. CAN gateway functionality
     * removed around version 1.8.0, these variables no longer have any meaning.
     * Retained so that the header remains backwards compatible.
     */
    U16 expected_pcode_version;
    U32 start_free_code;
    U32 end_free_code;
    U32 start_free_ram;
    U32 end_free_ram;
    U32 config_code_addr;

    /* Pointer to shared (R)PRG settings for CCP over CAN. Implemented
     * as U32 rather than pointer, so that across each of the targets
     * the header remains the same size (e.g., sizeof(U8*) on MPC55xx
     * differs from sizeof(U8*) on HCS12).
     */
    U32 ccp_rx_id;                                /* points to U32 */
    U32 ccp_tx_id;                                /* points to U32 */
    U32 ccp_baud;                                 /* points to U32 */
    U32 ccp_bus;                                  /* points to U8 */
    U32 ccp_station_addr;                         /* points to U8 */

    /* Shared (R)PRG settings for CCP over CAN */
    U32 new_ccp_rx_id;
    U32 new_ccp_tx_id;
    U32 new_ccp_baud;
    U8  new_ccp_bus;
    U8  new_ccp_station_addr;

    /* Model identification information */
    U32 model_major_ver;                          /* points to U16 */
    U32 model_minor_ver;                          /* points to U16 */
    U32 model_sub_ver;                            /* points to U16 */
    U32 model_name;                               /* points to char */
    U32 model_decr;                               /* points to char */
    U32 model_copyright;                          /* points to char */

    /* MPC565 specific initialisation.
     * Note that these augment the previous declarations.
     */
    U32 init_pdmcr2;
    U32 init_c3fmcr_a;
    U32 init_c3fmcre_a;
    U32 init_c3fmcr_b;
    U32 init_c3fmcre_b;
    U32 init_crammcr_a;
    U32 init_cramolvcr_a;
    U32 init_crammcr_b;
    U32 init_cramolvcr_b;

    /* MPC55xx specific initialisation
     * Note that these augment the previous declarations.
     */
    U32 init_tcr;
    U32 init_hid0;
    U32 init_bucsr;
    U8  init_tlbn_order[16];
    U32 init_tlbn_mas1[16];
    U32 init_tlbn_mas2[16];
    U32 init_tlbn_mas3[16];
    U32 init_mas4;
    U32 init_mas6;
    U32 init_syncr;

    /* Code size */
    U32 code_size;

    /* Software Part Number 
     * nnL-xxxxxx Iss. y
     *     nn = group id number
     *      L = group letter
     * xxxxxx = part id number
     *      y = issue number
     * e.g.: 36T-123456 Iss. 2
     */
    U16 part_issue;  /* Because part_issue is a U16, it needs to be placed here to avoid compiler silent padding*/
    U8  part_group;
    U8  part_letter;
    U32 part_id;
    
    /* Location of next associated header (e.g. calibration header) */
    U32 next_header_ptr;

    /* Padding up to 1K */
    U8  pad[236];

    /* Checksum table - takes the header up to 1K (192 bytes in size)*/
    PHDR_CHKSUM_REGION_T chksum_table[PHDR_MAX_CHKSUM_BLOCKS];
}
PHDR_HEADER_T;

/********* Global Prototypes *********/

/* None */

/********* Global Variables *********/

/* None */

#endif /* PHDR_H */


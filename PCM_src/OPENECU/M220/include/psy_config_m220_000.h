/*
 *****************************************************************************
 *
 *  Project:        OpenECU
 *  Description:    I/O configuration for the M220-000 target.
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

#ifndef PSY_CONFIG_M220_000_H
#define PSY_CONFIG_M220_000_H

/****************************************************************************/
/* Software configuration                                                   */
/****************************************************************************/

/* Support ADC inputs.
 */
#define CFG_FEAT_ADC_INPUT

/* Support QADC A ADC hardware.
 */
#define CFG_FEAT_ADC_QADC_A

/* Support basic angular/engine functionality.
 */
#define CFG_FEAT_ANGULAR

/* Support extended angular/engine functionality.
 */
#define CFG_FEAT_ANGULAR_EXT

/* Support angular A/D sampling (extended).
 */
#define CFG_FEAT_ANGULAR_AD_EXT

/* Support crank decoding.
 */
#define CFG_FEAT_ANGULAR_CRANK

/* Support crank decoding (extended).
 */
#define CFG_FEAT_ANGULAR_CRANK_EXT

/* Support cam decoding.
 */
#define CFG_FEAT_ANGULAR_CAM

/* Support cam decoding.
 */
#define CFG_FEAT_ANGULAR_CAM_EXT

/* Support injector configuration.
 */
#define CFG_FEAT_ANGULAR_INJ

/* Support injector configuration (extended).
 */
#define CFG_FEAT_ANGULAR_INJ_EXT

/* Support direct injections.
 */
#define CFG_FEAT_ANGULAR_INJ_DI

/* Support direct injections.
 */
#define CFG_FEAT_ANGULAR_INJ_PI

/* Support spark functionality.
 */
#define CFG_FEAT_ANGULAR_SPARK

/* Support CAN Calibration Protocol (CCP).
 */
#define CFG_FEAT_CCP

/* Support CAN Calibration Protocol Security.
 */
#define CFG_FEAT_CCP_SECURITY

/* Support calibration verification number.
 */
#define CFG_FEAT_CVN

/* Support digital inputs.
 */
#define CFG_FEAT_DIG_IN

/* Support GPIO A digital input hardware.
 */
#define CFG_FEAT_DIG_IN_GPIO_A

/* Support MUC A digital input hardware.
 */
#define CFG_FEAT_DIG_IN_MUC_A

/* Support SPI digital input hardware.
 */
#define CFG_FEAT_DIG_IN_SPI

/* Support TPU A digital input hardware.
 */
#define CFG_FEAT_DIG_IN_TPU_A

/* Support digital outputs.
 */
#define CFG_FEAT_DIG_OUT

/* Support GPIO A digital output hardware.
 */
#define CFG_FEAT_DIG_OUT_GPIO_A

/* Support MUC A digital output hardware.
 */
#define CFG_FEAT_DIG_OUT_MUC_A

/* Support TPU A digital output hardware.
 */
#define CFG_FEAT_DIG_OUT_TPU_A

/* Support DTCs.
 */
#define CFG_FEAT_DTCS

/* Support FEPS reprogramming.
 */
#define CFG_FEAT_FEPS

/* Support flash code generation.
 */
#define CFG_FEAT_FLASH_CODE

/* Support frequency inputs.
 */
#define CFG_FEAT_FREQ_IN

/* Support MUC A frequency input hardware.
 */
#define CFG_FEAT_FREQ_IN_MUC_A

/* Support TPU A frequency input hardware.
 */
#define CFG_FEAT_FREQ_IN_TPU_A

/* Support H-bridge A output hardware.
 */
#define CFG_FEAT_HBRIDGE_A

/* Support H-bridge outputs.
 */
#define CFG_FEAT_HBRIDGE_OUT

/* Support inhibiting reprogramming from the application.
 */
#define CFG_FEAT_INHIBIT_PROGRAMMING

/* Support facility to configure different memory allocations.
 */
#define CFG_FEAT_MEMORY_CONFIGURATION

/* Support over-current trip reset with no diagnostic output.
 */
#define CFG_FEAT_OC_TRIP_RESET_NO_DIAG

/* Support over-current trip reset.
 */
#define CFG_FEAT_OVER_CURRENT_TRIP_RESET

/* Support PCP feature.
 */
#define CFG_FEAT_PCP

/* Support PCX feature.
 */
#define CFG_FEAT_PCX

/* Support PFC feature.
 */
#define CFG_FEAT_PFC

/* Support PFF feature.
 */
#define CFG_FEAT_PFF

/* Support PFS feature.
 */
#define CFG_FEAT_PFS

/* Support PIDs (Parameter Identifiers) as defined in J1979, Keyword Protocol 2000 (KWP) or ISO-15765.
 */
#define CFG_FEAT_PIDS

/* Support ISO-15765-2 transport protocol feature.
 */
#define CFG_FEAT_PISO

/* Support J1939 transport protocol feature.
 */
#define CFG_FEAT_PJ1939

/* Support extra J1939 OBD services.
 */
#define CFG_FEAT_PJ1939_OBD

/* Support PNV feature.
 */
#define CFG_FEAT_PNV

/* Support PPR feature.
 */
#define CFG_FEAT_PPR

/* Support PRG feature.
 */
#define CFG_FEAT_PRG

/* Support PWM inputs.
 */
#define CFG_FEAT_PWM_IN

/* Support TPU A PWM input hardware.
 */
#define CFG_FEAT_PWM_IN_TPU_A

/* Support PWM outputs.
 */
#define CFG_FEAT_PWM_OUT

/* Support MIOS A PWM output hardware.
 */
#define CFG_FEAT_PWM_OUT_MIOS_A

/* Support TPU A PWM output hardware.
 */
#define CFG_FEAT_PWM_OUT_TPU_A

/* Support SPI hardware.
 */
#define CFG_FEAT_SPI

/* Specify the Freescale MPC55xx processor family.
 */
#define CFG_FEAT_UC_FAMILY_MPC55XX

/* Specify the Freescale MPC5534 processor.
 */
#define CFG_FEAT_UC_MPC5534

/* Support software watchdog.
 */
#define CFG_FEAT_WATCHDOG

#endif

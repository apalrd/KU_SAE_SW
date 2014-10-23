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
 *                  at Tue Mar 18 11:50:32 2014 (local time).
 *                  Do not modify.
 *
 *****************************************************************************
 */

#ifndef PIO_M220_000_H
#define PIO_M220_000_H

/****************************************************************************/
/* I/O ranges, scales and other data                                        */
/****************************************************************************/

/* Definition of DTC types supported by this target.
 */
#define PIO_TYPE_J1939_DTC                       (PDTC_J1939_TYPE)

/* The external crystal clock rate in MHz.
 */
#define PIO_RATE_CRYSTAL_FREQ_MHZ                (8)

/* The default system processor clock rate in MHz.
 */
#define PIO_RATE_DEFAULT_SYS_CLK_MHZ             (12)

/* The system processor clock rate in MHz.
 */
#define PIO_RATE_SYS_CLK_MHZ                     (80)

/* Frequency input configuration and count parameter values for this target.
 */
#define PIO_CONFIG_FIN                           (3)
#define PIO_COUNT_FIN                            (1)

/* Minimum and maximum timeout boundary for frequency inputs (in Hz).
 */
#define PIO_RATE_FIN_MIN_HZ                      (0.5F)
#define PIO_RATE_FIN_MAX_HZ                      (10000.0F)

/* Minimum and maximum timeout boundary for PWM inputs (in Hz).
 */
#define PIO_RATE_PWMI_MIN_HZ                     (0.5F)
#define PIO_RATE_PWMI_MAX_HZ                     (10000.0F)

/* Minimum and maximum frequency for PWM outputs (in Hz).
 */
#define PIO_RATE_POT_MIN_HZ                      (0.5F)
#define PIO_RATE_POT_MAX_HZ                      (pioc_rate_pot_max_hz) /* default: 10000.0 */
#define PIO_TIME_POT_OFFSET_MIN_MS               (0)
#define PIO_TIME_POT_OFFSET_MAX_MS               (2000)

/* Minimum and maximum frequency for PWM outputs (in Hz).
 */
#define PIO_RATE_POT_SLOW_CLK_MIN_HZ             (0.1F)
#define PIO_RATE_POT_SLOW_CLK_MAX_HZ             (40.0F)

/* Minimum and maximum frequency for H-bridge outputs (in Hz).
 */
#define PIO_RATE_HBOT_FREQ_MIN_HZ                (0.5F)
#define PIO_RATE_HBOT_FREQ_MAX_HZ                (10000.0F)

/* Range of engine cylinders this target can address.
 */
#define PIO_ANG_MIN_CYLINDERS                    (1)
#define PIO_ANG_MAX_CYLINDERS                    (6)

/* Default crank teeth edge for this ECU.
 */
#define PIO_CRANK_TOOTH_EDGE_ECU_DEFAULT         (PIO_CRANK_TOOTH_EDGE_RISING)

/* Range of teeth (physical + missing) for a 'missing teeth grouped' crank wheel.
 */
#define PIO_CRANK_TEETH_MIN                      (12)
#define PIO_CRANK_TEETH_MAX                      (60)

/* Range of missing teeth for a 'missing teeth grouped' crank wheel.
 */
#define PIO_CRANK_MISSING_MIN                    (1)
#define PIO_CRANK_MISSING_MAX                    (3)

/* Range of teeth for a cam wheel.
 */
#define PIO_CAM_TEETH_MIN                        (1)
#define PIO_CAM_TEETH_MAX                        (8)

/* The maximum number of injection pulses supported per-cylinder.
 */
#define PIO_ANG_INJECTOR_MAX_PULSES              (6)

/* The maximum size of the fuel duration axis on the injection duration compensation map.
 */
#define PIO_ANG_INJECTOR_DUR_MAP_VOL_AXIS_SZ     (10)

/* The maximum size of the fuel-rail pressure axis on the injection duration compensation map.
 */
#define PIO_ANG_INJECTOR_DUR_MAP_FRP_AXIS_SZ     (10)
#define PIO_ANG_MAX_INJECTORS                    (2)

/* Range of angular A/D samples this target can process.
 */
#define PIO_ANG_MIN_AD_SAMPLES                   (1)
#define PIO_ANG_MAX_AD_SAMPLES                   (8)

/* Calibration references
 */
extern volatile const F32 pioc_rate_pot_max_hz;

/** This enumeration declares the different types of DTC available. These types can be ORd together, for example if one DTC is reported over both J1939 and ISO protocols. The ORd case is listed explicitly so that the menu item in Simulink can be resolved correctly, but need never be used in the source code.
 */
typedef PSY_PACKED enum
{
    /** No DTC (e.g. empty entry)
     */
    PIO_DTC_NONE                   = 0,

    /** J1939 DTC
     */
    PIO_DTC_J1939                  = 1,

    /** ISO DTC
     */
    PIO_DTC_ISO                    = 2,

    /** J1939 or ISO DTC
     */
    PIO_DTC_J1939_ISO              = 3
}
PIO_DTC_TYPE_T;

/** This enumeration declares the different types of DTC available. These types can be ANDd together, for example if one DTC is reported over both J1939 and ISO protocols.
 */
typedef PSY_PACKED enum
{
    /** J1939 DTC
     */
    PIO_DTC_AND_J1939              = 1,

    /** ISO DTC
     */
    PIO_DTC_AND_ISO                = 2,

    /** J1939 and ISO DTC
     */
    PIO_DTC_AND_J1939_ISO          = 3
}
PIO_DTC_TYPE_AND_T;

/** This enumeration declares the different Emission related severity levels for DTCs.
 */
typedef PSY_PACKED enum
{
    /** None
     */
    PIO_ESEV_NONE                  = 0,

    /** C
     */
    PIO_ESEV_C                     = 1,

    /** B2
     */
    PIO_ESEV_B2                    = 2,

    /** B1
     */
    PIO_ESEV_B1                    = 3,

    /** A
     */
    PIO_ESEV_A                     = 4
}
PIO_EMISSION_SEV_TYPE_T;

/** This enumeration declares the different UDS $19 service severity levels for DTCs.
 */
typedef PSY_PACKED enum
{
    /** noSeverityAvailable
     */
    PIO_UDS_SEV_NONE               = 0,

    /** maintenanceOnly
     */
    PIO_UDS_SEV_MAINT_ONLY         = 32,

    /** checkAtNextHalt
     */
    PIO_UDS_SEV_NEXT_HALT          = 64,

    /** checkImmediately
     */
    PIO_UDS_SEV_CHECK_IMM          = 128
}
PIO_DTC_UDS_SEV_T;

/** This enumeration declares the different types of DTC lamp state available.
 *
 * \ingroup c_extdiag_interface
 */
typedef PSY_PACKED enum
{
    /** Slow Flash
     */
    PIO_DTC_LAMP_SLOW_FLASH        = 0,

    /** Fast Flash
     */
    PIO_DTC_LAMP_FAST_FLASH        = 1,

    /** Continuously On
     */
    PIO_DTC_LAMP_ON                = 2,

    /** No Effect
     */
    PIO_DTC_LAMP_OFF               = 3
}
PIO_DTC_LAMP_STATES_T;

/** This enumeration declares the different states for DTCs.
 */
typedef PSY_PACKED enum
{
    /** Clear
     */
    PIO_STATE_CLEAR                = 0,

    /** Active
     */
    PIO_STATE_ACTIVE               = 1,

    /** Previously Active
     */
    PIO_STATE_PREVIOUSLY_ACTIVE    = 2,

    /** Pending
     */
    PIO_STATE_PENDING              = 3
}
PIO_DTC_STATE_T;

/** This enumeration declares the type comparison options for DTCs.
 */
typedef PSY_PACKED enum
{
    /** Any
     */
    PIO_TYPE_DC                    = 0,

    /** Contains type
     */
    PIO_TYPE_CT                    = 1
}
PIO_DTC_TYPE_COMPARATOR_T;

/** This enumeration declares the emissions severity comparison options for DTCs.
 */
typedef PSY_PACKED enum
{
    /** Any
     */
    PIO_ESEV_DC                    = 0,

    /** Equals
     */
    PIO_ESEV_EQ                    = 1,

    /** Not equal to
     */
    PIO_ESEV_NE                    = 2,

    /** Less than
     */
    PIO_ESEV_LT                    = 3,

    /** Less than or equal to
     */
    PIO_ESEV_LTE                   = 4,

    /** Greater than
     */
    PIO_ESEV_GT                    = 5,

    /** Greater than or equal to
     */
    PIO_ESEV_GTE                   = 6
}
PIO_DTC_ESEV_COMPARATOR_T;

/** This enumeration declares the state comparison options for DTCs.
 */
typedef PSY_PACKED enum
{
    /** Any
     */
    PIO_STATE_DC                   = 0,

    /** Equals
     */
    PIO_STATE_EQ                   = 1,

    /** Not equal to
     */
    PIO_STATE_NE                   = 2
}
PIO_DTC_STATE_COMPARATOR_T;

/** Diagnostic service mode.
 */
typedef PSY_PACKED enum
{
    /** Standard PIDs
     */
    PIO_MODE_01,

    /** Custom PIDs
     */
    PIO_MODE_22
}
PIO_SERVICE_MODE_T;

/** Data types supported as outputs from scaling block
 */
typedef PSY_PACKED enum
{
    /** uint8
     */
    PIO_PPID_UINT8,

    /** uint16
     */
    PIO_PPID_UINT16,

    /** uint32
     */
    PIO_PPID_UINT32
}
PIO_SCALING_OUT_DATA_TYPE_T;

/** This enumeration declares the different types of Infotypes available as defined by the J1979 protocol (SEP2010).
 */
typedef PSY_PACKED enum
{
    /** $02 Vehicle Identification Number
     */
    PIO_ASCII_INFOTYPE_VIN         = 2,

    /** $04 Calibration Identification
     */
    PIO_ASCII_INFOTYPE_CALID       = 4,

    /** $06 Calibration Verification Number
     */
    PIO_INFOTYPE_CVN               = 6,

    /** $0A ECUNAME
     */
    PIO_ASCII_INFOTYPE_ECUNAME     = 10,

    /** $0B In-use Performance Tracking
     */
    PIO_INFOTYPE_IPT_DIESEL        = 11,

    /** $0D Engine Serial Number
     */
    PIO_ASCII_INFOTYPE_ESN         = 13,

    /** $0F Exhaust Regulation Or Type Approval Number
     */
    PIO_ASCII_INFOTYPE_EROTAN      = 15
}
PIO_INFOTYPE_T;

/** This enumeration declares the different number of data items (NODI), related to in-use performance tracking (IPT), which are reported over service 0x09 of J1979. Currently only IPT $0B (diesel) is supported
 */
typedef PSY_PACKED enum
{
    /** 16 (MY2010 - Compression Ignition)
     */
    PIO_IPT_DIESEL_NODI_2010MY     = 16,

    /** 18 (MY2013 - Compression Ignition)
     */
    PIO_IPT_DIESEL_NODI_2013MY     = 18
}
PIO_INFOTYPE_IPT_NODI_T;

/** Possible In-Use Performance Ratio monitor groups that this  target supports.
 */
typedef PSY_PACKED enum
{
    /** Catalyst Monitor Bank 1
     */
    PIO_CAT_BANK1_MON              = 1,

    /** Catalyst Monitor Bank 2
     */
    PIO_CAT_BANK2_MON              = 2,

    /** O2 Sensor Monitor Bank 1
     */
    PIO_O2S_BANK1_MON              = 3,

    /** O2 Sensor Monitor Bank 2
     */
    PIO_O2S_BANK2_MON              = 4,

    /** EGR and/or VVT Monitor
     */
    PIO_EGR_MON                    = 5,

    /** AIR Monitor
     */
    PIO_AIR_MON                    = 6,

    /** EVAP Monitor
     */
    PIO_EVAP_MON                   = 7,

    /** Secondary O2 Sensor Monitor Bank 1
     */
    PIO_SO2S_BANK1_MON             = 8,

    /** Secondary O2 Sensor Monitor Bank 2
     */
    PIO_SO2S_BANK2_MON             = 9,

    /** NMHC Catalyst Monitor
     */
    PIO_HCCAT_MON                  = 10,

    /** NOx/SCR Catalyst Monitor
     */
    PIO_NCAT_MON                   = 11,

    /** NOx Adsorber Monitor
     */
    PIO_NADS_MON                   = 12,

    /** PM Filter Monitor
     */
    PIO_PM_MON                     = 13,

    /** Exhaust Gas Sensor Monitor
     */
    PIO_EGS_MON                    = 14,

    /** Boost Pressure Monitor
     */
    PIO_BP_MON                     = 15,

    /** Fuel Monitor
     */
    PIO_FUEL_MON                   = 16,

    /** Other
     */
    PIO_OTHER_MON                  = 255
}
PIO_MONITOR_GROUP_T;

/** This enumeration declares the different NTE control areas.
 */
typedef PSY_PACKED enum
{
    /** NOx NTE area
     */
    PIO_NOX_NTE_AREA               = 0,

    /** NOx NTE carve out area
     */
    PIO_NOX_NTE_CARVE_OUT_AREA     = 1,

    /** NOx NTE deficiency area
     */
    PIO_NOX_NTE_DEFICIENCY_AREA    = 2,

    /** PM NTE area
     */
    PIO_PM_NTE_AREA                = 3,

    /** PM NTE carve out area
     */
    PIO_PM_NTE_CARVE_OUT_AREA      = 4,

    /** PM NTE deficiency area
     */
    PIO_PM_NTE_DEFICIENCY_AREA     = 5
}
PIO_NTE_CNTRL_AREA_T;

/** This enumeration declares the overrides available for J1979 service $03 responses
 */
typedef PSY_PACKED enum
{
    /** No override
     */
    PIO_SERVICE_03_NO_OVERRIDE     = 0,

    /** Transmit Active and Previously Active DTCs
     */
    PIO_SERVICE_03_ACTIVE_PREV_ACTIVE = 1
}
PIO_SERVICE_03_OVERRIDE_OPTIONS_T;

/** This enumeration declares the overrides available for J1979 service $07 responses
 */
typedef PSY_PACKED enum
{
    /** No override
     */
    PIO_SERVICE_07_NO_OVERRIDE     = 0,

    /** Transmit Pending and Active DTCs
     */
    PIO_SERVICE_07_PENDING_ACTIVE  = 1
}
PIO_SERVICE_07_OVERRIDE_OPTIONS_T;

/** This enumeration declares the overrides available for J1979 service $0A responses
 */
typedef PSY_PACKED enum
{
    /** No override
     */
    PIO_SERVICE_0A_NO_OVERRIDE     = 0,

    /** Transmit Active and Previously Active DTCs
     */
    PIO_SERVICE_0A_ACTIVE_PREV_ACTIVE = 1
}
PIO_SERVICE_0A_OVERRIDE_OPTIONS_T;

/** This enumeration declares the options available for services which can be restricted by seed-key security
 */
typedef PSY_PACKED enum
{
    /** Never allowed
     */
    PIO_NEVER_ALLOWED              = 0,

    /** Allowed without security
     */
    PIO_ALWAYS_ALLOWED             = 1,

    /** Allowed if any security level attained
     */
    PIO_ANY_LEVEL                  = 2,

    /** Allowed if specified security level(s) attained
     */
    PIO_SPECIFIC_LEVELS            = 3
}
PIO_PDG_SECURED_SERVICE_OPTIONS_T;

/** Definition of CAN baud rates supported by this target (in kBps).
 */
typedef PSY_PACKED enum
{
    /** 33.333 kBps
     */
    PIO_CBAUD_33_333_KBPS          = 33,

    /** 50 kBps
     */
    PIO_CBAUD_50_KBPS              = 50,

    /** 62.5 kBps
     */
    PIO_CBAUD_62_5_KBPS            = 62,

    /** 83.333 kBps
     */
    PIO_CBAUD_83_333_KBPS          = 83,

    /** 100 kBps
     */
    PIO_CBAUD_100_KBPS             = 100,

    /** 125 kBps
     */
    PIO_CBAUD_125_KBPS             = 125,

    /** 250 kBps
     */
    PIO_CBAUD_250_KBPS             = 250,

    /** 500 kBps
     */
    PIO_CBAUD_500_KBPS             = 500,

    /** 1000 kBps
     */
    PIO_CBAUD_1000_KBPS            = 1000
}
PIO_CAN_BAUD_RATE_T;

/** This enumeration declares the different memory allocation configurations available.
 */
typedef PSY_PACKED enum
{
    /** Configuration A
     */
    PIO_MEMORY_CONFIG_A            = 0,

    /** Configuration B
     */
    PIO_MEMORY_CONFIG_B            = 1,

    /** Configuration C
     */
    PIO_MEMORY_CONFIG_C            = 2,

    /** Configuration D
     */
    PIO_MEMORY_CONFIG_D            = 3
}
PIO_MEMORY_CONFIG_T;

/** Configurable PWM clock selection for PWM outputs.
 */
typedef PSY_PACKED enum
{
    /** Slow Clock (For signals with range 0.1Hz to 40Hz)
     */
    PIO_CFG_PWM_CLOCK_SELECT_SLOW,

    /** Fast Clock (For signals with range 0.5Hz to 10000 Hz)
     */
    PIO_CFG_PWM_CLOCK_SELECT_FAST
}
PIO_CFG_PWM_CLOCK_SELECT_T;

/** Possible H-Bridge modes this target supports.
 */
typedef PSY_PACKED enum
{
    /** No drive
     */
    PIO_HBRIDGE_MODE_NO_DRIVE,

    /** Brake
     */
    PIO_HBRIDGE_MODE_BRAKE,

    /** Forward
     */
    PIO_HBRIDGE_MODE_FORWARD,

    /** Reverse
     */
    PIO_HBRIDGE_MODE_REVERSE
}
PIO_HBRIDGE_MODE_T;

/** Different engine types supported by this target.
 */
typedef PSY_PACKED enum
{
    /** Diesel
     */
    PIO_ENGINE_TYPE_DIESEL,

    /** Diesel with spark
     */
    PIO_ENGINE_TYPE_DIESEL_WITH_SPARK,

    /** Gasoline (port injection)
     */
    PIO_ENGINE_TYPE_GASOLINE_PORT_INJ
}
PIO_ENGINE_TYPE_T;

/** Different engine cycle types supported by this target.
 */
typedef PSY_PACKED enum
{
    /** 4-stroke
     */
    PIO_ENGINE_CYCLE_TYPE_FOUR_STROKE,

    /** 2-stroke
     */
    PIO_ENGINE_CYCLE_TYPE_TWO_STROKE
}
PIO_ENGINE_CYCLE_TYPE_T;

/** Possible crank inputs available for use.
 */
typedef PSY_PACKED enum
{
    /** Primary
     */
    PIO_CRANK_WHEEL_PRIMARY
}
PIO_CRANK_WHEEL_T;

/** Possible crank wheel pattern synchronisation schemes this target implements.
 */
typedef PSY_PACKED enum
{
    /** Tooth-Missing-Tooth
     */
    PIO_CRANK_WHEEL_SYNC_TMT
}
PIO_CRANK_WHEEL_SYNC_T;

/** Possible crank teeth edge types.
 */
typedef PSY_PACKED enum
{
    /** Default
     */
    PIO_CRANK_TOOTH_EDGE_DEFAULT,

    /** Rising
     */
    PIO_CRANK_TOOTH_EDGE_RISING,

    /** Falling
     */
    PIO_CRANK_TOOTH_EDGE_FALLING
}
PIO_CRANK_TOOTH_EDGE_T;

/** Possible cam inputs available for use.
 */
typedef PSY_PACKED enum
{
    /** Primary
     */
    PIO_CAM_WHEEL_PRIMARY
}
PIO_CAM_WHEEL_T;

/** Possible cam teeth edge types to capture angle.
 */
typedef PSY_PACKED enum
{
    /** Rising
     */
    PIO_CAM_TOOTH_EDGE_RISING,

    /** Falling
     */
    PIO_CAM_TOOTH_EDGE_FALLING,

    /** Rising and falling
     */
    PIO_CAM_TOOTH_EDGE_BOTH
}
PIO_CAM_CAP_EDGE_T;

/** Possible spark schemes that this target supports.
 */
typedef PSY_PACKED enum
{
    /** Coil on plug
     */
    PIO_SPARK_TYPE_COIL_ON_PLUG
}
PIO_SPARK_TYPE_T;

/** Possible injector drive schemes that this target supports.
 */
typedef PSY_PACKED enum
{
    /** Saturating
     */
    PIO_INJECTOR_DRIVE_SATURATE
}
PIO_INJECTOR_DRIVE_T;

/** Injector delivery type
 */
typedef PSY_PACKED enum
{
    /** Single Pulse (GPI)
     */
    PIO_INJECTOR_PULSE_TYPE_GPI,

    /** Multiple Pulse (DI)
     */
    PIO_INJECTOR_PULSE_TYPE_DI,

    /** 
     */
    PIO_INJECTOR_PULSE_TYPE_IMPLICIT,

    /** 
     */
    PIO_INJECTOR_PULSE_TYPE_INVALID
}
PIO_INJECTOR_PULSE_TYPE_T;

/** Direct-injection pulse duration specification mode
 */
typedef PSY_PACKED enum
{
    /** Pluse schedule durations are computed from volume request using just-in-time fuel rail pressure measurements.
     */
    PIO_INJDI_DURATION_MODE_VOLUME,

    /** Pulse schedule durations are specified directly by the application.
     */
    PIO_INJDI_DURATION_MODE_TIME
}
PIO_INJDI_DURATION_MODE_T;

/** Possible angular A/D sampling groups this target supports.
 */
typedef PSY_PACKED enum
{
    /** Group 1
     */
    PIO_AD_GROUP_1,

    /** Group 2
     */
    PIO_AD_GROUP_2
}
PIO_AD_GROUP_T;

/****************************************************************************/
/* CAN buses                                                                */
/****************************************************************************/

#define PIO_CAN_A23_A24                          ((PCX_LCHAN_T)1)    

#define PIO_CAN_A28_A43                          ((PCX_LCHAN_T)0)    

/****************************************************************************/
/* LIN buses                                                                */
/****************************************************************************/

/* None */

/****************************************************************************/
/* RS232 links                                                              */
/****************************************************************************/

/* None */

/****************************************************************************/
/* Analogue inputs                                                          */
/****************************************************************************/

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_A1_MONITOR_V                     ((PAX_LCHAN_T)29)   

/* Function: Voltage monitor
 * Range:    0V to 40V
 * Notes:    Switched power supply voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=Vm*8
 */
#define PIO_AIN_A2_VPWR                          ((PAX_LCHAN_T)32)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_A3                               ((PAX_LCHAN_T)6)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_A5                               ((PAX_LCHAN_T)7)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_A7                               ((PAX_LCHAN_T)8)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_A10                              ((PAX_LCHAN_T)9)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_A12                              ((PAX_LCHAN_T)10)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_A13                              ((PAX_LCHAN_T)11)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_A14                              ((PAX_LCHAN_T)12)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_A15                              ((PAX_LCHAN_T)41)   

/* Function: Current monitor
 * Range:    0A to 15.625A
 * Notes:    Digital output current monitor. 12-bit unsigned conversion. For currents below 0.5A the relationship is non-linear (see the 'Digital output' sections for more information).
 */
#define PIO_AIN_A16_MONITOR_C                    ((PAX_LCHAN_T)17)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_A16_MONITOR_V                    ((PAX_LCHAN_T)30)   

/* Function: Current monitor
 * Range:    -5A to 5A
 * Notes:    Digital output current monitor (if fitted). 12-bit unsigned conversion.  To convert voltage (V) to current (I) use the equation, I=(V-2.5)/0.185
 */
#define PIO_AIN_A17_MONITOR_C                    ((PAX_LCHAN_T)38)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_A17_MONITOR_V                    ((PAX_LCHAN_T)23)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_A18                              ((PAX_LCHAN_T)49)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_A19                              ((PAX_LCHAN_T)57)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_A20                              ((PAX_LCHAN_T)65)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_A21                              ((PAX_LCHAN_T)13)   

/* Function: Voltage monitor
 * Range:    0V to 5V
 * Notes:    Sensor supply voltage monitor. 12-bit unsigned conversion.
 */
#define PIO_AIN_A25_MONITOR_V                    ((PAX_LCHAN_T)14)   

/* Function: Current monitor
 * Range:    -5A to 5A
 * Notes:    Digital output current monitor (if fitted). 12-bit unsigned conversion.  To convert voltage (V) to current (I) use the equation, I=(V-2.5)/0.185
 */
#define PIO_AIN_A29_MONITOR_C                    ((PAX_LCHAN_T)39)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_A29_MONITOR_V                    ((PAX_LCHAN_T)27)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_A30_MONITOR_V                    ((PAX_LCHAN_T)28)   

/* Function: Current monitor
 * Range:    -5A to 5A
 * Notes:    Digital output current monitor (if fitted). 12-bit unsigned conversion.  To convert voltage (V) to current (I) use the equation, I=(V-2.5)/0.185
 */
#define PIO_AIN_A32_MONITOR_C                    ((PAX_LCHAN_T)40)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_A32_MONITOR_V                    ((PAX_LCHAN_T)25)   

/* Function: Current monitor
 * Range:    -5A to 5A
 * Notes:    Digital output current monitor (if fitted). 12-bit unsigned conversion.  To convert voltage (V) to current (I) use the equation, I=(V-2.5)/0.185
 */
#define PIO_AIN_A33_MONITOR_C                    ((PAX_LCHAN_T)36)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_A33_MONITOR_V                    ((PAX_LCHAN_T)20)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_A34_MONITOR_V                    ((PAX_LCHAN_T)21)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_A35_MONITOR_V                    ((PAX_LCHAN_T)22)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_A36_MONITOR_V                    ((PAX_LCHAN_T)18)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_A37_MONITOR_V                    ((PAX_LCHAN_T)19)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_A44_MONITOR_V                    ((PAX_LCHAN_T)24)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_A45_MONITOR_V                    ((PAX_LCHAN_T)31)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_A46_MONITOR_V                    ((PAX_LCHAN_T)26)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    Internal 3.3V supply monitor. 12-bit unsigned conversion.
 */
#define PIO_AIN_INT_3_3V                         ((PAX_LCHAN_T)35)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    5V reference for analogue input conversions. 12-bit unsigned conversion.
 */
#define PIO_AIN_INT_VRH                          ((PAX_LCHAN_T)0)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    1.25V reference for analogue input conversions. 12-bit unsigned conversion.
 */
#define PIO_AIN_INT_VRH_VRL_25PC                 ((PAX_LCHAN_T)4)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    2.5V reference for analogue input conversions. Will read as 2.48V due to 20mV offset in processor implementation. 12-bit unsigned conversion.
 */
#define PIO_AIN_INT_VRH_VRL_50PC                 ((PAX_LCHAN_T)2)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    3.75V reference for analogue input conversions. 12-bit unsigned conversion.
 */
#define PIO_AIN_INT_VRH_VRL_75PC                 ((PAX_LCHAN_T)3)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    0V reference for analogue input conversions. 12-bit unsigned conversion.
 */
#define PIO_AIN_INT_VRL                          ((PAX_LCHAN_T)1)    

/****************************************************************************/
/* Analogue inputs (engine sync., group 1)                                  */
/****************************************************************************/

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_G1_A1_MONITOR_V                  ((PAX_LCHAN_T)20)   

/* Function: Voltage monitor
 * Range:    0V to 40V
 * Notes:    Switched power supply voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=Vm*8
 */
#define PIO_AIN_G1_A2_VPWR                       ((PAX_LCHAN_T)32)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_G1_A3                            ((PAX_LCHAN_T)6)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_G1_A5                            ((PAX_LCHAN_T)7)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_G1_A7                            ((PAX_LCHAN_T)8)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_G1_A10                           ((PAX_LCHAN_T)9)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_G1_A12                           ((PAX_LCHAN_T)10)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_G1_A13                           ((PAX_LCHAN_T)11)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_G1_A14                           ((PAX_LCHAN_T)12)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_G1_A15                           ((PAX_LCHAN_T)41)   

/* Function: Current monitor
 * Range:    0A to 15.625A
 * Notes:    Digital output current monitor. 12-bit unsigned conversion. For currents below 0.5A the relationship is non-linear (see the 'Digital output' sections for more information).
 */
#define PIO_AIN_G1_A16_MONITOR_C                 ((PAX_LCHAN_T)17)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_G1_A16_MONITOR_V                 ((PAX_LCHAN_T)30)   

/* Function: Current monitor
 * Range:    -5A to 5A
 * Notes:    Digital output current monitor (if fitted). 12-bit unsigned conversion.  To convert voltage (V) to current (I) use the equation, I=(V-2.5)/0.185
 */
#define PIO_AIN_G1_A17_MONITOR_C                 ((PAX_LCHAN_T)38)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_G1_A17_MONITOR_V                 ((PAX_LCHAN_T)23)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_G1_A18                           ((PAX_LCHAN_T)49)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_G1_A19                           ((PAX_LCHAN_T)57)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_G1_A20                           ((PAX_LCHAN_T)65)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_G1_A21                           ((PAX_LCHAN_T)13)   

/* Function: Voltage monitor
 * Range:    0V to 5V
 * Notes:    Sensor supply voltage monitor. 12-bit unsigned conversion.
 */
#define PIO_AIN_G1_A25_MONITOR_V                 ((PAX_LCHAN_T)14)   

/* Function: Current monitor
 * Range:    -5A to 5A
 * Notes:    Digital output current monitor (if fitted). 12-bit unsigned conversion.  To convert voltage (V) to current (I) use the equation, I=(V-2.5)/0.185
 */
#define PIO_AIN_G1_A29_MONITOR_C                 ((PAX_LCHAN_T)39)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_G1_A29_MONITOR_V                 ((PAX_LCHAN_T)27)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_G1_A30_MONITOR_V                 ((PAX_LCHAN_T)28)   

/* Function: Current monitor
 * Range:    -5A to 5A
 * Notes:    Digital output current monitor (if fitted). 12-bit unsigned conversion.  To convert voltage (V) to current (I) use the equation, I=(V-2.5)/0.185
 */
#define PIO_AIN_G1_A32_MONITOR_C                 ((PAX_LCHAN_T)40)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_G1_A32_MONITOR_V                 ((PAX_LCHAN_T)25)   

/* Function: Current monitor
 * Range:    -5A to 5A
 * Notes:    Digital output current monitor (if fitted). 12-bit unsigned conversion.  To convert voltage (V) to current (I) use the equation, I=(V-2.5)/0.185
 */
#define PIO_AIN_G1_A33_MONITOR_C                 ((PAX_LCHAN_T)36)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_G1_A33_MONITOR_V                 ((PAX_LCHAN_T)20)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_G1_A34_MONITOR_V                 ((PAX_LCHAN_T)21)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_G1_A35_MONITOR_V                 ((PAX_LCHAN_T)22)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_G1_A36_MONITOR_V                 ((PAX_LCHAN_T)18)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_G1_A37_MONITOR_V                 ((PAX_LCHAN_T)19)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_G1_A44_MONITOR_V                 ((PAX_LCHAN_T)24)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_G1_A46_MONITOR_V                 ((PAX_LCHAN_T)26)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    Internal 3.3V supply monitor. 12-bit unsigned conversion.
 */
#define PIO_AIN_G1_INT_3_3V                      ((PAX_LCHAN_T)35)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    5V reference for analogue input conversions. 12-bit unsigned conversion.
 */
#define PIO_AIN_G1_INT_VRH                       ((PAX_LCHAN_T)0)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    1.25V reference for analogue input conversions. 12-bit unsigned conversion.
 */
#define PIO_AIN_G1_INT_VRH_VRL_25PC              ((PAX_LCHAN_T)4)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    2.5V reference for analogue input conversions. Will read as 2.48V due to 20mV offset in processor implementation. 12-bit unsigned conversion.
 */
#define PIO_AIN_G1_INT_VRH_VRL_50PC              ((PAX_LCHAN_T)2)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    3.75V reference for analogue input conversions. 12-bit unsigned conversion.
 */
#define PIO_AIN_G1_INT_VRH_VRL_75PC              ((PAX_LCHAN_T)3)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    0V reference for analogue input conversions. 12-bit unsigned conversion.
 */
#define PIO_AIN_G1_INT_VRL                       ((PAX_LCHAN_T)1)    

/****************************************************************************/
/* Analogue inputs (engine sync., group 2)                                  */
/****************************************************************************/

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_G2_A1_MONITOR_V                  ((PAX_LCHAN_T)20)   

/* Function: Voltage monitor
 * Range:    0V to 40V
 * Notes:    Switched power supply voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=Vm*8
 */
#define PIO_AIN_G2_A2_VPWR                       ((PAX_LCHAN_T)32)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_G2_A3                            ((PAX_LCHAN_T)6)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_G2_A5                            ((PAX_LCHAN_T)7)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_G2_A7                            ((PAX_LCHAN_T)8)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_G2_A10                           ((PAX_LCHAN_T)9)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_G2_A12                           ((PAX_LCHAN_T)10)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_G2_A13                           ((PAX_LCHAN_T)11)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_G2_A14                           ((PAX_LCHAN_T)12)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_G2_A15                           ((PAX_LCHAN_T)41)   

/* Function: Current monitor
 * Range:    0A to 15.625A
 * Notes:    Digital output current monitor. 12-bit unsigned conversion. For currents below 0.5A the relationship is non-linear (see the 'Digital output' sections for more information).
 */
#define PIO_AIN_G2_A16_MONITOR_C                 ((PAX_LCHAN_T)17)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_G2_A16_MONITOR_V                 ((PAX_LCHAN_T)30)   

/* Function: Current monitor
 * Range:    -5A to 5A
 * Notes:    Digital output current monitor (if fitted). 12-bit unsigned conversion.  To convert voltage (V) to current (I) use the equation, I=(V-2.5)/0.185
 */
#define PIO_AIN_G2_A17_MONITOR_C                 ((PAX_LCHAN_T)38)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_G2_A17_MONITOR_V                 ((PAX_LCHAN_T)23)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_G2_A18                           ((PAX_LCHAN_T)49)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_G2_A19                           ((PAX_LCHAN_T)57)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_G2_A20                           ((PAX_LCHAN_T)65)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_G2_A21                           ((PAX_LCHAN_T)13)   

/* Function: Voltage monitor
 * Range:    0V to 5V
 * Notes:    Sensor supply voltage monitor. 12-bit unsigned conversion.
 */
#define PIO_AIN_G2_A25_MONITOR_V                 ((PAX_LCHAN_T)14)   

/* Function: Current monitor
 * Range:    -5A to 5A
 * Notes:    Digital output current monitor (if fitted). 12-bit unsigned conversion.  To convert voltage (V) to current (I) use the equation, I=(V-2.5)/0.185
 */
#define PIO_AIN_G2_A29_MONITOR_C                 ((PAX_LCHAN_T)39)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_G2_A29_MONITOR_V                 ((PAX_LCHAN_T)27)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_G2_A30_MONITOR_V                 ((PAX_LCHAN_T)28)   

/* Function: Current monitor
 * Range:    -5A to 5A
 * Notes:    Digital output current monitor (if fitted). 12-bit unsigned conversion.  To convert voltage (V) to current (I) use the equation, I=(V-2.5)/0.185
 */
#define PIO_AIN_G2_A32_MONITOR_C                 ((PAX_LCHAN_T)40)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_G2_A32_MONITOR_V                 ((PAX_LCHAN_T)25)   

/* Function: Current monitor
 * Range:    -5A to 5A
 * Notes:    Digital output current monitor (if fitted). 12-bit unsigned conversion.  To convert voltage (V) to current (I) use the equation, I=(V-2.5)/0.185
 */
#define PIO_AIN_G2_A33_MONITOR_C                 ((PAX_LCHAN_T)36)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_G2_A33_MONITOR_V                 ((PAX_LCHAN_T)20)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_G2_A34_MONITOR_V                 ((PAX_LCHAN_T)21)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_G2_A35_MONITOR_V                 ((PAX_LCHAN_T)22)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_G2_A36_MONITOR_V                 ((PAX_LCHAN_T)18)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_G2_A37_MONITOR_V                 ((PAX_LCHAN_T)19)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_G2_A44_MONITOR_V                 ((PAX_LCHAN_T)24)   

/* Function: Voltage monitor
 * Range:    -3.488V to 36.916V
 * Notes:    Digital output voltage monitor. 12-bit unsigned conversion. To convert measured voltage (Vm) to actual voltage (Va) use the equation, Va=(Vm-0.43169)*8.080808
 */
#define PIO_AIN_G2_A46_MONITOR_V                 ((PAX_LCHAN_T)26)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    Internal 3.3V supply monitor. 12-bit unsigned conversion.
 */
#define PIO_AIN_G2_INT_3_3V                      ((PAX_LCHAN_T)35)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    5V reference for analogue input conversions. 12-bit unsigned conversion.
 */
#define PIO_AIN_G2_INT_VRH                       ((PAX_LCHAN_T)0)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    1.25V reference for analogue input conversions. 12-bit unsigned conversion.
 */
#define PIO_AIN_G2_INT_VRH_VRL_25PC              ((PAX_LCHAN_T)4)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    2.5V reference for analogue input conversions. Will read as 2.48V due to 20mV offset in processor implementation. 12-bit unsigned conversion.
 */
#define PIO_AIN_G2_INT_VRH_VRL_50PC              ((PAX_LCHAN_T)2)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    3.75V reference for analogue input conversions. 12-bit unsigned conversion.
 */
#define PIO_AIN_G2_INT_VRH_VRL_75PC              ((PAX_LCHAN_T)3)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    0V reference for analogue input conversions. 12-bit unsigned conversion.
 */
#define PIO_AIN_G2_INT_VRL                       ((PAX_LCHAN_T)1)    

/****************************************************************************/
/* Analogue inputs (injector duration)                                      */
/****************************************************************************/

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_INJ_FBK_A3                       ((PAX_LCHAN_T)5)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_INJ_FBK_A5                       ((PAX_LCHAN_T)7)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_INJ_FBK_A7                       ((PAX_LCHAN_T)8)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_INJ_FBK_A10                      ((PAX_LCHAN_T)9)    

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_INJ_FBK_A12                      ((PAX_LCHAN_T)10)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_INJ_FBK_A13                      ((PAX_LCHAN_T)11)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_INJ_FBK_A14                      ((PAX_LCHAN_T)12)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_INJ_FBK_A15                      ((PAX_LCHAN_T)41)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_INJ_FBK_A18                      ((PAX_LCHAN_T)49)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_INJ_FBK_A19                      ((PAX_LCHAN_T)57)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_INJ_FBK_A20                      ((PAX_LCHAN_T)65)   

/* Function: Analogue
 * Range:    0V to 5V
 * Notes:    12-bit unsigned conversion.
 */
#define PIO_AIN_INJ_FBK_A21                      ((PAX_LCHAN_T)13)   

/****************************************************************************/
/* Cam-shaft inputs                                                         */
/****************************************************************************/

/* Function: Digital (Hall effect)
 * Range:    0V to VPWR
 * Notes:    Cam-shaft position sensor.
 */
#define PIO_CAIN_A11                             ((PDX_LCHAN_T)281)  

/****************************************************************************/
/* Crank-shaft inputs                                                       */
/****************************************************************************/

#define PIO_CRIN_A8_A9                           ((PDX_LCHAN_T)280)  

/****************************************************************************/
/* Digital inputs                                                           */
/****************************************************************************/

/* Function: Analogue (VRS single-ended)
 * Range:    TBD
 * Notes:    VRS input.
 */
#define PIO_DIN_A4                               ((PDX_LCHAN_T)265)  

/* Function: Analogue (VRS single-ended)
 * Range:    TBD
 * Notes:    VRS input.
 */
#define PIO_DIN_A6                               ((PDX_LCHAN_T)259)  

/* Function: Digital
 * Range:    0V to VPWR
 */
#define PIO_DIN_A11                              ((PDX_LCHAN_T)281)  

/* Function: Current trip monitor
 * Range:    0 or 1
 * Notes:    Digital output current trip.
 */
#define PIO_DIN_A16_MONITOR_CT                   ((PDX_LCHAN_T)303)  

/* Function: Digital
 * Range:    0V to VPWR
 */
#define PIO_DIN_A22                              ((PDX_LCHAN_T)298)  

/* Function: Digital
 * Range:    0V to VPWR
 * Notes:    Key position (ignition sense) input.
 */
#define PIO_DIN_A26                              ((PDX_LCHAN_T)101)  

/* Function: Digital
 * Range:    0 or 1
 * Notes:    H-bridge fault monitor. 0 indicates a fault, 1 indicates H-bridge ready for use.
 */
#define PIO_DIN_A30_A1_H_BRIDGE_READY            ((PDX_LCHAN_T)194)  

/* Function: Digital
 * Range:    0V to VPWR
 */
#define PIO_DIN_A38                              ((PDX_LCHAN_T)264)  

/* Function: Digital
 * Range:    0V to VPWR
 */
#define PIO_DIN_A39                              ((PDX_LCHAN_T)267)  

/* Function: Digital
 * Range:    0V to VPWR
 */
#define PIO_DIN_A42                              ((PDX_LCHAN_T)257)  

/* Function: Current trip monitor
 * Range:    0 or 1
 * Notes:    Digital input indicating current trip.
 */
#define PIO_DIN_A45_MONITOR_CT                   ((PDX_LCHAN_T)297)  

/* Function: Digital monitor
 * Range:    0 or 1
 * Notes:    Digital output state monitor.
 */
#define PIO_DIN_A45_MONITOR_D                    ((PDX_LCHAN_T)275)  

/****************************************************************************/
/* Frequency inputs                                                         */
/****************************************************************************/

#define PIO_FIN_A4                               ((PDX_LCHAN_T)265)  

#define PIO_FIN_A6                               ((PDX_LCHAN_T)259)  

#define PIO_FIN_A8_A9                            ((PDX_LCHAN_T)280)  

/* Function: Digital
 * Range:    0V to VPWR
 */
#define PIO_FIN_A11                              ((PDX_LCHAN_T)281)  

/* Function: Digital
 * Range:    0V to VPWR
 */
#define PIO_FIN_A22                              ((PDX_LCHAN_T)298)  

/* Function: Digital
 * Range:    0V to VPWR
 */
#define PIO_FIN_A38                              ((PDX_LCHAN_T)264)  

/* Function: Digital
 * Range:    0V to VPWR
 */
#define PIO_FIN_A39                              ((PDX_LCHAN_T)267)  

/* Function: Digital
 * Range:    0V to VPWR
 */
#define PIO_FIN_A42                              ((PDX_LCHAN_T)257)  

/****************************************************************************/
/* Knock inputs (analogue)                                                  */
/****************************************************************************/

/* None */

/****************************************************************************/
/* Knock inputs (digital)                                                   */
/****************************************************************************/

/* None */

/****************************************************************************/
/* Period inputs                                                            */
/****************************************************************************/

/* None */

/****************************************************************************/
/* PWM inputs                                                               */
/****************************************************************************/

#define PIO_PWIN_A8_A9                           ((PDX_LCHAN_T)280)  

/* Function: Digital
 * Range:    0V to VPWR
 */
#define PIO_PWIN_A11                             ((PDX_LCHAN_T)281)  

/* Function: Digital
 * Range:    0V to VPWR
 */
#define PIO_PWIN_A22                             ((PDX_LCHAN_T)298)  

/****************************************************************************/
/* Quadrature inputs                                                        */
/****************************************************************************/

/* None */

/****************************************************************************/
/* Quadrature (with frequency) inputs                                       */
/****************************************************************************/

/* None */

/****************************************************************************/
/* TLE4953 inputs                                                           */
/****************************************************************************/

/* None */

/****************************************************************************/
/* Constant current outputs                                                 */
/****************************************************************************/

/* None */

/****************************************************************************/
/* Digital outputs                                                          */
/****************************************************************************/

/* Function: Digital
 * Range:    15A
 */
#define PIO_DOT_A16                              ((PDX_LCHAN_T)290)  

/* Function: Digital
 * Range:    2A
 */
#define PIO_DOT_A17                              ((PDX_LCHAN_T)304)  

/* Function: Digital
 * Range:    0 or 1
 * Notes:    Set to 0 to enable the CAN-2 transceiver, set to 1 to disable.
 */
#define PIO_DOT_A23_A24_DISABLE_CAN              ((PDX_LCHAN_T)119)  

/* Function: Digital
 * Range:    0 or 1
 * Notes:    Sensor supply switch. Set to one to turn on the power supply and to zero to turn it off.
 */
#define PIO_DOT_A25_ENABLE_EXT_PSU1              ((PDX_LCHAN_T)191)  

/* Function: Digital
 * Range:    0 or 1
 * Notes:    Control power supply to ECU in conjunction with the key position (ignition sense) input. Set the output to 1 to enable power hold and 0 to disable it.
 */
#define PIO_DOT_A26_HOLD_PSU                     ((PDX_LCHAN_T)193)  

/* Function: Digital
 * Range:    0 or 1
 * Notes:    Set to 0 to enable the CAN-1 transceiver, set to 1 to disable.
 */
#define PIO_DOT_A28_A43_DISABLE_CAN              ((PDX_LCHAN_T)118)  

/* Function: Digital
 * Range:    2A
 */
#define PIO_DOT_A29                              ((PDX_LCHAN_T)306)  

/* Function: Digital
 * Range:    2A
 */
#define PIO_DOT_A32                              ((PDX_LCHAN_T)289)  

/* Function: Digital
 * Range:    2A
 */
#define PIO_DOT_A33                              ((PDX_LCHAN_T)279)  

/* Function: Digital
 * Range:    250mA
 */
#define PIO_DOT_A34                              ((PDX_LCHAN_T)277)  

/* Function: Digital
 * Range:    250mA
 */
#define PIO_DOT_A35                              ((PDX_LCHAN_T)286)  

/* Function: Digital
 * Range:    100mA
 */
#define PIO_DOT_A36                              ((PDX_LCHAN_T)299)  

/* Function: Digital
 * Range:    100mA
 */
#define PIO_DOT_A37                              ((PDX_LCHAN_T)287)  

/* Function: Digital
 * Range:    2A
 */
#define PIO_DOT_A44                              ((PDX_LCHAN_T)292)  

/* Function: Digital
 * Range:    15A
 */
#define PIO_DOT_A45                              ((PDX_LCHAN_T)295)  

/* Function: Digital
 * Range:    2A
 */
#define PIO_DOT_A46                              ((PDX_LCHAN_T)305)  

/****************************************************************************/
/* Fixed frequency PWM outputs                                              */
/****************************************************************************/

/* Function: Digital
 * Range:    15A
 */
#define PIO_FFPOT_A16                            ((PDX_LCHAN_T)290)  

/* Function: Digital
 * Range:    2A
 */
#define PIO_FFPOT_A17                            ((PDX_LCHAN_T)304)  

/* Function: Digital
 * Range:    2A
 */
#define PIO_FFPOT_A29                            ((PDX_LCHAN_T)306)  

/* Function: Digital
 * Range:    2A
 */
#define PIO_FFPOT_A32                            ((PDX_LCHAN_T)289)  

/* Function: Digital
 * Range:    2A
 */
#define PIO_FFPOT_A33                            ((PDX_LCHAN_T)279)  

/* Function: Digital
 * Range:    250mA
 */
#define PIO_FFPOT_A34                            ((PDX_LCHAN_T)277)  

/* Function: Digital
 * Range:    250mA
 */
#define PIO_FFPOT_A35                            ((PDX_LCHAN_T)286)  

/* Function: Digital
 * Range:    100mA
 */
#define PIO_FFPOT_A36                            ((PDX_LCHAN_T)299)  

/* Function: Digital
 * Range:    100mA
 */
#define PIO_FFPOT_A37                            ((PDX_LCHAN_T)287)  

/* Function: Digital
 * Range:    2A
 */
#define PIO_FFPOT_A44                            ((PDX_LCHAN_T)292)  

/* Function: Digital
 * Range:    15A
 */
#define PIO_FFPOT_A45                            ((PDX_LCHAN_T)295)  

/* Function: Digital
 * Range:    2A
 */
#define PIO_FFPOT_A46                            ((PDX_LCHAN_T)305)  

/****************************************************************************/
/* H-bridge outputs (grouped)                                               */
/****************************************************************************/

/* Function: Digital
 * Range:    5A
 */
#define PIO_HBOT_A30_A1                          ((PDX_LCHAN_HBRIDGE_T)0)

/****************************************************************************/
/* H-bridge outputs (single)                                                */
/****************************************************************************/

/* None */

/* None */

/****************************************************************************/
/* Ignition outputs                                                         */
/****************************************************************************/

/* Function: Digital
 * Range:    250mA
 * Notes:    Coil/spark (smart) driver.
 */
#define PIO_IGNOT_A35                            ((PDX_LCHAN_T)286)  

/* Function: Digital
 * Range:    100mA
 * Notes:    Coil/spark (smart) driver.
 */
#define PIO_IGNOT_A37                            ((PDX_LCHAN_T)287)  

/****************************************************************************/
/* Injector outputs (saturating)                                            */
/****************************************************************************/

/* Function: Digital (injector)
 * Range:    2A
 */
#define PIO_INJOT_A17                            ((PDX_LCHAN_T)304)  

/* Function: Digital (injector)
 * Range:    2A
 */
#define PIO_INJOT_A29                            ((PDX_LCHAN_T)306)  

/****************************************************************************/
/* Injector outputs (peak-and-hold)                                         */
/****************************************************************************/

/* None */

/****************************************************************************/
/* PWM outputs                                                              */
/****************************************************************************/

/* Function: Digital
 * Range:    15A
 */
#define PIO_POT_A16                              ((PDX_LCHAN_T)290)  

/* Function: Digital
 * Range:    2A
 */
#define PIO_POT_A17                              ((PDX_LCHAN_T)304)  

/* Function: Digital
 * Range:    2A
 */
#define PIO_POT_A29                              ((PDX_LCHAN_T)306)  

/* Function: Digital
 * Range:    2A
 */
#define PIO_POT_A32                              ((PDX_LCHAN_T)289)  

/* Function: Digital
 * Range:    2A
 */
#define PIO_POT_A33                              ((PDX_LCHAN_T)279)  

/* Function: Digital
 * Range:    250mA
 */
#define PIO_POT_A34                              ((PDX_LCHAN_T)277)  

/* Function: Digital
 * Range:    250mA
 */
#define PIO_POT_A35                              ((PDX_LCHAN_T)286)  

/* Function: Digital
 * Range:    100mA
 */
#define PIO_POT_A36                              ((PDX_LCHAN_T)299)  

/* Function: Digital
 * Range:    100mA
 */
#define PIO_POT_A37                              ((PDX_LCHAN_T)287)  

/* Function: Digital
 * Range:    2A
 */
#define PIO_POT_A44                              ((PDX_LCHAN_T)292)  

/* Function: Digital
 * Range:    15A
 */
#define PIO_POT_A45                              ((PDX_LCHAN_T)295)  

/* Function: Digital
 * Range:    2A
 */
#define PIO_POT_A46                              ((PDX_LCHAN_T)305)  

/****************************************************************************/
/* Stepped outputs                                                          */
/****************************************************************************/

/* None */

/****************************************************************************/
/* Stepper motor outputs                                                    */
/****************************************************************************/

/* None */

/****************************************************************************/
/* Synchronised PWM outputs                                                 */
/****************************************************************************/

/* None */

#endif

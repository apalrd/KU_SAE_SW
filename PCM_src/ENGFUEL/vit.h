//
// Outflows
// Outflows is the engine port mass flow calculation
// Outflows includes a calculation of VE and VE Corr
//


//Variables part of outflows - Outputs of out flows

//GF_Charge is mg/cyc/cyl
extern volatile float GF_Charge;
//GF_PortMassFlow charge but in mg/sec
extern volatile float GF_PortMassFlow;
//GF_PortExhaustFlow is charge + fuel in mg/sec
//This is used as gasflow thru cat
extern volatile float GF_PortExhaustFlow;
//Air Charge is the charge but only burnable air
extern volatile float GF_AirCharge;
//Volumetric Efficiency final
extern volatile float GF_PortCalcVE;
//Cylinder volume final
extern volatile float GF_PortCalcVol;
//Volumetric efficiency open-loop
extern volatile float GF_VEBase;
//Volumetric efficiency correction adaption
extern volatile float GF_VECorr;
//O2 correction integral
extern volatile float GF_VEO2S;
//Counter for VE adaption
extern volatile U8 GF_VECorrTmr;
//VE corr timer value to adapt
extern volatile U8 GF_VECorrTmrThrs;
//Charge Predicted calculated from CalcMAPPred
extern volatile float GF_ChargePred;
//Port mass flow predicted
extern volatile float GF_PortMassFlowPred;
//WOT Charge
extern volatile float GF_ChargeWOT;
//WOT port mass flow
extern volatile float GF_PortMassFlowWOT;
//MaxBoost Charge
extern volatile float GF_ChargeMaxBoost;
//MaxBoost Port Mass Flow
extern volatile float GF_PortMassFlowMaxBoost;
//VE at WOT
extern volatile float GF_PortCalcWOTVE;
//VE at MaxBoost
extern volatile float GF_PortCalcMaxBoostVE;
//VE Base at WOT
extern volatile float GF_VEBaseWOT;
//VE Base at MaxBoost
extern volatile float GF_VEBaseMaxBoost;
//VE Corr at WOT
extern volatile float GF_VECorrWOT;
//VE Corr at Max Boost
extern volatile float GF_VECorrMaxBoost;
//Compressor pressure ratio for calc boost temp
extern volatile float GF_CompPrsRat;
//Estimated charge air cooler efficiency
extern volatile float GF_CACEffCalc;
//Actual charge air cooler efficiency
extern volatile float GF_CACEff;
//Calculated max boost temperature
extern volatile float GF_ACTMaxBoostCalc;


//Variables part of outflows - Calibrations
//Specific gas constant - R_Air * Molar Mass of Air
extern float GF_SpecificGasConst;
//VE surface
extern float GF_VESurf[];
//RPM breakpoints for Gasflows high res
extern U16 GF_RPMBkp[];
//Load (Pratio/MAP) breakpoints for Gasflows
extern float GF_LoadBkp[];
//Low res charge ratio breakpoints for VE Corr
extern float GF_ChargeRatBkp[];
//Low res RPM breakpoints for VE Corr
extern U16 GF_RPMLowResBkp[];
//VE Correction surface
extern float GF_VECorrSurf[];
//VE corr timer cals
extern U8 GF_VECorrTmr_Nrm;
extern U8 GF_VECorrTmr_Idle;
//CAC Eff table
extern float GF_CACEffTbl[];
//CAC Eff breakpoints from input mass flow
extern float GF_CACMassFlowBkp[];
//Global register to control out flows cal
extern U32 GF_OutflowConfig;
//Values of outflow config
//BIT0: Use PRATIO for load (otherwise use MAP)
#define GF_OUTFLOW_USE_PRATIO BIT0
//BIT1: Enable use of VE CORR from surface
#define GF_OUTFLOW_USE_VECORR_SURF BIT1
//BIT2: Enable adaption of O2S to VECorr
#define GF_OUTFLOW_ENABLE_ADAPTION BIT2
//BIT3: Enable O2 Corr globally (include in VE calculation)
#define GF_OUTFLOW_ENABLE_O2_CORR BIT3
//BIT4: Use TIT for WOT flow (use ACT if false)
#define GF_OUTFLOW_USE_TIT_FOR_WOT BIT4
//BIT5: Use TIT for MaxBoost flow (use ACT if false)
#define GF_OUTFLOW_USE_TIT_FOR_MAXBOOST BIT5
//BIT6: Use Boost Temp Model for MaxBoost flow
//Overrides bit5 if selected
#define GF_OUTFLOW_USE_BOOST_TEMP_MODEL BIT6

//DIAL Outflows select register
extern U32 DIAL_GF_OutflowsSelReg;
//Values for dial outflow select:
#define DIAL_GF_Charge_Sel BIT0
#define DIAL_GF_Charge_Mult_Sel BIT1
#define DIAL_GF_PortCalcVE_Sel BIT2
#define DIAL_GF_VEBase_Sel BIT3
#define DIAL_GF_ChargeWOT_Sel BIT4
#define DIAL_GF_ChargeMaxBoost_Sel BIT5
#define DIAL_GF_ChargePred_Sel BIT6
#define DIAL_GF_PortMassFlowPred_Sel BIT7
#define DIAL_GF_PortMassFlowWOT_Sel BIT8
#define DIAL_GF_PortMassFlowMaxBoost_Sel BIT9



//Functions for calculating out flows in the TDC task
//Calculates GF_Charge and GF_ChargePred and associated lookups
//for the fuel calclations done at TDC and BDC
void GF_Outflow_CalcFlowsTDC();
//Functions for calculating out flows in the 10ms task
//Calculates the WOT and MaxBoost charges for the torque chain
void GF_Outflow_CalcFlows10MS();
//Function for calculating thermal factors in the 320ms task
void GF_Outflow_CalcDens320MS();
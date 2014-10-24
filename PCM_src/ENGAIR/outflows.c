//
// Andrew Palardy
// Out Flows
// Calculate the flows at the port

//Includes
#include "openecu.h"
#include "outflows.h"
#include "inflows.h"
#include "manifold.h"


//Helper functions
//Calculate the VE Base at a given load at current engine speed
float GF_Outflow_CalcVEBase(float load)
{
    float Temp1;
    //Interpolate the VE surface and apply dial VE's
    Temp1 = ???? Interpolation functions
    
    if(DIAL_GF_OutflowSelReg & DIAL_GF_VEBase_Sel)
    {
        Temp1 = DIAL_GF_VEBase;
    }
    
    //Return the value
    return Temp1;
}

//Calculate the VE Corr at a given charge ratio at the current engine speed
float GF_Outflow_CalcVECorr(float charge_ratio)
{
    //Do the same as above to VE Corr
}

//Calculate a load at a given MAP
float GF_Outflow_CalcLoad(float Prs)
{
    //Config bits tell us if MAP or Pratio is load
    if(GF_OutflowConfig & GF_OUTFLOW_USE_PRATIO)
    {
        //Load is map / baro
        return Prs / BARO;
    }
    else
    {
        //Load is MAP
        return Prs;
    }
}

//Functions for calculating out flows in the TDC task
//Calculates GF_Charge and GF_ChargePred and associated lookups
//for the fuel calclations done at TDC and BDC
void GF_Outflow_CalcFlowsTDC()
{
    float TempCharge;
    
    //This task is responsible for calculating GF_Charge and
    //GF_PortMassFlow in the TDC task for fuel and spark
    
    //Calculate GF Load based on either MAP or Pratio
    GF_Load = GF_Outflow_CalcLoad(GF_MAP);
    
    //Determine VE for charge
    GF_VEBase = GF_Outflow_CalcVEBase(GF_Load);
    
    //Determine GF Charge before VE Corrs for charge ratio
    TempCharge = GF_MAP * GF_EngDispEff * GF_GasFac * GF_VEBase;
    
    //Determine Charge Ratio from this temp charge before VE Corr's
    GF_ChargeRat = TempCharge / GF_ChargeAmbient;
    
    //Use Charge Ratio to determine VE Corr
    GF_VECorr = GF_Outflow_CalcVECorr(GF_ChargeRat);
    
    //Use VE Corr and O2S to adjust charge
    TempCharge = TempCharge * GF_VECorr * GF_VEO2S;
    
    //The result is GF_Charge
    GF_Charge = TempCharge;
    
    //Calculate Port Mass Flow from charge
    GF_PortMassFlow = GF_Charge * GF_CyclesPerSec;
    
    //Now do it again for MAPPred
    GF_ChargePred = GF_MAPPred * GF_EngDispEff * GF_GasFac * GF_VEBase * GF_VECorr * GF_VEO2S;
    
    //Now flow version
    GF_PortMassFlowPred = GF_ChargePred * GF_CyclesPerSec;
    
}
//Functions for calculating out flows in the 10ms task
void GF_Outflow_CalcFlows10MS()
{
    float TempCharge;
    //This is responsible for calculating GF_ChargeWOT and
    //GF_ChargeMaxBoost for the torque chain
    
    //First calculate GF_CyclesPerSec from RPM
    GF_CyclesPerSec = RPM / 120;
    
    //Now calculate Load for WOT and MaxBoost
    GF_LoadWOT = GF_Outflow_CalcLoad(GF_ThrInlPrs);
    GF_LoadMaxBoost = GF_Outflow_CalcLoad(GF_MAPMaxBoost);
    
    //Calculate VE for WOT and Max Boost
    GF_VEBaseWOT = GF_Outflow_CalcVEBase(GF_LoadWOT);
    GF_VEBaseMaxBoost = GF_Outflow_CalcVBase(GF_LoadMaxBoost);
    
    //Calculate Charge initially for each
    //WOT First
    TempCharge = GF_ThrInlPrs * GF_EngDispEff * GF_GasFacWOT * GF_VEBaseWOT;
    
    //Calculate Charge Ratio WOT
    GF_ChargeRatWOT = TempCharge / GF_ChargeAmbient;
    
    //Find VE Corr
    GF_VECorrWOT = GF_Outflow_CalcVECorr(GF_ChargeRatWOT);
    
    //Calculate Charge at WOT
    GF_ChargeWOT = TempCharge * GF_VECorrWOT;
    
    //Now do it for Max Boost
    TempCharge = GF_MAPMaxBoost * GF_EngDispEff * GF_GasFacMaxBoost * GF_VEBaseMaxBoost;
    
    //Calculate Charge Ratio
    GF_ChargeRatMaxBoost = TempCharge / GF_ChargeAmbient;
    
    //Find VE Corr at Max Boost
    GF_VECorrMaxBoost = GF_Outflow_CalcVECorr(GF_ChargeRatMaxBoost);
    
    //Now find charge
    GF_ChargeMaxBoost = TempCharge * GF_VECorrMaxBoost;
    
    //Now convert both to Flows
    GF_PortMassFlowWOT = GF_ChargeWOT * GF_CyclesPerSec;
    GF_PortMassFlowMaxBoost = GF_ChargeMaxBoost * GF_CyclesPerSec;
}
//Function for calculating thermal factors in the 320ms task
void GF_Outflow_CalcDens320MS()
{
    //Locals are more efficient
    //They are stored in registers, while volatile
    //variables require load/store for each access
    float Temp1, Temp2, temp3;
    
    
    //Thermal factors
    
    //Determine temperatures
    //TODO if we fault ACT and TIT is available use that instead
    //GF_Temps are in Kelvin
    GF_Temp = SENS_ACT + DEG_C_TO_K;
    
    //Calculate the normal gas factor
    GF_GasFac = 1/(GF_SpecificGasConst * GF_Temp);
    
    //Determine what WOT temp should be
    //TODO if we fail the TIT sensor use the ACT value
    if(GF_OutflowConfig & GF_OUTFLOW_USE_TIT_FOR_WOT)
    {
        //Use TIT for WOT Temp
        GF_TempWOT = SENS_TIT + DEG_C_TO_K;
    }
    //Otherwise
    else
    {
        GF_TempWOT = SENS_ACT + DEG_C_TO_K;
    }
    
    //Calculate the WOT gas factor
    GF_GasFacWOT = 1/(GF_SpecificGasconst * GF_TempWOT);
    
    //Calculate the max boost temp using the target boost
    //Always do the calculation for testing
    
    //Temp1 is ambient temp in kelvin
    Temp1 = SENS_AMB + DEG_C_TO_K;
    //Temp2 is the exponent
    Temp2 = (1.4-1.0)/(1.4);
    //Raw temp at max boost
    GF_TempMaxBoostCalcRaw = Temp1 * GF_CompPratioMaxBoost^Temp2;
    
    //This temp is the hot boost temp
    GF_TempHotBoost = GF_TempMaxBoostCalcRaw;
    
    //Calculate the HotBoost gas factor
    GF_GasFacHotBoost = 1/(GF_SpecificGasConst * GF_TempHotBoost);
    
    //Calculate the HotBoost port mass flow based on the current MaxBoost gas factor
    GF_PortMassFlowHotBoost = GF_PortMassFlowMaxBost * (GF_GasFacHotBoost / GF_GasFacMaxBoost);
    
    //Use the new port mass flow to lookup intercooler efficiency
    GF_CACEffCalc = ????TODO
    
    //Determine max boost temp
    //Temp1 is still ambient temp
    GF_TempMaxBoostCalc = Temp1 + ((GF_TempHotBoost - Temp1) * GF_CACEffCalc);
    
    //Determine which temperature we should use for Max Boost
    
    if(GF_OutflowConfig & GF_OUTFLOW_USE_BOOST_TEMP_MODEL)
    {
        //Use the max boost calc temp
        GF_TempMaxBoost = GF_TempMaxBoostCalc;
    }
    else if(GF_OutflowConfig & GF_OUTFLOW_USE_TIT_FOR_MAXBOST)
    {
        //Use TIT temp
        GF_TempMaxBoost = SENS_TIT + DEG_C_TO_K;
    }
    else
    {
        //Use ACT temp
        GF_TempMaxBoost = SENS_ACT + DEG_C_TO_K;
    }
    
    //Calculate MaxBoost gas factor
    GF_GasFacMaxBoost = 1/(GF_SpecificGasConst * GF_TempMaxBoost);
    
    //Calculate the Ambient gas factor
    GF_GasFacAmbient = 1/(GF_SpecificGasConst * (SENS_AMB + DEG_C_TO_K));
    
    //Calculate Ambient Charge
    GF_ChargeAmbient = BARO * GF_EngVol * GF_GasFacAmbient;
    
    //Calculate ambient port mass flow
    GF_PortMassFlowAmbient = GF_ChargeAmbient * GF_CyclesPerSec;
    
}
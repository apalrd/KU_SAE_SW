//
// Andrew Palardy
// Out Flows
// Calculate the flows at the port

//Includes
#include "openecu.h"
#include "outflows.h"
#include "inflows.h"
#include "manifold.h"


//Functions for calculating out flows in the TDC task
//Calculates GF_Charge and GF_ChargePred and associated lookups
//for the fuel calclations done at TDC and BDC
void GF_Outflow_CalcFlowsTDC()
{
    //This task is responsible for calculating GF_Charge and
    //GF_PortMassFlow in the TDC task for fuel and spark
    
}
//Functions for calculating out flows in the 10ms task
void GF_Outflow_CalcFlows10MS()
{
    //This is responsible for calculating GF_ChargeWOT and
    //GF_ChargeMaxBoost for the torque chain
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
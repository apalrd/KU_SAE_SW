//
// Andrew Palardy
// In flows calculation
// In Flows calculates:
// Throttle flows
// Restrictor flows and pressures
// Compressor pressure ratios
//

#include "openecu.h"
#include "inflows.h"
#include "manifold.h"
#include "outflows.h"

//Function calls
//Calculate the in flows in the 10MS task
void GF_Inflows_CalcFlows10MS()
{
    //Find throttle sonic flow from throttle position
    GF_ThrSonicFlow = ?? TABLE Lookup
    
    //Find throttle compressible flow factor
}

//Adapt the throttle flows in the 80ms task
void GF_Inflows_CalcThrAdapt80MS()
{
    //Set adaptives to 0
    GF_ThrFlowAdaptAdd = 0;
    GF_ThrFlowAdaptMult = 0;
    //We will enable throttle adaption later
}

//Calculate the density corrections in the 320ms task
//Restrictor pressure drop is calculated here as well
void GF_Inflows_CalcDensity320MS()
{
    //Calculate throttle inlet temp from SENS_TIT or SENS_ACT
    //TODO if we fail the TIT sensor use the ACT value
    if(GF_InflowConfig & GF_INFLOW_USE_ACT_FOR_THR)
    {
        //Use ACT for ThrTemp
        GF_ThrInlTemp = SENS_ACT + DEG_C_TO_K;
    }
    //Otherwise
    else
    {
        GF_ThrInlTemp = SENS_TIT + DEG_C_TO_K;
    }
    
    //First calculate the speed of sound at the throttle inlet temp
    GF_SpeedOfSound = sqrt(1.4*286*GF_ThrInlTemp);
    
    //Calculate throttle air density
    GF_ThrAirDensity = GF_ThrInlPrs / (GF_SpecificGasConst * GF_ThrInlTemp);
    
    //Calculate restrictor air density
    GF_RstcAirDensity = BARO / (GF_SpecificGasConst * (SENS_AMB + DEG_C_TO_K));
}
//
// Pulse Width
// Responsible for all interactions between fuel mass
// and Fuel Time.


//Variables part of Pulsewidth
//Total working pulse width for primaries
extern volatile float FUEL_PWTotalWork[];
//Total working pulse width for secondaries
extern volatile float FUEL_PWTotalWorkSec[];
//Drop Dead angle for primaries
extern volatile float FUEL_PWAngDropDead[];


//Variables part of Pulsewidth - Calibrations



//Functions for calculating out flows in the TDC task
//Calculates GF_Charge and GF_ChargePred and associated lookups
//for the fuel calclations done at TDC and BDC
void GF_Outflow_CalcFlowsTDC();
//Functions for calculating out flows in the 10ms task
//Calculates the WOT and MaxBoost charges for the torque chain
void GF_Outflow_CalcFlows10MS();
//Function for calculating thermal factors in the 320ms task
void GF_Outflow_CalcDens320MS();
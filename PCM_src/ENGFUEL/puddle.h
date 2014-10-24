//
// Andrew Palardy
// Puddle
// Puddle is the core of fuel
// Puddle is responsible for calculating fuel mass to inject
// from the gas flows and desired fuel air. Puddle is also
// responsible for the puddle mass estimate.
//


//Variables part of Puddle
//Puddle fuel inflow
extern float FUEL_PudFuelInflow;
//Puddle fuel mass to inject per cylinder
extern float FUEL_PudMassToInj[];
//Puddle fuel mass
extern float FUEL_PudMass[];
//Puddle X value
extern float FUEL_PudX;
//Puddle Tau value
extern float FUEL_PudTau;
//Time delta for Puddle angular calcs
extern float FUEL_PudTimeDT;
//Total fuel injected last cycle - This variable is written
//by Pulse Width, including for start fuel, for the primary
//injectors only
extern float FUEL_LastCycInj[];
//Total pulwe injected at the secondary injector
extern float FUEL_LastCycInjSec[];
//Fuel mass to inject secondaries
extern float FUEL_PudMassToInjSec[];
//Fuel upstream fraction from pulse width
extern float FUEL_PudInjFracSec;
//Filtered puddle mass for secondaries
//This is filtered per cylinder.
extern float FUEL_PudSecPudFilt[];

//Variables part of Puddle - Cals
//X factor from coolant temp
extern float FUEL_PudXTempFacTbl[];
//Tau factor from coolant temp
extern float FUEL_PudTauTempFacTbl[];
//X table from load
extern float FUEL_PudXTbl[];
//Tau table from load
extern float FUEL_PudTauTbl[];
//



//Functions for calculating out flows in the TDC task
//Calculates GF_Charge and GF_ChargePred and associated lookups
//for the fuel calclations done at TDC and BDC
void GF_Outflow_CalcFlowsTDC();
//Functions for calculating out flows in the 10ms task
//Calculates the WOT and MaxBoost charges for the torque chain
void GF_Outflow_CalcFlows10MS();
//Function for calculating thermal factors in the 320ms task
void GF_Outflow_CalcDens320MS();
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
//Fuel mass to inject secondaries - per secondary injector
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
//Upstream factor surface from speed/load
extern float FUEL_PudSecFacSurf[];




//Functions for calculating puddle in the TDC task
void FUEL_Puddle_CalcTDC();
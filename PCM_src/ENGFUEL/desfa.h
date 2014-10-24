//
// Desired Fuel Air
// Determines Phi targets for torque and puddle


//Variables part of Des FA
//Desired Fuel Air for puddle
extern volatile float FUEL_PhiTarget;
//Desired Fuel Air limits for fast path
//Des FA converts these to efficienes
extern volatile float FUEL_TrqEffMax;
extern volatile float FUEL_TrqEffMin;
extern volatile float FUEL_PhiTrqMax;
extern volatile float FUEL_PhiTrqMin;
//FA for slow path
extern volatile float FUEL_TrqEffSlw;
extern volatile float FUEL_PhiTrqSlw;
//Lean target for BSFC
extern volatile float FUEL_PhiBSFC;
//Lean limit for combustion stability (transient)
extern volatile float FUEL_PhiLean;
//LBT torque
extern volatile float FUEL_PhiLBT;
//FA enrichment request for thermal protection
extern volatile float FUEL_PhiTherm;
//FA enrichment request for knock protection
extern volatile float FUEL_PhiKnock;
//FA enrichment request for LNT regen request
extern volatile float FUEL_PhiLNTRegen;
//Fuel control ID - Indicats what determines FA
extern volatile U8 FUEL_PhiCtrlSlw;
extern volatile U8 FUEL_PhiCtrlFst;
//Stoich FA
extern volatile float FUEL_StoichFA;

//Variables part of Des FA - Cals
//Des FA surf for peak BSFC
extern float FUEL_PhiBSFCSurf[];
//Des FA limit for combustion stability
extern float FUEL_PhiLeanSurf[];
//Use the standard charge breakpoints from Gas Flows
//FA table
extern float FUEL_StoichFATbl[];
extern float FUEL_EthanolBkp[];


//Functions for calculating Des FA
//Des FA calculation for puddle and MidEPP torque
void FUEL_DesFA_CalcTDC();
//Des FA calculation for torque prediction
void FUEL_DesFA_Calc10MS();

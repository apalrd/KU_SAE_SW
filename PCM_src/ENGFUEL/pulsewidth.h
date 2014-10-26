//
// Pulse Width
// Responsible for all interactions between fuel mass
// and Fuel Time.


//Variables part of Pulsewidth
//Total working pulse width by injector #
extern volatile float FUEL_PWTotalWork[];
//Drop Dead angle for primaries
extern volatile float FUEL_PWAngDropDead[];
//Pulse width requested at initial pulse event
extern volatile float FUEL_PWInitial[];
//Pulse width requested at make-up pulse
extern volatile float FUEL_PWMakeUp[];
//Pulse actually delivered, reported by eTPU
extern volatile float FUEL_PWActual[];
//Dead time, global
extern volatile float FUEL_PWDead;
//nonlinear time
extern volatile float FUEL_PWNonlin;
//Injector is operating in nonlinear zone flag
extern volatile U8 FUEL_PWIsNonlin[];
//Injection pressure per injector
extern volatile float FUEL_PWInjPrs[];
//Enum of which pressure to use for downstream pressure
extern volatile U8 FUEL_PWPrsDown[];
//Enum of which pressure to use for upstream pressure
extern volatile U8 FUEL_PWPrsUp[];
//Field of the pressures which can be used as downstream
extern volatile float FUEL_PrsDown[];
//Field of the pressures which can be used as upstream
extern volatile float FUEL_PrsUp[];
//Mass requested by injector #
extern volatile float FUEL_PWDesMass[];
//Mass actual by injector #
extern volatile float FUEL_PWActMass[];
//FUEL Puddle must report masses per injector
//It is the responsibility of Puddle to
//map cylinders/banks to injectors


//Variables part of Pulsewidth - Calibrations
//Injector flow surface from injection pressure and mass des
//for injectors flagged as primary injectors
extern volatile float FUEL_PWInjFlowSurfPrimSurf[];
//Injector flow surface for secondary injectors
extern volatile float FUEL_PWInjFlowSurfSecSurf[];
//Nonlinear correction table for primaries
extern volatile float FUEL_PWInjNonlinPrimSurf[];
//For secondaries
extern volatile float FUEL_PWInjNonlinSecSurf[];
//Nonlinear threshold by injection pressure
extern volatile float FUEL_PWNonlinThrPrimTbl[];
//For secondaries
extern volatile float FUEL_PWNonlinThrSecTbl[];
//Battery voltage breakpoints for pulse width
extern volatile float FUEL_PWBattBkp[];
//Injection pressure breakpoints for pulse width
extern volatile float FUEL_PWInjPreBkp[];




//Functions for calculating out flows in the TDC task
//Calculates GF_Charge and GF_ChargePred and associated lookups
//for the fuel calclations done at TDC and BDC
void GF_Outflow_CalcFlowsTDC();
//Functions for calculating out flows in the 10ms task
//Calculates the WOT and MaxBoost charges for the torque chain
void GF_Outflow_CalcFlows10MS();
//Function for calculating thermal factors in the 320ms task
void GF_Outflow_CalcDens320MS();
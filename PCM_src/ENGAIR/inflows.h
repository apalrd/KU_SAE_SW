//
// Inflows
// Inflows calculate the flows into the manifold
// Inflows includes the throttle flow calculation


//Variables that are output by Inflows
//Output flow through the throttle mg/s
extern volatile float GF_ThrFlow;
//Sonic flow through the throttle mg/s
extern volatile float GF_ThrSonicFlow;
//Mach number of flow through the throttle
extern volatile float GF_ThrMachNum;
//Throttle pressure ratio MAP/TIP
extern volatile float GF_ThrPratio;
//Throttle flow adaption addition
extern volatile float GF_ThrFlowAdaptAdd
//Throttle flow adaption mult
extern volatile float GF_ThrFlowAdaptMult
//Throttle flow before adaption
extern volatile float GF_ThrRawFlow;
//Throttle air densty
extern volatile float GF_ThrAirDensity
//Speed of sound
extern volatile float GF_SpeedOfSound
//Restrictor pressure ratio
extern volatile float GF_RstcPratio;
//Restrictor flow (equals throttle flow)
extern volatile float GF_RstcFlow;
//Restrictor mach number
extern volatile float GF_RstcMachNum;
//Restrictor sonic flow
extern volatile float GF_RstcSonicFlow;
//Restrictor out pressure
//Used for compressor ratio calculation in out flows
extern volatile float GF_RstcOutPrs;

//Calibrations for in flows
//Sonic flow table for the throttle
extern float GF_ThrSonicFlowTbl[];
//Breakpoints for sonic flow table
extern float GF_ThrBkp[];
//Restrictor area
extern float GF_RstcArea;

//Function calls
//Calculate the in flows in the 10MS task
void GF_Inflows_CalcFlows10MS();
//Adapt the throttle flows in the 80ms task
void GF_Inflows_CalcThrAdapt80MS();
//Calculate the density corrections in the 320ms task
void GF_Inflows_CalcDensity320MS();


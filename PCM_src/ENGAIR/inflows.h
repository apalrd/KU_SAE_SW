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
//Restrictor flow at WOT
extern volatile float GF_RstcFlowWOT;
//Restrictor air density
extern volatile float GF_RstcAirDensity;
//Restrictor flow at MaxBoost
extern volatile float GF_RstcFlowMaxBoost;
//Restrictor mach number at WOT
extern volatile float GF_RstcMachNumWOT;
//Restrictor mach number at MaxBoost
extern volatile float GF_RstcMacnNumMaxBoost;
//Restrictor out pressure at WOT
extern volatile float GF_RstcOutPrsWOT;
//Restrictor out pressure at MaxBoost
extern volatile float GF_RstcOutPrsMaxBoost;
//Compressor pressure ratio
extern volatile float GF_CompPratio;
//Compressore pressure ratio at MaxBoost
extern volatile float GF_CompPratioMaxBoost;
//TIP pressure
extern volatile float GF_ThrInlPrs;
//TIT Temp
extern volatile float GF_ThrInlTmp;

//Calibrations for in flows
//Sonic flow table for the throttle
extern float GF_ThrSonicFlowTbl[];
//Breakpoints for sonic flow table
extern float GF_ThrBkp[];
//Restrictor area
extern float GF_RstcArea;
//Inflow config register
extern U32 GF_InflowConfig;
//Bit defines for inflow config:
//Bit0 use ACT instead of TIT for Thr temp
#defnie GF_INFLOW_USE_ACT_FOR_THR BIT0

//Function calls
//Calculate the in flows in the 10MS task
void GF_Inflows_CalcFlows10MS();
//Adapt the throttle flows in the 80ms task
void GF_Inflows_CalcThrAdapt80MS();
//Calculate the density corrections in the 320ms task
//Restrictor pressure drop is calculated here as well
void GF_Inflows_CalcDensity320MS();


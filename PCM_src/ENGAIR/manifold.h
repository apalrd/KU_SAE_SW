//
// Manifold
// Manifold is responsible for gasflow MAP calulation
// and the manifold mass balance. This is used for
// calc MAP, throttle flows adaption, and to provide
// a cleaner MAP signal for odd-fire engines

//Variables part of Manifold

//GF_MAP is the filtered MAP signal used for airflow calculation
extern float GF_MAP;
//GF_CalcMAP is the calculated MAP from Manifold
extern float GF_CalcMAP;
//GF_ManMass is the mass in the manifold
extern float GF_ManMass;
//GF_ManDens is the density in the manifold
extern float GF_ManDens;
//GF_ManInflows is the sum of the in flows
extern float GF_ManInflows;
//GF_ManOutflows is the sum of the out flows
extern float GF_ManOutflows;
//GF_ManFlowRatio is the in/out ratio
extern float GF_ManFlowRatio;
//GF_CalcMAPPred is the predicted Calc MAP next cycle
//This is used for puddle calculations
extern float GF_CalcMAPPred;
//MAPPred is stuffed with the correct value to use
extern float GF_MAPPRed;
//GF_MAPMaxBoost is the MAP at MaxBoost
extern float GF_MAPMAxBoost;


//Variables part of Manifold - Calibrations
//Specific gas constant - R_Air * Molar Mass of Air
extern float GF_SpecificGasConst;
//Volume of the intake manifold
extern float GF_ManVolume;



//Calculate the intake manifold model in the TDC task
void GF_ManModelTDC();
//Calculate the intake manifold model in the 10ms task
void GF_ManModel10MS();
//
// Fuel Pump control
//


//Variables part of Pump
//Fuel pump desired status
extern volatile U8 FUEL_PmpStat;
//Fuel pump status to be written to actuator
extern volatile U8 FUEL_PmpStatRaw;
//Prime timer number of 5ms task counts
extern volatile U16 FUEL_PmpPrimeTimer;


//Variables part of Pump
//Fuel pressure threshold
extern float FUEL_PmpPrs;
//Prime timer threshold
extern U16 FUEL_PmpPrimeTimeThr;
//Fuel pump config register
extern U8 FUEL_PmpConfigReg;
//Config bits
//Config the fuel pump polarity
#define FUEL_PMPCONFIG_POLARITY BIT0
//Disable fuel pump under ETC Power Free
#define FUEL_PMPCONFIG_ETC_PWR_FREE BIT1
//Use the alternate control pin
#define FUEL_PMPCONFIG_USE_ALT_PIN BIT2
//Dial fuel pump register
extern U8 DIAL_FUEL_PmpSel;
//Dial bits
#define DIAL_FUEL_PMP_ON BIT0
#define DIAL_FUEL_PMP_OFF BIT1
#define DIAL_FUEL_PMP_NOPRIME BIT2

//Calculate the fuel pump init
void FUEL_PmpInit();
//Calculate the fuel pump in the 5ms task
void FUEL_PmpCalc5MS();
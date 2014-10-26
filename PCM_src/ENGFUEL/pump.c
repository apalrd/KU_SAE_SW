//
// Fuel Pump Control
//

#include "openecu.h"
#include "pump.h"
#include "sensors.h"

//Function to write the fuel pump pin
void FUEL_PmpWritePin()
{
    //Read the FUEL_PmpStat for the value
    U8 FuelPmpStatTemp;
    
    FuelPmpStatTemp = FUEL_PmpStat;
    
    //Determine if there is an ETC Power Free request
    //TODO need to define ETC power free interface
    
    //Determine if there is a dial request for pump on
    if(DIAL_FUEL_PmpSel & DIAL_FUEL_PMP_ON) FuelPmpStatTemp = 1;
    
    //Determine if there is a dial request for pump off
    if(DIAL_FUEL_PmpSel & DIAL_FUEL_PMP_OFF) FuelPmpStatTemp = 0;
    
    //Invert if configured
    if(FUEL_PmpConfigReg & FUEL_PMPCONFIG_POLARITY)
    {
        if(FuelPmpStatTemp) FuelPmpStatTemp = 0;
        else FuelPmpStatTemp = 1;
    }
    
    //Write raw value
    FUEL_PmpStatRaw = FuelPmpStatTemp;
    
    //TODO OpenECU call to digital output
}
//Init the fuel pump control
void FUEL_PmpInit()
{
    //Reset the timer when we power up
    FUEL_PmpPrimeTimer = 0;
    //Turn the pump off
    FUEL_PmpStat = 0;
    
    //Turn the fuel pump off
    FUEL_PmpWritePin();
}

//Calculate the fuel pump in the 5ms task
void FUEL_PmpCalc5MS()
{
    //Create a temp variable for the state of the fuel pump this iteration
    U8 FuelPmpStatTemp
    
    //Determine the run-mode fuel pump status based on fuel pressure
    if(SENS_FUELP > FUEL_PmpPrs)
    {
        //Turn the pump off
        FuelPmpStatTemp = 0;
    }
    else
    {
        //Turn the pump on
        FuelPmpStatTemp = 1;
    }
    
    //TODO if there is a circuit fault on the fuel pump turn it on
    
    //write the fuel pump status variable
    FUEL_PmpStat = FuelPmpStatTemp;
    
    //Write the fuel pump status
    FUEL_PmpWritePin();
    
}
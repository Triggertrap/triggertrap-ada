#include <stdlib.h>
#include "MenuDefines.h"
#include "Arduino.h"
#include "HardwareGlobals.h"
#include "EEPROM.h"
#include "Inputs.h"

////////////////////////////
//only works on MIC output
//11.04 KHz  D = 0.5066
/////////////////////////////////

void MobileTriggerSetup(void)
{
	unsigned int time_low = 0x0BDA;
	unsigned int time_high = 0x05ED;
		
	PORTE.DIRSET   |= 0x10;                 // setup pout, relay outputs
	PORTE.OUTSET   |= 0x10;
		
	TCE1.PER      = time_low;                //
	TCE1.CCA      = time_high;                //
	TCE1.CTRLA    =  0x01;                 // Work from CPUCLK/1 11.0592mhz
}
void mobile_trigger_on(void)
{
	TCE1.CTRLB    =  0xf3;                 // enable compare A,B,C,D for single slope pwm
}

////////////////////////////////////
//this will turn of the pwm on the MIC pin
////////////////////////////////////////////
void mobile_trigger_off(void)
{	
	TCE1.CTRLB = 0x00;
}
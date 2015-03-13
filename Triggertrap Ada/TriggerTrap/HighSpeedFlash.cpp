#include <stdlib.h>
#include "MenuDefines.h"
#include "Arduino.h"
#include "HardwareGlobals.h"

#include "guimenu.h"
#include "guimenu_pages.h"
#include "Menu.h"
#include "Inputs.h"

#include "HighSpeedFlash.h"
#include "EEPROM.h"
#include "eeprom_addresses.h"

static uint8_t input_key;


/*****************************************************************************
*
*   Function name : HighSpeedFlash
*
*   Returns :       NIL
*
*   Parameters :  
*
*   Purpose :      Runs the application code for HSF 
*
*	Notes:		   Room for optimization but will require thought and interrupt routines
*
*****************************************************************************/

char HighSpeedFlash(char input)
{
   volatile unsigned long StartTimeMs,StartTimeUs,ElapsedTime = 0, FlashPulseLength,MicroElapsedTime = 0,MillisElapsedTime = 0,Reset_delay,Shutter_Plse_delay_us,Shutter_Plse_delay,shutter_cyc_delay;
   volatile char close_shutter_en;
   volatile unsigned long Flash_delay;
   
   unsigned int TimeActiveCheck = 500;
 
   unsigned char Reset_delayLow, Reset_delayHigh, Units,shutter_cyc_delayLow,shutter_cyc_delayHigh,Flash_delayLow,Flash_delayHigh,ButtonCheckDelay;
   unsigned char FlashPulseLengthLow,FlashPulseLengthHigh,TimeActiveSelector;   

   bool SensorTriggerReceived = false,FlashServiced,ResetDelayServiced,CloseShutterServiced;
  		
  Reset_delayLow  =  EEPROM.read(EEPROM_HSF_RESETDELAY_LO);
  Reset_delayHigh =  EEPROM.read(EEPROM_HSF_RESETDELAY_HI);
  Reset_delay = (Reset_delayHigh << 8) | Reset_delayLow;	//
  Units = EEPROM.read(EEPROM_HSF_RESETDELAY_UNITS);
  Reset_delay = formatTimeToMillis(Reset_delay,Units);

  shutter_cyc_delayLow  =  EEPROM.read(EEPROM_HSF_SHUTTERCYCLE_LO);
  shutter_cyc_delayHigh =  EEPROM.read(EEPROM_HSF_SHUTTERCYCLE_HI);
  shutter_cyc_delay = (shutter_cyc_delayHigh << 8) | shutter_cyc_delayLow;	//
  Units = EEPROM.read(EEPROM_HSF_SHUTTERCYCLE_UNITS);
  shutter_cyc_delay = formatTimeToMillis(shutter_cyc_delay,Units);	

  close_shutter_en =  EEPROM.read(EEPROM_HSF_CLOSESHUTTER);
  
  Flash_delayLow  =  EEPROM.read(EEPROM_HSF_FLASHDELAY_LO);
  Flash_delayHigh =  EEPROM.read(EEPROM_HSF_FLASHDELAY_HI);
  Flash_delay = (Flash_delayHigh << 8) | Flash_delayLow;	//
  Units = EEPROM.read(EEPROM_HSF_FLASHDELAY_UNITS);
  Flash_delay = formatTimeToMicro(Flash_delay,Units);	
  
  FlashPulseLengthLow  =  EEPROM.read(EEPROM_FLASHPULSE_LO);
  FlashPulseLengthHigh =  EEPROM.read(EEPROM_FLASHPULSE_HI);
  FlashPulseLength = (FlashPulseLengthHigh << 8) | FlashPulseLengthLow;		//
  Units = EEPROM.read(EEPROM_FLASHPULSE_UNITS);
  FlashPulseLength = formatTimeToMicro(FlashPulseLength,Units);
	
  TimeActiveSelector = EEPROM.read(EEPROM_HSF_TIMESACTIVE);			//variable to see if always active or times is selected
  
  digitalWrite(Trigger,1);	//open shutter
  digitalWrite(Focus, 1);	//
 
  ////////////////////////////////////////
	
  Shutter_Plse_delay = 1000;		//temporary set value
  Shutter_Plse_delay_us = Shutter_Plse_delay * 1000;
   ButtonCheckDelay = 100;
   
	 if (!TimeActiveSelector)
	 {
	 
		 while(!(time_active(EEPROM_HSF_START_HOURS,EEPROM_HSF_END_HOURS)))	//while not in time, wait here
		 {
			 if(GetButton() == KEY_MINUS)
			 {
				 digitalWrite(Focus, 0);
				 digitalWrite(Trigger, 0);
				 digitalWrite(CAMERAOUT2_A,0);	//trigger flash
				 digitalWrite(CAMERAOUT2_B,0);	//
				 mobile_trigger_off();
				 StackPowerDown();
				 return ST_HSF_START;
			 }
		 }
	 
	 }
	 
  
  while(1)	//main loop, to continue until user exits
  {
	  SensorTriggerReceived = false;
	  FlashServiced = false;
	  ResetDelayServiced = false;
	  CloseShutterServiced = !close_shutter_en;	
	  
	  StartTimeMs = millis();

	  while(SensorTriggerReceived == false)		//This routine only handles the shutter cycling, and the trigger, to maximize speed.
	  {											//All other actions can be completed after leaving this loop
	  
		 ElapsedTime = millis() - StartTimeMs;
	  
	  
		 if(digitalRead(Stack) == 0)	//have we received a trigger?
		 {
			SensorTriggerReceived = true;					//yes, exit
		 }
	  
	  
		 else if(shutter_cyc_delay != 0 && !SensorTriggerReceived)
		 {
	  
			 if(ElapsedTime >= shutter_cyc_delay)			//if shutter cycling = 0, it is disabled
			 {
	  
				digitalWrite(Trigger,0);	//close shutter
				digitalWrite(Focus, 0);		//	
			
				 if((ElapsedTime >= (shutter_cyc_delay + Shutter_Plse_delay)))
				 {
			 
					 digitalWrite(Trigger,1);	//open shutter
					 digitalWrite(Focus, 1);		//
					 StartTimeMs = millis();		//Reset time variable
			 
				 }
	 
			 }
		 }

		if(!ButtonCheckDelay)					//not checking the button all the time will speed the process
		{
			 if(GetButton() == KEY_MINUS)
			 {
	 	 		digitalWrite(Focus, 0);
	 	 		digitalWrite(Trigger, 0);
	 	 		digitalWrite(CAMERAOUT2_A,0);	//trigger flash
	 	 		digitalWrite(CAMERAOUT2_B,0);	//
	 	 		StackPowerDown();		  
	 			return	ST_HSF_START;
			 }
			 
			 if(!TimeActiveCheck)
			 {

				 if (!TimeActiveSelector)			//It's also worth checking the times active here too!
				 {
		 
					 while(!(time_active(EEPROM_HSF_START_HOURS,EEPROM_HSF_END_HOURS)))	//while not in time, wait here
					 {
						 if(GetButton() == KEY_MINUS)
						 {
							 digitalWrite(Focus, 0);
							 digitalWrite(Trigger, 0);
							 digitalWrite(CAMERAOUT2_A,0);	//trigger flash
							 digitalWrite(CAMERAOUT2_B,0);	//
							 mobile_trigger_off();
							 StackPowerDown();
							 return ST_HSF_START;
						 }
					 }
		 
				 }
				 
				 TimeActiveCheck = 500;
			 
			 }
			 
			 TimeActiveCheck--;
			 
			 ButtonCheckDelay = 100;
		}
		
		ButtonCheckDelay--;
	  
	  }
	  
	  StartTimeMs = millis();
	  StartTimeUs = micros();
	  
	  while(!(FlashServiced && ResetDelayServiced && CloseShutterServiced))				//not all of the conditions have been met
	  {
		  
		  MillisElapsedTime = millis() - StartTimeMs;
		  MicroElapsedTime = micros() - StartTimeUs;			//how much time has passed?
		  
		  if((MicroElapsedTime >= Flash_delay) && (!FlashServiced)) //has enough time passed before we should trigger the second output, Channel A?
		  {
			  digitalWrite(CAMERAOUT2_A,1);	//trigger flash
			  digitalWrite(CAMERAOUT2_B,1);	//
		  	  
		  	  if(MicroElapsedTime >= (Flash_delay + FlashPulseLength))	  //has enough time passed for the pulse time for this channel?
		  	  {
			      digitalWrite(CAMERAOUT2_A,0);	//trigger flash
			      digitalWrite(CAMERAOUT2_B,0);	//
			  	  FlashServiced = true;								  //yes, it has, turn off and mark complete
			  }
		  
		  }
		  
		  if((MicroElapsedTime >= (Flash_delay + FlashPulseLength)) && (!CloseShutterServiced)) //has enough time passed before we should trigger the second output, Channel A?
		  {
			  digitalWrite(Trigger,0);	//close shutter
			  digitalWrite(Focus, 0);	//
			  
			  
			  if(MicroElapsedTime >= (Flash_delay + FlashPulseLength + Shutter_Plse_delay_us))	  //has enough time passed for the pulse time for this channel?
			  {
			      digitalWrite(Trigger,1);	//open shutter
	    		  digitalWrite(Focus, 1);	//
				  CloseShutterServiced = true;								  //yes, it has, turn off and mark complete
			  }
			  
		  }
		  

		  if((MillisElapsedTime >= Reset_delay) && (!ResetDelayServiced)) //has enough time passed before we should trigger the second output, Channel A?
		  {
			  ResetDelayServiced = true;								  //yes, it has, turn off and mark complete
		  }
		  
		  
		  if(GetButton() == KEY_MINUS)
		  {
			  		
	 	 	digitalWrite(Focus, 0);
	 	 	digitalWrite(Trigger, 0);
			digitalWrite(CAMERAOUT2_A,0);	//trigger flash
			digitalWrite(CAMERAOUT2_B,0);	//
	 	 	StackPowerDown();
	 	 	return	ST_HSF_START;
		  }
	  }
	  
	  //close shutter if required
	  //repeat
  }// end main loop
  
 
	
	digitalWrite(Focus, 0);
	digitalWrite(Trigger, 0);
	digitalWrite(CAMERAOUT2_A,0);	//trigger flash
	digitalWrite(CAMERAOUT2_B,0);	//
	StackPowerDown();
	return ST_HSF_START;
	
}


char HSFConfigure (char input)
{
	char return_state = SensorSettlingDelay (GUIMENU_HSF_CONFIG_PAGE, ST_HSF_STOP, ST_HSF_START , EEPROM_HSF_TRIGGERON);
	
	return return_state;
}

	  
char HSFTriggerOnSet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_HSF_TRIGGERON_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
				next_state = ST_HSF_START;
			break;
			
			case KEY_DOWN:
				next_state = ST_HSF_CLOSESHUTTER_SET;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char HSFCloseShutterSet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_HSF_CLOSE_SHUTTER_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
				next_state = ST_HSF_TRIGGERON_SET;
			break;
			
			case KEY_DOWN:
				next_state = ST_HSF_SHUTTERCYCLE_SET;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char HSFShutterCycleSet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_HSF_SHUTTER_CYCLING_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
				next_state = ST_HSF_CLOSESHUTTER_SET;
			break;
			
			case KEY_DOWN:
				next_state = ST_HSF_FLASH_DELAY_SET;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char HSFFlashDelaySet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_HSF_FLASH_DELAY_PAGE	, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
				next_state = ST_HSF_SHUTTERCYCLE_SET;
			break;
			
			case KEY_DOWN:
				next_state = ST_HSF_RESETDELAY_SET;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char HSFResetDelaySet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_HSF_RESET_DELAY_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
				next_state = ST_HSF_FLASH_DELAY_SET;
			break;
			
			case KEY_DOWN:
				next_state = ST_HSF_TIMESACTIVE_SET;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}

char HSFTimesActiveSet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_HSF_TIMESACTIVE_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
				next_state = ST_HSF_RESETDELAY_SET;
			break;
			
			case KEY_DOWN:
				next_state = ST_HSF_START_TIME_SET;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char HSFStartTimeSet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_HSF_STARTTIME_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_HSF_TIMESACTIVE_SET;
			break;
			
			case KEY_DOWN:
			next_state = ST_HSF_END_TIME_SET;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char HSFEndTimeSet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_HSF_ENDTIME_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
				next_state = ST_HSF_START_TIME_SET;
			break;
			
			case KEY_DOWN:
				next_state = ST_HSF_END_TIME_SET;
			break;

		}
		
		input_key = GetButton();
	}

	return next_state;
}


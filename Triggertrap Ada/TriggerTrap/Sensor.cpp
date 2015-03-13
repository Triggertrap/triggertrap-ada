#include <stdlib.h>
#include "MenuDefines.h"
#include "Arduino.h"
#include "HardwareGlobals.h"
#include "guimenu.h"
#include "Menu.h"
#include "eeprom_addresses.h"
#include "Inputs.h"


#include "EEPROM.h"
static uint8_t input_key;

extern unsigned long (*CurrentTimeSelector (unsigned char Units))(void);

/*****************************************************************************
*
*   Function name : SensorTrigger
*
*   Returns :       NIL
*
*   Parameters :  
*
*   Purpose :      
*
*****************************************************************************/


char SensorTrigger(char input) {
  unsigned char HighByte,LowByte,StartDelayUnits,TimeActiveSelector;
  unsigned char TriggerInputsignal,Units,MobIn,StartDelayLow,StartDelayHigh,MobOut;    
  bool PrimaryOutputAServiced,PrimaryOutputBServiced,MobileOutputServiced,ReTriggerServiced;
  unsigned long MobileOutputDelay = 0, ElapsedTime, StartTime;
  unsigned long (*CurrentTime)(void),TriggerDelay,PrimaryOutputADelay,PrimaryOutputBDelay,PrimaryOutputBPulse;
  unsigned long ReTriggerDelay, StartDelay,MobileOutputRunTime = SEND_MOB_US;
  

  TimeActiveSelector = EEPROM.read(EEPROM_SENSOR_TIMESACTIVE);			//variable to see if always active or times is selected
  
  LowByte  = EEPROM.read(EEPROM_SENSOR_REST_DELAY_LO);
  HighByte = EEPROM.read(EEPROM_SENSOR_REST_DELAY_HI);
  ReTriggerDelay = (HighByte << 8) | LowByte;
  Units = EEPROM.read(EEPROM_SENSOR_RESET_UNITS);
  ReTriggerDelay = formatTimeToMicro(ReTriggerDelay,Units);				//Value must be converted to us

  LowByte  = EEPROM.read(EEPROM_SHUTTERPULSE_LO);
  HighByte = EEPROM.read(EEPROM_SHUTTERPULSE_HI);
  PrimaryOutputBPulse = (HighByte << 8) | LowByte;
  Units = EEPROM.read(EEPROM_SHUTTERPULSE_UNITS);
  PrimaryOutputBPulse = formatTimeToMicro(PrimaryOutputBPulse,Units);				//Value must be converted to us
  
  PrimaryOutputADelay = 0;
  PrimaryOutputBDelay = 0;
   
  LowByte  =  EEPROM.read(EEPROM_CAMERAPREFOCUS_LO);
  HighByte =  EEPROM.read(EEPROM_CAMERAPREFOCUS_HI);
  PrimaryOutputBDelay = (HighByte << 8) | LowByte;	// 
  Units = EEPROM.read(EEPROM_CAMERAPREFOCUS_UNITS);
  PrimaryOutputBDelay = formatTimeToMicro(PrimaryOutputBDelay,Units);				//Value must be converted to us
  
  LowByte =  EEPROM.read(EEPROM_SENSOR_TRIGDELAY_LO);
  HighByte =  EEPROM.read(EEPROM_SENSOR_TRIGDELAY_HI);
  TriggerDelay = (HighByte << 8) | LowByte;		
  Units = EEPROM.read(EEPROM_SENSOR_TRIGDELAY_UNITS);
  TriggerDelay = formatTimeToMicro(TriggerDelay,Units);					//Value must be converted to us  

  StartDelayLow  =  EEPROM.read(EEPROM_SENSOR_TRIGDELAY_LO);
  StartDelayHigh =  EEPROM.read(EEPROM_SENSOR_TRIGDELAY_HI);
  StartDelay = (StartDelayHigh << 8) | StartDelayLow;											
  StartDelayUnits = EEPROM.read(EEPROM_SENSOR_TRIGDELAY_UNITS);
  StartDelay = formatTime(StartDelay, StartDelayUnits);	
  
  MobIn = EEPROM.read(EEPROM_SENSOR_MOBILEIP);
  MobOut = EEPROM.read(EEPROM_SENSOR_MOBILEOP);

  if(!MobIn)
  {
	  TriggerInputsignal = BOTH_TRIGGERS;
  }
  
  else
  {
	  TriggerInputsignal = STACK_TRIGGER_ONLY;
  }		
  
	
 ////////////////////////////////////////

	if (!TimeActiveSelector)
	{
	
		while(!(time_active(EEPROM_SENSOR_START_HOURS,EEPROM_SENSOR_END_HOURS)))	//while not in time, wait here
		{
			  if(GetButton() == KEY_MINUS)
				{
					digitalWrite(Focus, 0);
					digitalWrite(Trigger, 0);
					digitalWrite(CAMERAOUT2_A,0);	//trigger flash
					digitalWrite(CAMERAOUT2_B,0);	//
					mobile_trigger_off();
					StackPowerDown();
					return ST_SENSOR_START;
				}
		}

	}
	
	CurrentTime = CurrentTimeSelector(StartDelayUnits);

	StartTime = CurrentTime();
	ElapsedTime = 0;
	
	while(StartDelay >= ElapsedTime)
	{
		ElapsedTime = CurrentTime() - StartTime;			//how much time has passed?
		
		if(GetButton() == KEY_MINUS)
		{
	 	 	digitalWrite(Focus, 0);
	 	 	digitalWrite(Trigger, 0);
	 	 	digitalWrite(CAMERAOUT2_A,0);	//trigger flash
	 	 	digitalWrite(CAMERAOUT2_B,0);	//
			mobile_trigger_off();
	 	 	StackPowerDown();
			return ST_SENSOR_START;
		}
		
	}
	

	ElapsedTime = 0;

while(1)
{
	
	if (!TimeActiveSelector)
	{
	
		while(!(time_active(EEPROM_SENSOR_START_HOURS,EEPROM_SENSOR_END_HOURS)))	//while not in time, wait here
		{
			  if(GetButton() == KEY_MINUS)
				{
					digitalWrite(Focus, 0);
					digitalWrite(Trigger, 0);
					digitalWrite(CAMERAOUT2_A,0);	//trigger flash
					digitalWrite(CAMERAOUT2_B,0);	//
					mobile_trigger_off();
					StackPowerDown();
					return ST_SENSOR_START;
				}
		}

	}

	PrimaryOutputAServiced = false;
	PrimaryOutputBServiced = false;
	MobileOutputServiced = MobOut;
	ReTriggerServiced = false;				
	
	

switch (TriggerInputsignal)			//Trigger signals must be received as fast possible, switch case avoids wasting time checking for an input that is not required
{
	
	case STACK_TRIGGER_ONLY:	
	
		while(digitalRead(Stack) == 1)
			{
				if(GetButton() == KEY_MINUS)
				{
	 	 			digitalWrite(Focus, 0);
	 	 			digitalWrite(Trigger, 0);
	 	 			digitalWrite(CAMERAOUT2_A,0);	//trigger flash
	 	 			digitalWrite(CAMERAOUT2_B,0);	//
					mobile_trigger_off();
	 	 			StackPowerDown();
					return ST_SENSOR_START;
				}
			}
		
		break;
		
	case MOBILE_TRIGGER_ONLY:
		
		//Read only the mobile input here
		while(AUDIO_READ() == 0)
			{
				if(GetButton() == KEY_MINUS)
				{
	 	 			digitalWrite(Focus, 0);
	 	 			digitalWrite(Trigger, 0);
	 	 			digitalWrite(CAMERAOUT2_A,0);	//trigger flash
	 	 			digitalWrite(CAMERAOUT2_B,0);	//
					mobile_trigger_off();
	 	 			StackPowerDown();
					return ST_SENSOR_START;
				}
			}
			
		break;
		
	case BOTH_TRIGGERS:
	
		//Read both inputs here
		while((AUDIO_READ() == 0) && (digitalRead(Stack) == 1))
			{
				if(GetButton() == KEY_MINUS)
				{
	 	 			digitalWrite(Focus, 0);
	 	 			digitalWrite(Trigger, 0);
	 	 			digitalWrite(CAMERAOUT2_A,0);	//trigger flash
	 	 			digitalWrite(CAMERAOUT2_B,0);	//
					mobile_trigger_off();
	 	 			StackPowerDown();
					return ST_SENSOR_START;
				}
			}
		break;
	
	default:
		//something has gone wrong if we get here! 
		break;	
}
	

	

	if(TriggerDelay)
	{
		StartTime = micros();
		ElapsedTime = 0;
		while(ElapsedTime <= TriggerDelay)
		{
			ElapsedTime = micros() - StartTime;			//how much time has passed?

			if(GetButton() == KEY_MINUS)
			{
	 	 		digitalWrite(Focus, 0);
	 	 		digitalWrite(Trigger, 0);
	 	 		digitalWrite(CAMERAOUT2_A,0);	//trigger flash
	 	 		digitalWrite(CAMERAOUT2_B,0);	//
				mobile_trigger_off();
	 	 		StackPowerDown();
				return ST_SENSOR_START;
			}

		}

	}


	StartTime = micros();
	
	
	while(!(PrimaryOutputAServiced && PrimaryOutputBServiced && MobileOutputServiced && ReTriggerServiced))							//not all of the conditions have been met
	{
		
		ElapsedTime = micros() - StartTime;			//how much time has passed?
		

		if((ElapsedTime >= PrimaryOutputADelay) && (!PrimaryOutputAServiced)) //has enough time passed before we should trigger the second output, Channel A?
		{
			digitalWrite(Focus,1);												//yes, it has, turn on the focus line to the camera
			digitalWrite(CAMERAOUT2_A, 1);
			digitalWrite(CAMERAOUT3_A, 1);
			PrimaryOutputAServiced = true;
		}

		if((ElapsedTime >= PrimaryOutputBDelay) && (!PrimaryOutputBServiced)) //has enough time passed before we should trigger the second output, Channel A?
		{
			digitalWrite(Trigger, 1);										  //yes, it has
			digitalWrite(CAMERAOUT2_B, 1);
			digitalWrite(CAMERAOUT3_B, 1);
			
			if(ElapsedTime >= (PrimaryOutputBDelay + PrimaryOutputBPulse))	  //has enough time passed for the pulse time for this channel?
			{
				digitalWrite(Trigger,0);				//yes, all off and mark that this routine need not be entered again
				digitalWrite(CAMERAOUT2_A, 0);
				digitalWrite(CAMERAOUT3_A, 0);
				digitalWrite(Focus,0);
				digitalWrite(CAMERAOUT2_B, 0);
				digitalWrite(CAMERAOUT3_B, 0);
				PrimaryOutputBServiced = true;								  //yes, it has, turn off and mark complete
			}

		}

		if((ElapsedTime >= MobileOutputDelay) && (!MobileOutputServiced))   //has enough time passed before we should trigger the mobile?
		{
			//mobile trigger here!
			mobile_trigger_on();
						
			if((ElapsedTime >= (MobileOutputDelay + MobileOutputRunTime)) && (!MobileOutputServiced))   //has enough time passed before we should trigger the mobile?
			{
				//mobile trigger off here!
				mobile_trigger_off();
				MobileOutputServiced = true;
			}
			
		}
		
		if((ElapsedTime >= ReTriggerDelay) && (!ReTriggerServiced))			//has enough time passed before a re-trigger?
		{
			ReTriggerServiced = true;										
		}																	
		
		
		if(GetButton() == KEY_MINUS)
		{
	 	 	digitalWrite(Focus, 0);
	 	 	digitalWrite(Trigger, 0);
	 	 	digitalWrite(CAMERAOUT2_A,0);	//trigger flash
	 	 	digitalWrite(CAMERAOUT2_B,0);	//
			mobile_trigger_off();
	 	 	StackPowerDown();
			return	ST_SENSOR_START;
		}
	}
	
	delay(100);
}	  
	

	digitalWrite(Focus, 0);
	digitalWrite(Trigger, 0);
	digitalWrite(CAMERAOUT2_A,0);	//trigger flash
	digitalWrite(CAMERAOUT2_B,0);	//
	StackPowerDown();
	mobile_trigger_off();
	guimenu_operation_complete(GUIMENU_SENSOR_STOP_PAGE, &input_key);
    return ST_SENSOR_START;
  
    
}


char SensorConfigure (char input)
{
	char return_state = SensorSettlingDelay (GUIMENU_SENSOR_CONFIG_PAGE, ST_SENSOR_STOP, ST_SENSOR_START , EEPROM_SENSOR_TRIGGERON);
	
	return return_state;
}

char SensorTriggerDelay(char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_SENSOR_TRIGGER_DELAY_PAGE, &input_key);

	while (!next_state)
	{
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_SENSOR_START;
			break;
			
			case KEY_DOWN:
			next_state = ST_SENSOR_RESET_DELAY;
			break;
		}
		
		input_key = GetButton();
	}
	
	return next_state;
}
char SensorResetDelay(char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_SENSOR_RESET_DELAY_PAGE, &input_key);

	while (!next_state)
	{
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_SENSOR_TRIGGER_DELAY;
			break;
			
			case KEY_DOWN:
			next_state = ST_SENSOR_TRIGGER_ON;
			break;
		}
		
		input_key = GetButton();
	}
	
	return next_state;
}
char SensorTriggerOn(char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_SENSOR_TIRGGER_ON_PAGE, &input_key);

	while (!next_state)
	{
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_SENSOR_RESET_DELAY;
			break;
			
			case KEY_DOWN:
			next_state = ST_SENSOR_MOBILE_INPUT;
			break;
		}
		
		input_key = GetButton();
	}
	
	return next_state;
}
char SensorMobileInput(char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_SENSOR_MOBILE_INPUT_PAGE, &input_key);

	while (!next_state)
	{
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_SENSOR_TRIGGER_ON;
			break;
			
			case KEY_DOWN:
			next_state = ST_SENSOR_MOBILE_OUTPUT;
			break;
		}
		
		input_key = GetButton();
	}
	
	return next_state;
}


char SensorMobileOutput(char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_SENSOR_MOBILE_OUTPUT_PAGE, &input_key);

	while (!next_state)
	{
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_SENSOR_MOBILE_INPUT;
			break;
			
			case KEY_DOWN:
			next_state = ST_SENSOR_TIME_ACTIVE;
			break;
		}
		
		input_key = GetButton();
	}
	
	return next_state;
}


char SensorTimeActive(char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_SENSOR_TIME_ACTIVE_PAGE, &input_key);

	while (!next_state)
	{
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_SENSOR_MOBILE_OUTPUT;
			break;
			
			case KEY_DOWN:
			next_state = ST_SENSOR_START_TIME;
			break;
		}
		
		
		input_key = GetButton();
	}
	
	return next_state;
}


char SensorStartTime(char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_SENSOR_START_TIME_PAGE, &input_key);

	while (!next_state)
	{
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_SENSOR_TIME_ACTIVE;
			break;
			
			case KEY_DOWN:
			next_state = ST_SENSOR_STOP_TIME;
			break;
		}
		
		input_key = GetButton();
	}
	
	return next_state;
}


char SensorStopTime(char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_SENSOR_STOP_TIME_PAGE, &input_key);

	while (!next_state)
	{
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_SENSOR_START_TIME;
			break;
			
			case KEY_DOWN:
			next_state = ST_SENSOR_STOP_TIME;
			break;
		}
		
		input_key = GetButton();
	}
	
	return next_state;
}

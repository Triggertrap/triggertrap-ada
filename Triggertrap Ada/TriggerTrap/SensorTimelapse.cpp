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
*   Function name : SensorTimeLapse
*
*   Returns :       Next state
*
*   Parameters :
*
*   Purpose :
*
*****************************************************************************/



char SensorTimeLapse(char input)
{
 unsigned char HighByte,LowByte,StartDelayUnits,TimelapseContinue;
 unsigned char SensorStop = 0;
 unsigned int TimelapseCount = 0;
 unsigned long PrimaryOutputAPulse;
 unsigned long ElapsedTime, StartTime;
 unsigned long PrimaryOutputADelay;
 unsigned char TriggerInputsignal,Units,MobInDisabled,TimeActiveSelector,IntervalUnits;
 unsigned long SecondaryOutputADelay = 0, SecondaryOutputBDelay = 0, MobileOutputDelay = 0, StartTimeMillis, ElapsedTimeMillis;
 unsigned long SecondaryOutputAPulse = 0, SecondaryOutputBPulse = 0, StartDelay,MobileOutputRunTime = SEND_MOB_MS,TimeLapseIntervalTime;
 unsigned long (*CurrentTime)(void),TotalSecondaryADelay,TotalSecondaryBDelay, PrimaryOutputBDelay,PrimaryOutputBPulse = 0,TotalPrimaryADelay,TotalPrimaryBDelay;
																																					
 struct  SpaceSaverA
 {
	uint8_t PrimaryOutputAServiced : 1;
	uint8_t SecondaryOutputAServiced : 1;
	uint8_t TertiaryOutputAServiced : 1;
	uint8_t MobileOutputServiced : 1;
	uint8_t InfiniteEnabled : 1;
	uint8_t ContinueTimelapse : 1;
 };

 struct  SpaceSaverB
 {
	uint8_t MobOut : 1;
	uint8_t PrimaryOutputBServiced : 1;
	uint8_t stackConfiguration : 1;
	uint8_t PrimaryOutputServiced : 1;
	uint8_t SecondaryOutputBServiced : 1;
	uint8_t TertiaryOutputBServiced : 1;
 };
 
 SpaceSaverA	ServiceFlagsA;
 SpaceSaverB	ServiceFlagsB;
  
 TimelapseContinue  =  EEPROM.read(EEPROM_SENSORTLAPSE_CONTINUE);
 
 switch (TimelapseContinue)
 {
 case 0:					//sen stop
	SensorStop = 1;
	ServiceFlagsA.InfiniteEnabled = 1;
 	break;
	 
 case 1:					//inf
	SensorStop = 0;
	ServiceFlagsA.InfiniteEnabled = 1;
 	break;
	 
 case 2:					//x shots
 	SensorStop = 0;
	ServiceFlagsA.InfiniteEnabled = 0;
	LowByte =  EEPROM.read(EEPROM_SENSORTLAPSE_CONTINUE_LO);
	HighByte =  EEPROM.read(EEPROM_SENSORTLAPSE_CONTINUE_HI);
	TimelapseCount = (HighByte << 8) | LowByte;
 	break;
	 
 } 
 
 TimeActiveSelector = EEPROM.read(EEPROM_SENSORTLAPSE_TIMESACTIVE);			//variable to see if always active or times is selected

 LowByte  =  EEPROM.read(EEPROM_SENSORTLAPSE_INTERVAL_LO);
 HighByte =  EEPROM.read(EEPROM_SENSORTLAPSE_INTERVAL_HI);
 TimeLapseIntervalTime = (HighByte << 8) | LowByte;				
 IntervalUnits = EEPROM.read(EEPROM_SENSORTLAPSE_INTERVAL_UNITS);
 TimeLapseIntervalTime = formatTimeToMillis (TimeLapseIntervalTime,IntervalUnits);
 

 LowByte  =  EEPROM.read(EEPROM_CAMERAPREFOCUS_LO);
 HighByte =  EEPROM.read(EEPROM_CAMERAPREFOCUS_HI);
 PrimaryOutputADelay = (HighByte << 8) | LowByte;
 Units = EEPROM.read(EEPROM_CAMERAPREFOCUS_UNITS);
 PrimaryOutputADelay = formatTimeToMillis(PrimaryOutputADelay,Units);
 

 LowByte  =  EEPROM.read(EEPROM_SHUTTERPULSE_LO);
 HighByte =  EEPROM.read(EEPROM_SHUTTERPULSE_HI);
 PrimaryOutputAPulse = (HighByte << 8) | LowByte;		
 Units = EEPROM.read(EEPROM_SHUTTERPULSE_UNITS);
 PrimaryOutputAPulse = formatTimeToMillis(PrimaryOutputAPulse,Units);

 PrimaryOutputBDelay = 0;
 
 LowByte  =  EEPROM.read(EEPROM_SENSORTLAPSE_DELAY_LO);
 HighByte =  EEPROM.read(EEPROM_SENSORTLAPSE_DELAY_HI);
 StartDelay = (HighByte << 8) | LowByte;											
 StartDelayUnits = EEPROM.read(EEPROM_SENSORTLAPSE_DELAY_UNITS);
 StartDelay = formatTime(StartDelay, StartDelayUnits);
 
 TotalPrimaryADelay = (PrimaryOutputAPulse + PrimaryOutputADelay);
 TotalPrimaryBDelay = (PrimaryOutputBPulse + PrimaryOutputBDelay);
 TotalSecondaryADelay = (SecondaryOutputADelay + SecondaryOutputAPulse);
 TotalSecondaryBDelay = (SecondaryOutputBDelay + SecondaryOutputBPulse);
 
 if(TimeLapseIntervalTime <= TotalPrimaryADelay)
 {
	return SettingError(ST_SEN_TL_START); 
 }
 else if (TimeLapseIntervalTime <= TotalPrimaryBDelay)
 {
	 return SettingError(ST_SEN_TL_START);
 }
 else if (TimeLapseIntervalTime <= TotalSecondaryADelay)
 {
	return SettingError(ST_SEN_TL_START); 
 }
 else if (TimeLapseIntervalTime <= TotalSecondaryBDelay)
 {
	return SettingError(ST_SEN_TL_START); 
 }

 
 ServiceFlagsB.MobOut = EEPROM.read(EEPROM_SENSORTLAPSE_MOBILEOP);
 
 MobInDisabled = EEPROM.read(EEPROM_SENSORTLAPSE_MOBILEIP);
 
 if(MobInDisabled)
 {
	 TriggerInputsignal = STACK_TRIGGER_ONLY;
 }
 else
 {
	 TriggerInputsignal = BOTH_TRIGGERS;
 }
 
 

  StartTime = millis();
  ElapsedTime = 0;

 
////////////////////////////////////////

 if (!TimeActiveSelector)
 {
 		
 	while(!(time_active(EEPROM_SENSOR_TL_START_HOURS,EEPROM_SENSOR_TL_END_HOURS)))	//while not in time, wait here
 	{
 		if(GetButton() == KEY_MINUS)
 		{
	 	 	digitalWrite(Focus, 0);
	 	 	digitalWrite(Trigger, 0);
	 	 	digitalWrite(CAMERAOUT2_A,0);	//trigger flash
	 	 	digitalWrite(CAMERAOUT2_B,0);	//
			mobile_trigger_off();
	 	 	StackPowerDown();
 			return ST_SEN_TL_START;
 		}
 	}
 
 }
 

 
 CurrentTime = CurrentTimeSelector(StartDelayUnits);

 StartTime = CurrentTime();
 ElapsedTime = 0;

 
 while(StartDelay > ElapsedTime)
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
		 return ST_SEN_TL_START;
	 }
	 
 }
 

 ElapsedTime = 0;

	ServiceFlagsA.ContinueTimelapse = true;  
	ServiceFlagsA.PrimaryOutputAServiced = false;
	ServiceFlagsB.PrimaryOutputBServiced = false;
	ServiceFlagsA.MobileOutputServiced = ServiceFlagsB.MobOut;

	 
	switch (TriggerInputsignal)			//Trigger signals must be received as fast possible, switch case avoids wasting time checking for an input that is not required
	{ 
		case STACK_TRIGGER_ONLY:
			while (digitalRead(Stack) == 1)
			{
				if (GetButton() == KEY_MINUS)
				{
					digitalWrite(Focus, 0);
					digitalWrite(Trigger, 0);
					digitalWrite(CAMERAOUT2_A, 0);
					digitalWrite(CAMERAOUT2_B, 0);
					digitalWrite(CAMERAOUT3_A, 0);
					digitalWrite(CAMERAOUT3_B, 0);
					mobile_trigger_off();
					StackPowerDown();
					return	ST_SEN_TL_START;
				}
			}
		break;
		 
		case MOBILE_TRIGGER_ONLY:	 
		 //Read only the mobile input here
			while (AUDIO_READ() == 0)
			{
				if (GetButton() == KEY_MINUS)
				{
					digitalWrite(Focus, 0);
					digitalWrite(Trigger, 0);
					digitalWrite(CAMERAOUT2_A, 0);
					digitalWrite(CAMERAOUT2_B, 0);
					digitalWrite(CAMERAOUT3_A, 0);
					digitalWrite(CAMERAOUT3_B, 0);
					mobile_trigger_off();
					StackPowerDown();
					return	ST_SEN_TL_START;
				}
			}
		break;
		 
		case BOTH_TRIGGERS:
			//Read both inputs here
			while ((AUDIO_READ() == 0) && (digitalRead (Stack) == 1))
			{
				if (GetButton() == KEY_MINUS)
				{
					digitalWrite(Focus, 0);
					digitalWrite(Trigger, 0);
					digitalWrite(CAMERAOUT2_A, 0);
					digitalWrite(CAMERAOUT2_B, 0);
					digitalWrite(CAMERAOUT3_A, 0);
					digitalWrite(CAMERAOUT3_B, 0);
					mobile_trigger_off();
					StackPowerDown();
					return	ST_SEN_TL_START;
				}
			}
		break;
		 
		default:
			digitalWrite(STACK_PWR, 0);	//turn power to the stack on
			//something has gone wrong if we get here!
		break;
	}

	while ((TimelapseCount || ServiceFlagsA.InfiniteEnabled) && ServiceFlagsA.ContinueTimelapse)		//Stay in this loop until we have finished our timelapse count
	{
		if (!TimeActiveSelector)
		{
			while (!(time_active(EEPROM_SENSOR_TL_START_HOURS,EEPROM_SENSOR_TL_END_HOURS)))	//while not in time, wait here
			{
				if (GetButton() == KEY_MINUS)
				{
					digitalWrite(Focus, 0);
					digitalWrite(Trigger, 0);
					digitalWrite(CAMERAOUT2_A, 0);
					digitalWrite(CAMERAOUT2_B, 0);
					digitalWrite(CAMERAOUT3_A, 0);
					digitalWrite(CAMERAOUT3_B, 0);
					mobile_trigger_off();
					StackPowerDown();
					return	ST_SEN_TL_START;
				}
			}
		}

		//RESET ALL VARIABLES HERE
		ServiceFlagsA.PrimaryOutputAServiced = false;
		ServiceFlagsB.PrimaryOutputBServiced = false;
		ServiceFlagsA.MobileOutputServiced = ServiceFlagsB.MobOut;
	 	
		 // PreFocus	
		digitalWrite(Focus,1);												
		digitalWrite(CAMERAOUT2_A, 1);
		digitalWrite(CAMERAOUT3_A, 1);
			 
		StartTime = millis();	 
			
		while (!(ServiceFlagsA.PrimaryOutputAServiced && ServiceFlagsA.MobileOutputServiced))
		{ 
			ElapsedTime = millis() - StartTime;			//how much time has passed?
				
			if ((ElapsedTime >= PrimaryOutputADelay) && (!ServiceFlagsA.PrimaryOutputAServiced)) //has enough time passed before we should trigger the second output, Channel A?
			{
				digitalWrite(Trigger, 1);										  //yes, it has
				digitalWrite(CAMERAOUT2_B, 1);
				digitalWrite(CAMERAOUT3_B, 1);
			
				if (ElapsedTime >= (PrimaryOutputADelay + PrimaryOutputAPulse))	  //has enough time passed for the pulse time for this channel?
				{
					digitalWrite(Trigger,0);				//yes, all off and mark that this routine need not be entered again
					digitalWrite(CAMERAOUT2_A, 0);
					digitalWrite(CAMERAOUT3_A, 0);
					digitalWrite(Focus,0);
					digitalWrite(CAMERAOUT2_B, 0);
					digitalWrite(CAMERAOUT3_B, 0);
					ServiceFlagsA.PrimaryOutputAServiced = true;								  //yes, it has, turn off and mark complete
				}

			}

			if ((ElapsedTime >= MobileOutputDelay) && (!ServiceFlagsA.MobileOutputServiced))   //has enough time passed before we should trigger the mobile?
			{
				mobile_trigger_on();
			 
				if((ElapsedTime >= (MobileOutputDelay + MobileOutputRunTime)) && (!ServiceFlagsA.MobileOutputServiced))   //has enough time passed before we should trigger the mobile?
				{
					mobile_trigger_off();
					ServiceFlagsA.MobileOutputServiced = true;
				}
			 
			}
		 

			if (GetButton() == KEY_MINUS)
			{
				digitalWrite(Focus, 0);
				digitalWrite(Trigger, 0);
				digitalWrite(CAMERAOUT2_A, 0);
				digitalWrite(CAMERAOUT2_B, 0);
				digitalWrite(CAMERAOUT3_A, 0);
				digitalWrite(CAMERAOUT3_B, 0);
				mobile_trigger_off();
				StackPowerDown();
				return ST_SEN_TL_START;
			}
			 
			if (SensorStop)
			{
				if (digitalRead(Stack))		//stop when the sensor stops triggering
				{
					ServiceFlagsA.ContinueTimelapse = false;
				}
			}
		}
		 
		guimenu_displaypage (GUIMENU_SENTLAPSE_PROG_PAGE);
		 
		StartTimeMillis = millis();
		ElapsedTimeMillis = 0;
		
		if (IntervalUnits >= GUIMENU_UNITS_S)
		{
			guimenu_progressbar_start (GUIMENU_SENTLAPSE_PROG_PAGE, (uint32_t)TimeLapseIntervalTime, IntervalUnits,0);
		}

		TimelapseCount <= 0 ? TimelapseCount = 0 : TimelapseCount--;      //Do not decrement past 0
		
		if (TimelapseCount || TimelapseContinue <= 1)
		{
			while (TimeLapseIntervalTime > ElapsedTimeMillis)		//wait here until the interval delay has passed
			{
				ElapsedTimeMillis = millis() - StartTimeMillis;			//how much time has passed?
				
				if (TimeLapseIntervalTime > ElapsedTimeMillis)
				{
					guimenu_progressbar_update((TimeLapseIntervalTime - ElapsedTimeMillis), 0);
				}
				else
				{
					guimenu_progressbar_update(0, 0);
				}
			
				if (SensorStop)
				{
					if (digitalRead(Stack) || (!MobInDisabled && (AUDIO_READ() <= 5)))			//if stack sensor or mobile trigger (if enabled)
					{
						ServiceFlagsA.ContinueTimelapse = false;
						ElapsedTimeMillis = TimeLapseIntervalTime + 1;	//Get out of loop
					}
				}
			
				if (GetButton() == KEY_MINUS)
				{
					digitalWrite(Focus, 0);
					digitalWrite(Trigger, 0);
					digitalWrite(CAMERAOUT2_A, 0);
					digitalWrite(CAMERAOUT2_B, 0);
					digitalWrite(CAMERAOUT3_A, 0);
					digitalWrite(CAMERAOUT3_B, 0);
					mobile_trigger_off();
					StackPowerDown();
					return ST_SEN_TL_START;
				}
			
			}
		}

		if (!TimeActiveSelector)
		{
			while(!(time_active(EEPROM_SENSOR_TL_START_HOURS,EEPROM_SENSOR_TL_END_HOURS)))	//while not in time, wait here
			{
				if(GetButton() == KEY_MINUS)
				{
					digitalWrite(Focus, 0);
					digitalWrite(Trigger, 0);
					digitalWrite(CAMERAOUT2_A, 0);
					digitalWrite(CAMERAOUT2_B, 0);
					digitalWrite(CAMERAOUT3_A, 0);
					digitalWrite(CAMERAOUT3_B, 0);
					mobile_trigger_off();
					StackPowerDown();
					return	ST_SEN_TL_START;
				}
			}
			//RESET ALL VARIABLES HERE
		}
		
		
		ElapsedTime = 0;
	 }	//end timelapse while loop
	 
	 
	 digitalWrite(Focus, 0);
	 digitalWrite(Trigger, 0);
	 digitalWrite(CAMERAOUT2_A, 0);
	 digitalWrite(CAMERAOUT2_B, 0);
	 digitalWrite(CAMERAOUT3_A, 0);
	 digitalWrite(CAMERAOUT3_B, 0);
	 mobile_trigger_off();
	 StackPowerDown();
	 guimenu_operation_complete(GUIMENU_SENTLAPSE_PROG_PAGE, &input_key);
	 return ST_SEN_TL_START;
}


char SensorTLConfigure (char input)
{
	char return_state = SensorSettlingDelay (GUIMENU_SENSORTLAPSE_CONFIG_PAGE, ST_SEN_TL_STOP, ST_SEN_TL_START , EEPROM_SENSORTLAPSE_TRIGGERON);
	
	return return_state;
}


char Sensor_TL_Delay (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_SENSOR_TL_DELAY_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_SEN_TL_START;
			break;
			
			case KEY_DOWN:
			next_state = ST_SEN_TL_INTERVAL;
			break;
			
			default:
			next_state = 0;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}

char Sensor_TL_Interval (char input)
{
	char next_state = 0;

	guimenu_selector (GUIMENU_SENSOR_TL_INTERVAL_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_SEN_TL_DELAY;
			break;
			
			case KEY_DOWN:
			next_state = ST_SEN_TL_CONTINUE_SET;
			break;
			
			default:
			next_state = 0;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}

char Sensor_TL_Continue (char input)
{
	char next_state = 0;

	guimenu_selector (GUIMENU_SENSOR_TL_CONTINUE_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_SEN_TL_CONTINUE_SET;
			break;
			
			case KEY_DOWN:
			next_state = ST_SEN_TL_TRIGGER;
			break;
			
			default:
			next_state = 0;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}

char Sensor_TL_Trigger (char input)
{
	char next_state = 0;

	guimenu_selector (GUIMENU_SENSOR_TL_TRIGGER_ON_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_SEN_TL_CONTINUE;
			break;
			
			case KEY_DOWN:
			next_state = ST_SEN_TL_MOBILE_INPUT;
			break;
			
			default:
			next_state = 0;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}

char Sensor_TL_MobileInput (char input)
{
	char next_state = 0;

	guimenu_selector (GUIMENU_SENSOR_TL_MOBILE_INPUT_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_SEN_TL_TRIGGER;
			break;
			
			case KEY_DOWN:
			next_state = ST_SEN_TL_MOBILE_OUTPUT;
			break;
			
			default:
			next_state = 0;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}

char Sensor_TL_MobileOutput (char input)
{
	char next_state = 0;

	guimenu_selector (GUIMENU_SENSOR_TL_MOBILE_OUTPUT_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_SEN_TL_MOBILE_INPUT;
			break;
			
			case KEY_DOWN:
			next_state = ST_SEN_TL_TIME_ACTIVE;
			break;
			
			default:
			next_state = 0;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}

char Sensor_TL_TimeActive (char input)
{
	char next_state = 0;

	guimenu_selector (GUIMENU_SENSOR_TL_TIME_ACTIVE_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_SEN_TL_MOBILE_OUTPUT;
			break;
			
			case KEY_DOWN:
			next_state = ST_SEN_TL_START_TIME;
			break;
			
			default:
			next_state = 0;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}

char Sensor_TL_StartTime (char input)
{
	char next_state = 0;

	guimenu_selector (GUIMENU_SENSOR_TL_START_TIME_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_SEN_TL_TIME_ACTIVE;
			break;
			
			case KEY_DOWN:
			next_state = ST_SEN_TL_STOP_TIME;
			break;
			
			default:
			next_state = 0;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}

char Sensor_TL_StopTime (char input)
{
	char next_state = 0;

	guimenu_selector (GUIMENU_SENSOR_TL_STOP_TIME_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_SEN_TL_START_TIME;
			break;
			
			case KEY_DOWN:
			next_state = ST_SEN_TL_STOP_TIME;
			break;
			
			default:
			next_state = 0;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}

char Sensor_TL_Continue_Set (char input)
{
	char next_state = 0;

	guimenu_selector (GUIMENU_SENSOR_TL_CONTINUE_SET_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_SEN_TL_INTERVAL;
			break;
			
			case KEY_DOWN:
			next_state = ST_SEN_TL_CONTINUE;
			break;
			
			default:
			next_state = 0;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}

char SettingError (char State)
{
	unsigned long StartTime,ElapsedTime;
	
while(1)
{
	 StartTime = millis();
	 ElapsedTime = 0;
	 
	 digitalWrite(BackLight,!digitalRead(BackLight));	//toggle back light every half second to show error
	 
	 while(500 > ElapsedTime)
	 {
		 ElapsedTime = millis() - StartTime;			//how much time has passed?
	 
		 if(GetButton() == KEY_MINUS)
		 {
			 digitalWrite(BackLight,1);
			 return State;
		 }
	 
	 }
}
 
}

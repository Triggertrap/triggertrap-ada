#include <stdlib.h>
#include "MenuDefines.h"
#include "Arduino.h"
#include "HardwareGlobals.h"
#include "guimenu.h"
#include "Menu.h"
#include "eeprom_addresses.h"
#include "Inputs.h"
#include "EEPROM.h"

extern "C" {
#include "timing.h"
}

static uint8_t input_key;

unsigned long (*CurrentTimeSelector (unsigned char Units))(void);

/*****************************************************************************
*
*   Function name : TimeLapse
*
*   Returns :       next state
*
*   Parameters :
*
*   Purpose :
*
*****************************************************************************/

char Timelapse_new(char input)
{
	unsigned char LowByte, HighByte,Units,StartDelayUnits,IntervalUnits;
	unsigned char TimeActiveSelector;
	int TimelapseCount;
	bool PrimaryOutputServiced, PrimaryOutputPreFocusServiced;
	unsigned long PrimaryOutputDelay = 0, PrimaryOutputPreFocus, PrimaryOutputPulse, ElapsedTime = 0, LastUpdate, StartTime;
	unsigned long TimeLapseIntervalTime, StartDelay;
	unsigned long (*CurrentTime)(void);
	bool InfiniteEnabled;
	
 	LowByte =  EEPROM.read(EEPROM_TIMELAPSE_COUNT_LO);
	HighByte =  EEPROM.read(EEPROM_TIMELAPSE_COUNT_HI);
	TimelapseCount = (HighByte << 8) | LowByte;		

	 if(TimelapseCount >= GUIMENU_INFINITE_VALUE)
	 {
		 InfiniteEnabled = true;
	 }
	 
	 else
	 {
		 InfiniteEnabled = false;
	 }
	  	
	LowByte  =  EEPROM.read(EEPROM_CAMERAPREFOCUS_LO);
	HighByte =  EEPROM.read(EEPROM_CAMERAPREFOCUS_HI);
	PrimaryOutputDelay = (HighByte << 8) | LowByte;	
	Units = EEPROM.read(EEPROM_CAMERAPREFOCUS_UNITS);
	PrimaryOutputDelay = formatTimeToMillis(PrimaryOutputDelay,Units);				//Value must be converted to us
	
	PrimaryOutputPreFocus = 0;
	
	LowByte  =  EEPROM.read(EEPROM_SHUTTERPULSE_LO);
	HighByte =  EEPROM.read(EEPROM_SHUTTERPULSE_HI);
	PrimaryOutputPulse = (HighByte << 8) | LowByte;		
	Units = EEPROM.read(EEPROM_SHUTTERPULSE_UNITS);
	PrimaryOutputPulse = formatTimeToMillis(PrimaryOutputPulse,Units);					//Value must be converted to us
		
	LowByte  =  EEPROM.read(EEPROM_TIMELAPSE_STARTDELAY_LO);
	HighByte =  EEPROM.read(EEPROM_TIMELAPSE_STARTDELAY_HI);
	StartDelay = (HighByte << 8) | LowByte;											
	StartDelayUnits = EEPROM.read(EEPROM_TIMELAPSE_STARTDELAY_UNITS);
	StartDelay = formatTime(StartDelay, StartDelayUnits);										//Value must be converted so as the correct delay can be used
	
	LowByte  =  EEPROM.read(EEPROM_TIMELAPSE_INTERVAL_LO);
	HighByte =  EEPROM.read(EEPROM_TIMELAPSE_INTERVAL_HI);
	TimeLapseIntervalTime = (HighByte << 8) | LowByte;			
	IntervalUnits = EEPROM.read(EEPROM_TIMELAPSE_INTERVAL_UNITS);
	TimeLapseIntervalTime = formatTimeToMillis(TimeLapseIntervalTime,IntervalUnits);
	
	TimeActiveSelector = EEPROM.read(EEPROM_TIMELAPSE_ACTIVE);			//variable to see if always active or times is selected



	if (!TimeActiveSelector)
	{
	
		while(!(time_active(EEPROM_TIMELAPSE_STARTHOURS,EEPROM_TIMELAPSE_ENDHOURS)))	//while not in time, wait here
		{
			  if(GetButton() == KEY_MINUS)
				{
					digitalWrite(Focus, 0);
					digitalWrite(Trigger, 0);
					digitalWrite(CAMERAOUT2_A, 0);
					digitalWrite(CAMERAOUT2_B, 0);
					digitalWrite(CAMERAOUT3_A, 0);
					digitalWrite(CAMERAOUT3_B, 0);
					digitalWrite(STACK_PWR, 0);	//turn power to the stack on
					return ST_TMLPSE_START;
				}
		}

	}
	CurrentTime = CurrentTimeSelector(StartDelayUnits);

	guimenu_progressbar_start (GUIMENU_TIMELAPSE_PROG_PAGE, StartDelay, StartDelayUnits, 0);

	StartTime = CurrentTime();
	
	while(StartDelay >= ElapsedTime)
	{
		ElapsedTime = CurrentTime() - StartTime;			//how much time has passed?
		
		if (ElapsedTime <= StartDelay)
		{
			guimenu_progressbar_update ((StartDelay - ElapsedTime), 0);
		}
		
		if(GetButton() == KEY_MINUS)
		{
			digitalWrite(Focus, 0);
			digitalWrite(Trigger, 0);
			digitalWrite(CAMERAOUT2_A, 0);
			digitalWrite(CAMERAOUT2_B, 0);
			digitalWrite(CAMERAOUT3_A, 0);
			digitalWrite(CAMERAOUT3_B, 0);
			digitalWrite(STACK_PWR, 0);	//turn power to the stack on
			return ST_TMLPSE_START;
		}
		
	}
	

	ElapsedTime = 0;


	while(TimelapseCount || InfiniteEnabled)		//Stay in this loop until we have finished our timelapse count
	{
		if (!TimeActiveSelector)
		{
			while(!(time_active(EEPROM_TIMELAPSE_STARTHOURS,EEPROM_TIMELAPSE_ENDHOURS)))	//while not in time, wait here
			{
					if(GetButton() == KEY_MINUS)
					{
						digitalWrite(Focus, 0);
						digitalWrite(Trigger, 0);
						digitalWrite(CAMERAOUT2_A, 0);
						digitalWrite(CAMERAOUT2_B, 0);
						digitalWrite(CAMERAOUT3_A, 0);
						digitalWrite(CAMERAOUT3_B, 0);
						return	ST_TMLPSE_START;
					}
			}
		}

		PrimaryOutputServiced = false;
		PrimaryOutputPreFocusServiced = false;
		

		/*	This part of the routine must be accurate up to a microsecond resolution. the fastest time able to be set by any channel delay is 10us
		*   The maximum is 60 seconds. as we are using unsigned long, this is acceptable to format as 60,000,000uS.
		*/

		StartTime = millis();
		CurrentTime = CurrentTimeSelector(IntervalUnits);				//For use later in the code, do it here so we have it ready and don't have to do it again
		
		
		while(!(PrimaryOutputServiced && PrimaryOutputPreFocusServiced))	
		{

			ElapsedTime = millis() - StartTime;			//how much time has passed?
		
			if((ElapsedTime >= PrimaryOutputDelay) && (!PrimaryOutputServiced)) //has enough time passed before we should trigger the second output, Channel A?
			{
				digitalWrite(Trigger, 1);										  //yes, it has
				digitalWrite(CAMERAOUT2_B, 1);
				digitalWrite(CAMERAOUT3_B, 1);
			
				if(ElapsedTime >= (PrimaryOutputDelay + PrimaryOutputPulse))	  //has enough time passed for the pulse time for this channel?
				{
					digitalWrite(Trigger, 0);
					digitalWrite(CAMERAOUT2_B, 0);
					digitalWrite(CAMERAOUT3_B, 0);
					digitalWrite(Focus, 0);
					digitalWrite(CAMERAOUT2_A, 0);
					digitalWrite(CAMERAOUT3_A, 0);
					PrimaryOutputServiced = true;								  //yes, it has, turn off and mark complete
				}

			}

			if((ElapsedTime >= PrimaryOutputPreFocus) && (!PrimaryOutputPreFocusServiced)) //has enough time passed before we should trigger the second output, Channel A?
			{
				digitalWrite(Focus, 1);										  //yes, it has
				digitalWrite(CAMERAOUT2_A, 1);
				digitalWrite(CAMERAOUT3_A, 1);
				PrimaryOutputPreFocusServiced = true;				  //mark complete

			}

			
			if(GetButton() == KEY_MINUS)
			{
				digitalWrite(Focus, 0);
				digitalWrite(Trigger, 0);
				digitalWrite(CAMERAOUT2_A, 0);
				digitalWrite(CAMERAOUT2_B, 0);
				digitalWrite(CAMERAOUT3_A, 0);
				digitalWrite(CAMERAOUT3_B, 0);
				return	ST_TMLPSE_START;
			}
			

		}

		if (TimeLapseIntervalTime >= 1000)
		{
			if (IntervalUnits < GUIMENU_UNITS_S)
			{
				IntervalUnits = GUIMENU_UNITS_S;
			}
			guimenu_progressbar_start (GUIMENU_TIMELAPSE_PROG_PAGE, (uint32_t)TimeLapseIntervalTime, IntervalUnits,0);
		}
		
		TimelapseCount--;
		StartTime = millis();
		ElapsedTime = LastUpdate = 0;
		
		if(TimelapseCount)
		{
			while(TimeLapseIntervalTime >= ElapsedTime)		//wait here until the interval delay has passed
			{
				deepSleep(0);

				ElapsedTime = millis() - StartTime;			//how much time has passed?
			
				if (ElapsedTime - LastUpdate > 1000)
				{
					LastUpdate = ElapsedTime;
					if(TimeLapseIntervalTime > ElapsedTime)
					{
						guimenu_progressbar_update((TimeLapseIntervalTime - ElapsedTime), 0);
					}
					else
					{
						guimenu_progressbar_update(0, 0);
					}
				}
			
				if(GetButton() == KEY_MINUS)
				{
					digitalWrite(Focus, 0);
					digitalWrite(Trigger, 0);
					digitalWrite(CAMERAOUT2_A, 0);
					digitalWrite(CAMERAOUT2_B, 0);
					digitalWrite(CAMERAOUT3_A, 0);
					digitalWrite(CAMERAOUT3_B, 0);
					digitalWrite(STACK_PWR, 0);	//turn power to the stack on
					return ST_TMLPSE_START;
				}
			
			}
		}

		
	}
	
	digitalWrite(Focus, 0);
	digitalWrite(Trigger, 0);
	digitalWrite(CAMERAOUT2_A, 0);
	digitalWrite(CAMERAOUT2_B, 0);
	digitalWrite(CAMERAOUT3_A, 0);
	digitalWrite(CAMERAOUT3_B, 0);
	digitalWrite(STACK_PWR, 0);	//turn power to the stack on
	guimenu_operation_complete(GUIMENU_TIMELAPSE_PROG_PAGE, &input_key);
	return ST_TMLPSE_START;
	
	
}

char TimelapseCountSet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_TIMELAPSE_COUNT_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_TMLPSE_INTERVAL;
			break;
			
			case KEY_DOWN:
			next_state = ST_TMLPSE_START_DELAY;
			break;
			
			default:
			next_state = 0;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}

char TimelapseIntervalSet (char input)
{
	char next_state = 0;
	
	
	guimenu_selector (GUIMENU_TIMELAPSE_INTERVAL_PAGE, &input_key);

	while (!next_state)
	{
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_TMLPSE_START;
			break;
			
			case KEY_DOWN:
			next_state = ST_TMLPSE_COUNT;
			break;
		}
		
		input_key = GetButton();
	}
	
	return next_state;
}

char TimelapseStartDelay (char input)
{
	char next_state = 0;

	
	guimenu_selector (GUIMENU_TIMELAPSE_START_DELAY_PAGE, &input_key);

	while (!next_state)
	{
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_TMLPSE_COUNT;
			break;
			
			case KEY_DOWN:
			next_state = ST_TMLPSE_ACTIVE;
			break;
		}
		
		input_key = GetButton();
	}
	
	return next_state;
}

char TimelapseTimeActive (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_TIMELAPSE_TIMESACTIVE_PAGE, &input_key);

	while (!next_state)
	{
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_TMLPSE_START_DELAY;
			break;
			
			case KEY_DOWN:
			next_state = ST_TMLPSE_START_TIME;
			break;
		}
		input_key = GetButton();
	}
	return next_state;
}

char TimelapseStartTime(char input)				
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_TIMELAPSE_STARTTIME_PAGE, &input_key);

	while (!next_state)
	{
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_TMLPSE_ACTIVE;
			break;
			
			case KEY_DOWN:
			next_state = ST_TMLPSE_END_TIME;
			break;
		}
		
		input_key = GetButton();
	}
	return next_state;
}

char TimelapseEndTime(char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_TIMELAPSE_ENDTIME_PAGE, &input_key);

	while (!next_state)
	{
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_TMLPSE_START_TIME;
			break;
			
			case KEY_DOWN:
			next_state = ST_TMLPSE_END_TIME;
			break;
		}
		
		input_key = GetButton();
	}
	return next_state;
}

unsigned long GetTimeMicros(void)
{
	return micros();
}

unsigned long GetTimeMillis(void)
{
	return millis();
}

unsigned long GetTimeSeconds(void)
{
	return millis();
}

unsigned long GetTimeMin(void)
{
	guimenu_time_t Time;
	
	get_time(&Time);
	
	return (unsigned long)Time.secs;
}

unsigned long GetTimeHours(void)
{
	guimenu_time_t Time;
	
	get_time(&Time);
	
	return (unsigned long)Time.mins;
}

unsigned long formatTime (unsigned long Time, char Units)
{
	
	if(Units == GUIMENU_UNITS_S)
	{
		Time = Time * 1000;				//extra resolution needed in case start is called at 0.9 sec for example.
	}
	
	else if(Units == GUIMENU_UNITS_M)
	{
		Time = Time * 60;				//extra resolution needed in case start is called at 0.9 sec for example.
	}
	
	return Time;
}

unsigned long formatTimeToMicro (unsigned long Time, char Units)
{
	
	switch (Units)
	{
		case GUIMENU_UNITS_US:
		break;
		
		case GUIMENU_UNITS_MS:
		Time = Time * 1000;
		break;
		
		case GUIMENU_UNITS_S:
		Time = Time * 1000000;
		break;
		
		default:			//Shouldn't get here, but lets protect ourselves in case we do!
		break;
	}
	
	return Time;
}

unsigned long formatTimeToMillis (unsigned long Time, char Units)
{
	
	switch (Units)
	{
		case GUIMENU_UNITS_US:
		Time = Time / 1000;
		break;
		
		case GUIMENU_UNITS_MS:
		break;
		
		case GUIMENU_UNITS_S:
		Time = Time * 1000;
		break;
		
		case GUIMENU_UNITS_M:
		Time = (Time * 60) * 1000;
		break;
		
		case GUIMENU_UNITS_H:
		Time = ((Time * 60) * 60) * 1000;
		break;
		
		default:			//Shouldn't get here, but lets protect ourselves in case we do!
		break;
	}
	
	return Time;
}

unsigned long formatTimeToSeconds (unsigned long Time, char Units)
{
	
	switch (Units)
	{
		case GUIMENU_UNITS_US:
		Time = Time / 1000000;
		break;
		
		case GUIMENU_UNITS_MS:
		Time = Time / 1000;
		break;
		
		case GUIMENU_UNITS_S:
		break;
		
		case GUIMENU_UNITS_M:
		Time = Time * 60;
		break;
		
		case GUIMENU_UNITS_H:
		Time = (Time * 60) * 60;
		break;
		
		default:			//Shouldn't get here, but lets protect ourselves in case we do!
		break;
	}
	
	return Time;
}

unsigned long (*CurrentTimeSelector (unsigned char Units))(void)
{
	unsigned long (*GetTimePointer)(void);
	
	switch (Units)
	{
		case GUIMENU_UNITS_US:
		GetTimePointer = GetTimeMicros;
		break;
		
		case GUIMENU_UNITS_MS:
		GetTimePointer = GetTimeMillis;
		break;
		
		case GUIMENU_UNITS_S:
		GetTimePointer = GetTimeMillis;
		break;
		
		case GUIMENU_UNITS_M:
		GetTimePointer = GetTimeMin;
		break;
		
		case GUIMENU_UNITS_H:
		GetTimePointer = GetTimeHours;
		break;
		
		default:			//Shouldn't get here, but lets protect ourselves in case we do!
		GetTimePointer = GetTimeSeconds;
		break;
	}
	
	return GetTimePointer;
	
}


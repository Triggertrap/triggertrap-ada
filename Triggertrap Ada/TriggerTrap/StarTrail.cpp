#include <stdlib.h>
#include "MenuDefines.h"
#include "Arduino.h"
#include "HardwareGlobals.h"
#include "eeprom_addresses.h"
#include "guimenu.h"
#include "Inputs.h"
#include "HighSpeedFlash.h"
#include "Menu.h"
#include "EEPROM.h"


static uint8_t input_key; // GCC doesn't like moving local pointers (stack) around

extern unsigned long (*CurrentTimeSelector (unsigned char Units))(void);

/*****************************************************************************
*
*   Function name : StarTrail
*
*   Returns :       next state
*
*   Parameters :  
*
*   Purpose :      Runs the application code for Star Trail
*
*	Notes:		   
*
*****************************************************************************/

char StarTrail(char input)
{
	unsigned long StartTime;
	uint16_t TimelapseCount; 
	bool PrimaryOutputServiced, MobileOutputServiced, InfiniteEnabled;
	unsigned long PrimaryOutputDelay = 0, MobileOutputDelay, MobileOutputRunTime = 3000000, PrimaryOutputPreFocus = 0, PrimaryOutputPreFocusSave, PrimaryOutputPulse, ElapsedTime = 0;
	unsigned long TimeLapseIntervalTime;
	unsigned long (*CurrentTime)(void);
	unsigned char TimelapseCountLow,TimelapseCountHigh,PrimaryOutputPreFocusLow,PrimaryOutputPreFocusHigh,PrimaryOutputPulseLow,PrimaryOutputPulseHigh;
	unsigned char TimelapseIntervalLow,TimelapseIntervalHigh,IntervalUnits,Units;
	
	
 	TimelapseCountLow =  EEPROM.read(EEPROM_STARTTRAIL_COUNT_LO);
 	TimelapseCountHigh =  EEPROM.read(EEPROM_STARTTRAIL_COUNT_HI);
 	TimelapseCount = (TimelapseCountHigh << 8) | TimelapseCountLow;
 	
	 
	 if(TimelapseCount >= GUIMENU_INFINITE_VALUE)
	 {
		 InfiniteEnabled = true;
	 }
	 else
	 {
		 InfiniteEnabled = false;
	 }
	  
	  
	PrimaryOutputPreFocusLow  =  EEPROM.read(EEPROM_CAMERAPREFOCUS_LO);
	PrimaryOutputPreFocusHigh =  EEPROM.read(EEPROM_CAMERAPREFOCUS_HI);
	PrimaryOutputPreFocusSave = (PrimaryOutputPreFocusHigh << 8) | PrimaryOutputPreFocusLow;	
	Units = EEPROM.read(EEPROM_CAMERAPREFOCUS_UNITS);
	PrimaryOutputPreFocusSave = formatTimeToMicro(PrimaryOutputPreFocusSave,Units);				//Value must be converted to us
	
	PrimaryOutputPulseLow  =  EEPROM.read(EEPROM_STARTTRAIL_SHUTTERSPEED_LO);
	PrimaryOutputPulseHigh =  EEPROM.read(EEPROM_STARTTRAIL_SHUTTERSPEED_HI);
	PrimaryOutputPulse = (PrimaryOutputPulseHigh << 8) | PrimaryOutputPulseLow;		//TODO: Should PrimaryOutputPulseSave be typecast as an int?
	Units = EEPROM.read(EEPROM_STARTTRAIL_SHUTTERSPEED_UNITS);
	PrimaryOutputPulse = formatTimeToMicro(PrimaryOutputPulse,Units);					//Value must be converted to us
	
	TimelapseIntervalLow  =  EEPROM.read(EEPROM_STARTTRAIL_INTERVAL_LO);
	TimelapseIntervalHigh =  EEPROM.read(EEPROM_STARTTRAIL_INTERVAL_HI);
	TimeLapseIntervalTime = (TimelapseIntervalHigh << 8) | TimelapseIntervalLow;				//TODO: Should PrimaryOutputPulseSave be typecast as an int?
	IntervalUnits = EEPROM.read(EEPROM_STARTTRAIL_INTERVAL_UNITS);
	TimeLapseIntervalTime = formatTime(TimeLapseIntervalTime,IntervalUnits);
	
	
#ifdef _USE_ARDUINO_ORIGINAL_CODE
		
	STStartDelay = STStartDelay/0.73;
	STInterval = STInterval/0.73;
	STShutterDelay = STShutterDelay/0.73;
	
#endif	

	uint32_t start_delay = ((uint16_t)EEPROM.read(EEPROM_STARTTRAIL_WAIT_HI) << 8)
							| (uint16_t)EEPROM.read(EEPROM_STARTTRAIL_WAIT_LO);

	uint8_t start_delay_units = EEPROM.read(EEPROM_STARTTRAIL_WAIT_UNITS);
/*	if (start_delay)
	{
		uint8_t start_delay_units = EEPROM.read(EEPROM_STARTTRAIL_WAIT_UNITS);
		uint32_t start_delay_secs = time_units_to_secs(start_delay, start_delay_units);
		uint32_t start_time_secs = get_time_in_secs();
		
		while ((get_time_in_secs() - start_time_secs) <= start_delay_secs)
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
				return	ST_STARTRAIL_START;
			}
		}
	}
	

	ElapsedTime = 0;
*/
	CurrentTime = CurrentTimeSelector(IntervalUnits);
	if (start_delay)
	{
		guimenu_displaypage(GUIMENU_STARTRAIL_PROG_PAGE);
		
		switch (start_delay_units)
		{
			case GUIMENU_UNITS_S:
				CurrentTime = CurrentTimeSelector (start_delay_units);
				start_delay = formatTimeToMillis (start_delay, start_delay_units);
			break;
			
			case GUIMENU_UNITS_M:
				start_delay *= 60;
				CurrentTime = CurrentTimeSelector ((unsigned char)GUIMENU_UNITS_S);
				start_delay = formatTimeToMillis (start_delay, GUIMENU_UNITS_S);
			break;
			
			case GUIMENU_UNITS_H:
				start_delay *= 3600;
				CurrentTime = CurrentTimeSelector ((unsigned char)GUIMENU_UNITS_S);
				start_delay = formatTimeToMillis (start_delay, GUIMENU_UNITS_S);
			break;
			
		}
		
		guimenu_progressbar_start (GUIMENU_STARTRAIL_PROG_PAGE, start_delay, start_delay_units, 0);
		
		StartTime = CurrentTime();
		
		ElapsedTime = 0;
	
		while(start_delay >= ElapsedTime)
		{
			ElapsedTime = CurrentTime() - StartTime;			//how much time has passed?
		
			if (ElapsedTime <= start_delay)
			{
				guimenu_progressbar_update ((start_delay - ElapsedTime), 0);
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
				return ST_STARTRAIL_START;
			}
		
		}
		
	}
	
	guimenu_displaypage(GUIMENU_STARTRAIL_STOP_PAGE);
	
	while(TimelapseCount || InfiniteEnabled)		//Stay in this loop until we have finished our timelapse count
	{

		//RESET ALL VARIABLES HERE

		PrimaryOutputServiced = false;
		MobileOutputServiced = true;

		/*	This part of the routine must be accurate up to a microsecond resolution. the fastest time able to be set by any channel delay is 10us
		*   The maximum is 60 seconds. as we are using unsigned long, this is acceptable to format as 60,000,000uS.
		*/
		
		StartTime = micros();
		
		while(!(PrimaryOutputServiced && MobileOutputServiced))							//not all of the conditions have been met
		{

			ElapsedTime = micros() - StartTime;			//how much time has passed?

			
			if((ElapsedTime >= PrimaryOutputDelay) && (!PrimaryOutputServiced))		//has enough time passed before we should trigger the first output?
			{
				
				digitalWrite(Focus,1);												//yes, it has, turn on the focus line to the camera
				digitalWrite(CAMERAOUT2_A, 1);
				digitalWrite(CAMERAOUT3_A, 1);												//yes, it has, turn on the focus line to the camera
				
				if(ElapsedTime >= (PrimaryOutputDelay + PrimaryOutputPreFocus))		//has enough time passed before we should trigger the camera shutter?
				{
					digitalWrite(Trigger, 1);										  //yes, it has
					digitalWrite(CAMERAOUT2_B, 1);
					digitalWrite(CAMERAOUT3_B, 1);
					
					if(ElapsedTime >= (PrimaryOutputDelay + PrimaryOutputPreFocus + PrimaryOutputPulse))	//has enough time passed before the pulse length has been satisfied?
					{
						digitalWrite(Trigger,0);				//yes, all off and mark that this routine need not be entered again
						digitalWrite(CAMERAOUT2_A, 0);
						digitalWrite(CAMERAOUT3_A, 0);
						digitalWrite(Focus,0);
						digitalWrite(CAMERAOUT2_B, 0);
						digitalWrite(CAMERAOUT3_B, 0);
						PrimaryOutputServiced = true;
					}

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
			

			
			
			if(GetButton() == KEY_MINUS)
			{
				digitalWrite(Focus, 0);
				digitalWrite(Trigger, 0);
				digitalWrite(CAMERAOUT2_A, 0);
				digitalWrite(CAMERAOUT2_B, 0);
				digitalWrite(CAMERAOUT3_A, 0);
				digitalWrite(CAMERAOUT3_B, 0);
				return	ST_STARTRAIL_START;
			}
		}
		

		StartTime = CurrentTime();						//need to accept a range from 24Hrs to 100ms. Select an appropriate time scale.
		ElapsedTime = 0;
		
		while(TimeLapseIntervalTime >= ElapsedTime)		//wait here until the interval delay has passed
		{

			ElapsedTime = CurrentTime() - StartTime;			//how much time has passed?

			
			if(GetButton() == KEY_MINUS)
			{
				digitalWrite(Focus, 0);
				digitalWrite(Trigger, 0);
				digitalWrite(CAMERAOUT2_A, 0);
				digitalWrite(CAMERAOUT2_B, 0);
				digitalWrite(CAMERAOUT3_A, 0);
				digitalWrite(CAMERAOUT3_B, 0);
				digitalWrite(STACK_PWR, 0);	//turn power to the stack on
				return ST_STARTRAIL_START;
			}
			
		}
		
		TimelapseCount--;
	}
	
	digitalWrite(Focus, 0);
	digitalWrite(Trigger, 0);
	digitalWrite(CAMERAOUT2_A, 0);
	digitalWrite(CAMERAOUT2_B, 0);
	digitalWrite(CAMERAOUT3_A, 0);
	digitalWrite(CAMERAOUT3_B, 0);
	digitalWrite(STACK_PWR, 0);	//turn power to the stack on
	guimenu_operation_complete(GUIMENU_STARTRAIL_STOP_PAGE, &input_key);
	return	ST_STARTRAIL_START;
	
}

char StarTrailInterval (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_STARTRAIL_INTERVAL_PAGE, &input_key);

	while (!next_state)
	{
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_STARTRAIL_START;
			break;
			
			case KEY_DOWN:
			next_state = ST_STARTRAIL_SHUTTER_SPEED;
			break;
		}
		
		input_key = GetButton();
	}
	
	return next_state;
}

char StarTrailCount(char input)
{
	char next_state = 0;
	
	guimenu_selector ( GUIMENU_STARTRAIL_COUNT_PAGE, &input_key);

	while (!next_state)
	{
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_STARTRAIL_SHUTTER_SPEED;
			break;
			
			case KEY_DOWN:
			next_state = ST_STARTRAIL_DELAY;
			break;
		}
		
		input_key = GetButton();
	}
	
	return next_state;
}

char StarTrailShutterSpeed(char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_STARTRAIL_SHUTTER_SPEED_PAGE, &input_key);

	while (!next_state)
	{
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_STARTRAIL_INTERVAL;
			break;
			
			case KEY_DOWN:
			next_state = ST_STARTRAIL_COUNT;
			break;
		}
		
		input_key = GetButton();
	}
	
	return next_state;
}

char StarTrailDelay(char input)
{
	char next_state = 0;
	
	guimenu_selector ( GUIMENU_STARTRAIL_DELAY_PAGE, &input_key);

	while (!next_state)
	{
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_STARTRAIL_COUNT;
			break;
			
			case KEY_DOWN:
			next_state = ST_STARTRAIL_DELAY;
			break;
		}
		
		input_key = GetButton();
	}
	
	return next_state;
}

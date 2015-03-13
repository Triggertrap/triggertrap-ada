#include <stdlib.h>
#include "MenuDefines.h"
#include "Arduino.h"
#include "HardwareGlobals.h"
#include "EEPROM.h"
#include "eeprom_addresses.h"
#include "guimenu.h"
#include "guimenu_pages.h"
#include "Menu.h"
#include "Inputs.h"


static uint8_t input_key;

extern unsigned long (*CurrentTimeSelector (unsigned char Units))(void);
extern unsigned long formatTimeToMillis (unsigned long Time, char Units);

unsigned long (*CurrentTime)(void);

/*****************************************************************************
*
*   Function name : BulbRamp
*
*   Returns :       N/A
*
*   Parameters :  Starting Shutter Speed (ShutterStart) Ending Shutter speed (ShutterEnd)
                  Number of Shots (TotalShot)f
*
*   Purpose :     Bulb Ramping function
*
*****************************************************************************/
float ExposureDelay,FirstExposure,LastExposure,MaxExposure,TotalFrames;
char ExposureEE;

char BulbRamp(char input)
{
  unsigned long StartTime;
  unsigned long StartDelay;
  unsigned long ElapsedTime = 0;
  unsigned long Duration,TLInterval,TLIntervalnorm;
  unsigned int BRShutterPulseDelay; 
  unsigned char  BRFocusDelayLow, BRFocusDelayHigh, BRShutterPlseDelayLow, BRShutterPlseDelayHigh, Units,StartDelayLow,StartDelayHigh,StartDelayUnits;
  unsigned char TotalFramesLow,TotalFramesHigh,UnitsLow,UnitsHigh; 
  int CurrentFrame;
  
  unsigned long PrimaryOutputDelay,PrimaryOutputPreFocus;
  unsigned long PrimaryOutputPulse;
  bool PrimaryOutputServiced;
 
 
  PrimaryOutputDelay = 0;
  PrimaryOutputPreFocus = 0;

  ExposureEE =  EEPROM.read(EEPROM_BULBRAMP_START_EXPOSURE);
  FirstExposure = ExtractExposure ((char)ExposureEE);
  
  
  ExposureEE =  EEPROM.read(EEPROM_BULBRAMP_END_EXPOSURE);
  LastExposure = ExtractExposure ((char)ExposureEE); 

 
 
  TotalFramesLow =  EEPROM.read(EEPROM_BULBRAMP_COUNT_LO);
  TotalFramesHigh =  EEPROM.read(EEPROM_BULBRAMP_COUNT_HI);
  TotalFrames = (TotalFramesHigh << 8) | TotalFramesLow;


  BRFocusDelayLow =  EEPROM.read(EEPROM_CAMERAPREFOCUS_LO);
  BRFocusDelayHigh =  EEPROM.read(EEPROM_CAMERAPREFOCUS_HI);
  PrimaryOutputPreFocus = (BRFocusDelayHigh << 8) | BRFocusDelayLow;
  Units = EEPROM.read(EEPROM_CAMERAPREFOCUS_UNITS);
  PrimaryOutputPreFocus = formatTimeToMicro(PrimaryOutputPreFocus,Units);  
  
  BRShutterPlseDelayLow = EEPROM.read(EEPROM_SHUTTERPULSE_LO);
  BRShutterPlseDelayHigh = EEPROM.read(EEPROM_SHUTTERPULSE_HI);
  BRShutterPulseDelay = (BRShutterPlseDelayHigh << 8) | BRShutterPlseDelayLow;
  Units = EEPROM.read(EEPROM_SHUTTERPULSE_UNITS);
  BRShutterPulseDelay = formatTimeToMicro(BRShutterPulseDelay,Units);  
  
  StartDelayLow  =  EEPROM.read(EEPROM_BULBRAMP_STARTDELAY_LO);
  StartDelayHigh =  EEPROM.read(EEPROM_BULBRAMP_STARTDELAY_HI);
  StartDelay = (StartDelayHigh << 8) | StartDelayLow;										
  StartDelayUnits = EEPROM.read(EEPROM_BULBRAMP_STARTDELAY_UNITS);

 
  UnitsLow  =  EEPROM.read(EEPROM_BULBRAMP_DURATION_LO);
  UnitsHigh =  EEPROM.read(EEPROM_BULBRAMP_DURATION_HI);
  Duration = (UnitsHigh << 8) | UnitsLow;									
  Units = EEPROM.read(EEPROM_BULBRAMP_DURATION_UNITS);
  Duration = formatTimeToMillis(Duration, Units);	
   
  CurrentTime = CurrentTimeSelector(StartDelayUnits);
  StartTime = CurrentTime();
  ElapsedTime = 0;
  
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  //Calculate if the user settings are viable
  /////////////////////////////////////////////////////////////////////////////////////////////////////

  MaxExposure = (FirstExposure >= LastExposure ? FirstExposure : LastExposure);		//return the max value
  
  TLIntervalnorm = Duration / (unsigned long)TotalFrames;
  
  if((unsigned long)MaxExposure > TLIntervalnorm)
  {
	digitalWrite(Focus, 0);
	digitalWrite(Trigger, 0);
	digitalWrite(CAMERAOUT2_A, 0);
	digitalWrite(CAMERAOUT2_B, 0);
	digitalWrite(CAMERAOUT3_A, 0);
	digitalWrite(CAMERAOUT3_B, 0);
	digitalWrite(STACK_PWR, 0);	//turn power to the stack on
	  return SettingError(ST_BULBRAMP_START);
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  //Start Delay
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  
	if (StartDelay)
	{
		switch (StartDelayUnits)
		{
			case GUIMENU_UNITS_S:
				CurrentTime = CurrentTimeSelector (StartDelayUnits);
				StartDelay = formatTimeToMillis (StartDelay, StartDelayUnits);
			break;
			
			case GUIMENU_UNITS_M:
				StartDelay *= 60;
				CurrentTime = CurrentTimeSelector ((unsigned char)GUIMENU_UNITS_S);
				StartDelay = formatTimeToMillis (StartDelay, GUIMENU_UNITS_S);
			break;
			
			case GUIMENU_UNITS_H:
				StartDelay *= 3600;
				CurrentTime = CurrentTimeSelector ((unsigned char)GUIMENU_UNITS_S);
				StartDelay = formatTimeToMillis (StartDelay, GUIMENU_UNITS_S);
			break;
			
		}
		
		guimenu_progressbar_start (GUIMENU_BRAMP_PROG_PAGE, StartDelay, StartDelayUnits, 0);
		
		StartTime = CurrentTime();
		
		ElapsedTime = 0;
	
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
				return ST_BULBRAMP_START;
			}
		
		}
	}

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  //Main Function
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  

  for(CurrentFrame = 0; CurrentFrame <= (TotalFrames - 1); CurrentFrame++)    //repeat as set by Total frames
  {
		ExposureDelay = ((((float)CurrentFrame / (TotalFrames - 1)) * (LastExposure - FirstExposure)) + FirstExposure) * 1000.0F;    //calculate the delay required by the next exposure and convert to millis
		PrimaryOutputPulse = (unsigned long)ExposureDelay;
		PrimaryOutputServiced = false;

		if(PrimaryOutputPulse >= 1000)				//we don't want to use this if we have a time of less than 1 sec
		{
			guimenu_displaypage(GUIMENU_BRAMP_EXPOPROG_PAGE);
			guimenu_progressbar_start (GUIMENU_BRAMP_EXPOPROG_PAGE, ((uint32_t)PrimaryOutputPulse / 1000), GUIMENU_UNITS_S,0);
		}
		
		/*	This part of the routine must be accurate up to a microsecond resolution. the fastest time able to be set by any channel delay is 10us
		*   The maximum is 60 seconds. as we are using unsigned long, this is acceptable to format as 60,000,000uS.
		*/

		StartTime = micros();
				
		while(!PrimaryOutputServiced)
		{

			ElapsedTime = micros() - StartTime;			//how much time has passed?

			
			if((ElapsedTime >= PrimaryOutputDelay) && (!PrimaryOutputServiced))		//has enough time passed before we should trigger the first output?
			{
				
				digitalWrite(Focus,1);												//yes, it has, turn on the focus line to the camera
				digitalWrite(CAMERAOUT2_A, 1);
				digitalWrite(CAMERAOUT3_A, 1);
				
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

			if(PrimaryOutputPulse > ElapsedTime)
			{
				guimenu_progressbar_update((uint32_t)((PrimaryOutputPulse - ElapsedTime) / 1000), 0);
			}
			
			else
			{
				guimenu_progressbar_update(0, 0);
			}
			
			
			if(GetButton() == KEY_MINUS)
			{
				digitalWrite(Focus, 0);
				digitalWrite(Trigger, 0);
				digitalWrite(CAMERAOUT2_A, 0);
				digitalWrite(CAMERAOUT2_B, 0);
				digitalWrite(CAMERAOUT3_A, 0);
				digitalWrite(CAMERAOUT3_B, 0);
				return	ST_BULBRAMP_START;
			}
			

		}
		
		TLInterval = TLIntervalnorm - (PrimaryOutputPulse/1000);

		if(TLInterval >= 1000)				//we don't want to use this if we have a time of less than 1 sec
		{
			guimenu_displaypage(GUIMENU_BRAMP_PROG_PAGE);
			guimenu_progressbar_start (GUIMENU_BRAMP_PROG_PAGE, (uint32_t)TLInterval, GUIMENU_UNITS_S,0);
		}
		
		StartTime = millis();
		ElapsedTime = 0;
		
		while(TLInterval >= ElapsedTime)		//wait here until the interval delay has passed
		{

			ElapsedTime = millis() - StartTime;			//how much time has passed?
			
			if(TLInterval > ElapsedTime)
			{
				guimenu_progressbar_update((uint32_t)(TLInterval - ElapsedTime), 0);
			}
			
			else
			{
				guimenu_progressbar_update(0, 0);
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
				return ST_BULBRAMP_START;
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
  guimenu_operation_complete(GUIMENU_BRAMP_PROG_PAGE, &input_key);
  return ST_BULBRAMP_START;
  
  
}


char BulbRampStartExpSet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_BULBRAMP_START_EXPOSURE_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_BULBRAMP_START;
			break;
			
			case KEY_DOWN:
			next_state = ST_BULBRAMP_END_EXP;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char BulbRampEndExpSet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_BULBRAMP_END_EXPOSURE_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_BULBRAMP_START_EXP;
			break;
			
			case KEY_DOWN:
			next_state = ST_BULBRAMP_DELAYSTART;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char BulbRampDelaySet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_BULBRAMP_STARTDELAY_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_BULBRAMP_END_EXP;
			break;
			
			case KEY_DOWN:
			next_state = ST_BULBRAMP_COUNT;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char BulbRampCountSet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_BULBRAMP_COUNT_PAGE	, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_BULBRAMP_DELAYSTART;
			break;
			
			case KEY_DOWN:
			next_state = ST_BULBRAMP_DURATION;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char BulbRampDurationSet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_BULBRAMP_DURATION_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
				next_state = ST_BULBRAMP_COUNT;
			break;
			
			case KEY_DOWN:
				next_state = ST_BULBRAMP_DURATION;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}

float ExtractExposure (char Selector)
{
	float Time;
	switch (Selector)	//27
	{
		
	case 0x00:			// 1/15
		Time = 67.0f;
		break;

	case 0x01:			// 1/13
		Time = 78.0f;
		break;
	
	case 0x02:			//	1/10
		Time = 100.0f;
		break;
	
	case 0x03:			// 1/8
		Time = 125.0f;
		break;
	
	case 0x04:			// 1/6
		Time = 167.0f;
		break;
	
	case 0x05:
		Time = 200.0f;		// 1/5
		break;
	
	case 0x06:			// 1/4
		Time = 250.0f;
		break;
	
	case 0x07:
		Time = 300.0f;
		break;
	
	case 0x08:
		Time = 400.0f;
		break;
	
	case 0x09:
		Time = 500.0f;
		break;
	
	case 0x0A:
		Time = 600.0f;
		break;
	
	case 0x0B:
		Time = 800.0f;
		break;
	
	case 0x0C:
		Time = 1000.0f;
		break;
	
	case 0x0D:
		Time = 1300.0f;
		break;
	
	case 0x0E:
		Time = 1600.0f;
		break;
	
	case 0x0F:
		Time = 2000.0f;
		break;
	
	case 0x10:
		Time = 2500.0f;
		break;
	
	case 0x11:
		Time = 3200.0f;
		break;
	
	case 0x12:
		Time = 4000.0f;
		break;
	
	case 0x13:
		Time = 5000.0f;
		break;
	
	case 0x14:
		Time = 6000.0f;
		break;
	
	case 0x15:
		Time = 8000.0f;
		break;
		
	case 0x16:
		Time = 10000.0f;
		break;
	
	case 0x17:
		Time = 13000.0f;
		break;
		
	case 0x18:
		Time = 15000.0f;
		break;
	
	case 0x19:
		Time = 20000.0f;
		break;
		
	case 0x1A:
		Time = 25000.0f;
		break;
	
	case 0x1B:
		Time = 30000.0f;
		break;
		
	default:
		Time = 200.0f;
	}
	
	return Time;
}

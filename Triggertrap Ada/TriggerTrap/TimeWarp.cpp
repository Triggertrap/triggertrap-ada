#include <stdlib.h>
#include "MenuDefines.h"
#include "Arduino.h"
#include "HardwareGlobals.h"
#include "EEPROM.h"
#include "eeprom_addresses.h"
#include "guimenu.h"
#include "Menu.h"
#include "Inputs.h"

volatile uint8_t g_exponent;
static uint8_t input_key;

/*****************************************************************************
*
*   Function name : TimeWarp
*
*   Returns :       N/A
*
*   Parameters :  
*
*   Purpose :     
*
*   Notes : 
*           
*
*****************************************************************************/

char Exponentlookup(char Value)  //returns number rounded to the specified nearest place
{
	char Exponent = 2;
	
	switch (Value)
	{
		case 0:		//quadratic
			Exponent = 2;
			break;
			
		case 1:		//quartic
			Exponent = 4;
			break;
			
		case 2:		//quintic
			Exponent = 5;
			break;
	}
	
	return Exponent;
	

}

float precisionRound(float num, int pointPlace)  //returns number rounded to the specified nearest place
{
  float lookup[4] = {1, 10, 100, 1000};
  
  if(pointPlace >= 4 || pointPlace < 0)
  {
    return 0;
  }
  
  num = num * lookup[pointPlace];
  num = round(num);
  return num / lookup[pointPlace];

}

float easeIn(float  frame)
{
  return pow((double)frame, (double)g_exponent);
}



float easeOut(float frame)
{
  return 1 - easeIn((1.0 - frame));
}


float easeInOut(float frame)
{
  if(frame <= 0.5) 
  {
    return easeIn(frame * 2.0) / 2.0;
  }
  
  else
  {

    return 0.5 + (easeOut((frame - 0.5) * 2.0) / 2.0);

  }
}



float easeOutIn(float frame)
{
  if(frame > 0.5)
  {
    return easeIn(frame * 2.0) / 2.0;

  }
  
  else
  {
    frame = frame + 0.1;
    return 0.5 + (easeOut((frame - 0.5) * 2.0) / 2.0);
  }
}


  
   struct SingleBit			//we only need 1 bit for a flag so lets save some space!
   {
	   volatile unsigned char CameraCalculated : 1;
	   volatile unsigned char FlashCalculated : 1;
	   volatile unsigned char Cameraserviced : 1;
	   volatile unsigned char Flashserviced : 1;
	   //room for 4 more flags
	   
   };
   typedef struct SingleBit singlebit;
   
  
  //volatile uint32_t WaitBeforeStart_secs,stop_time_secs;
  
  extern unsigned long (*CurrentTimeSelector (unsigned char Units))(void);
  
char TimeWarp(char input)
{
  float (*ease)(float);
  unsigned char easeingType;
  volatile unsigned long start_delay, CameraElapsedTime, CameraPrefocusDelay, CameraDelay, CameraPulseLength, FlashPulseLength, FlashDelay,CameraintervalStart,Camerainterval,StartTime,ElapsedTime;

  volatile unsigned int Totalframes;
  volatile unsigned long maxchanneltime, TotalCameraDelay, TotalFlashDelay, duration;
  float interval;
  volatile float ratio, eased, prev = 0;
  volatile int i;
  volatile uint8_t start_delay_units;
  unsigned long (*CurrentTime)(void);

  
   volatile singlebit Flags;
 
  
  unsigned char durationHi, durationLo,framesHi, framesLo, WaitBeforeStartHi, WaitBeforeStartLo;
  unsigned char FlashPulseLengthLow,FlashPulseLengthHigh,CameraPulseLengthLow,CameraPulseLengthHigh,CameraPrefocusDelayLow,CameraPrefocusDelayHigh,Units;

  CameraPrefocusDelayLow  =  EEPROM.read(EEPROM_CAMERAPREFOCUS_LO);
  CameraPrefocusDelayHigh =  EEPROM.read(EEPROM_CAMERAPREFOCUS_HI);
  CameraPrefocusDelay = (CameraPrefocusDelayHigh << 8) | CameraPrefocusDelayLow;	//
  Units = EEPROM.read(EEPROM_CAMERAPREFOCUS_UNITS);
  CameraPrefocusDelay = formatTimeToMillis(CameraPrefocusDelay,Units);				//Value must be converted to us
  
  CameraPulseLengthLow  =  EEPROM.read(EEPROM_SHUTTERPULSE_LO);
  CameraPulseLengthHigh =  EEPROM.read(EEPROM_SHUTTERPULSE_HI);
  CameraPulseLength = (CameraPulseLengthHigh << 8) | CameraPulseLengthLow;		//
  Units = EEPROM.read(EEPROM_SHUTTERPULSE_UNITS);
  CameraPulseLength = formatTimeToMillis(CameraPulseLength,Units);	
	
  FlashPulseLengthLow  =  EEPROM.read(EEPROM_FLASHPULSE_LO);
  FlashPulseLengthHigh =  EEPROM.read(EEPROM_FLASHPULSE_HI);
  FlashPulseLength = (FlashPulseLengthHigh << 8) | FlashPulseLengthLow;		//
  Units = EEPROM.read(EEPROM_FLASHPULSE_UNITS);
  FlashPulseLength = formatTimeToMillis(FlashPulseLength,Units);
 
  FlashDelay = 0;
  CameraDelay = 0;
  
  framesHi =  EEPROM.read(EEPROM_TIMEWARP_COUNT_HI);
  framesLo =  EEPROM.read(EEPROM_TIMEWARP_COUNT_LO);
  Totalframes = (framesHi << 8) | framesLo;
 
  durationHi =  EEPROM.read(EEPROM_TIMEWARP_DURATION_HI);
  durationLo =  EEPROM.read(EEPROM_TIMEWARP_DURATION_LO);
  duration = (durationHi << 8) | durationLo;
  Units = EEPROM.read(EEPROM_TIMEWARP_DURATION_UNITS);		
  duration = formatTimeToSeconds(duration,Units);			//needs to be returned as seconds for maths later
  
  
  g_exponent = Exponentlookup(EEPROM.read(EEPROM_TIMEWARP_FUNCTION));
  
  WaitBeforeStartHi =  EEPROM.read(EEPROM_TIMEWARP_WAIT_HI);
  WaitBeforeStartLo =  EEPROM.read(EEPROM_TIMEWARP_WAIT_LO);
  start_delay = (WaitBeforeStartHi << 8) | WaitBeforeStartLo;
  start_delay_units = EEPROM.read(EEPROM_TIMEWARP_WAIT_UNITS);
  
  easeingType = EEPROM.read(EEPROM_TIMEWARP_DIRECTION);
  
  
  //WaitBeforeStart_secs = time_units_to_secs(WaitBeforeStart, WaitBeforeStart_units);
 // stop_time_secs = get_time_in_secs();

  TotalCameraDelay = CameraPrefocusDelay + CameraDelay + CameraPulseLength;
  TotalFlashDelay = FlashDelay + FlashPulseLength;
  
  
  if(TotalCameraDelay >= TotalFlashDelay)
  {
	  maxchanneltime = TotalCameraDelay;
  }
  
  else
  {
	  maxchanneltime = TotalFlashDelay;
  }
  
  if(easeingType == EASE_IN)
  {
    ease = easeIn;
  }
  else if(easeingType == EASE_OUT)
  {
    ease = easeOut;
  }
  else if(easeingType == EASE_INOUT)
  {
    ease = easeInOut;    
  }
  else if(easeingType == EASE_OUTIN)
  {
    ease = easeOutIn;
  }
  else
  {
	ease = easeIn;		//Protection default
  }
	
	/*
		while ((get_time_in_secs() - stop_time_secs) <= WaitBeforeStart_secs)
		{
			if (GetButton() == KEY_MINUS)	//cancel selected by the user
			{
				WaitBeforeStart_secs = 0;			//user quit requested, exit to 
			}
			
		}
		
	*/
	
	if (start_delay)
	{
		guimenu_displaypage(GUIMENU_TIMEWARP_PROG_PAGE);
		
		switch (start_delay_units)
		{
			case GUIMENU_UNITS_S:
			default:
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
		
		guimenu_progressbar_start (GUIMENU_TIMEWARP_PROG_PAGE, start_delay, start_delay_units, 0);
		
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
				return ST_TIMEWARP_START;
			}
		
		}
		
	}
	
	guimenu_displaypage(GUIMENU_TIMEWARP_STOP_PAGE);

	for(i = 0; i <= ((int)Totalframes); i++)
	{
	  
	   ratio = (float)i / (float)Totalframes;
	   eased = ease(ratio);
	   interval = (eased - prev) * (float)duration;
	
	   Camerainterval = (unsigned long)(interval * 1000.0f);			//load the exposure for this shot convert to seconds
	   
		if(Camerainterval <= maxchanneltime)	//frame needs to be dropped if less than max channel time due to effects induced
		{
			Camerainterval = 0;  
		}

		prev = eased;
 
		Flags.Cameraserviced = 0;
		Flags.Flashserviced = 0;
		CameraintervalStart = millis();

		if(Camerainterval != 0)
		{
			while(!Flags.Cameraserviced)
			{
				CameraElapsedTime = millis() - CameraintervalStart;
	
				if((CameraElapsedTime >= (Camerainterval + CameraDelay)) && (!Flags.Cameraserviced))
				{
					
					digitalWrite(Focus,1);				//focus trigger here
					digitalWrite(CAMERAOUT2_A, 1);
					digitalWrite(CAMERAOUT3_A, 1);
			
					if(CameraElapsedTime >= (Camerainterval + CameraDelay + CameraPrefocusDelay))
					{
						
						digitalWrite(Trigger,1);				//trigger camera
						digitalWrite(CAMERAOUT2_B, 1);
						digitalWrite(CAMERAOUT3_B, 1);
				
						if(CameraElapsedTime >= (Camerainterval + CameraDelay + CameraPrefocusDelay + CameraPulseLength))
						{
							digitalWrite(Trigger,0);			//release camera
							digitalWrite(CAMERAOUT2_A, 0);
							digitalWrite(CAMERAOUT3_A, 0);
							digitalWrite(Focus,0);
							digitalWrite(CAMERAOUT2_B, 0);
							digitalWrite(CAMERAOUT3_B, 0);
							Flags.Cameraserviced = 1;			//serviced	
						}
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
					 return	ST_TIMEWARP_START;
				 }
	 
			}//end while
		}//End if
			
		CameraElapsedTime = 0;

	}//End for loop
	
	digitalWrite(Focus, 0);
	digitalWrite(Trigger, 0);
	digitalWrite(CAMERAOUT2_A, 0);
	digitalWrite(CAMERAOUT2_B, 0);
	digitalWrite(CAMERAOUT3_A, 0);
	digitalWrite(CAMERAOUT3_B, 0);
	digitalWrite(STACK_PWR, 0);	//turn power to the stack on
	guimenu_operation_complete(GUIMENU_TIMEWARP_STOP_PAGE, &input_key);
    return ST_TIMEWARP_START;
  
  }


char TimeWarpFunctionSet (char input)
{
	char next_state = 0;

	guimenu_selector (GUIMENU_TIMEWARP_FUNCTION_PAGE, &input_key);

	while (!next_state)
	{
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_TIMEWARP_DURATION_SET;
			break;
			
			case KEY_DOWN:
			next_state = ST_TIMEWARP_DIRECTION_SET;
			break;
		}
		
		input_key = GetButton();
	}
	return next_state;
}

char TimeWarpCountSet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_TIMEWARP_COUNT_PAGE, &input_key);

	while (!next_state)
	{
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_TIMEWARP_START;
			break;
			
			case KEY_DOWN:
			next_state = ST_TIMEWARP_DURATION_SET;
			break;
		}
		
		input_key = GetButton();
	}
	
	return next_state;
}

char TimeWarpDirectionSet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_TIMEWARP_DIRECTION_PAGE, &input_key);

	while (!next_state)
	{
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_TIMEWARP_FUNCTION;
			break;
			
			case KEY_DOWN:
			next_state = ST_TIMEWARP_WAIT_SET;
			break;
		}
		
		input_key = GetButton();
	}
	
	return next_state;
}

char TimeWarpWaitSet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_TIMEWARP_WAIT_PAGE, &input_key);

	while (!next_state)
	{
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_TIMEWARP_DIRECTION_SET;
			break;
			
			case KEY_DOWN:
			next_state = ST_TIMEWARP_WAIT_SET;
			break;
		}
		
		input_key = GetButton();
	}
	
	return next_state;
}

char TimeWarpDurationSet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_TIMEWARP_DURATION_PAGE, &input_key);

	while (!next_state)
	{
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_TIMEWARP_COUNT_SET;
			break;
			
			case KEY_DOWN:
			next_state = ST_TIMEWARP_FUNCTION;
			break;
		}
		
		input_key = GetButton();
	}
	
	return next_state;
}

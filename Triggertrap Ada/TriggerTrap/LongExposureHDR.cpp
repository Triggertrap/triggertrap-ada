#include <stdlib.h>
#include <math.h>
#include "MenuDefines.h"
#include "Arduino.h"
#include "HardwareGlobals.h"
#include "guimenu.h"
#include "guimenu_pages.h"
#include "eeprom_addresses.h"
#include "Menu.h"
#include "Inputs.h"
#include "LongExposureHDR.h"
#include "EEPROM.h"


static uint8_t input_key;

/*****************************************************************************
*   Function name : LongExposure_HDR
*
*   Returns :       N/A
*
*   Parameters :
*
*   Purpose :  Allows user to set under and over exposures and merge results together
*
*   Notes : Math round works to nearest int instead of nearest 0.5 as in Java example
*           There is also a micros() function if shorter exposure is required
*           Needs to add a time lapse or built in delay between shots. see notes
*****************************************************************************/
char LongExposure_HDR(char input)
{
  volatile float MiddleExpo,Expo_per_step;
  int StepInterval,i,TotalShots;
  volatile unsigned long OldTime, ElapsedTime = 0,Exposure, TimelapseDelay, TimelapseDelayStart;
  unsigned char Timelapse_enabled,TimelapseDelayHigh,TimelapseDelayLow,Units;
  int ShotCount;
  unsigned char temp;
  
  MiddleExpo = (ExtractExposure (EEPROM.read(EEPROM_LEHDR_MID_EXP))/1000);
  
  TotalShots = ExtractShot(EEPROM.read(EEPROM_LEHDR_SHOTS));
  
  temp = EEPROM.read(EEPROM_LEHDR_EVPERSHOT);
  Expo_per_step = ExtractEV(temp);
  
  TimelapseDelayHigh = EEPROM.read(EEPROM_LEHDR_TIMELAPSE_HI);
  TimelapseDelayLow = EEPROM.read(EEPROM_LEHDR_TIMELAPSE_LO);
  TimelapseDelay = (TimelapseDelayHigh << 8) | TimelapseDelayLow;
  Units = EEPROM.read(EEPROM_LEHDR_TIMELAPSE_UNITS);
  TimelapseDelay = formatTimeToMillis(TimelapseDelay,Units);
  TimelapseDelay = TimelapseDelay - 1000;				//to account for the first "timelapse" delay of 1 sec that is inherent in the way LE_HDR works
  
  if(TimelapseDelay)
  {
	  Timelapse_enabled = 1;
  }
  
  else
  {
	  Timelapse_enabled = 0;
  }
  
  do 
  {
	  
	  
	  
	  StepInterval = (TotalShots - 1) / 2;
	  
	  ShotCount = 1;
	  
	  for(i = -StepInterval; i <= StepInterval; i++)
	  {
	  
   
		Exposure = ((float)pow((float)pow(2,Expo_per_step),i) * MiddleExpo) * 1000;    //calculates exposure for each shot
	
		guimenu_progressbar_start (GUIMENU_LEHDR_PROG_PAGE, Exposure, GUIMENU_UNITS_S,TotalShots);
							
		//open shutter here!
		digitalWrite(Trigger,1);
		digitalWrite(CAMERAOUT2_A, 1);
		digitalWrite(CAMERAOUT3_A, 1);
		digitalWrite(Focus,1);
		digitalWrite(CAMERAOUT2_B, 1);
		digitalWrite(CAMERAOUT3_B, 1);
    
		
		OldTime = millis();              //save the current time in milliseconds
		ElapsedTime = 0;

		while(ElapsedTime <= Exposure)  //Have we waited long enough yet?
		{
		
			ElapsedTime = millis() - OldTime;            //calculate how much time has passed
														
														
		  if(Exposure > ElapsedTime)
		  {
			guimenu_progressbar_update((Exposure - ElapsedTime), ShotCount);
		  }
		  
		  else
		  {
			  guimenu_progressbar_update(0, ShotCount);
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
				return ST_LEHDR_START;
			}
		}
		

		digitalWrite(Trigger,0);
		digitalWrite(CAMERAOUT2_A, 0);
		digitalWrite(CAMERAOUT3_A, 0);
		digitalWrite(Focus,0);
		digitalWrite(CAMERAOUT2_B, 0);
		digitalWrite(CAMERAOUT3_B, 0);
		
		delay(1000);					//small delay in between shots
		
		ShotCount = ShotCount + 1;
		
		ElapsedTime = 0;
		OldTime = millis();              //save the current time in milliseconds
	
		ElapsedTime = 0;
	
	  }
	  
	  TimelapseDelayStart = millis();
	  
		while(ElapsedTime <= TimelapseDelay)  //Timelapse interval delay?
		{
		
			ElapsedTime = millis() - TimelapseDelayStart;            //calculate how much time has passed
														

			if(GetButton() == KEY_MINUS) 
			{
				digitalWrite(Focus, 0);
				digitalWrite(Trigger, 0);
				digitalWrite(CAMERAOUT2_A, 0);
				digitalWrite(CAMERAOUT2_B, 0);
				digitalWrite(CAMERAOUT3_A, 0);
				digitalWrite(CAMERAOUT3_B, 0);
				digitalWrite(STACK_PWR, 0);	//turn power to the stack on
				return ST_LEHDR_START;
			}
		}
 
 } while (Timelapse_enabled);

  digitalWrite(Focus, 0);
  digitalWrite(Trigger, 0);
  digitalWrite(CAMERAOUT2_A, 0);
  digitalWrite(CAMERAOUT2_B, 0);
  digitalWrite(CAMERAOUT3_A, 0);
  digitalWrite(CAMERAOUT3_B, 0);
  digitalWrite(STACK_PWR, 0);	//turn power to the stack on
  guimenu_operation_complete(GUIMENU_LEHDR_PROG_PAGE, &input_key);
  return ST_LEHDR_START; 
	
}


char LEHDRMidExpSet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_LEHDR_MID_EXP_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_LEHDR_START;
			break;
			
			case KEY_DOWN:
			next_state = ST_LEHDR_SHOTS_SET;
			break;
			
			default:
			next_state = 0;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}

char LEHDRShotsSet (char input)
{
	char next_state = 0;	
	guimenu_selector (GUIMENU_LEHDR_SHOTS_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_LEHDR_MIDEXP_SET;
			break;
			
			case KEY_DOWN:
			next_state = ST_LEHDR_EVPERSTEP_SET;
			break;
			
			default:
			next_state = 0;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}

char LEHDREVPerStepSet (char input)
{
	char next_state = 0;
	guimenu_selector (GUIMENU_LEHDR_EV_PER_STEP_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_LEHDR_SHOTS_SET;
			break;
			
			case KEY_DOWN:
			next_state = ST_LEHDR_TIMLAPSE_SET;
			break;
			
			default:
			next_state = 0;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}

char LEHDRTimelapseSet (char input)
{
	char next_state = 0;

	guimenu_selector (GUIMENU_LEHDR_TIMELAPSE_PAGE, &input_key);

	while (!next_state)
	{
		switch (input_key)
		{
			case KEY_PREV:
				next_state = ST_LEHDR_EVPERSTEP_SET;
			break;
			
			case KEY_DOWN:
				next_state = ST_LEHDR_TIMLAPSE_SET;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}

int ExtractShot(unsigned char Selector)
{
	int Shot;
	
	switch (Selector)
	{
		case 0x00:
			Shot = 3;
			break;
			
		case 0x01:
			Shot = 5;
			break;
			
		case 0x02:
			Shot = 7;
			break;
			
		case 0x03:
			Shot = 9;
			break;
			
		case 0x04:
			Shot = 11;
			break;
			
		case 0x05:
			Shot = 13;
			break;
			
		case 0x06:
			Shot = 15;
			break;
			
		default:
			Shot = 15;
			break;
	}
	
	return Shot;
		
	
}

float ExtractEV(unsigned char Selector)
{
	float EV = 0.33f;
	
	switch(Selector)
	{
		case 0x00:
			EV = 0.33f;
			break;
			
		case 0x01:
			EV = 0.5f;
			break;
			
		case 0x02:
			EV = 1.0f;
			break;
	}
	
	return EV;
}

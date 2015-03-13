#include <stdlib.h>
#include "MenuDefines.h"
#include "Arduino.h"
#include "HardwareGlobals.h"
#include "EEPROM.h"
#include "guimenu.h"
#include "guimenu_pages.h"
#include "Menu.h"
#include "Inputs.h"


#include "HighSpeedFlash.h"
#include "EEPROM.h"
#include "eeprom_addresses.h"


uint8_t input_key; // GCC doesn't like moving local pointers (stack) around
uint8_t TriggerOut;
/*****************************************************************************
*
*   Function name : Sensor Video
*
*   Returns :      Next state
*
*   Parameters :
*
*   Purpose :      Runs the application code for Sensor Video
*
*	Notes:
*
*****************************************************************************/

char SensorVideo(char input)
{
	uint8_t in_time_window;
	uint8_t ext_trigger_off;
	uint8_t start_video = 0;

  TriggerOut = EEPROM.read(EEPROM_SENSORVIDEO_TRIGGER);
  

	uint32_t start_delay = ((uint16_t)EEPROM.read(EEPROM_SENSORVIDEO_DELAY_HI) << 8)
							| (uint16_t)EEPROM.read(EEPROM_SENSORVIDEO_DELAY_LO);
	if (start_delay)
	{
		uint8_t start_delay_units = EEPROM.read(EEPROM_SENSORVIDEO_DELAY_UNITS);
		uint32_t start_delay_secs = time_units_to_secs(start_delay, start_delay_units);
		uint32_t start_time_secs = get_time_in_secs();
		
		while ((get_time_in_secs() - start_time_secs) <= start_delay_secs)
		{
			if(GetButton() == KEY_MINUS)
			{
	 	 		digitalWrite(Focus, 0);
	 	 		digitalWrite(Trigger, 0);
	 	 		digitalWrite(CAMERAOUT2_A,0);	//
	 	 		digitalWrite(CAMERAOUT2_B,0);	//
	 	 		digitalWrite(CAMERAOUT3_A,0);	//
	 	 		digitalWrite(CAMERAOUT3_B,0);	//
	 	 		StackPowerDown();
				return ST_SENSORVIDEO_START;
			}
		}
	}
	
	uint8_t times_active_always = EEPROM.read (EEPROM_SENSORVIDEO_TIMESACTIVE);
	
	if (!times_active_always)
	{
		while (!start_video)
		{
			in_time_window = time_active (EEPROM_SENSORVIDEO_START_HOURS, EEPROM_SENSORVIDEO_END_HOURS);
			while (in_time_window && !start_video)
			{
				ext_trigger_off = digitalRead (Stack);
				if (!ext_trigger_off)
				{
					start_video = 1;
				}
				
				if (GetButton() == KEY_MINUS)
				{
					digitalWrite (Focus, 0);
					digitalWrite (Trigger, 0);
					digitalWrite (CAMERAOUT2_A, 0);	//trigger flash
					digitalWrite (CAMERAOUT2_B, 0);	//
					digitalWrite (CAMERAOUT3_A, 0);	//
					digitalWrite (CAMERAOUT3_B, 0);	//
					StackPowerDown();
					return ST_SENSORVIDEO_START;
				}	
				
				in_time_window = time_active (EEPROM_SENSORVIDEO_START_HOURS, EEPROM_SENSORVIDEO_END_HOURS);
			}
			
			if (GetButton() == KEY_MINUS)
			{
				digitalWrite (Focus, 0);
				digitalWrite (Trigger, 0);
				digitalWrite (CAMERAOUT2_A, 0);	//trigger flash
				digitalWrite (CAMERAOUT2_B, 0);	//
				digitalWrite (CAMERAOUT3_A, 0);	//
				digitalWrite (CAMERAOUT3_B, 0);	//
				StackPowerDown();
				return ST_SENSORVIDEO_START;
			}	
		}
	}
	else	
	{
		while (digitalRead (Stack))
		{
			if (GetButton() == KEY_MINUS)
			{
				digitalWrite (Focus, 0);
				digitalWrite (Trigger, 0);
				digitalWrite (CAMERAOUT2_A, 0);	//trigger flash
				digitalWrite (CAMERAOUT2_B, 0);	//
				digitalWrite (CAMERAOUT3_A, 0);	//
				digitalWrite (CAMERAOUT3_B, 0);	//
				StackPowerDown();
				return ST_SENSORVIDEO_START;
			}
		}
	}

	switch (TriggerOut)
	  {
	  
	  case CAMERA_OUT_ONLY: 
	  
		digitalWrite(Focus,1);			//Trigger here!
		digitalWrite(CAMERAOUT2_A, 1);
		digitalWrite(CAMERAOUT3_A, 1);
		delay(50);					//50ms pulse to the focus line starts the video 
		digitalWrite(Focus,0);
		digitalWrite(CAMERAOUT2_A, 0);
		digitalWrite(CAMERAOUT3_A, 0);
  		break;
	  
	  case MOBILE_OUT_ONLY: //mobile
		
		mobile_trigger_on();
		delay(150);
		mobile_trigger_off();
  		break;
	  
	  case BOTH_OUTPUTS:
	  
		digitalWrite(Focus,1);			//Trigger here!
		digitalWrite(CAMERAOUT2_A, 1);
		digitalWrite(CAMERAOUT3_A, 1);
		mobile_trigger_on();
		delay(50);					//50ms pulse to the focus line starts the video 
		digitalWrite(Focus,0);
		digitalWrite(CAMERAOUT2_A, 0);
		digitalWrite(CAMERAOUT3_A, 0);
		delay(100);					//150ms pulse for the mobile
		mobile_trigger_off();
  		break;
	  
	  default:						//Hopefully, we won't get here, but add protection anyway...
		break;
		
	  }

	
	uint32_t stop_delay = ((uint16_t)EEPROM.read(EEPROM_SENSORVIDEO_STOPAFTER_HI) << 8)
							| (uint16_t)EEPROM.read(EEPROM_SENSORVIDEO_STOPAFTER_LO);
	if (stop_delay)
	{
		uint8_t stop_delay_units = EEPROM.read(EEPROM_SENSORVIDEO_STOPAFTER_UNITS);
		uint32_t stop_delay_secs = time_units_to_secs(stop_delay, stop_delay_units);
		uint32_t stop_time_secs = get_time_in_secs();
		
		while ((get_time_in_secs() - stop_time_secs) <= stop_delay_secs)
		{
			if (GetButton() == KEY_MINUS)	//cancel selected by the user
			{
				stop_delay_secs = 0;			//user quit requested, exit to 
			}
			
			if(digitalRead(Stack) == 0)
			{
				stop_time_secs = get_time_in_secs();		//if the stack re-triggers, reset the delay length and move to send off signal
			}
		}
	}
	
	
	switch (TriggerOut)					//Time to send the off signal!
	  {
	  
	  case CAMERA_OUT_ONLY: 
	  
		digitalWrite(Focus,1);			//Trigger here!
		digitalWrite(CAMERAOUT2_A, 1);
		digitalWrite(CAMERAOUT3_A, 1);
		delay(50);					//50ms pulse to the focus line stops the video 
		digitalWrite(Focus,0);
		digitalWrite(CAMERAOUT2_A, 0);
		digitalWrite(CAMERAOUT3_A, 0);
  		break;
	  
	  case MOBILE_OUT_ONLY: //mobile
		
		mobile_trigger_on();
		delay(150);
		mobile_trigger_off();
  		break;
	  
	  case BOTH_OUTPUTS:
	  
		digitalWrite(Focus,1);			//Trigger here!
		digitalWrite(CAMERAOUT2_A, 1);
		digitalWrite(CAMERAOUT3_A, 1);
		mobile_trigger_on();
		delay(50);					//50ms pulse to the focus line stops the video 
		digitalWrite(Focus,0);
		digitalWrite(CAMERAOUT2_A, 0);
		digitalWrite(CAMERAOUT3_A, 0);
		delay(100);					//150ms pulse to the focus line stops the mobile video 
		mobile_trigger_off();
  		break;
	  
	  default:						//Hopefully, we won't get here, but add protection anyway...
	  
		digitalWrite(Focus,1);			//Trigger here!
		digitalWrite(CAMERAOUT2_A, 1);
		digitalWrite(CAMERAOUT3_A, 1);
		delay(50);					//50ms pulse to the focus line starts the video 
		digitalWrite(Focus,0);
		digitalWrite(CAMERAOUT2_A, 0);
		digitalWrite(CAMERAOUT3_A, 0);
		break;
	  }
	
	
	digitalWrite(Trigger,0);				//yes, all off and mark that this routine need not be entered again
	digitalWrite(CAMERAOUT2_A, 0);
	digitalWrite(CAMERAOUT3_A, 0);
	digitalWrite(Focus,0);
	digitalWrite(CAMERAOUT2_A, 0);
	digitalWrite(CAMERAOUT3_A, 0);
	StackPowerDown();
	guimenu_operation_complete(GUIMENU_SENSOR_VIDEO_STOP_PAGE, &input_key);
	return ST_SENSORVIDEO_START;
}


char SensorVideoConfigure (char input)
{
	char return_state = SensorSettlingDelay (GUIMENU_SENSORVIDEO_CONFIG_PAGE, ST_SENSORVIDEO_STOP, ST_SENSORVIDEO_START , EEPROM_SENSORVIDEO_TRIGGERON);
	
	return return_state;
}


char SensorVideoDelaySet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_SENSORVIDEO_DELAY_PAGE, &input_key);
	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
				next_state = ST_SENSORVIDEO_START;
			break;
			
			case KEY_DOWN:
				next_state = ST_SENSORVIDEO_STOP_AFTER_SET;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}

char SensorVideoStopAfterActSet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_SENSORVIDEO_STOP_ACT_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_SENSORVIDEO_DELAY;
			break;
			
			case KEY_DOWN:
			next_state = ST_SENSORVIDEO_TRIGGER_SET;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char SensorVideoTriggerSet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_SENSORVIDEO_TRIGGER_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_SENSORVIDEO_STOP_AFTER_SET;
			break;
			
			case KEY_DOWN:
			next_state = ST_SENSORVIDEO_TIMESACTIVE_SET;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char SensorVideoTimesActiveSet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_SENSORVIDEO_TIMESACTIVE_PAGE	, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_SENSORVIDEO_TRIGGER_SET;
			break;
			
			case KEY_DOWN:
			next_state = ST_SENSORVIDEO_STARTTIME_SET;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char SensorVideoStartTimeSet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_SENSORVIDEO_STARTTIME_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_SENSORVIDEO_TIMESACTIVE_SET;
			break;
			
			case KEY_DOWN:
			next_state = ST_SENSORVIDEO_ENDTIME_SET;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char SensorVideoEndTimeSet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_SENSORVIDEO_ENDTIME_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_SENSORVIDEO_STARTTIME_SET;
			break;
			
			case KEY_DOWN:
			next_state = ST_SENSORVIDEO_TRIGGERON_SET;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char SensorVideoTriggerOnSet (char input)
{
	char next_state = 0;
	
	while (!next_state)
	{
		guimenu_selector (GUIMENU_SENSORVIDEO_TRIGGERON_PAGE, &input_key);
		
		switch (input_key)
		{
			case KEY_PREV:
				next_state = ST_SENSORVIDEO_ENDTIME_SET;
			break;
			
			case KEY_DOWN:
				next_state = ST_SENSORVIDEO_TRIGGERON_SET;
			break;
		}
	}

	return next_state;
}

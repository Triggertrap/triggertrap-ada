#include <stdint.h>
#include "Arduino.h"
#include "MenuDefines.h"
#include "HardwareGlobals.h"
#include "guimenu.h"


extern void LowBattery(void);
extern uint32_t get_time_in_secs (void);
unsigned int BatteryCheckCountOuter = 0x02FF, BatteryCheckCountInner = 0x00FF;
extern bool Low_Battery_Flag;

/*****************************************************************************
*
*   Function name : GetButton
*
*   Returns :       Button state
*
*   Parameters :
*
*   Purpose :       reads button and returns result
*
*****************************************************************************/

int GetButton() {
	uint8_t newstate;
	static uint8_t laststate = KEY_NULL;
	volatile static unsigned long OldTime = 0;
	unsigned long ElapsedTime = 0;
	int battery_test;

	BatteryCheckCountOuter++;

	//is the elapsed time larger than the timeout period
	ElapsedTime = millis() - OldTime;

	if(ElapsedTime >= BACKLIGHT_TIMEOUT)
	{
		digitalWrite(BackLight,0);
	}

	if(!digitalRead(UpButton))
	{
		newstate = KEY_PREV;
		ElapsedTime = 0;
		OldTime = millis();
		digitalWrite(BackLight,1);
	}
	
	else if(!digitalRead(SelectButton))
	{

		newstate = KEY_SELECT;
		ElapsedTime = 0;
		OldTime = millis();
		digitalWrite(BackLight,1);
	}
	
	else if(!digitalRead(LeftButton))
	{
		newstate = KEY_MINUS; 
		ElapsedTime = 0;
		OldTime = millis();
		digitalWrite(BackLight,1);
	}
	
	else if(!digitalRead(RightButton))
	{

		newstate = KEY_PLUS;
		ElapsedTime = 0;
		OldTime = millis();
		digitalWrite(BackLight,1);
	}	
	else if(!digitalRead(DownButton))
	{
		newstate = KEY_DOWN;
		ElapsedTime = 0;
		OldTime = millis();
		digitalWrite(BackLight,1);
	}
	else 
	{
		newstate = KEY_NULL;
	}
	
	if (BatteryCheckCountOuter >= 0x00FF)
	{
		BatteryCheckCountOuter = 0;
		BatteryCheckCountInner++;
		
		if (BatteryCheckCountInner >= 0x00FF)
		{	
			BatteryCheckCountInner = 0;
			
			battery_test = analogRead (BATTERY_MON);
	
			if (battery_test <= LOW_BATTERY_LEVEL2)
			{
				LowBattery();		
			}
			else if (battery_test <= LOW_BATTERY_LEVEL1)
			{
				if (Low_Battery_Flag == false)
				{
					guimenu_display_lowbattery_banner ();
					Low_Battery_Flag = true;
				}
			}
			else
			{	if (Low_Battery_Flag == true)
				{
					Low_Battery_Flag = false;
					guimenu_display_normalbattery_banner ();
				}
			}
			
		}
	}
	
	if(laststate == newstate)
	{
		return KEY_NULL;
	}
	
	else
	{
		laststate = newstate;
		return newstate;
	}
	
	
}

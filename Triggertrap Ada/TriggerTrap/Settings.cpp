#include <stdlib.h>
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"
#include "MenuDefines.h"
#include "Arduino.h"
#include "HardwareGlobals.h"
#include "EEPROM.h"
#include "guimenu_pages.h"
#include "guimenu.h"
#include "Inputs.h"
#include "EEPROM.h"


static uint8_t input_key;


char CameraPrefocusSet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_CAMERA_PREFOCUS_PAGE, &input_key);

	while (!next_state)
	{
		switch (input_key)
		{
			case KEY_MINUS:
				next_state = ST_SETTINGS;
				break;
		
			case KEY_DOWN:
				next_state = ST_SETTINGS_OP_SHTPLSE;
			break;
		}
		
		input_key = GetButton();
		
	}
	
	return next_state;
}

char ShutterPulseSet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_SHUTTER_PULSE_PAGE, &input_key);

	while (!next_state)
	{

		switch (input_key)
		{
			case KEY_PREV:
				next_state = ST_SETTINGS_OP_PREFOCUS;
			break;
		
			case KEY_DOWN:
				next_state = ST_SETTINGS_OP_FLSHPLSE;
			break;
		}
		
		input_key = GetButton();
	}
	
	return next_state;
}


char FlashPulseSet (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_FLASH_PULSE_PAGE, &input_key);

	while (!next_state)
	{
		
	
		switch (input_key)
		{
			case KEY_PREV:
				next_state = ST_SETTINGS_OP_SHTPLSE;
			break;
			
			case KEY_DOWN:
				next_state = ST_SETTINGS_SETSYSTEM_TIME;
				break;				
		}
		
		input_key = GetButton();
	}
	
	return next_state;
}

char Timeset (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_SETTINGS_SETSYSTEM_TIME_PAGE, &input_key);

	while (!next_state)
	{	
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_SETTINGS_OP_FLSHPLSE;
			break;
			
			case KEY_DOWN:
			next_state = ST_SETTINGS_ABOUT;
			break;
		}
		input_key = GetButton();
	}
	
	return next_state;
}

char About (char input)
{
	char next_state = 0;

	while (!next_state)
	{
	input_key = GetButton();
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_SETTINGS_SETSYSTEM_TIME;
			break;
		}

	}
	
	return next_state;
}

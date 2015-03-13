#include <stdlib.h>
#include "MenuDefines.h"
#include "Arduino.h"
#include "HardwareGlobals.h"
#include "guimenu.h"
#include "Menu.h"
#include "EEPROM.h"
#include "eeprom_addresses.h"
#include "EEPROM.h"

static long start_time = 0;


////////////////////////////////////////////////
//set time function no range check 24 hours
////////////////////////////////////////////
void set_time (guimenu_time_t  *p_time)
{
	start_time = ((long int)p_time->secs) + ((long int)p_time->mins) * 60
	    + ((long int)p_time->hours) * 3600 - seconds();
}


void get_time (guimenu_time_t  *p_current_time)
{
	unsigned long now = seconds() + start_time;
	p_current_time->hours = (now / 3600) % 24;
	now %= 3600;
	p_current_time->mins = now / 60;
	p_current_time->secs = now % 60;
}


uint32_t 
get_time_in_secs (void)
{
	return seconds();
}


uint32_t
time_units_to_secs (uint16_t time, uint8_t units)
{
	uint32_t secs;
	
	switch (units)
	{
		case GUIMENU_UNITS_H:
			secs = (uint32_t)time * 3600UL;
		break;
		
		case GUIMENU_UNITS_M:
			secs = (uint32_t)time * 60UL;
		break;
		
		case GUIMENU_UNITS_S:
			secs = (uint32_t)time;
		break;
		
		// Just in case units is us, ms or corrupted
		default:
			secs = 0;
		break;
	}
	
	return secs;
}


uint8_t 
time_active (uint16_t eeprom_start_address, uint16_t eeprom_stop_address)
{
	uint8_t active_flag = 0;
	//uint8_t current_seconds = 0;
	uint8_t current_minutes = 0;
	uint8_t current_hours = 0;	
	
	uint8_t start_minutes = 0;
	uint8_t start_hours = 0;
	uint8_t stop_minutes = 0;
	uint8_t stop_hours = 0;
	
	start_hours = EEPROM.read(eeprom_start_address);
	eeprom_start_address++;
	start_minutes = EEPROM.read(eeprom_start_address);
	stop_hours = EEPROM.read(eeprom_stop_address);
	eeprom_stop_address++;
	stop_minutes = EEPROM.read(eeprom_stop_address);

	guimenu_time_t p_current_time;
	get_time (&p_current_time);
	
	current_hours = p_current_time.hours;
	current_minutes = p_current_time.mins;
	//current_seconds = p_current_time.secs;
		
	if (stop_hours < start_hours)
	{
		if (current_hours == start_hours)
		{
			if (current_minutes >= start_minutes)
			{
				active_flag = 1;
			}
		}
		else if(current_hours > start_hours)
		{
			active_flag = 1;
		}
		else if(current_hours == stop_hours)
		{
			if (current_minutes < stop_minutes)
			{
				active_flag = 1;
			}
		}
		else if(current_hours < stop_hours)
		{
			active_flag = 1;
		}
	}
	else
	{
		if(current_hours == start_hours)
		{
			if(current_hours == stop_hours)
			{
				if ((current_minutes >= start_minutes) && (current_minutes < stop_minutes))
				{
					active_flag = 1;  
				}
			}
			else if(current_hours != stop_hours)
			{
				if (current_minutes >= start_minutes)
				{
					active_flag = 1;
				}
			}
		}
		else if((current_hours > start_hours) &&  (current_hours < stop_hours))
		{
			active_flag = 1;
		}	
		else if(current_hours == stop_hours)
		{
			if(current_hours == start_hours)
			{
				if ((current_minutes >= start_minutes) && (current_minutes < stop_minutes))
				{
					active_flag = 1;
				}
			}
			else if(current_hours != start_hours)
			{
				if (current_minutes < stop_minutes)
				{
					active_flag = 1;
				}
			}
		}
	}
	
	return active_flag;
}


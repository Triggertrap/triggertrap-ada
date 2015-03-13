/*
 Triggertrap Ada Source - High Speed Camera Trigger and Intervalometer
 Copyright (C) 2015  Triggertrap
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "main.h"
#include "utils.h"



// read analogue trigger pin
void adc_read (void)
{
    ADCON0 = 0b10011000;
    ADCON0bits.ADON = 1; // turn the ADC module on
    ADCON0bits.GO_nDONE = 1;
    while (GO_nDONE); // wait for conversion to finish
    ADCON0bits.ADON = 0; // turn ADC module off
    adc = ADRES;					// load "adc" with value from ADC output
}


void poll_stack (void)
{
    if (sensor_config.startup == 1) // startup =0 until the opamp settles then will always be 1 to stop false signals on startup
    {
        if (sensor_config.END == 0) // ignore the poll if it is the last sensor in the stack
        {
            if (STACK_IN == 0) // if a signal is being received from the next sensor in the stack
            {
//                if (sensor_config.OR == 1) // if in OR mode and its not the last in the stack then respond
//                {
//                    STACK_OUT = 0; // send signal towards base block
//                    LED = 1; // turn LED on
//                    //count = 0; // starts the count until flags are reset
//                }
//                if ((sensor_config.AND == 1) && (sensor_config.T == 1)) // if in AND mode only respond if its own trigger flag is set
//                {
//                    STACK_OUT = 0; // send signal towards base block
//                    LED = 1; // turn LED on
//                    //count = 0; // starts the count until flags are reset
//                }
                sensor_config.IN = 1; // set STACK_IN trigger flag
            }
            else
            {
                sensor_config.IN = 0; // reset STACK_IN trigger flag

            }
        }
    }
}


void output (void)
{
    if (sensor_config.OR == 1) // if in OR mode
    {
        if (sensor_config.T == 1) // If triggered itself
        {
            STACK_OUT = 0; // send signal
            //LED = 1; // turn LED on
        }
        else if (sensor_config.IN == 1) // trigger itself and received signal from next sensor
        {
            STACK_OUT = 0; // send signal
        }
    }
    else if (sensor_config.AND == 1) // if in AND mode
    {
        if ((sensor_config.END == 1) && (sensor_config.T == 1)) // if triggered itself and its the END sensor, send signal
        {
            //TRISC = 0b10000100;
            STACK_OUT = 0; // send signal
            //LED = 1; // turn LED on
        }
        else if (sensor_config.T == 1)
        {
            if (sensor_config.IN == 1) // trigger itself and received signal from next sensor
            {
                //TRISC = 0b10000100;
                STACK_OUT = 0; // send signal
                //LED = 1; // turn LED on
            }
            else
            {
                STACK_OUT = 1; // send signal
                //LED = 0; // turn LED on
            }
        }
    }

    if (sensor_info.sensor == LASER_SENSOR)
    {
        if (sensor_config.T == 1) // check for trigger
        {
            if (sensor_config.laseroff == 0) // ensures that the laser is turned back on instead of flashing on and off
            {
                if (LASER == 0) // if laser has been turned off
                {
                    __delay_ms(DELAY);
                    __delay_ms(DELAY);
                    __delay_ms(DELAY);;
                    __delay_ms(DELAY);
                    LASER = 1; // turn laser back on
                    sensor_config.laseroff = 1;
                }
            }
        }
    }
}


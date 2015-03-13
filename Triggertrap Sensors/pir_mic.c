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
#include "pir_mic.h"
#include "utils.h"

void pir_mic (unsigned int reset_count, unsigned char low_thold, unsigned char high_thold)
{
    while (1)
    {
        count++;
        count2++;

        // wait for ~150msec before turning off LED and accepting a retrigger
        if (count >= reset_count)
        {
            sensor_config.T = 0; // reset the TRIGGER FLAG
            STACK_OUT = 1; // stop sending signal towards baseblock
            LED = 0; // turn LED off
            sensor_config.startup = 1; // startup =0 until the opamp settles then will always be 1 to stop false signals on startup
        }

//        if (count2 >= reset_count) {
//            sensor_config.IN = 0; // reset the signal from next sensor flag
//        }

        adc_read (); // check PIR output voltage

        if (adc < low_thold) // trigger if movement detected // <1V
        {
            LED = 1;
            count = 0; // starts the 1 second count until flags are reset
            if (sensor_config.startup == 1) // startup =0 until the opamp settles then will always be 1 to stop false signals on startup
            {
                sensor_config.T = 1; // set self trigger flag
            }
        }
        else if (adc > high_thold) // trigger if movement detected // >4V
        {
            LED = 1;
            count = 0; // starts the 1 second count until flags are reset
            if (sensor_config.startup == 1) // startup =0 until the opamp settles then will always be 1 to stop false signals on startup
            {
                sensor_config.T = 1; // set self trigger flag
            }
        }

        poll_stack ();

        output (); // check for any trigger flags
    }
}

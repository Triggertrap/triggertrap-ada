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

#include "Main.h"
#include "laser.h"
#include "utils.h"

void laser (void)
{
    while (1)
    {
        sensor_config.laseroff = 0;

        // switch set to trigger if beam is broken
        while (SWITCH == 0)
        {
            count++;
            count2++;

            if (count >= LASER_RESET_COUNT) // wait before accepting retrigger
            {
                sensor_config.T = 0; // reset the TRIGGER FLAG
                STACK_OUT = 1; // stop sending signal towards baseblock
                LED = 0; // turn LED off
                sensor_config.startup = 1; // startup =0 until the opamp settles then will always be 1 to stop false signals on startup
            }

//            if (count2 >= LASER_RESET_COUNT2) {
//                sensor_config.IN = 0; // reset the signal from next sensor flag
//            }

            LASER = 1; // makes sure laser is switched on before the ADC read (needs to be here for LOW POWER mode)

            adc_read(); // check photodiode output voltage        

            if (sensor_info.low_power == 1)
            {
                LASER = 0; // if its in LOW POWEr mode then turn the laser OFF after the ADC read
            }
            if (adc < LASER_LOW_THRESHOLD) // if no laser is detected
            {
                if (sensor_config.laseroff == 0) // laseroff ensures the laser doesn't keep flashing ON and OFF while triggered but the LED stays lit up
                {
                    LED = 1;
                    LASER = 0;
                    count = 0; // starts the 1 second count until flags are reset
                    if (sensor_config.startup == 1) // startup =0 until the opamp settles then will always be 1 to stop false signals on startup
                    {
                        sensor_config.T = 1; // set self trigger flag
                    }
                }
                count = 0; // starts the 1 second count until flags are reset
            }
            else // laser detected again
            {
                sensor_config.laseroff = 0; // laseroff only =0 when it detects the laser again ( LED stays on during trigger but the LASER doesn't keep flashing On and OFF)
                sensor_config.T = 0; // reset self trigger flag
            }

            poll_stack ();

            output (); // check for any trigger flags
        }

        sensor_config.laseroff = 0;

        // switch is set to trigger when it picks up a laser
        while (SWITCH == 1)
        {
            count++;
            count2++;
            if (count >= LASER_RESET_COUNT) // wait before accepting retrigger
            {
                sensor_config.T = 0; // reset the TRIGGER FLAG
                STACK_OUT = 1; // stop sending signal towards baseblock
                LED = 0; // turn LED off
                sensor_config.startup = 1; // startup =0 until the opamp settles then will always be 1 to stop false signals on startup
            }

            if (count2 >= LASER_RESET_COUNT2) {
                sensor_config.IN = 0; // reset signal from next sensor flag
            }

            LASER = 1; // makes sure laser is switched on before the ADC read (needs to be here for LOW POWER mode)
       
            adc_read(); // check photodiode output voltage
          
            if (sensor_info.low_power == 1) {
                LASER = 0; // if its in LOW POWEr mode then turn the laser OFF after the ADC read
            }

            if (adc > LASER_HIGH_THRESHOLD) // if laser is detected
            {
                if (sensor_config.laseroff == 0) // laseroff ensures the laser doesn't keep flashing ON and OFF while triggered but the LED stays lit up
                {
                    LED = 1;
                    LASER = 0;
                    if (sensor_config.startup == 1) // startup =0 until the opamp settles then will always be 1 to stop false signals on startup
                    {
                        sensor_config.T = 1; // set the self trigger flag
                    }
                }
                count = 0; // starts the 1 second count until flags are reset
            }
            else //if laser is not detected, resets variable
            {
                sensor_config.laseroff = 0; // laseroff only =0 when it detects the laser again ( LED stays on during trigger but the LASER doesn't keep flashing On and OFF)
                sensor_config.T = 0; // reset self trigger flag
            }

            poll_stack ();

            output (); // check for any trigger flags
        }
    }
}

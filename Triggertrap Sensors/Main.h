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

#ifdef LASER_SENSOR_VERSION
#define _XTAL_FREQ 16000000
#else
#define _XTAL_FREQ 8000000
#endif
#include <xc.h>

#define	LASER		PORTCbits.RC6
#define	SWITCH		PORTCbits.RC7
#define LED		PORTCbits.RC5
#define STACK_IN	PORTAbits.RA2
#define STACK_OUT	PORTCbits.RC1
#define SHDN_B		PORTCbits.RC4

#define OPTION_SELECT1  RB6
#define OPTION_SELECT2  RB5


// Sensor Types
#define PIR_SENSOR      1
#define MIC_SENSOR      2
#define LIGHT_SENSOR    3
#define LASER_SENSOR    4

#define DELAY           17
#define DELAY1          170
#define DELAY2          21
#define DELAY3          340

#ifdef LASER_SENSOR_VERSION
#define AND_PULSE_COUNT     16000
#define NEXT_SENSOR_COUNT   60000
#else
#define AND_PULSE_COUNT     8000
#define NEXT_SENSOR_COUNT   30000
#endif

typedef struct {
    unsigned int AND : 1; // struct is used to save flash memory space
    unsigned int OR : 1;
    unsigned int END : 1;
    unsigned int IN : 1;
    unsigned int startup : 1;
    unsigned int T : 1;
    unsigned int Y : 1;
    unsigned int laseroff : 1;
} SENSOR_CONFIG;

typedef struct {
    unsigned char sensor : 3;
    unsigned int low_power : 1;
} SENSOR_INFO;


extern SENSOR_INFO sensor_info;
extern SENSOR_CONFIG sensor_config;
extern unsigned int count, count2;
extern char adc;

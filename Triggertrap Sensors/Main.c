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
#include "light.h"
#include "laser.h"
#include "utils.h"

/* CONFIG BITS */
#ifdef LASER_SENSOR_VERSION
#pragma config FOSC = HS        // Oscillator Selection (HS oscillator and automatic 18 ms DRT (DRTEN ignored))
#else
#pragma config FOSC = INTRC_IO  // Oscillator Selection (INTRC with I/O function on OSC2/CLKOUT and 10 us startup time)
#endif

#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT Disabled)
#pragma config CP = OFF         // Code Protection - User Program Memory (Code protection off)
#pragma config MCLRE = OFF      // Master Clear Enable (MCLR pin functions as MCLR)
#pragma config IOSCFS = 8MHz    // Internal Oscillator Frequency Select (8 MHz INTOSC Speed)
#pragma config CPSW = OFF       // Code Protection - Self Writable Memory (Code protection off)
#pragma config BOREN = OFF      // Brown-out Reset Enable (BOR Disabled)
#pragma config DRTEN = OFF      // Device Reset Timer Enable (DRT Disabled)

// Globals
SENSOR_INFO sensor_info;
SENSOR_CONFIG sensor_config;
unsigned int count = 0, count2 = 0;
unsigned char adc = 0;


void init (void);
void option_select (void);
void ping (void);


void main (void)
{
    init(); // initialise ports
    option_select (); // Check which sensor is connected
    RC5 = 0;
    sensor_info.low_power = 0;
    LASER = 0;
    ping (); // wait for signal from baseblock, then send signal back

    //TRISC = 0b10000100;
    STACK_OUT = 1;
    SHDN_B = 1; // Turn on opamp used for PIR
    //TRISC = 0b10000100;
    //  count=0;

    switch (sensor_info.sensor)
    {
        case PIR_SENSOR:
            pir_mic (PIR_RESET_COUNT, PIR_LOW_THRESHOLD, PIR_HIGH_THRESHOLD);
        break;

        case MIC_SENSOR:
            pir_mic (MIC_RESET_COUNT, MIC_LOW_THRESHOLD, MIC_HIGH_THRESHOLD);
        break;

        case LIGHT_SENSOR:
            light ();
        break;

        case LASER_SENSOR:
            laser ();
        break;
    }

    while (1);
}


void init (void)
{
    PORTAbits.RA1 = 1;

    TRISA = 0x28; // STACK_IN as input

    TRISC = 0x84; // SET ANA_TRIG AND SWITCH AS INPUTS

    TRISB = 0b11100000; // TEST PIN AND VOLTAGE DIVIDERS AS INPUTS

    CM2CON0bits.C2PREF2 = 1;
    CM2CON0bits.C2ON = 0;
    ANSELbits.ANS5 = 0;
}


// Selects which sensor board it is based on voltage dividers, chooses which main code to follow
void option_select (void)
{
    __delay_ms (DELAY);
    if (OPTION_SELECT1 == 0)
    {
        if (OPTION_SELECT2 == 0)
        {
            sensor_info.sensor = PIR_SENSOR;
        } 
        else
        {
            sensor_info.sensor = MIC_SENSOR;
        }
    } 
    else if (OPTION_SELECT1 == 1)
    {
        if (OPTION_SELECT2 == 0)
        {
            sensor_info.sensor = LIGHT_SENSOR;
        } 
        else
        {
            sensor_info.sensor = LASER_SENSOR;
        }
    }
}


// wait for signal from baseblock/adjacent sensor
void ping (void)
{
    unsigned int a = 0;
    ANSELbits.ANS2 = 0;
    OPTION = 11000000;
    CM1CON0bits.nC1OUTEN = 1;
    CM1CON0bits.C1ON = 0;
    PORTAbits.RA2 = 1;
    STACK_OUT = 1;
    sensor_config.Y = 0;
    count = 0;
    LED = 0;
    TRISC = 0b10000110; // switch STACK_OUT (jack) to an input
    while (sensor_config.Y == 0) // waits here for the first pulse (OR mode)
    {
        if (STACK_OUT == 0) {
            sensor_config.OR = 1;
            sensor_config.Y = 1; // OR MODE
            count = 1; // increase count to 1
            while (STACK_OUT == 0); // make sure first pulse has ended
        }
    }
    while (a < AND_PULSE_COUNT) // wait for another pulse (AND mode)
    {
        if (STACK_OUT == 0) // if a second pulse is detected
        {
            sensor_config.AND = 1;
            sensor_config.OR = 0; // AND MODE
            count = 2; // change count to 2
            a = (AND_PULSE_COUNT + 1000); // end the count
            while (STACK_OUT == 0); // make sure second pulse has ended
        }
        a++;

    }
//    a = 0;
//    sensor_info.low_power = 0;
//    while (a < 8000) // wait 8000 counts for a third pulse (OR mode LOW POWER)
//    {
//        if (STACK_OUT == 0) // if a third pulse is detected
//        {
//            sensor_config.AND = 0;
//            sensor_config.OR = 1; // OR MODE
//            sensor_info.low_power = 1; // LOW POWER
//            count = 3; // change count to 3
//            a = 9000; // end the count
//            while (STACK_OUT == 0); // make sure third pulse has ended
//        }
//        a++;
//    }
//    a = 0;
//    while (a < 8000) // wait 8000 counts for a fourth pulse (AND mode LOW POWER)
//    {
//        if (STACK_OUT == 0) {
//            sensor_config.AND = 1; // AND MODE
//            sensor_config.OR = 0;
//            sensor_info.low_power = 1; // LOW POWER
//            count = 4; // change count to 4
//            a = 9000; // end the count
//            while (STACK_OUT == 0); // make sure final pulse has ended
//        }
//        a++;
//    }

    if (count == 1) // if only 1 pulse was received
    {
        TRISA = 0b00100000;
        STACK_IN = 0; // pulse STACK_IN(socket) once
        __delay_ms (DELAY2);
        STACK_IN = 1;
        TRISA = 0b00101000;
        LED = 1; // flash LED once to indicate OR mode
        __delay_ms (DELAY3);
        LED = 0;
    }
    if (count >= 2) // if second pulse was detected
    {
        STACK_IN = 0; // pulse STACK_IN(socket) twice
        __delay_ms (DELAY2);
        STACK_IN = 1;
        __delay_ms (DELAY2);
        STACK_IN = 0;
        __delay_ms (DELAY2);
        STACK_IN = 1;
//        if (count == 3) // if a third pulse was received
//        { // send a THIRD pulse
//            __delay_ms (DELAY2);
//            STACK_IN = 0;
//            __delay_ms (DELAY2);
//            STACK_IN = 1;
//        }
//        if (count == 4) // if a fourth pulse was received
//        { // send a FOURTH pulse
//            __delay_ms (DELAY2);
//            STACK_IN = 0;
//            __delay_ms (DELAY2);
//            STACK_IN = 1;
//        }
        TRISA = 0b00101000;
        LED = 1; // LED is only flashed once for count=3 ( OR MODE LOW POWER)
        __delay_ms (DELAY1); // this had to be done due to memory issues :(
        LED = 0;
        if (count != 3) // if count !=3 then flash 3 times to signal AND MODE
        {
            __delay_ms (DELAY1);
            LED = 1;
            __delay_ms (DELAY1);
            LED = 0;
            __delay_ms (DELAY1);
            LED = 1;
            __delay_ms (DELAY1);
            LED = 0;
        }
    }

    TRISC = 0b10000100; // set STACK_IN(jack) back to an output
    STACK_OUT = 0;
    a = 0;
    TRISA = 0b00101100; // set STACK_OUT(socket) back to an input
    ANSELbits.ANS2 = 0;
    OPTION = 11000000;
    CM1CON0bits.nC1OUTEN = 1;
    CM1CON0bits.C1ON = 0;
    sensor_config.END = 0; // clear the END flag for ALL SENSORS
    while (a < NEXT_SENSOR_COUNT) // wait for signal coming back towards baseblock from next sensor
    {
        if (STACK_IN == 0) { // if a signal arrives
            a = (NEXT_SENSOR_COUNT + 5000); // immediately ends the while loop and makes the next if statement TRUE
        }
        a++;
    }
    if (a < (NEXT_SENSOR_COUNT + 1000)) // if signal never arrives
    {
        LED = 1; // flash the LED twice to signal its the end sensor
        __delay_ms (DELAY1);
        LED = 0;
        __delay_ms (DELAY1);
        LED = 1;
        __delay_ms (DELAY1);
        LED = 0;
        sensor_config.END = 1; // Set the sensor board as the END sensor
    }
}


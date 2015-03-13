/*
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

*/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>


//#define USE_RTC // Use RTC for millis etc.

#define REPEAT8(x) x, x, x, x, x, x, x, x
#define BV0TO7 _BV(0), _BV(1), _BV(2), _BV(3), _BV(4), _BV(5), _BV(6), _BV(7)
#define BV7TO0 _BV(7), _BV(6), _BV(5), _BV(4), _BV(3), _BV(2), _BV(1), _BV(0)

#define NUM_DIGITAL_PINS            28
#define NUM_ANALOG_INPUTS           6
#define EXTERNAL_NUM_INTERRUPTS     36 // PORTA to PORTE 3

#define analogInputToDigitalPin(p)  ((p < 6) ? (p) + 22 : -1)
#define digitalPinHasPWM(p)         (((p) >= 2 && (p) <= 6) || ((p) >= 9 && (p)<= 11) || ((p) >= 14 && (p)<= 19))

static const uint8_t SS    = 6;
static const uint8_t MOSI  = 11;
static const uint8_t MISO  = 12;
static const uint8_t SCK   = 13;

static const uint8_t SDA = 2;
static const uint8_t SCL = 3;
static const uint8_t LED_BUILTIN = 13;

static const uint8_t A0 = 22;
static const uint8_t A1 = 23;
static const uint8_t A2 = 24;
static const uint8_t A3 = 25;
static const uint8_t A4 = 26;
static const uint8_t A5 = 27;

#define Wire xmWireC
#define Wire1 xmWireE

#define SPI_PORT	SPID

#define digitalPinToPCICR(p)    (((p) >= 0 && (p) <= 21) ? (&PCICR) : ((uint8_t *)0))
#define digitalPinToPCICRbit(p) (((p) <= 7) ? 2 : (((p) <= 13) ? 0 : 1))
#define digitalPinToPCMSK(p)    (((p) <= 7) ? (&PCMSK2) : (((p) <= 13) ? (&PCMSK0) : (((p) <= 21) ? (&PCMSK1) : ((uint8_t *)0))))
#define digitalPinToPCMSKbit(p) (((p) <= 7) ? (p) : (((p) <= 13) ? ((p) - 8) : ((p) - 14)))

#ifdef ARDUINO_MAIN

// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)
const uint16_t PROGMEM port_to_PGM[] = {
	NOT_A_PORT,
	(uint16_t) &PORTA,
	(uint16_t) &PORTB,
	(uint16_t) &PORTC,
	(uint16_t) &PORTD,
	(uint16_t) &PORTE,
	(uint16_t) &PORTF,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] = {
		// PORTLIST
		PA,/* KEY1 */
		PA,/* KEY2 */
		PA,/* KEY3 */
		PA,/* KEY4 */
		PA,/* KEY5 */
		PB,/* BAT_MON */
		PB,/* AUDIO_L */ 
		PB,/* AUDIO_R */
#ifdef	VERSION_THREE_HW
		PE,/* MIC */
#else
		PB,/* MIC */		
#endif		
		PC,/* DC */
		PC,/* CE */
		PC,/* CLK */
		PC,/* DIN */
		PC,/* LCD_RST */
		PC,/* LDO_EN */
		PE,/* FTDI_RTS */
		PE,/* FTDI_CTS */
		PE,/* FTDI_TXD */
		PE,/* FTDI_RXD */
#ifdef	VERSION_THREE_HW
		PA,/* STACK_SW */
#else
		PE,/* STACK_SW */
#endif
		PF,/* TRIGGER 1 */
		PF,/* TRIGGER 2 */
		PF,/* TRIGGER 3 */
		PF,/* TRIGGER 4 */
		PF,/* TRIGGER 5 */
		PF,/* TRIGGER 6 */
		PF,/* BACKLIGHT */		
		PF,/* STACK_IN */
#ifdef	VERSION_THREE_HW
		PC,/* LCD POWER */
#else
		PD,/* BONUS_PIN */
#endif
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = {
		// PIN IN PORT		
		// -------------------------------------------		
		_BV( 0 ),/* KEY1 */
		_BV( 1 ),/* KEY2 */
		_BV( 2 ),/* KEY3 */
		_BV( 3 ),/* KEY4 */
		_BV( 4 ),/* KEY5 */
		_BV( 1 ),/* BAT_MON */
		_BV( 2 ),/* AUDIO_L */ 
		_BV( 3 ),/* AUDIO_R */
		_BV( 4 ),/* MIC */
		_BV( 0 ),/* DC */
		_BV( 1 ),/* CE */
		_BV( 2 ),/* CLK */
		_BV( 3 ),/* DIN */
		_BV( 4 ),/* LCD_RST */
		_BV( 5 ),/* LDO_EN */
		_BV( 0 ),/* FTDI_RTS */
		_BV( 1 ),/* FTDI_CTS */
		_BV( 2 ),/* FTDI_TXD */
		_BV( 3 ),/* FTDI_RXD */
#ifdef	VERSION_THREE_HW
		_BV( 5 ),/* STACK_SW */
#else
		_BV( 7 ),/* STACK_SW */
#endif
		_BV( 0 ),/* TRIGGER 1 */
		_BV( 1 ),/* TRIGGER 2 */
		_BV( 2 ),/* TRIGGER 3 */
		_BV( 3 ),/* TRIGGER 4 */
		_BV( 4 ),/* TRIGGER 5 */
		_BV( 5 ),/* TRIGGER 6 */
		_BV( 6 ),/* BACKLIGHT */
		_BV( 7 ),/* STACK_IN */
#ifdef	VERSION_THREE_HW
		_BV( 7 ),/* LCD POWER */
#else
		_BV( 5 ),/* BONUS_PIN */
#endif
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = {
	// TIMERS		
	// -------------------------------------------		
	TIMER_C0C	, // 0
	TIMER_C0D	, 
	TIMER_C0A	, 
	TIMER_C0B	, 
	TIMER_D0C	, 
	TIMER_D0D	, 
	TIMER_D1A	, 
	NOT_ON_TIMER	, 
	NOT_ON_TIMER	, 
	TIMER_C1A	, // 8
	TIMER_C1B	, 
	TIMER_D1B	, 
	NOT_ON_TIMER	, 
	NOT_ON_TIMER	, 
	TIMER_E0A	, // 14
	TIMER_E0B	, 
	TIMER_E0C	, 
	TIMER_E0D	, 
	TIMER_D0A	, 
	TIMER_D0B	, 
	NOT_ON_TIMER	, 
	NOT_ON_TIMER	, // 21
	NOT_ON_TIMER	, // A0
	NOT_ON_TIMER	, 
	NOT_ON_TIMER	, 
	NOT_ON_TIMER	, 
	NOT_ON_TIMER	, 
	NOT_ON_TIMER	, 
};

const TC0_t* timer_to_tc0_PGM[] = {
	NULL,

	&TCC0,
	&TCC0,
	&TCC0,
	&TCC0,
	NULL,
	NULL,

	&TCD0,
	&TCD0,
	&TCD0,
	&TCD0,
	NULL,
	NULL,

	&TCE0,
	&TCE0,
	&TCE0,
	&TCE0,
	NULL,
	NULL,
	};

const TC1_t* timer_to_tc1_PGM[] = {
	NULL,

	NULL,
	NULL,
	NULL,
	NULL,
	&TCC1,
	&TCC1,

	NULL,
	NULL,
	NULL,
	NULL,
	&TCD1,
	&TCD1,

	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
};


const uint8_t PROGMEM timer_to_channel_PGM[] = {
	NOT_ON_TIMER,

    0,
    1,
    2,
    3,
    0,
    1,

    0,
    1,
    2,
    3,
    0,
    1,

    0,
    1,
    2,
    3,
    0,
    1,
};

const uint8_t PROGMEM adc_to_channel_PGM[] = {
    0,
    1,
    2,
    3,
    4,
    5,
};

#endif

#endif

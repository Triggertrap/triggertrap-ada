#include <stdint.h>
#include <avr/pgmspace.h>
#include "eeprom_addresses.h"
#include "guimenu.h"
#include "tt_strings.h"
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"

#define NO_BITMAP			0
#define NO_TITLE			0
#define NO_BANNER			0
#define NO_BUTTON			0
#define NO_SELECTOR			0
#define NO_LIST				0
#define NO_PROGRESSBAR		0
#define NO_SETTINGS			false
#define MORE_SETTINGS		true
#define INVERT_TEXT			true
#define	NO_INVERT_TEXT		false
#define NO_SCROLLBAR		0
#define INVERT_BAR			true
#define NO_INVERT_BAR		false

#ifndef INCLUDE_NEWMODE
#define NUM_MODES_IN_MAIN_MENU	10
#else
#define NUM_MODES_IN_MAIN_MENU	11
#endif


// GUIMENU_START_PAGE
const uint8_t ada_bitmap[LCDWIDTH * LCDHEIGHT / 8] PROGMEM = 
{
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0xC0         ,/*  ______##  */ 
	0xF0         ,/*  ____####  */ 
	0xF8         ,/*  ___#####  */ 
	0xFC         ,/*  __######  */ 
	0xFE         ,/*  _#######  */ 
	0x3F         ,/*  ######__  */ 
	0x9F         ,/*  #####__#  */ 
	0xCF         ,/*  ####__##  */ 
	0xE7         ,/*  ###__###  */ 
	0xE0         ,/*  _____###  */ 
	0xF0         ,/*  ____####  */ 
	0xF0         ,/*  ____####  */ 
	0x70         ,/*  ____###_  */ 
	0x70         ,/*  ____###_  */ 
	0x70         ,/*  ____###_  */ 
	0x70         ,/*  ____###_  */ 
	0xF0         ,/*  ____####  */ 
	0xF0         ,/*  ____####  */ 
	0xE0         ,/*  _____###  */ 
	0xE6         ,/*  _##__###  */ 
	0xCF         ,/*  ####__##  */ 
	0x9F         ,/*  #####__#  */ 
	0x3F         ,/*  ######__  */ 
	0x7E         ,/*  _######_  */ 
	0xFC         ,/*  __######  */ 
	0xF8         ,/*  ___#####  */ 
	0xF0         ,/*  ____####  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x80         ,/*  _______#  */ 
	0x80         ,/*  _______#  */ 
	0x80         ,/*  _______#  */ 
	0x80         ,/*  _______#  */ 
	0x80         ,/*  _______#  */ 
	0x80         ,/*  _______#  */ 
	0x80         ,/*  _______#  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0xE0         ,/*  _____###  */ 
	0xE0         ,/*  _____###  */ 
	0xE0         ,/*  _____###  */ 
	0xE0         ,/*  _____###  */ 
	0xE0         ,/*  _____###  */ 
	0xE0         ,/*  _____###  */ 
	0xC0         ,/*  ______##  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0xFE         ,/*  _#######  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0x00         ,/*  ________  */ 
	0xFE         ,/*  _#######  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xC7         ,/*  ###___##  */ 
	0x01         ,/*  #_______  */ 
	0x01         ,/*  #_______  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x01         ,/*  #_______  */ 
	0x01         ,/*  #_______  */ 
	0xC7         ,/*  ###___##  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFC         ,/*  __######  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x80         ,/*  _______#  */ 
	0xF0         ,/*  ____####  */ 
	0xFE         ,/*  _#######  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFE         ,/*  _#######  */ 
	0xF0         ,/*  ____####  */ 
	0x80         ,/*  _______#  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0xC0         ,/*  ______##  */ 
	0xC0         ,/*  ______##  */ 
	0xE0         ,/*  _____###  */ 
	0xF0         ,/*  ____####  */ 
	0xF0         ,/*  ____####  */ 
	0xF0         ,/*  ____####  */ 
	0xF0         ,/*  ____####  */ 
	0xF0         ,/*  ____####  */ 
	0xE0         ,/*  _____###  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0xE0         ,/*  _____###  */ 
	0xF0         ,/*  ____####  */ 
	0xF0         ,/*  ____####  */ 
	0xF0         ,/*  ____####  */ 
	0xF0         ,/*  ____####  */ 
	0xF0         ,/*  ____####  */ 
	0xF0         ,/*  ____####  */ 
	0xF0         ,/*  ____####  */ 
	0xE0         ,/*  _____###  */ 
	0xE0         ,/*  _____###  */ 
	0xE0         ,/*  _____###  */ 
	0xC0         ,/*  ______##  */ 
	0x80         ,/*  _______#  */ 
	0x00         ,/*  ________  */ 
	0x30         ,/*  ____##__  */ 
	0x70         ,/*  ____###_  */ 
	0xF8         ,/*  ___#####  */ 
	0xF8         ,/*  ___#####  */ 
	0xF0         ,/*  ____####  */ 
	0xC7         ,/*  ###___##  */ 
	0x9F         ,/*  #####__#  */ 
	0x3F         ,/*  ######__  */ 
	0x7F         ,/*  #######_  */ 
	0xFC         ,/*  __######  */ 
	0xF9         ,/*  #__#####  */ 
	0xF3         ,/*  ##__####  */ 
	0xE7         ,/*  ###__###  */ 
	0xCF         ,/*  ####__##  */ 
	0x9F         ,/*  #####__#  */ 
	0x9E         ,/*  _####__#  */ 
	0x3E         ,/*  _#####__  */ 
	0x3C         ,/*  __####__  */ 
	0x3C         ,/*  __####__  */ 
	0x3C         ,/*  __####__  */ 
	0x3C         ,/*  __####__  */ 
	0x3E         ,/*  _#####__  */ 
	0x3E         ,/*  _#####__  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x0F         ,/*  ####____  */ 
	0x07         ,/*  ###_____  */ 
	0x03         ,/*  ##______  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0xF0         ,/*  ____####  */ 
	0xFE         ,/*  _#######  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xF3         ,/*  ##__####  */ 
	0xF0         ,/*  ____####  */ 
	0xF3         ,/*  ##__####  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFE         ,/*  _#######  */ 
	0xF0         ,/*  ____####  */ 
	0x00         ,/*  ________  */ 
	0x78         ,/*  ___####_  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0x87         ,/*  ###____#  */ 
	0x03         ,/*  ##______  */ 
	0x03         ,/*  ##______  */ 
	0x87         ,/*  ###____#  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0x00         ,/*  ________  */ 
	0xE0         ,/*  _____###  */ 
	0xF3         ,/*  ##__####  */ 
	0xFB         ,/*  ##_#####  */ 
	0xFB         ,/*  ##_#####  */ 
	0xFB         ,/*  ##_#####  */ 
	0x7B         ,/*  ##_####_  */ 
	0x7B         ,/*  ##_####_  */ 
	0x73         ,/*  ##__###_  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0xFF         ,/*  ########  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x01         ,/*  #_______  */ 
	0x03         ,/*  ##______  */ 
	0x07         ,/*  ###_____  */ 
	0x0F         ,/*  ####____  */ 
	0x1F         ,/*  #####___  */ 
	0x3F         ,/*  ######__  */ 
	0x3E         ,/*  _#####__  */ 
	0x7C         ,/*  __#####_  */ 
	0x79         ,/*  #__####_  */ 
	0x3B         ,/*  ##_###__  */ 
	0x03         ,/*  ##______  */ 
	0x07         ,/*  ###_____  */ 
	0x07         ,/*  ###_____  */ 
	0x0F         ,/*  ####____  */ 
	0x0F         ,/*  ####____  */ 
	0x0F         ,/*  ####____  */ 
	0x0F         ,/*  ####____  */ 
	0x0F         ,/*  ####____  */ 
	0x0F         ,/*  ####____  */ 
	0x0F         ,/*  ####____  */ 
	0x0F         ,/*  ####____  */ 
	0x07         ,/*  ###_____  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x18         ,/*  ___##___  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x07         ,/*  ###_____  */ 
	0x03         ,/*  ##______  */ 
	0x03         ,/*  ##______  */ 
	0x03         ,/*  ##______  */ 
	0x03         ,/*  ##______  */ 
	0x03         ,/*  ##______  */ 
	0x03         ,/*  ##______  */ 
	0x03         ,/*  ##______  */ 
	0x07         ,/*  ###_____  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x1E         ,/*  _####___  */ 
	0x18         ,/*  ___##___  */ 
	0x13         ,/*  ##__#___  */ 
	0x0F         ,/*  ####____  */ 
	0x0F         ,/*  ####____  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x0F         ,/*  ####____  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x00         ,/*  ________  */ 
	0x0F         ,/*  ####____  */ 
	0x0F         ,/*  ####____  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x1E         ,/*  _####___  */ 
	0x1E         ,/*  _####___  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x1F         ,/*  #####___  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         ,/*  ________  */ 
	0x00         /*  ________  */ 
};

guimenu_page_t start_page =
{
	ada_bitmap,
	NO_TITLE,
	NO_BANNER,
	NO_BUTTON,
	false,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	NO_SCROLLBAR		
};

// GUIMENU_TIMELAPSE_TITLE_PAGE
guimenu_title_t timelapse_title =
{
	GUIMENU_ONE,
	GUIMENU_TIMELAPSE,	
	GUIMENU_NULL_STRING,
	NO_INVERT_TEXT
};

guimenu_scrollbar_t timelapse_scrollbar =
{
	1,
	NUM_MODES_IN_MAIN_MENU
};

guimenu_page_t timelapse_title_page =
{
	NO_BITMAP,
	&timelapse_title,
	NO_BANNER,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	&timelapse_scrollbar		
};

// GUIMENU_TIMEWARP_TITLE_PAGE
guimenu_title_t timewarp_title =
{
	GUIMENU_TWO,
	GUIMENU_TIMEWARP,	
	GUIMENU_NULL_STRING,
	NO_INVERT_TEXT
};

guimenu_scrollbar_t timewarp_scrollbar =
{
	2,
	NUM_MODES_IN_MAIN_MENU
};

guimenu_page_t timewarp_title_page =
{
	NO_BITMAP,
	&timewarp_title,
	NO_BANNER,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	&timewarp_scrollbar		
};

// GUIMENU_BULBRAMPING_TITLE_PAGE
guimenu_title_t bulbramping_title =
{
	GUIMENU_THREE,
	GUIMENU_BULB,
	GUIMENU_RAMPING,
	NO_INVERT_TEXT
};

guimenu_scrollbar_t bumpramping_scrollbar =
{
	3,
	NUM_MODES_IN_MAIN_MENU
};

guimenu_page_t bulbramping_title_page =
{
	NO_BITMAP,
	&bulbramping_title,
	NO_BANNER,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	&bumpramping_scrollbar
};

// GUIMENU_STARTRAIL_TITLE_PAGE
guimenu_title_t startrail_title =
{
	GUIMENU_FOUR,
	GUIMENU_STAR,
	GUIMENU_TRAIL,
	NO_INVERT_TEXT
};

guimenu_scrollbar_t startrail_scrollbar =
{
	4,
	NUM_MODES_IN_MAIN_MENU
};

guimenu_page_t startrail_title_page =
{
	NO_BITMAP,
	&startrail_title,
	NO_BANNER,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	&startrail_scrollbar
};

// GUIMENU_HISPEEDFLASH_TITLE_PAGE
guimenu_title_t hsf_title =
{
	GUIMENU_FIVE,
	GUIMENU_HIGHSPEED,
	GUIMENU_FLASH,
	NO_INVERT_TEXT
};

guimenu_scrollbar_t hsf_scrollbar =
{
	5,
	NUM_MODES_IN_MAIN_MENU
};

guimenu_page_t hsf_title_page =
{
	NO_BITMAP,
	&hsf_title,
	NO_BANNER,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	&hsf_scrollbar
};

// GUIMENU_SENSOR_TITLE_PAGE
guimenu_title_t sensor_title =
{
	GUIMENU_SIX,
	GUIMENU_SENSOR,
	GUIMENU_NULL_STRING,
	NO_INVERT_TEXT
};

guimenu_scrollbar_t sensor_scrollbar =
{
	6,
	NUM_MODES_IN_MAIN_MENU
};

guimenu_page_t sensor_title_page =
{
	NO_BITMAP,
	&sensor_title,
	NO_BANNER,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	&sensor_scrollbar
};

// GUIMENU_SENSORTLAPSE_TITLE_PAGE
guimenu_title_t sensortlapse_title =
{
	GUIMENU_SEVEN,
	GUIMENU_SENSOR,
	GUIMENU_TIMELAPSE,
	NO_INVERT_TEXT
};

guimenu_scrollbar_t sensortlapse_scrollbar =
{
	7,
	NUM_MODES_IN_MAIN_MENU
};

guimenu_page_t sensortlapse_title_page =
{
	NO_BITMAP,
	&sensortlapse_title,
	NO_BANNER,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	&sensortlapse_scrollbar
};

// GUIMENU_SENSORVIDEO_TITLE_PAGE
guimenu_title_t sensorvideo_title =
{
	GUIMENU_EIGHT,
	GUIMENU_SENSOR,
	GUIMENU_VIDEO,
	NO_INVERT_TEXT
};

guimenu_scrollbar_t sensorvideo_scrollbar =
{
	8,
	NUM_MODES_IN_MAIN_MENU,
	NO_INVERT_BAR
};

guimenu_page_t sensorvideo_title_page =
{
	NO_BITMAP,
	&sensorvideo_title,
	NO_BANNER,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	&sensorvideo_scrollbar
};

// GUIMENU_ADVSENSOR_TITLE_PAGE
guimenu_title_t advsensor_title =
{
	GUIMENU_NINE,
	GUIMENU_ADVANCED,
	GUIMENU_SENSOR,
	NO_INVERT_TEXT
};

guimenu_scrollbar_t advsensor_scrollbar =
{
	9,
	NUM_MODES_IN_MAIN_MENU
};

guimenu_page_t advsensor_title_page =
{
	NO_BITMAP,
	&advsensor_title,
	NO_BANNER,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	&advsensor_scrollbar
};

// GUIMENU_LEHDR_TITLE_PAGE
guimenu_title_t lehdr_title =
{
	GUIMENU_TEN,
	GUIMENU_LEHDR,
	GUIMENU_NULL_STRING,
	NO_INVERT_TEXT
};

guimenu_scrollbar_t lehdr_scrollbar =
{
	10,
	NUM_MODES_IN_MAIN_MENU,
	NO_INVERT_BAR
};

guimenu_page_t lehdr_title_page =
{
	NO_BITMAP,
	&lehdr_title,
	NO_BANNER,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	&lehdr_scrollbar
};

// GUIMENU_TIMELAPSE_START_PAGE
guimenu_scrollbar_t timelapse1_scrollbar =
{
	1,
	7
};

guimenu_banner_t timelapse_banner =
{
	GUIMENU_TIMELAPSE,
	GUIMENU_NULL_STRING
};

guimenu_page_t timelapse_start_page =
{
	NO_BITMAP,
	NO_TITLE,
	&timelapse_banner,
	GUIMENU_START,
	MORE_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	&timelapse1_scrollbar	
};

// GUIMENU_TIMELAPSE_COUNT_PAGE

guimenu_scrollbar_t timelapse2_scrollbar =
{
	2,
	7
};
guimenu_selector_t timelapse_count_selector =
{
	
	GUIMENU_COUNT_TEXT,
	GUIMENU_IS,
	EEPROM_TIMELAPSE_COUNT_HI,
	thumbwheel_select,
	NO_LIST,
	0,
	0,
	0,
	2,
	GUIMENU_INFINITE_VALUE
};

guimenu_scrollbar_t timelapse3_scrollbar =
{
	3,
	7,
	NO_INVERT_BAR
};

guimenu_page_t timelapse_count_page =
{
	NO_BITMAP,
	NO_TITLE,
	&timelapse_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&timelapse_count_selector,
	NO_PROGRESSBAR,
	&timelapse3_scrollbar	
};

// GUIMENU_TIMSELAPSE_STOP_PAGE
guimenu_page_t timelapse_stop_page =
{
	NO_BITMAP,
	NO_TITLE,
	&timelapse_banner,
	GUIMENU_STOP,
	NO_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	NO_SCROLLBAR		
};

// GUIMENU_TIMELAPSE_PROG_PAGE
guimenu_progressbar_t timelapselapse_progressbar =
{
	GUIMENU_NULL_STRING,
	GUIMENU_DELAY
};

guimenu_page_t timelapse_prog_page =
{
	NO_BITMAP,
	NO_TITLE,
	&timelapse_banner,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	&timelapselapse_progressbar,
	NO_SCROLLBAR
};

// GUIMENU_BULBRAMP_START_PAGE
guimenu_banner_t bulbramp_banner =
{
	GUIMENU_BULB,
	GUIMENU_RAMPING
};

guimenu_scrollbar_t bulbramp_scrollbar1 =
{
	1,
	6,
	NO_INVERT_BAR
};

guimenu_page_t bulbramp_start_page =
{
	NO_BITMAP,
	NO_TITLE,
	&bulbramp_banner,
	GUIMENU_START,
	MORE_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	&bulbramp_scrollbar1		
};

// GUIMENU_BULBRAMP_COUNT_PAGE
guimenu_selector_t bulbramp_count_selector =
{
	GUIMENU_COUNT_TEXT,
	GUIMENU_IS,
	EEPROM_BULBRAMP_COUNT_HI,
	thumbwheel_select,
	NO_LIST,
	0,
	0,
	0,
	2,
	10000
};

guimenu_scrollbar_t bulbramp_scrollbar5 =
{
	5,
	6,
	NO_INVERT_BAR
};

guimenu_page_t bulbramp_count_page =
{
	NO_BITMAP,
	NO_TITLE,
	&bulbramp_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&bulbramp_count_selector,
	NO_PROGRESSBAR,
	&bulbramp_scrollbar5		
};

// GUIMENU_BULBRAMP_STOP_PAGE
guimenu_page_t bulbramp_stop_page =
{
	NO_BITMAP,
	NO_TITLE,
	&bulbramp_banner,
	GUIMENU_STOP,
	NO_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	&bulbramp_scrollbar1		
};

// GUIMENU_BRAMP_PROG_PAGE
guimenu_progressbar_t Bulbramp_progressbar =
{
	GUIMENU_NULL_STRING,
	GUIMENU_DELAY
};

guimenu_page_t Bulbramp_prog_page =
{
	NO_BITMAP,
	NO_TITLE,
	&bulbramp_banner,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	&Bulbramp_progressbar,
	NO_SCROLLBAR
};

// GUIMENU_BRAMP_EXPOPROG_PAGE
guimenu_progressbar_t Bulbramp_Expo_progressbar =
{
	GUIMENU_NULL_STRING,
	GUIMENU_EXPO
};

guimenu_page_t Bulbramp_Expoprog_page =
{
	NO_BITMAP,
	NO_TITLE,
	&bulbramp_banner,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	&Bulbramp_Expo_progressbar,
	NO_SCROLLBAR
};
// GUIMENU_TIMEWARP_START_PAGE

guimenu_scrollbar_t timewarp1_scrollbar =
{
	1,
	6
};

guimenu_banner_t timewarp_banner =
{
	GUIMENU_TIMEWARP,
	GUIMENU_NULL_STRING
};

guimenu_page_t timewarp_start_page =
{
	NO_BITMAP,
	NO_TITLE,
	&timewarp_banner,
	GUIMENU_START,
	MORE_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	&timewarp1_scrollbar		
};

// GUIMENU_TIMEWARP_FUNCTION_PAGE
guimenu_scrollbar_t timewarp4_scrollbar =
{
	4,
	6
};

uint8_t timewarp_func_list[] =
{
	GUIMENU_TIMEWARP_FN1,
	GUIMENU_TIMEWARP_FN2,
	GUIMENU_TIMEWARP_FN3, 
};

guimenu_selector_t timewarp_function_selector =
{
	GUIMENU_TIMEWARP_SELECTOR_TEXT1,
	GUIMENU_IS,
	EEPROM_TIMEWARP_FUNCTION,
	list_select,
	timewarp_func_list,
	3,
	0,
	0,
	0,
	0
};      

guimenu_page_t timewarp_function_page =
{
	NO_BITMAP,
	NO_TITLE,
	&timewarp_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&timewarp_function_selector,
	NO_PROGRESSBAR,
	&timewarp4_scrollbar		
};

// GUIMENU_TIMEWARP_STOP_PAGE
guimenu_page_t timewarp_stop_page =
{
	NO_BITMAP,
	NO_TITLE,
	&timewarp_banner,
	GUIMENU_STOP,
	NO_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	NO_SCROLLBAR		
};

// GUIMENU_SENSORVIDEO_START_PAGE
guimenu_banner_t sensorvideo_banner =
{
	GUIMENU_SENSOR,
	GUIMENU_VIDEO
};

guimenu_scrollbar_t sensorvideo_scrollbar1 =
{
	1,
	8,
	NO_INVERT_BAR
};

guimenu_page_t sensorvideo_start_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensorvideo_banner,
	GUIMENU_START,
	MORE_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	&sensorvideo_scrollbar1	
};

// GUIMENU_SENSORVIDEO_DELAY_PAGE
guimenu_selector_t sensorvideo_delay_selector =
{
	GUIMENU_SETUP,
	GUIMENU_DELAY,
	EEPROM_SENSORVIDEO_DELAY_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_S,
	GUIMENU_UNITS_S,
	0,
	60
};

guimenu_scrollbar_t sensorvideo_scrollbar2 =
{
	2,
	8,
	NO_INVERT_BAR
};

guimenu_page_t sensorvideo_delay_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensorvideo_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&sensorvideo_delay_selector,
	NO_PROGRESSBAR,
	&sensorvideo_scrollbar2		
};

// GUIMENU_POWEROFF_TITLE_PAGE
const uint8_t poweroff_bitmap[504] PROGMEM =
{
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0x7F , 0x3F , 0xBF , 0xFF , 0xFF , 0x0F , 0x0F , 0xFF,
	0xFF , 0xBF , 0x3F , 0x7F , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xC0 , 0x80 , 0x3F , 0x7F , 0xFF,
	0xFF , 0xFC , 0xFC , 0xFF , 0xFF , 0x7F , 0x3F , 0x80 , 0xC0 , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFE , 0xFC , 0xFC , 0xFC , 0xFC , 0xFC , 0xFC , 0xFE , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF
};

guimenu_title_t poweroff_title =
{
	GUIMENU_NULL_STRING,
	GUIMENU_NULL_STRING,
	GUIMENU_POWEROFF,
	INVERT_TEXT
};

guimenu_page_t poweroff_title_page =
{
	poweroff_bitmap,
	&poweroff_title,
	NO_BANNER,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	NO_SCROLLBAR
};

// GUIMENU_SETTINGS_TITLE_PAGE
const uint8_t settings_bitmap[504] PROGMEM =
{
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0x07 , 0xFF , 0xFF , 0x3F , 0x07 , 0x3F , 0xFF,
	0xFF , 0x07 , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xE1 , 0x80 , 0xE1 , 0xFF,
	0xFC , 0x80 , 0xFC , 0xFF , 0xE1 , 0x80 , 0xE1 , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF,
	0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF , 0xFF
};

guimenu_title_t settings_title =
{
	GUIMENU_NULL_STRING,
	GUIMENU_NULL_STRING,
	GUIMENU_SETTINGS,
	INVERT_TEXT	
};

guimenu_scrollbar_t settings_scrollbar1 =
{
	1,
	5,
	INVERT_BAR
};

guimenu_page_t settings_title_page =
{
	settings_bitmap,
	&settings_title,
	NO_BANNER,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	&settings_scrollbar1
};

// GUIMENU_CAMERA_PREFOCUS_PAGE
guimenu_banner_t settings_banner =
{
	GUIMENU_SETTINGS,
	GUIMENU_NULL_STRING
};

guimenu_selector_t camera_prefocus_selector =
{
	GUIMENU_CAMERA_PREFOCUS_TEXT1,
	GUIMENU_CAMERA_PREFOCUS_TEXT2,
	EEPROM_CAMERAPREFOCUS_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_MS,
	GUIMENU_UNITS_S,
	0,
	5
};

guimenu_page_t camera_prefocus_page =
{
	NO_BITMAP,
	NO_TITLE,
	&settings_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&camera_prefocus_selector,
	NO_PROGRESSBAR,
	&settings_scrollbar1
};

// GUIMENU_SHUTTER_PULSE_PAGE
guimenu_selector_t shutter_pulse_selector =
{
	GUIMENU_SHUTTER_TEXT,
	GUIMENU_PULSE_TEXT2,
	EEPROM_SHUTTERPULSE_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_MS,
	GUIMENU_UNITS_S,
	0,
	5
};

guimenu_scrollbar_t settings_scrollbar2 =
{
	2,
	5,
	INVERT_BAR
};

guimenu_page_t shutter_pulse_page =
{
	NO_BITMAP,
	NO_TITLE,
	&settings_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&shutter_pulse_selector,
	NO_PROGRESSBAR,
	&settings_scrollbar2
};

// GUIMENU_FLASH_PULSE_PAGE
guimenu_selector_t flash_pulse_selector =
{
	GUIMENU_FLASH_PULSE_TEXT1,
	GUIMENU_PULSE_TEXT2,
	EEPROM_FLASHPULSE_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_MS,
	GUIMENU_UNITS_MS,
	0,
	100
};

guimenu_scrollbar_t settings_scrollbar3 =
{
	3,
	5,
	INVERT_BAR
};

guimenu_page_t flash_pulse_page =
{
	NO_BITMAP,
	NO_TITLE,
	&settings_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&flash_pulse_selector,
	NO_PROGRESSBAR,
	&settings_scrollbar3
};

// GUIMENU_HSF_START_PAGE
guimenu_scrollbar_t hsf_scrollbar1 =
{
	1,
	9,
	NO_INVERT_BAR
};

guimenu_banner_t hsf_banner =
{
	GUIMENU_HIGHSPEED,
	GUIMENU_FLASH
};

guimenu_page_t hsf_start_page =
{
	NO_BITMAP,
	NO_TITLE,
	&hsf_banner,
	GUIMENU_START,
	MORE_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	&hsf_scrollbar1
};

// GUIMENU_HSF_STOP_PAGE
guimenu_page_t hsf_stop_page =
{
	NO_BITMAP,
	NO_TITLE,
	&hsf_banner,
	GUIMENU_STOP,
	NO_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	NO_SCROLLBAR//hsf_scrollbar1
};

// GUIMENU_HSF_TRIGGERON_PAGE
uint8_t triggeron_list[] =
{
	GUIMENU_ALL_TEXT,
	GUIMENU_ANY_TEXT,
};

guimenu_selector_t hsf_triggeron_selector =
{
	GUIMENU_TRIGGER_ON_TEXT1,
	GUIMENU_TRIGGER_ON_TEXT2,
	EEPROM_HSF_TRIGGERON,
	toggle_select,
	triggeron_list,
	2,
	0,
	0,
	0,
	0
};

guimenu_scrollbar_t hsf_scrollbar2 =
{
	2,
	9,
	NO_INVERT_BAR
};

guimenu_page_t hsf_triggeron_page =
{
	NO_BITMAP,
	NO_TITLE,
	&hsf_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&hsf_triggeron_selector,
	NO_PROGRESSBAR,
	&hsf_scrollbar2
};

// GUIMENU_SENSORTLAPSE_START_PAGE
guimenu_banner_t sensortlapse_banner =
{
	GUIMENU_SENSOR,
	GUIMENU_TIMELAPSE
};

guimenu_page_t sensortlapse_start_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensortlapse_banner,
	GUIMENU_START,
	MORE_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	NO_SCROLLBAR
};

// GUIMENU_SENSORTLAPSE_PROG_PAGE
guimenu_progressbar_t sensortlapse_progressbar =
{
	GUIMENU_NULL_STRING,
	GUIMENU_DELAY
};

guimenu_page_t sensortlapse_prog_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensortlapse_banner,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	&sensortlapse_progressbar,
	NO_SCROLLBAR
};

// GUIMENU_TIMELAPSE_INTERVAL_PAGE


guimenu_selector_t timelapse_interval_selector =
{
	GUIMENU_INTERVAL,
	GUIMENU_IS,
	EEPROM_TIMELAPSE_INTERVAL_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_MS,
	GUIMENU_UNITS_H,
	0,
	24
};

guimenu_page_t timelapse_interval_page =
{
	NO_BITMAP,
	NO_TITLE,
	&timelapse_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&timelapse_interval_selector,
	NO_PROGRESSBAR		,
	&timelapse2_scrollbar
};

// GUIMENU_TIMELAPSE_START_DELAY_PAGE
guimenu_scrollbar_t timelapse4_scrollbar =
{
	4,
	7
};
guimenu_selector_t timelapse_startdelay_selector =
{
	GUIMENU_STARTDELAY,
	GUIMENU_IS,
	EEPROM_TIMELAPSE_STARTDELAY_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_MS,
	GUIMENU_UNITS_H,
	0,
	9999
};


guimenu_page_t timelapse_startdelay_page =
{
	NO_BITMAP,
	NO_TITLE,
	&timelapse_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&timelapse_startdelay_selector,
	NO_PROGRESSBAR,
	&timelapse4_scrollbar		
};

// GUIMENU_TIMEWARP_COUNT_PAGE
guimenu_scrollbar_t timewarp2_scrollbar =
{
	2,
	6
};

guimenu_selector_t timewarp_count_selector =
{
	GUIMENU_COUNT_TEXT,
	GUIMENU_IS,
	EEPROM_TIMEWARP_COUNT_HI,
	thumbwheel_select,
	NO_LIST,
	0,
	0,
	0,
	2,
	10000
};

guimenu_page_t timewarp_count_page =
{
	NO_BITMAP,
	NO_TITLE,
	&timewarp_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&timewarp_count_selector,
	NO_PROGRESSBAR,
	&timewarp2_scrollbar	
};

// GUIMENU_TIMEWARP_DIRECTION_PAGE
guimenu_scrollbar_t timewarp5_scrollbar =
{
	5,
	6
};
uint8_t timewarp_direction_list[] =
{
	GUIMENU_IN,
	GUIMENU_OUT,
	GUIMENU_INOUT,
	GUIMENU_OUTIN,
};

guimenu_selector_t timewarp_direction_selector =
{
	GUIMENU_DIRECTION,
	GUIMENU_IS,
	EEPROM_TIMEWARP_DIRECTION,
	list_select,
	timewarp_direction_list,
	4,
	0,
	0,
	0,
	0
};

guimenu_page_t timewarp_direction_page =
{
	NO_BITMAP,
	NO_TITLE,
	&timewarp_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&timewarp_direction_selector,
	NO_PROGRESSBAR,
	&timewarp5_scrollbar	
};

// GUIMENU_TIMEWARP_WAIT_PAGE
guimenu_scrollbar_t timewarp6_scrollbar =
{
	6,
	6
};
guimenu_selector_t timewarp_wait_selector =
{
	GUIMENU_STARTDELAY,
	GUIMENU_NULL_STRING,
	EEPROM_TIMEWARP_WAIT_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_S,
	GUIMENU_UNITS_H,
	0,
	24
};

guimenu_page_t timewarp_wait_page =
{
	NO_BITMAP,
	NO_TITLE,
	&timewarp_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&timewarp_wait_selector,
	NO_PROGRESSBAR,
	&timewarp6_scrollbar
};

// GUIMENU_TIMEWARP_DURATION_PAGE
guimenu_scrollbar_t timewarp3_scrollbar =
{
	3,
	6
};

guimenu_selector_t timewarp_duration_selector =
{
	GUIMENU_DURATION,
	GUIMENU_IS,
	EEPROM_TIMEWARP_DURATION_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_M,
	GUIMENU_UNITS_H,
	10,
	24,
};

guimenu_page_t timewarp_duration_page =
{
	NO_BITMAP,
	NO_TITLE,
	&timewarp_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&timewarp_duration_selector,
	NO_PROGRESSBAR,
	&timewarp3_scrollbar
};

// GUIMENU_TIMEWARP_PROG_PAGE
guimenu_progressbar_t timewarp_progressbar =
{
	GUIMENU_NULL_STRING,
	GUIMENU_DELAY
};

guimenu_page_t timewarp_prog_page =
{
	NO_BITMAP,
	NO_TITLE,
	&timewarp_banner,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	&timewarp_progressbar,
	NO_SCROLLBAR
};
// GUIMENU_BULBRAMP_START_EXPOSURE_PAGE
uint8_t exposure_list[] =
{
	GUIMENU_1D15,
	GUIMENU_1D13,
	GUIMENU_1D10,
	GUIMENU_1D8,
	GUIMENU_1D6,
	GUIMENU_1D5,
	GUIMENU_1D4,
	GUIMENU_0_3,
	GUIMENU_0_4,
	GUIMENU_0_5,
	GUIMENU_0_6,
	GUIMENU_0_8,
	GUIMENU_1_0,
	GUIMENU_1_3,
	GUIMENU_1_6,
	GUIMENU_2_0,
	GUIMENU_2_5,
	GUIMENU_3_2,
	GUIMENU_4_0,
	GUIMENU_5_0,
	GUIMENU_6_0,
	GUIMENU_8_0,
	GUIMENU_10_0,
	GUIMENU_13_0,
	GUIMENU_15_0,
	GUIMENU_20_0,
	GUIMENU_25_0,
	GUIMENU_30_0,
};

guimenu_scrollbar_t bulbramp_scrollbar2 =
{
	2,
	6,
	NO_INVERT_BAR
};

guimenu_selector_t bulbramp_startexposure_selector =
{
	GUIMENU_START,
	GUIMENU_EXPOSUREIS,
	EEPROM_BULBRAMP_START_EXPOSURE,
	list_select,
	exposure_list,
	28,
	0,
	0,
	2,
	9999
};

guimenu_page_t bulbramp_startexposure_page =
{
	NO_BITMAP,
	NO_TITLE,
	&bulbramp_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&bulbramp_startexposure_selector,
	NO_PROGRESSBAR,
	&bulbramp_scrollbar2
};

// GUIMENU_BULBRAMP_END_EXPOSURE_PAGE
guimenu_scrollbar_t bulbramp_scrollbar3 =
{
	3,
	6,
	NO_INVERT_BAR
};

guimenu_selector_t bulbramp_endexposure_selector =
{
	GUIMENU_END,
	GUIMENU_EXPOSUREIS,
	EEPROM_BULBRAMP_END_EXPOSURE,
	list_select,
	exposure_list,
	28,
	0,
	0,
	0,
	0
};

guimenu_page_t bulbramp_endexposure_page =
{
	NO_BITMAP,
	NO_TITLE,
	&bulbramp_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&bulbramp_endexposure_selector,
	NO_PROGRESSBAR,
	&bulbramp_scrollbar3
};

// GUIMENU_BULBRAMP_START_DELAY_PAGE
guimenu_selector_t bulbramp_startdelay_selector =
{
	GUIMENU_STARTDELAY,
	GUIMENU_IS,
	EEPROM_BULBRAMP_STARTDELAY_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_S,
	GUIMENU_UNITS_H,
	1,
	24
};

guimenu_scrollbar_t bulbramp_scrollbar4 =
{
	4,
	6,
	NO_INVERT_BAR
};

guimenu_page_t bulbramp_startdelay_page =
{
	NO_BITMAP,
	NO_TITLE,
	&bulbramp_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&bulbramp_startdelay_selector,
	NO_PROGRESSBAR,
	&bulbramp_scrollbar4
};

// GUIMENU_BULBRAMP_DURATION_PAGE
guimenu_selector_t bulbramp_duration_selector =
{
	GUIMENU_DURATION,
	GUIMENU_IS,
	EEPROM_BULBRAMP_DURATION_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_M,
	GUIMENU_UNITS_H,
	10,
	12
};

guimenu_scrollbar_t bulbramp_scrollbar6 =
{
	6,
	6,
	NO_INVERT_BAR
};

guimenu_page_t bulbramp_duration_page =
{
	NO_BITMAP,
	NO_TITLE,
	&bulbramp_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&bulbramp_duration_selector,
	NO_PROGRESSBAR,
	&bulbramp_scrollbar6
};

// GUIMENU_CLOSE_SHUTTER_PAGE
uint8_t yesno_list[] =
{
	GUIMENU_NO,
	GUIMENU_YES_TEXT
};

guimenu_selector_t hsf_closeshutter_selector =
{
	GUIMENU_CLOSE_SHUTTER_TEXT1,
	GUIMENU_CLOSE_SHUTTER_TEXT2,
	EEPROM_HSF_CLOSESHUTTER,
	toggle_select,
	yesno_list,
	2,
	0,
	0,
	0,
	0
};

guimenu_scrollbar_t hsf_scrollbar3 =
{
	3,
	9,
	NO_INVERT_BAR
};

guimenu_page_t hsf_closeshutter_page =
{
	NO_BITMAP,
	NO_TITLE,
	&hsf_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&hsf_closeshutter_selector,
	NO_PROGRESSBAR,
	&hsf_scrollbar3
};

// GUIMENU_HSF_SHUTTER_CYCLING_PAGE
guimenu_selector_t hsf_shuttercycle_selector =
{
	GUIMENU_SHUTTER,
	GUIMENU_CYCLING,
	EEPROM_HSF_SHUTTERCYCLE_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_S,
	GUIMENU_UNITS_S,
	0,
	30
};

guimenu_scrollbar_t hsf_scrollbar4 =
{
	4,
	9,
	NO_INVERT_BAR
};

guimenu_page_t hsf_shuttercycle_page =
{
	NO_BITMAP,
	NO_TITLE,
	&hsf_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&hsf_shuttercycle_selector,
	NO_PROGRESSBAR,
	&hsf_scrollbar4
};

// GUIMENU_HSF_FLASH_DELAY_PAGE
guimenu_selector_t hsf_flashdelay_selector =
{
	GUIMENU_FLASH,
	GUIMENU_DELAY,
	EEPROM_HSF_FLASHDELAY_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_US,
	GUIMENU_UNITS_MS,
	0,
	10
};

//GUIMENU_TIMELAPSE_TIMESACTIVE_PAGE
guimenu_scrollbar_t timelapse5_scrollbar =
{
	5,
	7
};

uint8_t timesactive_list[] =
{
	GUIMENU_TIMES,
	GUIMENU_ALWAYS
	
};

guimenu_selector_t timelapse_timesactive_selector =
{
	GUIMENU_TIMES,
	GUIMENU_ACTIVE,
	EEPROM_TIMELAPSE_ACTIVE,
	toggle_select,
	timesactive_list,
	2,
	0,
	0,
	0,
	0,
};

guimenu_page_t timelapse_timesactive_page =
{
	NO_BITMAP,
	NO_TITLE,
	&timelapse_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&timelapse_timesactive_selector,
	NO_PROGRESSBAR,
	&timelapse5_scrollbar
};

//GUIMENU_TIMELAPSE_STARTTIME_PAGE
guimenu_scrollbar_t timelapse6_scrollbar =
{
	6,
	7
};
guimenu_selector_t timelapse_starttime_selector =
{
	GUIMENU_START,
	GUIMENU_TIME,
	EEPROM_TIMELAPSE_STARTHOURS,
	time_select,
	NO_LIST,
	0,
	0,
	0,
	0,
	0,
};

guimenu_page_t timelapse_starttime_page =
{
	NO_BITMAP,
	NO_TITLE,
	&timelapse_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&timelapse_starttime_selector,
	NO_PROGRESSBAR,
	&timelapse6_scrollbar
};


//GUIMENU_TIMELAPSE_ENDTIME_PAGE
guimenu_scrollbar_t timelapse7_scrollbar =
{
	7,
	7
};
guimenu_selector_t timelapse_endtime_selector =
{
	GUIMENU_END,
	GUIMENU_TIME,
	EEPROM_TIMELAPSE_ENDHOURS,
	time_select,
	NO_LIST,
	0,
	0,
	0,
	0,
	0,
};

guimenu_page_t timelapse_endtime_page =
{
	NO_BITMAP,
	NO_TITLE,
	&timelapse_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&timelapse_endtime_selector,
	NO_PROGRESSBAR,
	&timelapse7_scrollbar
};

//GUIMENU_SETTINGS_SETSYSTEM_TIME_PAGE
guimenu_scrollbar_t settings_scrollbar4 =
{
	4,
	5
};
guimenu_selector_t settings_setsystem_time_selector =
{
	GUIMENU_SET,
	GUIMENU_SYSTEMTIME,
	EEPROM_NONE,
	time_select,
	NO_LIST,
	0,
	0,
	0,
	0,
	0,
};

guimenu_page_t settings_setsystem_time_page =
{
	NO_BITMAP,
	NO_TITLE,
	&settings_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&settings_setsystem_time_selector,
	NO_PROGRESSBAR,
	&settings_scrollbar4
};

//star trail banner
guimenu_banner_t startrail_banner =
{
	GUIMENU_STARTRAIL,
	GUIMENU_NULL_STRING
};
// GUIMENU_STARTRAIL_INTERVAL_PAGE
guimenu_scrollbar_t startrail2_scrollbar =
{
	2,
	5
};

// GUIMENU_STARTRAIL_PROG_PAGE
guimenu_progressbar_t startrail_progressbar =
{
	GUIMENU_NULL_STRING,
	GUIMENU_DELAY
};

guimenu_page_t startrail_prog_page =
{
	NO_BITMAP,
	NO_TITLE,
	&startrail_banner,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	&startrail_progressbar,
	NO_SCROLLBAR
};

guimenu_selector_t startrail_interval_selector =
{
	GUIMENU_INTERVAL,
	GUIMENU_IS,
	EEPROM_STARTTRAIL_INTERVAL_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_S,
	GUIMENU_UNITS_S,
	1,
	30,
};

guimenu_page_t startrail_interval_page =
{
	NO_BITMAP,
	NO_TITLE,
	&startrail_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&startrail_interval_selector,
	NO_PROGRESSBAR		,
	&startrail2_scrollbar
};

//startrail start page

guimenu_scrollbar_t startrail1_scrollbar =
{
	1,
	5
};

guimenu_page_t startrail_start_page =
{
	NO_BITMAP,
	NO_TITLE,
	&startrail_banner,
	GUIMENU_START,
	MORE_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	&startrail1_scrollbar
};

// GUIMENU_STARTRAIL_SHUTTER_SPEED_PAGE
guimenu_scrollbar_t startrail3_scrollbar =
{
	3,
	5
};

guimenu_selector_t startrail_shutter_speed_selector =
{
	GUIMENU_SHUTTER_TEXT,
	GUIMENU_SPEED,
	EEPROM_STARTTRAIL_SHUTTERSPEED_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_S,
	GUIMENU_UNITS_M,
	1,
	30,
};

guimenu_page_t startrail_shutter_speed_page =
{
	NO_BITMAP,
	NO_TITLE,
	&startrail_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&startrail_shutter_speed_selector,
	NO_PROGRESSBAR		,
	&startrail3_scrollbar
};
// GUIMENU_STARTRAIL_COUNT_PAGE
guimenu_scrollbar_t startrail4_scrollbar =
{
	4,
	5
};

guimenu_selector_t startrail_count_selector =
{
	GUIMENU_COUNT_TEXT,
	GUIMENU_IS,
	EEPROM_STARTTRAIL_COUNT_HI,
	thumbwheel_select,
	NO_LIST,
	0,
	0,
	0,
	2,
	9999,
};

guimenu_page_t startrail_count_page =
{
	NO_BITMAP,
	NO_TITLE,
	&startrail_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&startrail_count_selector,
	NO_PROGRESSBAR		,
	&startrail4_scrollbar
};
// GUIMENU_STARTRAIL_DELAY_PAGE
guimenu_scrollbar_t startrail5_scrollbar =
{
	5,
	5
};

guimenu_selector_t startrail_delay_selector =
{
	GUIMENU_STARTDELAY,
	GUIMENU_IS,
	EEPROM_STARTTRAIL_WAIT_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_S,
	GUIMENU_UNITS_H,
	0,
	12,
};

guimenu_page_t startrail_delay_page =
{
	NO_BITMAP,
	NO_TITLE,
	&startrail_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&startrail_delay_selector,
	NO_PROGRESSBAR		,
	&startrail5_scrollbar
};

// GUIMENU_STARTRAIL_STOP_PAGE
guimenu_page_t startrail_stop_page =
{
	NO_BITMAP,
	NO_TITLE,
	&startrail_banner,
	GUIMENU_STOP,
	NO_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	NO_SCROLLBAR
};

guimenu_scrollbar_t hsf_scrollbar5 =
{
	5,
	9,
	NO_INVERT_BAR
};

guimenu_page_t hsf_flashdelay_page =
{
	NO_BITMAP,
	NO_TITLE,
	&hsf_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&hsf_flashdelay_selector,
	NO_PROGRESSBAR,
	&hsf_scrollbar5
};

// GUIMENU_HSF_RESET_DELAY_PAGE
guimenu_selector_t hsf_resetdelay_selector =
{
	GUIMENU_RESET,
	GUIMENU_DELAY,
	EEPROM_HSF_RESETDELAY_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_MS,
	GUIMENU_UNITS_S,
	1,
	30
};

guimenu_scrollbar_t hsf_scrollbar6 =
{
	6,
	9,
	NO_INVERT_BAR
};

guimenu_page_t hsf_resetdelay_page =
{
	NO_BITMAP,
	NO_TITLE,
	&hsf_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&hsf_resetdelay_selector,
	NO_PROGRESSBAR,
	&hsf_scrollbar6
};

// GUIMENU_HSF_TIMESACTIVE_PAGE
guimenu_selector_t hsf_timesactive_selector =
{
	GUIMENU_TIMES,
	GUIMENU_ACTIVE,
	EEPROM_HSF_TIMESACTIVE,
	toggle_select,
	timesactive_list,
	2,
	0,
	0,
	0,
	0
};

guimenu_scrollbar_t hsf_scrollbar7 =
{
	7,
	9,
	NO_INVERT_BAR
};

guimenu_page_t hsf_timesactive_page =
{
	NO_BITMAP,
	NO_TITLE,
	&hsf_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&hsf_timesactive_selector,
	NO_PROGRESSBAR,
	&hsf_scrollbar7
};

//GUIMENU_HSF_STARTTIME_PAGE
guimenu_scrollbar_t hsf_scrollbar8 =
{
	8,
	9,
	NO_INVERT_BAR
};
guimenu_selector_t hsf_starttime_selector =
{
	GUIMENU_START,
	GUIMENU_TIME,
	EEPROM_HSF_START_HOURS,
	time_select,
	NO_LIST,
	0,
	0,
	0,
	0,
	0,
};

guimenu_page_t hsf_starttime_page =
{
	NO_BITMAP,
	NO_TITLE,
	&hsf_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&hsf_starttime_selector,
	NO_PROGRESSBAR,
	&hsf_scrollbar8
};

//GUIMENU_HSF_ENDTIME_PAGE
guimenu_scrollbar_t hsf_scrollbar9 =
{
	9,
	9,
	NO_INVERT_BAR
};
guimenu_selector_t hsf_endtime_selector =
{
	GUIMENU_END,
	GUIMENU_TIME,
	EEPROM_HSF_END_HOURS,
	time_select,
	NO_LIST,
	0,
	0,
	0,
	0,
	0,
};

guimenu_page_t hsf_endtime_page =
{
	NO_BITMAP,
	NO_TITLE,
	&hsf_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&hsf_endtime_selector,
	NO_PROGRESSBAR,
	&hsf_scrollbar9
};

// GUIMENU_SENSORVIDEO_STOP_ACT_PAGE
guimenu_selector_t sensorvideo_stop_act_selector =
{
	GUIMENU_STOPAFTER,
	GUIMENU_ACTIVTY,
	EEPROM_SENSORVIDEO_STOPAFTER_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_S,
	GUIMENU_UNITS_M,
	0,
	60
};

guimenu_scrollbar_t sensorvideo_scrollbar3 =
{
	3,
	8,
	NO_INVERT_BAR
};

guimenu_page_t sensorvideo_stop_act_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensorvideo_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&sensorvideo_stop_act_selector,
	NO_PROGRESSBAR,
	&sensorvideo_scrollbar3
};

// GUIMENU_SENSORVIDEO_TRIGGER_PAGE
uint8_t trigger_list[] =
{
	GUIMENU_CAMERA,
	GUIMENU_MOBILE,
	GUIMENU_BOTH
};

guimenu_selector_t sensorvideo_trigger_selector =
{
	GUIMENU_TRIGGER,
	GUIMENU_NULL_STRING,
	EEPROM_SENSORVIDEO_TRIGGER,
	list_select,
	trigger_list,
	3,
	0,
	0,
	0,
	0
};

guimenu_scrollbar_t sensorvideo_scrollbar4 =
{
	4,
	8,
	NO_INVERT_BAR
};

guimenu_page_t sensorvideo_trigger_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensorvideo_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&sensorvideo_trigger_selector,
	NO_PROGRESSBAR,
	&sensorvideo_scrollbar4
};

// GUIMENU_SENSORVIDEO_TIMESACTIVE_PAGE
guimenu_selector_t sensorvideo_timesactive_selector =
{
	GUIMENU_TIMES,
	GUIMENU_ACTIVE,
	EEPROM_SENSORVIDEO_TIMESACTIVE,
	toggle_select,
	timesactive_list,
	2,
	0,
	0,
	0,
	0
};

guimenu_scrollbar_t sensorvideo_scrollbar5 =
{
	5,
	8,
	NO_INVERT_BAR
};

guimenu_page_t sensorvideo_timesactive_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensorvideo_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&sensorvideo_timesactive_selector,
	NO_PROGRESSBAR,
	&sensorvideo_scrollbar5
};

//GUIMENU_SENSORVIDEO_STARTTIME_PAGE
guimenu_scrollbar_t sensorvideo_scrollbar6 =
{
	6,
	8,
	NO_INVERT_BAR
};
guimenu_selector_t sensorvideo_starttime_selector =
{
	GUIMENU_START,
	GUIMENU_TIME,
	EEPROM_SENSORVIDEO_START_HOURS,
	time_select,
	NO_LIST,
	0,
	0,
	0,
	0,
	0,
};

guimenu_page_t sensorvideo_starttime_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensorvideo_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&sensorvideo_starttime_selector,
	NO_PROGRESSBAR,
	&sensorvideo_scrollbar6
};

//GUIMENU_SENSORVIDEO_ENDTIME_PAGE
guimenu_scrollbar_t sensorvideo_scrollbar7 =
{
	7,
	8,
	NO_INVERT_BAR
};
guimenu_selector_t sensorvideo_endtime_selector =
{
	GUIMENU_END,
	GUIMENU_TIME,
	EEPROM_SENSORVIDEO_END_HOURS,
	time_select,
	NO_LIST,
	0,
	0,
	0,
	0,
	0,
};

guimenu_page_t sensorvideo_endtime_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensorvideo_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&sensorvideo_endtime_selector,
	NO_PROGRESSBAR,
	&sensorvideo_scrollbar7
};

// GUIMENU_SENSORVIDEO_TRIGGERON_PAGE
guimenu_selector_t sensorvideo_triggeron_selector =
{
	GUIMENU_TRIGGER_ON_TEXT1,
	GUIMENU_TRIGGER_ON_TEXT2,
	EEPROM_SENSORVIDEO_TRIGGERON,
	toggle_select,
	triggeron_list,
	2,
	0,
	0,
	0,
	0
};

guimenu_scrollbar_t sensorvideo_scrollbar8 =
{
	8,
	8,
	NO_INVERT_BAR
};

guimenu_page_t sensorvideo_triggeron_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensorvideo_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&sensorvideo_triggeron_selector,
	NO_PROGRESSBAR,
	&sensorvideo_scrollbar8
};

// GUIMENU_LEHDR_START_PAGE
guimenu_banner_t lehdr_banner =
{
	GUIMENU_LEHDR,
	GUIMENU_NULL_STRING
};

guimenu_scrollbar_t lehdr_scrollbar1 =
{
	1,
	5,
	NO_INVERT_BAR
};

guimenu_page_t lehdr_start_page =
{
	NO_BITMAP,
	NO_TITLE,
	&lehdr_banner,
	GUIMENU_START,
	MORE_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	&lehdr_scrollbar1
};

// GUIMENU_LEHDR_STOP_PAGE
guimenu_page_t lehdr_stop_page =
{
	NO_BITMAP,
	NO_TITLE,
	&lehdr_banner,
	GUIMENU_STOP,
	NO_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	&lehdr_scrollbar1
};


// GUIMENU_LEHDR_MID_EXP_PAGE
guimenu_scrollbar_t lehdr_scrollbar2 =
{
	2,
	5,
	NO_INVERT_BAR
};

guimenu_selector_t lehdr_midexposure_selector =
{
	GUIMENU_MIDDLE,
	GUIMENU_EXPOSUREIS,
	EEPROM_LEHDR_MID_EXP,
	list_select,
	exposure_list,
	28,
	0,
	0,
	0,
	0
};

guimenu_page_t lehdr_midexposure_page =
{
	NO_BITMAP,
	NO_TITLE,
	&lehdr_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&lehdr_midexposure_selector,
	NO_PROGRESSBAR,
	&lehdr_scrollbar2
};

// GUIMENU_LEHDR_SHOTS_PAGE
uint8_t odd_shots_list[] =
{
	GUIMENU_THREE,
	GUIMENU_FIVE,
	GUIMENU_SEVEN,
	GUIMENU_NINE,
	GUIMENU_ELEVEN,
	GUIMENU_THIRTEEN,
	GUIMENU_FIFTEEN
};


guimenu_scrollbar_t lehdr_scrollbar3 =
{
	3,
	5,
	NO_INVERT_BAR
};

guimenu_selector_t lehdr_shots_selector =
{
	GUIMENU_SHOTS,
	GUIMENU_IS,
	EEPROM_LEHDR_SHOTS,
	list_select,
	odd_shots_list,
	7,
	0,
	0,
	0,
	0
};

guimenu_page_t lehdr_shots_page =
{
	NO_BITMAP,
	NO_TITLE,
	&lehdr_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&lehdr_shots_selector,
	NO_PROGRESSBAR,
	&lehdr_scrollbar3
};

// GUIMENU_LEHDR_EV_PER_STEP_PAGE
uint8_t ev_per_step_list[] =
{
	GUIMENU_THIRD,
	GUIMENU_HALF,
	GUIMENU_ONE,
};

guimenu_scrollbar_t lehdr_scrollbar4 =
{
	4,
	5,
	NO_INVERT_BAR
};

guimenu_selector_t lehdr_ev_per_step_selector =
{
	GUIMENU_EVPER,
	GUIMENU_SHOT,
	EEPROM_LEHDR_EVPERSHOT,
	list_select,
	ev_per_step_list,
	3,
	0,
	0,
	0,
	0
};

guimenu_page_t lehdr_ev_per_step_page =
{
	NO_BITMAP,
	NO_TITLE,
	&lehdr_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&lehdr_ev_per_step_selector,
	NO_PROGRESSBAR,
	&lehdr_scrollbar4
};

// GUIMENU_LEHDR_TIMELAPSE_PAGE
guimenu_selector_t lehdr_timelapse_selector =
{
	GUIMENU_TIMELAPSE,
	GUIMENU_NULL_STRING,
	EEPROM_LEHDR_TIMELAPSE_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_S,
	GUIMENU_UNITS_S,
	0,
	60
};

guimenu_scrollbar_t lehdr_scrollbar5 =
{
	5,
	5,
	NO_INVERT_BAR
};

guimenu_page_t lehdr_timelapse_page =
{
	NO_BITMAP,
	NO_TITLE,
	&lehdr_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&lehdr_timelapse_selector,
	NO_PROGRESSBAR,
	&lehdr_scrollbar5
};

// GUIMENU_LEHDR_PROG_PAGE
guimenu_progressbar_t lehdr_progressbar =
{
	GUIMENU_NULL_STRING,
	GUIMENU_NULL_STRING
};

guimenu_page_t lehdr_prog_page =
{
	NO_BITMAP,
	NO_TITLE,
	&lehdr_banner,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	&lehdr_progressbar,
	NO_SCROLLBAR
};

// SNESOR banner

guimenu_banner_t sensor_banner =
{
	GUIMENU_SENSOR,
	GUIMENU_NULL_STRING
};
// GUIMENU_SENSOR_START_PAGE

guimenu_scrollbar_t sensor1_scrollbar =
{
	1,
	9
};

guimenu_page_t sensor_start_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensor_banner,
	GUIMENU_START,
	MORE_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	&sensor1_scrollbar
};

// GUIMENU_SENSOR_STOP_PAGE
guimenu_page_t sensor_stop_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensor_banner,
	GUIMENU_STOP,
	NO_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	NO_SCROLLBAR
};

// GUIMENU_SENSOR_TRIGGER_DELAY_PAGE
guimenu_scrollbar_t sensor2_scrollbar =
{
	2,
	9
};

guimenu_selector_t sensor_trigger_delay_selector =
{
	GUIMENU_TRIGGER_DELAY,
	GUIMENU_DELAY,
	EEPROM_SENSOR_TRIGDELAY_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_MS,
	GUIMENU_UNITS_MS,
	0,
	200
};

guimenu_page_t sensor_trigger_delay_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensor_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&sensor_trigger_delay_selector,
	NO_PROGRESSBAR,
	&sensor2_scrollbar
};
// GUIMENU_SENSOR_RESET_DELAY_PAGE
guimenu_scrollbar_t sensor3_scrollbar =
{
	3,
	9
};
guimenu_selector_t sensor_reset_delay_selector =
{
	GUIMENU_RESET_DELAY,
	GUIMENU_DELAY,
	EEPROM_SENSOR_REST_DELAY_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_MS,
	GUIMENU_UNITS_S,
	1,
	60,
};
guimenu_page_t sensor_reset_delay_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensor_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&sensor_reset_delay_selector,
	NO_PROGRESSBAR,
	&sensor3_scrollbar
};
// GUIMENU_SENSOR_TIRGGER_ON_PAGE
uint8_t sensor_trigger_on_list[] =
{
	GUIMENU_ALL_TEXT,
	GUIMENU_ANY_TEXT
};
guimenu_scrollbar_t sensor4_scrollbar =
{
	4,
	9
};
guimenu_selector_t sensor_trigger_on_selector =
{
	GUIMENU_TRIGGER_ON,
	GUIMENU_NULL_STRING,
	EEPROM_SENSOR_TRIGGERON,
	toggle_select,
	sensor_trigger_on_list,
	2,
	0,
	0,
	0,
	0,
};
guimenu_page_t sensor_trigger_on_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensor_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&sensor_trigger_on_selector,
	NO_PROGRESSBAR,
	&sensor4_scrollbar
};
// GUIMENU_SENSOR_MOBILE_INPUT_PAGE
uint8_t sensor_mobile_input_list[] =
{
	GUIMENU_TRIGGER_ON_TEXT2,
	GUIMENU_OFF,
};
guimenu_scrollbar_t sensor5_scrollbar =
{
	5,
	9
};

guimenu_selector_t sensor_mobile_input_selector =
{
	GUIMENU_MOBILE,
	GUIMENU_INPUT,
	EEPROM_SENSOR_MOBILEIP,
	toggle_select,
	sensor_mobile_input_list,
	2,
	0,
	0,
	0,
	0,
};
guimenu_page_t sensor_mobile_input_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensor_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&sensor_mobile_input_selector,
	NO_PROGRESSBAR,
	&sensor5_scrollbar
};

// GUIMENU_SENSOR_MOBILE_OUTPUT_PAGE
uint8_t sensor_mobile_output_list[] =
{
	GUIMENU_TRIGGER_ON_TEXT2,
	GUIMENU_OFF,
};
guimenu_scrollbar_t sensor6_scrollbar =
{
	6,
	9
};
guimenu_selector_t sensor_mobile_output_selector =
{
	GUIMENU_MOBILE,
	GUIMENU_OUTPUT,
	EEPROM_SENSOR_MOBILEOP,
	toggle_select,
	sensor_mobile_output_list,
	2,
	0,
	0,
	0,
	0,
};
guimenu_page_t sensor_mobile_output_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensor_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&sensor_mobile_output_selector,
	NO_PROGRESSBAR,
	&sensor6_scrollbar
};

// GUIMENU_SENSOR_TIME_ACTIVE_PAGE
guimenu_scrollbar_t sensor7_scrollbar =
{
	7,
	9
};

guimenu_selector_t sensor_timesactive_selector =
{
	GUIMENU_TIMES,
	GUIMENU_ACTIVE,
	EEPROM_SENSOR_TIMESACTIVE,
	toggle_select,
	timesactive_list,
	2,
	0,
	0,
	0,
	0,
};

guimenu_page_t sensor_time_active_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensor_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&sensor_timesactive_selector,
	NO_PROGRESSBAR,
	&sensor7_scrollbar
};

// GUIMENU_SENSOR_TIME_START_PAGE
guimenu_scrollbar_t sensor8_scrollbar =
{
	8,
	9
};

guimenu_selector_t sensor_starttime_selector =
{
	GUIMENU_START,
	GUIMENU_TIME,
	EEPROM_SENSOR_START_HOURS,
	time_select,
	NO_LIST,
	0,
	0,
	0,
	0,
	0,
};

guimenu_page_t sensor_time_start_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensor_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&sensor_starttime_selector,
	NO_PROGRESSBAR,
	&sensor8_scrollbar
};

// GUIMENU_SENSOR_TIME_STOP_PAGE

guimenu_scrollbar_t sensor9_scrollbar =
{
	9,
	9
};
guimenu_selector_t sensor_end_time_selector =
{
	GUIMENU_END,
	GUIMENU_TIME,
	EEPROM_SENSOR_END_HOURS,
	time_select,
	NO_LIST,
	0,
	0,
	0,
	0,
	0,
};

guimenu_page_t sensor_time_stop_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensor_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&sensor_end_time_selector,
	NO_PROGRESSBAR,
	&sensor9_scrollbar
};


//SENSOR TIMELAPSE BANNER
guimenu_banner_t sensor_tl_banner =
{
	GUIMENU_SENSOR,
	GUIMENU_TIMELAPSE
};

// GUIMENU_SENSOR_TL_START_PAGE
guimenu_scrollbar_t sensor_tl1_scrollbar =
{
	1,
	11
};
guimenu_page_t sensor_tl_start_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensor_tl_banner,
	GUIMENU_START,
	MORE_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	&sensor_tl1_scrollbar
};

//GUIMENU_SENSOR_TL_STOP_PAGE
guimenu_page_t sensor_tl_stop_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensor_tl_banner,
	GUIMENU_STOP,
	NO_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	NO_SCROLLBAR
};

//GUIMENU_SENSOR_TL_DELAY_PAGE
guimenu_scrollbar_t sensor_tl2_scrollbar =
{
	2,
	11
};
guimenu_selector_t sensor_tl_delay_selector =
{
	GUIMENU_SETUP,
	GUIMENU_DELAY,
	EEPROM_SENSORTLAPSE_DELAY_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_S,
	GUIMENU_UNITS_S,
	0,
	60,
};

guimenu_page_t sensor_tl_delay_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensor_tl_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&sensor_tl_delay_selector,
	NO_PROGRESSBAR,
	&sensor_tl2_scrollbar
};



//GUIMENU_SENSOR_TL_INTERVAL_PAGE
guimenu_scrollbar_t sensor_tl3_scrollbar =
{
	3,
	11
};
guimenu_selector_t sensor_tl_interval_selector =
{
	GUIMENU_INTERVAL,
	GUIMENU_NULL_STRING,
	EEPROM_SENSORTLAPSE_INTERVAL_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_MS,
	GUIMENU_UNITS_M,
	1,
	60,
};
guimenu_page_t sensor_tl_interval_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensor_tl_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&sensor_tl_interval_selector,
	NO_PROGRESSBAR,
	&sensor_tl3_scrollbar
};

//GUIMENU_SENSOR_TL_CONTINUE_SET_PAGE
guimenu_scrollbar_t sensor_tl4_scrollbar =
{
	4,
	11
};

uint8_t sensor_tl_continue_set_list[] =
{
	GUIMENU_SENSOR_STOP,
	GUIMENU_INFINITE,
	GUIMENU_X_SHOTS,
};

guimenu_selector_t sensor_tl_continue_set_selector =
{
	GUIMENU_CONTINUE,
	GUIMENU_SET,
	EEPROM_SENSORTLAPSE_CONTINUE,
	toggle_select,
	sensor_tl_continue_set_list,
	3,
	0,
	0,
	0,
	0,
};
guimenu_page_t sensor_tl_continue_set_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensor_tl_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&sensor_tl_continue_set_selector,
	NO_PROGRESSBAR,
	&sensor_tl4_scrollbar
};


//GUIMENU_SENSOR_TL_CONTINUE_PAGE
guimenu_scrollbar_t sensor_tl5_scrollbar =
{
	5,
	11
};

guimenu_selector_t sensor_tl_continue_selector =
{
	GUIMENU_CONTINUE,
	GUIMENU_SHOTS,
	EEPROM_SENSORTLAPSE_CONTINUE_HI,
	thumbwheel_select,
	NO_LIST,
	0,
	0,
	0,
	0,
	10000,
};
guimenu_page_t sensor_tl_continue_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensor_tl_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&sensor_tl_continue_selector,
	NO_PROGRESSBAR,
	&sensor_tl5_scrollbar
};



//GUIMENU_SENSOR_TL_TRIGGER_ON_PAGE
guimenu_scrollbar_t sensor_tl6_scrollbar =
{
	6,
	11
};

uint8_t sensor_tl_trigger_on_list[] =
{
	GUIMENU_ALL_TEXT,
	GUIMENU_ANY_TEXT
};

guimenu_selector_t sensor_tl_trigger_on_selector =
{
	GUIMENU_TRIGGER_ON,
	GUIMENU_NULL_STRING,
	EEPROM_SENSORTLAPSE_TRIGGERON,
	toggle_select,
	sensor_tl_trigger_on_list,
	2,
	0,
	0,
	0,
	0,
};
guimenu_page_t sensor_tl_trigger_on_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensor_tl_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&sensor_tl_trigger_on_selector,
	NO_PROGRESSBAR,
	&sensor_tl6_scrollbar
};

//GUIMENU_SENSOR_TL_MOBILE_INPUT_PAGE
guimenu_scrollbar_t sensor_tl7_scrollbar =
{
	7,
	11
};

uint8_t sensor_tl_mobile_input_list[] =
{
	GUIMENU_TRIGGER_ON_TEXT2,
	GUIMENU_OFF,
};


guimenu_selector_t sensor_tl_mobile_input_selector =
{
	GUIMENU_MOBILE,
	GUIMENU_INPUT,
	EEPROM_SENSORTLAPSE_MOBILEIP,
	toggle_select,
	sensor_tl_mobile_input_list,
	2,
	0,
	0,
	0,
	0,
};
guimenu_page_t sensor_tl_mobile_input_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensor_tl_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&sensor_tl_mobile_input_selector,
	NO_PROGRESSBAR,
	&sensor_tl7_scrollbar
};


//GUIMENU_SENSOR_TL_MOBILE_OUTPUT_PAGE
guimenu_scrollbar_t sensor_tl8_scrollbar =
{
	8,
	11
};
uint8_t sensor_tl_mobile_output_list[] =
{
	GUIMENU_TRIGGER_ON_TEXT2,
	GUIMENU_OFF,
};

guimenu_selector_t sensor_tl_mobile_output_selector =
{
	GUIMENU_MOBILE,
	GUIMENU_OUTPUT,
	EEPROM_SENSORTLAPSE_MOBILEOP,
	toggle_select,
	sensor_tl_mobile_output_list,
	2,
	0,
	0,
	0,
	0,
};
guimenu_page_t sensor_tl_mobile_output_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensor_tl_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&sensor_tl_mobile_output_selector,
	NO_PROGRESSBAR,
	&sensor_tl8_scrollbar
};



//GUIMENU_SENSOR_TL_TIME_ACTIVE_PAGE
guimenu_scrollbar_t sensor_tl9_scrollbar =
{
	9,
	11
};


guimenu_selector_t sensor_tl_timesactive_selector =
{
	GUIMENU_TIMES,
	GUIMENU_ACTIVE,
	EEPROM_SENSORTLAPSE_TIMESACTIVE,
	toggle_select,
	timesactive_list,
	2,
	0,
	0,
	0,
	0,
};

guimenu_page_t sensor_tl_time_active_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensor_tl_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&sensor_tl_timesactive_selector,
	NO_PROGRESSBAR,
	&sensor_tl9_scrollbar
};

//GUIMENU_SENSOR_TL_START_TIME_PAGE
guimenu_scrollbar_t sensor_tl10_scrollbar =
{
	10,
	11
};
guimenu_selector_t sensor_tl_start_time_selector =
{
	GUIMENU_START,
	GUIMENU_TIME,
	EEPROM_SENSOR_TL_START_HOURS,
	time_select,
	NO_LIST,
	0,
	0,
	0,
	0,
	0,
};

guimenu_page_t sensor_tl_start_time_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensor_tl_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&sensor_tl_start_time_selector,
	NO_PROGRESSBAR,
	&sensor_tl10_scrollbar
};

//GUIMENU_SENSOR_TL_STOP_TIME_PAGE
guimenu_scrollbar_t sensor_tl11_scrollbar =
{
	11,
	11
};
guimenu_selector_t sensor_tl_stop_time_selector =
{
	GUIMENU_END,
	GUIMENU_TIME,
	EEPROM_SENSOR_TL_END_HOURS,
	time_select,
	NO_LIST,
	0,
	0,
	0,
	0,
	0,
};

guimenu_page_t sensor_tl_stop_time_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensor_tl_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&sensor_tl_stop_time_selector,
	NO_PROGRESSBAR,
	&sensor_tl11_scrollbar
};

//advance sensor banner
guimenu_banner_t a_sensor_banner =
{
	GUIMENU_ADVANCED,
	GUIMENU_SENSOR
};


//GUIMENU_A_SENSOR_START_PAGE
guimenu_scrollbar_t a_sensor_tl1_scrollbar =
{
	1,
	16
};
guimenu_page_t a_sensor_start_page =
{
	NO_BITMAP,
	NO_TITLE,
	&a_sensor_banner,
	GUIMENU_START,
	MORE_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	&a_sensor_tl1_scrollbar
};


//GUIMENU_A_SENSOR_STOP_PAGE

guimenu_page_t a_sensor_stop_page =
{
	NO_BITMAP,
	NO_TITLE,
	&a_sensor_banner,
	GUIMENU_STOP,
	NO_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	NO_SCROLLBAR
};

//GUIMENU_A_SENSOR_CH1A_DELAY_PAGE
guimenu_scrollbar_t a_sensor_tl2_scrollbar =
{
	2,
	16
};

guimenu_selector_t a_sensor_ch1a_delay_selector =
{
	GUIMENU_1A,
	GUIMENU_DELAY,
	EEPROM_ADVSENSOR_CHAN1A_DELAY_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_US,
	GUIMENU_UNITS_S,
	0,
	60,
};

guimenu_page_t a_sensor_ch1a_delay_page =
{
	NO_BITMAP,
	NO_TITLE,
	&a_sensor_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&a_sensor_ch1a_delay_selector,
	NO_PROGRESSBAR,
	&a_sensor_tl2_scrollbar
};

//GUIMENU_A_SENSOR_CH1A_PULSE_PAGE
guimenu_scrollbar_t a_sensor_tl3_scrollbar =
{
	3,
	16
};
guimenu_selector_t a_sensor_ch1a_pulse_selector =
{
	GUIMENU_1A,
	GUIMENU_PULSE_DURATION,
	EEPROM_ADVSENSOR_CHAN1A_PULSE_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_MS,
	GUIMENU_UNITS_S,
	0,
	60,
};

guimenu_page_t a_sensor_ch1a_pulse_page =
{
	NO_BITMAP,
	NO_TITLE,
	&a_sensor_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&a_sensor_ch1a_pulse_selector,
	NO_PROGRESSBAR,
	&a_sensor_tl3_scrollbar,
};

//GUIMENU_A_SENSOR_CH1B_DELAY_PAGE
guimenu_scrollbar_t a_sensor_tl4_scrollbar =
{
	4,
	16
};

guimenu_selector_t a_sensor_ch1b_delay_selector =
{
	GUIMENU_1B,
	GUIMENU_DELAY,
	EEPROM_ADVSENSOR_CHAN1B_DELAY_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_US,
	GUIMENU_UNITS_S,
	0,
	60,
};

guimenu_page_t a_sensor_ch1b_delay_page =
{
	NO_BITMAP,
	NO_TITLE,
	&a_sensor_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&a_sensor_ch1b_delay_selector,
	NO_PROGRESSBAR,
	&a_sensor_tl4_scrollbar
};


//GUIMENU_A_SENSOR_CH1B_PULSE_PAGE
guimenu_scrollbar_t a_sensor_tl5_scrollbar =
{
	5,
	16
};
guimenu_selector_t a_sensor_ch1b_pulse_selector =
{
	GUIMENU_1B,
	GUIMENU_PULSE_DURATION,
	EEPROM_ADVSENSOR_CHAN1B_PULSE_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_MS,
	GUIMENU_UNITS_S,
	0,
	60,
};

guimenu_page_t a_sensor_ch1b_pulse_page =
{
	NO_BITMAP,
	NO_TITLE,
	&a_sensor_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&a_sensor_ch1b_pulse_selector,
	NO_PROGRESSBAR,
	&a_sensor_tl5_scrollbar,
};

//GUIMENU_A_SENSOR_CH2A_DELAY_PAGE
guimenu_scrollbar_t a_sensor_tl6_scrollbar =
{
	6,
	16
};
guimenu_selector_t a_sensor_ch2a_delay_selector =
{
	GUIMENU_2A,
	GUIMENU_DELAY,
	EEPROM_ADVSENSOR_CHAN2A_DELAY_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_US,
	GUIMENU_UNITS_S,
	0,
	60,
};

guimenu_page_t a_sensor_ch2a_delay_page =
{
	NO_BITMAP,
	NO_TITLE,
	&a_sensor_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&a_sensor_ch2a_delay_selector,
	NO_PROGRESSBAR,
	&a_sensor_tl6_scrollbar
};
//GUIMENU_A_SENSOR_CH2A_PULSE_PAGE

guimenu_scrollbar_t a_sensor_tl7_scrollbar =
{
	7,
	16
};
guimenu_selector_t a_sensor_ch2a_pulse_selector =
{
	GUIMENU_2A,
	GUIMENU_PULSE_DURATION,
	EEPROM_ADVSENSOR_CHAN2A_PULSE_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_MS,
	GUIMENU_UNITS_S,
	0,
	60,
};

guimenu_page_t a_sensor_ch2a_pulse_page =
{
	NO_BITMAP,
	NO_TITLE,
	&a_sensor_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&a_sensor_ch2a_pulse_selector,
	NO_PROGRESSBAR,
	&a_sensor_tl7_scrollbar,
};

//GUIMENU_A_SENSOR_CH2B_DELAY_PAGE

guimenu_scrollbar_t a_sensor_t8_scrollbar =
{
	8,
	16
};
guimenu_selector_t a_sensor_ch2b_delay_selector =
{
	GUIMENU_2B,
	GUIMENU_DELAY,
	EEPROM_ADVSENSOR_CHAN2B_DELAY_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_US,
	GUIMENU_UNITS_S,
	0,
	60,
};

guimenu_page_t a_sensor_ch2b_delay_page =
{
	NO_BITMAP,
	NO_TITLE,
	&a_sensor_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&a_sensor_ch2b_delay_selector,
	NO_PROGRESSBAR,
	&a_sensor_t8_scrollbar
};
//GUIMENU_A_SENSOR_CH2B_PULSE_PAGE

guimenu_scrollbar_t a_sensor_tl9_scrollbar =
{
	9,
	16
};
guimenu_selector_t a_sensor_ch2b_pulse_selector =
{
	GUIMENU_2B,
	GUIMENU_PULSE_DURATION,
	EEPROM_ADVSENSOR_CHAN2B_PULSE_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_MS,
	GUIMENU_UNITS_S,
	0,
	60,
};

guimenu_page_t a_sensor_ch2b_pulse_page =
{
	NO_BITMAP,
	NO_TITLE,
	&a_sensor_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&a_sensor_ch2b_pulse_selector,
	NO_PROGRESSBAR,
	&a_sensor_tl9_scrollbar,
};

//GUIMENU_A_SENSOR_CH3A_DELAY_PAGE
guimenu_scrollbar_t a_sensor_tl10_scrollbar =
{
	10,
	16
};
guimenu_selector_t a_sensor_ch3a_delay_selector =
{
	GUIMENU_3A,
	GUIMENU_DELAY,
	EEPROM_ADVSENSOR_CHAN3A_DELAY_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_US,
	GUIMENU_UNITS_S,
	0,
	60,
};

guimenu_page_t a_sensor_ch3a_delay_page =
{
	NO_BITMAP,
	NO_TITLE,
	&a_sensor_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&a_sensor_ch3a_delay_selector,
	NO_PROGRESSBAR,
	&a_sensor_tl10_scrollbar
};
//GUIMENU_A_SENSOR_CH3A_PULSE_PAGE

guimenu_scrollbar_t a_sensor_tl11_scrollbar =
{
	11,
	16
};
guimenu_selector_t a_sensor_ch3a_pulse_selector =
{
	GUIMENU_3A,
	GUIMENU_PULSE_DURATION,
	EEPROM_ADVSENSOR_CHAN3A_PULSE_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_MS,
	GUIMENU_UNITS_S,
	0,
	60,
};

guimenu_page_t a_sensor_ch3a_pulse_page =
{
	NO_BITMAP,
	NO_TITLE,
	&a_sensor_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&a_sensor_ch3a_pulse_selector,
	NO_PROGRESSBAR,
	&a_sensor_tl11_scrollbar,
};

//GUIMENU_A_SENSOR_CH3B_DELAY_PAGE

guimenu_scrollbar_t a_sensor_tl12_scrollbar =
{
	12,
	16
};
guimenu_selector_t a_sensor_ch3b_delay_selector =
{
	GUIMENU_3B,
	GUIMENU_DELAY,
	EEPROM_ADVSENSOR_CHAN3B_DELAY_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_US,
	GUIMENU_UNITS_S,
	0,
	60,
};

guimenu_page_t a_sensor_ch3b_delay_page =
{
	NO_BITMAP,
	NO_TITLE,
	&a_sensor_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&a_sensor_ch3b_delay_selector,
	NO_PROGRESSBAR,
	&a_sensor_tl12_scrollbar
};
//GUIMENU_A_SENSOR_CH3B_PULSE_PAGE
guimenu_scrollbar_t a_sensor_tl13_scrollbar =
{
	13,
	16
};
guimenu_selector_t a_sensor_ch3b_pulse_selector =
{
	GUIMENU_3B,
	GUIMENU_PULSE_DURATION,
	EEPROM_ADVSENSOR_CHAN3B_PULSE_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_MS,
	GUIMENU_UNITS_S,
	0,
	60,
};

guimenu_page_t a_sensor_ch3b_pulse_page =
{
	NO_BITMAP,
	NO_TITLE,
	&a_sensor_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&a_sensor_ch3b_pulse_selector,
	NO_PROGRESSBAR,
	&a_sensor_tl13_scrollbar,
};

//GUIMENU_A_SENSOR_TRIGGER_MOBILE_PAGE

guimenu_scrollbar_t a_sensor_tl14_scrollbar =
{
	14,
	16
};
uint8_t a_sensor_trigger_mobile_list[] =
{
	GUIMENU_TRIGGER_ON_TEXT2,
	GUIMENU_OFF,
};

guimenu_selector_t a_sensor_trigger_mobile_selector =
{
	GUIMENU_TRIGGER_ON_TEXT1,
	GUIMENU_MOBILE,
	EEPROM_ADVSENSOR_TRIGMOBILE,
	toggle_select,
	a_sensor_trigger_mobile_list,
	2,
	0,
	0,
	0,
	0,
};

guimenu_page_t a_sensor_trigger_mobile_page =
{
	NO_BITMAP,
	NO_TITLE,
	&a_sensor_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&a_sensor_trigger_mobile_selector,
	NO_PROGRESSBAR,
	&a_sensor_tl14_scrollbar
};


//GUIMENU_A_SENSOR_RESET_DELAY_PAGE
guimenu_scrollbar_t a_sensor_tl15_scrollbar =
{
	15,
	16
};
guimenu_selector_t a_sensor_reset_delay_selector =
{
	GUIMENU_RESET_DELAY,
	GUIMENU_DELAY,
	EEPROM_ADVSENSOR_REST_DELAY_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_MS,
	GUIMENU_UNITS_S,
	0,
	60,
};
guimenu_page_t a_sensor_reset_delay_page =
{
	NO_BITMAP,
	NO_TITLE,
	&a_sensor_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&a_sensor_reset_delay_selector,
	NO_PROGRESSBAR,
	&a_sensor_tl15_scrollbar
};
//GUIMENU_A_SENSOR_TRIGGER_ON_PAGE

guimenu_scrollbar_t a_sensor_tl16_scrollbar =
{
	16,
	16
};
uint8_t a_sensor_trigger_on_list[] =
{
	GUIMENU_ALL_TEXT,
	GUIMENU_ANY_TEXT,
};

guimenu_selector_t a_sensor_trigger_on_selector =
{
	GUIMENU_TRIGGER_ON_TEXT1,
	GUIMENU_TRIGGER_ON_TEXT2,
	EEPROM_ADVSENSOR_TRIGGER_ON,
	toggle_select,
	a_sensor_trigger_on_list,
	2,
	0,
	0,
	0,
	0,
};

guimenu_page_t a_sensor_trigger_on_page =
{
	NO_BITMAP,
	NO_TITLE,
	&a_sensor_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&a_sensor_trigger_on_selector,
	NO_PROGRESSBAR,
	&a_sensor_tl16_scrollbar
};
//GUIMENU_SENSOR_VIDEO_STOP_PAGE
guimenu_page_t sensor_video_stop_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensorvideo_banner,
	GUIMENU_STOP,
	NO_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	NO_SCROLLBAR
};

//GUIMENU_SETTINGS_ABOUT
guimenu_banner_t settings_banner_1 =
{
	GUIMENU_SETTINGS1,
	GUIMENU_NULL_STRING
};

guimenu_scrollbar_t settings_scrollbar5 =
{
	5,
	5
};

guimenu_title_t about_title =
{
	GUIMENU_NULL_STRING,
	GUIMENU_VERSION,
	GUIMENU_VERSION_NUM,
	NO_INVERT_TEXT
};

guimenu_page_t settings_about_page =
{
       NO_BITMAP,
       &about_title,
       &settings_banner_1,
       NO_BUTTON,
       NO_SETTINGS,
	   NO_SELECTOR,
       NO_PROGRESSBAR,
       &settings_scrollbar5
};


// GUIMENU_HSF_CONFIG_PAGE
guimenu_progressbar_t config_progressbar =
{
	GUIMENU_NULL_STRING,
	GUIMENU_SETTING
};

guimenu_page_t hsf_config_page =
{
	NO_BITMAP,
	NO_TITLE,
	&hsf_banner,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	&config_progressbar,
	NO_SCROLLBAR
};

// GUIMENU_SENSOR_CONFIG_PAGE
guimenu_page_t sensor_config_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensor_banner,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	&config_progressbar,
	NO_SCROLLBAR
};

// GUIMENU_SENSORTLAPSE_CONFIG_PAGE
guimenu_page_t sensortlpase_config_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensortlapse_banner,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	&config_progressbar,
	NO_SCROLLBAR
};

// GUIMENU_SENSORVIDEO_CONFIG_PAGE
guimenu_page_t sensorvideo_config_page =
{
	NO_BITMAP,
	NO_TITLE,
	&sensorvideo_banner,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	&config_progressbar,
	NO_SCROLLBAR
};

// GUIMENU_ADVSENSOR_CONFIG_PAGE
guimenu_page_t advsensor_config_page =
{
	NO_BITMAP,
	NO_TITLE,
	&a_sensor_banner,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	&config_progressbar,
	NO_SCROLLBAR
};

#ifdef INCLUDE_NEWMODE
// GUIMENU_NEWMODE_TITLE_PAGE
guimenu_title_t newmode_title =
{
	GUIMENU_ELEVEN,
	GUIMENU_NEWMODE,
	GUIMENU_NULL_STRING,
	NO_INVERT_TEXT
};

guimenu_scrollbar_t newmode_title_scrollbar =
{
	11,
	NUM_MODES_IN_MAIN_MENU
};

guimenu_page_t newmode_title_page =
{
	NO_BITMAP,
	&newmode_title,
	NO_BANNER,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	&newmode_title_scrollbar
};

// GUIMENU_NEWMODE_START_PAGE
guimenu_scrollbar_t newmode_scrollbar1 =
{
	1,
	3
};

guimenu_banner_t newmode_banner =
{
	GUIMENU_NEWMODE,
	GUIMENU_NULL_STRING
};

guimenu_page_t newmode_start_page =
{
	NO_BITMAP,
	NO_TITLE,
	&newmode_banner,
	GUIMENU_START,
	MORE_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	&newmode_scrollbar1
};

// GUIMENU_NEWMODE_SETTLING_PAGE
guimenu_page_t newmode_settling_page =
{
	NO_BITMAP,
	NO_TITLE,
	&newmode_banner,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	&config_progressbar,
	NO_SCROLLBAR
};

// GUIMENU_NEWMODE_RUNNING_PAGE
guimenu_page_t newmode_running_page =
{
	NO_BITMAP,
	NO_TITLE,
	&newmode_banner,
	GUIMENU_STOP,
	NO_SETTINGS,
	NO_SELECTOR,
	NO_PROGRESSBAR,
	&newmode_scrollbar1
};

// GUIMENU_NEWMODE_TRIGGERON_PAGE
uint8_t newmode_trigger_list[] =
{
	GUIMENU_SENSOR,
	GUIMENU_MOBILE,
	GUIMENU_BOTH
};

guimenu_selector_t newmode_triggeron_selector =
{
	GUIMENU_TRIGGER,
	GUIMENU_ON,
	EEPROM_NEWMODE_TRIGGERON,
	list_select,
	newmode_trigger_list,
	3,
	0,
	0,
	0,
	0
};

guimenu_scrollbar_t newmode_scrollbar2 =
{
	2,
	3,
	NO_INVERT_BAR
};

guimenu_page_t newmode_triggeron_page =
{
	NO_BITMAP,
	NO_TITLE,
	&newmode_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&newmode_triggeron_selector,
	NO_PROGRESSBAR,
	&newmode_scrollbar2
};


// GUIMENU_NEWMODE_DELAY_PAGE
guimenu_selector_t newmode_delay_selector =
{
	GUIMENU_DELAY,
	GUIMENU_IS,
	EEPROM_NEWMODE_DELAY_HI,
	thumbwheel_units_select,
	NO_LIST,
	0,
	GUIMENU_UNITS_S,
	GUIMENU_UNITS_M,
	0,
	60
};

guimenu_scrollbar_t newmode_scrollbar3 =
{
	3,
	3,
	NO_INVERT_BAR
};

guimenu_page_t newmode_delay_page =
{
	NO_BITMAP,
	NO_TITLE,
	&newmode_banner,
	NO_BUTTON,
	NO_SETTINGS,
	&newmode_delay_selector,
	NO_PROGRESSBAR,
	&newmode_scrollbar3
};

// GUIMENU_NEWMODE_PROG_PAGE
guimenu_progressbar_t newmode_progressbar =
{
	GUIMENU_NULL_STRING,
	GUIMENU_DELAY
};

guimenu_page_t newmode_prog_page =
{
	NO_BITMAP,
	NO_TITLE,
	&newmode_banner,
	NO_BUTTON,
	NO_SETTINGS,
	NO_SELECTOR,
	&newmode_progressbar,
	NO_SCROLLBAR
};
#endif

// Menu Page Table
guimenu_page_t *g_guimenu_page_def[] =
{
	&start_page,						// GUIMENU_START_PAGE
	&timelapse_title_page,				// GUIMENU_TIMELAPSE_TITLE_PAGE
	&timewarp_title_page,				// GUIMENU_TIMEWARP_TITLE_PAGE
	&bulbramping_title_page,			// GUIMENU_BULBRAMPING_TITLE_PAGE
	&startrail_title_page,				// GUIMENU_STARTRAIL_TITLE_PAGE
	&hsf_title_page,					// GUIMENU_HISPEEDFLASH_TITLE_PAGE
	&sensor_title_page,					// GUIMENU_SENSOR_TITLE_PAGE
	&sensortlapse_title_page,			// GUIMENU_SENSORTLAPSE_TITLE_PAGE
	&sensorvideo_title_page,			// GUIMENU_SENSORVIDEO_TITLE_PAGE
	&advsensor_title_page,				// GUIMENU_ADVSENSOR_TITLE_PAGE
	&lehdr_title_page,					// GUIMENU_LEHDR_TITLE_PAGE
	&timelapse_start_page,				// GUIMENU_TIMELAPSE_START_PAGE
	&timelapse_count_page,				// GUIMENU_TIMELAPSE_COUNT_PAGE
	&timelapse_stop_page,				// GUIMENU_TIMELAPSE_STOP_PAGE
	&bulbramp_start_page,				// GUIMENU_BULBRAMP_START_PAGE
	&bulbramp_count_page,				// GUIMENU_BULBRAMP_COUNT_PAGE
	&bulbramp_stop_page,				// GUIMENU_BULBRAMP_STOP_PAGE
	&timewarp_start_page,				// GUIMENU_TIMEWARP_START_PAGE
	&timewarp_function_page,			// GUIMENU_TIMEWARP_FUNCTION_PAGE
	&timewarp_stop_page,				// GUIMENU_TIMEWARP_STOP_PAGE
	&sensorvideo_start_page,			// GUIMENU_SENSORVIDEO_START_PAGE
	&sensorvideo_delay_page,			// GUIMENU_SENSORVIDEO_DELAY_PAGE
	&poweroff_title_page,				// GUIMENU_POWEROFF_TITLE_PAGE
	&settings_title_page,				// GUIMENU_SETTINGS_TITLE_PAGE
	&camera_prefocus_page,				// GUIMENU_CAMERA_PREFOCUS_PAGE
	&shutter_pulse_page,				// GUIMENU_SHUTTER_PULSE_PAGE
	&flash_pulse_page,					// GUIMENU_FLASH_PULSE_PAGE
	&hsf_start_page,					// GUIMENU_HSF_START_PAGE
	&hsf_stop_page,						// GUIMENU_HSF_STOP_PAGE
	&hsf_triggeron_page,				// GUIMENU_HSF_TRIGGERON_PAGE
	&sensortlapse_start_page,			// GUIMENU_SENSORTLAPSE_START_PAGE
	&sensortlapse_prog_page,			// GUIMENU_SENSORTLAPSE_PROG_PAGE
	&timelapse_interval_page,			// GUIMENU_TIMELAPSE_INTERVAL_PAGE
	&timelapse_startdelay_page,			// GUIMENU_TIMELAPSE_START_DELAY_PAGE
	&timewarp_count_page,				// GUIMENU_TIMEWARP_COUNT_PAGE
	&timewarp_direction_page,			// GUIMENU_TIMEWARP_DIRECTION_PAGE
	&timewarp_wait_page,				// GUIMENU_TIMEWARP_WAIT_PAGE
	&timewarp_duration_page,			// GUIMENU_TIMEWARP_DURATION_PAGE
	&bulbramp_endexposure_page,			// GUIMENU_BULBRAMP_END_EXPOSURE_PAGE
	&bulbramp_startdelay_page,			// GUIMENU_BULBRAMP_STARTDELAY_PAGE
	&bulbramp_duration_page,			// GUIMENU_BULBRAMP_DURATION_PAGE
	&hsf_closeshutter_page,				// GUIMENU_HSF_CLOSE_SHUTTER_PAGE
	&hsf_shuttercycle_page,				// GUIMENU_HSF_SHUTTER_CYCLING_PAGE
	&hsf_flashdelay_page,				// GUIMENU_HSF_FLASH_DELAY_PAGE
	&hsf_resetdelay_page,				// GUIMENU_HSF_RESET_DELAY_PAGE
	&hsf_timesactive_page,				// GUIMENU_HSF_TIMESACTIVE
	&hsf_starttime_page,				// GUIMENU_HSF_STARTTIME_PAGE
	&hsf_endtime_page,					// GUIMENU_HSF_ENDTIME_PAGE	
	&sensorvideo_stop_act_page,			// GUIMENU_SENSORVIDEO_STOP_ACT_PAGE
	&sensorvideo_trigger_page,			// GUIMENU_SENSORVIDEO_TRIGGER_PAGE
	&sensorvideo_timesactive_page,		// GUIMENU_SENSORVIDEO_TIMESACTIVE_PAGE
	&sensorvideo_starttime_page,		// GUIMENU_SENSORVIDEO_STARTTIME_PAGE
	&sensorvideo_endtime_page,			// GUIMENU_SENSORVIDEO_ENDTIME_PAGE
	&sensorvideo_triggeron_page,		// GUIMENU_SENSORVIDEO_TRIGGERON_PAGE	
	&timelapse_timesactive_page,		// GUIMENU_TIMELAPSE_STARTACTIVE_PAGE
	&timelapse_starttime_page,			// GUIMENU_TIMELAPSE_STARTTIME_PAGE
	&timelapse_endtime_page,			// GUIMENU_TIMELAPSE_ENDTIME_PAGE
	&settings_setsystem_time_page,		// GUIMENU_SETTINGS_SETSYSTEM_TIME_PAGE
	&startrail_start_page,				// GUIMENU_STARTRAIL_START_PAGE_PAGE
	&startrail_interval_page,			// GUIMENU_STARTRAIL_INTERVAL_PAGE
	&startrail_shutter_speed_page,		// GUIMENU_STARTRAIL_SHUTTER_SPEED_PAGE
	&startrail_count_page,				// GUIMENU_STARTRAIL_COUNT_PAGE
	&startrail_delay_page,				// GUIMENU_STARTRAIL_DELAY_PAGE
	&startrail_stop_page,				// GUIMENU_STARTRAIL_DELAY_PAGE
	&bulbramp_startexposure_page,		// GUIMENU_BULBRAMP_START_EXPOSURE_PAGE
	&lehdr_midexposure_page,			// GUIMENU_LEHDR_MID_EXP_PAGE
	&lehdr_shots_page,					// GUIMENU_LEHDR_SHOTS_PAGE
	&lehdr_ev_per_step_page,			// GUIMENU_LEHDR_EV_PER_STEP_PAGE
	&lehdr_timelapse_page,				// GUIMENU_LEHDR_TIMELAPSE_PAGE
	&lehdr_start_page,					// GUIMENU_LEHDR_START_PAGE
	&lehdr_stop_page,					// GUIMENU_LEHDR_STOP_PAGE
	&sensor_start_page,					// GUIMENU_SENSOR_START_PAGE
	&sensor_stop_page,					// GUIMENU_SENSOR_STOP_PAGE
	&sensor_trigger_delay_page,			// GUIMENU_SENSOR_TRIGGER_DELAY_PAGE
	&sensor_reset_delay_page,			// GUIMENU_SENSOR_RESET_DELAY_PAGE
	&sensor_trigger_on_page,			// GUIMENU_SENSOR_TIRGGER_ON_PAGE
	&sensor_mobile_input_page,			// GUIMENU_SENSOR_MOBILE_INPUT_PAGE
	&sensor_mobile_output_page,			// GUIMENU_SENSOR_MOBILE_OUTPUT_PAGE
	&sensor_time_active_page,			// GUIMENU_SENSOR_TIME_ACTIVE_PAGE
	&sensor_time_start_page,			// GUIMENU_SENSOR_TIME_START_PAGE
	&sensor_time_stop_page,				// GUIMENU_SENSOR_TIME_STOP_PAGE
	&sensor_tl_start_page,				// GUIMENU_SENSOR_TL_START_PAGE
	&sensor_tl_stop_page,				// GUIMENU_SENSOR_TL_STOP_PAGE
	&sensor_tl_delay_page,				// GUIMENU_SENSOR_TL_DELAY_PAGE
	&sensor_tl_interval_page,			// GUIMENU_SENSOR_TL_INTERVAL_PAGE
	&sensor_tl_continue_page,			// GUIMENU_SENSOR_TL_CONTINUE_PAGE
	&sensor_tl_trigger_on_page,			// GUIMENU_SENSOR_TL_TRIGGER_ON_PAGE
	&sensor_tl_mobile_input_page,		// GUIMENU_SENSOR_TL_MOBILE_INPUT_PAGE
	&sensor_tl_mobile_output_page,		// GUIMENU_SENSOR_TL_MOBILE_OUTPUT_PAGE
	&sensor_tl_time_active_page,		// GUIMENU_SENSOR_TL_TIME_ACTIVE_PAGE
	&sensor_tl_start_time_page,			// GUIMENU_SENSOR_TL_START_TIME_PAGE
	&sensor_tl_stop_time_page,			// GUIMENU_SENSOR_TL_STOP_TIME_PAGE
	&sensor_tl_continue_set_page,		// GUIMENU_SENSOR_TL_CONTINUE_SET_PAGE
	&a_sensor_start_page,				// GUIMENU_A_SENSOR_START_PAGE
	&a_sensor_stop_page,				// GUIMENU_A_SENSOR_STOP_PAGE
	&a_sensor_ch1a_delay_page,			// GUIMENU_A_SENSOR_CH1A_DELAY_PAGE
	&a_sensor_ch1a_pulse_page,			// GUIMENU_A_SENSOR_CH1A_PULSE_PAGE
	&a_sensor_ch1b_delay_page,			// GUIMENU_A_SENSOR_CH1B_DELAY_PAGE
	&a_sensor_ch1b_pulse_page,			// GUIMENU_A_SENSOR_CH1B_PULSE_PAGE
	&a_sensor_ch2a_delay_page,			// GUIMENU_A_SENSOR_CH2A_DELAY_PAGE
	&a_sensor_ch2a_pulse_page,			// GUIMENU_A_SENSOR_CH2A_PULSE_PAGE
	&a_sensor_ch2b_delay_page,			// GUIMENU_A_SENSOR_CH2B_DELAY_PAGE
	&a_sensor_ch2b_pulse_page,			// GUIMENU_A_SENSOR_CH2B_PULSE_PAGE
	&a_sensor_ch3a_delay_page,			// GUIMENU_A_SENSOR_CH3A_DELAY_PAGE
	&a_sensor_ch3a_pulse_page,			// GUIMENU_A_SENSOR_CH3A_PULSE_PAGE
	&a_sensor_ch3b_delay_page,			// GUIMENU_A_SENSOR_CH3B_DELAY_PAGE
	&a_sensor_ch3b_pulse_page,			// GUIMENU_A_SENSOR_CH3B_PULSE_PAGE
	&a_sensor_trigger_mobile_page,		// GUIMENU_A_SENSOR_TRIGGER_MOBILE_PAGE
	&a_sensor_reset_delay_page,			// GUIMENU_A_SENSOR_RESET_DELAY_PAGE
	&a_sensor_trigger_on_page,			// GUIMENU_A_SENSOR_TRIGGER_ON_PAGE
	&sensor_video_stop_page,			// GUIMENU_SENSOR_VIDEO_STOP_PAGE
	&lehdr_prog_page,					// GUIMENU_LEHDR_PROG_PAGE
	&timelapse_prog_page,				// GUIMENU_TIMELAPSE_PROG_PAGE
	&Bulbramp_prog_page,				// GUIMENU_BRAMP_PROG_PAGE
	&Bulbramp_Expoprog_page,			// GUIMENU_BRAMP_EXPOPROG_PAGE
	&settings_about_page,				// GUIMENU_SETTINGS_ABOUT
	&hsf_config_page,					// GUIMENU_HSF_CONFIG_PAGE
	&sensor_config_page,				// GUIMENU_SENSOR_CONFIG_PAGE
	&sensortlpase_config_page,			// GUIMENU_SENSORTLAPSE_CONFIG_PAGE	
	&sensorvideo_config_page,			// GUIMENU_SENSORVIDEO_CONFIG_PAGE		
	&advsensor_config_page,				// GUIMENU_ADVSENSOR_CONFIG_PAGE
	&startrail_prog_page,				// GUIMENU_STARTRAIL_PROG_PAGE
	&timewarp_prog_page,				// GUIMENU_TIMEWARP_PROG_PAGE
	

#ifdef INCLUDE_NEWMODE
	&newmode_title_page,				// GUIMENU_NEWMODE_TITLE_PAGE
	&newmode_start_page,				// GUIMENU_NEWMODE_START_PAGE
	&newmode_settling_page,				// GUIMENU_NEWMODE_SETTLING_PAGE
	&newmode_running_page,				// GUIMENU_NEWMODE_RUNNING_PAGE
	&newmode_triggeron_page,			// GUIMENU_NEWMODE_TRIGGERON_PAGE
	&newmode_delay_page,				// GUIMENU_NEWMODE_DELAY_PAGE
	&newmode_prog_page,					// GUIMENU_NEWMODE_PROG_PAGE					
#endif
};	




/*********************************************************************
This is a library for our Monochrome Nokia 5110 LCD Displays

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/338

These displays use SPI to communicate, 4 or 5 pins are required to  
interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen below must be included in any redistribution
*********************************************************************/

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include <util/delay.h>
#include <stdlib.h>
#include <avr/pgmspace.h>

#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"


uint8_t pcd8544_buffer[LCDWIDTH * LCDHEIGHT / 8];
 //= {					//call as first splash
//
 ////,,,,
 //
  //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0xC0         ,/*  ______##  */ 
 //0xF0         ,/*  ____####  */ 
 //0xF8         ,/*  ___#####  */ 
 //0xFC         ,/*  __######  */ 
 //0xFE         ,/*  _#######  */ 
 //0x3F         ,/*  ######__  */ 
 //0x9F         ,/*  #####__#  */ 
 //0xCF         ,/*  ####__##  */ 
 //0xE7         ,/*  ###__###  */ 
 //0xE0         ,/*  _____###  */ 
 //0xF0         ,/*  ____####  */ 
 //0xF0         ,/*  ____####  */ 
 //0x70         ,/*  ____###_  */ 
 //0x70         ,/*  ____###_  */ 
 //0x70         ,/*  ____###_  */ 
 //0x70         ,/*  ____###_  */ 
 //0xF0         ,/*  ____####  */ 
 //0xF0         ,/*  ____####  */ 
 //0xE0         ,/*  _____###  */ 
 //0xE6         ,/*  _##__###  */ 
 //0xCF         ,/*  ####__##  */ 
 //0x9F         ,/*  #####__#  */ 
 //0x3F         ,/*  ######__  */ 
 //0x7E         ,/*  _######_  */ 
 //0xFC         ,/*  __######  */ 
 //0xF8         ,/*  ___#####  */ 
 //0xF0         ,/*  ____####  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x80         ,/*  _______#  */ 
 //0x80         ,/*  _______#  */ 
 //0x80         ,/*  _______#  */ 
 //0x80         ,/*  _______#  */ 
 //0x80         ,/*  _______#  */ 
 //0x80         ,/*  _______#  */ 
 //0x80         ,/*  _______#  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0xE0         ,/*  _____###  */ 
 //0xE0         ,/*  _____###  */ 
 //0xE0         ,/*  _____###  */ 
 //0xE0         ,/*  _____###  */ 
 //0xE0         ,/*  _____###  */ 
 //0xE0         ,/*  _____###  */ 
 //0xC0         ,/*  ______##  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0xFE         ,/*  _#######  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0x00         ,/*  ________  */ 
 //0xFE         ,/*  _#######  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xC7         ,/*  ###___##  */ 
 //0x01         ,/*  #_______  */ 
 //0x01         ,/*  #_______  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x01         ,/*  #_______  */ 
 //0x01         ,/*  #_______  */ 
 //0xC7         ,/*  ###___##  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFC         ,/*  __######  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x80         ,/*  _______#  */ 
 //0xF0         ,/*  ____####  */ 
 //0xFE         ,/*  _#######  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFE         ,/*  _#######  */ 
 //0xF0         ,/*  ____####  */ 
 //0x80         ,/*  _______#  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0xC0         ,/*  ______##  */ 
 //0xC0         ,/*  ______##  */ 
 //0xE0         ,/*  _____###  */ 
 //0xF0         ,/*  ____####  */ 
 //0xF0         ,/*  ____####  */ 
 //0xF0         ,/*  ____####  */ 
 //0xF0         ,/*  ____####  */ 
 //0xF0         ,/*  ____####  */ 
 //0xE0         ,/*  _____###  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0xE0         ,/*  _____###  */ 
 //0xF0         ,/*  ____####  */ 
 //0xF0         ,/*  ____####  */ 
 //0xF0         ,/*  ____####  */ 
 //0xF0         ,/*  ____####  */ 
 //0xF0         ,/*  ____####  */ 
 //0xF0         ,/*  ____####  */ 
 //0xF0         ,/*  ____####  */ 
 //0xE0         ,/*  _____###  */ 
 //0xE0         ,/*  _____###  */ 
 //0xE0         ,/*  _____###  */ 
 //0xC0         ,/*  ______##  */ 
 //0x80         ,/*  _______#  */ 
 //0x00         ,/*  ________  */ 
 //0x30         ,/*  ____##__  */ 
 //0x70         ,/*  ____###_  */ 
 //0xF8         ,/*  ___#####  */ 
 //0xF8         ,/*  ___#####  */ 
 //0xF0         ,/*  ____####  */ 
 //0xC7         ,/*  ###___##  */ 
 //0x9F         ,/*  #####__#  */ 
 //0x3F         ,/*  ######__  */ 
 //0x7F         ,/*  #######_  */ 
 //0xFC         ,/*  __######  */ 
 //0xF9         ,/*  #__#####  */ 
 //0xF3         ,/*  ##__####  */ 
 //0xE7         ,/*  ###__###  */ 
 //0xCF         ,/*  ####__##  */ 
 //0x9F         ,/*  #####__#  */ 
 //0x9E         ,/*  _####__#  */ 
 //0x3E         ,/*  _#####__  */ 
 //0x3C         ,/*  __####__  */ 
 //0x3C         ,/*  __####__  */ 
 //0x3C         ,/*  __####__  */ 
 //0x3C         ,/*  __####__  */ 
 //0x3E         ,/*  _#####__  */ 
 //0x3E         ,/*  _#####__  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x0F         ,/*  ####____  */ 
 //0x07         ,/*  ###_____  */ 
 //0x03         ,/*  ##______  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0xF0         ,/*  ____####  */ 
 //0xFE         ,/*  _#######  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xF3         ,/*  ##__####  */ 
 //0xF0         ,/*  ____####  */ 
 //0xF3         ,/*  ##__####  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFE         ,/*  _#######  */ 
 //0xF0         ,/*  ____####  */ 
 //0x00         ,/*  ________  */ 
 //0x78         ,/*  ___####_  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0x87         ,/*  ###____#  */ 
 //0x03         ,/*  ##______  */ 
 //0x03         ,/*  ##______  */ 
 //0x87         ,/*  ###____#  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0x00         ,/*  ________  */ 
 //0xE0         ,/*  _____###  */ 
 //0xF3         ,/*  ##__####  */ 
 //0xFB         ,/*  ##_#####  */ 
 //0xFB         ,/*  ##_#####  */ 
 //0xFB         ,/*  ##_#####  */ 
 //0x7B         ,/*  ##_####_  */ 
 //0x7B         ,/*  ##_####_  */ 
 //0x73         ,/*  ##__###_  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0xFF         ,/*  ########  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x01         ,/*  #_______  */ 
 //0x03         ,/*  ##______  */ 
 //0x07         ,/*  ###_____  */ 
 //0x0F         ,/*  ####____  */ 
 //0x1F         ,/*  #####___  */ 
 //0x3F         ,/*  ######__  */ 
 //0x3E         ,/*  _#####__  */ 
 //0x7C         ,/*  __#####_  */ 
 //0x79         ,/*  #__####_  */ 
 //0x3B         ,/*  ##_###__  */ 
 //0x03         ,/*  ##______  */ 
 //0x07         ,/*  ###_____  */ 
 //0x07         ,/*  ###_____  */ 
 //0x0F         ,/*  ####____  */ 
 //0x0F         ,/*  ####____  */ 
 //0x0F         ,/*  ####____  */ 
 //0x0F         ,/*  ####____  */ 
 //0x0F         ,/*  ####____  */ 
 //0x0F         ,/*  ####____  */ 
 //0x0F         ,/*  ####____  */ 
 //0x0F         ,/*  ####____  */ 
 //0x07         ,/*  ###_____  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x18         ,/*  ___##___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x07         ,/*  ###_____  */ 
 //0x03         ,/*  ##______  */ 
 //0x03         ,/*  ##______  */ 
 //0x03         ,/*  ##______  */ 
 //0x03         ,/*  ##______  */ 
 //0x03         ,/*  ##______  */ 
 //0x03         ,/*  ##______  */ 
 //0x03         ,/*  ##______  */ 
 //0x07         ,/*  ###_____  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1E         ,/*  _####___  */ 
 //0x18         ,/*  ___##___  */ 
 //0x13         ,/*  ##__#___  */ 
 //0x0F         ,/*  ####____  */ 
 //0x0F         ,/*  ####____  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x0F         ,/*  ####____  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x00         ,/*  ________  */ 
 //0x0F         ,/*  ####____  */ 
 //0x0F         ,/*  ####____  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1E         ,/*  _####___  */ 
 //0x1E         ,/*  _####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x1F         ,/*  #####___  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         ,/*  ________  */ 
 //0x00         /*  ________  */ 
//};

	
	
uint8_t *p; 


// reduces how much is refreshed, which speeds it up!
// originally derived from Steve Evans/JCW's mod but cleaned up and
// optimized
//#define enablePartialUpdate

#ifdef enablePartialUpdate
static uint8_t xUpdateMin, xUpdateMax, yUpdateMin, yUpdateMax;
#endif



static void updateBoundingBox(uint8_t xmin, uint8_t ymin, uint8_t xmax, uint8_t ymax) {
#ifdef enablePartialUpdate
  if (xmin < xUpdateMin) xUpdateMin = xmin;
  if (xmax > xUpdateMax) xUpdateMax = xmax;
  if (ymin < yUpdateMin) yUpdateMin = ymin;
  if (ymax > yUpdateMax) yUpdateMax = ymax;
#endif
}

Adafruit_PCD8544::Adafruit_PCD8544(int16_t Sclk, int16_t Din, int16_t Dc,
    int16_t Cs, int16_t Rst) : Adafruit_GFX(LCDWIDTH, LCDHEIGHT) {
  _din = Din;
  _sclk = Sclk;
  _dc = Dc;
  _rst = Rst;
  _cs = Cs;
}

Adafruit_PCD8544::Adafruit_PCD8544(int16_t Sclk, int16_t Din, int16_t Dc,
    int16_t Rst) : Adafruit_GFX(LCDWIDTH, LCDHEIGHT) {
  _din = Din;
  _sclk = Sclk;
  _dc = Dc;
  _rst = Rst;
  _cs = -1;
}


// the most basic function, set a single pixel
void Adafruit_PCD8544::drawPixel(int16_t x, int16_t y, uint16_t color) {
  if ((x < 0) || (x >= LCDWIDTH) || (y < 0) || (y >= LCDHEIGHT))
    return;

  // x is which column
  if (color) 
    pcd8544_buffer[x+ (y/8)*LCDWIDTH] |= _BV(y%8);  
  else
    pcd8544_buffer[x+ (y/8)*LCDWIDTH] &= ~_BV(y%8); 

  updateBoundingBox(x,y,x,y);
}


// the most basic function, get a single pixel
uint8_t Adafruit_PCD8544::getPixel(int8_t x, int8_t y) {
  if ((x < 0) || (x >= LCDWIDTH) || (y < 0) || (y >= LCDHEIGHT))
    return 0;

  return (pcd8544_buffer[x+ (y/8)*LCDWIDTH] >> (y%8)) & 0x1;  
}


void Adafruit_PCD8544::begin(uint8_t contrast) {


  // set pin directions
  pinMode(_din, OUTPUT);
  pinMode(_sclk, OUTPUT);
  pinMode(_dc, OUTPUT);
  if (_rst > 0)
    pinMode(_rst, OUTPUT);
  if (_cs > 0)
    pinMode(_cs, OUTPUT);

  // toggle RST low to reset
  if (_rst > 0) {
    digitalWrite(_rst, LOW);
    _delay_ms(500);
    digitalWrite(_rst, HIGH);
  }

  clkport     = portOutputRegister(digitalPinToPort(_sclk));
  clkpinmask  = digitalPinToBitMask(_sclk);
  mosiport    = portOutputRegister(digitalPinToPort(_din));
  mosipinmask = digitalPinToBitMask(_din);

  csport    = portOutputRegister(digitalPinToPort(_cs));
  cspinmask = digitalPinToBitMask(_cs);
  dcport    = portOutputRegister(digitalPinToPort(_dc));
  dcpinmask = digitalPinToBitMask(_dc);
  


  
  // get into the EXTENDED mode!
  command(PCD8544_FUNCTIONSET | PCD8544_EXTENDEDINSTRUCTION );

  // LCD bias select (4 is optimal?)
  command(PCD8544_SETBIAS | 0x4);

  // set VOP
  if (contrast > 0x7f)
    contrast = 0x7f;

  command( PCD8544_SETVOP | contrast); // Experimentally determined


  // normal mode
  command(PCD8544_FUNCTIONSET);

  // Set display to Normal
  command(PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYNORMAL);

  // initial display line
  // set page address
  // set column address
  // write display data

  // set up a bounding box for screen updates

  updateBoundingBox(0, 0, LCDWIDTH-1, LCDHEIGHT-1);
  // Push out pcd8544_buffer to the Display (will show the AFI logo)
  
 /* No splash screen for this project

  display();
  for(x = 0; x <= (LCDWIDTH * LCDHEIGHT / 8); x++)
  {
	pcd8544_buffer[x] = pcd8544_buffer_splash2[x];
  }
  */
 
  
  display();
  
}


/*
inline void Adafruit_PCD8544::fastSPIwrite(uint8_t d) {
  
  for(uint8_t bit = 0x80; bit; bit >>= 1) {
    *clkport &= ~clkpinmask;
    if(d & bit) *mosiport |=  mosipinmask;
    else        *mosiport &= ~mosipinmask;
    *clkport |=  clkpinmask;
  }
}
*/

// Modified for this project
inline void Adafruit_PCD8544::fastSPIwrite(uint8_t d) {
	
	for(uint8_t bit = 0x80; bit; bit >>= 1) {
		PORTC.OUT &= 0b11111011;
		if(d & bit) PORTC.OUT |=  0b00001000;
		else        PORTC.OUT &= ~0b00001000;
		PORTC.OUT |= 0b00000100;
	}
}

inline void Adafruit_PCD8544::slowSPIwrite(uint8_t c) {
  shiftOut(_din, _sclk, MSBFIRST, c);
}

void Adafruit_PCD8544::command(uint8_t c) {
  digitalWrite(_dc, LOW);
  if (_cs > 0)
    digitalWrite(_cs, LOW);
  fastSPIwrite(c);
  if (_cs > 0)
    digitalWrite(_cs, HIGH);
}

void Adafruit_PCD8544::data(uint8_t c) {
  digitalWrite(_dc, HIGH);
  if (_cs > 0)
    digitalWrite(_cs, LOW);
  fastSPIwrite(c);
  if (_cs > 0)
    digitalWrite(_cs, HIGH);
}

void Adafruit_PCD8544::setContrast(uint8_t val) {
  if (val > 0x7f) {
    val = 0x7f;
  }
  command(PCD8544_FUNCTIONSET | PCD8544_EXTENDEDINSTRUCTION );
  command( PCD8544_SETVOP | val); 
  command(PCD8544_FUNCTIONSET);
  
 }



void Adafruit_PCD8544::display(void) {
  uint8_t col, maxcol, p;
  
  for(p = 0; p < 6; p++) {
#ifdef enablePartialUpdate
    // check if this page is part of update
    if ( yUpdateMin >= ((p+1)*8) ) {
      continue;   // nope, skip it!
    }
    if (yUpdateMax < p*8) {
      break;
    }d
#endif

    command(PCD8544_SETYADDR | p);


#ifdef enablePartialUpdate
    col = xUpdateMin;
    maxcol = xUpdateMax;
#else
    // start at the beginning of the row
    col = 0;
    maxcol = LCDWIDTH-1;
#endif

    command(PCD8544_SETXADDR | col);

    digitalWrite(_dc, HIGH);
    if (_cs > 0)
      digitalWrite(_cs, LOW);
    for(; col <= maxcol; col++) {
      fastSPIwrite(pcd8544_buffer[(LCDWIDTH*p)+col]);
    }
    if (_cs > 0)
      digitalWrite(_cs, HIGH);

  }

  command(PCD8544_SETYADDR );  // no idea why this is necessary but it is to finish the last byte?
#ifdef enablePartialUpdate
  xUpdateMin = LCDWIDTH - 1;
  xUpdateMax = 0;
  yUpdateMin = LCDHEIGHT-1;
  yUpdateMax = 0;
#endif

}

// clear everything
void Adafruit_PCD8544::clearDisplay(void) {
  memset(pcd8544_buffer, 0, LCDWIDTH*LCDHEIGHT/8);
  updateBoundingBox(0, 0, LCDWIDTH-1, LCDHEIGHT-1);
  cursor_y = cursor_x = 0;
}

/*
// this doesnt touch the buffer, just clears the display RAM - might be handy
void Adafruit_PCD8544::clearDisplay(void) {
  
  uint8_t p, c;
  
  for(p = 0; p < 8; p++) {

    st7565_command(CMD_SET_PAGE | p);
    for(c = 0; c < 129; c++) {
      //uart_putw_dec(c);
      //uart_putchar(' ');
      st7565_command(CMD_SET_COLUMN_LOWER | (c & 0xf));
      st7565_command(CMD_SET_COLUMN_UPPER | ((c >> 4) & 0xf));
      st7565_data(0x0);
    }     
    }

}

*/


 void Adafruit_PCD8544::loadBuffer(const uint8_t *new_buffer)
 {
	int x;
  
	for (x = 0; x <= (LCDWIDTH * LCDHEIGHT / 8); x++)
	{
		pcd8544_buffer[x] = pgm_read_byte(new_buffer + x);
	}	 
 }
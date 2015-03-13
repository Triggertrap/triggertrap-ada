# triggertrap-ada

Ada source code

##Contents

1. About Ada
2. Licence Information
3. About this document
4. Adafruit files
5. Atmel Libraries
6. Arduino Libraries
7. Ada project files
8. EEPROM addresses
9. Creating a new mode
10. Notes on building firmware


##1. About Triggertrap Ada

Ada is a project created by Triggertrap (triggertrap.com), designed to be the world's fastest and easiest to use high-speed camera trigger. An initial prototype was created for a Kickstarter project (tri.gg/kickstarter2), and a significant of additional work was completed in order to bring the product to market. 

Triggertrap was unsuccessful in putting Ada into production, but are releasing the work completed under a GPLv3 open source licence. For full information about where to find all open-source parts of Ada, please see: http://tri.gg/adasource

The electronics and firmware for Ada was developed by Cubik Innovation (cubik-innovation.co.uk). Some additional changes to the firmware was done by Nick Johnson of Arachnid Labs (arachnidlabs.com). 

For discussion about this source code, please see the Triggertrap Ada forum - http://forum.triggertrap.com/categories/triggertrap-ada

##2. Licence Information

For licence information, please see Licence.txt. 

Please note: 
* **Triggertrap**  is a trademark of Triggertrap Ltd, and may not be used without prior permission from Triggertrap. 
* **Ada** is a trademark of Triggertrap Ltd, and may not be used commercially without prior permission from Triggertrap. 
* **Arduino**, **Adafruit** and other trademarks may be present in the Ada source code. Please ensure that you respect their respective trademarks. 

##3. About this document

This project contains all the source files needed to compile the running code on the TriggerTrap Ada device. An outline of what each file is and does is provided below

The project has been developed using files sourced from Atmel, Arduino, Adafruit and akafugu,  plus a number of application specific files written specially for this purpose.

##4. Adafruit files

Adafruit_PCD8544.cpp
Adafruit_PCD8544.h

* From lady ada and can be located at https://github.com/adafruit/Adafruit-PCD8544-Nokia-5110-LCD-library

Adafruit_GFX.cpp and Adafruit_GFX.h and glcdfont7x5.c

* From lady ada and can be located at https://github.com/adafruit/Adafruit-GFX-Library

## 5. Atmel Libraries

rtc.c
rtc.h

* Not used in project but included as an alternative to clock.c. Requires development

Iox128a3.h

* Chip specific header file

compiler.h and parts.h

* Compiler definitions and typedefs 

TC_driver.c
TC_driver.h

* Timer and counter driver files


## 6. Arduino Libraries

Arduino.h

* Holds defines used by Arduino 

binary.h

* Holds definitions for binary numbers used by Arduino

ByteBuffer.cpp
ByteBuffer.h

* Classes that handle buffer creation and use 

Client.h

* Arduino files for using internet protocols

HardwareSerial.h

* UART header file 

IPAddress.cpp

IPAddress.h

* Contains functions to handle IP addresses used by Arduino

main.cpp

* main program entry, just calls application main

new.cpp and new.h

* Contains new and delete operators for dynamic memory allocation

pins_arduino.h

* Pin mapping of the hardware against Arduino standard definitions

Print.cpp and Print.h

* Contains functions such as print() and println()

Printable.h

* Interface class that allows printing of complex types

Server.h

* Function headers for Ethernet related files

Stream.cpp

Stream.h

* adds parsing methods to Stream class

Tone.cpp

* Tone Generation

WCharacter.h

* Character utility functions for Wiring & Arduino

WInterupts.c

* Functions relating to interrupts of the device

Wire.h

* Two wire library for Arduino & wiring

wiring.c

* Contains low level drivers for delays initiating IO ports, ADCs etc

wiring_analog.c

* Contains functions relating to ADC and PWM

wiring_digital.c

* digital input and output functions

wiring_private.h

* definitions for wiring

EEPROM.cpp and EEPROM.h

* Arduino EEPROM library

Udp.h

* Arduino library to send/receive UDP packets
* 
* All files originated from http://arduino.cc/ but files have been modified to fit with the ATXMEGA and have therefore been based on files obtained from http://www.akafugu.jp/posts/products/akafuino_x/

###/debug (folder)

avrdude.exe

* avrdude compiler 

Makefile

* Project makefile

upload.bat

* bootloader upload batch file

## 6. Ada project files

glcdfont7x5.c

* Contains bitmaps for the 7x5 font used in the project.

AdvancedSensor.cpp

* Contains all functions relating to Advanced Sensor mode

BulbRamp.cpp

* Contains all functions relating to Bulb Ramp mode

Clock.cpp
Clock.h

* Contains all functions relating to the system clock time

eeprom_addresses.h

* Contains all addresses for the EEPROM used in the project

glcdfont.c

* Contains the pixel maps for the 5x5 font used in the project

guimenu.cpp

guimenu.h

* Contains all low level functions related to the graphical user interface

guimenu_pages.c

* Contains the data for the menu banners

guimenu_pages.h

* Contains the GUI page definitions

guimenupages.cpp

* Contains the Ada splash screen logo and the information for each page

HardwareGlobals.h

* Contains the definitions for the pins on the processor that are used in the project

Inputs.cpp
Inputs.h

* Contains all the functions related to user input from the buttons

LongExposureHDR.cpp

LongExposureHDR.h

* Contains all functions relating to the long exposure high dynamic range mode

Menu.h

* Contains all the prototypes for the functions accessed by the menu

MenuDefines.h

* Contains defines for the menu state machine along with some other misc defines

MobileTrigger.cpp

* Contains a function that sets up the PWM required for mobile out

NewMode.cpp

NewMode.h

* Contains examples for how to create your own mode within the unit

Sensor.cpp

* Contains functions relating to the sensor mode

SensorConfigs.cpp

* Contains functions for sending configurations to the sensors

SensorTimelapse.cpp

* Contains functions for sensor timelapse mode

SensorVideo.cpp

* Contains functions for sensor video mode

Settings.cpp

* Contains functions for the settings page

StarTrail.cpp

* Contains functions for startrail mode

StateMachine.cpp

* This file contains the main framework of the menu system. It must be called periodically in order to update the menu.

TriggerTrap.cppproj

* Atmel studio project file

TriggerTrap_main.cpp

* Main project entry file contains the high level operations of the system

tt_strings.dat

* Contains the strings used throughout the menu and the array that contains them

tt_strings.h

* Contains the definitions of the individual string location in the data array

Timelapse.cpp

Timelapse.h

* Contains the functions related to the timelapse mode

TimeWarp.cpp

* Contains the functions related to the timewarp mode
 
## 8. EEPROM addresses

EEPROM locations are referenced in the code using their labels, however the absolute addresses may be found in eeprom_addresses.h

###System Settings
EEPROM_STACK_CONFIG

* Data to determine if the stack is in AND/OR mode

EEPROM_LCD_CONTRAST_SET

* Determines if the contrast has been set by the user/factory yet

EEPROM_LCD_CONTRAST

* Data for the LCD contrast value

### Timelapse Settings
EEPROM_TIMELAPSE_INTERVAL_HI

EEPROM_TIMELAPSE_INTERVAL_LO

EEPROM_TIMELAPSE_INTERVAL_UNITS

* Setting for the delay between shots in timelapse mode

EEPROM_TIMELAPSE_COUNT_HI

EEPROM_TIMELAPSE_COUNT_LO

EEPROM_TIMELAPSE_COUNT_UNITS

* How many shots in the timelapse train

EEPROM_TIMELAPSE_STARTDELAY_HI

EEPROM_TIMELAPSE_STARTDELAY_LO

EEPROM_TIMELAPSE_STARTDELAY_UNITS

* Delay before the timelapse should start

EEPROM_TIMELAPSE_ACTIVE

* Defines if timelapse is limited by a time frame or not


###Timewarp Settings

EEPROM_TIMEWARP_COUNT_HI

EEPROM_TIMEWARP_COUNT_LO

* Holds data for how many shots are in timewarp


EEPROM_TIMEWARP_DURATION_HI

EEPROM_TIMEWARP_DURATION_LO

EEPROM_TIMEWARP_DURATION_UNITS

* Holds data for how the duration of the timewarp function

EEPROM_TIMEWARP_FUNCTION

* Defines if timewarp works as Quadratic/Quartic/Quintic

EEPROM_TIMEWARP_DIRECTION

* Defines the direction of the timewarp function

EEPROM_TIMEWARP_WAIT_HI

EEPROM_TIMEWARP_WAIT_LO

EEPROM_TIMEWARP_WAIT_UNITS

* Defines the wait before starting time

###Bulb Ramping
EEPROM_BULBRAMP_START_EXPOSURE

* Relates to Bulbramp start exposure value

EEPROM_BULBRAMP_END_EXPOSURE

* Relates to Bulbramp end exposure value

EEPROM_BULBRAMP_STARTDELAY_HI

EEPROM_BULBRAMP_STARTDELAY_LO

EEPROM_BULBRAMP_STARTDELAY_UNITS

* Holds data for the bulbramp start delay

EEPROM_BULBRAMP_COUNT_HI

EEPROM_BULBRAMP_COUNT_LO

* Holds data for the bulbramp count

EEPROM_BULBRAMP_DURATION_HI

EEPROM_BULBRAMP_DURATION_LO

EEPROM_BULBRAMP_DURATION_UNITS

* Holds data for the bulbramp duration

###Star Trail

EEPROM_STARTTRAIL_INTERVAL_HI

EEPROM_STARTTRAIL_INTERVAL_LO

EEPROM_STARTTRAIL_INTERVAL_UNITS

* Holds data for the interval time

EEPROM_STARTTRAIL_SHUTTERSPEED_HI

EEPROM_STARTTRAIL_SHUTTERSPEED_LO

EEPROM_STARTTRAIL_SHUTTERSPEED_UNITS

* Holds data for the star trail shutter speed

EEPROM_STARTTRAIL_COUNT_HI

EEPROM_STARTTRAIL_COUNT_LO

* Holds data for the startrail count

EEPROM_STARTTRAIL_WAIT_HI

EEPROM_STARTTRAIL_WAIT_LO

EEPROM_STARTTRAIL_WAIT_UNITS

* Holds data for Startrail wait time

###High Speed Flash
EEPROM_HSF_TRIGGERON

* Data for stack configuration for this mode

EEPROM_HSF_CLOSESHUTTER

* Data for determining if the shutter should close

EEPROM_HSF_SHUTTERCYCLE_HI

EEPROM_HSF_SHUTTERCYCLE_LO

EEPROM_HSF_SHUTTERCYCLE_UNITS

* Shutter cycle time

EEPROM_HSF_FLASHDELAY_HI

EEPROM_HSF_FLASHDELAY_LO

EEPROM_HSF_FLASHDELAY_UNITS

* Flash delay time

EEPROM_HSF_RESETDELAY_HI

EEPROM_HSF_RESETDELAY_LO

EEPROM_HSF_RESETDELAY_UNITS

* Reset delay time

EEPROM_HSF_TIMESACTIVE

* Determines if HSF mode is bound by a time window

EEPROM_HSF_START_HOURS

EEPROM_HSF_START_MINS

EEPROM_HSF_END_HOURS

EEPROM_HSF_END_MINS

* Start and end times for HSF times active

###Sensor

EEPROM_SENSOR_TRIGDELAY_HI

EEPROM_SENSOR_TRIGDELAY_LO

EEPROM_SENSOR_TRIGDELAY_UNITS

* Sensor trigger delay times

EEPROM_SENSOR_TRIGGERON

* Data for stack configuration for this mode

EEPROM_SENSOR_MOBILEIP

* Mobile input on/off indicator

EEPROM_SENSOR_MOBILEOP

* Mobile output on/off indicator

EEPROM_SENSOR_TIMESACTIVE

* Determines if sensor mode is bound by a time window

###Sensor Timelapse

EEPROM_SENSORTLAPSE_DELAY_HI

EEPROM_SENSORTLAPSE_DELAY_LO

EEPROM_SENSORTLAPSE_DELAY_UNITS

* Sensor time lapse delay time

EEPROM_SENSORTLAPSE_INTERVAL_HI

EEPROM_SENSORTLAPSE_INTERVAL_LO

EEPROM_SENSORTLAPSE_INTERVAL_UNITS

* Sensor timelapse interval time

EEPROM_SENSORTLAPSE_CONTINUE_HI

EEPROM_SENSORTLAPSE_CONTINUE_LO

* Determines how many shots to continue for

EEPROM_SENSORTLAPSE_TRIGGERON

* Data for stack configuration for this mode

EEPROM_SENSORTLAPSE_MOBILEIP

* Mobile input on/off indicator

EEPROM_SENSORTLAPSE_MOBILEOP

* Mobile output on/off indicator

EEPROM_SENSORTLAPSE_TIMESACTIVE

* Determines if sensor timelapse mode is bound by a time window

###Sensor Video
EEPROM_SENSORVIDEO_DELAY_HI

EEPROM_SENSORVIDEO_DELAY_LO

EEPROM_SENSORVIDEO_DELAY_UNITS

* Sensor video setup delay time

EEPROM_SENSORVIDEO_STOPAFTER_HI

EEPROM_SENSORVIDEO_STOPAFTER_LO

EEPROM_SENSORVIDEO_STOPAFTER_UNITS

* Sensor video stop after time setting

EEPROM_SENSORVIDEO_TRIGGER

* Camera/Mobile/Both setting

EEPROM_SENSORVIDEO_TIMESACTIVE

* Determines if sensor mode is bound by a time window

EEPROM_SENSORVIDEO_TRIGGERON

* Data for stack configuration for this mode

###Advanced Sensor

EEPROM_ADVSENSOR_CHAN1A

EEPROM_ADVSENSOR_CHAN1B

EEPROM_ADVSENSOR_CHAN2A

EEPROM_ADVSENSOR_CHAN2B

EEPROM_ADVSENSOR_CHAN3A

EEPROM_ADVSENSOR_CHAN3B

* Unused

EEPROM_ADVSENSOR_TRIGMOBILE

* Defines if the mobile output is enabled or not


###Settings

EEPROM_CAMERAPREFOCUS_HI

EEPROM_CAMERAPREFOCUS_LO

EEPROM_CAMERAPREFOCUS_UNITS

* Camera prefocus time 

EEPROM_FLASHPULSE_HI

EEPROM_FLASHPULSE_LO

EEPROM_FLASHPULSE_UNITS

* Camera flash pulse time

EEPROM_SHUTTERPULSE_HI

EEPROM_SHUTTERPULSE_LO

EEPROM_SHUTTERPULSE_UNITS

* Shutter open time

EEPROM_TIMELAPSE_STARTHOURS

EEPROM_TIMELAPSE_STARTMINS

EEPROM_TIMELAPSE_ENDHOURS

EEPROM_TIMELAPSE_ENDMINS

* Timelapse start and end times for times active mode

EEPROM_SENSORVIDEO_START_HOURS

EEPROM_SENSORVIDEO_START_MINS

EEPROM_SENSORVIDEO_END_HOURS

EEPROM_SENSORVIDEO_END_MINS

* Sensor video start and end times for times active mode

###LE_HDR
EEPROM_LEHDR_MID_EXP

* LEHDR middle exposure length

EEPROM_LEHDR_SHOTS

* LEHDR number of shots

EEPROM_LEHDR_EVPERSHOT

* The amount at which the exposure should change between shots

EEPROM_LEHDR_TIMELAPSE_HI

EEPROM_LEHDR_TIMELAPSE_LO

EEPROM_LEHDR_TIMELAPSE_UNITS

* LEHDR timelapseinterval time

EEPROM_SENSOR_TL_START_HOURS

EEPROM_SENSOR_TL_START_MINS

EEPROM_SENSOR_TL_END_HOURS

EEPROM_SENSOR_TL_END_MINS

* Sensor Timelapse start and end times

EEPROM_SENSORTLAPSE_CONTINUE

* Defines if sensor timelapse mode will stop on absence of sensor activity/infinite shots/x shots

EEPROM_SENSOR_REST_DELAY_HI

EEPROM_SENSOR_REST_DELAY_LO

EEPROM_SENSOR_RESET_UNITS

* Sensor reset delay time

EEPROM_SENSOR_START_HOURS

EEPROM_SENSOR_START_MINS

EEPROM_SENSOR_END_HOURS

EEPROM_SENSOR_END_MINS

* Sensor start and end times for times active mode

###Advanced Sensor

EEPROM_ADVSENSOR_CHAN1A_DELAY_HI

EEPROM_ADVSENSOR_CHAN1A_DELAY_LO

EEPROM_ADVSENSOR_CHAN1A_DELAY_UNITS

* Advanced Sensor channel 1A delay time

EEPROM_ADVSENSOR_CHAN1B_DELAY_HI

EEPROM_ADVSENSOR_CHAN1B_DELAY_LO

EEPROM_ADVSENSOR_CHAN1B_DELAY_UNITS

* Advanced Sensor channel 1B delay time

EEPROM_ADVSENSOR_CHAN2A_DELAY_HI

EEPROM_ADVSENSOR_CHAN2A_DELAY_LO

EEPROM_ADVSENSOR_CHAN2A_DELAY_UNITS

* Advanced Sensor channel 2A delay time

EEPROM_ADVSENSOR_CHAN2B_DELAY_HI

EEPROM_ADVSENSOR_CHAN2B_DELAY_LO

EEPROM_ADVSENSOR_CHAN2B_DELAY_UNITS

* Advanced Sensor channel 2B delay time

EEPROM_ADVSENSOR_CHAN3A_DELAY_HI

EEPROM_ADVSENSOR_CHAN3A_DELAY_LO

EEPROM_ADVSENSOR_CHAN3A_DELAY_UNITS

* Advanced Sensor channel 3A delay time

EEPROM_ADVSENSOR_CHAN3B_DELAY_HI

EEPROM_ADVSENSOR_CHAN3B_DELAY_LO

EEPROM_ADVSENSOR_CHAN3B_DELAY_UNITS

* Advanced Sensor channel 1A delay time


###pulse duration

EEPROM_ADVSENSOR_CHAN1A_PULSE_HI

EEPROM_ADVSENSOR_CHAN1A_PULSE_LO

EEPROM_ADVSENSOR_CHAN1A_PULSE_UNITS

* Advanced Sensor channel 1A pulse length

EEPROM_ADVSENSOR_CHAN1B_PULSE_HI

EEPROM_ADVSENSOR_CHAN1B_PULSE_LO

EEPROM_ADVSENSOR_CHAN1B_PULSE_UNITS

* Advanced Sensor channel 1B pulse length

EEPROM_ADVSENSOR_CHAN2A_PULSE_HI

EEPROM_ADVSENSOR_CHAN2A_PULSE_LO

EEPROM_ADVSENSOR_CHAN2A_PULSE_UNITS

* Advanced Sensor channel 2A pulse length

EEPROM_ADVSENSOR_CHAN2B_PULSE_HI

EEPROM_ADVSENSOR_CHAN2B_PULSE_LO

EEPROM_ADVSENSOR_CHAN2B_PULSE_UNITS

* Advanced Sensor channel 2B pulse length

EEPROM_ADVSENSOR_CHAN3A_PULSE_HI

EEPROM_ADVSENSOR_CHAN3A_PULSE_LO

EEPROM_ADVSENSOR_CHAN3A_PULSE_UNITS

* Advanced Sensor channel 3A pulse length

EEPROM_ADVSENSOR_CHAN3B_PULSE_HI

EEPROM_ADVSENSOR_CHAN3B_PULSE_LO

EEPROM_ADVSENSOR_CHAN3B_PULSE_UNITS

* Advanced Sensor channel 3B pulse length

EEPROM_ADVSENSOR_REST_DELAY_HI

EEPROM_ADVSENSOR_REST_DELAY_LO

EEPROM_ADVSENSOR_REST_DELAY_UNITS

* Advanced Sensor reset delay time

EEPROM_ADVSENSOR_TRIGGER_ON

* Data for stack configuration for this mode

EEPROM_TIME_HOURS

EEPROM_TIME_MINS

EEPROM_TIME_SECS

* RTC has a roll-over of approx. 18hrs. Alarm is configured to wake the micro before then, save the current time here and reset the counter

EEPROM_NEWMODE_TRIGGERON

EEPROM_NEWMODE_DELAY_HI

EEPROM_NEWMODE_DELAY_LO

EEPROM_NEWMODE_DELAY_UNITS

* Delay times for new mode example

EEPROM_NONE

* Null


##9. Creating a new mode

* Examples on how to include a new mode have been given in this project. The user must add in the definition: 

define INCLUDE_NEWMODE 

* This could either be defined in a file such as MenuDefines.h or it could be added as a symbol in the project properties. This will allow an example mode to appear on the device. This can be modified at will for experimentation. 

* Further information on how to make your own mode can be found in the comments of NewMode.cpp

##10. Notes on building firmware
The Baseblock firmware has been updated so it can be built using avr-gcc and make, however both the Bootloader and the Sensor firmware have not been converted to allow for this process. 

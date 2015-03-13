#include "pins_arduino.h"
#include <avr/sleep.h>
#include "HardwareGlobals.h"
#include "Inputs.h"
	
#include "HighSpeedFlash.h"
#include "guimenu.h"

#include "MenuDefines.h"
#include "Menu.h"
#include "EEPROM.h"
#include "eeprom_addresses.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Wire.h"
#include <stdlib.h>
#include <avr/power.h>


extern "C" 
{
	#include "TC_driver.h"
}



void(* reset) (void) = 0;			//declare reset function at address 0
void MenuUpdate(void);
void store_default_units_value (uint8_t address, uint16_t store_value, uint8_t units);
void start_lcd (uint8_t initial_contrast);
void HighSysClock (void);
void LowSysClock (void);
void WriteEEPROMSettingsDefaults (void);

extern MENU_NEXTSTATE menu_nextstate[];
extern MENU_STATE menu_state[];

#define DEFAULT_LCD_CONTRAST		50

bool Low_Battery_Flag = false;
int MenuSelect = 0, buttonState = 0, MenuLines = 0, MenuLinesTotal = 3, Toggle = 1, Sensor_Timelapse_Flag = 0;
int SelectedStartDelay = 1, Interval = 1, SelectedCount = 2, Infinite = 0, SenDisabled = 0, TimeLapseDisabled = 0, SenTimeDisabled = 0;
int ReTriggerDelay = 1, SetupDelay = 1, TLMobileInputEnabled = 0, SMobileInputEnabled = 0, SMobileOutputEnabled = 0, TLMobileOutputEnabled = 0;
unsigned char SenTimeHourActive, SenTimeMinActive, SenTimeHourOff, SenTimeMinOff, TimeLapseHourActive, TimeLapseMinActive, TimeLapseHourOff, TimeLapseMinOff, SenHourActive, SenMinActive, SenHourOff, SenMinOff;
unsigned char GLOBFlashDelayLow, GLOBFlashDelayHigh, GLOBFocusDelayLow, GLOBFocusDelayHigh, GLOBShutterPlseDelayLow, GLOBShutterPlseDelayHigh;
unsigned int GLOBFlashPulseDelay, GLOBPreFocusDelay, GLOBShutterPulseDelay;


char input;
unsigned volatile char nextstate, state;
char (*pStateFunc)(char);
volatile int TOGGLE = 1;


	
	
int ButtonPoll(int);
void start_lcd (uint8_t initial_contrast)
{
	uint8_t Contrast_set = EEPROM.read (EEPROM_LCD_CONTRAST_SET);
	uint8_t Contrast = initial_contrast;
	
	
	guimenu_initialise (initial_contrast, get_time, set_time);
	
	while (Contrast_set == 0xFF)
	{
		guimenu_clearpage();
		guimenu_println ("ADJUST SCREEN CONTRAST");
				
		
		if (!digitalRead (UpButton))
		{
			Contrast++;
		}
		else if (!digitalRead (DownButton))
		{
			Contrast--;
		}
		else if (!digitalRead (SelectButton))
		{
			Contrast_set = 0;
			EEPROM.write (EEPROM_LCD_CONTRAST_SET, 0);
			EEPROM.write (EEPROM_LCD_CONTRAST, Contrast);
			guimenu_clearpage();
			guimenu_println ("CONTRAST SET");
			guimenu_updatepage();
			
			WriteEEPROMSettingsDefaults();
		}
		
		if (Contrast >= 100)
		{
			Contrast = 100;
		}
		else if (Contrast <= 0)
		{
			Contrast = 0;
		}

		guimenu_setcontrast (Contrast);
		guimenu_updatepage();
		delay(250);
	}
	
	Contrast = EEPROM.read(EEPROM_LCD_CONTRAST);
	guimenu_setcontrast (Contrast);
	guimenu_updatepage();
}


void WriteEEPROMSettingsDefaults (void)
{
	//timelapse defaults
	EEPROM.write(EEPROM_TIMELAPSE_COUNT_HI, 0x27);		// Defaults to INFINITE,
	EEPROM.write(EEPROM_TIMELAPSE_COUNT_LO, 0x11);		// Defaults to INFINITE,

	EEPROM.write(EEPROM_TIMELAPSE_STARTHOURS, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_TIMELAPSE_STARTMINS, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_TIMELAPSE_ENDHOURS, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_TIMELAPSE_ENDMINS, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_TIMELAPSE_INTERVAL_HI, 0x00);		//
	EEPROM.write(EEPROM_TIMELAPSE_INTERVAL_LO, 0x01);		//
	EEPROM.write(EEPROM_TIMELAPSE_INTERVAL_UNITS, GUIMENU_UNITS_S);		// Defaults to 1 sec
	EEPROM.write(EEPROM_TIMELAPSE_STARTDELAY_HI, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_TIMELAPSE_STARTDELAY_LO, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_TIMELAPSE_STARTDELAY_UNITS, GUIMENU_UNITS_S);		// Defaults to 0
	EEPROM.write(EEPROM_TIMELAPSE_ACTIVE, 0x01);		// Defaults to always

	EEPROM.write(EEPROM_TIMEWARP_WAIT_HI, 0x00);		//
	EEPROM.write(EEPROM_TIMEWARP_WAIT_LO, 0x00);		//
	EEPROM.write(EEPROM_TIMEWARP_WAIT_UNITS, GUIMENU_UNITS_M);		//

	//timewarp defaults
	EEPROM.write(EEPROM_TIMEWARP_DURATION_HI, 0x00);		//
	EEPROM.write(EEPROM_TIMEWARP_DURATION_LO, 0x01);		// Defaults to 1 hour
	EEPROM.write(EEPROM_TIMEWARP_DURATION_UNITS, GUIMENU_UNITS_H);

	EEPROM.write(EEPROM_TIMEWARP_COUNT_HI, 0x00);		// set to 0
	EEPROM.write(EEPROM_TIMEWARP_COUNT_LO, 0x64);		// set 100

	EEPROM.write(EEPROM_TIMEWARP_FUNCTION, 0x00); // Defaults to Quadratic

	EEPROM.write(EEPROM_TIMEWARP_WAIT_HI, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_TIMEWARP_WAIT_LO, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_TIMEWARP_WAIT_UNITS, GUIMENU_UNITS_M);		// Defaults to 0

	EEPROM.write(EEPROM_TIMEWARP_DIRECTION, EASE_INOUT);		// Defaults to in-out

	//settings defaults
	EEPROM.write(EEPROM_CAMERAPREFOCUS_HI, 0x00);// Defaults to 0 seconds
	EEPROM.write(EEPROM_CAMERAPREFOCUS_LO, 0x00);// Defaults to 0 seconds
	EEPROM.write(EEPROM_CAMERAPREFOCUS_UNITS,GUIMENU_UNITS_S);// Defaults to 0 seconds

	EEPROM.write(EEPROM_SHUTTERPULSE_HI, 0x00);// Defaults to 150ms
	EEPROM.write(EEPROM_SHUTTERPULSE_LO, 0x96);// Defaults to 150ms
	EEPROM.write(EEPROM_SHUTTERPULSE_UNITS, GUIMENU_UNITS_MS);// Defaults to 150ms

	EEPROM.write(EEPROM_FLASHPULSE_HI, 0x00);// Defaults to 30ms
	EEPROM.write(EEPROM_FLASHPULSE_LO, 0x1E);// Defaults to 30ms
	EEPROM.write(EEPROM_FLASHPULSE_UNITS, GUIMENU_UNITS_MS);// Defaults to 30ms

	//startrail
	EEPROM.write(EEPROM_STARTTRAIL_INTERVAL_HI, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_STARTTRAIL_INTERVAL_LO, 0x02);		// Defaults to 2
	EEPROM.write(EEPROM_STARTTRAIL_INTERVAL_UNITS, GUIMENU_UNITS_S);		// Defaults to 0

	EEPROM.write(EEPROM_STARTTRAIL_SHUTTERSPEED_HI, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_STARTTRAIL_SHUTTERSPEED_LO, 0x1E);		// Defaults to 30 sec
	EEPROM.write(EEPROM_STARTTRAIL_SHUTTERSPEED_UNITS, GUIMENU_UNITS_S);		// Defaults to seconds

	EEPROM.write(EEPROM_STARTTRAIL_COUNT_HI, 0x27);		// Defaults to INFINITE,
	EEPROM.write(EEPROM_STARTTRAIL_COUNT_LO, 0x11);		// Defaults to INFINITE,

	EEPROM.write(EEPROM_STARTTRAIL_WAIT_HI, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_STARTTRAIL_WAIT_LO, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_STARTTRAIL_WAIT_UNITS, GUIMENU_UNITS_S);		// Defaults to 0

	//HSF Defaults
	EEPROM.write(EEPROM_HSF_TRIGGERON, 0x01);			// Defaults to ANY
	EEPROM.write(EEPROM_HSF_CLOSESHUTTER, 0x00);		// Defaults to NO


	EEPROM.write(EEPROM_HSF_SHUTTERCYCLE_HI, 0);			// Defaults to 0 seconds (OFF)
	EEPROM.write(EEPROM_HSF_SHUTTERCYCLE_LO, 0);
	EEPROM.write(EEPROM_HSF_SHUTTERCYCLE_UNITS, GUIMENU_UNITS_S);


	EEPROM.write(EEPROM_HSF_FLASHDELAY_HI, 0x00);			 // Defaults to 0 milliseconds (OFF)
	EEPROM.write(EEPROM_HSF_FLASHDELAY_LO, 0x00);
	EEPROM.write(EEPROM_HSF_FLASHDELAY_UNITS, GUIMENU_UNITS_US);

	EEPROM.write(EEPROM_HSF_RESETDELAY_HI, 0);			 // Defaults to 1 second
	EEPROM.write(EEPROM_HSF_RESETDELAY_LO, 0x01);
	EEPROM.write(EEPROM_HSF_RESETDELAY_UNITS, GUIMENU_UNITS_S);

	EEPROM.write(EEPROM_HSF_START_HOURS, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_HSF_START_MINS, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_HSF_END_HOURS, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_HSF_END_MINS, 0x00);		// Defaults to 0

	EEPROM.write(EEPROM_HSF_TIMESACTIVE, 0x01);

	//BulbRamp Defaults
	EEPROM.write(EEPROM_BULBRAMP_START_EXPOSURE, 0x04);			// Defaults to 1/6
	EEPROM.write(EEPROM_BULBRAMP_END_EXPOSURE, 0x16);		// Defaults to 10

	EEPROM.write(EEPROM_BULBRAMP_STARTDELAY_HI, 0x00);			// Defaults to off
	EEPROM.write(EEPROM_BULBRAMP_STARTDELAY_LO, 0x0);		// Defaults to	off
	EEPROM.write(EEPROM_BULBRAMP_STARTDELAY_UNITS, GUIMENU_UNITS_S);

	EEPROM.write(EEPROM_BULBRAMP_COUNT_HI, 0x01);		// Defaults to 360
	EEPROM.write(EEPROM_BULBRAMP_COUNT_LO, 0x68);		// Defaults to	360

	EEPROM.write(EEPROM_BULBRAMP_DURATION_HI, 0x00);		// Defaults to 1 Hr
	EEPROM.write(EEPROM_BULBRAMP_DURATION_LO, 0x01);		// Defaults to 1 Hr
	EEPROM.write(EEPROM_BULBRAMP_DURATION_UNITS, GUIMENU_UNITS_H);		// Defaults to 1 Hr


	//LE_HDR
	EEPROM.write(EEPROM_LEHDR_MID_EXP, 0x0B);			//default 0.8
	EEPROM.write(EEPROM_LEHDR_SHOTS, 0x00);				//default 3
	EEPROM.write(EEPROM_LEHDR_EVPERSHOT, 0x02);			//default 1
	store_default_units_value (EEPROM_LEHDR_TIMELAPSE_HI, 0, GUIMENU_UNITS_S);

	//sensor
	EEPROM.write(EEPROM_SENSOR_TRIGDELAY_HI, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_SENSOR_TRIGDELAY_LO, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_SENSOR_TRIGDELAY_UNITS, GUIMENU_UNITS_MS);		// Defaults to 0
	EEPROM.write(EEPROM_SENSOR_TRIGGERON, 0x01);		// Defaults to 1
	EEPROM.write(EEPROM_SENSOR_MOBILEIP, 0x01);		// Defaults to 0
	EEPROM.write(EEPROM_SENSOR_MOBILEOP, 0x01);		// Defaults to 1
	EEPROM.write(EEPROM_SENSOR_TIMESACTIVE, 0x01);
	EEPROM.write(EEPROM_SENSOR_REST_DELAY_HI, 0x00);
	EEPROM.write(EEPROM_SENSOR_REST_DELAY_LO, 0x01);		// Defaults to 1
	EEPROM.write(EEPROM_SENSOR_RESET_UNITS, GUIMENU_UNITS_S);

	EEPROM.write(EEPROM_SENSOR_START_HOURS, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_SENSOR_START_MINS, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_SENSOR_END_HOURS, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_SENSOR_END_MINS, 0x00);		// Defaults to 0

	//sensor timelapse
	EEPROM.write(EEPROM_SENSORTLAPSE_DELAY_HI, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_SENSORTLAPSE_DELAY_LO, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_SENSORTLAPSE_DELAY_UNITS, GUIMENU_UNITS_S);		// Defaults to 0
	EEPROM.write(EEPROM_SENSORTLAPSE_INTERVAL_HI, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_SENSORTLAPSE_INTERVAL_LO, 0x01);		// Defaults to 1
	EEPROM.write(EEPROM_SENSORTLAPSE_INTERVAL_UNITS, GUIMENU_UNITS_S);
	EEPROM.write(EEPROM_SENSORTLAPSE_CONTINUE_HI, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_SENSORTLAPSE_CONTINUE_LO, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_SENSORTLAPSE_TRIGGERON, 0x01);
	EEPROM.write(EEPROM_SENSORTLAPSE_MOBILEIP, 0x01);
	EEPROM.write(EEPROM_SENSORTLAPSE_MOBILEOP, 0x01);
	EEPROM.write(EEPROM_SENSORTLAPSE_TIMESACTIVE, 0x01);		// Defaults to always
	EEPROM.write(EEPROM_SENSOR_TL_START_HOURS, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_SENSOR_TL_START_MINS, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_SENSOR_TL_END_HOURS, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_SENSOR_TL_END_MINS, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_SENSORTLAPSE_CONTINUE, 0x00);		// Defaults to 0

	//ADVANCE SENSOR
	EEPROM.write(EEPROM_ADVSENSOR_CHAN1A_DELAY_HI, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_ADVSENSOR_CHAN1A_DELAY_LO, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_ADVSENSOR_CHAN1A_DELAY_UNITS, GUIMENU_UNITS_MS);		// Defaults to 0

	EEPROM.write(EEPROM_ADVSENSOR_CHAN1B_DELAY_HI, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_ADVSENSOR_CHAN1B_DELAY_LO, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_ADVSENSOR_CHAN1B_DELAY_UNITS, GUIMENU_UNITS_MS);		// Defaults to 0

	EEPROM.write(EEPROM_ADVSENSOR_CHAN2A_DELAY_HI, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_ADVSENSOR_CHAN2A_DELAY_LO, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_ADVSENSOR_CHAN2A_DELAY_UNITS, GUIMENU_UNITS_MS);		// Defaults to 0

	EEPROM.write(EEPROM_ADVSENSOR_CHAN2B_DELAY_HI, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_ADVSENSOR_CHAN2B_DELAY_LO, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_ADVSENSOR_CHAN2B_DELAY_UNITS, GUIMENU_UNITS_MS);		// Defaults to 0

	EEPROM.write(EEPROM_ADVSENSOR_CHAN3A_DELAY_HI, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_ADVSENSOR_CHAN3A_DELAY_LO, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_ADVSENSOR_CHAN3A_DELAY_UNITS, GUIMENU_UNITS_MS);		// Defaults to 0

	EEPROM.write(EEPROM_ADVSENSOR_CHAN3B_DELAY_HI, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_ADVSENSOR_CHAN3B_DELAY_LO, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_ADVSENSOR_CHAN3B_DELAY_UNITS, GUIMENU_UNITS_MS);		// Defaults to 0

	//PULSE
	EEPROM.write(EEPROM_ADVSENSOR_CHAN1A_PULSE_HI, 0x00);
	EEPROM.write(EEPROM_ADVSENSOR_CHAN1A_PULSE_LO, 0x96);
	EEPROM.write(EEPROM_ADVSENSOR_CHAN1A_PULSE_UNITS, GUIMENU_UNITS_MS);

	EEPROM.write(EEPROM_ADVSENSOR_CHAN1B_PULSE_HI, 0x00);
	EEPROM.write(EEPROM_ADVSENSOR_CHAN1B_PULSE_LO, 0x96);
	EEPROM.write(EEPROM_ADVSENSOR_CHAN1B_PULSE_UNITS, GUIMENU_UNITS_MS);

	EEPROM.write(EEPROM_ADVSENSOR_CHAN2A_PULSE_HI, 0x00);
	EEPROM.write(EEPROM_ADVSENSOR_CHAN2A_PULSE_LO, 0x96);
	EEPROM.write(EEPROM_ADVSENSOR_CHAN2A_PULSE_UNITS, GUIMENU_UNITS_MS);

	EEPROM.write(EEPROM_ADVSENSOR_CHAN2B_PULSE_HI, 0x00);
	EEPROM.write(EEPROM_ADVSENSOR_CHAN2B_PULSE_LO, 0x96);
	EEPROM.write(EEPROM_ADVSENSOR_CHAN2B_PULSE_UNITS, GUIMENU_UNITS_MS);

	EEPROM.write(EEPROM_ADVSENSOR_CHAN3A_PULSE_HI, 0x00);
	EEPROM.write(EEPROM_ADVSENSOR_CHAN3A_PULSE_LO, 0x96);
	EEPROM.write(EEPROM_ADVSENSOR_CHAN3A_PULSE_UNITS, GUIMENU_UNITS_MS);

	EEPROM.write(EEPROM_ADVSENSOR_CHAN3B_PULSE_HI, 0x00);
	EEPROM.write(EEPROM_ADVSENSOR_CHAN3B_PULSE_LO, 0x96);
	EEPROM.write(EEPROM_ADVSENSOR_CHAN3B_PULSE_UNITS, GUIMENU_UNITS_MS);
	// THE REST
	EEPROM.write(EEPROM_ADVSENSOR_TRIGMOBILE, 0x01);
	EEPROM.write(EEPROM_ADVSENSOR_REST_DELAY_HI, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_ADVSENSOR_REST_DELAY_LO, 0x00);		// Defaults to 0
	EEPROM.write(EEPROM_ADVSENSOR_REST_DELAY_UNITS, GUIMENU_UNITS_MS);		// Defaults to 0
	EEPROM.write(EEPROM_ADVSENSOR_TRIGGER_ON, 0x01);

	//sensor video
	store_default_units_value (EEPROM_SENSORVIDEO_DELAY_HI, 0, GUIMENU_UNITS_S);
	store_default_units_value(EEPROM_SENSORVIDEO_STOPAFTER_HI, 30, GUIMENU_UNITS_S);
	EEPROM.write(EEPROM_SENSORVIDEO_TRIGGER, 0);
	EEPROM.write(EEPROM_SENSORVIDEO_TIMESACTIVE, 0);
	EEPROM.write(EEPROM_SENSORVIDEO_START_HOURS, 0x00);
	EEPROM.write(EEPROM_SENSORVIDEO_START_MINS, 0x00);
	EEPROM.write(EEPROM_SENSORVIDEO_END_HOURS, 0x00);
	EEPROM.write(EEPROM_SENSORVIDEO_END_MINS, 0x00);
	EEPROM.write(EEPROM_SENSORVIDEO_TRIGGERON, 0);

	#ifdef INCLUDE_NEWMODE
	EEPROM.write (EEPROM_NEWMODE_TRIGGERON, STACK_TRIGGER_ONLY);
	EEPROM.write (EEPROM_NEWMODE_DELAY_HI, 0x00);
	EEPROM.write (EEPROM_NEWMODE_DELAY_LO, 0x01);
	EEPROM.write (EEPROM_NEWMODE_DELAY_UNITS, GUIMENU_UNITS_S);
	#endif	
}


void setup(){
	
 pinMode(BackLight,OUTPUT);
 digitalWrite(BackLight, 0);
 	
#ifdef VERSION_THREE_HW
  pinMode(LCD_POWER, OUTPUT);
  digitalWrite(LCD_POWER, 0);
#endif
 
  pinMode(Stack,INPUT);
  pinMode(UpButton,INPUT);
  pinMode(DownButton,INPUT);
  pinMode(LeftButton,INPUT);
  pinMode(SelectButton,INPUT);
  pinMode(RightButton,INPUT);	//returns nothing
  
  pinMode(AudioRight,INPUT);
  pinMode(AudioLeft,INPUT);
  
  pinMode(Focus,OUTPUT);
  pinMode(Trigger,OUTPUT);
  pinMode(CAMERAOUT2_A,OUTPUT);		
  pinMode(CAMERAOUT2_B,OUTPUT);		
  pinMode(CAMERAOUT3_A,OUTPUT);
  pinMode(CAMERAOUT3_B,OUTPUT);

#ifndef VERSION_THREE_HW
  pinMode(BONUS_PIN,OUTPUT);
  digitalWrite(BONUS_PIN,HIGH);
#endif
  
  pinMode(MIC,OUTPUT);
  pinMode(STACK_PWR,OUTPUT);
	
  digitalWrite(CAMERAOUT2_A, 0);
  digitalWrite(CAMERAOUT2_B, 0);
  digitalWrite(CAMERAOUT3_A, 0);
  digitalWrite(CAMERAOUT3_B, 0);
  digitalWrite(Focus, 0);
  digitalWrite(Trigger, 0);
  digitalWrite(MIC, 0);
 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//				8Mhz clock chosen for startup, to remain in safe operating
	//				zone during low battery conditions. Once the Boost converter has started
	//				a faster clock can be chosen
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//8MHz Clock
	OSC.CTRL |= OSC_RC32MEN_bm; // turn on 32 MHz oscillator
	CCP = CCP_IOREG_gc;
	CLK.PSCTRL = 0b0001100;
	while (!(OSC.STATUS & OSC_RC32MRDY_bm)) { }; // wait for it to start
	DFLLRC32M.CTRL = DFLL_ENABLE_bm ;				//enable calibrated clock
	CCP = CCP_IOREG_gc;
	CLK.CTRL = CLK_SCLKSEL_RC32M_gc;
 
	//Adjust timings accordingly
	
	TCF0.CTRLA    = TC_CLKSEL_DIV2_gc;			//
  
#ifndef _FASTBOOT

  if(!digitalRead(SelectButton))		//Has the user pressed the button to turn the device on?
  {
	if(EEPROM.read (EEPROM_LCD_CONTRAST_SET) != 0xFF)		//if this is the first time we power up, don't wait for 2 seconds
	{
		delay(2000);						//wait for 2 sec
	}
	
  }
  
  
  if(digitalRead(SelectButton))
  {
	PowerDownFunc(input);				//If not, then false alarm (batteries have been replaced)
  }
  
  #ifdef VERSION_THREE_HW
  pinMode(LCD_POWER, OUTPUT);
  digitalWrite(LCD_POWER, 1);
  #endif
  
  digitalWrite(BackLight, 1);
	
#endif // _FASTBOOT

  digitalWrite(STACK_PWR, 0);	//turn power to the stack off 
#ifdef VERSION_THREE_HW
  pinMode(LDO_EN,OUTPUT);
#endif
  digitalWrite(LDO_EN, 1);


		  
  PORTA_INTCTRL = 0x00;			//interrupt priority off
  

	start_lcd (DEFAULT_LCD_CONTRAST);

	
	
	
if(!digitalRead(UpButton) && !digitalRead(DownButton))		//condition for factory re-set
{
	EEPROM.write(EEPROM_LCD_CONTRAST_SET, 0xFF);

	guimenu_clearpage();
	guimenu_println("FACTORY RESET!");
	guimenu_updatepage();
	delay(2000);
	reset();
}
  

    guimenu_update();

    SetupDelay = 0;
    ReTriggerDelay = 1;
    SMobileOutputEnabled = 0;
    SMobileInputEnabled = 0;
	
	Infinite = 1;
	Interval = 1;
	SelectedStartDelay = 0;
	
	//stack defaults
	EEPROM.write(EEPROM_STACK_CONFIG,OR_CONFIG);
	
	pinMode(BATTERY_MON,INPUT);
	

	ADCB.CTRLA = ADC_ENABLE_bm ; // Enable the ADC
	ADCB.CTRLB = (1<<4); // Signed Mode
	ADCB.REFCTRL = 0; // Internal 1v ref
	ADCB.EVCTRL = 0 ; // no events
	ADCB.PRESCALER = ADC_PRESCALER_DIV64_gc ;
	delay(1);
	ADCB.CH0.CTRL = ADC_CH_INPUTMODE0_bm; // 0x01
	ADCB.CH0.MUXCTRL = ADC_CH_MUXINT0_bm;
	ADCB.CH0.INTCTRL = 0; // No interrupt
	
	
	
	
	MobileTriggerSetup();

	LowSysClock();
	
	PORTA_INTCTRL = 0x00;			//interrupt priority off
}

void store_default_units_value (uint8_t address, uint16_t store_value, uint8_t units)
{
	uint8_t hi, lo;
	
	hi = store_value >> 8;
	lo = store_value - (hi << 8);
	
	EEPROM.write(address, hi); 
	EEPROM.write((address + 1), lo);
	EEPROM.write((address + 2), units);	
}



/*****************************************************************************
*
*   Function name : LowBattery
*
*   Returns :       NIL
*
*   Parameters :
*
*   Purpose : indicates a low battery
*
*****************************************************************************/

void LowBattery (void)
{
	guimenu_clearpage();
	guimenu_println ("BATTERY DEPLETED");
	guimenu_updatepage();
	delay (3000);
	PowerDownFunc (input);
}
/*****************************************************************************
*
*   Function name : timer1
*
*   Returns :       NIL
*
*   Parameters :
*
*   Purpose : Sets up Timer 1 interrupt
*
*****************************************************************************/

void timer1(int ms){ 

	//with a 16MHz clock divided by 8 means there are 2000 ticks per millisecond 
	TC_SetPeriod(&TCC1,ms*2000); 
	TC1_SetOverflowIntLevel(&TCC1,TC_OVFINTLVL_LO_gc); 
	TC1_ConfigClockSource(&TCC1,TC_CLKSEL_DIV8_gc); 
	
}

	
/*****************************************************************************
*
*   Function name : HardwareTest
*
*   Returns :       NIL
*
*   Parameters :
*
*   Purpose : 
*
*****************************************************************************/
#ifndef _DISABLE_OLD_CODE
void HardwareTest()
{
		pinMode(MIC,OUTPUT);
		analogWrite(13, 160);
		while(1);
}


/*****************************************************************************
*
*   Function name : MIC_OUT
*
*   Returns :       NIL
*
*   Parameters :  
*
*   Purpose :      
*
*****************************************************************************/

void MIC_OUT()
{
  while(GetButton() == KEY_NULL)    //repeat until button pressed
  {
    digitalWrite(MIC,1);
    delayMicroseconds(500);
    digitalWrite(MIC,0);
    delayMicroseconds(500); 
  }
}
#endif
/*****************************************************************************
*
*   Function name : AUDIO_READ
*
*   Returns :       NIL
*
*   Parameters :  
*
*   Purpose :      
*
*****************************************************************************/

int AUDIO_READ(void)
{
  static int Value;
 
   uint8_t oldSREG = SREG;
   cli();					//disable interrupts whilst taking an analog read as otherwise the data might be corrupted by the battery monitor reading
   Value = analogRead(AudioLeft);
   SREG = oldSREG;


   if(Value >= 60)                //if above a setpoint then output. analog read returns 0 - 255
   {
     return 1;
   }
  
#ifdef _STEREO_MOBILE 

   Value = analogRead(AudioRight);    
   
   if(Value >= 60)
   {
     return 1;
   }
   
#endif   //_STEREO_MOBILE

   else
   {
     return 0;
   }
   
   
 
}

/*****************************************************************************
*
*   Function name : MOB_IN
*
*   Returns :       NIL
*
*   Parameters :  
*
*   Purpose :      
*
*****************************************************************************/
#ifndef _DISABLE_OLD_CODE
char MOB_IN(char input)
{
    
   if(state == ST_SEN_TMLPSE_OP_MOBIN_OFF_FUNC)
   {
     TLMobileInputEnabled = 0;
     nextstate = ST_SEN_TMLPSE_OP_MOBIN;
   }
   
   else if(state == ST_SEN_TMLPSE_OP_MOBIN_ON_FUNC)
   {
     TLMobileInputEnabled = 1;
     nextstate = ST_SEN_TMLPSE_OP_MOBIN;
   }

   else if(state == ST_SEN_OP_MOBIN_OFF_FUNC)
   {
     SMobileInputEnabled = 0;
     nextstate = ST_SEN_OP_MOBIN;
   }
     
   else if(state == ST_SEN_OP_MOBIN_ON_FUNC)
   {
     SMobileInputEnabled = 1;
     nextstate = ST_SEN_OP_MOBIN;
   }
     
     
}

/*****************************************************************************
*
*   Function name : MOB_IN
*
*   Returns :       NIL
*
*   Parameters :  
*
*   Purpose :      
*
*****************************************************************************/

char MOB_OUT(char input)
{
    
   if(state == ST_SEN_TMLPSE_OP_MOBOUT_OFF_FUNC)
   {
     TLMobileOutputEnabled = 0;
     nextstate = ST_SEN_TMLPSE_OP_MOBOUT;
   }
   
   else if(state == ST_SEN_TMLPSE_OP_MOBOUT_ON_FUNC)
   {
     TLMobileOutputEnabled = 1;
     nextstate = ST_SEN_TMLPSE_OP_MOBOUT;
   }
   
   else if(state == ST_SEN_OP_MOBOUT_ON_FUNC)
   {
     SMobileOutputEnabled = 1;
     nextstate = ST_SEN_OP_MOBOUT;
   }
   
   else if(state == ST_SEN_OP_MOBOUT_OFF_FUNC)
   {
     SMobileOutputEnabled = 0;
     nextstate = ST_SEN_OP_MOBOUT;
   }
   
   
     
     
}

#endif
  
 

  
/*****************************************************************************
*
*   Function name : PowerDown
*
*   Returns :       NIL
*
*   Parameters :  
*
*   Purpose :       Shutdown
*
*
*	Notes:		interrupt not jumping to vector. Work around implemented due to time limits but will need to be investigated!
*****************************************************************************/

char PowerDownFunc(char input) {

  guimenu_clearpage();  
#ifdef	VERSION_THREE_HW
  digitalWrite(LCD_POWER, 0);
#endif

  digitalWrite(BackLight, 0);

  digitalWrite(LDO_EN, 0);
  
  pinMode(MIC,OUTPUT);
  pinMode(STACK_PWR,OUTPUT);
  
  digitalWrite(CAMERAOUT2_A, 0);
  digitalWrite(CAMERAOUT2_B, 0);
  digitalWrite(CAMERAOUT3_A, 0);
  digitalWrite(CAMERAOUT3_B, 0);
  digitalWrite(Focus, 0);
  digitalWrite(Trigger, 0);

  digitalWrite(FTDI_CTS,0);
  digitalWrite(FTDI_RXD,0);

  digitalWrite(LCD_DC, 0);
  digitalWrite(LCD_CLK, 0);
  digitalWrite(LCD_DIN, 0);
  digitalWrite(LCD_RST, 0);
  digitalWrite(LCD_CE, 0);
  
  
  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//				8Mhz clock chosen for startup, to remain in safe operating
//				zone during low battery conditions. Once the Boost converter has started
//				a faster clock can be chosen
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //8MHz Clock
  OSC.CTRL |= OSC_RC32MEN_bm; // turn on 32 MHz oscillator
  CCP = CCP_IOREG_gc;
  CLK.PSCTRL = 0b0001100;
  while (!(OSC.STATUS & OSC_RC32MRDY_bm)) { }; // wait for it to start
  DFLLRC32M.CTRL = DFLL_ENABLE_bm ;				//enable calibrated clock
  CCP = CCP_IOREG_gc;
  CLK.CTRL = CLK_SCLKSEL_RC32M_gc;


  PORTA_INT1MASK = 0x04;		//set interrupt to select button
  PORTA_INTCTRL = 0x04;			//interrupt priority
  
  sei();
  ADCA.CTRLA = 0;
  ADCB.CTRLA = 0;
  TCC1.CTRLA = 0x00;		//turn off timer 1
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_cpu();
  sleep_disable();
  reset();      //Equal to a power on
  
  return 0;
}


/*****************************************************************************
*
*   Function name : SendConfigAND
*
*   Returns :       N/A
*
*   Parameters :
*
*   Purpose :       Sends Data to configure sensors attached to the stack as AND
*
*****************************************************************************/

void SendConfigAND(void) {
	
	HighSysClock();
	pinMode(Stack,OUTPUT);
	digitalWrite(Stack, 1);
	digitalWrite(STACK_PWR, 1);	//turn power to the stack on
	delay(250);					//give the sensors some time to power up
	digitalWrite(Stack, 0);
	delay(6);
	digitalWrite(Stack, 1);
	delay(6);
	digitalWrite(Stack, 0);
	delay(6);
	digitalWrite(Stack, 1);
	delay(250);
	pinMode(Stack,INPUT);
	
}

/*****************************************************************************
*
*   Function name : SendConfigOR
*
*   Returns :       N/A
*
*   Parameters :
*
*   Purpose :       Sends Data to configure sensors attached to the stack as AND
*
*****************************************************************************/

void SendConfigOR(void) {
	
	HighSysClock();
	pinMode(Stack,OUTPUT);
	digitalWrite(Stack, 1);
	digitalWrite(STACK_PWR, 1);	//turn power to the stack on
	delay(250);					//give the sensors some time to power up
	digitalWrite(Stack, 0);
	delay(6);      //dwrie takes 4us to execute
	digitalWrite(Stack, 1);
	delay(250);
	pinMode(Stack,INPUT);

	
}

void HighSysClock (void)
{
	//32MHz Clock
	OSC.CTRL |= OSC_RC32MEN_bm; // turn on 32 MHz oscillator
	CCP = CCP_IOREG_gc;
	CLK.PSCTRL = 0b0000000;
	while (!(OSC.STATUS & OSC_RC32MRDY_bm)) { }; // wait for it to start
	DFLLRC32M.CTRL = DFLL_ENABLE_bm ;				//enable calibrated clock
	CCP = CCP_IOREG_gc;
	CLK.CTRL = CLK_SCLKSEL_RC32M_gc;
	
	TCF0.CTRLA    = TC_CLKSEL_DIV8_gc;			//adjust system delay timings
}

void LowSysClock (void)
{
	//16MHz Clock
	OSC.CTRL |= OSC_RC32MEN_bm; // turn on 32 MHz oscillator
	CCP = CCP_IOREG_gc;
	CLK.PSCTRL = 0b0000100;
	while (!(OSC.STATUS & OSC_RC32MRDY_bm)) { }; // wait for it to start
	DFLLRC32M.CTRL = DFLL_ENABLE_bm ;				//enable calibrated clock
	CCP = CCP_IOREG_gc;
	CLK.CTRL = CLK_SCLKSEL_RC32M_gc;
	
	TCF0.CTRLA    = TC_CLKSEL_DIV4_gc;			//adjust system delay timings
}

void StackPowerDown (void)
{
	digitalWrite(STACK_PWR, 0);		//turn power to the stack off
	LowSysClock ();	
}
/*****************************************************************************
*
*   Function name : StateMachine
*
*   Returns :       nextstate
*
*   Parameters :    state, stimuli
*
*   Purpose :       Shifts between the different states
*
*****************************************************************************/

unsigned char StateMachine (unsigned char state, unsigned char stimuli)
{
    uint8_t nextstate = state;    // Default stay in same state
    uint8_t thex;
    unsigned char teststate,testnextstate; 
   
    thex = 0;

	teststate = menu_nextstate[thex].state;
    testnextstate =  menu_nextstate[thex].nextstate[stimuli];	
    
	while (teststate != 0)
    {
		if (teststate == state)
		{		
			return testnextstate;
		}
      
		thex++;
  
		teststate = menu_nextstate[thex].state;   
		testnextstate =  menu_nextstate[thex].nextstate[stimuli];
    } 
	
    return nextstate;
}


char SensorSettlingDelay (uint8_t page_number, char end_state, char cancel_state, char TriggerOn_addr)
{
	uint32_t start_time_secs = millis();
	uint32_t ElapsedTime = 0;
	uint8_t return_state = end_state;
	
	char stackConfiguration = EEPROM.read (TriggerOn_addr);
	if (stackConfiguration == OR_CONFIG)	//Send signal to the sensors to tell them which mode to operate in
	{
		SendConfigOR();
	}
	
	else
	{
		SendConfigAND();
	}
	
	guimenu_progressbar_start (page_number, SENSOR_SETTLING_TIME_MS, GUIMENU_UNITS_S, 0);
		
	while ((ElapsedTime <= SENSOR_SETTLING_TIME_MS) && (return_state != cancel_state))
	{
		guimenu_progressbar_update ((SENSOR_SETTLING_TIME_MS - ElapsedTime), 0);
		ElapsedTime = millis() - start_time_secs;
		
		if (GetButton () == KEY_MINUS)
		{
			digitalWrite(Focus, 0);
			digitalWrite(Trigger, 0);
			digitalWrite(CAMERAOUT2_A, 0);
			digitalWrite(CAMERAOUT2_B, 0);
			digitalWrite(CAMERAOUT3_A, 0);
			digitalWrite(CAMERAOUT3_B, 0);
			StackPowerDown();
			return_state = cancel_state;
		}
	}
	
	return return_state;
}


  

void loop (void)
{
	char current_menu_page = GUIMENU_TIMELAPSE_TITLE_PAGE;
  
	state = nextstate = ST_TMLPSE;
	pStateFunc = NULL;
  
	// Display Splash Screen for a certain time
	guimenu_displaypage (GUIMENU_START_PAGE);
	
	#ifndef _FASTBOOT
	delay (3000);
	#endif
	
	
	// Display Initial Menu
	guimenu_displaypage (current_menu_page);

	while(1)
	{
		
		input = GetButton();    //Check keypad situation
		  
		if (pStateFunc)
		{
			// When in this state, we must call the state function
			nextstate = pStateFunc(input);
		}
		else if (input != KEY_NULL)
		{
			// Plain menu, clock the state machine
			nextstate = StateMachine (state, input);
		}

        if (nextstate != state)
        {
			state = nextstate;
			for (current_menu_page=0; menu_state[current_menu_page].state; current_menu_page++)
            {
                if (menu_state[current_menu_page].state == state)
                {
					guimenu_displaypage (menu_state[current_menu_page].page_number);
					pStateFunc = menu_state[current_menu_page].pFunc;
					delay(250);
					break;
                }
            }
        }
	}
}
  

#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"
#include "MenuDefines.h"
#include "Arduino.h"
#include "HardwareGlobals.h"
#include "EEPROM.h"
#include "eeprom_addresses.h"
#include "guimenu.h"
#include "Menu.h"
#include "Inputs.h"


static uint8_t input_key;


extern unsigned long (*CurrentTimeSelector (unsigned char Units))(void);

char AdvancedSensor(char input)
{
  unsigned long SecondaryOutputADelay, SecondaryOutputBDelay, TertiaryOutputADelay, TertiaryOutputBDelay, MobileOutputDelay = 0,ElapsedTime, StartTime;
  unsigned char HighByte,LowByte,StartDelayUnits;
  unsigned char TriggerInputsignal,Units, StartDelayLow,StartDelayHigh,MobOut;  
  bool SecondaryOutputAServiced, SecondaryOutputBServiced, TertiaryOutputAServiced, TertiaryOutputBServiced, MobileOutputServiced, ReTriggerServiced;
  bool PrimaryOutputAServiced,PrimaryOutputBServiced;
 
  unsigned long SecondaryOutputAPulse, SecondaryOutputBPulse, TertiaryOutputAPulse, TertiaryOutputBPulse, ReTriggerDelay, StartDelay,MobileOutputRunTime = 150000;
  unsigned long (*CurrentTime)(void),TriggerDelay,PrimaryOutputADelay,PrimaryOutputBDelay,PrimaryOutputAPulse,PrimaryOutputBPulse;

  LowByte  = EEPROM.read(EEPROM_ADVSENSOR_REST_DELAY_LO);
  HighByte = EEPROM.read(EEPROM_ADVSENSOR_REST_DELAY_HI);
  ReTriggerDelay = (HighByte << 8) | LowByte;
  Units = EEPROM.read(EEPROM_ADVSENSOR_REST_DELAY_UNITS);
  ReTriggerDelay = formatTimeToMicro(ReTriggerDelay,Units);				//Value must be converted to us
  
  LowByte  =  EEPROM.read(EEPROM_ADVSENSOR_CHAN1A_DELAY_LO);
  HighByte =  EEPROM.read(EEPROM_ADVSENSOR_CHAN1A_DELAY_HI);
  PrimaryOutputADelay = (HighByte << 8) | LowByte;
  Units = EEPROM.read(EEPROM_ADVSENSOR_CHAN1A_DELAY_UNITS);
  PrimaryOutputADelay = formatTimeToMicro(PrimaryOutputADelay,Units);					// Value must be converted to us

  LowByte  =  EEPROM.read(EEPROM_ADVSENSOR_CHAN1A_PULSE_LO);
  HighByte =  EEPROM.read(EEPROM_ADVSENSOR_CHAN1A_PULSE_HI);
  PrimaryOutputAPulse = (HighByte << 8) | LowByte;	
  Units = EEPROM.read(EEPROM_ADVSENSOR_CHAN1A_PULSE_UNITS);
  PrimaryOutputAPulse = formatTimeToMicro(PrimaryOutputAPulse,Units);					//Value must be converted to us

  LowByte  =  EEPROM.read(EEPROM_ADVSENSOR_CHAN1B_DELAY_LO);
  HighByte =  EEPROM.read(EEPROM_ADVSENSOR_CHAN1B_DELAY_HI);
  PrimaryOutputBDelay = (HighByte << 8) | LowByte;	
  Units = EEPROM.read(EEPROM_ADVSENSOR_CHAN1B_DELAY_UNITS);
  PrimaryOutputBDelay = formatTimeToMicro(PrimaryOutputBDelay,Units);					//Value must be converted to us

  LowByte  =  EEPROM.read(EEPROM_ADVSENSOR_CHAN1B_PULSE_LO);
  HighByte =  EEPROM.read(EEPROM_ADVSENSOR_CHAN1B_PULSE_HI);
  PrimaryOutputBPulse = (HighByte << 8) | LowByte;	
  Units = EEPROM.read(EEPROM_ADVSENSOR_CHAN1B_PULSE_UNITS);
  PrimaryOutputBPulse = formatTimeToMicro(PrimaryOutputBPulse,Units);					//Value must be converted to us

  LowByte =  EEPROM.read(EEPROM_ADVSENSOR_CHAN2A_DELAY_LO);
  HighByte =  EEPROM.read(EEPROM_ADVSENSOR_CHAN2A_DELAY_HI);
  SecondaryOutputADelay = (HighByte << 8) | LowByte; 
  Units = EEPROM.read(EEPROM_ADVSENSOR_CHAN2A_DELAY_UNITS);
  SecondaryOutputADelay = formatTimeToMicro(SecondaryOutputADelay,Units);					//Value must be converted to us
  
  LowByte =  EEPROM.read(EEPROM_ADVSENSOR_CHAN2B_DELAY_LO);
  HighByte =  EEPROM.read(EEPROM_ADVSENSOR_CHAN2B_DELAY_HI);
  SecondaryOutputBDelay = (HighByte << 8) | LowByte;		
  Units = EEPROM.read(EEPROM_ADVSENSOR_CHAN2B_DELAY_UNITS);
  SecondaryOutputBDelay = formatTimeToMicro(SecondaryOutputBDelay,Units);					//Value must be converted to us  

  LowByte =  EEPROM.read(EEPROM_ADVSENSOR_CHAN2A_PULSE_LO);
  HighByte =  EEPROM.read(EEPROM_ADVSENSOR_CHAN2A_PULSE_HI);
  SecondaryOutputAPulse = (HighByte << 8) | LowByte;		
  Units = EEPROM.read(EEPROM_ADVSENSOR_CHAN2A_PULSE_UNITS);
  SecondaryOutputAPulse = formatTimeToMicro(SecondaryOutputAPulse,Units);					//Value must be converted to us   
 
  LowByte =  EEPROM.read(EEPROM_ADVSENSOR_CHAN2B_PULSE_LO);
  HighByte =  EEPROM.read(EEPROM_ADVSENSOR_CHAN2B_PULSE_HI);
  SecondaryOutputBPulse = (HighByte << 8) | LowByte;		
  Units = EEPROM.read(EEPROM_ADVSENSOR_CHAN2B_PULSE_UNITS);
  SecondaryOutputBPulse = formatTimeToMicro(SecondaryOutputBPulse,Units);					//Value must be converted to us
 
  LowByte =  EEPROM.read(EEPROM_ADVSENSOR_CHAN3A_DELAY_LO);
  HighByte =  EEPROM.read(EEPROM_ADVSENSOR_CHAN3A_DELAY_HI);
  TertiaryOutputADelay = (HighByte << 8) | LowByte;     
  Units = EEPROM.read(EEPROM_ADVSENSOR_CHAN3A_DELAY_UNITS);
  TertiaryOutputADelay = formatTimeToMicro(TertiaryOutputADelay,Units);					//Value must be converted to us
  
  LowByte =  EEPROM.read(EEPROM_ADVSENSOR_CHAN3A_PULSE_LO);
  HighByte =  EEPROM.read(EEPROM_ADVSENSOR_CHAN3A_PULSE_HI);
  TertiaryOutputAPulse = (HighByte << 8) | LowByte;		
  Units = EEPROM.read(EEPROM_ADVSENSOR_CHAN3A_PULSE_UNITS);
  TertiaryOutputAPulse = formatTimeToMicro(TertiaryOutputAPulse,Units);					//Value must be converted to us  

  LowByte =  EEPROM.read(EEPROM_ADVSENSOR_CHAN3B_PULSE_LO);
  HighByte =  EEPROM.read(EEPROM_ADVSENSOR_CHAN3B_PULSE_HI);
  TertiaryOutputBPulse = (HighByte << 8) | LowByte;		
  Units = EEPROM.read(EEPROM_ADVSENSOR_CHAN3B_PULSE_UNITS);
  TertiaryOutputBPulse = formatTimeToMicro(TertiaryOutputBPulse,Units);					//Value must be converted to us   
 
  LowByte =  EEPROM.read(EEPROM_ADVSENSOR_CHAN3B_DELAY_LO);
  HighByte =  EEPROM.read(EEPROM_ADVSENSOR_CHAN3B_DELAY_HI);
  TertiaryOutputBDelay = (HighByte << 8) | LowByte;		
  Units = EEPROM.read(EEPROM_ADVSENSOR_CHAN3B_DELAY_UNITS);
  TertiaryOutputBDelay = formatTimeToMicro(TertiaryOutputBDelay,Units);					//Value must be converted to us

  LowByte =  EEPROM.read(EEPROM_SENSOR_TRIGDELAY_LO);
  HighByte =  EEPROM.read(EEPROM_SENSOR_TRIGDELAY_HI);
  TriggerDelay = (HighByte << 8) | LowByte;		
  Units = EEPROM.read(EEPROM_SENSOR_TRIGDELAY_UNITS);
  TriggerDelay = formatTimeToMicro(TriggerDelay,Units);					//Value must be converted to us  

  StartDelayLow  =  EEPROM.read(EEPROM_SENSOR_TRIGDELAY_LO);
  StartDelayHigh =  EEPROM.read(EEPROM_SENSOR_TRIGDELAY_HI);
  StartDelay = (StartDelayHigh << 8) | StartDelayLow;								
  StartDelayUnits = EEPROM.read(EEPROM_SENSOR_TRIGDELAY_UNITS);
  StartDelay = formatTime(StartDelay, StartDelayUnits);	

  MobOut = EEPROM.read(EEPROM_ADVSENSOR_TRIGMOBILE);

  TriggerInputsignal = STACK_TRIGGER_ONLY;

  
	

////////////////////////////////////////

	CurrentTime = CurrentTimeSelector(StartDelayUnits);

	StartTime = CurrentTime();
	ElapsedTime = 0;
	
	while(StartDelay >= ElapsedTime)
	{
		ElapsedTime = CurrentTime() - StartTime;			//how much time has passed?
		
		if(GetButton() == KEY_MINUS)
		{
			digitalWrite(Focus, 0);
			digitalWrite(Trigger, 0);
			digitalWrite(CAMERAOUT2_A, 0);
			digitalWrite(CAMERAOUT2_B, 0);
			digitalWrite(CAMERAOUT3_A, 0);
			digitalWrite(CAMERAOUT3_B, 0);
			mobile_trigger_off();
			StackPowerDown();
			return ST_A_SENSOR_START;
		}
		
	}
	

	ElapsedTime = 0;

while(1)
{
	
	PrimaryOutputAServiced = false;
	PrimaryOutputBServiced = false;
	SecondaryOutputAServiced = false;
	SecondaryOutputBServiced = false;
	TertiaryOutputAServiced = false;
	TertiaryOutputBServiced = false;
	MobileOutputServiced = MobOut;
	ReTriggerServiced = false;				//do these need to be passed in by the user!?
	
	
	
switch (TriggerInputsignal)			//Trigger signals must be received as fast possible, switch case avoids wasting time checking for an input that is not required
{
	
	case STACK_TRIGGER_ONLY:	
	
		while(digitalRead(Stack) == 1)
			{
				if(GetButton() == KEY_MINUS)
				{
					digitalWrite(Focus, 0);
					digitalWrite(Trigger, 0);
					digitalWrite(CAMERAOUT2_A, 0);
					digitalWrite(CAMERAOUT2_B, 0);
					digitalWrite(CAMERAOUT3_A, 0);
					digitalWrite(CAMERAOUT3_B, 0);
					mobile_trigger_off();
					StackPowerDown();
					return ST_A_SENSOR_START;
				}
			}
		
		break;
		
	case MOBILE_TRIGGER_ONLY:
		
		//Read only the mobile input here
		while(AUDIO_READ() == 0)
			{
				if(GetButton() == KEY_MINUS)
				{
					digitalWrite(Focus, 0);
					digitalWrite(Trigger, 0);
					digitalWrite(CAMERAOUT2_A, 0);
					digitalWrite(CAMERAOUT2_B, 0);
					digitalWrite(CAMERAOUT3_A, 0);
					digitalWrite(CAMERAOUT3_B, 0);
					mobile_trigger_off();
					StackPowerDown();
					return ST_A_SENSOR_START;
				}
			}
			
		break;
		
	case BOTH_TRIGGERS:
	
		//Read both inputs here
		while((AUDIO_READ() == 0) && (digitalRead(Stack) == 1))
			{
				if(GetButton() == KEY_MINUS)
				{
					digitalWrite(Focus, 0);
					digitalWrite(Trigger, 0);
					digitalWrite(CAMERAOUT2_A, 0);
					digitalWrite(CAMERAOUT2_B, 0);
					digitalWrite(CAMERAOUT3_A, 0);
					digitalWrite(CAMERAOUT3_B, 0);
					mobile_trigger_off();
					StackPowerDown();
					return ST_A_SENSOR_START;
				}
			}
		break;
	
	default:
		//something has gone wrong if we get here! 
		break;	
}
	

	if(TriggerDelay)
	{
		StartTime = micros();
		ElapsedTime = 0;
		while(ElapsedTime <= TriggerDelay)
		{
			ElapsedTime = micros() - StartTime;			//how much time has passed?

			if(GetButton() == KEY_MINUS)
			{
				digitalWrite(Focus, 0);
				digitalWrite(Trigger, 0);
				digitalWrite(CAMERAOUT2_A, 0);
				digitalWrite(CAMERAOUT2_B, 0);
				digitalWrite(CAMERAOUT3_A, 0);
				digitalWrite(CAMERAOUT3_B, 0);
				mobile_trigger_off();
				StackPowerDown();
				return ST_A_SENSOR_START;
			}

		}

	}


	StartTime = micros();
	
	
	while(!(PrimaryOutputAServiced && PrimaryOutputBServiced && SecondaryOutputAServiced && SecondaryOutputBServiced && TertiaryOutputAServiced && TertiaryOutputBServiced && MobileOutputServiced && ReTriggerServiced))							//not all of the conditions have been met
	
	{
		
		ElapsedTime = micros() - StartTime;			//how much time has passed?
		
			if((ElapsedTime >= PrimaryOutputADelay) && (!PrimaryOutputAServiced)) //has enough time passed before we should trigger the second output, Channel A?
			{
				digitalWrite(Focus, 1);										  //yes, it has
			
				if(ElapsedTime >= (PrimaryOutputADelay + PrimaryOutputAPulse))	  //has enough time passed for the pulse time for this channel?
				{
					digitalWrite(Focus, 0);
					PrimaryOutputAServiced = true;								  //yes, it has, turn off and mark complete
				}

			}

			if((ElapsedTime >= PrimaryOutputBDelay) && (!PrimaryOutputBServiced)) //has enough time passed before we should trigger the second output, Channel A?
			{
				digitalWrite(Trigger, 1);										  //yes, it has
			
				if(ElapsedTime >= (PrimaryOutputBDelay + PrimaryOutputBPulse))	  //has enough time passed for the pulse time for this channel?
				{
					digitalWrite(Trigger, 0);
					PrimaryOutputBServiced = true;								  //yes, it has, turn off and mark complete
				}

			}
		
			if((ElapsedTime >= SecondaryOutputADelay) && (!SecondaryOutputAServiced)) //has enough time passed before we should trigger the second output, Channel A?
			{
				digitalWrite(CAMERAOUT2_A, 1);										  //yes, it has
			
				if(ElapsedTime >= (SecondaryOutputADelay + SecondaryOutputAPulse))	  //has enough time passed for the pulse time for this channel?
				{
					digitalWrite(CAMERAOUT2_A, 0);
					SecondaryOutputAServiced = true;								  //yes, it has, turn off and mark complete
				}

			}
		
			if((ElapsedTime >= SecondaryOutputBDelay) && (!SecondaryOutputBServiced)) //has enough time passed before we should trigger the second output, Channel B?
			{
				digitalWrite(CAMERAOUT2_B, 1);										  //yes, it has
			
				if(ElapsedTime >= (SecondaryOutputBDelay + SecondaryOutputBPulse))	  //has enough time passed for the pulse time for this channel?
				{
					digitalWrite(CAMERAOUT2_B, 0);
					SecondaryOutputBServiced = true;								  //yes, it has, turn off and mark complete
				}

			}
		
			if((ElapsedTime >= TertiaryOutputADelay) && (!TertiaryOutputAServiced))   //has enough time passed before we should trigger the third output, Channel A?
			{
				digitalWrite(CAMERAOUT3_A, 1);										  //yes, it has
			
				if(ElapsedTime >= (TertiaryOutputADelay + TertiaryOutputAPulse))	  //has enough time passed for the pulse time for this channel?
				{
					digitalWrite(CAMERAOUT3_A, 0);
					TertiaryOutputAServiced = true;								      //yes, it has, turn off and mark complete
				}

			}
		
			if((ElapsedTime >= TertiaryOutputBDelay) && (!TertiaryOutputBServiced))   //has enough time passed before we should trigger the third output, Channel A?
			{
				digitalWrite(CAMERAOUT3_B, 1);										  //yes, it has
			
				if(ElapsedTime >= (TertiaryOutputBDelay + TertiaryOutputBPulse))	  //has enough time passed for the pulse time for this channel?
				{
					digitalWrite(CAMERAOUT3_B, 0);
					TertiaryOutputBServiced = true;								      //yes, it has, turn off and mark complete
				}

			}
		
			if((ElapsedTime >= MobileOutputDelay) && (!MobileOutputServiced))   //has enough time passed before we should trigger the mobile?
			{
				//mobile trigger here!
				mobile_trigger_on();
				
				if((ElapsedTime >= (MobileOutputDelay + MobileOutputRunTime)) && (!MobileOutputServiced))   //has enough time passed before we should trigger the mobile?
				{
					//mobile trigger off here!
					mobile_trigger_off();
					MobileOutputServiced = true;
				}
				
			}
		
		if((ElapsedTime >= ReTriggerDelay) && (!ReTriggerServiced))			//has enough time passed before a re-trigger?
		{
			ReTriggerServiced = true;										
		}																	
		
		
		if(GetButton() == KEY_MINUS)
		{
			digitalWrite(Focus, 0);
			digitalWrite(Trigger, 0);
			digitalWrite(CAMERAOUT2_A, 0);
			digitalWrite(CAMERAOUT2_B, 0);
			digitalWrite(CAMERAOUT3_A, 0);
			digitalWrite(CAMERAOUT3_B, 0);
			mobile_trigger_off();
			StackPowerDown();
			return	ST_A_SENSOR_START;
		}
	}
}	  
	

	digitalWrite(Focus, 0);
	digitalWrite(Trigger, 0);
	digitalWrite(CAMERAOUT2_A, 0);
	digitalWrite(CAMERAOUT2_B, 0);
	digitalWrite(CAMERAOUT3_A, 0);
	digitalWrite(CAMERAOUT3_B, 0);
	mobile_trigger_off();
	StackPowerDown();
	guimenu_operation_complete(GUIMENU_SENSOR_STOP_PAGE, &input_key);
    return ST_A_SENSOR_START;

}


char AdvancedSensorConfigure (char input)
{
	char return_state = SensorSettlingDelay (GUIMENU_ADVSENSOR_CONFIG_PAGE, ST_A_SENSOR_STOP, ST_A_SENSOR_START , EEPROM_ADVSENSOR_TRIGGER_ON);
	
	return return_state;
}


char A_Sensor_CH1A_D (char input)
{
	char next_state = 0;

	
	guimenu_selector (GUIMENU_A_SENSOR_CH1A_DELAY_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_A_SENSOR_START;
			break;
			
			case KEY_DOWN:
			next_state = ST_A_SENSOR_CH1A_P;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char A_Sensor_CH1A_P (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_A_SENSOR_CH1A_PULSE_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_A_SENSOR_CH1A_D;
			break;
			
			case KEY_DOWN:
			next_state = ST_A_SENSOR_CH1B_D;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char A_Sensor_CH1B_D (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_A_SENSOR_CH1B_DELAY_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_A_SENSOR_CH1A_P;
			break;
			
			case KEY_DOWN:
			next_state = ST_A_SENSOR_CH1B_P;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char A_Sensor_CH1B_P (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_A_SENSOR_CH1B_PULSE_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_A_SENSOR_CH1B_D;
			break;
			
			case KEY_DOWN:
			next_state = ST_A_SENSOR_CH2A_D;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char A_Sensor_CH2A_D (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_A_SENSOR_CH2A_DELAY_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_A_SENSOR_CH1B_P;
			break;
			
			case KEY_DOWN:
			next_state = ST_A_SENSOR_CH2A_P;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char A_Sensor_CH2A_P (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_A_SENSOR_CH2A_PULSE_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_A_SENSOR_CH2A_D;
			break;
			
			case KEY_DOWN:
			next_state = ST_A_SENSOR_CH2B_D;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char A_Sensor_CH2B_D (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_A_SENSOR_CH2B_DELAY_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_A_SENSOR_CH2A_P;
			break;
			
			case KEY_DOWN:
			next_state = ST_A_SENSOR_CH2B_P;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char A_Sensor_CH2B_P (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_A_SENSOR_CH2B_PULSE_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_A_SENSOR_CH2B_D;
			break;
			
			case KEY_DOWN:
			next_state = ST_A_SENSOR_CH3A_D;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char A_Sensor_CH3A_D (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_A_SENSOR_CH3A_DELAY_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_A_SENSOR_CH2B_P;
			break;
			
			case KEY_DOWN:
			next_state = ST_A_SENSOR_CH3A_P;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char A_Sensor_CH3A_P (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_A_SENSOR_CH3A_PULSE_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_A_SENSOR_CH3A_D;
			break;
			
			case KEY_DOWN:
			next_state = ST_A_SENSOR_CH3B_D;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char A_Sensor_CH3B_D (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_A_SENSOR_CH3B_DELAY_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_A_SENSOR_CH3A_P;
			break;
			
			case KEY_DOWN:
			next_state = ST_A_SENSOR_CH3B_P;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char A_Sensor_CH3B_P (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_A_SENSOR_CH3B_PULSE_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_A_SENSOR_CH3B_D;
			break;
			
			case KEY_DOWN:
			next_state = ST_A_SENSOR_TRIGGER_MOBILE;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char A_Sensor_Trigger_Mobile (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_A_SENSOR_TRIGGER_MOBILE_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_A_SENSOR_CH3B_P;
			break;
			
			case KEY_DOWN:
			next_state = ST_A_SENSOR_RESET_DELAY;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char A_Sensor_Reset_Delay (char input)
{
	char next_state = 0;
	
	guimenu_selector (GUIMENU_A_SENSOR_RESET_DELAY_PAGE, &input_key);

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
			next_state = ST_A_SENSOR_TRIGGER_MOBILE;
			break;
			
			case KEY_DOWN:
			next_state = ST_A_SENSOR_TRIGGER_ON;
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


char A_Sensor_Trigger_On (char input)
{
	char next_state = 0;
	
	while (!next_state)
	{
		guimenu_selector (GUIMENU_A_SENSOR_TRIGGER_ON_PAGE, &input_key);
		
		switch (input_key)
		{
			case KEY_PREV:
				next_state = ST_A_SENSOR_RESET_DELAY;
			break;
			
			case KEY_DOWN:
				next_state = ST_A_SENSOR_TRIGGER_ON;
			break;
		}
	}

	return next_state;
}

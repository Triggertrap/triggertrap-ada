#include "MenuDefines.h"
#include "Arduino.h"
#include "HardwareGlobals.h"
#include "EEPROM.h"
#include "eeprom_addresses.h"
#include "guimenu.h"
#include "Menu.h"
#include "Inputs.h"
#include "NewMode.h"

/******************************************************************************************************************

HOW TO ADD A NEW MODE

A) Add this new mode by defining 'INCLUDE_NEWMODE' as a symbol in the project properties for C++ compilation.
B) Build this and check that your build environment is working. This new mode should be added in and allow to see
   how to trigger any output from the mobile and / or a sensor (stack) trigger. And then keep triggering using a
   delay. The delay can be adjusted and you can choose which trigger input(s) are used via the menu settings.
C) Delete the 'INCLUDE_NEWMODE' symbol from the project properties.
D) When you are ready to write your own new mode...

1) Copy the NewMode.h and NewMode.cpp and rename them to reflect your own mode, e.g. MyTimelapse.cpp and .h. Don't
   forget to add these files to to he Solution via the Solution Explorer.
2) In your new .cpp file, rename the NewModeRun, NewModeSettling functions to reflect your own mode and ensure your 
   new .h file is updated accordingly. Add a #include for your .h file into Menu.h.
3) With reference to the NewMode menu sub state and NewMode sub state machines shown below, create your own
   state machines. It is likely that they will be similar, but with different names for each of the states, menu
   pages and calling functions. The Ada framework will follow the state machine, so time spent getting this right
   is time well spent.
   
   When the Ada framework changes to a particular state, it will display a particular menu page and then optionally call a
   function which have defined in your new .cpp file. The states can be forced by returning a new state Id from
   these functions or the framework will use the next button press to choose the next state. The state machine
   is defined in StateMachine.cpp.
	
   All state Ids are defined in MenuDefines.h.
   
   For each new state which requires the framework to change the state depending on a button press, add a new entry
   into menu_nextstate[], with the format as follows:
		
	{
		STARTING_STATE,
		{
			STARTING_STATE,
			STATE1,				// KEY_MINUS
			STATE2,				// KEY_SELECT
			STATE3,				// KEY_PREV
			STATE4,				// KEY_PLUS
			STATE5				// KEY_DOWN
		}
	},
	
   You can see each button will transition the framework to a particular state.
   
   menu_state[] details which menu page is displayed when a state is entered and what function in your new .cpp is
   called, as defined in a new entry with the following format:
	
	{STATE,					GUIMENU_PAGE,			Function},
		
   If there is no function to call, use NULL.
	
   So far the following files will now have been created or modified:
	
	YourMode.cpp						Your version of NewMode.cpp, named appropriately
	YourMode.h							Your version of NewMode.h, named appropriately
	Menu.h								Modified to #include "YourMode.h"
	MenuDefines.h						All your new state machine Id definitions should be in here
	StateMachine.cpp					All your new state machine table entries in menu_state[] & menu_nextstate[]
	
4) Define the EEPROM addresses for the settings of your new mode in eeprom_addresses.h. There are a number of
   different setting types with different addressing (storage) requirements:
	
	list_select							1 address for an index into a list of options (larger number of options)
	thumbwheel_select					2 addresses, 1st one holds low byte, 2nd the high byte of a 16bit value					
	thumbwheel_units_select				3 addresses, as thumbwheel_select, but with a 3rd units byte
	time_select							2 addresses, 1st one holds hours, 2nd minutes of a time (HH:MM)
	toggle_select						1 address for an index into a list of options (smaller number of options)
	
   Then make entries in the setup() function located in TriggerTrap_main.cpp to define the default values for all your
   settings, e.g.
	 
	EEPROM.write (EEPROM_LIST_SELECT_SETTING, 0);			// Defaults to option 1
	
	// Defaults to 256
	EEPROM.write (EEPROM_THUMBWHEEL_SELECT_HI, 1);
	EEPROM.write (EEPROM_THUMBWHEEL_SELECT_LO, 1);
	
	// Defaults to 520 seconds
	store_default_units_value (EEPROM_THUMBWHEEL_UNITS_SELECT_HI, 520, GUIMENU_UNITS_S);
	 
	// Defaults to 03:22
	EEPROM.write (EEPROM_TIME_SELECT_HOURS, 3);
	EEPROM.write (EEPROM_TIME_SELECT_MINS, 22);
	 
	EEPROM.write (EEPROM_TOGGLE_SELECT_SETTING, 1);	// Defaults to option 2
	
    Units can be:
	
	GUIMENU_UNITS_US				Microseconds
	GUIMENU_UNITS_MS				Milliseconds
	GUIMENU_UNITS_S					Seconds
	GUIMENU_UNITS_M					Minutes
	GUIMENU_UNITS_H					Hours
	
   So far the following files will now have been created or modified:
	
	YourMode.cpp					Your version of NewMode.cpp, named appropriately
	YourMode.h						Your version of NewMode.h, named appropriately
	Menu.h							Modified to #include "YourMode.h"
	MenuDefines.h					All your new state machine Id definitions should be in here
	StateMachine.cpp				All your new state machine table entries in menu_state[] & menu_nextstate[]
	eeprom_addresses.h				EEPROM locations for your settings
	TriggerTrap_main.cpp			Your mode's default settings programmed into EEPROM
	
5) Define the GUI menu pages in guimenupages.cpp and page numbers in guimenu_pages.h.

    ***** VERY IMPORTANT *****
	The menu pages must follow on from the last one and from each other, as the menu page number is an index into 
	an array.
	
   The structure of a menu page is of the format:
	
	 guimenu_page_t page_identifer =
        {
	     Pointer to Bitmap			
	     Pointer to Title object,		
	     Pointer to Banner object,		
	     String Id of a button in the middle of the display,
	     MORE_SETTINGS if there are settings for this mode,
	     Pointer to a Selector object,
	     Pointer to a Progress bar object,
	     Pointer to a Scrollbar object
        };
	
   For more information on how to define these objects, see guimenu.h.
	
   All the elements of a page are optional.
   The Title objects are used for the main menu pages.
   Banner objects are for the text at the top of a mode page or setting page.
   Define a Selector object for a setting page.
   Scroll bar objects control shows where you are in your sub menu structure.
   No strings are defined in a menu page, but an Id which is defined in tt_strings.h and specified in tt_strings.dat.
	
   So far the following files will now have been created or modified:
    
	YourMode.cpp						Your version of NewMode.cpp, named appropriately
       YourMode.h						Your version of NewMode.h, named appropriately
       Menu.h							Modified to #include "YourMode.h"
       MenuDefines.h						All your new state machine Id definitions should be in here
       StateMachine.cpp					All your new state machine table entries in menu_state[] & menu_nextstate[]
       eeprom_addresses.h				EEPROM locations for your settings
       TriggerTrap_main.cpp				Your mode's default settings programmed into EEPROM
	guimenu_pages.h					Your page number definitions
	guimenupages.cpp					Your page definitions

6) Define any new string Ids in tt_strings.h and specify them in tt_strings.dat by defining the next string Id number, e.g.

       const char string_148[] PROGMEM = "YOUR MODE";		// For string Id number 148
	   
    ***** VERY IMPORTANT *****
    New strings must follow on from the last one and from each other, as the string Id is an index into an array.
	
   Then insert into to the g_guimenu_stringtable[] at position 148.
	
   The following files will now have been created or modified:
     
	YourMode.cpp						Your version of NewMode.cpp, named appropriately
       YourMode.h						Your version of NewMode.h, named appropriately
       Menu.h							Modified to #include "YourMode.h"
       MenuDefines.h						All your new state machine Id definitions should be in here
       StateMachine.cpp					All your new state machine table entries in menu_state[] & menu_nextstate[]
       eeprom_addresses.h				EEPROM locations for your settings
       TriggerTrap_main.cpp				Your mode's default settings programmed into EEPROM
       guimenu_pages.h					Your page number definitions
       guimenupages.cpp					Your page definitions
	tt_strings.h						Any new string Id definitions
	tt_strings.dat						Any new string table entries
	
7) Add functionality to your new mode by modifying YourMode.cpp. Here are some hints and tips:

	* Ensure that there is a settling delay before using sensor triggering. This has been taken care of using a
	  progress bar and a settling state, e.g. NewModeSettling()
	* When digitalRead(Stack()==0, ANY / ALL of the sensor blocks have triggered. (ANY or ALL can be selected via your own 
	  setting or you can use the setting stored at EEPROM_SENSOR_TRIGGERON which is selected with the High Speed 
	  Flash Trigger On setting. 0 = ALL, 1 = ANY)
	* When AUDIO_READ() == 1, the mobile input has been triggered.
	* Progress bars need their own page defined and are best for showing delays of a few seconds or more.
	* Use get_time (guimenu_time_t  *p_time) to obtain the systen time.
	* Use time_active (uint16_t eeprom_start_address, uint16_t eeprom_stop_address) to return 1 if the current
	  system time is within the two times stored at eeprom_start_address and eeprom_stop_address.
	* get_time_in_secs() returns the system time in seconds
	* Output triggers must be a minimum of 1 second
	
8) Build the project and enjoy your new mode!

******************************************************************************************************************/


/* 
Files modified for NewMode:
	Menu.h									#include "NewMode.h" is located here
	MenuDefines.h							NewMode's state machine Id definitions
	StateMachine.cpp						NewMode's state machine table entries
	eeprom_addresses.h						EEPROM locations for NewMode's settings
	TriggerTrap_main.cpp					NewMode's default settings programmed into EEPROM
	guimenu_pages.h							NewMode's page number definitions
	guimenupages.cpp						NewMode's page definitions
	tt_strings.h							NewMode's string Id definitions
	tt_strings.dat							NewMode's string table entries
*/

/* 
EEPROM Settings for NewMode:
	EEPROM_NEWMODE_TRIGGERON				NewMode's triggering options (STACK_TRIGGER_ONLY, MOBILE_TRIGGER_ONLY, BOTH_TRIGGERS)
											Default: STACK_TRIGGER_ONLY
	EEPROM_NEWMODE_DELAY_HI					NewMode's delay between triggers (Hi byte)
	EEPROM_NEWMODE_DELAY_LO					NewMode's delay between triggers (Lo byte)
											Default: 1
	EEPROM_NEWMODE_DELAY_UNITS				NewMode's delay units (GUIMENU_UNITS_US, GUIMENU_UNITS_MS, GUIMENU_UNITS_S, GUIMENU_UNITS_M, GUIMENU_UNITS_H)
											Default: GUIMENU_UNITS_S
*/

/* 
Menu page numbers (guimenu_pages.h):
	GUIMENU_NEWMODE_TITLE_PAGE				Page used in the main menu
	GUIMENU_NEWMODE_START_PAGE				The first page in NewMode, from which control of the mode can be acheived
	GUIMENU_NEWMODE_SETTLING_PAGE			Shows the sensor settling progress bar
	GUIMENU_NEWMODE_RUNNING_PAGE			Displayed whilst the mode is in progress
	GUIMENU_NEWMODE_TRIGGERON_PAGE			Trigger On Setting Page
	GUIMENU_NEWMODE_DELAY_PAGE				Delay Setting Page
	GUIMENU_NEWMODE_PROG_PAGE				Progress bar page for the delay
*/


/* 
New Mode States (MenuDefines.h):
	ST_NEWMODE
	ST_NEWMODE_START
	ST_NEWMODE_SETTLING
	ST_NEWMODE_RUNNING
	ST_NEWMODE_TRIGGERON
	ST_NEWMODE_DELAY
*/
	

/* New Mode menu sub state machine:

													ST_LEHDR
													GUIMENU_LEHDR_TITLE_PAGE
													Function: NULL
													
														^
														|
														KEY_PREV
														|
												
ST_LEHDR							--KEY_DOWN-->   ST_NEWMODE							--KEY_SELECT-->		ST_NEWMODE_START
GUIMENU_LEHDR_TITLE_PAGE							GUIMENU_NEWMODE_TITLE_PAGE							GUIMENU_NEWMODE_START_PAGE
Function: NULL										Function: NULL											Function: NULL

														|														|
													KEY_DOWN												KEY_MINUS
														|														|
														V														V
												
													ST_SETTINGS												ST_NEWMODE
													GUIMENU_SETTINGS_TITLE_PAGE								GUIMENU_NEWMODE_TITLE_PAGE
													Function: NULL											Function: NULL
												


New Mode sub state machine:

ST_NEWMODE_START					--KEY_SELECT-->	ST_NEWMODE_SETTLING				--------------------->	ST_NEWMODE_RUNNING
GUIMENU_NEWMODE_START_PAGE						GUIMENU_NEWMODE_SETTLING_PAGE						GUIMENU_NEWMODE_RUNNING_PAGE
Function: NULL										Function: NewModeSettling								Function: NewModeRun

	|													|													|
	KEY_DOWN											KEY_MINUS											KEY_MINUS
	|													|													|
	V													V													V
																											
ST_NEWMODE_TRIGGERON				--KEY_PREV->		ST_NEWMODE_START									ST_NEWMODE_START
GUIMENU_NEWMODE_TRIGGERON_PAGE					GUIMENU_NEWMODE_START_PAGE						GUIMENU_NEWMODE_START_PAGE
Function: NewModeTriggerOn								Function: NULL										Function: NULL

	|
	KEY_DOWN
	|
	V
	
ST_NEWMODE_DELAY					--KEY_PREV-->		ST_NEWMODE_TRIGGERON
GUIMENU_NEWMODE_DELAY_PAGE						GUIMENU_NEWMODE_TRIGGERON_PAGE
Function: NewModeDelay								Function: NewModeTriggerOn

*/



// Internal Functions
static void AllOutputsAndStackOff (void);

// Internal Variables
static uint8_t input_key;


char NewModeRun (char input)
{
	unsigned char NewModeRunning = 1;
	unsigned long StartTime = 0UL, Delay = 0, ElapsedTime;
	unsigned char DelayUnits = GUIMENU_UNITS_S;
	unsigned char TriggerInputsignal = STACK_TRIGGER_ONLY;
	unsigned long (*CurrentTime)(void) = NULL;

	// Read the delay settings from the EEPROM
#ifdef INCLUDE_NEWMODE
	Delay = (EEPROM.read (EEPROM_NEWMODE_DELAY_HI) << 8) | EEPROM.read (EEPROM_NEWMODE_DELAY_LO);	
	DelayUnits = EEPROM.read (EEPROM_NEWMODE_DELAY_UNITS);

	// Format the delay with respect to the units
	Delay = formatTime (Delay, DelayUnits);	
	CurrentTime = CurrentTimeSelector (DelayUnits);

	// Read the trigger settings from the EEPROM 
	TriggerInputsignal = EEPROM.read (EEPROM_NEWMODE_TRIGGERON);
#endif
 
 
	// Wait for a trigger before continuing
	// Trigger signals must be received as fast possible,
	// switch case avoids wasting time checking for an input that is not required
	switch (TriggerInputsignal)
	{
		// Trigger coming from ANY or ALL sensor blocks only
		case STACK_TRIGGER_ONLY:
			while ((digitalRead (Stack) == 1) && NewModeRunning)
			{
				// To ensure that we can cancel the mode
				if (GetButton() == KEY_MINUS)
				{
					NewModeRunning = 0;
				}
			}
		break;
		
		// Trigger coming from mobile only
		case MOBILE_TRIGGER_ONLY:
			while ((AUDIO_READ() == 0) && NewModeRunning)
			{
				// To ensure that we can cancel the mode
				if (GetButton() == KEY_MINUS)
				{
					NewModeRunning = 0;
				}
			}
		break;
		
		// Trigger coming from mobile and ANY or ALL sensor blocks
		case BOTH_TRIGGERS:
		while ((AUDIO_READ() == 0) && (digitalRead (Stack) == 1) && NewModeRunning)
			{
				if(GetButton() == KEY_MINUS)
				{
					NewModeRunning = 0;
				}
			}
		break;
	}

	// Run the NewMode: trigger & delay until KEY_MINUS is pressed
	while (NewModeRunning)
	{
#ifdef INCLUDE_NEWMODE
		guimenu_displaypage (GUIMENU_NEWMODE_PROG_PAGE);
#endif
		
		// Send triggers and delay before sending next output triggers
		if (NewModeRunning)
		{
			// Trigger all output triggers, comment out those you don't want
			digitalWrite (Focus, 1);
			digitalWrite (Trigger, 1);
			digitalWrite (CAMERAOUT2_A, 1);
			digitalWrite (CAMERAOUT2_B, 1);
			digitalWrite (CAMERAOUT3_A, 1);
			digitalWrite (CAMERAOUT3_B, 1);
			mobile_trigger_on();
	
			StartTime = CurrentTime();
			ElapsedTime = 0;
			
			// Initialise the progress bar for multiples of seconds or longer
			if (DelayUnits >= GUIMENU_UNITS_S)
			{
#ifdef INCLUDE_NEWMODE
				guimenu_progressbar_start (GUIMENU_NEWMODE_PROG_PAGE, Delay, DelayUnits, 0);
#endif
			}
			
			// This is the delay between each output trigger
			while ((Delay >= ElapsedTime) && NewModeRunning)
			{
				ElapsedTime = CurrentTime() - StartTime;
				
				// Update the progress bar during the delay
				if (DelayUnits >= GUIMENU_UNITS_S)
				{
					if (Delay > ElapsedTime)
					{
						guimenu_progressbar_update ((Delay - ElapsedTime), 0);
					}
					else
					{
						guimenu_progressbar_update(0, 0);
					}
				}
		
				// To ensure that we can cancel the mode
				if(GetButton() == KEY_MINUS)
				{
					NewModeRunning = 0;
				}
		
			}
			
			// Turn off all output triggers, comment out those you don't want
			digitalWrite (Focus, 0);
			digitalWrite (Trigger, 0);
			digitalWrite (CAMERAOUT2_A, 0);
			digitalWrite (CAMERAOUT2_B, 0);
			digitalWrite (CAMERAOUT3_A, 0);
			digitalWrite (CAMERAOUT3_B, 0);
			mobile_trigger_off();
		}
	}  
	
	AllOutputsAndStackOff ();
	
#ifdef INCLUDE_NEWMODE
	// Display a page notifying the user the mode has completed (optional)
	guimenu_operation_complete (GUIMENU_NEWMODE_RUNNING_PAGE, &input_key);
	
    return ST_NEWMODE_START;
#else
	return 0;
#endif
}


// This provides the functionality for the sensor delay settling time
char NewModeSettling (char input)
{
	char return_state = 0;
	
	// The value in EEPROM_SENSOR_TRIGGERON determines the OR or ANY function for the sensor stack
	// To change this between OR and ANY, use the Sensor Mode, Trigger On setting
#ifdef INCLUDE_NEWMODE
	return_state = SensorSettlingDelay (GUIMENU_NEWMODE_SETTLING_PAGE, ST_NEWMODE_RUNNING, ST_NEWMODE_START, EEPROM_SENSOR_TRIGGERON);
#endif

	return return_state;
}


// This provides the functionality for the Trigger On setting
char NewModeTriggerOn (char input)
{
	char next_state = 0;

#ifdef INCLUDE_NEWMODE
	guimenu_selector (GUIMENU_NEWMODE_TRIGGERON_PAGE, &input_key);
#endif

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
#ifdef INCLUDE_NEWMODE
				next_state = ST_NEWMODE_START;
#endif
			break;
			
			case KEY_DOWN:
#ifdef INCLUDE_NEWMODE
				next_state = ST_NEWMODE_DELAY;
#endif
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


// This provides the functionality for the Delay setting
char NewModeDelay (char input)
{
	char next_state = 0;

#ifdef INCLUDE_NEWMODE
	guimenu_selector (GUIMENU_NEWMODE_DELAY_PAGE, &input_key);
#endif

	while (!next_state)
	{
		
		switch (input_key)
		{
			case KEY_PREV:
#ifdef INCLUDE_NEWMODE
				next_state = ST_NEWMODE_TRIGGERON;
#endif
			break;
			
			case KEY_DOWN:
#ifdef INCLUDE_NEWMODE
				next_state = ST_NEWMODE_DELAY;
#endif
			break;
		}
		
		input_key = GetButton();
	}

	return next_state;
}


// Switch all triggers off and turn off the stack to save power
static void AllOutputsAndStackOff (void)
{
	digitalWrite (Focus, 0);
	digitalWrite (Trigger, 0);
	digitalWrite (CAMERAOUT2_A, 0);
	digitalWrite (CAMERAOUT2_B, 0);
	digitalWrite (CAMERAOUT3_A, 0);
	digitalWrite (CAMERAOUT3_B, 0);
	StackPowerDown ();
}


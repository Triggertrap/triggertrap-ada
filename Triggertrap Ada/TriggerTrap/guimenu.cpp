#include <avr/pgmspace.h>
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"
#include "guimenu.h"
#include "guimenu_pages.h"
#include "MenuDefines.h"
#include "HardwareGlobals.h"
#include "EEPROM.h"
#include "eeprom_addresses.h"

#include "tt_strings.dat"		// Never do this...it's only because externs & PROGMEM don't mix! (Bug in GCC)
#include "tt_strings.h"	
#include "Inputs.h"


// Definitions
#define DISPLAY_SCLK				11
#define DISPLAY_DIN					12
#define DISPLAY_DCSEL				9
#define DISPLAY_CS					10
#define DISPLAY_RST					13

// Assume 5 x 5 character font
#define STD_CHAR_WIDTH				5
#define STD_CHAR_HEIGHT				5
#define STD_CHAR_SPACING			1
#define STD_LINE_SPACING			1
#define STD_CHARS_PER_LINE			14

#define MENU_NUMBER_POS_Y			0
#define MENU_NUMBER_SIZE			2
#define MENU_TEXTLINE1_POS_Y		24
#define MENU_TEXTLINE1_SIZE			1
#define MENU_TEXTLINE2_POS_Y		32
#define MENU_TEXTLINE2_SIZE			1
#define MENU_BANNER_SIZE			1
#define MENU_BANNER_TEXT1_POS_X		1
#define MENU_BANNER_TEXT1_POS_Y		1
#define MENU_BANNER_TEXT2_POS_X		1
#define MENU_BUTTON_SIZE			2
#define MENU_BUTTON_TEXT_POS_Y		20
#define MENU_MORE_SETTINGS_POS_X	18
#define MENU_MORE_SETTINGS_POS_Y	39
#define MENU_MORE_SETTINGS_SIZE		1
#define MENU_SELECT_Y_POS			40
#define MENU_SELECT_SIZE			1
#define MENU_SELECTTEXT1_Y_POS		17
#define MENU_SELECTTEXT2_Y_POS		25
#define MENU_TW_BOX_WIDTH			STD_CHAR_WIDTH + 4
#define MENU_TW_BOX_HEIGHT			STD_CHAR_HEIGHT + 4
#define MENU_NUM_OF_TW				5
#define MENU_TW_Y_POS				21	
#define MENU_TW_CANCEL_POS_X		21
#define MENU_TW_CANCEL_SIZE			1
#define MENU_TW_X_POS_OFFSET		13
#define MENU_TWU_X_POS_OFFSET		8
#define MENU_TWU_UNITS_X_POS_OFFSET	60
#define MENU_TWU_BOX_WIDTH			16
#define MENU_TWU_CANCEL_POS_X		42
#define MENU_PBARTEXT1_Y_POS		10
#define MENU_PBARTEXT2_Y_POS		18
#define MENU_PBAR_Y_POS				27
#define MENU_PBAR_HEIGHT			10
#define MENU_PBAR_WIDTH				84
#define MENU_PBAR_SEGMENTS			12
#define MENU_PBAR_SEG_SIZE			7
#define MENU_PBAR_EMPTY_STRING		"         "
#define MENU_PBAR_BLANK_X_POS		16
#define MENU_BACK_X_POS				26
#define MENU_ABS_MAX_VALUE			10000
#define MENU_INFINITE_TEXT			"-INF-"
#define	MENU_NUM_OF_TIME_WHEELS		4
#define MENU_MINS_UNITS				3
#define MENU_MINS_TENS				2
#define MENU_HOURS_UNITS			1
#define MENU_HOURS_TENS				0
#define MENU_HOURS_X_POS_OFFSET		18
#define MENU_TIME_COLON				':'
#define MENU_VERTICAL_BAR_X_POS		81
#define MENU_VERTICAL_BAR_MAX_SIZE	40
#define MENU_VERTICAL_BAR_Y_TRIM	4
#define MENU_VERTICAL_BAR_WIDTH		2
#define MENU_MAX_LCD_LIST_LINES		8


extern guimenu_page_t *g_guimenu_page_def[];
extern bool Low_Battery_Flag;

// Local Static Objects / Variables
static Adafruit_PCD8544 display = Adafruit_PCD8544(DISPLAY_SCLK,  DISPLAY_DIN, DISPLAY_DCSEL, DISPLAY_CS, DISPLAY_RST);
static char str_text[15];
static uint16_t thumbwheel_multiplier[] =
{
	10000, 1000, 100, 10, 1
};
static uint8_t current_page_number = GUIMENU_NO_PAGE;
void (*p_get_time_fn)(guimenu_time_t *p_time);
void (*p_set_time_fn)(guimenu_time_t *p_time);


// Internal functions
static void get_string (char *str_output, uint8_t string_id);
static uint16_t draw_string (int16_t start_x, int16_t start_y, char *str_input_text, uint16_t fg_colour, uint16_t bg_colour, uint8_t size);
static uint8_t get_mid_x (uint8_t char_size, const char *str_message);
static void make_value_units_string (char str_value[], uint16_t current_value, uint8_t units);
static void display_page_banner (uint8_t page_number);
static void pad_string (char *str_text, uint8_t num_of_chars);
static void secs_to_hms (uint32_t time, guimenu_time_t *p_hms_time);
static void display_scrollbar (uint8_t page_number, uint8_t num_of_pages, uint8_t num_of_banner_lines, bool b_select_list);
static void display_lowbattery_banner (void);

static void list_selector_operation (uint8_t page_number, uint8_t *p_exit_key);
static bool list_selector_main (uint8_t page_number, uint8_t current_value, uint8_t *p_exit_key);
static void list_selector_control (uint8_t page_number, uint8_t current_value);
static void list_selector_display (uint8_t page_number, uint8_t current_value);

static void thumbwheel_selector_operation (uint8_t page_number, uint8_t *p_exit_key);
static void thumbwheel_selector_display (uint8_t page_number, uint16_t current_value);
static bool thumbwheel_selector_main (uint8_t page_number, uint16_t current_value, uint8_t *p_exit_key);
static void thumbwheel_selector_control (uint8_t page_number, uint16_t current_value);
static void display_tw_value (uint16_t current_value, uint8_t selected_wheel);
static void display_thumbwheel_digit (uint16_t x, uint16_t y, char character, bool b_selected);

static void thumbwheelu_selector_operation (uint8_t page_number, uint8_t *p_exit_key);
static void thumbwheelu_selector_display (uint8_t page_number, uint16_t current_value, uint8_t units);
static bool thumbwheelu_selector_main (uint8_t page_number, uint16_t current_value, uint8_t units, uint8_t *p_exit_key);
static void thumbwheelu_selector_control (uint8_t page_number, uint16_t current_value, uint8_t units);
static void display_twu_value (uint16_t current_value, uint8_t selected_wheel);
static void display_twu_units (uint8_t units, bool b_selected);
static void display_tw_sec_value (uint8_t units, uint16_t current_value);

static void time_selector_operation (uint8_t page_number, uint8_t *p_exit_key);
static bool time_selector_main (uint8_t page_number, uint16_t p_current_mins, uint8_t *p_exit_key);
static void time_selector_control (uint8_t page_number, uint16_t *p_current_mins);
static void time_selector_display (uint8_t page_number, uint16_t p_current_mins);
static void display_time_value (uint16_t current_mins, uint8_t selected_wheel);
static void increment_time (uint16_t *p_current_mins, uint8_t wheel_select);
static void decrement_time (uint16_t *p_current_mins, uint8_t wheel_select);

static void toggle_selector_operation (uint8_t page_number, uint8_t *p_exit_key);
static bool toggle_selector_main (uint8_t page_number, uint8_t current_value, uint8_t *p_exit_key);
static void toggle_selector_display (uint8_t page_number, uint8_t current_value);


void 
guimenu_initialise (uint8_t contrast, void (*pf_get_time)(guimenu_time_t *p_time), void (*pf_set_time)(guimenu_time_t *p_time))
{
	display.begin (contrast);
	display.clearDisplay();
	
	p_get_time_fn = pf_get_time;
	p_set_time_fn = pf_set_time;
}


void 
guimenu_clearpage (void)
{
	display.clearDisplay();
	display.display();
}


void 
guimenu_println(char *str_message)
{
	display.println(str_message);
}


static uint8_t
get_mid_x (uint8_t char_size, const char *str_message)
{
	uint16_t x = (LCDWIDTH >> 1);
	
	if (*str_message)
	{
		uint8_t num_of_chars = strlen (str_message);
		x -= (num_of_chars >> 1)
			 * ((char_size * STD_CHAR_WIDTH) + STD_CHAR_SPACING);
		// For odd number of chars, adjust
		if (num_of_chars & 0x01)
		{
			x -= STD_CHAR_WIDTH;
		}	
	}
	
	return x;
}


static char str_units_list[][3] = 
{
	"US",
	"MS",
	"S ",
	"M ",
	"H "
};

static void
make_value_units_string (char str_value[], uint16_t current_value, uint8_t units)
{
	sprintf (str_text, "%d %s", current_value, str_units_list[units]);
}


static void 
get_string (char *str_output, uint8_t string_id)
{
	strcpy_P (str_output, (PGM_P)pgm_read_word(&(g_guimenu_stringtable[string_id])));
}


static void
secs_to_hms (uint32_t time, guimenu_time_t *p_hms_time)
{
	uint32_t residual_time = time;
	
	p_hms_time->hours = (uint8_t)(residual_time / 3600UL);
	residual_time -= ((uint32_t)p_hms_time->hours * 3600UL);
	p_hms_time->mins = (uint8_t)(residual_time / 60UL);
	residual_time -= (uint32_t)p_hms_time->mins * 60UL;
	p_hms_time->secs = residual_time;
}


void
guimenu_displaypage (uint8_t page_number)
{
	unsigned char current_value_byte;
	uint16_t current_value_2byte;
	uint8_t units;	
	guimenu_time_t current_time;
	uint16_t fg_colour, bg_colour;

	current_page_number = page_number;

	if (page_number != GUIMENU_NO_PAGE)
	{
		display.clearDisplay();
	
		// Draw bitmap if there is one to draw
		if (g_guimenu_page_def[page_number]->bitmap)
		{
			display.loadBuffer(g_guimenu_page_def[page_number]->bitmap);
		}
	
		if (g_guimenu_page_def[page_number]->title_info->number_id)
		{
			// Draw the number
			get_string (str_text, g_guimenu_page_def[page_number]->title_info->number_id);
			int16_t start_x = get_mid_x (MENU_NUMBER_SIZE, str_text);
			draw_string (start_x, MENU_NUMBER_POS_Y, str_text, BLACK, WHITE, MENU_NUMBER_SIZE);	
		}
		
		if (g_guimenu_page_def[page_number]->title_info->text1_id)
		{
			// Draw 1st line of text
			get_string (str_text, g_guimenu_page_def[page_number]->title_info->text1_id);
			int16_t start_x = get_mid_x (MENU_TEXTLINE1_SIZE, str_text);
			if (g_guimenu_page_def[page_number]->title_info->b_invert_text)
			{
				fg_colour = WHITE;
				bg_colour = BLACK;
			}
			else
			{
				fg_colour = BLACK;
				bg_colour = WHITE;
			}
			
			draw_string (start_x, MENU_TEXTLINE1_POS_Y,
						 str_text,
						 fg_colour, bg_colour, 
						 MENU_TEXTLINE2_SIZE);
		}
			
		if (g_guimenu_page_def[page_number]->title_info->text2_id)
		{
			// Draw 2nd line of text
			get_string (str_text, g_guimenu_page_def[page_number]->title_info->text2_id);
			int16_t start_x = get_mid_x (MENU_TEXTLINE2_SIZE, str_text);
			if (g_guimenu_page_def[page_number]->title_info->b_invert_text)
			{
				fg_colour = WHITE;
				bg_colour = BLACK;
			}
			else
			{
				fg_colour = BLACK;
				bg_colour = WHITE;
			}
			
			draw_string (start_x, (MENU_TEXTLINE1_POS_Y + STD_CHAR_HEIGHT + STD_LINE_SPACING),
						 str_text,
						 fg_colour, bg_colour, 
						 MENU_TEXTLINE2_SIZE);
		}
		
		if (Low_Battery_Flag == false)
		{
			display_page_banner (page_number);
		}
		else
		{
			if (g_guimenu_page_def[page_number]->banner_info->text1_id)
			{
				display_lowbattery_banner ();
			}
		}
		
		if (g_guimenu_page_def[page_number]->button_text_id)
		{
			get_string (str_text, g_guimenu_page_def[page_number]->button_text_id);
			uint8_t start_x = get_mid_x (MENU_BUTTON_SIZE, str_text);
	
			draw_string (start_x, MENU_BUTTON_TEXT_POS_Y, 
						 str_text, 
						 GUIMENU_TEXT_WHITE, GUIMENU_TEXT_BLACK, MENU_BUTTON_SIZE);
		}
		
		if (g_guimenu_page_def[page_number]->b_more_settings)
		{
			get_string (str_text, GUIMENU_MORE_SETTINGS);
			draw_string (MENU_MORE_SETTINGS_POS_X, MENU_MORE_SETTINGS_POS_Y, 
						 str_text, 
						 BLACK, WHITE, MENU_MORE_SETTINGS_SIZE);
		}
			
		if (g_guimenu_page_def[page_number]->selector)
		{
			// Write out text labels
			get_string (str_text, g_guimenu_page_def[page_number]->selector->text1_id);
			uint8_t start_x = get_mid_x (MENU_SELECT_SIZE, str_text);
			draw_string (start_x, MENU_SELECTTEXT1_Y_POS, str_text, BLACK, WHITE, MENU_SELECT_SIZE);
			get_string (str_text, g_guimenu_page_def[page_number]->selector->text2_id);
			start_x = get_mid_x (MENU_SELECT_SIZE, str_text);
			draw_string (start_x, MENU_SELECTTEXT2_Y_POS, str_text, BLACK, WHITE, MENU_SELECT_SIZE);
				
			// Write out value
			switch (g_guimenu_page_def[page_number]->selector->select_type)
			{
				case list_select:
				case toggle_select:
					current_value_byte = EEPROM.read (g_guimenu_page_def[page_number]->selector->eeprom_address);
					get_string (str_text, g_guimenu_page_def[page_number]->selector->select_list[current_value_byte]);
					start_x = get_mid_x (MENU_SELECT_SIZE, str_text);
					draw_string (start_x, MENU_SELECT_Y_POS, str_text, GUIMENU_TEXT_WHITE, GUIMENU_TEXT_BLACK, MENU_SELECT_SIZE);		
				break;

				case thumbwheel_select:
					current_value_2byte = ((uint16_t)(EEPROM.read (g_guimenu_page_def[page_number]->selector->eeprom_address)) << 8)
											+ (uint16_t)EEPROM.read (g_guimenu_page_def[page_number]->selector->eeprom_address + 1);
											
					if (current_value_2byte >= GUIMENU_INFINITE_VALUE)
					{
						sprintf (str_text, "%s", MENU_INFINITE_TEXT);	
					}
					else
					{
						sprintf (str_text, "%d", current_value_2byte);
					}
					start_x = get_mid_x (MENU_SELECT_SIZE, str_text);
					draw_string (start_x, MENU_SELECT_Y_POS, str_text, GUIMENU_TEXT_WHITE, GUIMENU_TEXT_BLACK, MENU_SELECT_SIZE);	
				break;

				case thumbwheel_units_select:
					current_value_2byte = (EEPROM.read (g_guimenu_page_def[page_number]->selector->eeprom_address) << 8)
											+ EEPROM.read (g_guimenu_page_def[page_number]->selector->eeprom_address + 1);
					units = EEPROM.read (g_guimenu_page_def[page_number]->selector->eeprom_address + 2);
					make_value_units_string (str_text, current_value_2byte, units);
					start_x = get_mid_x (MENU_SELECT_SIZE, str_text);
					draw_string (start_x, MENU_SELECT_Y_POS, str_text, GUIMENU_TEXT_WHITE, GUIMENU_TEXT_BLACK, MENU_SELECT_SIZE);
				break;
				
				case time_select:
					if (g_guimenu_page_def[page_number]->selector->eeprom_address == EEPROM_NONE)
					{
						p_get_time_fn (&current_time);
					}
					else
					{
						current_time.hours = EEPROM.read (g_guimenu_page_def[page_number]->selector->eeprom_address);
						current_time.mins = EEPROM.read (g_guimenu_page_def[page_number]->selector->eeprom_address + 1);
					}
					sprintf (str_text, "%02d:%02d", current_time.hours, current_time.mins);
					start_x = get_mid_x (MENU_SELECT_SIZE, str_text);
					draw_string (start_x, MENU_SELECT_Y_POS, str_text, GUIMENU_TEXT_WHITE, GUIMENU_TEXT_BLACK, MENU_SELECT_SIZE);
				break;
			}
		}
			
		if (g_guimenu_page_def[page_number]->progressbar)
		{
			// Write out text labels if appropriate
			if (g_guimenu_page_def[page_number]->progressbar->text1_id)
			{
				get_string (str_text, g_guimenu_page_def[page_number]->progressbar->text1_id);
				draw_string (0, MENU_PBARTEXT1_Y_POS, str_text, BLACK, WHITE, MENU_SELECT_SIZE);
			}
			
			if (g_guimenu_page_def[page_number]->progressbar->text2_id)
			{
				get_string (str_text, g_guimenu_page_def[page_number]->progressbar->text2_id);
				draw_string (0, MENU_PBARTEXT2_Y_POS, str_text, BLACK, WHITE, MENU_SELECT_SIZE);
			}
				
			// Draw progress bar
			display.drawRect (0, MENU_PBAR_Y_POS, MENU_PBAR_WIDTH, MENU_PBAR_HEIGHT, BLACK);
				
			// Draw CANCEL button
			get_string (str_text, GUIMENU_CANCEL);
			draw_string (MENU_TW_CANCEL_POS_X, MENU_MORE_SETTINGS_POS_Y, str_text, 
						 WHITE, BLACK, MENU_TW_CANCEL_SIZE);
		}
		
		if (g_guimenu_page_def[page_number]->scrollbar)
		{
			uint8_t banner_lines = 0;
			
			if (g_guimenu_page_def[page_number]->banner_info->text2_id)
			{
				banner_lines = 2;
			}
			else if (g_guimenu_page_def[page_number]->banner_info->text1_id)
			{
				banner_lines = 1;
			}
			
			display_scrollbar (g_guimenu_page_def[page_number]->scrollbar->page, 
							   g_guimenu_page_def[page_number]->scrollbar->total_pages, 
							   banner_lines, false);	
			
			if (!g_guimenu_page_def[page_number]->title_info)
			{
				// Draw page number
				sprintf(str_text, "%d", g_guimenu_page_def[page_number]->scrollbar->page);
				uint16_t x_pos = LCDWIDTH - (strlen (str_text) * (STD_CHAR_WIDTH + STD_CHAR_SPACING));
				draw_string (x_pos, MENU_BANNER_TEXT1_POS_Y, str_text, WHITE, BLACK, MENU_SELECT_SIZE);
			}
		}
			
		display.display();
	}
}


void 
guimenu_updatepage (void)
{
	display.display();
}


void 
guimenu_setcontrast (int contrast)
{
	display.setContrast(contrast);	
}


void
guimenu_settextsize (uint8_t size)
{
	display.setTextSize(size);
}


void
guimenu_settextcolour (uint16_t colour)
{
	display.setTextColor(colour);
}


void 
guimenu_update (void)
{
	display.clearDisplay();
	display.setTextSize(1);
	display.setTextColor(BLACK);
	display.setCursor(0,0);
}


void 
guimenu_display_lowbattery_banner (void)
{
	if (g_guimenu_page_def[current_page_number]->banner_info->text1_id)
	{
		display_lowbattery_banner ();	
	}
}


void
guimenu_display_normalbattery_banner (void)
{
	guimenu_displaypage (current_page_number);
	
	//display_page_banner (current_page_number);
	//if (!g_guimenu_page_def[current_page_number]->banner_info->text2_id)
	//{
		//*str_text = NULL;
		//pad_string (str_text, STD_CHARS_PER_LINE);
		//draw_string (MENU_BANNER_TEXT2_POS_X, (MENU_BANNER_TEXT1_POS_Y + STD_CHAR_HEIGHT + STD_LINE_SPACING + 1), 
					 //str_text, 
					 //BLACK, WHITE, MENU_BANNER_SIZE);	
	//}	
	//display.display();
}


static void
display_lowbattery_banner (void)
{
	get_string (str_text, GUIMENU_LOW);
	pad_string (str_text, STD_CHARS_PER_LINE);
	draw_string (MENU_BANNER_TEXT1_POS_X, MENU_BANNER_TEXT1_POS_Y,
				 str_text,
				 GUIMENU_TEXT_WHITE, GUIMENU_TEXT_BLACK, MENU_BANNER_SIZE);
				 
	get_string (str_text, GUIMENU_BATTERY);
	pad_string (str_text, STD_CHARS_PER_LINE);
	draw_string (MENU_BANNER_TEXT2_POS_X, 
				 (MENU_BANNER_TEXT1_POS_Y + STD_CHAR_HEIGHT + STD_LINE_SPACING + 1),
				 str_text,
				 GUIMENU_TEXT_WHITE, GUIMENU_TEXT_BLACK, MENU_BANNER_SIZE);
	display.display();
}


static void pad_string (char *str_text, uint8_t num_of_chars)
{
	uint8_t num_string_chars = strlen (str_text);
	while (num_string_chars < num_of_chars)
	{
		str_text[num_string_chars++] = ' ';
	}
	str_text[num_string_chars] = '\0';
}

static void
display_page_banner (uint8_t page_number)
{
	if (g_guimenu_page_def[page_number]->banner_info->text1_id)
	{
		get_string (str_text, g_guimenu_page_def[page_number]->banner_info->text1_id);
		pad_string (str_text, STD_CHARS_PER_LINE);
		draw_string (MENU_BANNER_TEXT1_POS_X, MENU_BANNER_TEXT1_POS_Y, 
					 str_text, 
					 GUIMENU_TEXT_WHITE, GUIMENU_TEXT_BLACK, MENU_BANNER_SIZE);		
	}
		
	if (g_guimenu_page_def[page_number]->banner_info->text2_id)
	{
		get_string (str_text, g_guimenu_page_def[page_number]->banner_info->text2_id);
		pad_string (str_text, STD_CHARS_PER_LINE);
		draw_string (MENU_BANNER_TEXT2_POS_X, (MENU_BANNER_TEXT1_POS_Y + STD_CHAR_HEIGHT + STD_LINE_SPACING + 1), 
					 str_text, 
					 WHITE, BLACK, MENU_BANNER_SIZE);		
	}
}


static uint16_t
draw_string (int16_t start_x, int16_t start_y, char *str_text_input, uint16_t fg_colour, uint16_t bg_colour, uint8_t size)
{
	int16_t width = 0;

	if (*str_text_input)
	{
		int16_t char_xpos = start_x;
		int16_t char_ypos = start_y;
		for (uint8_t char_num = 0; (str_text_input[char_num] && (char_num < 15)); char_num++)
		{
			display.drawChar(char_xpos, char_ypos, str_text_input[char_num], fg_colour, bg_colour, size);
			char_xpos += (size * STD_CHAR_WIDTH) + STD_CHAR_SPACING;
		}
	
		width = char_xpos - start_x;
	
		if (fg_colour == WHITE)
		{
			display.drawRect((start_x -1), (start_y - 1), (width + 2), ((STD_CHAR_HEIGHT * size) + 3), BLACK);
		}
	}
	
	return width;
}


void
guimenu_selector (uint8_t page_number, uint8_t *p_exit_key)
{
	switch (g_guimenu_page_def[page_number]->selector->select_type)
	{
		case list_select:
			list_selector_operation (page_number, p_exit_key);
		break;
		
		case thumbwheel_select:
			thumbwheel_selector_operation (page_number, p_exit_key);
		break;

		case thumbwheel_units_select:
			thumbwheelu_selector_operation (page_number, p_exit_key);
		break;
		
		case time_select:
			time_selector_operation (page_number, p_exit_key);
		break;
		
		case toggle_select:
			toggle_selector_operation(page_number, p_exit_key);
		break;
		
		default:
		break;		
	}
}


static void
list_selector_display (uint8_t page_number, uint8_t current_value)
{
	uint8_t first_list_string_num = 0;
	uint8_t last_list_string_num;
	
	if (current_value > (MENU_MAX_LCD_LIST_LINES - 1))
	{
		first_list_string_num = current_value - MENU_MAX_LCD_LIST_LINES + 1;	
	}
	
	if ((g_guimenu_page_def[page_number]->selector->list_size - first_list_string_num) > MENU_MAX_LCD_LIST_LINES)
	{
		last_list_string_num = first_list_string_num + MENU_MAX_LCD_LIST_LINES;	
	}
	else
	{
		last_list_string_num = g_guimenu_page_def[page_number]->selector->list_size;
	}
	
	for (uint8_t list_string_num = first_list_string_num; list_string_num < last_list_string_num; list_string_num++)
	{
		get_string (str_text, g_guimenu_page_def[page_number]->selector->select_list[list_string_num]);
		if (list_string_num != current_value)
		{
			draw_string (1, (list_string_num - first_list_string_num) * (STD_CHAR_HEIGHT + STD_CHAR_SPACING) + 1,
						 str_text, BLACK, WHITE, MENU_SELECT_SIZE);
		}
	}
	
	get_string (str_text, g_guimenu_page_def[page_number]->selector->select_list[current_value]);
	draw_string (1, (current_value - first_list_string_num) * (STD_CHAR_HEIGHT + STD_CHAR_SPACING) + 1,
				 str_text, WHITE, BLACK, MENU_SELECT_SIZE);
	
	if (g_guimenu_page_def[page_number]->selector->list_size > MENU_MAX_LCD_LIST_LINES)
	{
		display_scrollbar (current_value, 
						   g_guimenu_page_def[page_number]->selector->list_size, 0, true);
	}
}


static void
list_selector_operation (uint8_t page_number, uint8_t *p_exit_key)
{
	bool b_selector_end = false;

	while (!b_selector_end)
	{
		uint8_t current_value = EEPROM.read (g_guimenu_page_def[page_number]->selector->eeprom_address);
		b_selector_end = list_selector_main (page_number, current_value, p_exit_key);
		if (!b_selector_end)
		{
			list_selector_control (page_number, current_value);
			guimenu_displaypage (page_number);
		}
	}
}


static bool
list_selector_main (uint8_t page_number, uint8_t current_value, uint8_t *p_exit_key)
{
	bool b_key_response = false;
	bool b_selector_end = false;

	while (!b_key_response)
	{
		uint8_t key_input = GetButton();
		switch (key_input)
		{
			case KEY_SELECT:
				display.clearDisplay();
				list_selector_display (page_number, current_value);
				display.display();
				b_key_response = true;
			break;
				
			case KEY_PREV:
			case KEY_DOWN:
				*p_exit_key = key_input;
				b_key_response = true;
				b_selector_end = true;
			break;
		}
	}

	return b_selector_end;
}


static void
list_selector_control (uint8_t page_number, uint8_t current_value)
{
	bool b_control_end = false;
	uint8_t new_value = current_value;
	uint8_t original_value = current_value;

	while (!b_control_end)
	{
		uint8_t key_input = GetButton();
		
		switch (key_input)
		{
			case KEY_DOWN:
				if (new_value < (g_guimenu_page_def[page_number]->selector->list_size - 1))
				{
					new_value++;
					display.clearDisplay ();
					list_selector_display (page_number, new_value);
					current_value = new_value;
					display.display();
				}
			break;
		
			case KEY_PREV:
				if (new_value)
				{
					new_value--;
					display.clearDisplay ();
					list_selector_display (page_number, new_value);
					current_value = new_value;
					display.display();
				}
			break;
		
			case KEY_SELECT:
				b_control_end = true;
			break;

			default:
			break;
		}
	}
	
	if (new_value != original_value)
	{
		EEPROM.write (g_guimenu_page_def[page_number]->selector->eeprom_address, new_value);
	}
}


static void
display_thumbwheel_digit (uint16_t x, uint16_t y, char character, bool b_selected)
{
	uint16_t fg_colour, bg_colour;
		
	display.drawChar ((x + 2), (y + STD_CHAR_HEIGHT + 5), '\x01', BLACK, WHITE, 1);
	display.drawChar ((x + 2), (y - STD_CHAR_HEIGHT - 1), '\x02', BLACK, WHITE, 1);
	
	if (b_selected)
	{
		display.fillRect (x,y, MENU_TW_BOX_WIDTH, MENU_TW_BOX_HEIGHT, BLACK);
		fg_colour = WHITE;
		bg_colour = BLACK;
	}
	else
	{
		display.drawRect (x,y, MENU_TW_BOX_WIDTH, MENU_TW_BOX_HEIGHT, BLACK);
		display.fillRect ((x + 1),(y + 1), (MENU_TW_BOX_WIDTH - 2), (MENU_TW_BOX_HEIGHT - 2), WHITE);
		fg_colour = BLACK;
		bg_colour = WHITE;
	}
	
	display.drawChar ((x + 2), (y + 2), character, fg_colour, bg_colour, 1);	
}


static void
thumbwheel_selector_operation (uint8_t page_number, uint8_t *p_exit_key)
{
	bool b_selector_end = false;
	uint16_t current_value;

	while (!b_selector_end)
	{
		current_value = (EEPROM.read (g_guimenu_page_def[page_number]->selector->eeprom_address) << 8) 
						 + EEPROM.read (g_guimenu_page_def[page_number]->selector->eeprom_address + 1);
		
		b_selector_end = thumbwheel_selector_main (page_number, current_value, p_exit_key);
		if (!b_selector_end)
		{
			thumbwheel_selector_control (page_number, current_value);
			guimenu_displaypage (page_number);
		}
	}
}


static bool 
thumbwheel_selector_main (uint8_t page_number, uint16_t current_value, uint8_t *p_exit_key)
{
	bool b_key_response = false;
	bool b_selector_end = false;
	uint8_t key_input;

	while (!b_key_response)
	{
		key_input = GetButton();
		switch (key_input)
		{
			case KEY_SELECT:
				display.clearDisplay();
				thumbwheel_selector_display (page_number, current_value);
				b_key_response = true;
			break;
				
			case KEY_PREV:
			case KEY_DOWN:
				*p_exit_key = key_input;
				b_key_response = true;
				b_selector_end = true;
			break;
		}
	}

	return b_selector_end;
}


static void 
thumbwheel_selector_control (uint8_t page_number, uint16_t current_value)
{
	bool b_control_end = false;
	uint16_t original_value = current_value;
	uint8_t wheel_select = MENU_NUM_OF_TW - 1;
	bool b_cancelled = false;
	uint16_t new_value = current_value;

	while (!b_control_end)
	{
		uint8_t key_input = GetButton();
		
		switch (key_input)
		{
			case KEY_PLUS:
				if ((new_value < GUIMENU_INFINITE_VALUE) && (wheel_select < (MENU_NUM_OF_TW - 1)))
				{
					wheel_select++;
					display_tw_value (new_value, wheel_select);
					display.display();
				}
			break;
			
			case KEY_MINUS:
				if ((new_value < GUIMENU_INFINITE_VALUE) && wheel_select)
				{
					wheel_select--;
					display_tw_value (new_value, wheel_select);
					display.display();
				}
				else
				{
					b_cancelled = true;
					b_control_end = true;
				}
			break;
			
			case KEY_PREV:
				new_value = new_value + thumbwheel_multiplier[wheel_select];
				if (new_value < GUIMENU_INFINITE_VALUE)
				{
					display_tw_value (new_value, wheel_select);
					display.display();
				}
				else
				{
					new_value = GUIMENU_INFINITE_VALUE;
					display_tw_value (new_value, wheel_select);
					display.display();
				}
			break;
			
			case KEY_DOWN:
				if (new_value >= GUIMENU_INFINITE_VALUE)
				{
					new_value = GUIMENU_INFINITE_VALUE - 1;
					display_tw_value (new_value, wheel_select);
					display.display();
				}
				else if (new_value >= thumbwheel_multiplier[wheel_select])
				{
					new_value -= thumbwheel_multiplier[wheel_select];
					display_tw_value (new_value, wheel_select);
					display.display();
				}
			break;

			case KEY_SELECT:
				b_control_end = true;
			break;

			default:
			break;
		}
	}
	
	if (!b_cancelled)
	{
		if (new_value != original_value)
		{
			if (new_value > g_guimenu_page_def[page_number]->selector->max_value)
			{
				new_value = g_guimenu_page_def[page_number]->selector->max_value;
			}
			else if (new_value < g_guimenu_page_def[page_number]->selector->min_value)
			{
				new_value = g_guimenu_page_def[page_number]->selector->min_value;
			}
			
			EEPROM.write (g_guimenu_page_def[page_number]->selector->eeprom_address, (new_value >> 8));
			EEPROM.write ((g_guimenu_page_def[page_number]->selector->eeprom_address + 1), new_value & 0xff);
		}	
	}
}


static void
display_tw_value (uint16_t current_value, uint8_t selected_wheel)
{
	uint16_t fg_colour;
	bool b_infinite = false;
	
	if (current_value >= GUIMENU_INFINITE_VALUE)
	{
		sprintf (str_text, "%s", MENU_INFINITE_TEXT);	
		b_infinite = true;
	}
	else
	{
		sprintf (str_text, "%05d", current_value);
	}
	
	// Draw each wheel & put number in box
	for (uint8_t wheel_number = 0; wheel_number < MENU_NUM_OF_TW; wheel_number++)
	{
		if (!b_infinite && (wheel_number == selected_wheel))
		{
			fg_colour = WHITE;
		}
		else
		{
			fg_colour = BLACK;
		}
		
		display_thumbwheel_digit ((MENU_TW_X_POS_OFFSET + (wheel_number * (MENU_TW_BOX_WIDTH + STD_CHAR_SPACING))),
								  MENU_TW_Y_POS,
								  str_text[wheel_number], 
								  (fg_colour == WHITE));
	}
}

static void
thumbwheel_selector_display (uint8_t page_number, uint16_t current_value)
{
	sprintf (str_text, "%05d", current_value);
	
	// Draw banner text
	display_page_banner (page_number);
	
	// Draw page number
	if (g_guimenu_page_def[page_number]->scrollbar)
	{
		sprintf(str_text, "%d", g_guimenu_page_def[page_number]->scrollbar->page);
		uint16_t x_pos = LCDWIDTH - (strlen (str_text) * (STD_CHAR_WIDTH + STD_CHAR_SPACING));
		draw_string (x_pos, MENU_BANNER_TEXT1_POS_Y, str_text, WHITE, BLACK, MENU_SELECT_SIZE);
	}
	
	display_tw_value (current_value, (MENU_NUM_OF_TW - 1));
	
	// Draw CANCEL button
	get_string (str_text, GUIMENU_CANCEL);
	draw_string (MENU_TW_CANCEL_POS_X, MENU_MORE_SETTINGS_POS_Y, str_text, 
				 WHITE, BLACK, MENU_TW_CANCEL_SIZE);

	display.display();
}


static void
thumbwheelu_selector_operation (uint8_t page_number, uint8_t *p_exit_key)
{
	bool b_selector_end = false;

	while (!b_selector_end)
	{
		uint16_t current_value = (EEPROM.read (g_guimenu_page_def[page_number]->selector->eeprom_address) << 8) 
								  + EEPROM.read (g_guimenu_page_def[page_number]->selector->eeprom_address + 1);
		uint8_t units = EEPROM.read (g_guimenu_page_def[page_number]->selector->eeprom_address + 2);
		
		b_selector_end = thumbwheelu_selector_main (page_number, current_value, units, p_exit_key);
		if (!b_selector_end)
		{
			thumbwheelu_selector_control (page_number, current_value, units);
			guimenu_displaypage (page_number);
		}
	}
}


static bool 
thumbwheelu_selector_main (uint8_t page_number, uint16_t current_value, uint8_t units, uint8_t *p_exit_key)
{
	bool b_key_response = false;
	bool b_selector_end = false;

	while (!b_key_response)
	{
		uint8_t key_input = GetButton();
		switch (key_input)
		{
			case KEY_SELECT:
				display.clearDisplay();
				thumbwheelu_selector_display (page_number, current_value, units);
				b_key_response = true;
			break;
				
			case KEY_MINUS:	
			case KEY_PREV:
			case KEY_DOWN:
				*p_exit_key = key_input;
				b_key_response = true;
				b_selector_end = true;
			break;
		}
	}

	return b_selector_end;
}

static void
display_tw_sec_value (uint8_t units, uint16_t current_value)
{	
	//  If units are milliseconds - can display format as 1.001S
	if (units == GUIMENU_UNITS_MS)
	{
		uint8_t seconds = (current_value / 1000);
		sprintf (str_text, "%1d.%03dS", seconds, (current_value % 1000));
	}
	else
	{
		sprintf (str_text, "      ");	
	}
	
	draw_string (0, MENU_MORE_SETTINGS_POS_Y, str_text,	BLACK, WHITE, 1);
}


static void 
thumbwheelu_selector_control (uint8_t page_number, uint16_t current_value, uint8_t units)
{
	bool b_control_end = false;
	uint16_t original_value = current_value;
	uint8_t wheel_select = MENU_NUM_OF_TW - 1;
	bool b_cancelled = false;
	uint8_t orginal_units = units;
	uint16_t new_value = current_value;
	uint8_t page_num = page_number;		// Shouldn't have to do this - bug in GCC?
	
	sprintf (str_text, "%05d", current_value);

	while (!b_control_end)
	{
		uint8_t key_input = GetButton();
		
		switch (key_input)
		{
			case KEY_PLUS:
				if (wheel_select < MENU_NUM_OF_TW)
				{
					wheel_select++;
					display_twu_value (current_value, wheel_select);
					display_twu_units (units, (wheel_select == MENU_NUM_OF_TW));
					display_tw_sec_value (units, current_value);
					display.display();
				}
			break;
			
			case KEY_MINUS:
				if (wheel_select)
				{
					wheel_select--;
					display_twu_value (current_value, wheel_select);
					display_twu_units (units, false);
					display_tw_sec_value (units, current_value);
					display.display();
				}
				else
				{
					b_cancelled = true;
					b_control_end = true;
				}
			break;
			
			case KEY_PREV:
				if (wheel_select == MENU_NUM_OF_TW)
				{
					if (units < g_guimenu_page_def[page_num]->selector->high_units)
					{
						units++;
						
						display_twu_units (units, true);
						display_tw_sec_value (units, current_value);
						display.display();
					}
				}
				else 
				{
					new_value = current_value + thumbwheel_multiplier[wheel_select];
					if (new_value <= MENU_ABS_MAX_VALUE)
					{
						current_value = new_value;
						display_twu_value (current_value, wheel_select);
						display_tw_sec_value (units, current_value);
						display.display();
					}
				}
			break;
			
			case KEY_DOWN:
				if (wheel_select == MENU_NUM_OF_TW)
				{
					if (units > g_guimenu_page_def[page_number]->selector->low_units)
					{
						units--;
						display_twu_units (units, true);
						display_tw_sec_value (units, current_value);
						display.display();
					}
				}
				else if (current_value >= thumbwheel_multiplier[wheel_select])
				{
					current_value -= thumbwheel_multiplier[wheel_select];
					display_twu_value (current_value, wheel_select);
					display_tw_sec_value (units, current_value);
					display.display();
				}
			break;

			case KEY_SELECT:
				b_control_end = true;
			break;

			default:
			break;
		}
	}
	
	if (!b_cancelled)
	{
		// New value entered, so save in EEPROM
		if ((current_value != original_value) || (units != orginal_units))
		{
			if ((units == g_guimenu_page_def[page_number]->selector->high_units) 
			    && (current_value > g_guimenu_page_def[page_number]->selector->max_value))
			{
				current_value = g_guimenu_page_def[page_number]->selector->max_value;
			}
			else if ((units == g_guimenu_page_def[page_number]->selector->low_units) 
					 && (current_value < g_guimenu_page_def[page_number]->selector->min_value))
			{
				current_value = g_guimenu_page_def[page_number]->selector->min_value;
			}
			
			EEPROM.write (g_guimenu_page_def[page_number]->selector->eeprom_address, (current_value >> 8));
			EEPROM.write ((g_guimenu_page_def[page_number]->selector->eeprom_address + 1), current_value & 0xff);
			EEPROM.write ((g_guimenu_page_def[page_number]->selector->eeprom_address + 2), units);
		}	
	}
}


static void
display_twu_value (uint16_t current_value, uint8_t selected_wheel)
{
	uint16_t fg_colour;
	
	sprintf (str_text, "%05d", current_value);
	
	// Draw each wheel & put number in box
	for (uint8_t wheel_number = 0; wheel_number < MENU_NUM_OF_TW; wheel_number++)
	{
		if (wheel_number == selected_wheel)
		{
			fg_colour = WHITE;
		}
		else
		{
			fg_colour = BLACK;
		}
		
		display_thumbwheel_digit ((MENU_TWU_X_POS_OFFSET + (wheel_number * (MENU_TW_BOX_WIDTH + STD_CHAR_SPACING))),
								  MENU_TW_Y_POS,
								  str_text[wheel_number],
								  (fg_colour == WHITE));
	}
}


static void
display_twu_units (uint8_t units, bool b_selected)
{
	char str_units[3];
	uint16_t fg_colour, bg_colour;
	
	sprintf (str_units, "%s", str_units_list[units]);
		  
	display.drawChar ((MENU_TWU_UNITS_X_POS_OFFSET + 2), 
					  (MENU_TW_Y_POS + STD_CHAR_HEIGHT + 5), 
					  '\x01', BLACK, WHITE, 1);
	
	display.drawChar ((MENU_TWU_UNITS_X_POS_OFFSET + 2), 
					  (MENU_TW_Y_POS - STD_CHAR_HEIGHT - 1), 
					  '\x02', BLACK, WHITE, 1);
					  
	if (b_selected)
	{
		fg_colour = WHITE;
		bg_colour = BLACK;
		display.fillRect (MENU_TWU_UNITS_X_POS_OFFSET,
						  MENU_TW_Y_POS,
						  MENU_TWU_BOX_WIDTH, MENU_TW_BOX_HEIGHT,
						  BLACK);
	}
	else
	{
		fg_colour = BLACK;
		bg_colour = WHITE;
		display.fillRect ((MENU_TWU_UNITS_X_POS_OFFSET + 1),
						  (MENU_TW_Y_POS + 1),
						  (MENU_TWU_BOX_WIDTH - 2), 
						  (MENU_TW_BOX_HEIGHT - 2),
						  WHITE);
		display.drawRect (MENU_TWU_UNITS_X_POS_OFFSET,
						  MENU_TW_Y_POS,
						  MENU_TWU_BOX_WIDTH, MENU_TW_BOX_HEIGHT,
						  BLACK);
	}

	draw_string (MENU_TWU_UNITS_X_POS_OFFSET + 2,
				 MENU_TW_Y_POS + 2, str_units, fg_colour, bg_colour, 1);
				 
}



static void
thumbwheelu_selector_display (uint8_t page_number, uint16_t current_value, uint8_t units)
{
	char str_units[3];
	
	sprintf (str_text, "%05d", current_value);
	sprintf (str_units, "%s", str_units_list[units]);
	
	// Draw banner text
	display_page_banner (page_number);
	
	// Draw page number
	if (g_guimenu_page_def[page_number]->scrollbar)
	{
		sprintf(str_text, "%d", g_guimenu_page_def[page_number]->scrollbar->page);
		uint16_t x_pos = LCDWIDTH - (strlen (str_text) * (STD_CHAR_WIDTH + STD_CHAR_SPACING));
		draw_string (x_pos, MENU_BANNER_TEXT1_POS_Y, str_text, WHITE, BLACK, MENU_SELECT_SIZE);
	}
	
	display_twu_value (current_value, (MENU_NUM_OF_TW - 1));
	display_twu_units (units, false);
	display_tw_sec_value (units, current_value);
		
	// Draw CANCEL button
	get_string (str_text, GUIMENU_CANCEL);
	draw_string (MENU_TWU_CANCEL_POS_X, MENU_MORE_SETTINGS_POS_Y, str_text, 
				 WHITE, BLACK, MENU_TW_CANCEL_SIZE);

	display.display();
}

static float pbar_size;
static uint8_t pbar_page_number;
static uint32_t pbar_start_time;
static uint8_t pbar_num_of_shots;
static uint8_t pbar_units;

void guimenu_progressbar_start (uint8_t page_number, uint32_t start_time, uint8_t units, uint8_t num_of_shots)
{
	uint8_t x_pos;
	uint32_t disp_time = 0;
	
	pbar_size = (float)LCDWIDTH / (float)start_time;
	pbar_page_number = page_number;
	pbar_num_of_shots = num_of_shots;
	pbar_units = units;
	pbar_start_time = start_time;

	display.fillRect (1, MENU_PBAR_Y_POS + 1, (MENU_PBAR_WIDTH - 2), (MENU_PBAR_HEIGHT - 2), WHITE);

	switch (units)
	{
		case GUIMENU_UNITS_S:
			disp_time = start_time / 1000UL;
		break;
		
		case GUIMENU_UNITS_M:
			disp_time = start_time / 60000UL;
		break;	
		
		case GUIMENU_UNITS_H:
			disp_time = start_time / 3600000UL;
		break;
	}
	
	if ((g_guimenu_page_def[page_number]->progressbar->text1_id)
		|| (g_guimenu_page_def[page_number]->progressbar->text2_id))
	{
		make_value_units_string (str_text, disp_time, units);
		x_pos = LCDWIDTH - (strlen (str_text) * (STD_CHAR_SPACING + STD_CHAR_WIDTH));
		draw_string (x_pos, MENU_PBARTEXT2_Y_POS,
						str_text,
						BLACK,
						WHITE,
						1);
	}
	else
	{		 
		sprintf (str_text, "1/%d", num_of_shots);
		x_pos = get_mid_x (MENU_SELECT_SIZE, str_text);
		draw_string (x_pos, MENU_PBARTEXT1_Y_POS, str_text, BLACK, WHITE, MENU_SELECT_SIZE);
		
		if (disp_time)
		{
			guimenu_time_t hms_time;
			secs_to_hms (disp_time, &hms_time);
			sprintf (str_text, "%02d:%02d:%02d", hms_time.hours, hms_time.mins, hms_time.secs);
			x_pos = get_mid_x (MENU_SELECT_SIZE, str_text);
			draw_string (x_pos, MENU_PBARTEXT2_Y_POS, str_text, BLACK, WHITE, MENU_SELECT_SIZE);
		}
		else
		{
			strcpy (str_text, " 00:00:00 ");
			x_pos = get_mid_x (MENU_SELECT_SIZE, str_text);
			draw_string (x_pos, MENU_PBARTEXT2_Y_POS, str_text, BLACK, WHITE, MENU_SELECT_SIZE);
			display.fillRect (1, MENU_PBAR_Y_POS + 1, (MENU_PBAR_WIDTH - 2), (MENU_PBAR_HEIGHT - 2), BLACK);
		}
	}
				 
	display.display ();
}

void guimenu_progressbar_update (uint32_t time_left, uint8_t shot_num)
{	
	uint8_t x_pos;
	uint32_t disp_time = 0;
	
	switch (pbar_units)
	{
		case GUIMENU_UNITS_S:
		disp_time = time_left / 1000UL;
		break;
		
		case GUIMENU_UNITS_M:
		disp_time = time_left / 60000UL;
		break;
		
		case GUIMENU_UNITS_H:
		disp_time = time_left / 3600000UL;
		break;
	}
	
	disp_time++;
	
	if (time_left)
	{
		sprintf (str_text, MENU_PBAR_EMPTY_STRING);
		draw_string (MENU_PBAR_BLANK_X_POS, MENU_PBARTEXT2_Y_POS,
		str_text,
		BLACK,
		WHITE,
		1);
		
		display.fillRect (0,
		MENU_PBAR_Y_POS,
		(uint16_t)(pbar_size * (float)(pbar_start_time - time_left)),
		MENU_PBAR_HEIGHT,
		BLACK);
	}
	else
	{
		display.fillRect (1, MENU_PBAR_Y_POS + 1, (MENU_PBAR_WIDTH - 2), (MENU_PBAR_HEIGHT - 2), BLACK);
	}
				 
	if (g_guimenu_page_def[pbar_page_number]->progressbar->text1_id)
	{
		get_string (str_text, g_guimenu_page_def[pbar_page_number]->progressbar->text1_id);
		draw_string (0, MENU_PBARTEXT1_Y_POS, str_text, BLACK, WHITE, MENU_SELECT_SIZE);
	}
	
	if (g_guimenu_page_def[pbar_page_number]->progressbar->text2_id)
	{
		get_string (str_text, g_guimenu_page_def[pbar_page_number]->progressbar->text2_id);
		draw_string (0, MENU_PBARTEXT2_Y_POS, str_text, BLACK, WHITE, MENU_SELECT_SIZE);
	}
		
	
	
	if ((g_guimenu_page_def[pbar_page_number]->progressbar->text1_id)
	    || (g_guimenu_page_def[pbar_page_number]->progressbar->text2_id))
	{
		make_value_units_string (str_text, disp_time, pbar_units);
		x_pos = LCDWIDTH - (strlen (str_text) * (STD_CHAR_SPACING + STD_CHAR_WIDTH));
		draw_string (x_pos, MENU_PBARTEXT2_Y_POS, str_text, BLACK, WHITE, 1);
	}
	
	if (shot_num)
	{
		sprintf (str_text, "%d/%d", shot_num, pbar_num_of_shots);
		x_pos = get_mid_x (MENU_SELECT_SIZE, str_text);
		draw_string (x_pos, MENU_PBARTEXT1_Y_POS, str_text, BLACK, WHITE, MENU_SELECT_SIZE);
		
		if (time_left)
		{
			guimenu_time_t hms_time;
			secs_to_hms (disp_time, &hms_time);
			sprintf (str_text, "%02d:%02d:%02d", hms_time.hours, hms_time.mins, hms_time.secs);
			x_pos = get_mid_x (MENU_SELECT_SIZE, str_text);
			draw_string (x_pos, MENU_PBARTEXT2_Y_POS, str_text, BLACK, WHITE, MENU_SELECT_SIZE);
		}
		else
		{
			sprintf (str_text, " 00:00:00 ");
			x_pos = get_mid_x (MENU_SELECT_SIZE, str_text);
			draw_string (x_pos, MENU_PBARTEXT2_Y_POS, str_text, BLACK, WHITE, MENU_SELECT_SIZE);
		}
	}

	
	
	display.display ();	
}


void guimenu_operation_complete (uint8_t page_number, uint8_t *exit_key)
{
	display.clearDisplay();
	display_page_banner (page_number);	
	
	get_string (str_text, GUIMENU_DONE);
	uint8_t start_x = get_mid_x (MENU_BUTTON_SIZE, str_text);
	draw_string (start_x, MENU_BUTTON_TEXT_POS_Y, str_text, 
				 BLACK, WHITE, MENU_BUTTON_SIZE);
	display.display();
				 
	get_string(str_text, GUIMENU_MENUBACK);
	start_x = get_mid_x (MENU_BUTTON_SIZE, str_text);
	
	for (uint8_t text_flashes = 0; text_flashes < 3; text_flashes ++)
	{
		draw_string (MENU_BACK_X_POS, MENU_MORE_SETTINGS_POS_Y, str_text, 
					 BLACK, WHITE, 1);	
		display.display();
		delay (250);	
		draw_string (MENU_BACK_X_POS, MENU_MORE_SETTINGS_POS_Y, str_text, 
					 WHITE, BLACK, 1);
		display.display();
		delay (250);
	}

	draw_string (MENU_BACK_X_POS, MENU_MORE_SETTINGS_POS_Y, str_text, 
				 BLACK, WHITE, 1);
	display.display();
				 
	do 
	{
		*exit_key = GetButton();
	} 
	while (*exit_key != KEY_MINUS);
}


static void
time_selector_operation (uint8_t page_number, uint8_t *p_exit_key)
{
	bool b_selector_end = false;
	guimenu_time_t current_time;
	uint16_t current_mins;
	
	if (g_guimenu_page_def[page_number]->selector->eeprom_address == EEPROM_NONE)
	{
		p_get_time_fn (&current_time);
	}
	else
	{
		current_time.hours = EEPROM.read (g_guimenu_page_def[page_number]->selector->eeprom_address);
		current_time.mins = EEPROM.read (g_guimenu_page_def[page_number]->selector->eeprom_address + 1);
	}

	current_mins = current_time.mins + (current_time.hours * 60);

	while (!b_selector_end)
	{
		b_selector_end = time_selector_main (page_number, current_mins, p_exit_key);
		if (!b_selector_end)
		{
			time_selector_control (page_number, &current_mins);
			guimenu_displaypage (page_number);
		}
	}
}


static bool
time_selector_main (uint8_t page_number, uint16_t current_mins, uint8_t *p_exit_key)
{
	bool b_key_response = false;
	bool b_selector_end = false;
	uint8_t key_input;

	while (!b_key_response)
	{
		key_input = GetButton();
		switch (key_input)
		{
			case KEY_SELECT:
				display.clearDisplay();
				time_selector_display (page_number, current_mins);
				b_key_response = true;
			break;
			
			case KEY_PREV:
			case KEY_DOWN:
				*p_exit_key = key_input;
				b_key_response = true;
				b_selector_end = true;
			break;
		}
	}

	return b_selector_end;
}


static void
time_selector_control (uint8_t page_number, uint16_t *p_current_mins)
{
	bool b_control_end = false;
	uint16_t original_value = *p_current_mins;
	uint8_t wheel_select = MENU_NUM_OF_TIME_WHEELS - 1;
	bool b_cancelled = false;

	while (!b_control_end)
	{
		uint8_t key_input = GetButton();
		
		switch (key_input)
		{
			case KEY_PLUS:
			if (wheel_select < (MENU_NUM_OF_TIME_WHEELS - 1))
			{
				wheel_select++;
				display_time_value (*p_current_mins, wheel_select);
				display.display();
			}
			break;
			
			case KEY_MINUS:
			if (wheel_select)
			{
				wheel_select--;
				display_time_value (*p_current_mins, wheel_select);
				display.display();
			}
			else
			{
				b_cancelled = true;
				b_control_end = true;
			}
			break;
			
			case KEY_PREV:
				increment_time (p_current_mins, wheel_select);
				display_time_value (*p_current_mins, wheel_select);
				display.display();
			break;
			
			case KEY_DOWN:
				decrement_time (p_current_mins, wheel_select);
				display_time_value (*p_current_mins, wheel_select);
				display.display();
			break;

			case KEY_SELECT:
				b_control_end = true;
			break;

			default:
			break;
		}
	}
	
	if (!b_cancelled)
	{
		if (*p_current_mins != original_value)
		{
			uint8_t hours = *p_current_mins / 60;
			uint8_t mins = *p_current_mins - (hours * 60);
			if (g_guimenu_page_def[page_number]->selector->eeprom_address != EEPROM_NONE)
			{
				EEPROM.write (g_guimenu_page_def[page_number]->selector->eeprom_address, hours);
				EEPROM.write ((g_guimenu_page_def[page_number]->selector->eeprom_address + 1), mins);
			}
			else
			{
				guimenu_time_t new_time;
				new_time.hours = *p_current_mins / 60;
				new_time.mins = *p_current_mins - (new_time.hours * 60);
				p_set_time_fn (&new_time);
			}
		}
	}
}


static void
display_time_value (uint16_t current_mins, uint8_t selected_wheel)
{
	uint8_t hours = current_mins / 60;
	uint8_t mins = current_mins - (hours * 60);
	uint16_t x_position = MENU_HOURS_X_POS_OFFSET;
	uint16_t fg_colour;
		
	sprintf (str_text, "%02d%02d", hours, mins);
	
	// Draw each wheel & put number in box (Hours only)
	for (uint8_t wheel_number = 0; wheel_number < 2; wheel_number++)
	{
		if (wheel_number == selected_wheel)
		{
			fg_colour = WHITE;
		}
		else
		{
			fg_colour = BLACK;
		}
		
		display_thumbwheel_digit (x_position,
								  MENU_TW_Y_POS,
								  str_text[wheel_number],
								  (fg_colour == WHITE));
		
		x_position += (MENU_TW_BOX_WIDTH + STD_CHAR_SPACING);
	}
	
	// Draw time separator
	display.drawChar (x_position, MENU_TW_Y_POS, MENU_TIME_COLON, BLACK, WHITE, 2);
	x_position += (MENU_TW_BOX_WIDTH + STD_CHAR_SPACING);
	
	// Draw each wheel & put number in box (Mins only)
	for (uint8_t wheel_number = 2; wheel_number < MENU_NUM_OF_TIME_WHEELS; wheel_number++)
	{
		if (wheel_number == selected_wheel)
		{
			fg_colour = WHITE;
		}
		else
		{
			fg_colour = BLACK;
		}
		
		display_thumbwheel_digit (x_position,
								  MENU_TW_Y_POS,
								  str_text[wheel_number],
								  (fg_colour == WHITE));
		
		x_position += (MENU_TW_BOX_WIDTH + STD_CHAR_SPACING);
	}
}


static void
time_selector_display (uint8_t page_number, uint16_t current_mins)
{
	// Draw banner text
	display_page_banner (page_number);
	
	// Draw page number
	if (g_guimenu_page_def[page_number]->scrollbar)
	{
		sprintf(str_text, "%d", g_guimenu_page_def[page_number]->scrollbar->page);
		uint16_t x_pos = LCDWIDTH - (strlen (str_text) * (STD_CHAR_WIDTH + STD_CHAR_SPACING));
		draw_string (x_pos, MENU_BANNER_TEXT1_POS_Y, str_text, WHITE, BLACK, MENU_SELECT_SIZE);
	}
	
	display_time_value (current_mins, (MENU_NUM_OF_TIME_WHEELS - 1));
	
	// Draw CANCEL button
	get_string (str_text, GUIMENU_CANCEL);
	draw_string (MENU_TW_CANCEL_POS_X, MENU_MORE_SETTINGS_POS_Y, str_text,
				 WHITE, BLACK, MENU_TW_CANCEL_SIZE);

	display.display();
}


void increment_time (uint16_t *p_current_mins, uint8_t wheel_select)
{
	switch (wheel_select)
	{
		case MENU_MINS_UNITS:
			*p_current_mins = *p_current_mins + 1;
		break;
		
		case MENU_MINS_TENS:
			*p_current_mins += 10;
		break;
		
		case MENU_HOURS_UNITS:
			*p_current_mins += 60;
		break;
				
		case MENU_HOURS_TENS:
			*p_current_mins += 600;
		break;
	}
	
	if (*p_current_mins >= 1440)
	{
		*p_current_mins = *p_current_mins % 60;
	}
}


void decrement_time (uint16_t *p_current_mins, uint8_t wheel_select)
{
	switch (wheel_select)
	{
		case MENU_MINS_UNITS:
			if (*p_current_mins > 0)
			{
				*p_current_mins = *p_current_mins - 1;	
			}
		break;
		
		case MENU_MINS_TENS:
			if (*p_current_mins >= 10)
			{
				*p_current_mins -= 10;
			}
		break;
		
		case MENU_HOURS_UNITS:
			if (*p_current_mins >= 60)
			{
				*p_current_mins -= 60;
			}
		break;
		
		case MENU_HOURS_TENS:
			if (*p_current_mins >= 600)
			{
				*p_current_mins -= 600;
			}
		break;
	}
}


static void display_scrollbar (uint8_t page_number, uint8_t num_of_pages, uint8_t num_of_banner_lines, bool b_select_list)
{
	uint16_t vertical_height;
	uint16_t bar_y_pos;
	uint16_t y_trim;
	float bar_pos_size;
	uint16_t bar_size;
	
	vertical_height = LCDHEIGHT - (num_of_banner_lines * (STD_CHAR_HEIGHT + STD_LINE_SPACING));
	uint16_t y_pos_start = num_of_banner_lines * (STD_CHAR_HEIGHT + STD_LINE_SPACING);
	
	if (b_select_list)
	{
		y_trim = 0;
		bar_pos_size = (float)vertical_height / (float)num_of_pages;
		bar_size = (uint16_t)bar_pos_size;
		bar_size = (bar_size) ? bar_size : 1;
		bar_y_pos = y_pos_start + (uint16_t)((float)page_number * bar_pos_size);
	}
	else
	{
		if (num_of_banner_lines)
		{
			y_trim = MENU_VERTICAL_BAR_Y_TRIM;
		}
		else
		{
			y_trim = 0;
		}
		
		bar_pos_size = (float)(vertical_height - y_trim) / (float)num_of_pages;
		bar_size = (uint16_t)bar_pos_size;
		bar_size = (bar_size) ? bar_size : 1;
		bar_y_pos = y_pos_start + (uint16_t)((float)(page_number - 1) * bar_pos_size) + y_trim;
	}
	
	display.drawLine (MENU_VERTICAL_BAR_X_POS, (y_pos_start + y_trim), 
					  MENU_VERTICAL_BAR_X_POS, 
					  (y_pos_start + y_trim + vertical_height), BLACK);
	
	display.fillRect (MENU_VERTICAL_BAR_X_POS - MENU_VERTICAL_BAR_WIDTH, 
					  bar_y_pos, 
					  ((MENU_VERTICAL_BAR_WIDTH * 2) + 1), 
					  bar_size, BLACK);
}


static void
toggle_selector_display (uint8_t page_number, uint8_t current_value)
{
	get_string (str_text, g_guimenu_page_def[page_number]->selector->select_list[current_value]);
	uint8_t start_x = get_mid_x (MENU_SELECT_SIZE, str_text);
	draw_string (start_x, MENU_SELECT_Y_POS, str_text, GUIMENU_TEXT_WHITE, GUIMENU_TEXT_BLACK, MENU_SELECT_SIZE);
}


static void
toggle_selector_operation (uint8_t page_number, uint8_t *p_exit_key)
{
	bool b_selector_end = false;

	while (!b_selector_end)
	{
		uint8_t current_value = EEPROM.read (g_guimenu_page_def[page_number]->selector->eeprom_address);
		b_selector_end = toggle_selector_main (page_number, current_value, p_exit_key);
	}
}


static bool
toggle_selector_main (uint8_t page_number, uint8_t current_value, uint8_t *p_exit_key)
{
	bool b_key_response = false;
	bool b_selector_end = false;
	uint8_t original_value = current_value;
	uint8_t new_value = current_value;

	while (!b_key_response)
	{
		uint8_t key_input = GetButton();
		switch (key_input)
		{
			case KEY_PLUS:
				if (new_value < (g_guimenu_page_def[page_number]->selector->list_size - 1))
				{
					new_value++;
					toggle_selector_display (page_number, new_value);
					current_value = new_value;
					display.display();
				}
			break;
			
			case KEY_MINUS:
				if (new_value)
				{
					new_value--;
					toggle_selector_display (page_number, new_value);
					current_value = new_value;
					display.display();
				}
			break;
			
			case KEY_PREV:
			case KEY_DOWN:
				if (new_value != original_value)
				{
					EEPROM.write (g_guimenu_page_def[page_number]->selector->eeprom_address, new_value);
				}
				*p_exit_key = key_input;
				b_key_response = true;
				b_selector_end = true;
			break;
		}
	}

	return b_selector_end;
}



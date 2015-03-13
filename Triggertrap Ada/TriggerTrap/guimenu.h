#ifndef GUIMENU_H_
#define GUIMENU_H_

#include "guimenu_pages.h"

// Definitions
#define GUIMENU_MAX_NUM_STRING_SIZE		3
#define GUIMENU_MAX_STRING_NAME_SIZE	15
#define GUIMENU_MAX_SELECTOR_LIST_SIZE	25

#define GUIMENU_TEXT_BLACK				1
#define GUIMENU_TEXT_WHITE				0

#define GUIMENU_UNITS_US				0
#define GUIMENU_UNITS_MS				1
#define GUIMENU_UNITS_S					2
#define GUIMENU_UNITS_M					3
#define GUIMENU_UNITS_H					4

#define GUIMENU_INFINITE_VALUE			10001


// Type definitions
typedef struct {
	uint8_t number_id;
	uint8_t text1_id;
	uint8_t text2_id;
	bool b_invert_text;
} guimenu_title_t;

typedef enum {
	list_select,
	thumbwheel_select,
	thumbwheel_units_select,
	time_select,
	toggle_select
} guimenu_selectortype_t;

typedef struct {
	uint8_t text1_id;
	uint8_t text2_id;
	uint16_t eeprom_address;
	guimenu_selectortype_t select_type;						
	uint8_t *select_list;							// Only valid if select_type == list_select or toggle_select
	uint8_t list_size;								// Only valid if select_type == list_select or toggle_select
	uint8_t low_units;
	uint8_t high_units;
	uint16_t min_value;
	uint16_t max_value;
} guimenu_selector_t;

typedef struct {
	uint8_t text1_id;
	uint8_t text2_id;
} guimenu_progressbar_t;

typedef struct {
	uint8_t text1_id;
	uint8_t text2_id;
} guimenu_banner_t;

typedef struct {
	uint8_t page;
	uint8_t total_pages;
	bool b_invert;
} guimenu_scrollbar_t;

typedef struct {
	const uint8_t *bitmap;
	guimenu_title_t *title_info;
	guimenu_banner_t *banner_info;
	uint8_t button_text_id;
	bool b_more_settings;
	guimenu_selector_t *selector;
	const guimenu_progressbar_t *progressbar;
	guimenu_scrollbar_t *scrollbar;
} guimenu_page_t;


typedef struct {
	uint8_t hours;
	uint8_t mins;
	uint8_t secs;
} guimenu_time_t;

#ifdef __cplusplus
extern "C" {
#endif

void guimenu_initialise (uint8_t contrast, void (*pf_get_time)(guimenu_time_t *p_time), void (*pf_set_time)(guimenu_time_t *p_time));
void guimenu_clearpage (void);
void guimenu_println (char *str_message);
void guimenu_displaypage (uint8_t page_number);
void guimenu_updatepage (void);
void guimenu_setcontrast (int contrast);
void guimenu_settextsize (uint8_t size);
void guimenu_settextcolour (uint16_t colour);
void guimenu_update (void);
void guimenu_selector (uint8_t page_number, uint8_t *p_exit_key);
void guimenu_progressbar_start (uint8_t page_number, uint32_t start_time, uint8_t units, uint8_t num_of_shots);
void guimenu_progressbar_update (uint32_t time_left, uint8_t shot_num);
void guimenu_operation_complete (uint8_t page_number, uint8_t *p_exit_key);
void guimenu_display_lowbattery_banner (void);
void guimenu_display_normalbattery_banner (void);

#ifdef __cplusplus
}
#endif



#endif /* GUIMENU_H_ */
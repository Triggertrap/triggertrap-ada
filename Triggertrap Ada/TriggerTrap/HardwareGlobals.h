#ifndef HARDWARE_GLOBALS_H
#define HARDWARE_GLOBALS_H


#define DownButton		0     //
#define LeftButton		1     //
#define SelectButton	2     //
#define RightButton		3     //
#define UpButton		4     //

#define AND_CONFIG		0
#define OR_CONFIG		1

#define BackLight		26

#define Focus			21     //triggers 1 and 2 of output 1
#define Trigger			20     //
#define CAMERAOUT2_A	23
#define CAMERAOUT2_B	22
#define CAMERAOUT3_A	25
#define CAMERAOUT3_B	24
#define LDO_EN			14     //
#define FTDI_RTS		15
#define FTDI_CTS		16
#define FTDI_TXD		17
#define FTDI_RXD		18
#define Stack			27     //
#define LCD_CE			10
#define BATTERY_MON		5
#define AudioRight		7
#define AudioLeft		6
#define MIC				8
#define LCD_DC			9
#define LCD_CE			10
#define LCD_CLK			11
#define LCD_DIN			12
#define LCD_RST			13
#define STACK_PWR		19
#ifdef VERSION_THREE_HW
#define LCD_POWER		28
#else
#define BONUS_PIN		28
#endif

#define LOW_BATTERY_LEVEL1						229				//2.1V
#define LOW_BATTERY_LEVEL2						186				//1.7V
#define SEND_MOB_MS								150
#define SEND_MOB_US								150000
#define BACKLIGHT_TIMEOUT						30000			//time in milliseconds

#endif //HARDWARE_GLOBALS_H

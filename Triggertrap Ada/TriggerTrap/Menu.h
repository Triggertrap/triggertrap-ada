#ifndef MENU_H
#define MENU_H

#include <avr/pgmspace.h>
#include <stdlib.h>
#include "Timelapse.h"
#include "HighSpeedFlash.h"

#define SENSOR_SETTLING_TIME_MS			15000UL

#ifdef INCLUDE_NEWMODE
#include "NewMode.h"
#endif


char HSFConfigure (char input);
char SensorConfigure (char input);
char SensorTLConfigure (char input);
char SensorVideoConfigure (char input);
char AdvancedSensorConfigure (char input);
char SensorSettlingDelay (uint8_t page_number, char end_state, char cancel_state, char TriggerOn_addr);

char Exponentlookup(char Value);

char SensorTrigger(char input);
char SensorTimeLapse(char input);
char PowerDownFunc(char input);
void MobileTrigger(void);
int AUDIO_READ(void);
char MOB_IN(char input);
char MOB_OUT(char input);
char Timelapse_new(char input);
char BulbRamp(char input);
char BulbRampStartExpSet (char input);
char BulbRampEndExpSet (char input);
char BulbRampDelaySet (char input);
char BulbRampCountSet (char input);
char BulbRampDurationSet (char input);

char HSFTriggerOnSet (char input);
char HSFCloseShutterSet (char input);
char HSFShutterCycleSet (char input);
char HSFFlashDelaySet (char input);
char HSFResetDelaySet (char input);
char HSFTimesActiveSet (char input);
char HSFStartTimeSet (char input);
char HSFEndTimeSet (char input);

char SensorVideoDelaySet (char input);
char SensorVideoStopAfterActSet (char input);
char SensorVideoTriggerSet (char input);
char SensorVideoTimesActiveSet (char input);
char SensorVideoStartTimeSet (char input);
char SensorVideoEndTimeSet (char input);
char SensorVideoTriggerOnSet (char input);

char HighSpeedFlash(char input);
char TimeWarp(char input);
char TimeWarpFunctionSet (char input);
void SendConfigOR(void);
void SendConfigAND(void);
void HardwareTest(void);
char StarTrail(char input);
char SensorVideo(char input);
char SensorVideoDelaySet (char input);
void timer1(int ms);
char TimelapseCountSet(char input);
char CameraPrefocusSet (char input);
char ShutterPulseSet (char input);
char FlashPulseSet (char input);

char ShutterPulse(char input);
char NULLFUNC(char input);

char AdvancedSensor(char input);
char TimelapseIntervalSet(char input);
char TimelapseStartDelay(char input);
char TimeWarpCountSet (char input);
char TimeWarpDirectionSet (char input);
char TimeWarpWaitSet (char input);
char TimeWarpDurationSet (char input);
char BulbRampStartExposureSet (char input);
char BulbRampEndExposureSet (char input);
char BulbRampWaitSet (char input);
char BulbRampDurationSet (char input);
void MobileTriggerSetup(void);
void mobile_trigger_on(void);
void mobile_trigger_off(void);
char SettingError (char State);

unsigned long GetTimeMicros(void);
unsigned long GetTimeMillis(void);
unsigned long GetTimeSeconds(void);
unsigned long GetTimeMin(void);
unsigned long GetTimeHours(void);
unsigned long (*CurrentTimeSelector (char Units))(void);			//function that returns a pointer to a function (hence weird looking declaration)
unsigned long formatTime (unsigned long Time, char Units);
unsigned long formatTimeToMicro (unsigned long Time, char Units);
unsigned long formatTimeToMillis (unsigned long Time, char Units);
unsigned long formatTimeToSeconds (unsigned long Time, char Units);

char TimelapseTimeActive (char input);
char TimelapseStartTime(char input);
char TimelapseEndTime(char input);
void set_time(guimenu_time_t  *p_time);
void get_time(guimenu_time_t  *p_time);
uint32_t get_time_in_secs (void);
uint32_t time_units_to_secs (uint16_t time, uint8_t units);
char Timeset (char input);
char About (char input);
uint8_t time_active(uint16_t eeprom_start_address, uint16_t eeprom_stop_address );

char StarTrailInterval (char input);
char StarTrailShutterSpeed(char input);
char StarTrailCount(char input);
char StarTrailDelay(char input);

char LEHDRMidExpSet (char input);
char LEHDRShotsSet (char input);
char LEHDREVPerStepSet (char input);
char LEHDRTimelapseSet (char input);
float ExtractExposure (char Selector);
int ExtractShot(unsigned char Selector);
float ExtractEV(unsigned char Selector);


char SensorTriggerDelay(char input);
char SensorResetDelay(char input);
char SensorTriggerOn(char input);
char SensorMobileInput(char input);
char SensorMobileOutput(char input);
char SensorTimeActive(char input);
char SensorStartTime(char input);
char SensorStopTime(char input);

char Sensor_TL_Delay(char input);
char Sensor_TL_Interval(char input);
char Sensor_TL_Continue(char input);
char Sensor_TL_Trigger(char input);
char Sensor_TL_MobileInput(char input);
char Sensor_TL_MobileOutput(char input);
char Sensor_TL_TimeActive(char input);
char Sensor_TL_StartTime(char input);
char Sensor_TL_StopTime(char input);
char Sensor_TL_Continue_Set(char input);

void StackPowerDown (void);

char A_Sensor_CH1A_D(char input);
char A_Sensor_CH1A_P(char input);
char A_Sensor_CH1B_D(char input);
char A_Sensor_CH1B_P(char input);

char A_Sensor_CH2A_D(char input);
char A_Sensor_CH2A_P(char input);
char A_Sensor_CH2B_D(char input);
char A_Sensor_CH2B_P(char input);

char A_Sensor_CH3A_D(char input);
char A_Sensor_CH3A_P(char input);
char A_Sensor_CH3B_D(char input);
char A_Sensor_CH3B_P(char input);

char A_Sensor_Trigger_Mobile(char input);
char A_Sensor_Reset_Delay(char input);
char A_Sensor_Trigger_On(char input);			

typedef struct
{
	unsigned char state;
	unsigned char nextstate[NUM_OF_KEYS + 1];
} MENU_NEXTSTATE;

typedef struct
{
	unsigned char state;
	uint8_t page_number;
	char (*pFunc)(char input);
} MENU_STATE;



#endif //MENU_H
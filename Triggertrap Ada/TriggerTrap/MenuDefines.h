#ifndef DEFINES_H
#define DEFINES_H

#define TRUE						1
#define FALSE						0


#define ST_TMLPSE                			1
#define ST_LEHDR_START						2
#define ST_HSF                   			3
#define ST_LEHDR_MIDEXP_SET					4
#define ST_SEN_TL          					5
#define ST_LEHDR_SHOTS_SET					6
#define ST_SETTINGS             			7
#define ST_LEHDR_EVPERSTEP_SET				8
#define ST_LEHDR_TIMLAPSE_SET				9
#define ST_LEHDR_STOP						10
#define ST_SENSOR_START						11
#define ST_SENSOR_STOP						12
#define ST_SENSOR_TRIGGER_DELAY				13
#define ST_HSF_CLOSESHUTTER_SET				14
#define ST_HSF_SHUTTERCYCLE_SET				15
#define ST_HSF_FLASH_DELAY_SET				16
#define ST_HSF_RESETDELAY_SET				17
#define ST_HSF_OP_TACTVE					18
#define ST_SENSOR_RESET_DELAY				19
#define ST_SENSOR_TRIGGER_ON				20
#define ST_SENSOR_MOBILE_INPUT				21
#define ST_SENSOR_MOBILE_OUTPUT				22
#define ST_SENSOR_TIME_ACTIVE				23
#define ST_SENSOR_START_TIME				24
#define ST_SENSOR_STOP_TIME					25
#define ST_SETTINGS_OP_PREFOCUS				26
#define ST_SETTINGS_OP_SHTPLSE				27
#define ST_SETTINGS_OP_FLSHPLSE				28
#define ST_SETTINGS_OP_SETCLK				29
#define ST_SENSOR_CONFIG_PROGESS			30
#define ST_SEN_TL_CONFIG_PROGESS			31
#define ST_SENSORVIDEO_CONFIG_PROGESS		32
#define ST_ADVSENSOR_CONFIG_PROGESS			33
#define ST_SEN_TL_CONTINUE					34
#define ST_SEN_TL_TRIGGER					35
#define ST_SEN_TL_MOBILE_INPUT				36		
#define ST_SEN_TL_MOBILE_OUTPUT				37		
#define ST_SEN_TL_TIME_ACTIVE				38		
#define ST_SEN_TL_START_TIME				39			
#define ST_SEN								40
#define ST_SEN_RUN							41
#define ST_SEN_RUNNING						42
#define ST_OFF								43
#define ST_OFF_FUNC							44
#define ST_SEN_TL_STOP_TIME					45
#define ST_SEN_TL_CONTINUE_SET				46
#define ST_OFF_CONFIRM						47
#define ST_OFF_CANCEL						48
#define ST_UNSUPPORTED						49
#define ST_SEN_OP_TRGR						50
#define ST_SEN_STACK_AND					51
#define ST_SEN_STACK_OR						52
#define ST_SEN_STACK_OR_FUNC				53
#define ST_SEN_STACK_AND_FUNC				54
#define ST_SEN_RESET_DELAY					55
#define ST_SEN_START_DELAY					56
#define ST_SEN_RESET_DELAY_FUNC				57
#define ST_SEN_START_DELAY_FUNC				58
#define ST_SEN_TRIGGER_DELAY				59
#define ST_SEN_TRIGGER_DELAY_FUNC			60
#define ST_SEN_TL_START						66
#define ST_SEN_TL_STOP						67
#define ST_SEN_TL_DELAY						68
#define ST_SEN_TL_INTERVAL					69
#define ST_SETTINGS_OP_SETCLK_FUNC			70
#define ST_TMLPSE_OP_TACTIVE_ENABLE			71
#define ST_TMLPSE_OP_TACTIVE_START			72
#define ST_TMLPSE_OP_TACTIVE_END			73
#define ST_TMLPSE_OP_TACTIVE_START_FUNC		74
#define ST_TMLPSE_OP_TACTIVE_END_FUNC		75
#define ST_A_SENSOR_START					76
#define ST_A_SENSOR_STOP					77
#define ST_A_SENSOR_CH1A_D					78
#define ST_A_SENSOR_CH1A_P					79
#define ST_A_SENSOR_CH1B_D					80
#define ST_A_SENSOR_CH1B_P					81
#define ST_A_SENSOR_CH2A_D					82
#define ST_A_SENSOR_CH2A_P					83
#define ST_A_SENSOR_CH2B_D					84
#define ST_A_SENSOR_CH2B_P					85
#define ST_A_SENSOR_CH3A_D					86
#define ST_A_SENSOR_CH3A_P					87
#define ST_A_SENSOR_CH3B_D					88
#define ST_A_SENSOR_CH3B_P					89
#define ST_A_SENSOR_TRIGGER_MOBILE			90
#define ST_A_SENSOR_RESET_DELAY				91
#define ST_A_SENSOR_TRIGGER_ON				92
#define ST_TIMEWARP							93
#define ST_BULBRAMP							94
#define ST_STARTRAIL						95
#define ST_SENSVIDEO						96
#define ST_ADVANCESENS						97
#define ST_LEHDR							98
#define ST_HSF_OP_TRIG_AND					99
#define ST_HSF_OP_TRIG_OR					100
#define ST_HSF_STACK_AND_FUNC				101
#define ST_HSF_STACK_OR_FUNC				102
#define ST_HSF_OP_SHTRCYC_FUNC				103
#define ST_HSF_OP_FLSHDLY_FUNC				104
#define ST_HSF_OP_RSTDLY_FUNC				105
#define ST_HSF_OP_START						106
#define ST_HSF_OP_START_FUNC				107
#define ST_HSF_OP_CLSHTR_FUNC_YES			108
#define ST_HSF_OP_CLSHTR_FUNC_NO			109
#define ST_STARTRAIL_RUN					110
#define ST_STARTRAIL_INTERVAL				111
#define ST_STARTRAIL_SHTR_SPD				112
#define ST_STARTRAIL_CNT					113
#define ST_STARTRAIL_WAIT					114
#define ST_STARTRAIL_RUN_FUNC				115
#define ST_BULBRAMP_RUN_FUNC				116
#define ST_LEHDR_RUN						117
#define ST_LEHDR_RUN_FUNC					118
#define ST_TIMEWARP_RUN_FUNC				119
#define ST_SETTINGS_OP_PREFOCUS_FUNC		120
#define ST_SETTINGS_OP_SHTPLSE_FUNC			121
#define ST_SETTINGS_OP_FLSHPLSE_FUNC		122
#define ST_ADVANCESENS_1A					123
#define ST_ADVANCESENS_1A_FUNC				124
#define ST_ADVANCESENS_1B					125
#define ST_ADVANCESENS_1B_FUNC				126
// 127 seems to cause crashes
#define ST_ADVANCESENS_2A					128
#define ST_ADVANCESENS_2A_FUNC				129
#define ST_ADVANCESENS_2B					130
#define ST_ADVANCESENS_2B_FUNC				131
#define ST_ADVANCESENS_MOB					132
#define ST_ADVANCESENS_MOB_FUNC				133
#define ST_ADVANCESENS_RSTDLY				134
#define ST_ADVANCESENS_RSTDLY_FUNC			135
#define ST_ADVANCESENS_TRG					136
#define ST_ADVANCESENS_TRG_AND				137
#define ST_ADVANCESENS_TRG_OR				138
#define ST_ADVANCESENS_TRG_OR_FUNC			139
#define	ST_ADVANCESENS_TRG_AND_FUNC			140
#define ST_ADVANCESENS_1A_DELAY				141
#define ST_ADVANCESENS_1B_DELAY				142
#define ST_ADVANCESENS_2A_DELAY				143
#define ST_ADVANCESENS_2B_DELAY				144
#define ST_ADVANCESENS_1A_DELAY_FUNC		145
#define ST_ADVANCESENS_1B_DELAY_FUNC		146
#define ST_ADVANCESENS_2A_DELAY_FUNC		147
#define ST_ADVANCESENS_2B_DELAY_FUNC		148
#define ST_TMLPSE_START						149
#define ST_TMLPSE_COUNT						150
#define ST_TMLPSE_WAIT						151
#define ST_TMLPSE_ACTIVE					152
#define ST_TMLPSE_RUN						153
#define ST_BULBRAMP_RUN						154
#define ST_TIMEWARP_START					155
#define ST_TIMEWARP_FUNCTION				156
#define ST_TIMEWARP_RUN						157
#define ST_TIMEWARP_STOP					158
#define ST_SENSORVIDEO_START				159
#define ST_SENSORVIDEO_DELAY				160
#define ST_HSF_STOP							161
#define ST_TMLPSE_INTERVAL					162
#define ST_TMLPSE_START_DELAY				163
#define ST_TIMEWARP_COUNT_SET				164
#define ST_TIMEWARP_DIRECTION_SET			165
#define ST_TIMEWARP_WAIT_SET				166
#define ST_TIMEWARP_DURATION_SET			167
#define ST_BULBRAMP_START_EXPOSURE			168
#define ST_BULBRAMP_END_EXPOSURE			169
#define ST_BULBRAMP_WAIT					170
#define ST_HSF_CONFIG_PROGRESS				171
#define ST_TMLPSE_START_TIME				172
#define ST_TMLPSE_END_TIME					173
#define ST_SETTINGS_SETSYSTEM_TIME			174
#define ST_STARTRAIL_START					175
#define ST_STARTRAIL_SHUTTER_SPEED			176
#define ST_STARTRAIL_COUNT					177
#define ST_STARTRAIL_DELAY					178
#define ST_STARTRAIL_STOP					179
#define ST_HSF_START						180
#define ST_BULBRAMP_START					181
#define ST_BULBRAMP_COUNT					182
#define ST_BULBRAMP_START_EXP				183
#define ST_BULBRAMP_END_EXP					184
#define ST_BULBRAMP_DELAYSTART				185
#define ST_BULBRAMP_DURATION				186
#define ST_HSF_TRIGGERON_SET				187
#define ST_HSF_TIMESACTIVE_SET				188
#define ST_HSF_START_TIME_SET				189
#define ST_HSF_END_TIME_SET					190
#define ST_HSF_OP_CLSHTR					191
#define ST_SENSORVIDEO_STOP_AFTER_SET		192
#define ST_SENSORVIDEO_TRIGGER_SET			193
#define ST_SENSORVIDEO_TIMESACTIVE_SET		194
#define ST_SENSORVIDEO_STARTTIME_SET		195
#define ST_SENSORVIDEO_ENDTIME_SET			196
#define ST_SENSORVIDEO_TRIGGERON_SET		197
#define ST_SENSORVIDEO_STOP					198
#define ST_SEN_TL_PROGBAR					199
#define ST_LEHDR_PROGBAR				    200
#define ST_TMLPSE_PROGBAR					201
#define ST_BULBRAMP_PROGBAR					202
#define ST_SETTINGS_ABOUT					203

#ifdef INCLUDE_NEWMODE
#define ST_NEWMODE							204
#define ST_NEWMODE_START					205
#define ST_NEWMODE_SETTLING					206
#define ST_NEWMODE_RUNNING					207
#define ST_NEWMODE_TRIGGERON				208
#define ST_NEWMODE_DELAY					209
#endif



#define KEY_NULL              		  0
#define KEY_MINUS              		  1
#define KEY_SELECT             		  2
#define KEY_PREV              		  3
#define KEY_PLUS              		  4
#define KEY_DOWN             		  5
#define NUM_OF_KEYS					  5


#define CAMERA_OUT_ONLY				0x00
#define MOBILE_OUT_ONLY				0x01
#define BOTH_OUTPUTS				0x02

 
// TIMEWARP DEFINES
	
#define EASE_IN				1
#define EASE_OUT			2
#define EASE_INOUT			3
#define EASE_OUTIN			4
#define MAX_SHOTS			721

//MISC DEFINE 

#define STACK_TRIGGER_ONLY					0
#define MOBILE_TRIGGER_ONLY					1
#define BOTH_TRIGGERS						2

#define _TESTING							//removes certain functionality for testing
#define _DISABLE_OLD_CODE
#define TEMPNOTINUSE						
//#define _USE_ARDUINO_ORIGINAL_CODE		//uncomment if needed to return to original arduino library functions 
//#define _STEREO_MOBILE						//no reason to use both channels when reading from the mobile
#define _USE_ARDUINO_RTC_SETUP				1
//#define _HIGH_CONTRAST

#endif //DEFINES_H
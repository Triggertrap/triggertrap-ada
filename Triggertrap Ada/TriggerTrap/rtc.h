 #if 0
 #ifndef DRIVERS_RTC_RTC_H
 #define DRIVERS_RTC_RTC_H

#include <inttypes.h>
//#include "compiler.h"
 //#include <conf_rtc.h>
 
#define 	SYSCLK_RTC   PR_RTC_bm

 #ifdef __DOXYGEN__
 # define CONFIG_RTC_COMPARE_INT_LEVEL
 #endif

 #ifdef __DOXYGEN__
 # define CONFIG_RTC_OVERFLOW_INT_LEVEL
 #endif

 #ifdef __DOXYGEN__
 # define CONFIG_RTC_PRESCALER
 #endif

 typedef void (*rtc_callback_t)(uint32_t time);

 void rtc_set_callback(rtc_callback_t callback);
 void rtc_set_time(uint32_t time);
 uint32_t rtc_get_time(void);
 void rtc_set_alarm(uint32_t time);
 int rtc_alarm_has_triggered(void);

 static inline void rtc_set_alarm_relative(uint32_t offset)
 {
        rtc_set_alarm(rtc_get_time() + offset);
 }

 extern void rtc_init(void);


 #endif /* RTC_H */
 #endif //
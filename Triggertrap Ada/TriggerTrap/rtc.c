 #if 0
 //#include "compiler.h"
 //#include "sysclk.h"

// #include <sleepmgr.h>
 #include <inttypes.h>
 #include "Arduino.h"
 #include "rtc.h"
 

 #ifdef CONFIG_RTC_CLOCK_SOURCE
 # error CONFIG_RTC_CLOCK_SOURCE is deprecated. Use CONFIG_RTC_SOURCE in \
         conf_clock.h as it is now done in sysclk_init()
 #endif

 #ifdef CONFIG_RTC_OVERFLOW_INT_LEVEL
 # define RTC_OVERFLOW_INT_LEVEL CONFIG_RTC_OVERFLOW_INT_LEVEL
 #else
 # define RTC_OVERFLOW_INT_LEVEL RTC_OVFINTLVL_LO_gc
 #endif

 #ifdef CONFIG_RTC_COMPARE_INT_LEVEL
 # define RTC_COMPARE_INT_LEVEL CONFIG_RTC_COMPARE_INT_LEVEL
 #else
 # define RTC_COMPARE_INT_LEVEL RTC_COMPINTLVL_LO_gc
 #endif

 struct rtc_data_struct {
     uint16_t counter_high;
     uint16_t alarm_high;
     uint16_t alarm_low;
     rtc_callback_t callback;
 };

 struct rtc_data_struct rtc_data;

 static inline __attribute__((__always_inline__)) int rtc_is_busy(void)
 {
     return RTC.STATUS & RTC_SYNCBUSY_bm;
 }

inline __attribute__((__always_inline__)) int rtc_alarm_has_triggered(void)
 {
     return !(RTC.INTCTRL & RTC_COMPARE_INT_LEVEL );
 }

 void rtc_set_time(uint32_t time)
 {
     RTC.CTRL = RTC_PRESCALER_OFF_gc;

     while (rtc_is_busy());

     RTC.CNT = time;
     rtc_data.counter_high = time >> 16;
     //RTC.CTRL = CONFIG_RTC_PRESCALER;
	 RTC.CTRL = RTC_PRESCALER_DIV1_gc;
 }

 uint32_t rtc_get_time(void)
 {
    // irqflags_t flags;
	 uint8_t	flags;
     uint16_t   count_high;
     uint16_t   count_low;

     while (rtc_is_busy());

     flags = cpu_irq_save();
     count_high = rtc_data.counter_high;
     count_low = RTC.CNT;
     // Test for possible pending increase of high count value
     if ((count_low == 0) && (RTC.INTFLAGS & RTC_OVFIF_bm))
         count_high++;
     cpu_irq_restore(flags);

     return ((uint32_t)count_high << 16) | count_low;
 }

 void rtc_set_alarm(uint32_t time)
 {
     RTC.INTCTRL = RTC_OVERFLOW_INT_LEVEL;
     RTC.COMP = time;
     rtc_data.alarm_low = time;
     rtc_data.alarm_high = time >> 16;

     while (rtc_is_busy());

     RTC.INTFLAGS = RTC_COMPIF_bm;
     RTC.INTCTRL = (uint8_t)RTC_COMPARE_INT_LEVEL
         | (uint8_t)RTC_OVERFLOW_INT_LEVEL;
 }

 void rtc_set_callback(rtc_callback_t callback)
 {
     rtc_data.callback = callback;
 }

 void rtc_init(void)
 {
    //sysclk_enable_module(SYSCLK_PORT_GEN, SYSCLK_RTC);
	sysclk_enable_module(0, SYSCLK_RTC);	//is 0 equal to SYSCLK_PORT_GEN!? cannot find the def!! DEBUG
    RTC.PER = 0xffff;
    RTC.CNT = 0;
    /* Since overflow interrupt is needed all the time we limit sleep to
     * power-save.
     */
   // sleepmgr_lock_mode(SLEEPMGR_PSAVE);	//LETS REMOVE THIS FOR NOW; DEBUG!
    RTC.INTCTRL = RTC_OVERFLOW_INT_LEVEL;
    //RTC.CTRL = CONFIG_RTC_PRESCALER;
	RTC.CTRL = RTC_PRESCALER_DIV1_gc;
 }

 ISR(RTC_OVF_vect)
 {
    rtc_data.counter_high++;
 }

 ISR(RTC_COMP_vect)
 {
     if (rtc_data.counter_high >= rtc_data.alarm_high) {
	         RTC.INTCTRL = RTC_OVERFLOW_INT_LEVEL;
	                  if (rtc_data.callback) {
		             uint32_t count = ((uint32_t)rtc_data.counter_high << 16)
		             | RTC.CNT;
		             uint32_t alarm = ((uint32_t)rtc_data.alarm_high << 16)
		             | rtc_data.alarm_low;
		             /* Workaround for errata. Count might not be updated
		             * when waking up from sleep, so in this case use alarm
		             * time plus one.
		             */
		             if (alarm >= count)
		             count = alarm + 1;
		                          rtc_data.callback(count);
	        }
    }
 }
 #endif
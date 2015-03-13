#include <avr/sleep.h>
#include "timing.h"
#include "Arduino.h"

void do_sleep(unsigned long ms) {
#ifdef SLEEP_DEBUG_PIN
	pinMode(SLEEP_DEBUG_PIN, OUTPUT);
#endif
	unsigned long start = millis();
	do {
#ifdef SLEEP_DEBUG_PIN
		digitalWrite(SLEEP_DEBUG_PIN, LOW);
#endif
		sleep_mode();
#ifdef SLEEP_DEBUG_PIN
		digitalWrite(SLEEP_DEBUG_PIN, HIGH);
#endif
	} while(millis() - start < ms);
}

// Goes into idle mode, conserving power, for the specified amount of time.
// If ms is 0, still sleeps at least once, so minimum sleep time is until the
// next RTC tick (up to 3ms)
void sleep(unsigned long ms) {
	set_sleep_mode(SLEEP_MODE_IDLE);
	do_sleep(ms);
}

// Goes into power save mode, conserving a lot more power, for the specified
// amount of time. If ms is 0, still sleeps at least once, so minimum sleep time
// is until the next RTC tick (up to 3ms)
void deepSleep(unsigned long ms) {
	set_sleep_mode(SLEEP_MODE_PWR_SAVE);
	do_sleep(ms);
}

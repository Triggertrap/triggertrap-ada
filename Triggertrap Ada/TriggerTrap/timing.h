#ifndef USE_RTC
#error This code requires USE_RTC to function!
#endif

// Sleep functions can be debugged by setting SLEEP_DEBUG_PIN to an Arduino
// pin name. This pin will be taken high when awake, and low when sleeping.

// Goes into idle mode, conserving power, for the specified amount of time.
// If ms is 0, still sleeps at least once, so minimum sleep time is until the
// next RTC tick (up to 3ms)
void sleep(unsigned long ms);

// Goes into power save mode, conserving a lot more power, for the specified
// amount of time. If ms is 0, still sleeps at least once, so minimum sleep time
// is until the next RTC tick (up to 3ms)
void deepSleep(unsigned long ms);

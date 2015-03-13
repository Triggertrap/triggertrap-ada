#include "Arduino.h"
#include "EEPROM.h"
#include "eeprom_addresses.h"




int main(void)
{

	init();
	setup();
    
	for (;;)
		loop();
        
	return 0;
}


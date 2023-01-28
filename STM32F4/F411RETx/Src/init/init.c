#include "init.h"


void __init__(void){


	/* Initialise drivers according to the flags defined in config/config.h */

	if(__LED_INIT__ == 0x1){
		LED_INIT();
	}
	if(__UART_INIT__ == 0x1){
		UART_INIT();
	}

}

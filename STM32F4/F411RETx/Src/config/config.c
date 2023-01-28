#include "config.h"

/*
 *
 * @brief ysRTOS configuration API.
 *
 * Modify flags whose description is given in the documentation accordingly.
 *
 * */

void __ENABLE_LED__(void){
	__LED_INIT__ = 0x1;
}

void __DISABLE_LED__(void){
	__LED_INIT__ = 0x0;
}

void __ENABLE_UART__(void){
	__UART_INIT__ = 0x1;
}

void DISABLE_UART__(void){
	__UART_INIT__ = 0x0;
}

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdio.h>

/* ERROR VALUES */
enum ERR{
	__SET_MAX_THREADS_FAIL__,
	__SET_STK_SIZE_FAIL__
};

/* All values you see assigned to the flags are the DEFAULT values */
/* Use the ysRTOS configuration API defined in config/config.c to manipulate them */

/* Flags for initialising device drivers (0x1 -> Enable, else Disable) */
extern uint8_t __LED_INIT__	 = 0x1;
extern uint8_t __UART_INIT__	 = 0x1;

/* Kernel flags and variables (Default values) */
extern uint32_t MAX_THREADS 		= 5;
extern uint32_t STK_SIZE			= 100;	/* Stack size (working with threads) */
extern const uint32_t BUS_FREQ		= 16000000;
extern const uint32_t quanta		= 10; /* time quanta for the round robin scheduler in milliseconds */
extern uint8_t RTOS_INITIALISED 	= 0x0;

/* ysRTOS Configuration API functions*/

void __SET_MAX_THREADS__(uint32_t val);
void __SET_STK_SIZE__(uint32_t stk_size);



#endif

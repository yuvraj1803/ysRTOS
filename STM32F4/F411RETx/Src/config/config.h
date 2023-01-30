/**
 ******************************************************************************
 * @file           : config.h
 * @author         : Yuvraj Sakshith
 * @brief          : ysRTOS configuration file
 ******************************************************************************
 ******************************************************************************
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdio.h>

/* ERROR CODES */

enum ERR{
	__ADD_THREAD_FAILURE__,
	__ADD_PERIODIC_THREAD_FAILURE__
};


/* All values you see assigned to the flags are the DEFAULT values */
/* Use the ysRTOS configuration API defined in config/config.c to manipulate them */

/* Flags for initialising device drivers (0x1 -> Enable, else Disable) [DISABLED ON DEFAULT]*/
#define __LED_INIT__	 0x0
#define __UART_INIT__	 0x0

/* Kernel flags and variables (Default values) */
#define MAX_THREADS 	 		5
#define MAX_PERIODIC_THREADS 	5
#define STACK_SIZE	     		100	/* Stack size (working with threads) */
#define BUS_FREQ		 		16000000
#define quanta			 		10  /* time quanta for the round robin scheduler in milliseconds */
#define MAX_MSG_ARR		 		100


#endif

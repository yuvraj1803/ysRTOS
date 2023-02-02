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
#define __LED_INIT__	 0x1
#define __UART_INIT__	 0x1
#define __ADC_INIT__ 	 0x0
/*
 * * All periodic threads rely on the TIM2_IRQHandler.
   * Be very careful when modifying the value of __TIM2_INIT__ -> Enables TIM2 timer.
 */
#define __TIM2_INIT__	 0x1

#define __EXTI_13_INIT__ 0x0

/* Kernel flags and variables (Default values) */
#define MAX_THREADS 	 		5
#define MAX_PERIODIC_THREADS 	5
#define STACK_SIZE	     		100	/* Stack size (working with threads) */
#define BUS_FREQ		 		16000000
#define quanta			 		10  /* time quanta for the round robin scheduler in milliseconds */
#define MAX_MSG_ARR		 		100
#define ticks_in_1ms 			16000; /* Number of clock ticks in one millisecond */

/* Interrupt Handler Priorities
 *
 * Note: The priorities are arranged in increasing order.
 * 		 Going against it can cause unexpected outcomes, which may be difficult to debug.
 *
 *  */
#define SYSTICK_PRIO		15
#define TIM2_PRIO			7
#define PENDSV_PRIO			0



/* Misc. flags used in the kernel */
#define THREAD_ACTIVE			1

#endif

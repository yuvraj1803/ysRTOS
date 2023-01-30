/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Yuvraj Sakshith
 * @brief          : Main program body
 ******************************************************************************
 ******************************************************************************
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "config/config.h"
#include "init/init.h"
#include "kernel/kernel.h"


int main(void)
{

	/* Configuration Notes */

	/* To enable LED Driver, set __LED_INIT__ = 0x1 in config/config.h
	 *
	 * To enable UART Driver, set __UART_INIT__ = 0x1 in config/config.h (YOU WILL NEED THIS TO READ ERROR MESSAGES FROM THE BOARD)
	 *
	 * Maximum threads allowed are 5 (default), to modify change MAX_THREADS preprocessor in config/config.h
	 *
	 * Stack size allocated for each thread is 100*4, 400 bytes (default)
	 * to modify change STACK_SIZE preprocessor in config/config.h
	 *
	 * BUS_FREQ (in config/config.h) is set to 16MHz. DO NOT MODIFY unless you are using this on some other microcontroller.
	 *
	 * Time Quanta for the Round-Robin Scheduler is 10 milliseconds(default). To modify change "quanta" in config/config.h
	 *
	 * MAX_MSG_ARR is the maximum size of an array which can fit into a message_unit. Refer kernel/mb/mb.c

	******************/




	__init__(); /* ysRTOS initialisation */


	/* Add all your threads below */

	 // add_thread(&your_thread);

	/*  */

	kernel_launch();


}

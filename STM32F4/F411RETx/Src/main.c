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
#include "drivers/LED/LED.h"
#include "kernel/kernel.h"

int a = 0;
int b = 0;

void pa(void){
	while(1){
		a++;
	}
}

void pb(void){
	while(1){
		b++;
	}
}

void on(void){
	LED_ON();
}
void off(void){
	LED_OFF();
}


int main(void)
{

	/* Configuration Notes */

	/* To enable LED Driver, set __LED_INIT__ = 0x1 in config/config.h
	 *
	 * To enable UART Driver, set __UART_INIT__ = 0x1 in config/config.h (YOU WILL NEED THIS TO READ ERROR MESSAGES FROM THE BOARD)
	 *
	 * To disable TIM2 timer (ENABLED BY DEFAULT), set __TIM2_INIT__ = 0x0 in config/config.h
	 *  (PERIODIC THREADS WILL NOT EXECUTE IF DONE SO)
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


	******************/

	/*
	 * DEFAULT CONFIGURATIONS
	 *
	 * -> LED ENABLED
	 * -> UART ENABLED
	 * -> TIM2 ENABLED
	 * -> ADC1 DISABLED
	 * -> MAX_THREADS = 5
	 * -> MAX_PERIODIC_THREADS = 5
	 * -> STACK SIZE = 400 BYTES
	 * -> TIME QUANTA FOR RR-SCHEDULER = 10 MILLISECONDS
	 *
	 * -> CPU CLOCK = 16Mhz
	 *
	 * */




	__init__(); /* ysRTOS initialisation */

	/* Add all your threads below */

	 add_thread(&pa);
	 add_thread(&pb);
	 add_periodic_thread(&on,50);
	 add_periodic_thread(&off,130);

	/*  */

	kernel_launch();


}

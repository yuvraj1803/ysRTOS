/*
 ******************************************************************************
 * @file           : init.c
 * @author         : Yuvraj Sakshith
 * @brief          : OS Initialisation
 ******************************************************************************
 ******************************************************************************
 */

/*
 *
 * Copyright (c) 2023 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */

#include "init.h"


void __init__(void){

	/* Initialise drivers according to the flags defined in config/config.h */

	if(__LED_INIT__ == 0x1){
		LED_INIT();
	}
	if(__UART_INIT__ == 0x1){
		UART_INIT();
	}

	if(__ADC_INIT__ == 0x1){
		ADC1_INIT();
	}

	if(__EXTI_13_INIT__ == 0x1){
		EXTI13_INIT();
	}




	/* Initialise the kernel */

	kernel_init();


}

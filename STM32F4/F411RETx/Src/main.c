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
#include "drivers/LED/LED.h"
#include "drivers/UART/UART.h"

int main(void)
{

	LED_INIT();
	UART_INIT();


	while(1){
		LED_ON();
		printf("helo");
	}

}

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

#include "config/config.h"
#include "drivers/LED/LED.h"

int main(void)
{

	LED_INIT();



	while(1){
		LED_ON();
	}

}

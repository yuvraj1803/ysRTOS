/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Yuvraj Sakshith
 * @brief          : Main program body
 ******************************************************************************
 ******************************************************************************
 */

#include <stdint.h>
#include "../config/config.h"
#include "../drivers/LED/LED.h"

int main(void)
{

	led_init();

	while(1){
		led_on();
	}

}

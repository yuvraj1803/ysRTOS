/**
 ******************************************************************************
 * @file           : LED.c
 * @author         : Yuvraj Sakshith
 * @brief          : LED Driver
 ******************************************************************************
 ******************************************************************************
 */

#include "LED.h"

#define GPIOAEN		(1U << 0) /* GPIOA Clock Access Enable Bit */
#define LED_PIN		(1U << 5) /* Using Pin 5 in GPIOA as LED_PIN */

void LED_INIT(void){

	RCC -> AHB1ENR |= GPIOAEN; /* Enable clock access to GPIOA */

	/* set pin 5 in GPIOA as output pin */
	GPIOA -> MODER |= (1U << 10);
	GPIOA -> MODER &= ~(1U << 11);

}

void LED_ON(void){

	GPIOA -> ODR |= LED_PIN; /* Set LED_PIN high in GPIOA's output data register */
}

void LED_OFF(void){
	// set LED pin LOW

	GPIOA -> ODR &= ~LED_PIN; /* Set LED_PIN low in GPIOA's output data register */

}

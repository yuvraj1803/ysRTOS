#include "LED.h"

#define GPIOAEN		(1U << 0) /* GPIOA Clock Access Enable Bit */
#define LED_PIN		(1U << 5) /* Using Pin 5 in GPIOA as LED_PIN */

void led_init(void){

	RCC -> AHB1ENR |= GPIOAEN; /* Enable clock access to GPIOA */

	/* set pin 5 in GPIOA as output pin */
	GPIOA -> MODER |= (1U << 10);
	GPIOA -> MODER &= ~(1U << 10);

}

void led_on(void){

	GPIOA -> ODR |= LED_PIN; /* Set LED_PIN high in GPIOA's output data register */
}

void led_off(void){
	// set LED pin LOW

	GPIOA -> ODR &= ~LED_PIN; /* Set LED_PIN low in GPIOA's output data register */

}

/**
 ******************************************************************************
 * @file           : EXTI.c
 * @author         : Yuvraj Sakshith
 * @brief          : External Interrupt Handler Initialisation
 ******************************************************************************
 ******************************************************************************
 */

#include "EXTI.h"

#define GPIOAEN				(1U << 0)
#define SYSCFGEN			(1U << 14)
#define EXTI13_PIN				3
#define EXTI_IMR_MR13		(1U << 13)
#define EXTI_FTSR_TR13		(1U << 13)

void EXTI13_INIT(void){

	/*
	 *
	 * GPIOA PIN 3 is used as an input source to EXTI13.
	 */

	__disable_irq();

	/* enable clock access to GPIOA and System Configuration Controller */
	RCC->AHB1ENR |= GPIOAEN;
	RCC->APB2ENR |= SYSCFGEN;

	/* set GPIOA pin 3 to input mode */
	GPIOA->MODER &= ~(1U << (2U*EXTI13_PIN));
	GPIOA->MODER &= ~(1U << (2U*EXTI13_PIN | 1));

	/* set GPIOA pin 3 as input source to EXT13 */
	SYSCFG->EXTICR[3] &= ~(0xE * (1U<<4));
	SYSCFG->EXTICR[3] |= EXTI13_PIN * (1U << 4);

	/* unmask EXTI13 and set falling edge trigger */
	EXTI->IMR |= EXTI_IMR_MR13;
	EXTI->FTSR |= EXTI_FTSR_TR13;

	NVIC_EnableIRQ(EXTI15_10_IRQn);

	__enable_irq();

}

void EXTI15_10_IRQHandler(void){

	EXTI->PR |= EXTI_PR13;
}

#include "ADC.h"

/**
 ******************************************************************************
 * @file           : ADC.c
 * @author         : Yuvraj Sakshith
 * @brief          : Analog to Digital Converter (ADC) Driver
 ******************************************************************************
 ******************************************************************************
 */

#define GPIOAEN		(1U << 0)

#define ADC1EN		(1U << 8);
#define ADC1ON		(1U << 0);
#define ADC1OFF			0
#define ADC1SWSTART	(1U << 30)
#define ADC1EOC		(1U << 1)

void ADC1_INIT(void){

	RCC->AHB1ENR |= GPIOAEN; /* enable clock for GPIOA */
	GPIOA->MODER |= ((1U << 2) | (1U << 3)); /* set pin 1 as analog, 2y:2y+1 */

	RCC->APB2ENR |= ADC1EN;
	ADC1->CR2 =  ADC1OFF;  	/* turn off ADC1 */
	ADC1->SQR3 = 1; 		/* conversion sequence start at channel 1*/
	ADC1->SQR1 = 0;			/* length of sequence is 1 */
	ADC1->CR2 |= ADC1ON;	/* turn on ADC1 */

}

uint32_t ADC1_READ(void){

	ADC1->CR2 |= ADC1SWSTART; /* begin conversation */

	while(!(ADC1->SR & ADC1EOC)){} /* wait for conversation to complete */


	return ADC1->DR;

}

void ENABLE_ADC1_SEQ(uint8_t SQn, uint8_t CHn){ /* Assigns Channel CHn to Sequence SQn */

}

void DISABLE_ADC1_SEQ(uint8_t SQn, uint8_t CHn){

}

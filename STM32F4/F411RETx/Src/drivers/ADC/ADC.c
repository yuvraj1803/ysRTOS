#include "ADC.h"

/**
 ******************************************************************************
 * @file           : ADC.c
 * @author         : Yuvraj Sakshith
 * @brief          : Analog to Digital Converter (ADC) Driver
 ******************************************************************************
 ******************************************************************************
 */


void adc1_init(void){

	RCC->AHB1ENR |= 1; /* enable clock for GPIOA */
	GPIOA->MODER |= 0xC; /* set pin 1 as analog */

	RCC->APB2ENR |= 0x00000100;
	ADC1->CR2 = 0;
	ADC1->SQR3 = 1; /* conversion sequence start at channel 1*/
	ADC1->SQR1 = 0; /* length of sequence is 1 */
	ADC1->CR2 |= 1;

}

uint32_t adc1_read(void){

	ADC1->CR2 |= 0x40000000; /* begin conversation */

	while(!(ADC1->SR & 2)){} /* wait for conversation to complete */


	return ADC1->DR;

}

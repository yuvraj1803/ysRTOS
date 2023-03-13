/**
 ******************************************************************************
 * @file           : UART.h
 * @author         : Yuvraj Sakshith
 * @brief          : UART Driver
 ******************************************************************************
 ******************************************************************************
 */

#ifndef __UART_H__
#define __UART_H__


#include "stm32f4xx.h"
#include "../../kernel/kernel.h"
#include "../../kernel/sem/semaphore.h"

void UART_INIT(void);
void uart_write(int ch);


#endif

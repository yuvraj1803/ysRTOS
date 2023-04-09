/**
 ******************************************************************************
 * @file           : LED.h
 * @author         : Yuvraj Sakshith
 * @brief          : LED Driver
 ******************************************************************************
 ******************************************************************************
 */

/*
 *
 * Copyright (c) 2023 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */

#ifndef __LED_H__
#define __LED_H__


#include "stm32f4xx.h"

#define LED_PIN		(1U << 5) /* Using Pin 5 in GPIOA as LED_PIN */


void LED_INIT(void);
void LED_ON(void);
void LED_OFF(void);

#endif

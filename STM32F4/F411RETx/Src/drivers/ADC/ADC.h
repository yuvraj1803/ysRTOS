#ifndef __ADC_H__
#define __ADC_H__

#include "stm32f4xx.h"

/**
 ******************************************************************************
 * @file           : ADC.h
 * @author         : Yuvraj Sakshith
 * @brief          : Analog to Digital Converter (ADC) Driver
 ******************************************************************************
 ******************************************************************************
 */

/*
 *
 * Copyright (c) 2023 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */

void ADC1_INIT(void);
uint32_t ADC1_READ(void);

#endif

/*
 ******************************************************************************
 * @file           : init.h
 * @author         : Yuvraj Sakshith
 * @brief          : OS Initialisation
 ******************************************************************************
 ******************************************************************************
 */

/*
 *
 * Copyright (c) 2023 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */

#ifndef __INIT_H__
#define __INIT_H__

#include "stm32f4xx.h"

#include "../drivers/LED/LED.h"
#include "../drivers/UART/UART.h"
#include "../drivers/ADC/ADC.h"
#include "../config/config.h"
#include "../kernel/kernel.h"
#include "../drivers/EXTI/EXTI.h"



void __init__(void);


#endif

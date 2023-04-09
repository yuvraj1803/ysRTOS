/*
 ******************************************************************************
 * @file           : sched.h
 * @author         : Yuvraj Sakshith
 * @brief          : Scheduler related function and hardware interrupt handlers
 ******************************************************************************
 ******************************************************************************
 */

/*
 *
 * Copyright (c) 2023 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */

#ifndef __SCHED_H__
#define	__SCHED_H__

#include "stm32f4xx.h"
#include "../../config/config.h"


void scheduler_launch(void);

void SysTick_Handler(void);
__attribute__((naked)) void PendSV_Handler(void);




#endif

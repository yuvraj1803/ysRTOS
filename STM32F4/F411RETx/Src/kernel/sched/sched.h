/*
 ******************************************************************************
 * @file           : sched.h
 * @author         : Yuvraj Sakshith
 * @brief          : Scheduler related function and hardware interrupt handlers
 ******************************************************************************
 ******************************************************************************
 */


#ifndef __SCHED_H__
#define	__SCHED_H__

#include "stm32f4xx.h"


void scheduler_launch(void);
__attribute__((naked)) void SysTick_Handler(void);
void cpu_yeild(void);


#endif

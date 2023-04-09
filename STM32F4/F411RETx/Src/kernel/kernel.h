
/*
 ******************************************************************************
 * @file           : kernel.h
 * @author         : Yuvraj Sakshith
 * @brief          : ysRTOS kernel
 ******************************************************************************
 ******************************************************************************
 */

/*
 *
 * Copyright (c) 2023 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */

#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "stm32f4xx.h"
#include "../config/config.h"
#include "tcb/tcb.h"
#include "sched/sched.h"
#include "../timers/tim2/tim2.h"
#include "sem/semaphore.h"

#include <stdlib.h>

void cpu_yeild(void);
void kernel_init(void);
void stk_init(uint32_t thread_id);
void kernel_launch(void);
tid_t add_thread(void (*thread)(void));
tid_t add_periodic_thread(void (*pthread)(void), uint32_t period);

extern TCB __tcbs__[MAX_THREADS + MAX_PERIODIC_THREADS];
extern uint32_t min_periodic_thread_id;
extern uint32_t max_periodic_thread_id;
extern TCB * __current_ptr__;
extern TCB * __current_periodic_ptr__;

extern uint32_t sys_counter;

extern uint32_t LED_sem;
extern uint32_t UART_sem;
extern uint32_t ADC1_sem;
extern uint32_t TIM2_sem;

#endif

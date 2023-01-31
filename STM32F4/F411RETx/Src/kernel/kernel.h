
/*
 ******************************************************************************
 * @file           : kernel.h
 * @author         : Yuvraj Sakshith
 * @brief          : ysRTOS kernel
 ******************************************************************************
 ******************************************************************************
 */

#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "stm32f4xx.h"
#include "../config/config.h"
#include "tm/tcb/tcb.h"
#include "sched/sched.h"
#include "../timers/tim2/tim2.h"

#include <stdlib.h>

void kernel_init(void);
void stk_init(uint32_t thread_id);
void kernel_launch(void);
void add_thread(void (*thread)(void));
void add_periodic_thread(void (*pthread)(void), uint32_t period);

extern TCB __tcbs__[MAX_THREADS + MAX_PERIODIC_THREADS];
extern uint32_t min_periodic_thread_id;
extern uint32_t max_periodic_thread_id;
extern TCB * __current_ptr__;

extern uint32_t sys_counter;


#endif

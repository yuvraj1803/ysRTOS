
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

#include <stdlib.h>

void kernel_init(void);
void stk_init(uint32_t thread_id);
void kernel_launch(void);
void add_thread(void (*thread)(void));

#endif

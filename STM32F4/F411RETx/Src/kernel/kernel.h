#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "stm32f4xx.h"

#include "../config/config.h"
#include "tm/tcb/tcb.h"

TCB __tcbs__[MAX_THREADS]; /* Thread control blocks */
TCB __current_ptr__; /* pointer to currently executing thread */

int32_t TCB_STACK[MAX_THREADS][STK_SIZE];
uint32_t MILLIS_PRESCALER;

void kernel_init(void);
void stk_init(void);
void kernel_launch(void);
void cpu_yeild(void);

#endif

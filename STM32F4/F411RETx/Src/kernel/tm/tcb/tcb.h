#ifndef __TCB_H__
#define __TCB_H__

#include "stm32f4xx.h"

/*
 *
 * TCB (Thread Control Block)
 * Basically has all the info about a thread that might be handled by the RTOS at some point of time.
 *
 * */

typedef struct tcb{
	int32_t * stackptr; /* Address of the stack pointer */
	struct tcb * nextthread; /* address of TCB of next thread */
	uint32_t sleeptime = 0;
}TCB;

#endif

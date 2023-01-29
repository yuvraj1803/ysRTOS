
/*
 ******************************************************************************
 * @file           : tcb.c
 * @author         : Yuvraj Sakshith
 * @brief          : Thread Control Block
 ******************************************************************************
 ******************************************************************************
 */


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

	/* Do not change the relative order of the variables declared below,
	 *  this will alter the context switch mechanism*/

	int32_t * stackptr; /* Address of the stack pointer */
	struct tcb * next_thread; /* address of TCB of next thread */

	/* Unrestricted below this line */

	uint32_t sleeptime;
	uint32_t thread_id;

}TCB;

#endif

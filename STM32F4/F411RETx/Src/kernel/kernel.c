#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "stm32f4xx.h"
#include "sched/scheduler.h"

void kernel_init(void){
	MILLIS_PRESCALER = (BUS_FREQ/1000); /*  for scaling milliseconds relative to the clock frequency.  */
}

void stk_init(void){
		__tcbs__[i].stackptr = &TCB_STACK[i][STACK_SIZE-16]; /* stack pointer */

		TCB_STACK[i][STACK_SIZE-1] = (1U << 24); /* enable 24'st bit to activate thumb mode */

		/* TCB_STACK[i][STACK_SIZE-2] => PC */

		/*
		// DUMMY STACK CONTENT
		TCB_STACK[i][STACK_SIZE-3] = 0xAAAAAAAA; // LR
		TCB_STACK[i][STACK_SIZE-4] = 0xAAAAAAAA; // R12
		TCB_STACK[i][STACK_SIZE-5] = 0xAAAAAAAA; // R3
		TCB_STACK[i][STACK_SIZE-6] = 0xAAAAAAAA; // R2
		TCB_STACK[i][STACK_SIZE-7] = 0xAAAAAAAA; // R1
		TCB_STACK[i][STACK_SIZE-8] = 0xAAAAAAAA; // R0

		TCB_STACK[i][STACK_SIZE-9] =  0xAAAAAAAA; // R11
		TCB_STACK[i][STACK_SIZE-10] = 0xAAAAAAAA; // R10
		TCB_STACK[i][STACK_SIZE-11] = 0xAAAAAAAA; // R9
		TCB_STACK[i][STACK_SIZE-12] = 0xAAAAAAAA; // R8
		TCB_STACK[i][STACK_SIZE-13] = 0xAAAAAAAA; // R7
		TCB_STACK[i][STACK_SIZE-14] = 0xAAAAAAAA; // R6
		TCB_STACK[i][STACK_SIZE-15] = 0xAAAAAAAA; // R5
		TCB_STACK[i][STACK_SIZE-16] = 0xAAAAAAAA; // R4

			(FOR DEBUGGING PURPOSES)
		*/
}

void kernel_launch(void){

		/*
		 *
		 * We mainly rely on the Round-Robin Scheduler. This is why we use the SysTick Handler for the context switches.
		 *
		 * We load the time quanta into the SysTick LOAD register and when it counts down to 0, we perform the context switch.
		 *
		 * */

		SysTick -> CTRL = CTRL_RESET; /* reset SysTick */

		SysTick -> VAL = 0; /* clear SysTick current value register */

		SysTick -> LOAD = (quanta * MILLIS_PRESCALER - 1); /* Load the quanta factored into milliseconds into the SysTick LOAD register */


		NVIC_SetPriority(SysTick_IRQn, 15); /* Set SysTick to low-priority */


		SysTick -> CTRL |= (CTRL_CLKSRC | CTRL_ENABLE); /* enable SysTick and select internal clock */


		SysTick -> CTRL |= CTRL_TICKINT; /* Enable interrupts */

		scheduler_launch();
}

#endif

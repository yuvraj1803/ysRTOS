
/*
 ******************************************************************************
 * @file           : kernel.c
 * @author         : Yuvraj Sakshith
 * @brief          : ysRTOS kernel
 ******************************************************************************
 ******************************************************************************
 */

#include "kernel.h"

/* for SysTick CTRL Register*/
#define CTRL_ENABLE			(1U << 0)
#define CTRL_TICKINT		(1U << 1)
#define CTRL_CLKSRC			(1U << 2)
#define CTRL_COUNTFLAG		(1U << 16)
#define CTRL_RESET				0


void kernel_init(void);
void stk_init(uint32_t);
void kernel_launch(void);
void add_thread(void (*thread)(void));


TCB __tcbs__[MAX_THREADS]; /* Thread control blocks */
TCB * __current_ptr__; /* pointer to currently executing thread */

int32_t TCB_STACK[MAX_THREADS][STACK_SIZE];
uint32_t MILLIS_PRESCALER;

uint32_t recently_added_thread_id; /* thread id of the most recently added thread*/

/*
 * Note: Thread ID is simply the index of the TCB_STACK in which the thread's content is stored.
 * */


void kernel_init(void){
	MILLIS_PRESCALER = (BUS_FREQ/1000); /*  for scaling milliseconds relative to the clock frequency.  */
	recently_added_thread_id = -1; /* no threads active currently */
}

void stk_init(uint32_t thread_id){

		__tcbs__[thread_id].stackptr = &TCB_STACK[thread_id][STACK_SIZE-16]; /* init stack pointer */
		__tcbs__[thread_id].thread_id = thread_id;

		TCB_STACK[thread_id][STACK_SIZE-1] = (1U << 24); /* enable 24th bit in PSR to activate thumb mode */

		/* TCB_STACK[i][STACK_SIZE-2] => PC */

		/*
		// DUMMY STACK CONTENT
		TCB_STACK[THREAD_NO][STACK_SIZE-3] = 0xAAAAAAAA; // LR
		TCB_STACK[THREAD_NO][STACK_SIZE-4] = 0xAAAAAAAA; // R12
		TCB_STACK[THREAD_NO][STACK_SIZE-5] = 0xAAAAAAAA; // R3
		TCB_STACK[THREAD_NO][STACK_SIZE-6] = 0xAAAAAAAA; // R2
		TCB_STACK[THREAD_NO][STACK_SIZE-7] = 0xAAAAAAAA; // R1
		TCB_STACK[THREAD_NO][STACK_SIZE-8] = 0xAAAAAAAA; // R0

		TCB_STACK[THREAD_NO][STACK_SIZE-9] =  0xAAAAAAAA; // R11
		TCB_STACK[THREAD_NO][STACK_SIZE-10] = 0xAAAAAAAA; // R10
		TCB_STACK[THREAD_NO][STACK_SIZE-11] = 0xAAAAAAAA; // R9
		TCB_STACK[THREAD_NO][STACK_SIZE-12] = 0xAAAAAAAA; // R8
		TCB_STACK[THREAD_NO][STACK_SIZE-13] = 0xAAAAAAAA; // R7
		TCB_STACK[THREAD_NO][STACK_SIZE-14] = 0xAAAAAAAA; // R6
		TCB_STACK[THREAD_NO][STACK_SIZE-15] = 0xAAAAAAAA; // R5
		TCB_STACK[THREAD_NO][STACK_SIZE-16] = 0xAAAAAAAA; // R4

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

void add_thread(void (*thread)(void)){
	if(recently_added_thread_id + 1 == MAX_THREADS){
		fprintf(stderr,"Cannot add thread %p, max thread limit reached",&thread);
		exit(__ADD_THREAD_FAILURE__);
	}

	uint32_t thread_id = recently_added_thread_id + 1; /* thread_id for the thread we are going to add */

	__disable_irq(); /* Disable global interrupts */

	__tcbs__[thread_id].sleeptime = 0;

	stk_init(thread_id); /* initialise the stack */
	TCB_STACK[thread_id][STACK_SIZE - 2] = (uint32_t) thread;  /* set the program counter to thread function's address */

	if(thread_id == 0){ 	/* If this is the first thread we are adding */
		__current_ptr__ = &__tcbs__[0];
		__tcbs__[0].next_thread = &__tcbs__[0];
	}else{

		/*Threads are linked in a circular linked list fashion. */
		__tcbs__[thread_id].next_thread = __tcbs__[recently_added_thread_id].next_thread;
		__tcbs__[recently_added_thread_id].next_thread = &__tcbs__[thread_id];

	}

	recently_added_thread_id = thread_id;

	__enable_irq(); /* Enable global interrupts */


}





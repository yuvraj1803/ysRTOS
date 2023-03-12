
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

/* System Handler Priority Register 3 */
#define SHPR3				*((volatile uint32_t * ) 0xE000ED20)


/*
 * We define a resource as a component of the board which can be accessed by one or more threads at
 * a given instance (at the same time).
 *
 * Defined below are semaphores for all the resources.
 *
 * */

/*I decided to define the semaphores here instead of the respective driver files
 * to keep the code more organised.
 * */

/* Initialised to 0 as none of them have been initialised at this moment in time */
uint32_t * LED_sem 	= 0;
uint32_t * UART_sem = 0;
uint32_t * ADC1_sem = 0;
uint32_t * TIM2_sem	= 0;



void kernel_init(void);
void stk_init(uint32_t);
void kernel_launch(void);
tid_t add_thread(void (*thread)(void));
tid_t add_periodic_thread(void (*pthread)(void), uint32_t period);


TCB __tcbs__[MAX_THREADS + MAX_PERIODIC_THREADS]; /* Thread control blocks */

TCB * __current_ptr__; /* pointer to currently executing thread */

int32_t TCB_STACK[MAX_THREADS + MAX_PERIODIC_THREADS][STACK_SIZE];
uint32_t MILLIS_PRESCALER;

uint32_t recently_added_thread_id; /* thread id of the most recently added thread*/
uint32_t recently_added_periodic_thread_id; /* thread id of the most recently added *periodic* thread*/
uint32_t min_thread_id;
uint32_t max_thread_id;

uint32_t min_periodic_thread_id;
uint32_t max_periodic_thread_id;

uint32_t sys_counter;          /* Keeps track of number of milliseconds elapsed. Handled by TIM2*/


/*
 * Note: Thread ID is simply the index of the TCB_STACK in which the thread's content is stored.
 * */

void _loop_(void){
	/*
	 * If no threads are given, __current_ptr__ shall point at this function and run here until 'something' is done ;)
	 * */
	while(1){}
}

void kernel_init(void){
	MILLIS_PRESCALER = (BUS_FREQ/1000); /*  for scaling milliseconds relative to the clock frequency.  */

	sys_counter = 0; /* reset */

	min_thread_id = 0;
	max_thread_id = MAX_THREADS - 1;

	min_periodic_thread_id = MAX_THREADS;
	max_periodic_thread_id = MAX_THREADS + MAX_PERIODIC_THREADS - 1;

	recently_added_thread_id = min_thread_id - 1; /* no threads active currently */
	recently_added_periodic_thread_id = min_periodic_thread_id - 1; /* no periodic threads active currently */

	__current_ptr__ = NULL;

}

void stk_init(uint32_t thread_id){

		__tcbs__[thread_id].stackptr = &TCB_STACK[thread_id][STACK_SIZE-16]; /* init stack pointer */


		TCB_STACK[thread_id][STACK_SIZE-1] = (1U << 24); /* enable 24th bit in PSR to activate thumb mode */

		/* TCB_STACK[i][STACK_SIZE-2] => PC */

		/*
		 *
		// DUMMY STACK CONTENT
		TCB_STACK[thread_id][STACK_SIZE-3] = 0xFFFFFFFF; // LR
		TCB_STACK[thread_id][STACK_SIZE-4] = 0xFFFFFFFF; // R12
		TCB_STACK[thread_id][STACK_SIZE-5] = 0xFFFFFFFF; // R3
		TCB_STACK[thread_id][STACK_SIZE-6] = 0xFFFFFFFF; // R2
		TCB_STACK[thread_id][STACK_SIZE-7] = 0xFFFFFFFF; // R1
		TCB_STACK[thread_id][STACK_SIZE-8] = 0xFFFFFFFF; // R0

		TCB_STACK[thread_id][STACK_SIZE-9] =  0xFFFFFFFF; // R11
		TCB_STACK[thread_id][STACK_SIZE-10] = 0xFFFFFFFF; // R10
		TCB_STACK[thread_id][STACK_SIZE-11] = 0xFFFFFFFF; // R9
		TCB_STACK[thread_id][STACK_SIZE-12] = 0xFFFFFFFF; // R8
		TCB_STACK[thread_id][STACK_SIZE-13] = 0xFFFFFFFF; // R7
		TCB_STACK[thread_id][STACK_SIZE-14] = 0xFFFFFFFF; // R6
		TCB_STACK[thread_id][STACK_SIZE-15] = 0xFFFFFFFF; // R5
		TCB_STACK[thread_id][STACK_SIZE-16] = 0xFFFFFFFF; // R4


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

		NVIC_SetPriority(SysTick_IRQn, SYSTICK_PRIO); /* Set SysTick to low-priority */
		NVIC_SetPriority(PendSV_IRQn,  PENDSV_PRIO); /* Set  PendSV to high-priority */

		SysTick -> CTRL |= (CTRL_CLKSRC | CTRL_ENABLE); /* enable SysTick and select internal clock */
		SysTick -> CTRL |= CTRL_TICKINT; /* Enable interrupts */


		


		/*
		 * We disable global interrupts here.
		 *
		 * This is done to stop TIM2_IRQHandler interrupting the scheduler launching process.
		 *
		 * Global interrupts are re-enabled in scheduler_launch() function.
		 *
		 * */

		__disable_irq();


		if(__TIM2_INIT__ == 0x1){

					/*
					 * All periodic threads rely on the TIM2_IRQHandler.
					 * Be very careful when modifying the value of __TIM2_INIT__ in config/config.h
					 *
					 * */

					tim2_1ms_interrupt_init();
		}


		if(__current_ptr__ == NULL){
			/* no threads specified, we spin in an infinite loop until processor is taken away */
			add_thread(&_loop_);
		}

		scheduler_launch();




}

tid_t add_thread(void (*thread)(void)){
	if(recently_added_thread_id == max_thread_id){
		fprintf(stderr,"Cannot add thread %p, max thread limit reached",&thread);
		exit(__ADD_THREAD_FAILURE__);
	}

	uint32_t thread_id = recently_added_thread_id + 1; /* thread_id for the thread we are going to add */

	__disable_irq(); /* Disable global interrupts */

	__tcbs__[thread_id].sleeptime = 0;
	__tcbs__[thread_id].thread_id = thread_id;
	__tcbs__[thread_id].period = 0xffffffff; /* non periodic threads */
	__tcbs__[thread_id].status = THREAD_ACTIVE;
	__tcbs__[thread_id].periodic_task = NULL;

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


	return thread_id;

}

tid_t add_periodic_thread(void (*pthread)(void), uint32_t period){
	/* pthread has nothing to do with posix threads.
	 *
	 * uint32_t period is measured in milliseconds.
	 *
	 *
	 * We shall be using TIM2 timer in the STM32F4 Board for measuring the time.
	 *
	 * TIM2_IRQHandler will be called when TIM2->CNT hits 0. This will initiate the context switching process.
	 *
	 *
	 * */

	if(recently_added_periodic_thread_id == max_periodic_thread_id){
		fprintf(stderr, "Cannot add periodic thread %p, max periodic thread limit reached", &pthread);
		exit(__ADD_PERIODIC_THREAD_FAILURE__);
	}

	uint32_t pthread_id = recently_added_periodic_thread_id + 1;

	__disable_irq();

	__tcbs__[pthread_id].sleeptime = 0;
	__tcbs__[pthread_id].thread_id = pthread_id;
	__tcbs__[pthread_id].period = period;
	__tcbs__[pthread_id].status = THREAD_ACTIVE;
	__tcbs__[pthread_id].periodic_task = pthread;

	stk_init(pthread_id);
	TCB_STACK[pthread_id][STACK_SIZE-2] = (uint32_t) pthread;

	recently_added_periodic_thread_id = pthread_id;

	__enable_irq();


	return pthread_id;

}





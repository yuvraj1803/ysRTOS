#include "tim2.h"

#define TIM2EN				(1U << 0)
#define	CR1_CEN				(1U << 0)
#define DIER_UIE			(1U << 0)
#define SR_UIF				(1U << 0)

/*	Interrupt Control and State Register	*/
#define	ICSR				*((volatile uint32_t * ) 0xE000ED04)
#define ICSR_PENDSTSET		(1U << 26)		/* SysTick Exception pending bit */

void tim2_1ms_interrupt_init(void){

	/*
	 * This initialises TIM2 to generate an interrupt every 1 millisecond.
	 * Every time the interrupt is generated, TIM2_IRQHandler is called.
	 *
	 * */


	RCC -> APB1ENR |= TIM2EN; /*enable clock access to tim2*/

	TIM2->PSC = 16000 - 1;	 /*Set timer prescaler*/
	TIM2->ARR = 10 - 1;	 	/*Set auto-reload value*/
	TIM2->CNT = 0;			 /*clear counter*/
	TIM2->CR1 = CR1_CEN;     /*Enable TIM2*/
	TIM2->DIER |= DIER_UIE;	 /*Enable timer interrupt*/

	NVIC_EnableIRQ(TIM2_IRQn); /*Enable timer interrupt in NVIC*/
}

void TIM2_IRQHandler(void){ /* TIM2 Interrupt Handler */

	sys_counter = (sys_counter + 1) % ticks_in_1ms; /* Increment this at every millisecond passed */

	TIM2->SR &= ~SR_UIF;	/* clear update interrupt flag */

	for(uint32_t current_thread_id =  min_periodic_thread_id;
			current_thread_id <= max_periodic_thread_id;
			current_thread_id++)
	{
		/*
		 * If the time has arrived for the thread w/ current_thread_id to execute, we shall preempt the currenly running
		 * thread and assign the periodic thread the processor.
		 *
		 * This thread shall run for time-period specified to the Round-Robin Scheduler.
		 *
		 * */
		if(sys_counter % __tcbs__[current_thread_id].period == 0 && __tcbs__[current_thread_id].status == THREAD_ACTIVE){


			/*
			 * Preempts the currently running thread.
			 * Gives the periodic thread, the CPU.
			 * After execution, for "quanta" time, we resume the normal scheduling from where we stopped.
			 *
			 * */

			__tcbs__[current_thread_id].next_thread = __current_ptr__->next_thread;
			__current_ptr__ = &__tcbs__[current_thread_id];

			/* yield the CPU */
			SysTick->VAL = 0; /* clear SysTick Current Value Register */
			ICSR |= ICSR_PENDSTSET; /* trigger SysTick */

		}
	}


}

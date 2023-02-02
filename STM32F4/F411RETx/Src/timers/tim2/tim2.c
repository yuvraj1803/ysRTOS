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

	TIM2->PSC = 1600 - 1;	 /*Set timer prescaler*/
	TIM2->ARR = 10 - 1;	 	/*Set auto-reload value*/
	TIM2->CNT = 0;			 /*clear counter*/
	TIM2->CR1 = CR1_CEN;     /*Enable TIM2*/
	TIM2->DIER |= DIER_UIE;	 /*Enable timer interrupt*/

	NVIC_EnableIRQ(TIM2_IRQn); /*Enable timer interrupt in NVIC*/
	NVIC_SetPriority(TIM2_IRQn,TIM2_PRIO);


}

void TIM2_IRQHandler(void){ /* TIM2 Interrupt Handler */

	sys_counter = (sys_counter + 1) % ticks_in_1ms; /* Increment this at every millisecond passed */

	TIM2->SR &= ~SR_UIF;	/* clear update interrupt flag */

	__disable_irq();

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
		if((__tcbs__[current_thread_id].status == THREAD_ACTIVE) &&
		   (__tcbs__[current_thread_id].period != 0)             &&		/* to avoid division by zero */
		   (sys_counter % __tcbs__[current_thread_id].period == 0)){

				SysTick->VAL = SysTick->LOAD;
				__tcbs__[current_thread_id].periodic_task();

		}
	}

	__enable_irq();

}

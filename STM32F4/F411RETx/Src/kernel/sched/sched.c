/*
 ******************************************************************************
 * @file           : sched.c
 * @author         : Yuvraj Sakshith
 * @brief          : Scheduler related function and hardware interrupt handlers
 ******************************************************************************
 ******************************************************************************
 */


#include "sched.h"

/*	Interrupt Control and State Register	*/
#define	ICSR				*((volatile uint32_t * ) 0xE000ED04)
#define ICSR_PENDSTSET		(1U << 26)		/* SysTick Exception pending bit */


void scheduler_launch(void){

	/*
	 *
	 * @brief	Loads the current thread into the CPU,
	 *  		initialises the Stack Pointer,
	 *			Restores all the registers from memory
	 *
	 * */

		__asm("LDR R0,=__current_ptr__");/* Load address of __current_ptr__ into R0 */
		__asm("LDR R2,[R0]");	/* Load R2 = __current_ptr__ */
		__asm("LDR SP, [R2]");	/* Load SP from __current_ptr__-> stackptr */
		__asm("POP {R4-R11}");	/* Restore R4-R11 */
		__asm("POP {R12}");		/* Restore R12 */
		__asm("POP {R0-R3}");	/* Restore R0-R3 */
		__asm("ADD SP,SP,#4");	/* Skip LR */
		__asm("POP {LR}");		/* create a new stop location by popping LR */
		__asm("ADD SP,SP,#4"); 	/* Skip PSR by adding 4 to SP */
		__asm("CPSIE I"); 		/* Enable global interrupts */
		__asm("BX LR");			/* Return from exception */

}



void cpu_yield(void){

	/* Voluntarily gives back the CPU to the next thread. */


		SysTick->VAL = 0; /* clear SysTick Current Value Register */
		ICSR |= ICSR_PENDSTSET; /* trigger SysTick */

}

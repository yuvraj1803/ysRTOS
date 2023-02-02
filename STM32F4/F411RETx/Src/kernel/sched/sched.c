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
#define ICSR_PENDSVSET		(1U << 28) 		/* PendSV  Exception pending bit*/


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

/*
 * Context switch is performed by the SysTick Handler(indirectly) which calls the PendSV handler.
 *
 * */

__attribute__((naked)) void PendSV_Handler(void){

	/* PendSV_Handler shall be handling the context switch process
	 * in the future versions of the RTOS.
	 */

}

__attribute__((naked)) void SysTick_Handler(void){

	/*
		 *  @brief
		 *  -> Suspends the current thread.
		 *  -> Saves all the Registers into the thread's stack.
		 *	-> Updates the Stack Pointer in the TCB.
		 *
		 *	-> Selects the next thread to be executed.
		 *	-> Update the Stack Pointer in the CPU with the new thread's SP.
		 *	-> Restore all the Registers.
		 * */

		/* SUSPEND CURRENT THREAD */

		__asm("CPSID I");		/* disable global interrupts */
		__asm("PUSH {R4-R11}");	/* save r4-r11 into the stack */
		__asm("LDR R0 ,=__current_ptr__");	/* load address of __current_ptr__ into r0 */
		__asm("LDR R1,[R0]");		/* load r1 from address stored in r0 i.e. r1 = __current_ptr__*/
		__asm("STR SP,[R1]");		/* store SP into r1 i.e. add SP to TCB*/


		/* CHOOSE NEXT THREAD */

		__asm("LDR R1,[R1,#4]");		/* load r1 from 4 bytes above r1 i.e. r1 = __current_ptr__->next */
		__asm("STR R1,[R0]");			/* store r1 at address equals r0 i.e. __current_ptr__ = r1 */
		__asm("LDR SP,[R1]");			/* update SP from address of r1 i.e. SP = cur__current_ptr__rentptr-> stackptr */
		__asm("POP {R4-R11}");			/* restore r4-r11 */
		__asm("CPSIE I");				/* enable global interrupts */
		__asm("BX LR");					/* return from exception and restore r0,r1,r2,r3,sp,lr,pc,psr */


		//	ICSR |= ICSR_PENDSVSET; /* Trigger the PendSV interrupt handler to perform the context switch.*/
}


void cpu_yield(void){

	/* Voluntarily gives back the CPU to the next thread. */


		SysTick->VAL = 0; /* clear SysTick Current Value Register */
		ICSR |= ICSR_PENDSTSET; /* trigger SysTick */

}

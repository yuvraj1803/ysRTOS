#include "../kernel.h"

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
	//
	//		__asm("push {r0-lr}");
	//		__asm("bl osSchedulerPeriodic"); // for the periodic scheduler
	//		__asm("pop {r0-lr}");

			__asm("LDR R1,[R1,#4]");		/* load r1 from 4 bytes above r1 i.e. r1 = __current_ptr__->next */
			__asm("STR R1,[R0]");			/* store r1 at address equals r0 i.e. __current_ptr__ = r1 */
			__asm("LDR SP,[R1]");			/* update SP from address of r1 i.e. SP = cur__current_ptr__rentptr-> stackptr */
			__asm("POP {R4-R11}");			/* restore r4-r11 */
			__asm("CPSIE I");				/* enable global interrupts */
			__asm("BX LR");					/* return from exception and restore r0,r1,r2,r3,sp,lr,pc,psr */
}

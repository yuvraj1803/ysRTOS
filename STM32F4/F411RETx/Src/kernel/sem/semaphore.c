
/*
 ******************************************************************************
 * @file           : semaphore.c
 * @author         : Yuvraj Sakshith
 * @brief          : Semaphores for exclusive access of resources.
 ******************************************************************************
 ******************************************************************************
 */


#include "semaphore.h"

/*
 * More like a co-operative semaphore.
 *
 * Waiting for a semaphore gives back the CPU instead of wasting clock-cycles in a spin lock.
 *
 * */


void semaphore_give(uint32_t * sem){
	__disable_irq();
	*sem += 1;
	__enable_irq();

}
void semaphore_wait(uint32_t * sem){
	__disable_irq();

	while(*sem <= 0){
		__disable_irq(); /* Spin lock */

//		cpu_yeild(); /* give back the CPU */

		__enable_irq();
	}
	*sem -= 1;

	__enable_irq();
}
void semaphore_init(uint32_t * sem, uint32_t value){
	*sem = value;
}

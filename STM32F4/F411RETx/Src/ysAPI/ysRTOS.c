#include "ysRTOS.h"


tid_t osAddThread(void (*thread)(void)){


	/*
	 * tid_t defined in config/config.h
	 *
	 * */

	tid_t thread_id = add_thread(thread);

	return thread_id;

}

tid_t osAddPeriodicThread(void (*thread)(void), uint32_t period){

	tid_t thread_id = add_periodic_thread(thread, period);

	return thread_id;

}

void osSemaphoreGive(uint32_t * semaphore){
	semaphore_give(semaphore);
}

void osSemaphoreWait(uint32_t * semaphore){
	semaphore_wait(semaphore);
}

void osSemaphoreInit(uint32_t * semaphore, uint32_t value){
	semaphore_init(semaphore, value);
}

void osLEDOn(){

}

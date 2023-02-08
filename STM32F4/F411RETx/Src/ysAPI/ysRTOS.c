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

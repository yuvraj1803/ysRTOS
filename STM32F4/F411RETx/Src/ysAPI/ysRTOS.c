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

void osLEDOn(void){


	if(__LED_INIT__ == 0){
		fprintf(stderr, "[FAILED] LED Driver Uninitialised");
		exit(__LED_DRIVER_UNINITIALISED__);
	}

	osSemaphoreWait(&LED_sem);

	LED_ON();

	osSemaphoreGive(&LED_sem);

}

void osLEDOff(void){


	if(__LED_INIT__ == 0){
		fprintf(stderr, "[FAILED] LED Driver Uninitialised");
		exit(__LED_DRIVER_UNINITIALISED__);
	}

	osSemaphoreWait(&LED_sem);

	LED_OFF();

	osSemaphoreGive(&LED_sem);

}

void osLEDToggle(void){
	if(__LED_INIT__ == 0){
			fprintf(stderr, "[FAILED] LED Driver Uninitialised");
			exit(__LED_DRIVER_UNINITIALISED__);
	}

	osSemaphoreWait(&LED_sem);

	if(GPIOA->ODR & LED_PIN){ /* If LED is ON*/
		osLEDOff();
	}else{
		osLEDOn();
	}

	osSemaphoreGive(&LED_sem);

}


uint32_t osADCRead(void){
	if(__ADC_INIT__ == 0){
		fprintf(stderr, "[FAILED] ADC1 Driver Uninitialised");
		exit(__ADC1_DRIVER_UNINITIALISED__);
	}

	osSemaphoreWait(&ADC1_sem);

	uint32_t adc_data = ADC1_READ();

	osSemaphoreGive(&ADC1_sem);

	return adc_data;

}



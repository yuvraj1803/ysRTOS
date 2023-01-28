#include "config.h"

/*
 *
 * @brief ysRTOS configuration API.
 *
 * Modify flags whose description is given in the documentation accordingly.
 *
 * */


void __SET_MAX_THREADS__(uint32_t val){
	if(RTOS_INITIALISED){
		perror("Kernel already initialised. Cannot update variable");
		exit(__SET_MAX_THREADS_FAIL__);
	}
	MAX_THREADS = val;
}

void __SET_STK_SIZE__(uint32_t stk_size){
	if(RTOS_INITIALISED){
		perror("Kernel already initialised. Cannot update variable");
		exit(__SET_STK_SIZE_FAIL__);
	}
	STK_SIZE = stk_size;
}


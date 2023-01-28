#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include "stm32f4xx.h"

void semaphore_give(uint32_t * sem);
void semaphore_wait(uint32_t * sem);
void semaphore_init(uint32_t * sem, uint32_t value);

#endif

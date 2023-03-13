#ifndef __YSRTOS_H__
#define __YSRTOS_H__

#include "stm32f4xx.h"

#include "../config/config.h"

#include "../kernel/kernel.h"
#include "../kernel/sem/semaphore.h"

#include "../drivers/LED/LED.h"
#include "../drivers/UART/UART.h"
#include "../drivers/ADC/ADC.h"

tid_t osAddThread(void (*thread)(void));
tid_t osAddPeriodicThread(void (*thread)(void), uint32_t period);

void osSemaphoreGive(uint32_t * semaphore);
void osSemaphoreWait(uint32_t * semaphore);
void osSemaphoreInit(uint32_t * semaphore, uint32_t value);

void osLEDOn(void);
void osLEDOff(void);
void osLEDToggle(void);

void osUARTWrite(int ch);

uint32_t osADCRead(void);

#endif

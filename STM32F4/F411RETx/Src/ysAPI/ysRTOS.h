#ifndef __YSRTOS_H__
#define __YSRTOS_H__

#include "stm32f4xx.h"
#include "../kernel/kernel.h"
#include "../config/config.h"

tid_t osAddThread(void (*thread)(void));
tid_t osAddPeriodicThread(void (*thread)(void), uint32_t period);

#endif

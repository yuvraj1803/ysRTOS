
/*
 ******************************************************************************
 * @file           : semaphore.h
 * @author         : Yuvraj Sakshith
 * @brief          : Semaphores for exclusive access of resources.
 ******************************************************************************
 ******************************************************************************
 */

/*
 *
 * Copyright (c) 2023 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */


#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include "stm32f4xx.h"
#include "../sched/sched.h"

void semaphore_give(uint32_t * sem);
void semaphore_wait(uint32_t * sem);
void semaphore_init(uint32_t * sem, uint32_t value);



#endif

# ysRTOS
 ysRTOS is a Real Time Operating System written specifically for microcontrollers equipped with ARM-Cortex-M4 processors.
 
 Board Support Packages shall be added in the future upon request or as an extention to some other project.

# Boards Supported
 + STM32F411REx

# RTOS Design and Architecture
 <img width="701" alt="block" src="https://user-images.githubusercontent.com/37622719/225209069-dfd4d340-ec9f-4a02-9e83-299d854d40e7.png">

# ysRTOS Kernel API Documentation
 + Threads and Scheduling
   + tid_t osAddThread(void (*thread)(void)) => creates a thread and returns its thread id.
   + tid_t osAddPeriodicThread(void (*thread)(void), uint32_t period) => creates a thread which runs once every 'period' milliseconds. Returns its thread id.
   + void osSemaphoreGive(uint32_t * semaphore) => increments given semaphore
   + void osSemaphoreWait(uint32_t * semaphore) => waits in a spin-lock for a given semaphore
   + void osSemaphoreInit(uint32_t * semaphore, uint32_t value) => initialises a given semaphore with a given value.
   
# How To Use
   + Download the latest release.
   + Create an empty STM32 project in your STM32 IDE(preferred).
   + Replace the Src folder in your project directory with the Src folder in the downloaded file.
   + Write your driver code in main.c

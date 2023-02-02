# Setting Up
 
 I suggest using STM32Cube IDE for making things a lot easier.

 **Setup**
 
 *(CMSIS can be found at ysRTOS/STM32F4/F411RETx)*
 
 1. Goto Project > Properties > Paths and Symbols > Includes
  
  ----------------------------------------------------------------------------------------
 	Click Add
  
 	Type -> **${ProjDirPath}/CMSIS/Device/ST/STM32F4xx/Include**
  
 	Click Ok
  
  ----------------------------------------------------------------------------------------

 	Click Add again,
  
 	Type -> **${ProjDirPath}/CMSIS/Include**
  
 	Click Ok
  
  ----------------------------------------------------------------------------------------

 2. Goto Project > Properties > Paths and Symbols > Symbols
   
  ---------------------------------------------------------------------------------------- 
 	Click Add
  
 	Type -> **STM32F411xE**
  
 	Click Ok
  ----------------------------------------------------------------------------------------
  
  # Startup
  
  **STM32F4** 
  *                - Set the initial SP
  *                - Set the initial PC == Reset_Handler,
  *                - Set the vector table entries with the exceptions ISR address
  *                - Branches to main in the C library (which eventually calls main())
  *                - Initialises drivers as specified in the config/config.h file.
  *                - Initialises the ysRTOS-kernel.
  *                - Adds threads.
  *                - Launches the kernel.

  # Reserved Hardware
  
  Some hardware components in the STM32F4 board are reserved for operating-system services.
  
  *(Make sure not to modify or reuse the below mentioned hardware. This can cause unnecessary runtime bugs to appear in the OS, which may be very hard to debug.)*
  
      * LED:     GPIOA PIN5 (PA5)
      * UART Tx: GPIOA PIN2 (PA2)
      * SysTick Timer
      * PendSV Interrupt Service
      * TIM2 Timer (used to manage Periodic Threads)
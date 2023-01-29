# ysRTOS
 ysRTOS is a Real Time Operating System written specifically for microcontrollers equipped with ARM-Cortex-M4 processors.
 Currently ysRTOS is only supported for the STM32F411RETx chips. There shall be more BSPs added in the future.

# Setting Up
 
 I suggest using STM32Cube IDE for making things a lot easier.

 **Setup**
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

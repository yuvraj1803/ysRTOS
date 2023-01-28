# ysRTOS
 ysRTOS is a Real Time Operating System

# Setting Up
 Currently ysRTOS is only supported for the STM32F411RETx chips. There shall be more BSPs added in the future.

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

################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/kernel/sem/semaphore.c 

OBJS += \
./Src/kernel/sem/semaphore.o 

C_DEPS += \
./Src/kernel/sem/semaphore.d 


# Each subdirectory must supply rules for building sources it contributes
Src/kernel/sem/%.o Src/kernel/sem/%.su: ../Src/kernel/sem/%.c Src/kernel/sem/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I"/Users/boju/Desktop/ysRTOS/ysRTOS/STM32F4/F411RETx/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/boju/Desktop/ysRTOS/ysRTOS/STM32F4/F411RETx/CMSIS/Include" -I"/Users/boju/Desktop/ysRTOS/ysRTOS/STM32F4/F411RETx" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-kernel-2f-sem

clean-Src-2f-kernel-2f-sem:
	-$(RM) ./Src/kernel/sem/semaphore.d ./Src/kernel/sem/semaphore.o ./Src/kernel/sem/semaphore.su

.PHONY: clean-Src-2f-kernel-2f-sem


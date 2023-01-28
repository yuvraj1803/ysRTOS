################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/drivers/LED/LED.c 

OBJS += \
./Src/drivers/LED/LED.o 

C_DEPS += \
./Src/drivers/LED/LED.d 


# Each subdirectory must supply rules for building sources it contributes
Src/drivers/LED/%.o Src/drivers/LED/%.su: ../Src/drivers/LED/%.c Src/drivers/LED/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I"/Users/boju/Desktop/ysRTOS/ysRTOS/STM32F4/F411RETx/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/boju/Desktop/ysRTOS/ysRTOS/STM32F4/F411RETx/CMSIS/Include" -I"/Users/boju/Desktop/ysRTOS/ysRTOS/STM32F4/F411RETx" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-drivers-2f-LED

clean-Src-2f-drivers-2f-LED:
	-$(RM) ./Src/drivers/LED/LED.d ./Src/drivers/LED/LED.o ./Src/drivers/LED/LED.su

.PHONY: clean-Src-2f-drivers-2f-LED


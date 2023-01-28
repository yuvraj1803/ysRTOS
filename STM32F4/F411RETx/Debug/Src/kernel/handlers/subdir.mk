################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Src/kernel/handlers/handlers.s 

OBJS += \
./Src/kernel/handlers/handlers.o 

S_DEPS += \
./Src/kernel/handlers/handlers.d 


# Each subdirectory must supply rules for building sources it contributes
Src/kernel/handlers/%.o: ../Src/kernel/handlers/%.s Src/kernel/handlers/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Src-2f-kernel-2f-handlers

clean-Src-2f-kernel-2f-handlers:
	-$(RM) ./Src/kernel/handlers/handlers.d ./Src/kernel/handlers/handlers.o

.PHONY: clean-Src-2f-kernel-2f-handlers


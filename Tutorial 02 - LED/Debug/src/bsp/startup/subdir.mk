################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../src/bsp/startup/startup_stm32h750vbtx.s 

OBJS += \
./src/bsp/startup/startup_stm32h750vbtx.o 

S_DEPS += \
./src/bsp/startup/startup_stm32h750vbtx.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/startup/%.o: ../src/bsp/startup/%.s src/bsp/startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"


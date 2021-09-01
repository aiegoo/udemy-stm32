################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ap/ap.c 

OBJS += \
./src/ap/ap.o 

C_DEPS += \
./src/ap/ap.d 


# Each subdirectory must supply rules for building sources it contributes
src/ap/%.o: ../src/ap/%.c src/ap/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -c -I"D:/STM32H750VB Projects/STM32_Proj_Basic/src" -I"D:/STM32H750VB Projects/STM32_Proj_Basic/src/ap" -I"D:/STM32H750VB Projects/STM32_Proj_Basic/src/bsp" -I"D:/STM32H750VB Projects/STM32_Proj_Basic/src/common" -I"D:/STM32H750VB Projects/STM32_Proj_Basic/src/hw" -I"D:/STM32H750VB Projects/STM32_Proj_Basic/src/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"


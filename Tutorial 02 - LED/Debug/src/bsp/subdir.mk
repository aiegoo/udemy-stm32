################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/bsp/bsp.c \
../src/bsp/syscalls.c \
../src/bsp/sysmem.c 

OBJS += \
./src/bsp/bsp.o \
./src/bsp/syscalls.o \
./src/bsp/sysmem.o 

C_DEPS += \
./src/bsp/bsp.d \
./src/bsp/syscalls.d \
./src/bsp/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
src/bsp/%.o: ../src/bsp/%.c src/bsp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -c -I"D:/STM32H750VB Projects/STM32-Tutorials/Tutorial 02 - LED/src" -I"D:/STM32H750VB Projects/STM32-Tutorials/Tutorial 02 - LED/src/ap" -I"D:/STM32H750VB Projects/STM32-Tutorials/Tutorial 02 - LED/src/bsp" -I"D:/STM32H750VB Projects/STM32-Tutorials/Tutorial 02 - LED/src/common" -I"D:/STM32H750VB Projects/STM32-Tutorials/Tutorial 02 - LED/src/hw" -I"D:/STM32H750VB Projects/STM32-Tutorials/Tutorial 02 - LED/src/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"


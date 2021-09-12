################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/source/driver/uart.c 

OBJS += \
./Application/source/driver/uart.o 

C_DEPS += \
./Application/source/driver/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Application/source/driver/%.o: ../Application/source/driver/%.c Application/source/driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/STM32_DEMO/STM32-Tutorials/Tutorial 100 - UART_RingBuffer/Application/config" -I"C:/STM32_DEMO/STM32-Tutorials/Tutorial 100 - UART_RingBuffer/Application/include/driver" -I"C:/STM32_DEMO/STM32-Tutorials/Tutorial 100 - UART_RingBuffer/Application/include/module" -I"C:/STM32_DEMO/STM32-Tutorials/Tutorial 100 - UART_RingBuffer/Application/include/utility" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


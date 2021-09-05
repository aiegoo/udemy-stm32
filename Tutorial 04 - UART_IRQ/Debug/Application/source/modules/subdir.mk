################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/source/modules/blinking.c 

OBJS += \
./Application/source/modules/blinking.o 

C_DEPS += \
./Application/source/modules/blinking.d 


# Each subdirectory must supply rules for building sources it contributes
Application/source/modules/%.o: ../Application/source/modules/%.c Application/source/modules/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/STM32_DEMO/STM32-Tutorials/Tuto-03_UART/Application/include/drivers" -I"C:/STM32_DEMO/STM32-Tutorials/Tuto-03_UART/Application/include/modules" -I"C:/STM32_DEMO/STM32-Tutorials/Tuto-03_UART/Application/include/util" -I"C:/STM32_DEMO/STM32-Tutorials/Tuto-03_UART/Core/config" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


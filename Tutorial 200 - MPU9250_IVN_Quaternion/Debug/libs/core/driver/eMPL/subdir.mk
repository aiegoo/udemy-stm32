################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libs/core/driver/eMPL/inv_mpu.c \
../libs/core/driver/eMPL/inv_mpu_dmp_motion_driver.c 

OBJS += \
./libs/core/driver/eMPL/inv_mpu.o \
./libs/core/driver/eMPL/inv_mpu_dmp_motion_driver.o 

C_DEPS += \
./libs/core/driver/eMPL/inv_mpu.d \
./libs/core/driver/eMPL/inv_mpu_dmp_motion_driver.d 


# Each subdirectory must supply rules for building sources it contributes
libs/core/driver/eMPL/%.o: ../libs/core/driver/eMPL/%.c libs/core/driver/eMPL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -DEMPL_TARGET_STM32F4 -DMPU9250 -DEMPL -DUSE_DMP -DARM_MATH_CM4 -DEMPL_TARGET_STM32F4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/STM32_DEMO/STM32-Tutorials/Tutorial 200 - MPU9250_IVN_Quaternion/Application/config" -I"C:/STM32_DEMO/STM32-Tutorials/Tutorial 200 - MPU9250_IVN_Quaternion/Application/include/driver" -I"C:/STM32_DEMO/STM32-Tutorials/Tutorial 200 - MPU9250_IVN_Quaternion/Application/include/module" -I"C:/STM32_DEMO/STM32-Tutorials/Tutorial 200 - MPU9250_IVN_Quaternion/Application/include/utility" -I"C:/STM32_DEMO/STM32-Tutorials/Tutorial 200 - MPU9250_IVN_Quaternion/libs/core/driver/eMPL" -I"C:/STM32_DEMO/STM32-Tutorials/Tutorial 200 - MPU9250_IVN_Quaternion/libs/core/driver/include" -I"C:/STM32_DEMO/STM32-Tutorials/Tutorial 200 - MPU9250_IVN_Quaternion/libs/core/driver/stm32L" -I"C:/STM32_DEMO/STM32-Tutorials/Tutorial 200 - MPU9250_IVN_Quaternion/libs/core/eMPL-hal" -I"C:/STM32_DEMO/STM32-Tutorials/Tutorial 200 - MPU9250_IVN_Quaternion/libs/core/mllite" -I"C:/STM32_DEMO/STM32-Tutorials/Tutorial 200 - MPU9250_IVN_Quaternion/libs/core/mpl" -I"C:/STM32_DEMO/STM32-Tutorials/Tutorial 200 - MPU9250_IVN_Quaternion/libs/core/mpl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


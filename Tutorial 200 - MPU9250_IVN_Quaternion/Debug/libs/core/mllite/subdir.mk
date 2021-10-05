################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libs/core/mllite/data_builder.c \
../libs/core/mllite/hal_outputs.c \
../libs/core/mllite/message_layer.c \
../libs/core/mllite/ml_math_func.c \
../libs/core/mllite/mlmath.c \
../libs/core/mllite/mpl.c \
../libs/core/mllite/results_holder.c \
../libs/core/mllite/start_manager.c \
../libs/core/mllite/storage_manager.c 

OBJS += \
./libs/core/mllite/data_builder.o \
./libs/core/mllite/hal_outputs.o \
./libs/core/mllite/message_layer.o \
./libs/core/mllite/ml_math_func.o \
./libs/core/mllite/mlmath.o \
./libs/core/mllite/mpl.o \
./libs/core/mllite/results_holder.o \
./libs/core/mllite/start_manager.o \
./libs/core/mllite/storage_manager.o 

C_DEPS += \
./libs/core/mllite/data_builder.d \
./libs/core/mllite/hal_outputs.d \
./libs/core/mllite/message_layer.d \
./libs/core/mllite/ml_math_func.d \
./libs/core/mllite/mlmath.d \
./libs/core/mllite/mpl.d \
./libs/core/mllite/results_holder.d \
./libs/core/mllite/start_manager.d \
./libs/core/mllite/storage_manager.d 


# Each subdirectory must supply rules for building sources it contributes
libs/core/mllite/%.o: ../libs/core/mllite/%.c libs/core/mllite/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -DEMPL_TARGET_STM32F4 -DMPU9250 -DEMPL -DUSE_DMP -DARM_MATH_CM4 -DEMPL_TARGET_STM32F4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/STM32_DEMO/STM32-Tutorials/Tutorial 200 - MPU9250_IVN_Quaternion/Application/config" -I"C:/STM32_DEMO/STM32-Tutorials/Tutorial 200 - MPU9250_IVN_Quaternion/Application/include/driver" -I"C:/STM32_DEMO/STM32-Tutorials/Tutorial 200 - MPU9250_IVN_Quaternion/Application/include/module" -I"C:/STM32_DEMO/STM32-Tutorials/Tutorial 200 - MPU9250_IVN_Quaternion/Application/include/utility" -I"C:/STM32_DEMO/STM32-Tutorials/Tutorial 200 - MPU9250_IVN_Quaternion/libs/core/driver/eMPL" -I"C:/STM32_DEMO/STM32-Tutorials/Tutorial 200 - MPU9250_IVN_Quaternion/libs/core/driver/include" -I"C:/STM32_DEMO/STM32-Tutorials/Tutorial 200 - MPU9250_IVN_Quaternion/libs/core/driver/stm32L" -I"C:/STM32_DEMO/STM32-Tutorials/Tutorial 200 - MPU9250_IVN_Quaternion/libs/core/eMPL-hal" -I"C:/STM32_DEMO/STM32-Tutorials/Tutorial 200 - MPU9250_IVN_Quaternion/libs/core/mllite" -I"C:/STM32_DEMO/STM32-Tutorials/Tutorial 200 - MPU9250_IVN_Quaternion/libs/core/mpl" -I"C:/STM32_DEMO/STM32-Tutorials/Tutorial 200 - MPU9250_IVN_Quaternion/libs/core/mpl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


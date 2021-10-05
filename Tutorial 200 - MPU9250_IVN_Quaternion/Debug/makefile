################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include libs/core/mllite/subdir.mk
-include libs/core/eMPL-hal/subdir.mk
-include libs/core/driver/stm32L/subdir.mk
-include libs/core/driver/eMPL/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Application/source/utility/subdir.mk
-include Application/source/driver/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Tutorial 200 - MPU9250_IVN_Quaternion
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Tutorial\ 200\ -\ MPU9250_IVN_Quaternion.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Tutorial\ 200\ -\ MPU9250_IVN_Quaternion.list \

OBJCOPY_BIN += \
Tutorial\ 200\ -\ MPU9250_IVN_Quaternion.bin \


# All Target
all: main-build

# Main-build Target
main-build: Tutorial\ 200\ -\ MPU9250_IVN_Quaternion.elf secondary-outputs

# Tool invocations
Tutorial\ 200\ -\ MPU9250_IVN_Quaternion.elf: $(OBJS) $(USER_OBJS) C:\STM32_DEMO\STM32-Tutorials\Tutorial\ 200\ -\ MPU9250_IVN_Quaternion\STM32F429ZITX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Tutorial 200 - MPU9250_IVN_Quaternion.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\STM32_DEMO\STM32-Tutorials\Tutorial 200 - MPU9250_IVN_Quaternion\STM32F429ZITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Tutorial 200 - MPU9250_IVN_Quaternion.map" -Wl,--gc-sections -static -u_printf_float --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Tutorial\ 200\ -\ MPU9250_IVN_Quaternion.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Tutorial 200 - MPU9250_IVN_Quaternion.list"
	@echo 'Finished building: $@'
	@echo ' '

Tutorial\ 200\ -\ MPU9250_IVN_Quaternion.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Tutorial 200 - MPU9250_IVN_Quaternion.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SIZE_OUTPUT)$(OBJDUMP_LIST)$(EXECUTABLES)$(OBJS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS)$(OBJCOPY_BIN) "Tutorial 200 - MPU9250_IVN_Quaternion.elf"
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets

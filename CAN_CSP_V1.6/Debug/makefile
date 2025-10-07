################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Tests/subdir.mk
-include Services/Logger/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include CSP_V1/libcsp/src/transport/subdir.mk
-include CSP_V1/libcsp/src/rtable/subdir.mk
-include CSP_V1/libcsp/src/interfaces/subdir.mk
-include CSP_V1/libcsp/src/drivers/usart/subdir.mk
-include CSP_V1/libcsp/src/drivers/can/subdir.mk
-include CSP_V1/libcsp/src/crypto/subdir.mk
-include CSP_V1/libcsp/src/bindings/python/subdir.mk
-include CSP_V1/libcsp/src/arch/windows/subdir.mk
-include CSP_V1/libcsp/src/arch/posix/subdir.mk
-include CSP_V1/libcsp/src/arch/macosx/subdir.mk
-include CSP_V1/libcsp/src/arch/freertos/subdir.mk
-include CSP_V1/libcsp/src/arch/subdir.mk
-include CSP_V1/libcsp/src/subdir.mk
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


BUILD_ARTIFACT_NAME := CAN_CSP_V1
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
CAN_CSP_V1.elf \

MAP_FILES += \
CAN_CSP_V1.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
CAN_CSP_V1.list \


# All Target
all: main-build

# Main-build Target
main-build: CAN_CSP_V1.elf secondary-outputs

# Tool invocations
CAN_CSP_V1.elf CAN_CSP_V1.map: $(OBJS) $(USER_OBJS) C:\Users\hoang\STM32CubeIDE\workspace_1.19.0\CAN_CSP_V1\STM32F405RGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "CAN_CSP_V1.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\hoang\STM32CubeIDE\workspace_1.19.0\CAN_CSP_V1\STM32F405RGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="CAN_CSP_V1.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

CAN_CSP_V1.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "CAN_CSP_V1.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) CAN_CSP_V1.elf CAN_CSP_V1.list CAN_CSP_V1.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets

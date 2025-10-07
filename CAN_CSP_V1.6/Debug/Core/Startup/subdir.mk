################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f405rgtx.s 

OBJS += \
./Core/Startup/startup_stm32f405rgtx.o 

S_DEPS += \
./Core/Startup/startup_stm32f405rgtx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/Services/Logger" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include/csp" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include/csp/arch" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include/csp/arch/posix" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include/csp/crypto" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include/csp/drivers" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include/csp/interfaces" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/arch" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/arch/freertos" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/crypto" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/interfaces" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/rtable" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/transport" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/Tests" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/Tests/CSP_CAN_STM32" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/arch/macosx" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/arch/posix" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/arch/windows" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/bindings" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/bindings/python" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/drivers" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/drivers/can" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/drivers/usart" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f405rgtx.d ./Core/Startup/startup_stm32f405rgtx.o

.PHONY: clean-Core-2f-Startup


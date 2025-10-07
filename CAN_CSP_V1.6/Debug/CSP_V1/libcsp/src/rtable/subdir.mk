################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CSP_V1/libcsp/src/rtable/csp_rtable.c \
../CSP_V1/libcsp/src/rtable/csp_rtable_cidr.c \
../CSP_V1/libcsp/src/rtable/csp_rtable_static.c 

OBJS += \
./CSP_V1/libcsp/src/rtable/csp_rtable.o \
./CSP_V1/libcsp/src/rtable/csp_rtable_cidr.o \
./CSP_V1/libcsp/src/rtable/csp_rtable_static.o 

C_DEPS += \
./CSP_V1/libcsp/src/rtable/csp_rtable.d \
./CSP_V1/libcsp/src/rtable/csp_rtable_cidr.d \
./CSP_V1/libcsp/src/rtable/csp_rtable_static.d 


# Each subdirectory must supply rules for building sources it contributes
CSP_V1/libcsp/src/rtable/%.o CSP_V1/libcsp/src/rtable/%.su CSP_V1/libcsp/src/rtable/%.cyclo: ../CSP_V1/libcsp/src/rtable/%.c CSP_V1/libcsp/src/rtable/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/Services/Logger" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include/csp" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include/csp/arch" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include/csp/arch/posix" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include/csp/crypto" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include/csp/drivers" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include/csp/interfaces" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/arch" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/arch/freertos" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/crypto" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/interfaces" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/rtable" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/transport" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/Tests" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/Tests/CSP_CAN_STM32" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/arch/macosx" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/arch/posix" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/arch/windows" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/bindings" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/bindings/python" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/drivers" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/drivers/can" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/drivers/usart" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CSP_V1-2f-libcsp-2f-src-2f-rtable

clean-CSP_V1-2f-libcsp-2f-src-2f-rtable:
	-$(RM) ./CSP_V1/libcsp/src/rtable/csp_rtable.cyclo ./CSP_V1/libcsp/src/rtable/csp_rtable.d ./CSP_V1/libcsp/src/rtable/csp_rtable.o ./CSP_V1/libcsp/src/rtable/csp_rtable.su ./CSP_V1/libcsp/src/rtable/csp_rtable_cidr.cyclo ./CSP_V1/libcsp/src/rtable/csp_rtable_cidr.d ./CSP_V1/libcsp/src/rtable/csp_rtable_cidr.o ./CSP_V1/libcsp/src/rtable/csp_rtable_cidr.su ./CSP_V1/libcsp/src/rtable/csp_rtable_static.cyclo ./CSP_V1/libcsp/src/rtable/csp_rtable_static.d ./CSP_V1/libcsp/src/rtable/csp_rtable_static.o ./CSP_V1/libcsp/src/rtable/csp_rtable_static.su

.PHONY: clean-CSP_V1-2f-libcsp-2f-src-2f-rtable


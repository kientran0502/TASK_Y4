################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CSP_V1/libcsp/src/arch/freertos/csp_clock.c \
../CSP_V1/libcsp/src/arch/freertos/csp_malloc.c \
../CSP_V1/libcsp/src/arch/freertos/csp_queue.c \
../CSP_V1/libcsp/src/arch/freertos/csp_semaphore.c \
../CSP_V1/libcsp/src/arch/freertos/csp_system.c \
../CSP_V1/libcsp/src/arch/freertos/csp_thread.c \
../CSP_V1/libcsp/src/arch/freertos/csp_time.c 

OBJS += \
./CSP_V1/libcsp/src/arch/freertos/csp_clock.o \
./CSP_V1/libcsp/src/arch/freertos/csp_malloc.o \
./CSP_V1/libcsp/src/arch/freertos/csp_queue.o \
./CSP_V1/libcsp/src/arch/freertos/csp_semaphore.o \
./CSP_V1/libcsp/src/arch/freertos/csp_system.o \
./CSP_V1/libcsp/src/arch/freertos/csp_thread.o \
./CSP_V1/libcsp/src/arch/freertos/csp_time.o 

C_DEPS += \
./CSP_V1/libcsp/src/arch/freertos/csp_clock.d \
./CSP_V1/libcsp/src/arch/freertos/csp_malloc.d \
./CSP_V1/libcsp/src/arch/freertos/csp_queue.d \
./CSP_V1/libcsp/src/arch/freertos/csp_semaphore.d \
./CSP_V1/libcsp/src/arch/freertos/csp_system.d \
./CSP_V1/libcsp/src/arch/freertos/csp_thread.d \
./CSP_V1/libcsp/src/arch/freertos/csp_time.d 


# Each subdirectory must supply rules for building sources it contributes
CSP_V1/libcsp/src/arch/freertos/%.o CSP_V1/libcsp/src/arch/freertos/%.su CSP_V1/libcsp/src/arch/freertos/%.cyclo: ../CSP_V1/libcsp/src/arch/freertos/%.c CSP_V1/libcsp/src/arch/freertos/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/Services/Logger" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include/csp" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include/csp/arch" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include/csp/arch/posix" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include/csp/crypto" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include/csp/drivers" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include/csp/interfaces" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/arch" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/arch/freertos" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/crypto" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/interfaces" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/rtable" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/transport" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/Tests" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/Tests/CSP_CAN_STM32" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/arch/macosx" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/arch/posix" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/arch/windows" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/bindings" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/bindings/python" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/drivers" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/drivers/can" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/drivers/usart" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CSP_V1-2f-libcsp-2f-src-2f-arch-2f-freertos

clean-CSP_V1-2f-libcsp-2f-src-2f-arch-2f-freertos:
	-$(RM) ./CSP_V1/libcsp/src/arch/freertos/csp_clock.cyclo ./CSP_V1/libcsp/src/arch/freertos/csp_clock.d ./CSP_V1/libcsp/src/arch/freertos/csp_clock.o ./CSP_V1/libcsp/src/arch/freertos/csp_clock.su ./CSP_V1/libcsp/src/arch/freertos/csp_malloc.cyclo ./CSP_V1/libcsp/src/arch/freertos/csp_malloc.d ./CSP_V1/libcsp/src/arch/freertos/csp_malloc.o ./CSP_V1/libcsp/src/arch/freertos/csp_malloc.su ./CSP_V1/libcsp/src/arch/freertos/csp_queue.cyclo ./CSP_V1/libcsp/src/arch/freertos/csp_queue.d ./CSP_V1/libcsp/src/arch/freertos/csp_queue.o ./CSP_V1/libcsp/src/arch/freertos/csp_queue.su ./CSP_V1/libcsp/src/arch/freertos/csp_semaphore.cyclo ./CSP_V1/libcsp/src/arch/freertos/csp_semaphore.d ./CSP_V1/libcsp/src/arch/freertos/csp_semaphore.o ./CSP_V1/libcsp/src/arch/freertos/csp_semaphore.su ./CSP_V1/libcsp/src/arch/freertos/csp_system.cyclo ./CSP_V1/libcsp/src/arch/freertos/csp_system.d ./CSP_V1/libcsp/src/arch/freertos/csp_system.o ./CSP_V1/libcsp/src/arch/freertos/csp_system.su ./CSP_V1/libcsp/src/arch/freertos/csp_thread.cyclo ./CSP_V1/libcsp/src/arch/freertos/csp_thread.d ./CSP_V1/libcsp/src/arch/freertos/csp_thread.o ./CSP_V1/libcsp/src/arch/freertos/csp_thread.su ./CSP_V1/libcsp/src/arch/freertos/csp_time.cyclo ./CSP_V1/libcsp/src/arch/freertos/csp_time.d ./CSP_V1/libcsp/src/arch/freertos/csp_time.o ./CSP_V1/libcsp/src/arch/freertos/csp_time.su

.PHONY: clean-CSP_V1-2f-libcsp-2f-src-2f-arch-2f-freertos


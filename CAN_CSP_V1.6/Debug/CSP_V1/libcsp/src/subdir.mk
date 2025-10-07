################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CSP_V1/libcsp/src/csp_bridge.c \
../CSP_V1/libcsp/src/csp_buffer.c \
../CSP_V1/libcsp/src/csp_conn.c \
../CSP_V1/libcsp/src/csp_crc32.c \
../CSP_V1/libcsp/src/csp_debug.c \
../CSP_V1/libcsp/src/csp_dedup.c \
../CSP_V1/libcsp/src/csp_endian.c \
../CSP_V1/libcsp/src/csp_hex_dump.c \
../CSP_V1/libcsp/src/csp_iflist.c \
../CSP_V1/libcsp/src/csp_init.c \
../CSP_V1/libcsp/src/csp_io.c \
../CSP_V1/libcsp/src/csp_port.c \
../CSP_V1/libcsp/src/csp_promisc.c \
../CSP_V1/libcsp/src/csp_qfifo.c \
../CSP_V1/libcsp/src/csp_route.c \
../CSP_V1/libcsp/src/csp_service_handler.c \
../CSP_V1/libcsp/src/csp_services.c \
../CSP_V1/libcsp/src/csp_sfp.c 

OBJS += \
./CSP_V1/libcsp/src/csp_bridge.o \
./CSP_V1/libcsp/src/csp_buffer.o \
./CSP_V1/libcsp/src/csp_conn.o \
./CSP_V1/libcsp/src/csp_crc32.o \
./CSP_V1/libcsp/src/csp_debug.o \
./CSP_V1/libcsp/src/csp_dedup.o \
./CSP_V1/libcsp/src/csp_endian.o \
./CSP_V1/libcsp/src/csp_hex_dump.o \
./CSP_V1/libcsp/src/csp_iflist.o \
./CSP_V1/libcsp/src/csp_init.o \
./CSP_V1/libcsp/src/csp_io.o \
./CSP_V1/libcsp/src/csp_port.o \
./CSP_V1/libcsp/src/csp_promisc.o \
./CSP_V1/libcsp/src/csp_qfifo.o \
./CSP_V1/libcsp/src/csp_route.o \
./CSP_V1/libcsp/src/csp_service_handler.o \
./CSP_V1/libcsp/src/csp_services.o \
./CSP_V1/libcsp/src/csp_sfp.o 

C_DEPS += \
./CSP_V1/libcsp/src/csp_bridge.d \
./CSP_V1/libcsp/src/csp_buffer.d \
./CSP_V1/libcsp/src/csp_conn.d \
./CSP_V1/libcsp/src/csp_crc32.d \
./CSP_V1/libcsp/src/csp_debug.d \
./CSP_V1/libcsp/src/csp_dedup.d \
./CSP_V1/libcsp/src/csp_endian.d \
./CSP_V1/libcsp/src/csp_hex_dump.d \
./CSP_V1/libcsp/src/csp_iflist.d \
./CSP_V1/libcsp/src/csp_init.d \
./CSP_V1/libcsp/src/csp_io.d \
./CSP_V1/libcsp/src/csp_port.d \
./CSP_V1/libcsp/src/csp_promisc.d \
./CSP_V1/libcsp/src/csp_qfifo.d \
./CSP_V1/libcsp/src/csp_route.d \
./CSP_V1/libcsp/src/csp_service_handler.d \
./CSP_V1/libcsp/src/csp_services.d \
./CSP_V1/libcsp/src/csp_sfp.d 


# Each subdirectory must supply rules for building sources it contributes
CSP_V1/libcsp/src/%.o CSP_V1/libcsp/src/%.su CSP_V1/libcsp/src/%.cyclo: ../CSP_V1/libcsp/src/%.c CSP_V1/libcsp/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/Services/Logger" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include/csp" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include/csp/arch" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include/csp/arch/posix" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include/csp/crypto" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include/csp/drivers" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/include/csp/interfaces" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/arch" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/arch/freertos" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/crypto" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/interfaces" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/rtable" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/transport" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/Tests" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/Tests/CSP_CAN_STM32" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/arch/macosx" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/arch/posix" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/arch/windows" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/bindings" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/bindings/python" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/drivers" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/drivers/can" -I"C:/Users/hoang/STM32CubeIDE/workspace_1.19.0/CAN_CSP_V1/CSP_V1/libcsp/src/drivers/usart" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CSP_V1-2f-libcsp-2f-src

clean-CSP_V1-2f-libcsp-2f-src:
	-$(RM) ./CSP_V1/libcsp/src/csp_bridge.cyclo ./CSP_V1/libcsp/src/csp_bridge.d ./CSP_V1/libcsp/src/csp_bridge.o ./CSP_V1/libcsp/src/csp_bridge.su ./CSP_V1/libcsp/src/csp_buffer.cyclo ./CSP_V1/libcsp/src/csp_buffer.d ./CSP_V1/libcsp/src/csp_buffer.o ./CSP_V1/libcsp/src/csp_buffer.su ./CSP_V1/libcsp/src/csp_conn.cyclo ./CSP_V1/libcsp/src/csp_conn.d ./CSP_V1/libcsp/src/csp_conn.o ./CSP_V1/libcsp/src/csp_conn.su ./CSP_V1/libcsp/src/csp_crc32.cyclo ./CSP_V1/libcsp/src/csp_crc32.d ./CSP_V1/libcsp/src/csp_crc32.o ./CSP_V1/libcsp/src/csp_crc32.su ./CSP_V1/libcsp/src/csp_debug.cyclo ./CSP_V1/libcsp/src/csp_debug.d ./CSP_V1/libcsp/src/csp_debug.o ./CSP_V1/libcsp/src/csp_debug.su ./CSP_V1/libcsp/src/csp_dedup.cyclo ./CSP_V1/libcsp/src/csp_dedup.d ./CSP_V1/libcsp/src/csp_dedup.o ./CSP_V1/libcsp/src/csp_dedup.su ./CSP_V1/libcsp/src/csp_endian.cyclo ./CSP_V1/libcsp/src/csp_endian.d ./CSP_V1/libcsp/src/csp_endian.o ./CSP_V1/libcsp/src/csp_endian.su ./CSP_V1/libcsp/src/csp_hex_dump.cyclo ./CSP_V1/libcsp/src/csp_hex_dump.d ./CSP_V1/libcsp/src/csp_hex_dump.o ./CSP_V1/libcsp/src/csp_hex_dump.su ./CSP_V1/libcsp/src/csp_iflist.cyclo ./CSP_V1/libcsp/src/csp_iflist.d ./CSP_V1/libcsp/src/csp_iflist.o ./CSP_V1/libcsp/src/csp_iflist.su ./CSP_V1/libcsp/src/csp_init.cyclo ./CSP_V1/libcsp/src/csp_init.d ./CSP_V1/libcsp/src/csp_init.o ./CSP_V1/libcsp/src/csp_init.su ./CSP_V1/libcsp/src/csp_io.cyclo ./CSP_V1/libcsp/src/csp_io.d ./CSP_V1/libcsp/src/csp_io.o ./CSP_V1/libcsp/src/csp_io.su ./CSP_V1/libcsp/src/csp_port.cyclo ./CSP_V1/libcsp/src/csp_port.d ./CSP_V1/libcsp/src/csp_port.o ./CSP_V1/libcsp/src/csp_port.su ./CSP_V1/libcsp/src/csp_promisc.cyclo ./CSP_V1/libcsp/src/csp_promisc.d ./CSP_V1/libcsp/src/csp_promisc.o ./CSP_V1/libcsp/src/csp_promisc.su ./CSP_V1/libcsp/src/csp_qfifo.cyclo ./CSP_V1/libcsp/src/csp_qfifo.d ./CSP_V1/libcsp/src/csp_qfifo.o ./CSP_V1/libcsp/src/csp_qfifo.su ./CSP_V1/libcsp/src/csp_route.cyclo ./CSP_V1/libcsp/src/csp_route.d ./CSP_V1/libcsp/src/csp_route.o ./CSP_V1/libcsp/src/csp_route.su ./CSP_V1/libcsp/src/csp_service_handler.cyclo ./CSP_V1/libcsp/src/csp_service_handler.d ./CSP_V1/libcsp/src/csp_service_handler.o ./CSP_V1/libcsp/src/csp_service_handler.su ./CSP_V1/libcsp/src/csp_services.cyclo ./CSP_V1/libcsp/src/csp_services.d ./CSP_V1/libcsp/src/csp_services.o ./CSP_V1/libcsp/src/csp_services.su ./CSP_V1/libcsp/src/csp_sfp.cyclo ./CSP_V1/libcsp/src/csp_sfp.d ./CSP_V1/libcsp/src/csp_sfp.o ./CSP_V1/libcsp/src/csp_sfp.su

.PHONY: clean-CSP_V1-2f-libcsp-2f-src


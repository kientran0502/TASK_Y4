################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Services/Logger/debug_logger.c 

OBJS += \
./Services/Logger/debug_logger.o 

C_DEPS += \
./Services/Logger/debug_logger.d 


# Each subdirectory must supply rules for building sources it contributes
Services/Logger/%.o Services/Logger/%.su Services/Logger/%.cyclo: ../Services/Logger/%.c Services/Logger/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"D:/Task_Y4/DRAM_IMG_test/BSP" -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I"D:/Task_Y4/DRAM_IMG_test/Tests" -I"D:/Task_Y4/DRAM_IMG_test/Services" -I"D:/Task_Y4/DRAM_IMG_test/Services/Queuex" -I"D:/Task_Y4/DRAM_IMG_test/BSP/SDRAM" -I"D:/Task_Y4/DRAM_IMG_test/Services/Logger" -I"D:/Task_Y4/DRAM_IMG_test/BSP/CRC" -I"D:/Task_Y4/DRAM_IMG_test/Tests/usb_dummy" -I"D:/Task_Y4/DRAM_IMG_test/Tests/usb_transfer_file_v1" -I"D:/Task_Y4/DRAM_IMG_test/Services/File" -I"D:/Task_Y4/DRAM_IMG_test/BSP/Timer" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Services-2f-Logger

clean-Services-2f-Logger:
	-$(RM) ./Services/Logger/debug_logger.cyclo ./Services/Logger/debug_logger.d ./Services/Logger/debug_logger.o ./Services/Logger/debug_logger.su

.PHONY: clean-Services-2f-Logger


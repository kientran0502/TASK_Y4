################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Tests/usb_dummy/usb_test_dummy.c 

OBJS += \
./Tests/usb_dummy/usb_test_dummy.o 

C_DEPS += \
./Tests/usb_dummy/usb_test_dummy.d 


# Each subdirectory must supply rules for building sources it contributes
Tests/usb_dummy/%.o Tests/usb_dummy/%.su Tests/usb_dummy/%.cyclo: ../Tests/usb_dummy/%.c Tests/usb_dummy/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"D:/Task_Y4/DRAM_IMG_test/BSP" -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I"D:/Task_Y4/DRAM_IMG_test/Tests" -I"D:/Task_Y4/DRAM_IMG_test/Services" -I"D:/Task_Y4/DRAM_IMG_test/Services/Queuex" -I"D:/Task_Y4/DRAM_IMG_test/BSP/SDRAM" -I"D:/Task_Y4/DRAM_IMG_test/Services/Logger" -I"D:/Task_Y4/DRAM_IMG_test/Services/File_Chunker" -I"D:/Task_Y4/DRAM_IMG_test/BSP/CRC" -I"D:/Task_Y4/DRAM_IMG_test/Tests/usb_transfer_file" -I"D:/Task_Y4/DRAM_IMG_test/Tests/usb_dummy" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Tests-2f-usb_dummy

clean-Tests-2f-usb_dummy:
	-$(RM) ./Tests/usb_dummy/usb_test_dummy.cyclo ./Tests/usb_dummy/usb_test_dummy.d ./Tests/usb_dummy/usb_test_dummy.o ./Tests/usb_dummy/usb_test_dummy.su

.PHONY: clean-Tests-2f-usb_dummy


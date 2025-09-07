################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Tests/test_usb_transfer_file.c 

OBJS += \
./Tests/test_usb_transfer_file.o 

C_DEPS += \
./Tests/test_usb_transfer_file.d 


# Each subdirectory must supply rules for building sources it contributes
Tests/%.o Tests/%.su Tests/%.cyclo: ../Tests/%.c Tests/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"D:/Internlab/Internlab/F7_DRAM_test/DRAM_IMG_test/BSP" -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I"D:/Internlab/Internlab/F7_DRAM_test/DRAM_IMG_test/Tests" -I"D:/Internlab/Internlab/F7_DRAM_test/DRAM_IMG_test/Services" -I"D:/Internlab/Internlab/F7_DRAM_test/DRAM_IMG_test/Services/Queuex" -I"D:/Internlab/Internlab/F7_DRAM_test/DRAM_IMG_test/BSP/SDRAM" -I"D:/Internlab/Internlab/F7_DRAM_test/DRAM_IMG_test/Services/Logger" -I"D:/Internlab/Internlab/F7_DRAM_test/DRAM_IMG_test/Services/File_Chunker" -I"D:/Internlab/Internlab/F7_DRAM_test/DRAM_IMG_test/BSP/CRC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Tests

clean-Tests:
	-$(RM) ./Tests/test_usb_transfer_file.cyclo ./Tests/test_usb_transfer_file.d ./Tests/test_usb_transfer_file.o ./Tests/test_usb_transfer_file.su

.PHONY: clean-Tests


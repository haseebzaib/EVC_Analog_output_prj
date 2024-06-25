################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/SIO/sio.c 

OBJS += \
./Application/SIO/sio.o 

C_DEPS += \
./Application/SIO/sio.d 


# Each subdirectory must supply rules for building sources it contributes
Application/SIO/%.o Application/SIO/%.su Application/SIO/%.cyclo: ../Application/SIO/%.c Application/SIO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32C031xx -c -I../Core/Inc -I../Drivers/STM32C0xx_HAL_Driver/Inc -I../Drivers/STM32C0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32C0xx/Include -I../Drivers/CMSIS/Include -I"F:/haseeb/EVC_FreeRTOS_Bare_Workspace/EVC_Analog_output_prj/Application" -I"F:/haseeb/EVC_FreeRTOS_Bare_Workspace/EVC_Analog_output_prj/Application/SIO" -I"F:/haseeb/EVC_FreeRTOS_Bare_Workspace/EVC_Analog_output_prj/Application/dac161s997" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Application-2f-SIO

clean-Application-2f-SIO:
	-$(RM) ./Application/SIO/sio.cyclo ./Application/SIO/sio.d ./Application/SIO/sio.o ./Application/SIO/sio.su

.PHONY: clean-Application-2f-SIO


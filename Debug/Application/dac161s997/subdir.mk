################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/dac161s997/dac161s997.c \
../Application/dac161s997/dac161s997_regs.c 

OBJS += \
./Application/dac161s997/dac161s997.o \
./Application/dac161s997/dac161s997_regs.o 

C_DEPS += \
./Application/dac161s997/dac161s997.d \
./Application/dac161s997/dac161s997_regs.d 


# Each subdirectory must supply rules for building sources it contributes
Application/dac161s997/%.o Application/dac161s997/%.su Application/dac161s997/%.cyclo: ../Application/dac161s997/%.c Application/dac161s997/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32C031xx -c -I../Core/Inc -I../Drivers/STM32C0xx_HAL_Driver/Inc -I../Drivers/STM32C0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32C0xx/Include -I../Drivers/CMSIS/Include -I"F:/haseeb/EVC_FreeRTOS_Bare_Workspace/EVC_Analog_output_prj/Application" -I"F:/haseeb/EVC_FreeRTOS_Bare_Workspace/EVC_Analog_output_prj/Application/SIO" -I"F:/haseeb/EVC_FreeRTOS_Bare_Workspace/EVC_Analog_output_prj/Application/dac161s997" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Application-2f-dac161s997

clean-Application-2f-dac161s997:
	-$(RM) ./Application/dac161s997/dac161s997.cyclo ./Application/dac161s997/dac161s997.d ./Application/dac161s997/dac161s997.o ./Application/dac161s997/dac161s997.su ./Application/dac161s997/dac161s997_regs.cyclo ./Application/dac161s997/dac161s997_regs.d ./Application/dac161s997/dac161s997_regs.o ./Application/dac161s997/dac161s997_regs.su

.PHONY: clean-Application-2f-dac161s997


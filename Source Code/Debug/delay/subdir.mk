################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../delay/dwt_stm32_delay.c 

OBJS += \
./delay/dwt_stm32_delay.o 

C_DEPS += \
./delay/dwt_stm32_delay.d 


# Each subdirectory must supply rules for building sources it contributes
delay/dwt_stm32_delay.o: ../delay/dwt_stm32_delay.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/m.sehati/STM32CubeIDE/workspace_1.5.1/step_motor/delay" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"delay/dwt_stm32_delay.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


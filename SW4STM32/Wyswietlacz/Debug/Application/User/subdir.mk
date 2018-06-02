################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/STMHAL/Wyswietlacz/Src/main.c \
D:/STMHAL/Wyswietlacz/Src/stm32f4xx_hal_msp.c \
D:/STMHAL/Wyswietlacz/Src/stm32f4xx_it.c 

CPP_SRCS += \
../Application/User/Game.cpp \
../Application/User/MAX7219.cpp \
../Application/User/MAX7219_MatrixDisplay.cpp \
../Application/User/Player.cpp 

OBJS += \
./Application/User/Game.o \
./Application/User/MAX7219.o \
./Application/User/MAX7219_MatrixDisplay.o \
./Application/User/Player.o \
./Application/User/main.o \
./Application/User/stm32f4xx_hal_msp.o \
./Application/User/stm32f4xx_it.o 

C_DEPS += \
./Application/User/main.d \
./Application/User/stm32f4xx_hal_msp.d \
./Application/User/stm32f4xx_it.d 

CPP_DEPS += \
./Application/User/Game.d \
./Application/User/MAX7219.d \
./Application/User/MAX7219_MatrixDisplay.d \
./Application/User/Player.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/%.o: ../Application/User/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	@echo $(PWD)
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/STMHAL/Wyswietlacz/Inc" -I"D:/STMHAL/Wyswietlacz/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/STMHAL/Wyswietlacz/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/STMHAL/Wyswietlacz/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/STMHAL/Wyswietlacz/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/main.o: D:/STMHAL/Wyswietlacz/Src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/STMHAL/Wyswietlacz/Inc" -I"D:/STMHAL/Wyswietlacz/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/STMHAL/Wyswietlacz/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/STMHAL/Wyswietlacz/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/STMHAL/Wyswietlacz/Drivers/CMSIS/Include" -I"D:/STMHAL/Wyswietlacz/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f4xx_hal_msp.o: D:/STMHAL/Wyswietlacz/Src/stm32f4xx_hal_msp.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/STMHAL/Wyswietlacz/Inc" -I"D:/STMHAL/Wyswietlacz/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/STMHAL/Wyswietlacz/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/STMHAL/Wyswietlacz/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/STMHAL/Wyswietlacz/Drivers/CMSIS/Include" -I"D:/STMHAL/Wyswietlacz/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f4xx_it.o: D:/STMHAL/Wyswietlacz/Src/stm32f4xx_it.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/STMHAL/Wyswietlacz/Inc" -I"D:/STMHAL/Wyswietlacz/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/STMHAL/Wyswietlacz/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/STMHAL/Wyswietlacz/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/STMHAL/Wyswietlacz/Drivers/CMSIS/Include" -I"D:/STMHAL/Wyswietlacz/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



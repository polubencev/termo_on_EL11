################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../avr-ds18b20-master/include/ds18b20/ds18b20.c \
../avr-ds18b20-master/include/ds18b20/onewire.c \
../avr-ds18b20-master/include/ds18b20/romsearch.c 

OBJS += \
./avr-ds18b20-master/include/ds18b20/ds18b20.o \
./avr-ds18b20-master/include/ds18b20/onewire.o \
./avr-ds18b20-master/include/ds18b20/romsearch.o 

C_DEPS += \
./avr-ds18b20-master/include/ds18b20/ds18b20.d \
./avr-ds18b20-master/include/ds18b20/onewire.d \
./avr-ds18b20-master/include/ds18b20/romsearch.d 


# Each subdirectory must supply rules for building sources it contributes
avr-ds18b20-master/include/ds18b20/%.o: ../avr-ds18b20-master/include/ds18b20/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -O2 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega8 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



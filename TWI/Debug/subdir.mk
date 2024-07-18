################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIO_prog.c \
../EEPROM_prog.c \
../PORT_prog.c \
../TWI_prog.c \
../main.c 

OBJS += \
./DIO_prog.o \
./EEPROM_prog.o \
./PORT_prog.o \
./TWI_prog.o \
./main.o 

C_DEPS += \
./DIO_prog.d \
./EEPROM_prog.d \
./PORT_prog.d \
./TWI_prog.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



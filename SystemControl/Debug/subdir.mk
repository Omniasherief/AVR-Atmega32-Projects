################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_prog.c \
../CLCD.prog.c \
../DCMotor_prog.c \
../DIO_prog.c \
../KPD_prog.c \
../LDR_prog.c \
../LM35_prog.c \
../PORT_prog.c \
../main.c 

OBJS += \
./ADC_prog.o \
./CLCD.prog.o \
./DCMotor_prog.o \
./DIO_prog.o \
./KPD_prog.o \
./LDR_prog.o \
./LM35_prog.o \
./PORT_prog.o \
./main.o 

C_DEPS += \
./ADC_prog.d \
./CLCD.prog.d \
./DCMotor_prog.d \
./DIO_prog.d \
./KPD_prog.d \
./LDR_prog.d \
./LM35_prog.d \
./PORT_prog.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Buzzer_prog.c \
../CLCD.prog.c \
../DIO_prog.c \
../LED_prog.c \
../PORT_prog.c \
../Timer_prog.c \
../Ultrasonic.c \
../main.c 

OBJS += \
./Buzzer_prog.o \
./CLCD.prog.o \
./DIO_prog.o \
./LED_prog.o \
./PORT_prog.o \
./Timer_prog.o \
./Ultrasonic.o \
./main.o 

C_DEPS += \
./Buzzer_prog.d \
./CLCD.prog.d \
./DIO_prog.d \
./LED_prog.d \
./PORT_prog.d \
./Timer_prog.d \
./Ultrasonic.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CLCD.prog.c \
../DCMotor_prog.c \
../DIO_prog.c \
../DashBoard.c \
../KPD_prog.c \
../PORT_prog.c \
../StepperMotor_prog.c \
../main.c 

OBJS += \
./CLCD.prog.o \
./DCMotor_prog.o \
./DIO_prog.o \
./DashBoard.o \
./KPD_prog.o \
./PORT_prog.o \
./StepperMotor_prog.o \
./main.o 

C_DEPS += \
./CLCD.prog.d \
./DCMotor_prog.d \
./DIO_prog.d \
./DashBoard.d \
./KPD_prog.d \
./PORT_prog.d \
./StepperMotor_prog.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



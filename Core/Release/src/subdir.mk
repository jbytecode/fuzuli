################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/IO.cpp \
../src/Math.cpp \
../src/MySql.cpp \
../src/fltk.cpp \
../src/gd.cpp \
../src/ncurses.cpp \
../src/net.cpp \
../src/strings.cpp \
../src/utils.cpp 

OBJS += \
./src/IO.o \
./src/Math.o \
./src/MySql.o \
./src/fltk.o \
./src/gd.o \
./src/ncurses.o \
./src/net.o \
./src/strings.o \
./src/utils.o 

CPP_DEPS += \
./src/IO.d \
./src/Math.d \
./src/MySql.d \
./src/fltk.d \
./src/gd.d \
./src/ncurses.d \
./src/net.d \
./src/strings.d \
./src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include/tcl -I/usr/include/FL -I../../Interpreter/include/ -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



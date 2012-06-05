################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/IO.cpp \
../src/Math.cpp \
../src/MySql.cpp \
../src/TclTk.cpp \
../src/gd.cpp \
../src/java.cpp \
../src/net.cpp \
../src/strings.cpp \
../src/utils.cpp 

OBJS += \
./src/IO.o \
./src/Math.o \
./src/MySql.o \
./src/TclTk.o \
./src/gd.o \
./src/java.o \
./src/net.o \
./src/strings.o \
./src/utils.o 

CPP_DEPS += \
./src/IO.d \
./src/Math.d \
./src/MySql.d \
./src/TclTk.d \
./src/gd.d \
./src/java.d \
./src/net.d \
./src/strings.d \
./src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include/tcl -I../../Interpreter/include/ -I/usr/lib/jvm/default-java/include/linux -I/usr/lib/jvm/default-java/include/ -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



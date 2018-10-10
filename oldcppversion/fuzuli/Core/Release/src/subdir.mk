################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/IO.cpp \
../src/Math.cpp \
../src/strings.cpp \
../src/utils.cpp 

OBJS += \
./src/IO.o \
./src/Math.o \
./src/strings.o \
./src/utils.o 

CPP_DEPS += \
./src/IO.d \
./src/Math.d \
./src/strings.d \
./src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../../Interpreter/include/ -O3 -Wall -c -fmessage-length=0 -std=c++0x -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



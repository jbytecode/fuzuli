################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src_gui/fltk.cpp 

OBJS += \
./src_gui/fltk.o 

CPP_DEPS += \
./src_gui/fltk.d 


# Each subdirectory must supply rules for building sources it contributes
src_gui/%.o: ../src_gui/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I../../Interpreter/include/ -I/usr/include/FL -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



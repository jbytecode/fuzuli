################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AritmeticExpression.cpp \
../src/AstBuilder.cpp \
../src/BlockExpression.cpp \
../src/CppEmitter.cpp \
../src/DataTypeExpression.cpp \
../src/DynLoadExpression.cpp \
../src/Environment.cpp \
../src/EvalExpression.cpp \
../src/Expression.cpp \
../src/FunctionExpression.cpp \
../src/IOExpression.cpp \
../src/IfExpression.cpp \
../src/LetExpression.cpp \
../src/ListExpression.cpp \
../src/LoopsExpression.cpp \
../src/SourceCode.cpp \
../src/Token.cpp \
../src/WebExpression.cpp 

OBJS += \
./src/AritmeticExpression.o \
./src/AstBuilder.o \
./src/BlockExpression.o \
./src/CppEmitter.o \
./src/DataTypeExpression.o \
./src/DynLoadExpression.o \
./src/Environment.o \
./src/EvalExpression.o \
./src/Expression.o \
./src/FunctionExpression.o \
./src/IOExpression.o \
./src/IfExpression.o \
./src/LetExpression.o \
./src/ListExpression.o \
./src/LoopsExpression.o \
./src/SourceCode.o \
./src/Token.o \
./src/WebExpression.o 

CPP_DEPS += \
./src/AritmeticExpression.d \
./src/AstBuilder.d \
./src/BlockExpression.d \
./src/CppEmitter.d \
./src/DataTypeExpression.d \
./src/DynLoadExpression.d \
./src/Environment.d \
./src/EvalExpression.d \
./src/Expression.d \
./src/FunctionExpression.d \
./src/IOExpression.d \
./src/IfExpression.d \
./src/LetExpression.d \
./src/ListExpression.d \
./src/LoopsExpression.d \
./src/SourceCode.d \
./src/Token.d \
./src/WebExpression.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



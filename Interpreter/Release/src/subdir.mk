################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AndExpression.cpp \
../src/AstBuilder.cpp \
../src/AsterixExpression.cpp \
../src/BlockExpression.cpp \
../src/DivisionExpression.cpp \
../src/Environment.cpp \
../src/EqualsExpression.cpp \
../src/Expression.cpp \
../src/IfExpression.cpp \
../src/IntegerExpression.cpp \
../src/NotExpression.cpp \
../src/OrExpression.cpp \
../src/PlusExpression.cpp \
../src/PrintExpression.cpp \
../src/SourceCode.cpp \
../src/StringExpression.cpp \
../src/SubtractionExpression.cpp \
../src/Token.cpp \
../src/main.cpp 

OBJS += \
./src/AndExpression.o \
./src/AstBuilder.o \
./src/AsterixExpression.o \
./src/BlockExpression.o \
./src/DivisionExpression.o \
./src/Environment.o \
./src/EqualsExpression.o \
./src/Expression.o \
./src/IfExpression.o \
./src/IntegerExpression.o \
./src/NotExpression.o \
./src/OrExpression.o \
./src/PlusExpression.o \
./src/PrintExpression.o \
./src/SourceCode.o \
./src/StringExpression.o \
./src/SubtractionExpression.o \
./src/Token.o \
./src/main.o 

CPP_DEPS += \
./src/AndExpression.d \
./src/AstBuilder.d \
./src/AsterixExpression.d \
./src/BlockExpression.d \
./src/DivisionExpression.d \
./src/Environment.d \
./src/EqualsExpression.d \
./src/Expression.d \
./src/IfExpression.d \
./src/IntegerExpression.d \
./src/NotExpression.d \
./src/OrExpression.d \
./src/PlusExpression.d \
./src/PrintExpression.d \
./src/SourceCode.d \
./src/StringExpression.d \
./src/SubtractionExpression.d \
./src/Token.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



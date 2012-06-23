################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: libFuzuliJava.so

dependents:
	-cd /home/hako/workspace/fuzuli/Interpreter/Release && $(MAKE) clean all

# Tool invocations
libFuzuliJava.so: $(OBJS) $(USER_OBJS) /home/hako/workspace/fuzuli/Interpreter/Release/libfuzuli.so
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	g++ -L/usr/lib/jvm/default-java/jre/lib/i386/ -L/usr/lib/jvm/default-java/jre/lib/i386/client -shared -o "libFuzuliJava.so" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(CC_DEPS)$(LIBRARIES)$(CPP_DEPS)$(CXX_DEPS)$(C_UPPER_DEPS) libFuzuliJava.so
	-@echo ' '

post-build:
	-./eclipse-post-inst.sh
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
/home/hako/workspace/fuzuli/Interpreter/Release/libfuzuli.so:

-include ../makefile.targets

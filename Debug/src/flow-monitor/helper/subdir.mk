################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/flow-monitor/helper/flow-monitor-helper.cc 

CC_DEPS += \
./src/flow-monitor/helper/flow-monitor-helper.d 

OBJS += \
./src/flow-monitor/helper/flow-monitor-helper.o 


# Each subdirectory must supply rules for building sources it contributes
src/flow-monitor/helper/%.o: ../src/flow-monitor/helper/%.cc src/flow-monitor/helper/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-flow-2d-monitor-2f-helper

clean-src-2f-flow-2d-monitor-2f-helper:
	-$(RM) ./src/flow-monitor/helper/flow-monitor-helper.d ./src/flow-monitor/helper/flow-monitor-helper.o

.PHONY: clean-src-2f-flow-2d-monitor-2f-helper


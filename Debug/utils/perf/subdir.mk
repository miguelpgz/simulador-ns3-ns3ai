################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../utils/perf/perf-io.cc 

CC_DEPS += \
./utils/perf/perf-io.d 

OBJS += \
./utils/perf/perf-io.o 


# Each subdirectory must supply rules for building sources it contributes
utils/perf/%.o: ../utils/perf/%.cc utils/perf/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-utils-2f-perf

clean-utils-2f-perf:
	-$(RM) ./utils/perf/perf-io.d ./utils/perf/perf-io.o

.PHONY: clean-utils-2f-perf


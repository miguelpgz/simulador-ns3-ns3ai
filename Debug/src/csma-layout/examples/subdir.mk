################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/csma-layout/examples/csma-star.cc 

CC_DEPS += \
./src/csma-layout/examples/csma-star.d 

OBJS += \
./src/csma-layout/examples/csma-star.o 


# Each subdirectory must supply rules for building sources it contributes
src/csma-layout/examples/%.o: ../src/csma-layout/examples/%.cc src/csma-layout/examples/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-csma-2d-layout-2f-examples

clean-src-2f-csma-2d-layout-2f-examples:
	-$(RM) ./src/csma-layout/examples/csma-star.d ./src/csma-layout/examples/csma-star.o

.PHONY: clean-src-2f-csma-2d-layout-2f-examples

################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../examples/naming/object-names.cc 

CC_DEPS += \
./examples/naming/object-names.d 

OBJS += \
./examples/naming/object-names.o 


# Each subdirectory must supply rules for building sources it contributes
examples/naming/%.o: ../examples/naming/%.cc examples/naming/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-examples-2f-naming

clean-examples-2f-naming:
	-$(RM) ./examples/naming/object-names.d ./examples/naming/object-names.o

.PHONY: clean-examples-2f-naming


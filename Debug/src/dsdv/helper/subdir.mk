################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/dsdv/helper/dsdv-helper.cc 

CC_DEPS += \
./src/dsdv/helper/dsdv-helper.d 

OBJS += \
./src/dsdv/helper/dsdv-helper.o 


# Each subdirectory must supply rules for building sources it contributes
src/dsdv/helper/%.o: ../src/dsdv/helper/%.cc src/dsdv/helper/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-dsdv-2f-helper

clean-src-2f-dsdv-2f-helper:
	-$(RM) ./src/dsdv/helper/dsdv-helper.d ./src/dsdv/helper/dsdv-helper.o

.PHONY: clean-src-2f-dsdv-2f-helper


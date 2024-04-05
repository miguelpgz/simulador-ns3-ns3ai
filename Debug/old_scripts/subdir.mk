################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../old_scripts/sim2_v1.cc \
../old_scripts/sim2_v2.cc 

CC_DEPS += \
./old_scripts/sim2_v1.d \
./old_scripts/sim2_v2.d 

OBJS += \
./old_scripts/sim2_v1.o \
./old_scripts/sim2_v2.o 


# Each subdirectory must supply rules for building sources it contributes
old_scripts/%.o: ../old_scripts/%.cc old_scripts/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-old_scripts

clean-old_scripts:
	-$(RM) ./old_scripts/sim2_v1.d ./old_scripts/sim2_v1.o ./old_scripts/sim2_v2.d ./old_scripts/sim2_v2.o

.PHONY: clean-old_scripts


################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../scratch/a_plus_b/sim.cc 

CC_DEPS += \
./scratch/a_plus_b/sim.d 

OBJS += \
./scratch/a_plus_b/sim.o 


# Each subdirectory must supply rules for building sources it contributes
scratch/a_plus_b/%.o: ../scratch/a_plus_b/%.cc scratch/a_plus_b/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-scratch-2f-a_plus_b

clean-scratch-2f-a_plus_b:
	-$(RM) ./scratch/a_plus_b/sim.d ./scratch/a_plus_b/sim.o

.PHONY: clean-scratch-2f-a_plus_b


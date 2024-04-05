################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../scratch/escenarios_estudio/escenario1.cc 

CC_DEPS += \
./scratch/escenarios_estudio/escenario1.d 

OBJS += \
./scratch/escenarios_estudio/escenario1.o 


# Each subdirectory must supply rules for building sources it contributes
scratch/escenarios_estudio/%.o: ../scratch/escenarios_estudio/%.cc scratch/escenarios_estudio/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-scratch-2f-escenarios_estudio

clean-scratch-2f-escenarios_estudio:
	-$(RM) ./scratch/escenarios_estudio/escenario1.d ./scratch/escenarios_estudio/escenario1.o

.PHONY: clean-scratch-2f-escenarios_estudio


################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../scratch/ns3ai-data-collection/sim2.cc 

CC_DEPS += \
./scratch/ns3ai-data-collection/sim2.d 

OBJS += \
./scratch/ns3ai-data-collection/sim2.o 


# Each subdirectory must supply rules for building sources it contributes
scratch/ns3ai-data-collection/%.o: ../scratch/ns3ai-data-collection/%.cc scratch/ns3ai-data-collection/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-scratch-2f-ns3ai-2d-data-2d-collection

clean-scratch-2f-ns3ai-2d-data-2d-collection:
	-$(RM) ./scratch/ns3ai-data-collection/sim2.d ./scratch/ns3ai-data-collection/sim2.o

.PHONY: clean-scratch-2f-ns3ai-2d-data-2d-collection


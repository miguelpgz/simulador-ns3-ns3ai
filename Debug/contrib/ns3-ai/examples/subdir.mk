################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../contrib/ns3-ai/examples/test-shm.cc 

CC_DEPS += \
./contrib/ns3-ai/examples/test-shm.d 

OBJS += \
./contrib/ns3-ai/examples/test-shm.o 


# Each subdirectory must supply rules for building sources it contributes
contrib/ns3-ai/examples/%.o: ../contrib/ns3-ai/examples/%.cc contrib/ns3-ai/examples/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-contrib-2f-ns3-2d-ai-2f-examples

clean-contrib-2f-ns3-2d-ai-2f-examples:
	-$(RM) ./contrib/ns3-ai/examples/test-shm.d ./contrib/ns3-ai/examples/test-shm.o

.PHONY: clean-contrib-2f-ns3-2d-ai-2f-examples


################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../contrib/ns3-ai/examples/rate-control/ai-constant-rate-wifi-manager.cc \
../contrib/ns3-ai/examples/rate-control/ai-thompson-sampling-wifi-manager.cc \
../contrib/ns3-ai/examples/rate-control/rate-control.cc 

CC_DEPS += \
./contrib/ns3-ai/examples/rate-control/ai-constant-rate-wifi-manager.d \
./contrib/ns3-ai/examples/rate-control/ai-thompson-sampling-wifi-manager.d \
./contrib/ns3-ai/examples/rate-control/rate-control.d 

OBJS += \
./contrib/ns3-ai/examples/rate-control/ai-constant-rate-wifi-manager.o \
./contrib/ns3-ai/examples/rate-control/ai-thompson-sampling-wifi-manager.o \
./contrib/ns3-ai/examples/rate-control/rate-control.o 


# Each subdirectory must supply rules for building sources it contributes
contrib/ns3-ai/examples/rate-control/%.o: ../contrib/ns3-ai/examples/rate-control/%.cc contrib/ns3-ai/examples/rate-control/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-contrib-2f-ns3-2d-ai-2f-examples-2f-rate-2d-control

clean-contrib-2f-ns3-2d-ai-2f-examples-2f-rate-2d-control:
	-$(RM) ./contrib/ns3-ai/examples/rate-control/ai-constant-rate-wifi-manager.d ./contrib/ns3-ai/examples/rate-control/ai-constant-rate-wifi-manager.o ./contrib/ns3-ai/examples/rate-control/ai-thompson-sampling-wifi-manager.d ./contrib/ns3-ai/examples/rate-control/ai-thompson-sampling-wifi-manager.o ./contrib/ns3-ai/examples/rate-control/rate-control.d ./contrib/ns3-ai/examples/rate-control/rate-control.o

.PHONY: clean-contrib-2f-ns3-2d-ai-2f-examples-2f-rate-2d-control


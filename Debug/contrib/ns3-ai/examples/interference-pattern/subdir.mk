################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../contrib/ns3-ai/examples/interference-pattern/mygym.cc \
../contrib/ns3-ai/examples/interference-pattern/sim.cc 

CC_DEPS += \
./contrib/ns3-ai/examples/interference-pattern/mygym.d \
./contrib/ns3-ai/examples/interference-pattern/sim.d 

OBJS += \
./contrib/ns3-ai/examples/interference-pattern/mygym.o \
./contrib/ns3-ai/examples/interference-pattern/sim.o 


# Each subdirectory must supply rules for building sources it contributes
contrib/ns3-ai/examples/interference-pattern/%.o: ../contrib/ns3-ai/examples/interference-pattern/%.cc contrib/ns3-ai/examples/interference-pattern/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-contrib-2f-ns3-2d-ai-2f-examples-2f-interference-2d-pattern

clean-contrib-2f-ns3-2d-ai-2f-examples-2f-interference-2d-pattern:
	-$(RM) ./contrib/ns3-ai/examples/interference-pattern/mygym.d ./contrib/ns3-ai/examples/interference-pattern/mygym.o ./contrib/ns3-ai/examples/interference-pattern/sim.d ./contrib/ns3-ai/examples/interference-pattern/sim.o

.PHONY: clean-contrib-2f-ns3-2d-ai-2f-examples-2f-interference-2d-pattern


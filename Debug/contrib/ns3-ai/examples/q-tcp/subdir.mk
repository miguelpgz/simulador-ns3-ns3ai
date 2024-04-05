################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../contrib/ns3-ai/examples/q-tcp/sim.cc \
../contrib/ns3-ai/examples/q-tcp/tcp-rl-env.cc \
../contrib/ns3-ai/examples/q-tcp/tcp-rl.cc 

CC_DEPS += \
./contrib/ns3-ai/examples/q-tcp/sim.d \
./contrib/ns3-ai/examples/q-tcp/tcp-rl-env.d \
./contrib/ns3-ai/examples/q-tcp/tcp-rl.d 

OBJS += \
./contrib/ns3-ai/examples/q-tcp/sim.o \
./contrib/ns3-ai/examples/q-tcp/tcp-rl-env.o \
./contrib/ns3-ai/examples/q-tcp/tcp-rl.o 


# Each subdirectory must supply rules for building sources it contributes
contrib/ns3-ai/examples/q-tcp/%.o: ../contrib/ns3-ai/examples/q-tcp/%.cc contrib/ns3-ai/examples/q-tcp/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-contrib-2f-ns3-2d-ai-2f-examples-2f-q-2d-tcp

clean-contrib-2f-ns3-2d-ai-2f-examples-2f-q-2d-tcp:
	-$(RM) ./contrib/ns3-ai/examples/q-tcp/sim.d ./contrib/ns3-ai/examples/q-tcp/sim.o ./contrib/ns3-ai/examples/q-tcp/tcp-rl-env.d ./contrib/ns3-ai/examples/q-tcp/tcp-rl-env.o ./contrib/ns3-ai/examples/q-tcp/tcp-rl.d ./contrib/ns3-ai/examples/q-tcp/tcp-rl.o

.PHONY: clean-contrib-2f-ns3-2d-ai-2f-examples-2f-q-2d-tcp


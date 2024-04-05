################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../contrib/ns3-ai/examples/lte_cqi/cqi-dl-env.cc \
../contrib/ns3-ai/examples/lte_cqi/lte_cqi.cc \
../contrib/ns3-ai/examples/lte_cqi/my-rr-sched.cc 

CC_DEPS += \
./contrib/ns3-ai/examples/lte_cqi/cqi-dl-env.d \
./contrib/ns3-ai/examples/lte_cqi/lte_cqi.d \
./contrib/ns3-ai/examples/lte_cqi/my-rr-sched.d 

OBJS += \
./contrib/ns3-ai/examples/lte_cqi/cqi-dl-env.o \
./contrib/ns3-ai/examples/lte_cqi/lte_cqi.o \
./contrib/ns3-ai/examples/lte_cqi/my-rr-sched.o 


# Each subdirectory must supply rules for building sources it contributes
contrib/ns3-ai/examples/lte_cqi/%.o: ../contrib/ns3-ai/examples/lte_cqi/%.cc contrib/ns3-ai/examples/lte_cqi/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-contrib-2f-ns3-2d-ai-2f-examples-2f-lte_cqi

clean-contrib-2f-ns3-2d-ai-2f-examples-2f-lte_cqi:
	-$(RM) ./contrib/ns3-ai/examples/lte_cqi/cqi-dl-env.d ./contrib/ns3-ai/examples/lte_cqi/cqi-dl-env.o ./contrib/ns3-ai/examples/lte_cqi/lte_cqi.d ./contrib/ns3-ai/examples/lte_cqi/lte_cqi.o ./contrib/ns3-ai/examples/lte_cqi/my-rr-sched.d ./contrib/ns3-ai/examples/lte_cqi/my-rr-sched.o

.PHONY: clean-contrib-2f-ns3-2d-ai-2f-examples-2f-lte_cqi


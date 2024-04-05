################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../contrib/ns3-ai/py_interface/memory-pool-module.c \
../contrib/ns3-ai/py_interface/memory-pool.c 

C_DEPS += \
./contrib/ns3-ai/py_interface/memory-pool-module.d \
./contrib/ns3-ai/py_interface/memory-pool.d 

OBJS += \
./contrib/ns3-ai/py_interface/memory-pool-module.o \
./contrib/ns3-ai/py_interface/memory-pool.o 


# Each subdirectory must supply rules for building sources it contributes
contrib/ns3-ai/py_interface/%.o: ../contrib/ns3-ai/py_interface/%.c contrib/ns3-ai/py_interface/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-contrib-2f-ns3-2d-ai-2f-py_interface

clean-contrib-2f-ns3-2d-ai-2f-py_interface:
	-$(RM) ./contrib/ns3-ai/py_interface/memory-pool-module.d ./contrib/ns3-ai/py_interface/memory-pool-module.o ./contrib/ns3-ai/py_interface/memory-pool.d ./contrib/ns3-ai/py_interface/memory-pool.o

.PHONY: clean-contrib-2f-ns3-2d-ai-2f-py_interface


################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/bridge/examples/csma-bridge-one-hop.cc \
../src/bridge/examples/csma-bridge.cc 

CC_DEPS += \
./src/bridge/examples/csma-bridge-one-hop.d \
./src/bridge/examples/csma-bridge.d 

OBJS += \
./src/bridge/examples/csma-bridge-one-hop.o \
./src/bridge/examples/csma-bridge.o 


# Each subdirectory must supply rules for building sources it contributes
src/bridge/examples/%.o: ../src/bridge/examples/%.cc src/bridge/examples/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-bridge-2f-examples

clean-src-2f-bridge-2f-examples:
	-$(RM) ./src/bridge/examples/csma-bridge-one-hop.d ./src/bridge/examples/csma-bridge-one-hop.o ./src/bridge/examples/csma-bridge.d ./src/bridge/examples/csma-bridge.o

.PHONY: clean-src-2f-bridge-2f-examples


################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/olsr/model/olsr-header.cc \
../src/olsr/model/olsr-routing-protocol.cc \
../src/olsr/model/olsr-state.cc 

CC_DEPS += \
./src/olsr/model/olsr-header.d \
./src/olsr/model/olsr-routing-protocol.d \
./src/olsr/model/olsr-state.d 

OBJS += \
./src/olsr/model/olsr-header.o \
./src/olsr/model/olsr-routing-protocol.o \
./src/olsr/model/olsr-state.o 


# Each subdirectory must supply rules for building sources it contributes
src/olsr/model/%.o: ../src/olsr/model/%.cc src/olsr/model/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-olsr-2f-model

clean-src-2f-olsr-2f-model:
	-$(RM) ./src/olsr/model/olsr-header.d ./src/olsr/model/olsr-header.o ./src/olsr/model/olsr-routing-protocol.d ./src/olsr/model/olsr-routing-protocol.o ./src/olsr/model/olsr-state.d ./src/olsr/model/olsr-state.o

.PHONY: clean-src-2f-olsr-2f-model

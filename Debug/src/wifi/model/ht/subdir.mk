################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/wifi/model/ht/ht-capabilities.cc \
../src/wifi/model/ht/ht-configuration.cc \
../src/wifi/model/ht/ht-frame-exchange-manager.cc \
../src/wifi/model/ht/ht-operation.cc \
../src/wifi/model/ht/ht-phy.cc \
../src/wifi/model/ht/ht-ppdu.cc 

CC_DEPS += \
./src/wifi/model/ht/ht-capabilities.d \
./src/wifi/model/ht/ht-configuration.d \
./src/wifi/model/ht/ht-frame-exchange-manager.d \
./src/wifi/model/ht/ht-operation.d \
./src/wifi/model/ht/ht-phy.d \
./src/wifi/model/ht/ht-ppdu.d 

OBJS += \
./src/wifi/model/ht/ht-capabilities.o \
./src/wifi/model/ht/ht-configuration.o \
./src/wifi/model/ht/ht-frame-exchange-manager.o \
./src/wifi/model/ht/ht-operation.o \
./src/wifi/model/ht/ht-phy.o \
./src/wifi/model/ht/ht-ppdu.o 


# Each subdirectory must supply rules for building sources it contributes
src/wifi/model/ht/%.o: ../src/wifi/model/ht/%.cc src/wifi/model/ht/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-wifi-2f-model-2f-ht

clean-src-2f-wifi-2f-model-2f-ht:
	-$(RM) ./src/wifi/model/ht/ht-capabilities.d ./src/wifi/model/ht/ht-capabilities.o ./src/wifi/model/ht/ht-configuration.d ./src/wifi/model/ht/ht-configuration.o ./src/wifi/model/ht/ht-frame-exchange-manager.d ./src/wifi/model/ht/ht-frame-exchange-manager.o ./src/wifi/model/ht/ht-operation.d ./src/wifi/model/ht/ht-operation.o ./src/wifi/model/ht/ht-phy.d ./src/wifi/model/ht/ht-phy.o ./src/wifi/model/ht/ht-ppdu.d ./src/wifi/model/ht/ht-ppdu.o

.PHONY: clean-src-2f-wifi-2f-model-2f-ht


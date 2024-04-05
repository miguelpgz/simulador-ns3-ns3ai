################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/wifi/model/vht/vht-capabilities.cc \
../src/wifi/model/vht/vht-configuration.cc \
../src/wifi/model/vht/vht-frame-exchange-manager.cc \
../src/wifi/model/vht/vht-operation.cc \
../src/wifi/model/vht/vht-phy.cc \
../src/wifi/model/vht/vht-ppdu.cc 

CC_DEPS += \
./src/wifi/model/vht/vht-capabilities.d \
./src/wifi/model/vht/vht-configuration.d \
./src/wifi/model/vht/vht-frame-exchange-manager.d \
./src/wifi/model/vht/vht-operation.d \
./src/wifi/model/vht/vht-phy.d \
./src/wifi/model/vht/vht-ppdu.d 

OBJS += \
./src/wifi/model/vht/vht-capabilities.o \
./src/wifi/model/vht/vht-configuration.o \
./src/wifi/model/vht/vht-frame-exchange-manager.o \
./src/wifi/model/vht/vht-operation.o \
./src/wifi/model/vht/vht-phy.o \
./src/wifi/model/vht/vht-ppdu.o 


# Each subdirectory must supply rules for building sources it contributes
src/wifi/model/vht/%.o: ../src/wifi/model/vht/%.cc src/wifi/model/vht/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-wifi-2f-model-2f-vht

clean-src-2f-wifi-2f-model-2f-vht:
	-$(RM) ./src/wifi/model/vht/vht-capabilities.d ./src/wifi/model/vht/vht-capabilities.o ./src/wifi/model/vht/vht-configuration.d ./src/wifi/model/vht/vht-configuration.o ./src/wifi/model/vht/vht-frame-exchange-manager.d ./src/wifi/model/vht/vht-frame-exchange-manager.o ./src/wifi/model/vht/vht-operation.d ./src/wifi/model/vht/vht-operation.o ./src/wifi/model/vht/vht-phy.d ./src/wifi/model/vht/vht-phy.o ./src/wifi/model/vht/vht-ppdu.d ./src/wifi/model/vht/vht-ppdu.o

.PHONY: clean-src-2f-wifi-2f-model-2f-vht


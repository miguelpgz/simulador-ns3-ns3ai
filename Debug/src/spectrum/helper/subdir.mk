################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/spectrum/helper/adhoc-aloha-noack-ideal-phy-helper.cc \
../src/spectrum/helper/spectrum-analyzer-helper.cc \
../src/spectrum/helper/spectrum-helper.cc \
../src/spectrum/helper/tv-spectrum-transmitter-helper.cc \
../src/spectrum/helper/waveform-generator-helper.cc 

CC_DEPS += \
./src/spectrum/helper/adhoc-aloha-noack-ideal-phy-helper.d \
./src/spectrum/helper/spectrum-analyzer-helper.d \
./src/spectrum/helper/spectrum-helper.d \
./src/spectrum/helper/tv-spectrum-transmitter-helper.d \
./src/spectrum/helper/waveform-generator-helper.d 

OBJS += \
./src/spectrum/helper/adhoc-aloha-noack-ideal-phy-helper.o \
./src/spectrum/helper/spectrum-analyzer-helper.o \
./src/spectrum/helper/spectrum-helper.o \
./src/spectrum/helper/tv-spectrum-transmitter-helper.o \
./src/spectrum/helper/waveform-generator-helper.o 


# Each subdirectory must supply rules for building sources it contributes
src/spectrum/helper/%.o: ../src/spectrum/helper/%.cc src/spectrum/helper/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-spectrum-2f-helper

clean-src-2f-spectrum-2f-helper:
	-$(RM) ./src/spectrum/helper/adhoc-aloha-noack-ideal-phy-helper.d ./src/spectrum/helper/adhoc-aloha-noack-ideal-phy-helper.o ./src/spectrum/helper/spectrum-analyzer-helper.d ./src/spectrum/helper/spectrum-analyzer-helper.o ./src/spectrum/helper/spectrum-helper.d ./src/spectrum/helper/spectrum-helper.o ./src/spectrum/helper/tv-spectrum-transmitter-helper.d ./src/spectrum/helper/tv-spectrum-transmitter-helper.o ./src/spectrum/helper/waveform-generator-helper.d ./src/spectrum/helper/waveform-generator-helper.o

.PHONY: clean-src-2f-spectrum-2f-helper


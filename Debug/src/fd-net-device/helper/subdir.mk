################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/fd-net-device/helper/creator-utils.cc \
../src/fd-net-device/helper/dpdk-net-device-helper.cc \
../src/fd-net-device/helper/emu-fd-net-device-helper.cc \
../src/fd-net-device/helper/encode-decode.cc \
../src/fd-net-device/helper/fd-net-device-helper.cc \
../src/fd-net-device/helper/netmap-device-creator.cc \
../src/fd-net-device/helper/netmap-net-device-helper.cc \
../src/fd-net-device/helper/raw-sock-creator.cc \
../src/fd-net-device/helper/tap-device-creator.cc \
../src/fd-net-device/helper/tap-fd-net-device-helper.cc 

CC_DEPS += \
./src/fd-net-device/helper/creator-utils.d \
./src/fd-net-device/helper/dpdk-net-device-helper.d \
./src/fd-net-device/helper/emu-fd-net-device-helper.d \
./src/fd-net-device/helper/encode-decode.d \
./src/fd-net-device/helper/fd-net-device-helper.d \
./src/fd-net-device/helper/netmap-device-creator.d \
./src/fd-net-device/helper/netmap-net-device-helper.d \
./src/fd-net-device/helper/raw-sock-creator.d \
./src/fd-net-device/helper/tap-device-creator.d \
./src/fd-net-device/helper/tap-fd-net-device-helper.d 

OBJS += \
./src/fd-net-device/helper/creator-utils.o \
./src/fd-net-device/helper/dpdk-net-device-helper.o \
./src/fd-net-device/helper/emu-fd-net-device-helper.o \
./src/fd-net-device/helper/encode-decode.o \
./src/fd-net-device/helper/fd-net-device-helper.o \
./src/fd-net-device/helper/netmap-device-creator.o \
./src/fd-net-device/helper/netmap-net-device-helper.o \
./src/fd-net-device/helper/raw-sock-creator.o \
./src/fd-net-device/helper/tap-device-creator.o \
./src/fd-net-device/helper/tap-fd-net-device-helper.o 


# Each subdirectory must supply rules for building sources it contributes
src/fd-net-device/helper/%.o: ../src/fd-net-device/helper/%.cc src/fd-net-device/helper/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-fd-2d-net-2d-device-2f-helper

clean-src-2f-fd-2d-net-2d-device-2f-helper:
	-$(RM) ./src/fd-net-device/helper/creator-utils.d ./src/fd-net-device/helper/creator-utils.o ./src/fd-net-device/helper/dpdk-net-device-helper.d ./src/fd-net-device/helper/dpdk-net-device-helper.o ./src/fd-net-device/helper/emu-fd-net-device-helper.d ./src/fd-net-device/helper/emu-fd-net-device-helper.o ./src/fd-net-device/helper/encode-decode.d ./src/fd-net-device/helper/encode-decode.o ./src/fd-net-device/helper/fd-net-device-helper.d ./src/fd-net-device/helper/fd-net-device-helper.o ./src/fd-net-device/helper/netmap-device-creator.d ./src/fd-net-device/helper/netmap-device-creator.o ./src/fd-net-device/helper/netmap-net-device-helper.d ./src/fd-net-device/helper/netmap-net-device-helper.o ./src/fd-net-device/helper/raw-sock-creator.d ./src/fd-net-device/helper/raw-sock-creator.o ./src/fd-net-device/helper/tap-device-creator.d ./src/fd-net-device/helper/tap-device-creator.o ./src/fd-net-device/helper/tap-fd-net-device-helper.d ./src/fd-net-device/helper/tap-fd-net-device-helper.o

.PHONY: clean-src-2f-fd-2d-net-2d-device-2f-helper


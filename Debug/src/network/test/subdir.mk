################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/network/test/bit-serializer-test.cc \
../src/network/test/buffer-test.cc \
../src/network/test/drop-tail-queue-test-suite.cc \
../src/network/test/error-model-test-suite.cc \
../src/network/test/ipv6-address-test-suite.cc \
../src/network/test/lollipop-counter-test.cc \
../src/network/test/packet-metadata-test.cc \
../src/network/test/packet-socket-apps-test-suite.cc \
../src/network/test/packet-test-suite.cc \
../src/network/test/packetbb-test-suite.cc \
../src/network/test/pcap-file-test-suite.cc \
../src/network/test/sequence-number-test-suite.cc \
../src/network/test/test-data-rate.cc 

CC_DEPS += \
./src/network/test/bit-serializer-test.d \
./src/network/test/buffer-test.d \
./src/network/test/drop-tail-queue-test-suite.d \
./src/network/test/error-model-test-suite.d \
./src/network/test/ipv6-address-test-suite.d \
./src/network/test/lollipop-counter-test.d \
./src/network/test/packet-metadata-test.d \
./src/network/test/packet-socket-apps-test-suite.d \
./src/network/test/packet-test-suite.d \
./src/network/test/packetbb-test-suite.d \
./src/network/test/pcap-file-test-suite.d \
./src/network/test/sequence-number-test-suite.d \
./src/network/test/test-data-rate.d 

OBJS += \
./src/network/test/bit-serializer-test.o \
./src/network/test/buffer-test.o \
./src/network/test/drop-tail-queue-test-suite.o \
./src/network/test/error-model-test-suite.o \
./src/network/test/ipv6-address-test-suite.o \
./src/network/test/lollipop-counter-test.o \
./src/network/test/packet-metadata-test.o \
./src/network/test/packet-socket-apps-test-suite.o \
./src/network/test/packet-test-suite.o \
./src/network/test/packetbb-test-suite.o \
./src/network/test/pcap-file-test-suite.o \
./src/network/test/sequence-number-test-suite.o \
./src/network/test/test-data-rate.o 


# Each subdirectory must supply rules for building sources it contributes
src/network/test/%.o: ../src/network/test/%.cc src/network/test/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-network-2f-test

clean-src-2f-network-2f-test:
	-$(RM) ./src/network/test/bit-serializer-test.d ./src/network/test/bit-serializer-test.o ./src/network/test/buffer-test.d ./src/network/test/buffer-test.o ./src/network/test/drop-tail-queue-test-suite.d ./src/network/test/drop-tail-queue-test-suite.o ./src/network/test/error-model-test-suite.d ./src/network/test/error-model-test-suite.o ./src/network/test/ipv6-address-test-suite.d ./src/network/test/ipv6-address-test-suite.o ./src/network/test/lollipop-counter-test.d ./src/network/test/lollipop-counter-test.o ./src/network/test/packet-metadata-test.d ./src/network/test/packet-metadata-test.o ./src/network/test/packet-socket-apps-test-suite.d ./src/network/test/packet-socket-apps-test-suite.o ./src/network/test/packet-test-suite.d ./src/network/test/packet-test-suite.o ./src/network/test/packetbb-test-suite.d ./src/network/test/packetbb-test-suite.o ./src/network/test/pcap-file-test-suite.d ./src/network/test/pcap-file-test-suite.o ./src/network/test/sequence-number-test-suite.d ./src/network/test/sequence-number-test-suite.o ./src/network/test/test-data-rate.d ./src/network/test/test-data-rate.o

.PHONY: clean-src-2f-network-2f-test


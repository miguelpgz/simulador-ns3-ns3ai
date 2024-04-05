################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../examples/tcp/dctcp-example.cc \
../examples/tcp/star.cc \
../examples/tcp/tcp-bbr-example.cc \
../examples/tcp/tcp-bulk-send.cc \
../examples/tcp/tcp-large-transfer.cc \
../examples/tcp/tcp-linux-reno.cc \
../examples/tcp/tcp-pacing.cc \
../examples/tcp/tcp-pcap-nanosec-example.cc \
../examples/tcp/tcp-star-server.cc \
../examples/tcp/tcp-validation.cc \
../examples/tcp/tcp-variants-comparison.cc 

CC_DEPS += \
./examples/tcp/dctcp-example.d \
./examples/tcp/star.d \
./examples/tcp/tcp-bbr-example.d \
./examples/tcp/tcp-bulk-send.d \
./examples/tcp/tcp-large-transfer.d \
./examples/tcp/tcp-linux-reno.d \
./examples/tcp/tcp-pacing.d \
./examples/tcp/tcp-pcap-nanosec-example.d \
./examples/tcp/tcp-star-server.d \
./examples/tcp/tcp-validation.d \
./examples/tcp/tcp-variants-comparison.d 

OBJS += \
./examples/tcp/dctcp-example.o \
./examples/tcp/star.o \
./examples/tcp/tcp-bbr-example.o \
./examples/tcp/tcp-bulk-send.o \
./examples/tcp/tcp-large-transfer.o \
./examples/tcp/tcp-linux-reno.o \
./examples/tcp/tcp-pacing.o \
./examples/tcp/tcp-pcap-nanosec-example.o \
./examples/tcp/tcp-star-server.o \
./examples/tcp/tcp-validation.o \
./examples/tcp/tcp-variants-comparison.o 


# Each subdirectory must supply rules for building sources it contributes
examples/tcp/%.o: ../examples/tcp/%.cc examples/tcp/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-examples-2f-tcp

clean-examples-2f-tcp:
	-$(RM) ./examples/tcp/dctcp-example.d ./examples/tcp/dctcp-example.o ./examples/tcp/star.d ./examples/tcp/star.o ./examples/tcp/tcp-bbr-example.d ./examples/tcp/tcp-bbr-example.o ./examples/tcp/tcp-bulk-send.d ./examples/tcp/tcp-bulk-send.o ./examples/tcp/tcp-large-transfer.d ./examples/tcp/tcp-large-transfer.o ./examples/tcp/tcp-linux-reno.d ./examples/tcp/tcp-linux-reno.o ./examples/tcp/tcp-pacing.d ./examples/tcp/tcp-pacing.o ./examples/tcp/tcp-pcap-nanosec-example.d ./examples/tcp/tcp-pcap-nanosec-example.o ./examples/tcp/tcp-star-server.d ./examples/tcp/tcp-star-server.o ./examples/tcp/tcp-validation.d ./examples/tcp/tcp-validation.o ./examples/tcp/tcp-variants-comparison.d ./examples/tcp/tcp-variants-comparison.o

.PHONY: clean-examples-2f-tcp


################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/test/ns3tcp/ns3tcp-loss-test-suite.cc \
../src/test/ns3tcp/ns3tcp-no-delay-test-suite.cc \
../src/test/ns3tcp/ns3tcp-socket-test-suite.cc \
../src/test/ns3tcp/ns3tcp-socket-writer.cc \
../src/test/ns3tcp/ns3tcp-state-test-suite.cc 

CC_DEPS += \
./src/test/ns3tcp/ns3tcp-loss-test-suite.d \
./src/test/ns3tcp/ns3tcp-no-delay-test-suite.d \
./src/test/ns3tcp/ns3tcp-socket-test-suite.d \
./src/test/ns3tcp/ns3tcp-socket-writer.d \
./src/test/ns3tcp/ns3tcp-state-test-suite.d 

OBJS += \
./src/test/ns3tcp/ns3tcp-loss-test-suite.o \
./src/test/ns3tcp/ns3tcp-no-delay-test-suite.o \
./src/test/ns3tcp/ns3tcp-socket-test-suite.o \
./src/test/ns3tcp/ns3tcp-socket-writer.o \
./src/test/ns3tcp/ns3tcp-state-test-suite.o 


# Each subdirectory must supply rules for building sources it contributes
src/test/ns3tcp/%.o: ../src/test/ns3tcp/%.cc src/test/ns3tcp/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-test-2f-ns3tcp

clean-src-2f-test-2f-ns3tcp:
	-$(RM) ./src/test/ns3tcp/ns3tcp-loss-test-suite.d ./src/test/ns3tcp/ns3tcp-loss-test-suite.o ./src/test/ns3tcp/ns3tcp-no-delay-test-suite.d ./src/test/ns3tcp/ns3tcp-no-delay-test-suite.o ./src/test/ns3tcp/ns3tcp-socket-test-suite.d ./src/test/ns3tcp/ns3tcp-socket-test-suite.o ./src/test/ns3tcp/ns3tcp-socket-writer.d ./src/test/ns3tcp/ns3tcp-socket-writer.o ./src/test/ns3tcp/ns3tcp-state-test-suite.d ./src/test/ns3tcp/ns3tcp-state-test-suite.o

.PHONY: clean-src-2f-test-2f-ns3tcp


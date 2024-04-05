################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/traffic-control/test/adaptive-red-queue-disc-test-suite.cc \
../src/traffic-control/test/cobalt-queue-disc-test-suite.cc \
../src/traffic-control/test/codel-queue-disc-test-suite.cc \
../src/traffic-control/test/fifo-queue-disc-test-suite.cc \
../src/traffic-control/test/pie-queue-disc-test-suite.cc \
../src/traffic-control/test/prio-queue-disc-test-suite.cc \
../src/traffic-control/test/queue-disc-traces-test-suite.cc \
../src/traffic-control/test/red-queue-disc-test-suite.cc \
../src/traffic-control/test/tbf-queue-disc-test-suite.cc \
../src/traffic-control/test/tc-flow-control-test-suite.cc 

CC_DEPS += \
./src/traffic-control/test/adaptive-red-queue-disc-test-suite.d \
./src/traffic-control/test/cobalt-queue-disc-test-suite.d \
./src/traffic-control/test/codel-queue-disc-test-suite.d \
./src/traffic-control/test/fifo-queue-disc-test-suite.d \
./src/traffic-control/test/pie-queue-disc-test-suite.d \
./src/traffic-control/test/prio-queue-disc-test-suite.d \
./src/traffic-control/test/queue-disc-traces-test-suite.d \
./src/traffic-control/test/red-queue-disc-test-suite.d \
./src/traffic-control/test/tbf-queue-disc-test-suite.d \
./src/traffic-control/test/tc-flow-control-test-suite.d 

OBJS += \
./src/traffic-control/test/adaptive-red-queue-disc-test-suite.o \
./src/traffic-control/test/cobalt-queue-disc-test-suite.o \
./src/traffic-control/test/codel-queue-disc-test-suite.o \
./src/traffic-control/test/fifo-queue-disc-test-suite.o \
./src/traffic-control/test/pie-queue-disc-test-suite.o \
./src/traffic-control/test/prio-queue-disc-test-suite.o \
./src/traffic-control/test/queue-disc-traces-test-suite.o \
./src/traffic-control/test/red-queue-disc-test-suite.o \
./src/traffic-control/test/tbf-queue-disc-test-suite.o \
./src/traffic-control/test/tc-flow-control-test-suite.o 


# Each subdirectory must supply rules for building sources it contributes
src/traffic-control/test/%.o: ../src/traffic-control/test/%.cc src/traffic-control/test/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-traffic-2d-control-2f-test

clean-src-2f-traffic-2d-control-2f-test:
	-$(RM) ./src/traffic-control/test/adaptive-red-queue-disc-test-suite.d ./src/traffic-control/test/adaptive-red-queue-disc-test-suite.o ./src/traffic-control/test/cobalt-queue-disc-test-suite.d ./src/traffic-control/test/cobalt-queue-disc-test-suite.o ./src/traffic-control/test/codel-queue-disc-test-suite.d ./src/traffic-control/test/codel-queue-disc-test-suite.o ./src/traffic-control/test/fifo-queue-disc-test-suite.d ./src/traffic-control/test/fifo-queue-disc-test-suite.o ./src/traffic-control/test/pie-queue-disc-test-suite.d ./src/traffic-control/test/pie-queue-disc-test-suite.o ./src/traffic-control/test/prio-queue-disc-test-suite.d ./src/traffic-control/test/prio-queue-disc-test-suite.o ./src/traffic-control/test/queue-disc-traces-test-suite.d ./src/traffic-control/test/queue-disc-traces-test-suite.o ./src/traffic-control/test/red-queue-disc-test-suite.d ./src/traffic-control/test/red-queue-disc-test-suite.o ./src/traffic-control/test/tbf-queue-disc-test-suite.d ./src/traffic-control/test/tbf-queue-disc-test-suite.o ./src/traffic-control/test/tc-flow-control-test-suite.d ./src/traffic-control/test/tc-flow-control-test-suite.o

.PHONY: clean-src-2f-traffic-2d-control-2f-test


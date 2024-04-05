################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/core/examples/build-version-example.cc \
../src/core/examples/command-line-example.cc \
../src/core/examples/empirical-random-variable-example.cc \
../src/core/examples/fatal-example.cc \
../src/core/examples/hash-example.cc \
../src/core/examples/length-example.cc \
../src/core/examples/main-callback.cc \
../src/core/examples/main-ptr.cc \
../src/core/examples/main-random-variable-stream.cc \
../src/core/examples/main-test-sync.cc \
../src/core/examples/sample-log-time-format.cc \
../src/core/examples/sample-random-variable-stream.cc \
../src/core/examples/sample-random-variable.cc \
../src/core/examples/sample-show-progress.cc \
../src/core/examples/sample-simulator.cc \
../src/core/examples/system-path-examples.cc \
../src/core/examples/test-string-value-formatting.cc 

CC_DEPS += \
./src/core/examples/build-version-example.d \
./src/core/examples/command-line-example.d \
./src/core/examples/empirical-random-variable-example.d \
./src/core/examples/fatal-example.d \
./src/core/examples/hash-example.d \
./src/core/examples/length-example.d \
./src/core/examples/main-callback.d \
./src/core/examples/main-ptr.d \
./src/core/examples/main-random-variable-stream.d \
./src/core/examples/main-test-sync.d \
./src/core/examples/sample-log-time-format.d \
./src/core/examples/sample-random-variable-stream.d \
./src/core/examples/sample-random-variable.d \
./src/core/examples/sample-show-progress.d \
./src/core/examples/sample-simulator.d \
./src/core/examples/system-path-examples.d \
./src/core/examples/test-string-value-formatting.d 

OBJS += \
./src/core/examples/build-version-example.o \
./src/core/examples/command-line-example.o \
./src/core/examples/empirical-random-variable-example.o \
./src/core/examples/fatal-example.o \
./src/core/examples/hash-example.o \
./src/core/examples/length-example.o \
./src/core/examples/main-callback.o \
./src/core/examples/main-ptr.o \
./src/core/examples/main-random-variable-stream.o \
./src/core/examples/main-test-sync.o \
./src/core/examples/sample-log-time-format.o \
./src/core/examples/sample-random-variable-stream.o \
./src/core/examples/sample-random-variable.o \
./src/core/examples/sample-show-progress.o \
./src/core/examples/sample-simulator.o \
./src/core/examples/system-path-examples.o \
./src/core/examples/test-string-value-formatting.o 


# Each subdirectory must supply rules for building sources it contributes
src/core/examples/%.o: ../src/core/examples/%.cc src/core/examples/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-core-2f-examples

clean-src-2f-core-2f-examples:
	-$(RM) ./src/core/examples/build-version-example.d ./src/core/examples/build-version-example.o ./src/core/examples/command-line-example.d ./src/core/examples/command-line-example.o ./src/core/examples/empirical-random-variable-example.d ./src/core/examples/empirical-random-variable-example.o ./src/core/examples/fatal-example.d ./src/core/examples/fatal-example.o ./src/core/examples/hash-example.d ./src/core/examples/hash-example.o ./src/core/examples/length-example.d ./src/core/examples/length-example.o ./src/core/examples/main-callback.d ./src/core/examples/main-callback.o ./src/core/examples/main-ptr.d ./src/core/examples/main-ptr.o ./src/core/examples/main-random-variable-stream.d ./src/core/examples/main-random-variable-stream.o ./src/core/examples/main-test-sync.d ./src/core/examples/main-test-sync.o ./src/core/examples/sample-log-time-format.d ./src/core/examples/sample-log-time-format.o ./src/core/examples/sample-random-variable-stream.d ./src/core/examples/sample-random-variable-stream.o ./src/core/examples/sample-random-variable.d ./src/core/examples/sample-random-variable.o ./src/core/examples/sample-show-progress.d ./src/core/examples/sample-show-progress.o ./src/core/examples/sample-simulator.d ./src/core/examples/sample-simulator.o ./src/core/examples/system-path-examples.d ./src/core/examples/system-path-examples.o ./src/core/examples/test-string-value-formatting.d ./src/core/examples/test-string-value-formatting.o

.PHONY: clean-src-2f-core-2f-examples


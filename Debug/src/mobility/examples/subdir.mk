################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/mobility/examples/bonnmotion-ns2-example.cc \
../src/mobility/examples/main-grid-topology.cc \
../src/mobility/examples/main-random-topology.cc \
../src/mobility/examples/main-random-walk.cc \
../src/mobility/examples/mobility-trace-example.cc \
../src/mobility/examples/ns2-mobility-trace.cc \
../src/mobility/examples/reference-point-group-mobility-example.cc 

CC_DEPS += \
./src/mobility/examples/bonnmotion-ns2-example.d \
./src/mobility/examples/main-grid-topology.d \
./src/mobility/examples/main-random-topology.d \
./src/mobility/examples/main-random-walk.d \
./src/mobility/examples/mobility-trace-example.d \
./src/mobility/examples/ns2-mobility-trace.d \
./src/mobility/examples/reference-point-group-mobility-example.d 

OBJS += \
./src/mobility/examples/bonnmotion-ns2-example.o \
./src/mobility/examples/main-grid-topology.o \
./src/mobility/examples/main-random-topology.o \
./src/mobility/examples/main-random-walk.o \
./src/mobility/examples/mobility-trace-example.o \
./src/mobility/examples/ns2-mobility-trace.o \
./src/mobility/examples/reference-point-group-mobility-example.o 


# Each subdirectory must supply rules for building sources it contributes
src/mobility/examples/%.o: ../src/mobility/examples/%.cc src/mobility/examples/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-mobility-2f-examples

clean-src-2f-mobility-2f-examples:
	-$(RM) ./src/mobility/examples/bonnmotion-ns2-example.d ./src/mobility/examples/bonnmotion-ns2-example.o ./src/mobility/examples/main-grid-topology.d ./src/mobility/examples/main-grid-topology.o ./src/mobility/examples/main-random-topology.d ./src/mobility/examples/main-random-topology.o ./src/mobility/examples/main-random-walk.d ./src/mobility/examples/main-random-walk.o ./src/mobility/examples/mobility-trace-example.d ./src/mobility/examples/mobility-trace-example.o ./src/mobility/examples/ns2-mobility-trace.d ./src/mobility/examples/ns2-mobility-trace.o ./src/mobility/examples/reference-point-group-mobility-example.d ./src/mobility/examples/reference-point-group-mobility-example.o

.PHONY: clean-src-2f-mobility-2f-examples


################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../examples/traffic-control/cobalt-vs-codel.cc \
../examples/traffic-control/queue-discs-benchmark.cc \
../examples/traffic-control/red-vs-fengadaptive.cc \
../examples/traffic-control/red-vs-nlred.cc \
../examples/traffic-control/tbf-example.cc \
../examples/traffic-control/traffic-control.cc 

CC_DEPS += \
./examples/traffic-control/cobalt-vs-codel.d \
./examples/traffic-control/queue-discs-benchmark.d \
./examples/traffic-control/red-vs-fengadaptive.d \
./examples/traffic-control/red-vs-nlred.d \
./examples/traffic-control/tbf-example.d \
./examples/traffic-control/traffic-control.d 

OBJS += \
./examples/traffic-control/cobalt-vs-codel.o \
./examples/traffic-control/queue-discs-benchmark.o \
./examples/traffic-control/red-vs-fengadaptive.o \
./examples/traffic-control/red-vs-nlred.o \
./examples/traffic-control/tbf-example.o \
./examples/traffic-control/traffic-control.o 


# Each subdirectory must supply rules for building sources it contributes
examples/traffic-control/%.o: ../examples/traffic-control/%.cc examples/traffic-control/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-examples-2f-traffic-2d-control

clean-examples-2f-traffic-2d-control:
	-$(RM) ./examples/traffic-control/cobalt-vs-codel.d ./examples/traffic-control/cobalt-vs-codel.o ./examples/traffic-control/queue-discs-benchmark.d ./examples/traffic-control/queue-discs-benchmark.o ./examples/traffic-control/red-vs-fengadaptive.d ./examples/traffic-control/red-vs-fengadaptive.o ./examples/traffic-control/red-vs-nlred.d ./examples/traffic-control/red-vs-nlred.o ./examples/traffic-control/tbf-example.d ./examples/traffic-control/tbf-example.o ./examples/traffic-control/traffic-control.d ./examples/traffic-control/traffic-control.o

.PHONY: clean-examples-2f-traffic-2d-control


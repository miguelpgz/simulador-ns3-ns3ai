################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/netanim/examples/colors-link-description.cc \
../src/netanim/examples/dumbbell-animation.cc \
../src/netanim/examples/grid-animation.cc \
../src/netanim/examples/resources-counters.cc \
../src/netanim/examples/star-animation.cc \
../src/netanim/examples/uan-animation.cc \
../src/netanim/examples/wireless-animation.cc 

CC_DEPS += \
./src/netanim/examples/colors-link-description.d \
./src/netanim/examples/dumbbell-animation.d \
./src/netanim/examples/grid-animation.d \
./src/netanim/examples/resources-counters.d \
./src/netanim/examples/star-animation.d \
./src/netanim/examples/uan-animation.d \
./src/netanim/examples/wireless-animation.d 

OBJS += \
./src/netanim/examples/colors-link-description.o \
./src/netanim/examples/dumbbell-animation.o \
./src/netanim/examples/grid-animation.o \
./src/netanim/examples/resources-counters.o \
./src/netanim/examples/star-animation.o \
./src/netanim/examples/uan-animation.o \
./src/netanim/examples/wireless-animation.o 


# Each subdirectory must supply rules for building sources it contributes
src/netanim/examples/%.o: ../src/netanim/examples/%.cc src/netanim/examples/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-netanim-2f-examples

clean-src-2f-netanim-2f-examples:
	-$(RM) ./src/netanim/examples/colors-link-description.d ./src/netanim/examples/colors-link-description.o ./src/netanim/examples/dumbbell-animation.d ./src/netanim/examples/dumbbell-animation.o ./src/netanim/examples/grid-animation.d ./src/netanim/examples/grid-animation.o ./src/netanim/examples/resources-counters.d ./src/netanim/examples/resources-counters.o ./src/netanim/examples/star-animation.d ./src/netanim/examples/star-animation.o ./src/netanim/examples/uan-animation.d ./src/netanim/examples/uan-animation.o ./src/netanim/examples/wireless-animation.d ./src/netanim/examples/wireless-animation.o

.PHONY: clean-src-2f-netanim-2f-examples


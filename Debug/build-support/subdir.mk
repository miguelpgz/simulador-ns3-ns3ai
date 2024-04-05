################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../build-support/empty-main.cc \
../build-support/empty.cc 

CC_DEPS += \
./build-support/empty-main.d \
./build-support/empty.d 

OBJS += \
./build-support/empty-main.o \
./build-support/empty.o 


# Each subdirectory must supply rules for building sources it contributes
build-support/%.o: ../build-support/%.cc build-support/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-build-2d-support

clean-build-2d-support:
	-$(RM) ./build-support/empty-main.d ./build-support/empty-main.o ./build-support/empty.d ./build-support/empty.o

.PHONY: clean-build-2d-support


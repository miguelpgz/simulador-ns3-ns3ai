################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/olsr/examples/olsr-hna.cc \
../src/olsr/examples/simple-point-to-point-olsr.cc 

CC_DEPS += \
./src/olsr/examples/olsr-hna.d \
./src/olsr/examples/simple-point-to-point-olsr.d 

OBJS += \
./src/olsr/examples/olsr-hna.o \
./src/olsr/examples/simple-point-to-point-olsr.o 


# Each subdirectory must supply rules for building sources it contributes
src/olsr/examples/%.o: ../src/olsr/examples/%.cc src/olsr/examples/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-olsr-2f-examples

clean-src-2f-olsr-2f-examples:
	-$(RM) ./src/olsr/examples/olsr-hna.d ./src/olsr/examples/olsr-hna.o ./src/olsr/examples/simple-point-to-point-olsr.d ./src/olsr/examples/simple-point-to-point-olsr.o

.PHONY: clean-src-2f-olsr-2f-examples


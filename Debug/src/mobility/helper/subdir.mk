################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/mobility/helper/group-mobility-helper.cc \
../src/mobility/helper/mobility-helper.cc \
../src/mobility/helper/ns2-mobility-helper.cc 

CC_DEPS += \
./src/mobility/helper/group-mobility-helper.d \
./src/mobility/helper/mobility-helper.d \
./src/mobility/helper/ns2-mobility-helper.d 

OBJS += \
./src/mobility/helper/group-mobility-helper.o \
./src/mobility/helper/mobility-helper.o \
./src/mobility/helper/ns2-mobility-helper.o 


# Each subdirectory must supply rules for building sources it contributes
src/mobility/helper/%.o: ../src/mobility/helper/%.cc src/mobility/helper/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-mobility-2f-helper

clean-src-2f-mobility-2f-helper:
	-$(RM) ./src/mobility/helper/group-mobility-helper.d ./src/mobility/helper/group-mobility-helper.o ./src/mobility/helper/mobility-helper.d ./src/mobility/helper/mobility-helper.o ./src/mobility/helper/ns2-mobility-helper.d ./src/mobility/helper/ns2-mobility-helper.o

.PHONY: clean-src-2f-mobility-2f-helper


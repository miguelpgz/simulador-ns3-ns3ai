################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/stats/helper/file-helper.cc \
../src/stats/helper/gnuplot-helper.cc 

CC_DEPS += \
./src/stats/helper/file-helper.d \
./src/stats/helper/gnuplot-helper.d 

OBJS += \
./src/stats/helper/file-helper.o \
./src/stats/helper/gnuplot-helper.o 


# Each subdirectory must supply rules for building sources it contributes
src/stats/helper/%.o: ../src/stats/helper/%.cc src/stats/helper/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-stats-2f-helper

clean-src-2f-stats-2f-helper:
	-$(RM) ./src/stats/helper/file-helper.d ./src/stats/helper/file-helper.o ./src/stats/helper/gnuplot-helper.d ./src/stats/helper/gnuplot-helper.o

.PHONY: clean-src-2f-stats-2f-helper


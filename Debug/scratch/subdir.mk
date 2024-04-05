################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../scratch/first.cc \
../scratch/scratch-simulator.cc \
../scratch/tutorial-app.cc \
../scratch/wifi-ap-flowmonitor.cc \
../scratch/wifi-ap-modified.cc \
../scratch/wifi-ap.cc 

CC_DEPS += \
./scratch/first.d \
./scratch/scratch-simulator.d \
./scratch/tutorial-app.d \
./scratch/wifi-ap-flowmonitor.d \
./scratch/wifi-ap-modified.d \
./scratch/wifi-ap.d 

OBJS += \
./scratch/first.o \
./scratch/scratch-simulator.o \
./scratch/tutorial-app.o \
./scratch/wifi-ap-flowmonitor.o \
./scratch/wifi-ap-modified.o \
./scratch/wifi-ap.o 


# Each subdirectory must supply rules for building sources it contributes
scratch/%.o: ../scratch/%.cc scratch/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-scratch

clean-scratch:
	-$(RM) ./scratch/first.d ./scratch/first.o ./scratch/scratch-simulator.d ./scratch/scratch-simulator.o ./scratch/tutorial-app.d ./scratch/tutorial-app.o ./scratch/wifi-ap-flowmonitor.d ./scratch/wifi-ap-flowmonitor.o ./scratch/wifi-ap-modified.d ./scratch/wifi-ap-modified.o ./scratch/wifi-ap.d ./scratch/wifi-ap.o

.PHONY: clean-scratch


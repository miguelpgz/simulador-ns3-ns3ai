################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/wifi/model/he/constant-obss-pd-algorithm.cc \
../src/wifi/model/he/he-capabilities.cc \
../src/wifi/model/he/he-configuration.cc \
../src/wifi/model/he/he-frame-exchange-manager.cc \
../src/wifi/model/he/he-operation.cc \
../src/wifi/model/he/he-phy.cc \
../src/wifi/model/he/he-ppdu.cc \
../src/wifi/model/he/he-ru.cc \
../src/wifi/model/he/mu-edca-parameter-set.cc \
../src/wifi/model/he/mu-snr-tag.cc \
../src/wifi/model/he/multi-user-scheduler.cc \
../src/wifi/model/he/obss-pd-algorithm.cc \
../src/wifi/model/he/rr-multi-user-scheduler.cc 

CC_DEPS += \
./src/wifi/model/he/constant-obss-pd-algorithm.d \
./src/wifi/model/he/he-capabilities.d \
./src/wifi/model/he/he-configuration.d \
./src/wifi/model/he/he-frame-exchange-manager.d \
./src/wifi/model/he/he-operation.d \
./src/wifi/model/he/he-phy.d \
./src/wifi/model/he/he-ppdu.d \
./src/wifi/model/he/he-ru.d \
./src/wifi/model/he/mu-edca-parameter-set.d \
./src/wifi/model/he/mu-snr-tag.d \
./src/wifi/model/he/multi-user-scheduler.d \
./src/wifi/model/he/obss-pd-algorithm.d \
./src/wifi/model/he/rr-multi-user-scheduler.d 

OBJS += \
./src/wifi/model/he/constant-obss-pd-algorithm.o \
./src/wifi/model/he/he-capabilities.o \
./src/wifi/model/he/he-configuration.o \
./src/wifi/model/he/he-frame-exchange-manager.o \
./src/wifi/model/he/he-operation.o \
./src/wifi/model/he/he-phy.o \
./src/wifi/model/he/he-ppdu.o \
./src/wifi/model/he/he-ru.o \
./src/wifi/model/he/mu-edca-parameter-set.o \
./src/wifi/model/he/mu-snr-tag.o \
./src/wifi/model/he/multi-user-scheduler.o \
./src/wifi/model/he/obss-pd-algorithm.o \
./src/wifi/model/he/rr-multi-user-scheduler.o 


# Each subdirectory must supply rules for building sources it contributes
src/wifi/model/he/%.o: ../src/wifi/model/he/%.cc src/wifi/model/he/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-wifi-2f-model-2f-he

clean-src-2f-wifi-2f-model-2f-he:
	-$(RM) ./src/wifi/model/he/constant-obss-pd-algorithm.d ./src/wifi/model/he/constant-obss-pd-algorithm.o ./src/wifi/model/he/he-capabilities.d ./src/wifi/model/he/he-capabilities.o ./src/wifi/model/he/he-configuration.d ./src/wifi/model/he/he-configuration.o ./src/wifi/model/he/he-frame-exchange-manager.d ./src/wifi/model/he/he-frame-exchange-manager.o ./src/wifi/model/he/he-operation.d ./src/wifi/model/he/he-operation.o ./src/wifi/model/he/he-phy.d ./src/wifi/model/he/he-phy.o ./src/wifi/model/he/he-ppdu.d ./src/wifi/model/he/he-ppdu.o ./src/wifi/model/he/he-ru.d ./src/wifi/model/he/he-ru.o ./src/wifi/model/he/mu-edca-parameter-set.d ./src/wifi/model/he/mu-edca-parameter-set.o ./src/wifi/model/he/mu-snr-tag.d ./src/wifi/model/he/mu-snr-tag.o ./src/wifi/model/he/multi-user-scheduler.d ./src/wifi/model/he/multi-user-scheduler.o ./src/wifi/model/he/obss-pd-algorithm.d ./src/wifi/model/he/obss-pd-algorithm.o ./src/wifi/model/he/rr-multi-user-scheduler.d ./src/wifi/model/he/rr-multi-user-scheduler.o

.PHONY: clean-src-2f-wifi-2f-model-2f-he


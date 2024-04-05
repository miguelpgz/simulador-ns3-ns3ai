################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/wifi/model/non-ht/dsss-error-rate-model.cc \
../src/wifi/model/non-ht/dsss-parameter-set.cc \
../src/wifi/model/non-ht/dsss-phy.cc \
../src/wifi/model/non-ht/dsss-ppdu.cc \
../src/wifi/model/non-ht/erp-information.cc \
../src/wifi/model/non-ht/erp-ofdm-phy.cc \
../src/wifi/model/non-ht/erp-ofdm-ppdu.cc \
../src/wifi/model/non-ht/ofdm-phy.cc \
../src/wifi/model/non-ht/ofdm-ppdu.cc 

CC_DEPS += \
./src/wifi/model/non-ht/dsss-error-rate-model.d \
./src/wifi/model/non-ht/dsss-parameter-set.d \
./src/wifi/model/non-ht/dsss-phy.d \
./src/wifi/model/non-ht/dsss-ppdu.d \
./src/wifi/model/non-ht/erp-information.d \
./src/wifi/model/non-ht/erp-ofdm-phy.d \
./src/wifi/model/non-ht/erp-ofdm-ppdu.d \
./src/wifi/model/non-ht/ofdm-phy.d \
./src/wifi/model/non-ht/ofdm-ppdu.d 

OBJS += \
./src/wifi/model/non-ht/dsss-error-rate-model.o \
./src/wifi/model/non-ht/dsss-parameter-set.o \
./src/wifi/model/non-ht/dsss-phy.o \
./src/wifi/model/non-ht/dsss-ppdu.o \
./src/wifi/model/non-ht/erp-information.o \
./src/wifi/model/non-ht/erp-ofdm-phy.o \
./src/wifi/model/non-ht/erp-ofdm-ppdu.o \
./src/wifi/model/non-ht/ofdm-phy.o \
./src/wifi/model/non-ht/ofdm-ppdu.o 


# Each subdirectory must supply rules for building sources it contributes
src/wifi/model/non-ht/%.o: ../src/wifi/model/non-ht/%.cc src/wifi/model/non-ht/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-wifi-2f-model-2f-non-2d-ht

clean-src-2f-wifi-2f-model-2f-non-2d-ht:
	-$(RM) ./src/wifi/model/non-ht/dsss-error-rate-model.d ./src/wifi/model/non-ht/dsss-error-rate-model.o ./src/wifi/model/non-ht/dsss-parameter-set.d ./src/wifi/model/non-ht/dsss-parameter-set.o ./src/wifi/model/non-ht/dsss-phy.d ./src/wifi/model/non-ht/dsss-phy.o ./src/wifi/model/non-ht/dsss-ppdu.d ./src/wifi/model/non-ht/dsss-ppdu.o ./src/wifi/model/non-ht/erp-information.d ./src/wifi/model/non-ht/erp-information.o ./src/wifi/model/non-ht/erp-ofdm-phy.d ./src/wifi/model/non-ht/erp-ofdm-phy.o ./src/wifi/model/non-ht/erp-ofdm-ppdu.d ./src/wifi/model/non-ht/erp-ofdm-ppdu.o ./src/wifi/model/non-ht/ofdm-phy.d ./src/wifi/model/non-ht/ofdm-phy.o ./src/wifi/model/non-ht/ofdm-ppdu.d ./src/wifi/model/non-ht/ofdm-ppdu.o

.PHONY: clean-src-2f-wifi-2f-model-2f-non-2d-ht


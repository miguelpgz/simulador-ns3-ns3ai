################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/lte/examples/lena-cc-helper.cc \
../src/lte/examples/lena-cqi-threshold.cc \
../src/lte/examples/lena-deactivate-bearer.cc \
../src/lte/examples/lena-distributed-ffr.cc \
../src/lte/examples/lena-dual-stripe.cc \
../src/lte/examples/lena-fading.cc \
../src/lte/examples/lena-frequency-reuse.cc \
../src/lte/examples/lena-intercell-interference.cc \
../src/lte/examples/lena-ipv6-addr-conf.cc \
../src/lte/examples/lena-ipv6-ue-rh.cc \
../src/lte/examples/lena-ipv6-ue-ue.cc \
../src/lte/examples/lena-pathloss-traces.cc \
../src/lte/examples/lena-profiling.cc \
../src/lte/examples/lena-radio-link-failure.cc \
../src/lte/examples/lena-rem-sector-antenna.cc \
../src/lte/examples/lena-rem.cc \
../src/lte/examples/lena-rlc-traces.cc \
../src/lte/examples/lena-simple-epc-backhaul.cc \
../src/lte/examples/lena-simple-epc-emu.cc \
../src/lte/examples/lena-simple-epc.cc \
../src/lte/examples/lena-simple.cc \
../src/lte/examples/lena-uplink-power-control.cc \
../src/lte/examples/lena-x2-handover-measures.cc \
../src/lte/examples/lena-x2-handover.cc 

CC_DEPS += \
./src/lte/examples/lena-cc-helper.d \
./src/lte/examples/lena-cqi-threshold.d \
./src/lte/examples/lena-deactivate-bearer.d \
./src/lte/examples/lena-distributed-ffr.d \
./src/lte/examples/lena-dual-stripe.d \
./src/lte/examples/lena-fading.d \
./src/lte/examples/lena-frequency-reuse.d \
./src/lte/examples/lena-intercell-interference.d \
./src/lte/examples/lena-ipv6-addr-conf.d \
./src/lte/examples/lena-ipv6-ue-rh.d \
./src/lte/examples/lena-ipv6-ue-ue.d \
./src/lte/examples/lena-pathloss-traces.d \
./src/lte/examples/lena-profiling.d \
./src/lte/examples/lena-radio-link-failure.d \
./src/lte/examples/lena-rem-sector-antenna.d \
./src/lte/examples/lena-rem.d \
./src/lte/examples/lena-rlc-traces.d \
./src/lte/examples/lena-simple-epc-backhaul.d \
./src/lte/examples/lena-simple-epc-emu.d \
./src/lte/examples/lena-simple-epc.d \
./src/lte/examples/lena-simple.d \
./src/lte/examples/lena-uplink-power-control.d \
./src/lte/examples/lena-x2-handover-measures.d \
./src/lte/examples/lena-x2-handover.d 

OBJS += \
./src/lte/examples/lena-cc-helper.o \
./src/lte/examples/lena-cqi-threshold.o \
./src/lte/examples/lena-deactivate-bearer.o \
./src/lte/examples/lena-distributed-ffr.o \
./src/lte/examples/lena-dual-stripe.o \
./src/lte/examples/lena-fading.o \
./src/lte/examples/lena-frequency-reuse.o \
./src/lte/examples/lena-intercell-interference.o \
./src/lte/examples/lena-ipv6-addr-conf.o \
./src/lte/examples/lena-ipv6-ue-rh.o \
./src/lte/examples/lena-ipv6-ue-ue.o \
./src/lte/examples/lena-pathloss-traces.o \
./src/lte/examples/lena-profiling.o \
./src/lte/examples/lena-radio-link-failure.o \
./src/lte/examples/lena-rem-sector-antenna.o \
./src/lte/examples/lena-rem.o \
./src/lte/examples/lena-rlc-traces.o \
./src/lte/examples/lena-simple-epc-backhaul.o \
./src/lte/examples/lena-simple-epc-emu.o \
./src/lte/examples/lena-simple-epc.o \
./src/lte/examples/lena-simple.o \
./src/lte/examples/lena-uplink-power-control.o \
./src/lte/examples/lena-x2-handover-measures.o \
./src/lte/examples/lena-x2-handover.o 


# Each subdirectory must supply rules for building sources it contributes
src/lte/examples/%.o: ../src/lte/examples/%.cc src/lte/examples/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-lte-2f-examples

clean-src-2f-lte-2f-examples:
	-$(RM) ./src/lte/examples/lena-cc-helper.d ./src/lte/examples/lena-cc-helper.o ./src/lte/examples/lena-cqi-threshold.d ./src/lte/examples/lena-cqi-threshold.o ./src/lte/examples/lena-deactivate-bearer.d ./src/lte/examples/lena-deactivate-bearer.o ./src/lte/examples/lena-distributed-ffr.d ./src/lte/examples/lena-distributed-ffr.o ./src/lte/examples/lena-dual-stripe.d ./src/lte/examples/lena-dual-stripe.o ./src/lte/examples/lena-fading.d ./src/lte/examples/lena-fading.o ./src/lte/examples/lena-frequency-reuse.d ./src/lte/examples/lena-frequency-reuse.o ./src/lte/examples/lena-intercell-interference.d ./src/lte/examples/lena-intercell-interference.o ./src/lte/examples/lena-ipv6-addr-conf.d ./src/lte/examples/lena-ipv6-addr-conf.o ./src/lte/examples/lena-ipv6-ue-rh.d ./src/lte/examples/lena-ipv6-ue-rh.o ./src/lte/examples/lena-ipv6-ue-ue.d ./src/lte/examples/lena-ipv6-ue-ue.o ./src/lte/examples/lena-pathloss-traces.d ./src/lte/examples/lena-pathloss-traces.o ./src/lte/examples/lena-profiling.d ./src/lte/examples/lena-profiling.o ./src/lte/examples/lena-radio-link-failure.d ./src/lte/examples/lena-radio-link-failure.o ./src/lte/examples/lena-rem-sector-antenna.d ./src/lte/examples/lena-rem-sector-antenna.o ./src/lte/examples/lena-rem.d ./src/lte/examples/lena-rem.o ./src/lte/examples/lena-rlc-traces.d ./src/lte/examples/lena-rlc-traces.o ./src/lte/examples/lena-simple-epc-backhaul.d ./src/lte/examples/lena-simple-epc-backhaul.o ./src/lte/examples/lena-simple-epc-emu.d ./src/lte/examples/lena-simple-epc-emu.o ./src/lte/examples/lena-simple-epc.d ./src/lte/examples/lena-simple-epc.o ./src/lte/examples/lena-simple.d ./src/lte/examples/lena-simple.o ./src/lte/examples/lena-uplink-power-control.d ./src/lte/examples/lena-uplink-power-control.o ./src/lte/examples/lena-x2-handover-measures.d ./src/lte/examples/lena-x2-handover-measures.o ./src/lte/examples/lena-x2-handover.d ./src/lte/examples/lena-x2-handover.o

.PHONY: clean-src-2f-lte-2f-examples


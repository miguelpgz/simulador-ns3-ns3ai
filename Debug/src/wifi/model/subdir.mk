################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/wifi/model/adhoc-wifi-mac.cc \
../src/wifi/model/ampdu-subframe-header.cc \
../src/wifi/model/ampdu-tag.cc \
../src/wifi/model/amsdu-subframe-header.cc \
../src/wifi/model/ap-wifi-mac.cc \
../src/wifi/model/block-ack-agreement.cc \
../src/wifi/model/block-ack-manager.cc \
../src/wifi/model/block-ack-type.cc \
../src/wifi/model/block-ack-window.cc \
../src/wifi/model/capability-information.cc \
../src/wifi/model/channel-access-manager.cc \
../src/wifi/model/ctrl-headers.cc \
../src/wifi/model/edca-parameter-set.cc \
../src/wifi/model/error-rate-model.cc \
../src/wifi/model/extended-capabilities.cc \
../src/wifi/model/frame-capture-model.cc \
../src/wifi/model/frame-exchange-manager.cc \
../src/wifi/model/interference-helper.cc \
../src/wifi/model/mac-rx-middle.cc \
../src/wifi/model/mac-tx-middle.cc \
../src/wifi/model/mgt-headers.cc \
../src/wifi/model/mpdu-aggregator.cc \
../src/wifi/model/msdu-aggregator.cc \
../src/wifi/model/nist-error-rate-model.cc \
../src/wifi/model/originator-block-ack-agreement.cc \
../src/wifi/model/phy-entity.cc \
../src/wifi/model/preamble-detection-model.cc \
../src/wifi/model/qos-blocked-destinations.cc \
../src/wifi/model/qos-frame-exchange-manager.cc \
../src/wifi/model/qos-txop.cc \
../src/wifi/model/qos-utils.cc \
../src/wifi/model/recipient-block-ack-agreement.cc \
../src/wifi/model/simple-frame-capture-model.cc \
../src/wifi/model/snr-tag.cc \
../src/wifi/model/spectrum-wifi-phy.cc \
../src/wifi/model/ssid.cc \
../src/wifi/model/sta-wifi-mac.cc \
../src/wifi/model/status-code.cc \
../src/wifi/model/supported-rates.cc \
../src/wifi/model/table-based-error-rate-model.cc \
../src/wifi/model/threshold-preamble-detection-model.cc \
../src/wifi/model/txop.cc \
../src/wifi/model/wifi-ack-manager.cc \
../src/wifi/model/wifi-acknowledgment.cc \
../src/wifi/model/wifi-default-ack-manager.cc \
../src/wifi/model/wifi-default-protection-manager.cc \
../src/wifi/model/wifi-information-element-vector.cc \
../src/wifi/model/wifi-information-element.cc \
../src/wifi/model/wifi-mac-header.cc \
../src/wifi/model/wifi-mac-queue-item.cc \
../src/wifi/model/wifi-mac-queue.cc \
../src/wifi/model/wifi-mac-trailer.cc \
../src/wifi/model/wifi-mac.cc \
../src/wifi/model/wifi-mode.cc \
../src/wifi/model/wifi-net-device.cc \
../src/wifi/model/wifi-phy-common.cc \
../src/wifi/model/wifi-phy-operating-channel.cc \
../src/wifi/model/wifi-phy-state-helper.cc \
../src/wifi/model/wifi-phy.cc \
../src/wifi/model/wifi-ppdu.cc \
../src/wifi/model/wifi-protection-manager.cc \
../src/wifi/model/wifi-protection.cc \
../src/wifi/model/wifi-psdu.cc \
../src/wifi/model/wifi-radio-energy-model.cc \
../src/wifi/model/wifi-remote-station-info.cc \
../src/wifi/model/wifi-remote-station-manager.cc \
../src/wifi/model/wifi-spectrum-phy-interface.cc \
../src/wifi/model/wifi-spectrum-signal-parameters.cc \
../src/wifi/model/wifi-tx-current-model.cc \
../src/wifi/model/wifi-tx-parameters.cc \
../src/wifi/model/wifi-tx-timer.cc \
../src/wifi/model/wifi-tx-vector.cc \
../src/wifi/model/wifi-utils.cc \
../src/wifi/model/yans-error-rate-model.cc \
../src/wifi/model/yans-wifi-channel.cc \
../src/wifi/model/yans-wifi-phy.cc 

CC_DEPS += \
./src/wifi/model/adhoc-wifi-mac.d \
./src/wifi/model/ampdu-subframe-header.d \
./src/wifi/model/ampdu-tag.d \
./src/wifi/model/amsdu-subframe-header.d \
./src/wifi/model/ap-wifi-mac.d \
./src/wifi/model/block-ack-agreement.d \
./src/wifi/model/block-ack-manager.d \
./src/wifi/model/block-ack-type.d \
./src/wifi/model/block-ack-window.d \
./src/wifi/model/capability-information.d \
./src/wifi/model/channel-access-manager.d \
./src/wifi/model/ctrl-headers.d \
./src/wifi/model/edca-parameter-set.d \
./src/wifi/model/error-rate-model.d \
./src/wifi/model/extended-capabilities.d \
./src/wifi/model/frame-capture-model.d \
./src/wifi/model/frame-exchange-manager.d \
./src/wifi/model/interference-helper.d \
./src/wifi/model/mac-rx-middle.d \
./src/wifi/model/mac-tx-middle.d \
./src/wifi/model/mgt-headers.d \
./src/wifi/model/mpdu-aggregator.d \
./src/wifi/model/msdu-aggregator.d \
./src/wifi/model/nist-error-rate-model.d \
./src/wifi/model/originator-block-ack-agreement.d \
./src/wifi/model/phy-entity.d \
./src/wifi/model/preamble-detection-model.d \
./src/wifi/model/qos-blocked-destinations.d \
./src/wifi/model/qos-frame-exchange-manager.d \
./src/wifi/model/qos-txop.d \
./src/wifi/model/qos-utils.d \
./src/wifi/model/recipient-block-ack-agreement.d \
./src/wifi/model/simple-frame-capture-model.d \
./src/wifi/model/snr-tag.d \
./src/wifi/model/spectrum-wifi-phy.d \
./src/wifi/model/ssid.d \
./src/wifi/model/sta-wifi-mac.d \
./src/wifi/model/status-code.d \
./src/wifi/model/supported-rates.d \
./src/wifi/model/table-based-error-rate-model.d \
./src/wifi/model/threshold-preamble-detection-model.d \
./src/wifi/model/txop.d \
./src/wifi/model/wifi-ack-manager.d \
./src/wifi/model/wifi-acknowledgment.d \
./src/wifi/model/wifi-default-ack-manager.d \
./src/wifi/model/wifi-default-protection-manager.d \
./src/wifi/model/wifi-information-element-vector.d \
./src/wifi/model/wifi-information-element.d \
./src/wifi/model/wifi-mac-header.d \
./src/wifi/model/wifi-mac-queue-item.d \
./src/wifi/model/wifi-mac-queue.d \
./src/wifi/model/wifi-mac-trailer.d \
./src/wifi/model/wifi-mac.d \
./src/wifi/model/wifi-mode.d \
./src/wifi/model/wifi-net-device.d \
./src/wifi/model/wifi-phy-common.d \
./src/wifi/model/wifi-phy-operating-channel.d \
./src/wifi/model/wifi-phy-state-helper.d \
./src/wifi/model/wifi-phy.d \
./src/wifi/model/wifi-ppdu.d \
./src/wifi/model/wifi-protection-manager.d \
./src/wifi/model/wifi-protection.d \
./src/wifi/model/wifi-psdu.d \
./src/wifi/model/wifi-radio-energy-model.d \
./src/wifi/model/wifi-remote-station-info.d \
./src/wifi/model/wifi-remote-station-manager.d \
./src/wifi/model/wifi-spectrum-phy-interface.d \
./src/wifi/model/wifi-spectrum-signal-parameters.d \
./src/wifi/model/wifi-tx-current-model.d \
./src/wifi/model/wifi-tx-parameters.d \
./src/wifi/model/wifi-tx-timer.d \
./src/wifi/model/wifi-tx-vector.d \
./src/wifi/model/wifi-utils.d \
./src/wifi/model/yans-error-rate-model.d \
./src/wifi/model/yans-wifi-channel.d \
./src/wifi/model/yans-wifi-phy.d 

OBJS += \
./src/wifi/model/adhoc-wifi-mac.o \
./src/wifi/model/ampdu-subframe-header.o \
./src/wifi/model/ampdu-tag.o \
./src/wifi/model/amsdu-subframe-header.o \
./src/wifi/model/ap-wifi-mac.o \
./src/wifi/model/block-ack-agreement.o \
./src/wifi/model/block-ack-manager.o \
./src/wifi/model/block-ack-type.o \
./src/wifi/model/block-ack-window.o \
./src/wifi/model/capability-information.o \
./src/wifi/model/channel-access-manager.o \
./src/wifi/model/ctrl-headers.o \
./src/wifi/model/edca-parameter-set.o \
./src/wifi/model/error-rate-model.o \
./src/wifi/model/extended-capabilities.o \
./src/wifi/model/frame-capture-model.o \
./src/wifi/model/frame-exchange-manager.o \
./src/wifi/model/interference-helper.o \
./src/wifi/model/mac-rx-middle.o \
./src/wifi/model/mac-tx-middle.o \
./src/wifi/model/mgt-headers.o \
./src/wifi/model/mpdu-aggregator.o \
./src/wifi/model/msdu-aggregator.o \
./src/wifi/model/nist-error-rate-model.o \
./src/wifi/model/originator-block-ack-agreement.o \
./src/wifi/model/phy-entity.o \
./src/wifi/model/preamble-detection-model.o \
./src/wifi/model/qos-blocked-destinations.o \
./src/wifi/model/qos-frame-exchange-manager.o \
./src/wifi/model/qos-txop.o \
./src/wifi/model/qos-utils.o \
./src/wifi/model/recipient-block-ack-agreement.o \
./src/wifi/model/simple-frame-capture-model.o \
./src/wifi/model/snr-tag.o \
./src/wifi/model/spectrum-wifi-phy.o \
./src/wifi/model/ssid.o \
./src/wifi/model/sta-wifi-mac.o \
./src/wifi/model/status-code.o \
./src/wifi/model/supported-rates.o \
./src/wifi/model/table-based-error-rate-model.o \
./src/wifi/model/threshold-preamble-detection-model.o \
./src/wifi/model/txop.o \
./src/wifi/model/wifi-ack-manager.o \
./src/wifi/model/wifi-acknowledgment.o \
./src/wifi/model/wifi-default-ack-manager.o \
./src/wifi/model/wifi-default-protection-manager.o \
./src/wifi/model/wifi-information-element-vector.o \
./src/wifi/model/wifi-information-element.o \
./src/wifi/model/wifi-mac-header.o \
./src/wifi/model/wifi-mac-queue-item.o \
./src/wifi/model/wifi-mac-queue.o \
./src/wifi/model/wifi-mac-trailer.o \
./src/wifi/model/wifi-mac.o \
./src/wifi/model/wifi-mode.o \
./src/wifi/model/wifi-net-device.o \
./src/wifi/model/wifi-phy-common.o \
./src/wifi/model/wifi-phy-operating-channel.o \
./src/wifi/model/wifi-phy-state-helper.o \
./src/wifi/model/wifi-phy.o \
./src/wifi/model/wifi-ppdu.o \
./src/wifi/model/wifi-protection-manager.o \
./src/wifi/model/wifi-protection.o \
./src/wifi/model/wifi-psdu.o \
./src/wifi/model/wifi-radio-energy-model.o \
./src/wifi/model/wifi-remote-station-info.o \
./src/wifi/model/wifi-remote-station-manager.o \
./src/wifi/model/wifi-spectrum-phy-interface.o \
./src/wifi/model/wifi-spectrum-signal-parameters.o \
./src/wifi/model/wifi-tx-current-model.o \
./src/wifi/model/wifi-tx-parameters.o \
./src/wifi/model/wifi-tx-timer.o \
./src/wifi/model/wifi-tx-vector.o \
./src/wifi/model/wifi-utils.o \
./src/wifi/model/yans-error-rate-model.o \
./src/wifi/model/yans-wifi-channel.o \
./src/wifi/model/yans-wifi-phy.o 


# Each subdirectory must supply rules for building sources it contributes
src/wifi/model/%.o: ../src/wifi/model/%.cc src/wifi/model/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-wifi-2f-model

clean-src-2f-wifi-2f-model:
	-$(RM) ./src/wifi/model/adhoc-wifi-mac.d ./src/wifi/model/adhoc-wifi-mac.o ./src/wifi/model/ampdu-subframe-header.d ./src/wifi/model/ampdu-subframe-header.o ./src/wifi/model/ampdu-tag.d ./src/wifi/model/ampdu-tag.o ./src/wifi/model/amsdu-subframe-header.d ./src/wifi/model/amsdu-subframe-header.o ./src/wifi/model/ap-wifi-mac.d ./src/wifi/model/ap-wifi-mac.o ./src/wifi/model/block-ack-agreement.d ./src/wifi/model/block-ack-agreement.o ./src/wifi/model/block-ack-manager.d ./src/wifi/model/block-ack-manager.o ./src/wifi/model/block-ack-type.d ./src/wifi/model/block-ack-type.o ./src/wifi/model/block-ack-window.d ./src/wifi/model/block-ack-window.o ./src/wifi/model/capability-information.d ./src/wifi/model/capability-information.o ./src/wifi/model/channel-access-manager.d ./src/wifi/model/channel-access-manager.o ./src/wifi/model/ctrl-headers.d ./src/wifi/model/ctrl-headers.o ./src/wifi/model/edca-parameter-set.d ./src/wifi/model/edca-parameter-set.o ./src/wifi/model/error-rate-model.d ./src/wifi/model/error-rate-model.o ./src/wifi/model/extended-capabilities.d ./src/wifi/model/extended-capabilities.o ./src/wifi/model/frame-capture-model.d ./src/wifi/model/frame-capture-model.o ./src/wifi/model/frame-exchange-manager.d ./src/wifi/model/frame-exchange-manager.o ./src/wifi/model/interference-helper.d ./src/wifi/model/interference-helper.o ./src/wifi/model/mac-rx-middle.d ./src/wifi/model/mac-rx-middle.o ./src/wifi/model/mac-tx-middle.d ./src/wifi/model/mac-tx-middle.o ./src/wifi/model/mgt-headers.d ./src/wifi/model/mgt-headers.o ./src/wifi/model/mpdu-aggregator.d ./src/wifi/model/mpdu-aggregator.o ./src/wifi/model/msdu-aggregator.d ./src/wifi/model/msdu-aggregator.o ./src/wifi/model/nist-error-rate-model.d ./src/wifi/model/nist-error-rate-model.o ./src/wifi/model/originator-block-ack-agreement.d ./src/wifi/model/originator-block-ack-agreement.o ./src/wifi/model/phy-entity.d ./src/wifi/model/phy-entity.o ./src/wifi/model/preamble-detection-model.d ./src/wifi/model/preamble-detection-model.o ./src/wifi/model/qos-blocked-destinations.d ./src/wifi/model/qos-blocked-destinations.o ./src/wifi/model/qos-frame-exchange-manager.d ./src/wifi/model/qos-frame-exchange-manager.o ./src/wifi/model/qos-txop.d ./src/wifi/model/qos-txop.o ./src/wifi/model/qos-utils.d ./src/wifi/model/qos-utils.o ./src/wifi/model/recipient-block-ack-agreement.d ./src/wifi/model/recipient-block-ack-agreement.o ./src/wifi/model/simple-frame-capture-model.d ./src/wifi/model/simple-frame-capture-model.o ./src/wifi/model/snr-tag.d ./src/wifi/model/snr-tag.o ./src/wifi/model/spectrum-wifi-phy.d ./src/wifi/model/spectrum-wifi-phy.o ./src/wifi/model/ssid.d ./src/wifi/model/ssid.o ./src/wifi/model/sta-wifi-mac.d ./src/wifi/model/sta-wifi-mac.o ./src/wifi/model/status-code.d ./src/wifi/model/status-code.o ./src/wifi/model/supported-rates.d ./src/wifi/model/supported-rates.o ./src/wifi/model/table-based-error-rate-model.d ./src/wifi/model/table-based-error-rate-model.o ./src/wifi/model/threshold-preamble-detection-model.d ./src/wifi/model/threshold-preamble-detection-model.o ./src/wifi/model/txop.d ./src/wifi/model/txop.o ./src/wifi/model/wifi-ack-manager.d ./src/wifi/model/wifi-ack-manager.o ./src/wifi/model/wifi-acknowledgment.d ./src/wifi/model/wifi-acknowledgment.o ./src/wifi/model/wifi-default-ack-manager.d ./src/wifi/model/wifi-default-ack-manager.o ./src/wifi/model/wifi-default-protection-manager.d ./src/wifi/model/wifi-default-protection-manager.o ./src/wifi/model/wifi-information-element-vector.d ./src/wifi/model/wifi-information-element-vector.o ./src/wifi/model/wifi-information-element.d ./src/wifi/model/wifi-information-element.o ./src/wifi/model/wifi-mac-header.d ./src/wifi/model/wifi-mac-header.o ./src/wifi/model/wifi-mac-queue-item.d ./src/wifi/model/wifi-mac-queue-item.o ./src/wifi/model/wifi-mac-queue.d ./src/wifi/model/wifi-mac-queue.o ./src/wifi/model/wifi-mac-trailer.d ./src/wifi/model/wifi-mac-trailer.o ./src/wifi/model/wifi-mac.d ./src/wifi/model/wifi-mac.o ./src/wifi/model/wifi-mode.d ./src/wifi/model/wifi-mode.o ./src/wifi/model/wifi-net-device.d ./src/wifi/model/wifi-net-device.o ./src/wifi/model/wifi-phy-common.d ./src/wifi/model/wifi-phy-common.o ./src/wifi/model/wifi-phy-operating-channel.d ./src/wifi/model/wifi-phy-operating-channel.o ./src/wifi/model/wifi-phy-state-helper.d ./src/wifi/model/wifi-phy-state-helper.o ./src/wifi/model/wifi-phy.d ./src/wifi/model/wifi-phy.o ./src/wifi/model/wifi-ppdu.d ./src/wifi/model/wifi-ppdu.o ./src/wifi/model/wifi-protection-manager.d ./src/wifi/model/wifi-protection-manager.o ./src/wifi/model/wifi-protection.d ./src/wifi/model/wifi-protection.o ./src/wifi/model/wifi-psdu.d ./src/wifi/model/wifi-psdu.o ./src/wifi/model/wifi-radio-energy-model.d ./src/wifi/model/wifi-radio-energy-model.o ./src/wifi/model/wifi-remote-station-info.d ./src/wifi/model/wifi-remote-station-info.o ./src/wifi/model/wifi-remote-station-manager.d ./src/wifi/model/wifi-remote-station-manager.o ./src/wifi/model/wifi-spectrum-phy-interface.d ./src/wifi/model/wifi-spectrum-phy-interface.o ./src/wifi/model/wifi-spectrum-signal-parameters.d ./src/wifi/model/wifi-spectrum-signal-parameters.o ./src/wifi/model/wifi-tx-current-model.d ./src/wifi/model/wifi-tx-current-model.o ./src/wifi/model/wifi-tx-parameters.d ./src/wifi/model/wifi-tx-parameters.o ./src/wifi/model/wifi-tx-timer.d ./src/wifi/model/wifi-tx-timer.o ./src/wifi/model/wifi-tx-vector.d ./src/wifi/model/wifi-tx-vector.o ./src/wifi/model/wifi-utils.d ./src/wifi/model/wifi-utils.o ./src/wifi/model/yans-error-rate-model.d ./src/wifi/model/yans-error-rate-model.o ./src/wifi/model/yans-wifi-channel.d ./src/wifi/model/yans-wifi-channel.o ./src/wifi/model/yans-wifi-phy.d ./src/wifi/model/yans-wifi-phy.o

.PHONY: clean-src-2f-wifi-2f-model


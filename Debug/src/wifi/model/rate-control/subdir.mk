################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/wifi/model/rate-control/aarf-wifi-manager.cc \
../src/wifi/model/rate-control/aarfcd-wifi-manager.cc \
../src/wifi/model/rate-control/amrr-wifi-manager.cc \
../src/wifi/model/rate-control/aparf-wifi-manager.cc \
../src/wifi/model/rate-control/arf-wifi-manager.cc \
../src/wifi/model/rate-control/cara-wifi-manager.cc \
../src/wifi/model/rate-control/constant-rate-wifi-manager.cc \
../src/wifi/model/rate-control/ideal-wifi-manager.cc \
../src/wifi/model/rate-control/minstrel-ht-wifi-manager.cc \
../src/wifi/model/rate-control/minstrel-wifi-manager.cc \
../src/wifi/model/rate-control/onoe-wifi-manager.cc \
../src/wifi/model/rate-control/parf-wifi-manager.cc \
../src/wifi/model/rate-control/rraa-wifi-manager.cc \
../src/wifi/model/rate-control/rrpaa-wifi-manager.cc \
../src/wifi/model/rate-control/thompson-sampling-wifi-manager.cc 

CC_DEPS += \
./src/wifi/model/rate-control/aarf-wifi-manager.d \
./src/wifi/model/rate-control/aarfcd-wifi-manager.d \
./src/wifi/model/rate-control/amrr-wifi-manager.d \
./src/wifi/model/rate-control/aparf-wifi-manager.d \
./src/wifi/model/rate-control/arf-wifi-manager.d \
./src/wifi/model/rate-control/cara-wifi-manager.d \
./src/wifi/model/rate-control/constant-rate-wifi-manager.d \
./src/wifi/model/rate-control/ideal-wifi-manager.d \
./src/wifi/model/rate-control/minstrel-ht-wifi-manager.d \
./src/wifi/model/rate-control/minstrel-wifi-manager.d \
./src/wifi/model/rate-control/onoe-wifi-manager.d \
./src/wifi/model/rate-control/parf-wifi-manager.d \
./src/wifi/model/rate-control/rraa-wifi-manager.d \
./src/wifi/model/rate-control/rrpaa-wifi-manager.d \
./src/wifi/model/rate-control/thompson-sampling-wifi-manager.d 

OBJS += \
./src/wifi/model/rate-control/aarf-wifi-manager.o \
./src/wifi/model/rate-control/aarfcd-wifi-manager.o \
./src/wifi/model/rate-control/amrr-wifi-manager.o \
./src/wifi/model/rate-control/aparf-wifi-manager.o \
./src/wifi/model/rate-control/arf-wifi-manager.o \
./src/wifi/model/rate-control/cara-wifi-manager.o \
./src/wifi/model/rate-control/constant-rate-wifi-manager.o \
./src/wifi/model/rate-control/ideal-wifi-manager.o \
./src/wifi/model/rate-control/minstrel-ht-wifi-manager.o \
./src/wifi/model/rate-control/minstrel-wifi-manager.o \
./src/wifi/model/rate-control/onoe-wifi-manager.o \
./src/wifi/model/rate-control/parf-wifi-manager.o \
./src/wifi/model/rate-control/rraa-wifi-manager.o \
./src/wifi/model/rate-control/rrpaa-wifi-manager.o \
./src/wifi/model/rate-control/thompson-sampling-wifi-manager.o 


# Each subdirectory must supply rules for building sources it contributes
src/wifi/model/rate-control/%.o: ../src/wifi/model/rate-control/%.cc src/wifi/model/rate-control/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-wifi-2f-model-2f-rate-2d-control

clean-src-2f-wifi-2f-model-2f-rate-2d-control:
	-$(RM) ./src/wifi/model/rate-control/aarf-wifi-manager.d ./src/wifi/model/rate-control/aarf-wifi-manager.o ./src/wifi/model/rate-control/aarfcd-wifi-manager.d ./src/wifi/model/rate-control/aarfcd-wifi-manager.o ./src/wifi/model/rate-control/amrr-wifi-manager.d ./src/wifi/model/rate-control/amrr-wifi-manager.o ./src/wifi/model/rate-control/aparf-wifi-manager.d ./src/wifi/model/rate-control/aparf-wifi-manager.o ./src/wifi/model/rate-control/arf-wifi-manager.d ./src/wifi/model/rate-control/arf-wifi-manager.o ./src/wifi/model/rate-control/cara-wifi-manager.d ./src/wifi/model/rate-control/cara-wifi-manager.o ./src/wifi/model/rate-control/constant-rate-wifi-manager.d ./src/wifi/model/rate-control/constant-rate-wifi-manager.o ./src/wifi/model/rate-control/ideal-wifi-manager.d ./src/wifi/model/rate-control/ideal-wifi-manager.o ./src/wifi/model/rate-control/minstrel-ht-wifi-manager.d ./src/wifi/model/rate-control/minstrel-ht-wifi-manager.o ./src/wifi/model/rate-control/minstrel-wifi-manager.d ./src/wifi/model/rate-control/minstrel-wifi-manager.o ./src/wifi/model/rate-control/onoe-wifi-manager.d ./src/wifi/model/rate-control/onoe-wifi-manager.o ./src/wifi/model/rate-control/parf-wifi-manager.d ./src/wifi/model/rate-control/parf-wifi-manager.o ./src/wifi/model/rate-control/rraa-wifi-manager.d ./src/wifi/model/rate-control/rraa-wifi-manager.o ./src/wifi/model/rate-control/rrpaa-wifi-manager.d ./src/wifi/model/rate-control/rrpaa-wifi-manager.o ./src/wifi/model/rate-control/thompson-sampling-wifi-manager.d ./src/wifi/model/rate-control/thompson-sampling-wifi-manager.o

.PHONY: clean-src-2f-wifi-2f-model-2f-rate-2d-control


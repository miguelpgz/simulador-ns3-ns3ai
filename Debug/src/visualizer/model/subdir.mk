################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/visualizer/model/pyviz.cc \
../src/visualizer/model/visual-simulator-impl.cc 

CC_DEPS += \
./src/visualizer/model/pyviz.d \
./src/visualizer/model/visual-simulator-impl.d 

OBJS += \
./src/visualizer/model/pyviz.o \
./src/visualizer/model/visual-simulator-impl.o 


# Each subdirectory must supply rules for building sources it contributes
src/visualizer/model/%.o: ../src/visualizer/model/%.cc src/visualizer/model/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-visualizer-2f-model

clean-src-2f-visualizer-2f-model:
	-$(RM) ./src/visualizer/model/pyviz.d ./src/visualizer/model/pyviz.o ./src/visualizer/model/visual-simulator-impl.d ./src/visualizer/model/visual-simulator-impl.o

.PHONY: clean-src-2f-visualizer-2f-model


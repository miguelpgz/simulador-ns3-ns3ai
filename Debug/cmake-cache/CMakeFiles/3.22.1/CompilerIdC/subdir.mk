################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cmake-cache/CMakeFiles/3.22.1/CompilerIdC/CMakeCCompilerId.c 

C_DEPS += \
./cmake-cache/CMakeFiles/3.22.1/CompilerIdC/CMakeCCompilerId.d 

OBJS += \
./cmake-cache/CMakeFiles/3.22.1/CompilerIdC/CMakeCCompilerId.o 


# Each subdirectory must supply rules for building sources it contributes
cmake-cache/CMakeFiles/3.22.1/CompilerIdC/%.o: ../cmake-cache/CMakeFiles/3.22.1/CompilerIdC/%.c cmake-cache/CMakeFiles/3.22.1/CompilerIdC/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-cmake-2d-cache-2f-CMakeFiles-2f-3-2e-22-2e-1-2f-CompilerIdC

clean-cmake-2d-cache-2f-CMakeFiles-2f-3-2e-22-2e-1-2f-CompilerIdC:
	-$(RM) ./cmake-cache/CMakeFiles/3.22.1/CompilerIdC/CMakeCCompilerId.d ./cmake-cache/CMakeFiles/3.22.1/CompilerIdC/CMakeCCompilerId.o

.PHONY: clean-cmake-2d-cache-2f-CMakeFiles-2f-3-2e-22-2e-1-2f-CompilerIdC


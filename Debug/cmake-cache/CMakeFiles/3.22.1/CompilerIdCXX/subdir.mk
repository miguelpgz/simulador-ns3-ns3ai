################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cmake-cache/CMakeFiles/3.22.1/CompilerIdCXX/CMakeCXXCompilerId.cpp 

CPP_DEPS += \
./cmake-cache/CMakeFiles/3.22.1/CompilerIdCXX/CMakeCXXCompilerId.d 

OBJS += \
./cmake-cache/CMakeFiles/3.22.1/CompilerIdCXX/CMakeCXXCompilerId.o 


# Each subdirectory must supply rules for building sources it contributes
cmake-cache/CMakeFiles/3.22.1/CompilerIdCXX/%.o: ../cmake-cache/CMakeFiles/3.22.1/CompilerIdCXX/%.cpp cmake-cache/CMakeFiles/3.22.1/CompilerIdCXX/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-cmake-2d-cache-2f-CMakeFiles-2f-3-2e-22-2e-1-2f-CompilerIdCXX

clean-cmake-2d-cache-2f-CMakeFiles-2f-3-2e-22-2e-1-2f-CompilerIdCXX:
	-$(RM) ./cmake-cache/CMakeFiles/3.22.1/CompilerIdCXX/CMakeCXXCompilerId.d ./cmake-cache/CMakeFiles/3.22.1/CompilerIdCXX/CMakeCXXCompilerId.o

.PHONY: clean-cmake-2d-cache-2f-CMakeFiles-2f-3-2e-22-2e-1-2f-CompilerIdCXX


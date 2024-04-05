################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CXX_SRCS += \
../cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch.hxx.cxx 

CXX_DEPS += \
./cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch.hxx.d 

OBJS += \
./cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch.hxx.o 


# Each subdirectory must supply rules for building sources it contributes
cmake-cache/CMakeFiles/stdlib_pch.dir/%.o: ../cmake-cache/CMakeFiles/stdlib_pch.dir/%.cxx cmake-cache/CMakeFiles/stdlib_pch.dir/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-cmake-2d-cache-2f-CMakeFiles-2f-stdlib_pch-2e-dir

clean-cmake-2d-cache-2f-CMakeFiles-2f-stdlib_pch-2e-dir:
	-$(RM) ./cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch.hxx.d ./cmake-cache/CMakeFiles/stdlib_pch.dir/cmake_pch.hxx.o

.PHONY: clean-cmake-2d-cache-2f-CMakeFiles-2f-stdlib_pch-2e-dir


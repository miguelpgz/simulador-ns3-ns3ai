################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cmake-cache/CMakeFiles/CheckTypeSize/int128_t_HAVE__int128_t.c \
../cmake-cache/CMakeFiles/CheckTypeSize/int128_t_HAVEint128_as_long_long.c \
../cmake-cache/CMakeFiles/CheckTypeSize/int128_t_HAVEint128_t.c \
../cmake-cache/CMakeFiles/CheckTypeSize/uint128_t_HAVE__uint128_t.c \
../cmake-cache/CMakeFiles/CheckTypeSize/uint128_t_HAVEuint128_as_u_long_long.c \
../cmake-cache/CMakeFiles/CheckTypeSize/uint128_t_HAVEuint128_t.c 

C_DEPS += \
./cmake-cache/CMakeFiles/CheckTypeSize/int128_t_HAVE__int128_t.d \
./cmake-cache/CMakeFiles/CheckTypeSize/int128_t_HAVEint128_as_long_long.d \
./cmake-cache/CMakeFiles/CheckTypeSize/int128_t_HAVEint128_t.d \
./cmake-cache/CMakeFiles/CheckTypeSize/uint128_t_HAVE__uint128_t.d \
./cmake-cache/CMakeFiles/CheckTypeSize/uint128_t_HAVEuint128_as_u_long_long.d \
./cmake-cache/CMakeFiles/CheckTypeSize/uint128_t_HAVEuint128_t.d 

OBJS += \
./cmake-cache/CMakeFiles/CheckTypeSize/int128_t_HAVE__int128_t.o \
./cmake-cache/CMakeFiles/CheckTypeSize/int128_t_HAVEint128_as_long_long.o \
./cmake-cache/CMakeFiles/CheckTypeSize/int128_t_HAVEint128_t.o \
./cmake-cache/CMakeFiles/CheckTypeSize/uint128_t_HAVE__uint128_t.o \
./cmake-cache/CMakeFiles/CheckTypeSize/uint128_t_HAVEuint128_as_u_long_long.o \
./cmake-cache/CMakeFiles/CheckTypeSize/uint128_t_HAVEuint128_t.o 


# Each subdirectory must supply rules for building sources it contributes
cmake-cache/CMakeFiles/CheckTypeSize/%.o: ../cmake-cache/CMakeFiles/CheckTypeSize/%.c cmake-cache/CMakeFiles/CheckTypeSize/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-cmake-2d-cache-2f-CMakeFiles-2f-CheckTypeSize

clean-cmake-2d-cache-2f-CMakeFiles-2f-CheckTypeSize:
	-$(RM) ./cmake-cache/CMakeFiles/CheckTypeSize/int128_t_HAVE__int128_t.d ./cmake-cache/CMakeFiles/CheckTypeSize/int128_t_HAVE__int128_t.o ./cmake-cache/CMakeFiles/CheckTypeSize/int128_t_HAVEint128_as_long_long.d ./cmake-cache/CMakeFiles/CheckTypeSize/int128_t_HAVEint128_as_long_long.o ./cmake-cache/CMakeFiles/CheckTypeSize/int128_t_HAVEint128_t.d ./cmake-cache/CMakeFiles/CheckTypeSize/int128_t_HAVEint128_t.o ./cmake-cache/CMakeFiles/CheckTypeSize/uint128_t_HAVE__uint128_t.d ./cmake-cache/CMakeFiles/CheckTypeSize/uint128_t_HAVE__uint128_t.o ./cmake-cache/CMakeFiles/CheckTypeSize/uint128_t_HAVEuint128_as_u_long_long.d ./cmake-cache/CMakeFiles/CheckTypeSize/uint128_t_HAVEuint128_as_u_long_long.o ./cmake-cache/CMakeFiles/CheckTypeSize/uint128_t_HAVEuint128_t.d ./cmake-cache/CMakeFiles/CheckTypeSize/uint128_t_HAVEuint128_t.o

.PHONY: clean-cmake-2d-cache-2f-CMakeFiles-2f-CheckTypeSize


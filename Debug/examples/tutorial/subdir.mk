################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../examples/tutorial/fifth.cc \
../examples/tutorial/first.cc \
../examples/tutorial/fourth.cc \
../examples/tutorial/hello-simulator.cc \
../examples/tutorial/second.cc \
../examples/tutorial/seventh.cc \
../examples/tutorial/sixth.cc \
../examples/tutorial/third.cc \
../examples/tutorial/tutorial-app.cc 

CC_DEPS += \
./examples/tutorial/fifth.d \
./examples/tutorial/first.d \
./examples/tutorial/fourth.d \
./examples/tutorial/hello-simulator.d \
./examples/tutorial/second.d \
./examples/tutorial/seventh.d \
./examples/tutorial/sixth.d \
./examples/tutorial/third.d \
./examples/tutorial/tutorial-app.d 

OBJS += \
./examples/tutorial/fifth.o \
./examples/tutorial/first.o \
./examples/tutorial/fourth.o \
./examples/tutorial/hello-simulator.o \
./examples/tutorial/second.o \
./examples/tutorial/seventh.o \
./examples/tutorial/sixth.o \
./examples/tutorial/third.o \
./examples/tutorial/tutorial-app.o 


# Each subdirectory must supply rules for building sources it contributes
examples/tutorial/%.o: ../examples/tutorial/%.cc examples/tutorial/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-examples-2f-tutorial

clean-examples-2f-tutorial:
	-$(RM) ./examples/tutorial/fifth.d ./examples/tutorial/fifth.o ./examples/tutorial/first.d ./examples/tutorial/first.o ./examples/tutorial/fourth.d ./examples/tutorial/fourth.o ./examples/tutorial/hello-simulator.d ./examples/tutorial/hello-simulator.o ./examples/tutorial/second.d ./examples/tutorial/second.o ./examples/tutorial/seventh.d ./examples/tutorial/seventh.o ./examples/tutorial/sixth.d ./examples/tutorial/sixth.o ./examples/tutorial/third.d ./examples/tutorial/third.o ./examples/tutorial/tutorial-app.d ./examples/tutorial/tutorial-app.o

.PHONY: clean-examples-2f-tutorial


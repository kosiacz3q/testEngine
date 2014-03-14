################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/msg/Message.cpp 

OBJS += \
./src/msg/Message.o 

CPP_DEPS += \
./src/msg/Message.d 


# Each subdirectory must supply rules for building sources it contributes
src/msg/%.o: ../src/msg/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I/usr/include/c++/4.7.2 -I/usr/include/c++/4.7.2/x86_64-linux-gnu/32 -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



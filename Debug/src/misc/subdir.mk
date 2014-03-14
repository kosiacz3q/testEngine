################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/misc/Camera.cpp \
../src/misc/Model.cpp \
../src/misc/Skeleton.cpp \
../src/misc/Texture.cpp \
../src/misc/Timer.cpp \
../src/misc/TypeHandlers.cpp \
../src/misc/Vectorf.cpp \
../src/misc/hashFun.cpp 

OBJS += \
./src/misc/Camera.o \
./src/misc/Model.o \
./src/misc/Skeleton.o \
./src/misc/Texture.o \
./src/misc/Timer.o \
./src/misc/TypeHandlers.o \
./src/misc/Vectorf.o \
./src/misc/hashFun.o 

CPP_DEPS += \
./src/misc/Camera.d \
./src/misc/Model.d \
./src/misc/Skeleton.d \
./src/misc/Texture.d \
./src/misc/Timer.d \
./src/misc/TypeHandlers.d \
./src/misc/Vectorf.d \
./src/misc/hashFun.d 


# Each subdirectory must supply rules for building sources it contributes
src/misc/%.o: ../src/misc/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I/usr/include/c++/4.7.2 -I/usr/include/c++/4.7.2/x86_64-linux-gnu/32 -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



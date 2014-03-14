################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DisplayManager.cpp \
../src/Doll.cpp \
../src/Game.cpp \
../src/GameState.cpp \
../src/LightSource.cpp \
../src/MessagesHandler.cpp \
../src/Object.cpp \
../src/ObjectContainer.cpp \
../src/PlainAnimation.cpp \
../src/PlainTexture.cpp \
../src/ResourcesManager.cpp \
../src/Scene.cpp \
../src/SomePlatformGame.cpp \
../src/TerrainBlock.cpp 

OBJS += \
./src/DisplayManager.o \
./src/Doll.o \
./src/Game.o \
./src/GameState.o \
./src/LightSource.o \
./src/MessagesHandler.o \
./src/Object.o \
./src/ObjectContainer.o \
./src/PlainAnimation.o \
./src/PlainTexture.o \
./src/ResourcesManager.o \
./src/Scene.o \
./src/SomePlatformGame.o \
./src/TerrainBlock.o 

CPP_DEPS += \
./src/DisplayManager.d \
./src/Doll.d \
./src/Game.d \
./src/GameState.d \
./src/LightSource.d \
./src/MessagesHandler.d \
./src/Object.d \
./src/ObjectContainer.d \
./src/PlainAnimation.d \
./src/PlainTexture.d \
./src/ResourcesManager.d \
./src/Scene.d \
./src/SomePlatformGame.d \
./src/TerrainBlock.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I/usr/include/c++/4.7.2 -I/usr/include/c++/4.7.2/x86_64-linux-gnu/32 -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



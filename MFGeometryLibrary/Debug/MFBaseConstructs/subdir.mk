################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MFBaseConstructs/MFBrickWall.cpp 

CPP_DEPS += \
./MFBaseConstructs/MFBrickWall.d 

OBJS += \
./MFBaseConstructs/MFBrickWall.o 


# Each subdirectory must supply rules for building sources it contributes
MFBaseConstructs/%.o: ../MFBaseConstructs/%.cpp MFBaseConstructs/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I$$LIB_NOISE_HEADERS -I$$BULLET_PHYSICS_HEADERS -I$$MF_BASICS_DIR -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-MFBaseConstructs

clean-MFBaseConstructs:
	-$(RM) ./MFBaseConstructs/MFBrickWall.d ./MFBaseConstructs/MFBrickWall.o

.PHONY: clean-MFBaseConstructs


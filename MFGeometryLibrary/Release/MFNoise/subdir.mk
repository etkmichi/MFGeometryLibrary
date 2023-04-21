################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MFNoise/MFNoiseCombinor.cpp \
../MFNoise/MFNoiseSetup.cpp \
../MFNoise/MFNoiseTile.cpp 

CPP_DEPS += \
./MFNoise/MFNoiseCombinor.d \
./MFNoise/MFNoiseSetup.d \
./MFNoise/MFNoiseTile.d 

OBJS += \
./MFNoise/MFNoiseCombinor.o \
./MFNoise/MFNoiseSetup.o \
./MFNoise/MFNoiseTile.o 


# Each subdirectory must supply rules for building sources it contributes
MFNoise/%.o: ../MFNoise/%.cpp MFNoise/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++17 -I$$LIB_NOISE_HEADERS -I$$BULLET_PHYSICS_HEADERS -I$$MF_BASICS_DIR -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-MFNoise

clean-MFNoise:
	-$(RM) ./MFNoise/MFNoiseCombinor.d ./MFNoise/MFNoiseCombinor.o ./MFNoise/MFNoiseSetup.d ./MFNoise/MFNoiseSetup.o ./MFNoise/MFNoiseTile.d ./MFNoise/MFNoiseTile.o

.PHONY: clean-MFNoise


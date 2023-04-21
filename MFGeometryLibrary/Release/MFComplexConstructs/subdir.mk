################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MFComplexConstructs/MFComplexConstruct.cpp \
../MFComplexConstructs/MFComplexSegment.cpp \
../MFComplexConstructs/MFLimitationMarker.cpp 

CPP_DEPS += \
./MFComplexConstructs/MFComplexConstruct.d \
./MFComplexConstructs/MFComplexSegment.d \
./MFComplexConstructs/MFLimitationMarker.d 

OBJS += \
./MFComplexConstructs/MFComplexConstruct.o \
./MFComplexConstructs/MFComplexSegment.o \
./MFComplexConstructs/MFLimitationMarker.o 


# Each subdirectory must supply rules for building sources it contributes
MFComplexConstructs/%.o: ../MFComplexConstructs/%.cpp MFComplexConstructs/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++17 -I$$LIB_NOISE_HEADERS -I$$BULLET_PHYSICS_HEADERS -I$$MF_BASICS_DIR -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-MFComplexConstructs

clean-MFComplexConstructs:
	-$(RM) ./MFComplexConstructs/MFComplexConstruct.d ./MFComplexConstructs/MFComplexConstruct.o ./MFComplexConstructs/MFComplexSegment.d ./MFComplexConstructs/MFComplexSegment.o ./MFComplexConstructs/MFLimitationMarker.d ./MFComplexConstructs/MFLimitationMarker.o

.PHONY: clean-MFComplexConstructs


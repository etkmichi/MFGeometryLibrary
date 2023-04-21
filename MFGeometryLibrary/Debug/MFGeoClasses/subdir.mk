################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MFGeoClasses/MFGeoAxis.cpp 

CPP_DEPS += \
./MFGeoClasses/MFGeoAxis.d 

OBJS += \
./MFGeoClasses/MFGeoAxis.o 


# Each subdirectory must supply rules for building sources it contributes
MFGeoClasses/%.o: ../MFGeoClasses/%.cpp MFGeoClasses/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I$$LIB_NOISE_HEADERS -I$$BULLET_PHYSICS_HEADERS -I$$MF_BASICS_DIR -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-MFGeoClasses

clean-MFGeoClasses:
	-$(RM) ./MFGeoClasses/MFGeoAxis.d ./MFGeoClasses/MFGeoAxis.o

.PHONY: clean-MFGeoClasses


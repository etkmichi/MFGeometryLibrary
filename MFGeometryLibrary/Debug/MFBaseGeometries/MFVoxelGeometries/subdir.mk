################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MFBaseGeometries/MFVoxelGeometries/MFNoiseVoxel.cpp 

CPP_DEPS += \
./MFBaseGeometries/MFVoxelGeometries/MFNoiseVoxel.d 

OBJS += \
./MFBaseGeometries/MFVoxelGeometries/MFNoiseVoxel.o 


# Each subdirectory must supply rules for building sources it contributes
MFBaseGeometries/MFVoxelGeometries/%.o: ../MFBaseGeometries/MFVoxelGeometries/%.cpp MFBaseGeometries/MFVoxelGeometries/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I$$LIB_NOISE_HEADERS -I$$BULLET_PHYSICS_HEADERS -I$$MF_BASICS_DIR -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-MFBaseGeometries-2f-MFVoxelGeometries

clean-MFBaseGeometries-2f-MFVoxelGeometries:
	-$(RM) ./MFBaseGeometries/MFVoxelGeometries/MFNoiseVoxel.d ./MFBaseGeometries/MFVoxelGeometries/MFNoiseVoxel.o

.PHONY: clean-MFBaseGeometries-2f-MFVoxelGeometries


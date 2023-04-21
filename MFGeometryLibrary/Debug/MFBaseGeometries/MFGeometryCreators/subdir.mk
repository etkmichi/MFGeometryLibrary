################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MFBaseGeometries/MFGeometryCreators/MFCreatorAxis.cpp \
../MFBaseGeometries/MFGeometryCreators/MFCreatorBox.cpp \
../MFBaseGeometries/MFGeometryCreators/MFCreatorNoise.cpp \
../MFBaseGeometries/MFGeometryCreators/MFCreatorSphere.cpp 

CPP_DEPS += \
./MFBaseGeometries/MFGeometryCreators/MFCreatorAxis.d \
./MFBaseGeometries/MFGeometryCreators/MFCreatorBox.d \
./MFBaseGeometries/MFGeometryCreators/MFCreatorNoise.d \
./MFBaseGeometries/MFGeometryCreators/MFCreatorSphere.d 

OBJS += \
./MFBaseGeometries/MFGeometryCreators/MFCreatorAxis.o \
./MFBaseGeometries/MFGeometryCreators/MFCreatorBox.o \
./MFBaseGeometries/MFGeometryCreators/MFCreatorNoise.o \
./MFBaseGeometries/MFGeometryCreators/MFCreatorSphere.o 


# Each subdirectory must supply rules for building sources it contributes
MFBaseGeometries/MFGeometryCreators/%.o: ../MFBaseGeometries/MFGeometryCreators/%.cpp MFBaseGeometries/MFGeometryCreators/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I$$LIB_NOISE_HEADERS -I$$BULLET_PHYSICS_HEADERS -I$$MF_BASICS_DIR -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-MFBaseGeometries-2f-MFGeometryCreators

clean-MFBaseGeometries-2f-MFGeometryCreators:
	-$(RM) ./MFBaseGeometries/MFGeometryCreators/MFCreatorAxis.d ./MFBaseGeometries/MFGeometryCreators/MFCreatorAxis.o ./MFBaseGeometries/MFGeometryCreators/MFCreatorBox.d ./MFBaseGeometries/MFGeometryCreators/MFCreatorBox.o ./MFBaseGeometries/MFGeometryCreators/MFCreatorNoise.d ./MFBaseGeometries/MFGeometryCreators/MFCreatorNoise.o ./MFBaseGeometries/MFGeometryCreators/MFCreatorSphere.d ./MFBaseGeometries/MFGeometryCreators/MFCreatorSphere.o

.PHONY: clean-MFBaseGeometries-2f-MFGeometryCreators


################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MFBaseGeometries/MFAbstractGeometry.cpp \
../MFBaseGeometries/MFAdvancedBox.cpp \
../MFBaseGeometries/MFAxis.cpp \
../MFBaseGeometries/MFBox.cpp \
../MFBaseGeometries/MFBrickGeometry.cpp \
../MFBaseGeometries/MFCapsule.cpp \
../MFBaseGeometries/MFCone.cpp \
../MFBaseGeometries/MFCylinder.cpp \
../MFBaseGeometries/MFDynCompoundGeometry.cpp \
../MFBaseGeometries/MFGeometryData.cpp \
../MFBaseGeometries/MFNoiseGeometry.cpp \
../MFBaseGeometries/MFPyramid.cpp \
../MFBaseGeometries/MFSphere.cpp \
../MFBaseGeometries/MFStaticCompountGeometry.cpp 

CPP_DEPS += \
./MFBaseGeometries/MFAbstractGeometry.d \
./MFBaseGeometries/MFAdvancedBox.d \
./MFBaseGeometries/MFAxis.d \
./MFBaseGeometries/MFBox.d \
./MFBaseGeometries/MFBrickGeometry.d \
./MFBaseGeometries/MFCapsule.d \
./MFBaseGeometries/MFCone.d \
./MFBaseGeometries/MFCylinder.d \
./MFBaseGeometries/MFDynCompoundGeometry.d \
./MFBaseGeometries/MFGeometryData.d \
./MFBaseGeometries/MFNoiseGeometry.d \
./MFBaseGeometries/MFPyramid.d \
./MFBaseGeometries/MFSphere.d \
./MFBaseGeometries/MFStaticCompountGeometry.d 

OBJS += \
./MFBaseGeometries/MFAbstractGeometry.o \
./MFBaseGeometries/MFAdvancedBox.o \
./MFBaseGeometries/MFAxis.o \
./MFBaseGeometries/MFBox.o \
./MFBaseGeometries/MFBrickGeometry.o \
./MFBaseGeometries/MFCapsule.o \
./MFBaseGeometries/MFCone.o \
./MFBaseGeometries/MFCylinder.o \
./MFBaseGeometries/MFDynCompoundGeometry.o \
./MFBaseGeometries/MFGeometryData.o \
./MFBaseGeometries/MFNoiseGeometry.o \
./MFBaseGeometries/MFPyramid.o \
./MFBaseGeometries/MFSphere.o \
./MFBaseGeometries/MFStaticCompountGeometry.o 


# Each subdirectory must supply rules for building sources it contributes
MFBaseGeometries/%.o: ../MFBaseGeometries/%.cpp MFBaseGeometries/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I$$LIB_NOISE_HEADERS -I$$BULLET_PHYSICS_HEADERS -I$$MF_BASICS_DIR -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-MFBaseGeometries

clean-MFBaseGeometries:
	-$(RM) ./MFBaseGeometries/MFAbstractGeometry.d ./MFBaseGeometries/MFAbstractGeometry.o ./MFBaseGeometries/MFAdvancedBox.d ./MFBaseGeometries/MFAdvancedBox.o ./MFBaseGeometries/MFAxis.d ./MFBaseGeometries/MFAxis.o ./MFBaseGeometries/MFBox.d ./MFBaseGeometries/MFBox.o ./MFBaseGeometries/MFBrickGeometry.d ./MFBaseGeometries/MFBrickGeometry.o ./MFBaseGeometries/MFCapsule.d ./MFBaseGeometries/MFCapsule.o ./MFBaseGeometries/MFCone.d ./MFBaseGeometries/MFCone.o ./MFBaseGeometries/MFCylinder.d ./MFBaseGeometries/MFCylinder.o ./MFBaseGeometries/MFDynCompoundGeometry.d ./MFBaseGeometries/MFDynCompoundGeometry.o ./MFBaseGeometries/MFGeometryData.d ./MFBaseGeometries/MFGeometryData.o ./MFBaseGeometries/MFNoiseGeometry.d ./MFBaseGeometries/MFNoiseGeometry.o ./MFBaseGeometries/MFPyramid.d ./MFBaseGeometries/MFPyramid.o ./MFBaseGeometries/MFSphere.d ./MFBaseGeometries/MFSphere.o ./MFBaseGeometries/MFStaticCompountGeometry.d ./MFBaseGeometries/MFStaticCompountGeometry.o

.PHONY: clean-MFBaseGeometries


################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MFVertexClasses/MFAdaptableVertex.cpp \
../MFVertexClasses/MFVertexDataCollection.cpp \
../MFVertexClasses/MFVertexDataOptimizer.cpp 

CPP_DEPS += \
./MFVertexClasses/MFAdaptableVertex.d \
./MFVertexClasses/MFVertexDataCollection.d \
./MFVertexClasses/MFVertexDataOptimizer.d 

OBJS += \
./MFVertexClasses/MFAdaptableVertex.o \
./MFVertexClasses/MFVertexDataCollection.o \
./MFVertexClasses/MFVertexDataOptimizer.o 


# Each subdirectory must supply rules for building sources it contributes
MFVertexClasses/%.o: ../MFVertexClasses/%.cpp MFVertexClasses/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I$$LIB_NOISE_HEADERS -I$$BULLET_PHYSICS_HEADERS -I$$MF_BASICS_DIR -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-MFVertexClasses

clean-MFVertexClasses:
	-$(RM) ./MFVertexClasses/MFAdaptableVertex.d ./MFVertexClasses/MFAdaptableVertex.o ./MFVertexClasses/MFVertexDataCollection.d ./MFVertexClasses/MFVertexDataCollection.o ./MFVertexClasses/MFVertexDataOptimizer.d ./MFVertexClasses/MFVertexDataOptimizer.o

.PHONY: clean-MFVertexClasses


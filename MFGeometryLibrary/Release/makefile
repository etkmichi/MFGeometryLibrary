################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MFVertexClasses/subdir.mk
-include MFNoise/subdir.mk
-include MFGeoClasses/subdir.mk
-include MFDockingSystem/subdir.mk
-include MFComplexConstructs/subdir.mk
-include MFBaseGeometries/MFVoxelGeometries/subdir.mk
-include MFBaseGeometries/MFGeometryCreators/subdir.mk
-include MFBaseGeometries/subdir.mk
-include MFBaseConstructs/subdir.mk
-include subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := MFGeometryLibrary
BUILD_ARTIFACT_EXTENSION := so
BUILD_ARTIFACT_PREFIX := lib
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: main-build

# Main-build Target
main-build: libMFGeometryLibrary.so

# Tool invocations
libMFGeometryLibrary.so: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	g++ -L$$MF_BASICS_DIR/Release -shared -o "libMFGeometryLibrary.so" $(OBJS) $(USER_OBJS) $(LIBS) -lBullet3Collision -lnoise -lBulletCollision -lBullet3Common -lBullet3Dynamics -lBullet3Geometry -lBullet3OpenCL_clew -lBulletDynamics -lLinearMath
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) libMFGeometryLibrary.so
	-@echo ' '

.PHONY: all clean dependents main-build

-include ../makefile.targets

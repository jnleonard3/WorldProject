################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CommonGeometry.cpp \
../CoordinatePoint.cpp \
../CoordinateSystem.cpp \
../Graph.cpp \
../IcosahedronDrawer.cpp \
../IcosahedronGraph.cpp \
../IcosahedronWorld.cpp \
../MessageLogger.cpp \
../Plane.cpp \
../PyramidCoordinateSpace.cpp \
../TriangleTerrainSkin.cpp \
../main.cpp 

OBJS += \
./CommonGeometry.o \
./CoordinatePoint.o \
./CoordinateSystem.o \
./Graph.o \
./IcosahedronDrawer.o \
./IcosahedronGraph.o \
./IcosahedronWorld.o \
./MessageLogger.o \
./Plane.o \
./PyramidCoordinateSpace.o \
./TriangleTerrainSkin.o \
./main.o 

CPP_DEPS += \
./CommonGeometry.d \
./CoordinatePoint.d \
./CoordinateSystem.d \
./Graph.d \
./IcosahedronDrawer.d \
./IcosahedronGraph.d \
./IcosahedronWorld.d \
./MessageLogger.d \
./Plane.d \
./PyramidCoordinateSpace.d \
./TriangleTerrainSkin.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/Jon/Downloads/OpenSceneGraph-3.0.0/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CommonGeometry.cpp \
../Graph.cpp \
../IcosahedronGraph.cpp \
../Plane.cpp \
../main.cpp 

OBJS += \
./CommonGeometry.o \
./Graph.o \
./IcosahedronGraph.o \
./Plane.o \
./main.o 

CPP_DEPS += \
./CommonGeometry.d \
./Graph.d \
./IcosahedronGraph.d \
./Plane.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/Jon/Downloads/OpenSceneGraph-3.0.0/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



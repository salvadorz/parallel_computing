#******************************************************************************
#*Copyright (C) 2023 by Salvador Z                                            *
#*                                                                            *
#*****************************************************************************/
#*
#*@author Salvador Z
#*@brief CMakeLists file to create a CMake project
#*
cmake_minimum_required(VERSION 3.0.0)
project(System_Models
  VERSION 0.1.0
  DESCRIPTION "Project for Parallel Computing"
  LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

### Build Options ###
option(ENABLE_COVERAGE "Enable coverage reporting"              OFF)

### General Configuration ###

set_property(GLOBAL PROPERTY CXX_STANDARD 17)

set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

### Compiler Flags Configuration ###

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_PREFIX_PATH "/opt/OpenCL/ICD-Loader/install/share/cmake" ${CMAKE_PREFIX_PATH})
##########################
# Enable Static Analysis #
##########################
#include(analysis/code-format)


### General Project Structure ###
#find_package(OpenCL REQUIRED)
# https://github.com/KhronosGroup/OpenCL-ICD-Loader
find_package(OpenCLHeaders REQUIRED)
find_package(OpenCLICDLoader REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})

### Project Source Tree ###
add_subdirectory("src")
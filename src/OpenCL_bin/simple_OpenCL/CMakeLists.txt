#******************************************************************************
#*Copyright (C) 2023 by Salvador Z                                            *
#*                                                                            *
#*****************************************************************************/
#*
#*@author Salvador Z
#*@brief CMakeLists file for add directories
#*
add_executable(simple_OpenCL simple_OpenCL.cpp utility.cpp)
target_link_libraries(simple_OpenCL OpenCL::OpenCL)
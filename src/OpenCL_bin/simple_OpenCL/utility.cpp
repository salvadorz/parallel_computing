/*******************************************************************************
 * Copyright (C) 2023 by Salvador Z                                            *
 *                                                                             *
 * This file is part of Parallel Computing                                     *
 *                                                                             *
 *   Permission is hereby granted, free of charge, to any person obtaining a   *
 *   copy of this software and associated documentation files (the Software)   *
 *   to deal in the Software without restriction including without limitation  *
 *   the rights to use, copy, modify, merge, publish, distribute, sublicense,  *
 *   and/or sell copies ot the Software, and to permit persons to whom the     *
 *   Software is furnished to do so, subject to the following conditions:      *
 *                                                                             *
 *   The above copyright notice and this permission notice shall be included   *
 *   in all copies or substantial portions of the Software.                    *
 *                                                                             *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS   *
 *   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARANTIES OF MERCHANTABILITY *
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL   *
 *   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR      *
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,     *
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE        *
 *   OR OTHER DEALINGS IN THE SOFTWARE.                                        *
 ******************************************************************************/

/**
 * @file utility.cpp
 * @author Salvador Z
 * @date 11 Jul 2023
 * @brief File for utility
 *
 */

#include "utility.h"
#include <iostream>
#include <math.h>
#include <stdio.h>

void print_platform_info(std::vector<cl::Platform> *PlatformList) {
  uint num_platforms = PlatformList->size();
  std::cout << "Number of Platforms: " << num_platforms << "\n";
  // Grab Platform Info for each platform
  for (uint i = 0; i < num_platforms; i++) {
    std::cout << "Platform " << i << ": " << PlatformList->at(i).getInfo<CL_PLATFORM_NAME>() << "\n";
  }
  std::cout << "\n";
}

uint get_platform_id_with_string(std::vector<cl::Platform> *PlatformList, const char *name) {
  uint num_platforms = PlatformList->size();
  uint ret_value     = -1;
  // Grab Platform Info for each platform
  for (uint i = 0; i < num_platforms; i++) {
    std::basic_string<char> platform_name = PlatformList->at(i).getInfo<CL_PLATFORM_NAME>();
    if (platform_name.find(name) != std::string::npos) {
      return i;
    }
  }
  return ret_value;
}

void print_device_info(std::vector<cl::Device> *DeviceList) {
  uint num_devices = DeviceList->size();
  std::cout << "Number of Devices in Platform: " << num_devices << "\n";
  // Grab Device Info for each device
  for (uint i = 0; i < num_devices; i++) {
    printf("Device Number: %d\n", i);
    std::cout << "Device Name: " << DeviceList->at(i).getInfo<CL_DEVICE_NAME>() << "\n";
    std::cout << "Is Device Available?: " << DeviceList->at(i).getInfo<CL_DEVICE_AVAILABLE>() << "\n";
    std::cout << "Device Max Compute Units: " << DeviceList->at(i).getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>()
              << "\n";
    std::cout << "Device Max Work Item Dimensions: "
              << DeviceList->at(i).getInfo<CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS>() << "\n";
    std::cout << "Device Max Work Group Size: " << DeviceList->at(i).getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>()
              << "\n";
    std::cout << "Device Max Frequency: " << DeviceList->at(i).getInfo<CL_DEVICE_MAX_CLOCK_FREQUENCY>()
              << "\n";
    std::cout << "Device Max Mem Alloc Size: " << DeviceList->at(i).getInfo<CL_DEVICE_MAX_MEM_ALLOC_SIZE>()
              << "\n\n";
  }
}

void fill_generate(cl_float X[], cl_float Y[], cl_float Z[], cl_float LO, cl_float HI, size_t vectorSize) {

  // Assigns random number from LO to HI to all location of X and Y
  for (uint i = 0; i < vectorSize; ++i) {
    X[i] = LO + (cl_float)rand() / ((cl_float)RAND_MAX / (HI - LO));
    Y[i] = LO + (cl_float)rand() / ((cl_float)RAND_MAX / (HI - LO));
  }
  (void)Z;
}

bool verification(float X[], float Y[], float Z[], float CalcZ[], size_t vectorSize) {
  // Verify if OpenCL Calculation is Same as C Result
  for (uint i = 0; i < vectorSize - 4; i++) {
    if (fabs(CalcZ[i] - Z[i]) > EPSILON) {
      printf("\nVERIFICATION FAILED! index %d, X:%f, Y:%f, OpenCL Result:%f != Result %f)", i, X[i], Y[i],
             Z[i], CalcZ[i]);
      return false;
    }
  }

  // Print 10 Sample Data to Standard Out
  printf("\n\nVERIFICATION PASSED!!!\n\nSome Sample of Results\n");
  printf("------------------------------------\n");
  for (int i = 0; i < (int)vectorSize; i = i + ((int)vectorSize) / 5) {
    printf("Index %d: Input 1 is %f, Input 2 is %f, Result is %f\n", i, ((float *)X)[i], ((float *)Y)[i],
           ((float *)Z)[i]);
  }
  return true;
}

void checkErr(cl_int err, const char *name) {
  if (err != CL_SUCCESS) {
    std::cerr << "ERROR: " << name << " (" << err << ")" << std::endl;
    exit(EXIT_FAILURE);
  }
}

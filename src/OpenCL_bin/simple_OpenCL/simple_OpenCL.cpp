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
 * @file main.cpp
 * @author Salvador Z
 * @date 11 Jul 2023
 * @brief File for simple OpenCL program
 *
 */

#include <fstream>
#include <math.h>
#include <stdio.h>
#include <string>

#include "CL/cl.hpp"
#include "utility.h"

static const cl_uint vectorSize = 4096; // must be evenly divisible by workSize
static const cl_uint workSize   = 256;

#define EXERCISE1

int main(void) {
  cl_int err;

  // Setup Platform
  // Get Platform ID
  std::vector<cl::Platform> PlatformList;

  err = cl::Platform::get(&PlatformList);
  checkErr(err, "Get Platform List");
  checkErr(PlatformList.size() >= 1 ? CL_SUCCESS : -1, "cl::Platform::get");
  print_platform_info(&PlatformList);
  // Look for Fast Emulation Platform
  uint current_platform_id = get_platform_id_with_string(&PlatformList, "Intel(R) OpenCL HD Graphics");
  printf("Using Platform: %d\n\n", current_platform_id);

  // Setup Device
  // Get Device ID
  std::vector<cl::Device> DeviceList;
  err = PlatformList[current_platform_id].getDevices(CL_DEVICE_TYPE_ALL, &DeviceList);
  checkErr(err, "Get Devices");
  print_device_info(&DeviceList);

  // Create Context
  cl::Context mycontext(DeviceList, NULL, NULL, NULL, &err);
  checkErr(err, "Context Constructor");

  // Create Command queue
  cl::CommandQueue myqueue(mycontext, DeviceList[0], 0, &err);
  checkErr(err, "Queue Constructor");

  // Create Buffers for input and output
  cl::Buffer Buffer_In(mycontext, CL_MEM_READ_ONLY, sizeof(cl_float) * vectorSize);
  cl::Buffer Buffer_In2(mycontext, CL_MEM_READ_ONLY, sizeof(cl_float) * vectorSize);
  cl::Buffer Buffer_Out(mycontext, CL_MEM_WRITE_ONLY, sizeof(cl_float) * vectorSize);

  // Inputs and Outputs to Kernel, X and Y are inputs, Z is output
  // The aligned attribute is used to ensure alignment
  // so that DMA could be used if we were working with a real FPGA board
  cl_float X[vectorSize] __attribute__((aligned(64)));
  cl_float Y[vectorSize] __attribute__((aligned(64)));
  cl_float Z[vectorSize] __attribute__((aligned(64)));

  // Allocates memory with value from 0 to 1000
  cl_float LO = 0;
  cl_float HI = 1000;
  fill_generate(X, Y, Z, LO, HI, vectorSize);

  // Write data to device
  err = myqueue.enqueueWriteBuffer(Buffer_In, CL_FALSE, 0, sizeof(cl_float) * vectorSize, X);
  checkErr(err, "WriteBuffer");
  err = myqueue.enqueueWriteBuffer(Buffer_In2, CL_FALSE, 0, sizeof(cl_float) * vectorSize, Y);
  checkErr(err, "WriteBuffer 2");
  myqueue.finish();


  return 0;
}

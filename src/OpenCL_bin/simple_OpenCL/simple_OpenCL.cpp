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

  ////////////// Exercise 1 Step 2.3
  err = checkErr(err, "Get Platform List");
  checkErr(PlatformList.size() >= 1 ? CL_SUCCESS : -1, "cl::Platform::get");
  print_platform_info(&PlatformList);
  // Look for Fast Emulation Platform
  uint current_platform_id = get_platform_id_with_string(&PlatformList, "Emulation");
  printf("Using Platform: %d\n\n", current_platform_id);

  // Setup Device
  // Get Device ID
  std::vector<cl::Device> DeviceList;

  ////////////// Exercise 1 Step 2.5
  err = checkErr(err, "Get Devices");
  print_device_info(&DeviceList);

  // Create Context
  ////////////// Exercise 1 Step 2.6
  cl::Context checkErr(err, "Context Constructor");

  // Create Command queue
  ////////////// Exercise 1 Step 2.7
  cl::CommandQueue checkErr(err, "Queue Constructor");

  // Create Buffers for input and output
  ////////////// Exercise 1 Step 2.8
  cl::Buffer cl::Buffer cl::Buffer

      // Inputs and Outputs to Kernel, X and Y are inputs, Z is output
      // The aligned attribute is used to ensure alignment
      // so that DMA could be used if we were working with a real FPGA board
      cl_float X[vectorSize] __attribute__((aligned(64)));
  cl_float     Y[vectorSize] __attribute__((aligned(64)));
  cl_float     Z[vectorSize] __attribute__((aligned(64)));

  // Allocates memory with value from 0 to 1000
  cl_float LO = 0;
  cl_float HI = 1000;
  fill_generate(X, Y, Z, LO, HI, vectorSize);

  // Write data to device
  ////////////// Exercise 1 Step 2.9
  err = checkErr(err, "WriteBuffer");
  err = checkErr(err, "WriteBuffer 2");
  myqueue.finish();

#ifndef EXERCISE1
  // create the kernel
  const char *kernel_name = "SimpleKernel";

  // Read in binaries from file
  std::ifstream aocx_stream("../SimpleKernel.aocx", std::ios::in | std::ios::binary);
  checkErr(aocx_stream.is_open() ? CL_SUCCESS : -1, "SimpleKernel.aocx");
  std::string           prog(std::istreambuf_iterator<char>(aocx_stream), (std::istreambuf_iterator<char>()));
  cl::Program::Binaries mybinaries(1, std::make_pair(prog.c_str(), prog.length()));

  // Create the Program from the AOCX file.
  ////////////////////// Exercise 2 Step 2.3    ///////////////////
  cl::Program checkErr(err, "Program Constructor");

  // build the program
  //////////////      Compile the Kernel.... For Intel FPGA, nothing is done here, but this conforms to the
  ///standard
  //////////////       Exercise 2   Step 2.4    ///////////////////
  err = checkErr(err, "Build Program");

  // create the kernel
  //////////////       Find Kernel in Program
  //////////////       Exercise 2   Step 2.5    ///////////////////
  cl::Kernel checkErr(err, "Kernel Creation");

  //////////////     Set Arguments to the Kernels
  //////////////       Exercise 2   Step 2.6    ///////////////////
  err = checkErr(err, "Arg 0");
  err = checkErr(err, "Arg 1");
  err = checkErr(err, "Arg 2");
  err = checkErr(err, "Arg 3");

  printf("\nLaunching the kernel...\n");

  // Launch Kernel
  //////////////       Exercise 2   Step 2.7    ///////////////////
  err = checkErr(err, "Kernel Execution");

  // read the output
  //////////////       Exercise 2   Step 2.8    ///////////////////
  err = checkErr(err, "Read Buffer");

  err = myqueue.finish();
  checkErr(err, "Finish Queue");

  float CalcZ[vectorSize];

  for (uint i = 0; i < vectorSize; i++) {
    //////////////  Equivalent Code running on CPUs
    //////////////       Exercise 2   Step 2.9    ///////////////////
    CalcZ[i] =
  }

  // Print Performance Results
  verification(X, Y, Z, CalcZ, vectorSize);

#endif

  return 1;
}

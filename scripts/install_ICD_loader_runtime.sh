#!/bin/bash
# Script to Install ICD loader runtime files from source
# Author: Salvador Z.

# This script avoids the need to install the ICD loader runtime files from package manager
#sudo apt install ocl-icd-libopencl1
#sudo apt install opencl-headers

# Install clinfo to verify OpenCL installation
#sudo apt install clinfo

current_dir=$(pwd)

cd /opt/OpenCL

mkdir -p ICD-Loader/src
cd ICD-Loader/src

# This script installs the ICD loader runtime files
git clone --recursive https://github.com/KhronosGroup/OpenCL-CLHPP
git clone https://github.com/KhronosGroup/OpenCL-ICD-Loader 
git clone https://github.com/KhronosGroup/OpenCL-Headers

cd ..

# Install ICD loader runtime headers files
cmake -D CMAKE_INSTALL_PREFIX=. -S ./src/OpenCL-Headers -B./src/OpenCL-Headers/build 
cmake --build ./src/OpenCL-Headers/build --target install

# Install ICD loader runtime library files
cmake -D CMAKE_PREFIX_PATH=/opt/OpenCL/ICD-Loader -D CMAKE_INSTALL_PREFIX=. -S ./src/OpenCL-ICD-Loader -B./src/OpenCL-ICD-Loader/build 
cmake --build ./src/OpenCL-ICD-Loader/build --target install

# Install OpenCL-CLHPP
cmake -D CMAKE_PREFIX_PATH=/opt/OpenCL/ICD-Loader -D CMAKE_INSTALL_PREFIX=. -S ./src/OpenCL-CLHPP -B./src/OpenCL-CLHPP/build
cmake --build ./src/OpenCL-CLHPP/build --target install

cd "$current_dir"
exit 0
#!/bin/bash
# Script to Install OpenCL Runtimes
# Author: Salvador Z.

#sudo apt install ocl-icd-libopencl1
current_dir=$(pwd)
ubuntu_version=$(lsb_release -rs)

echo "Installing OpenCL™ Runtimes..."
# https://github.com/intel/compute-runtime


cd /opt/OpenCL

install_18_04_dep() {

    mkdir neo-$ubuntu_version
    cd neo-$ubuntu_version
    # Descargar todos los paquetes *.deb

    # Download all *.deb packages
    # release 21.38.21026 (last support for ubuntu 18.04) 
    # https://github.com/intel/compute-runtime/releases/tag/21.38.21026
    wget https://github.com/intel/compute-runtime/releases/download/21.38.21026/intel-gmmlib_21.2.1_amd64.deb
    wget https://github.com/intel/intel-graphics-compiler/releases/download/igc-1.0.8708/intel-igc-core_1.0.8708_amd64.deb
    wget https://github.com/intel/intel-graphics-compiler/releases/download/igc-1.0.8708/intel-igc-opencl_1.0.8708_amd64.deb
    wget https://github.com/intel/compute-runtime/releases/download/21.38.21026/intel-opencl_21.38.21026_amd64.deb
    wget https://github.com/intel/compute-runtime/releases/download/21.38.21026/intel-ocloc_21.38.21026_amd64.deb
    wget https://github.com/intel/compute-runtime/releases/download/21.38.21026/intel-level-zero-gpu_1.2.21026_amd64.deb

    # Verify sha256 sum
    wget https://github.com/intel/compute-runtime/releases/download/21.38.21026/ww38.sum
    sha256sum -c ww38.sum

}

install_20_04_dep() {
    
    mkdir neo-$ubuntu_version
    cd neo-$ubuntu_version

    # release 22.24.23453 (last support for ubuntu 20.04)
    # https://github.com/intel/compute-runtime/releases/tag/22.24.23453
    wget https://github.com/intel/intel-graphics-compiler/releases/download/igc-1.0.11378/intel-igc-core_1.0.11378_amd64.deb
    wget https://github.com/intel/intel-graphics-compiler/releases/download/igc-1.0.11378/intel-igc-opencl_1.0.11378_amd64.deb
    wget https://github.com/intel/compute-runtime/releases/download/22.24.23453/intel-level-zero-gpu-dbgsym_1.3.23453_amd64.ddeb
    wget https://github.com/intel/compute-runtime/releases/download/22.24.23453/intel-level-zero-gpu_1.3.23453_amd64.deb
    wget https://github.com/intel/compute-runtime/releases/download/22.24.23453/intel-opencl-icd-dbgsym_22.24.23453_amd64.ddeb
    wget https://github.com/intel/compute-runtime/releases/download/22.24.23453/intel-opencl-icd_22.24.23453_amd64.deb
    wget https://github.com/intel/compute-runtime/releases/download/22.24.23453/libigdgmm12_22.1.3_amd64.deb

    # Verify sha256 sum
    wget https://github.com/intel/compute-runtime/releases/download/22.24.23453/ww24.sum
    sha256sum -c ww24.sum

}

install_22_04_dep() {

    mkdir neo-$ubuntu_version
    cd neo-$ubuntu_version
    # Descargar paquetes adicionales para Ubuntu 22.04
    wget https://github.com/intel/intel-graphics-compiler/releases/download/igc-1.0.13822.6/intel-igc-core_1.0.13822.6_amd64.deb
    wget https://github.com/intel/intel-graphics-compiler/releases/download/igc-1.0.13822.6/intel-igc-opencl_1.0.13822.6_amd64.deb
    wget https://github.com/intel/compute-runtime/releases/download/23.17.26241.22/intel-level-zero-gpu-dbgsym_1.3.26241.22_amd64.ddeb
    wget https://github.com/intel/compute-runtime/releases/download/23.17.26241.22/intel-level-zero-gpu_1.3.26241.22_amd64.deb
    wget https://github.com/intel/compute-runtime/releases/download/23.17.26241.22/intel-opencl-icd-dbgsym_23.17.26241.22_amd64.ddeb
    wget https://github.com/intel/compute-runtime/releases/download/23.17.26241.22/intel-opencl-icd_23.17.26241.22_amd64.deb
    wget https://github.com/intel/compute-runtime/releases/download/23.17.26241.22/libigdgmm12_22.3.0_amd64.deb

    # Verify sha256 sum
    wget https://github.com/intel/compute-runtime/releases/download/23.17.26241.22/ww17.sum
    sha256sum -c ww17.sum

}

# Verificar la versión de Ubuntu y llamar a la función de instalación correspondiente
case $ubuntu_version in
    18.04)
        install_18_04_dep
        ;;
    20.04)
        install_20_04_dep
        ;;
    22.04)
        install_22_04_dep
        ;;
    *)
        echo "Check for your Ubuntu version"
        ;;
esac

# Install packages
sudo dpkg -i *.deb

cd "$current_dir"

exit 0
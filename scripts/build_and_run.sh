#!/bin/bash

set -e  # Exit on error

# Create build directory if it doesn't exist
mkdir -p build
cd build

# Generate Makefiles with CMake
cmake ..

# Build the project
make

# Run the executable and redirect output to img.ppm
./cpp-raytracer > ../img.ppm
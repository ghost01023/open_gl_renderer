#!/bin/bash

echo "🧹 Cleaning previous build artifacts..."
rm -rf build CMakeFiles CMakeCache.txt cmake_install.cmake Makefile

echo "📁 Creating build directory..."
mkdir build

echo "🔧 Configuring the project with CMake..."
cmake -S . -B build

echo "🔨 Building the project..."
cmake --build build

echo "✅ Build completed successfully."

for i in {1..3}; do
echo ""
done


echo "Launching Game..."
./build/OpenGLApp
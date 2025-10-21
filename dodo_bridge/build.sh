#!/bin/bash

# Build script for image delay subscriber

set -e

echo "Installing dependencies..."
sudo apt update
sudo apt install -y libwebsocketpp-dev libjsoncpp-dev libssl-dev cmake build-essential libopencv-dev libboost-all-dev

echo "Creating build directory..."
mkdir -p build
cd build

echo "Running cmake..."
cmake ..

echo "Building project..."
make -j"$(nproc)"

echo "Build complete! Run ./image_delay_subscriber to start the application."
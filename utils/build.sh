#!/bin/bash

set -e

echo "go in build directory"

rm -rf bin && mkdir bin

rm -rf build && mkdir build && cd build


cmake ../ -DCMAKE_PREFIX_PATH=$(pwd)/../vcpkg_installed/arm64-osx && make

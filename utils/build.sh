#!/bin/bash

set -e

echo "go in build directory"

rm -rf bin && mkdir bin

cmake ../ -DCMAKE_PREFIX_PATH=$(pwd)/../vcpkg_installed/x64-linux && make


cmake ../ -DCMAKE_PREFIX_PATH=$(pwd)/../vcpkg_installed/x64-linux && make

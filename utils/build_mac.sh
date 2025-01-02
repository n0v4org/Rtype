#!/bin/bash

set -e

echo "go in build directory"

rm -rf bin && mkdir bin

rm -rf build && mkdir build && cd build

cmake ../ -DCMAKE_TOOLCHAIN_FILE=~$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake && make
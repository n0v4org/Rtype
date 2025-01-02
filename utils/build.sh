#!/bin/bash

set -e

echo "go in build directory"

rm -rf bin && mkdir bin

rm -rf build && mkdir build && cd build && pwd

cmake ../ -DCMAKE_PREFIX_PATH=/home/TristanDlh/Work/tek3/cpp/leVraiRtype/vcpkg_installed/x64-linux && make

#!/bin/bash

set -e

echo "go in build directory"

rm -rf build
mkdir build
cd build/

cmake ../ -DCMAKE_TOOLCHAIN_FILE=~$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake && make

mv server/r-type_server  server/r-type_server_tests client/r-type_client client/r-type_client_tests ../ 

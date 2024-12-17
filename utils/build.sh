#!/bin/bash

set -e

echo "go in build directory"

rm -rf build
mkdir build
cd build/

cmake ../ -DCMAKE_PREFIX_PATH=~/vcpkg/installed/x64-linux && make

#mv server/r-type_server  server/r-type_server_tests client/r-type_client client/r-type_client_tests ../ 

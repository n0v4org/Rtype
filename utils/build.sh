#!/bin/bash

set -e

echo "go in build directory"

rm -rf build
mkdir build
cd build/

cmake ../ -DCMAKE_PREFIX_PATH=C:\Users\Tristan\OneDrive\Documents\RType\Rtype\vcpkg_installed\x64-windows  && make

#mv server/r-type_server  server/r-type_server_tests client/r-type_client client/r-type_client_tests ../ 

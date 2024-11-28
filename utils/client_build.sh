#!/bin/bash

set -e

echo "go in build directory"

rm -rf client_build
mkdir client_build
cd client_build/

cmake ../client/ -DCMAKE_TOOLCHAIN_FILE=~$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake && make

mv r-type_client r-type_client_tests ../ 

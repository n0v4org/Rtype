#!/bin/bash

set -e

echo "go in build directory"

rm -rf engine/build
mkdir engine/build
cd engine/build


cmake ../ && make


mv libzefir.a ../bin/
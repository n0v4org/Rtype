#!/bin/bash

set -e

echo "go in build directory"

rm -rf engine/graphic/sfml/build
mkdir engine/graphic/sfml/build
cd engine/graphic/sfml/build


cmake ../ && make


mv libsfml.a ../../../bin/
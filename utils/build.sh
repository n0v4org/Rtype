#!/bin/bash

set -e

echo "go in build directory"

cd build/

cmake ../ && make

mv server/r-type_server client/r-type_client ../ 

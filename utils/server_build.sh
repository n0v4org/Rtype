set -e

echo "go in build directory"

rm -rf server_build
mkdir server_build
cd server_build/

cmake ../server/ -DCMAKE_TOOLCHAIN_FILE=~$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake && make

mv r-type_server  r-type_server_tests ../ 
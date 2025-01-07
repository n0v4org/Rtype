
rmdir /s /q .\build
mkdir build
cd .\build\

cmake ..\ -DCMAKE_PREFIX_PATH=C:\Users\Tristan\OneDrive\Documents\RType\Rtype\vcpkg_installed\x64-windows  && cmake --build .

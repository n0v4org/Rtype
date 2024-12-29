
rmdir /s /q .\build\server
mkdir .\build\server
rmdir /s /q .\build\engine
mkdir .\build\engine
cd .\build\

cmake ..\ -DCMAKE_PREFIX_PATH=C:\Users\Tristan\OneDrive\Documents\RType\Rtype\vcpkg_installed\x64-windows  && cmake --build .


rmdir /s /q .\bin
mkdir bin

rmdir /s /q .\build
mkdir build
cd .\build\

cmake ..\ -DCMAKE_PREFIX_PATH=%cd%\..\vcpkg_installed\x64-windows  && cmake --build .

echo %cd%
move ..\bin\Debug\* ..\bin
rmdir ..\bin\Debug

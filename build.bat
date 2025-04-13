echo Starting build...
cmake -B ./build
cd ./build
cmake --build . --config Release
cd ./bin
dir
echo BUILD COMPLETED
echo "Starting build..."
cmake -B ./build
cd ./build
cmake --build . --config Release
cd ./bin
ls
echo "BUILD COMPLETED"
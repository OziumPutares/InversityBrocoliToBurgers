conan install . --output-folder=build --build=missing -s build_type=Debug
cmake -B build --preset conan-debug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build --preset conan-debug

WASI_SDK_PATH=`pwd`/wasi-sdk-${WASI_VERSION_FULL}-${WASI_ARCH}-${WASI_OS}
CC="${WASI_SDK_PATH}/bin/clang --sysroot=${WASI_SDK_PATH}/share/wasi-sysroot"
conan install . --output-folder=build --build=missing -s build_type=Debug
cmake -B build --preset conan-debug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON DCMAKE_TOOLCHAIN_FILE=${WASI_SDK_PATH}/share/cmake/wasi-sdk.cmake
cmake --build build --preset conan-debug

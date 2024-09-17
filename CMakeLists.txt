cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED 23)
project(ObesityTacklingAdBlocker CXX)

# Enable testing framework
enable_testing()
# Set up subdirectories
add_subdirectory(tests)
add_subdirectory(src)


# Optional for LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

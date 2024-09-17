# Create test executable
add_executable(ParseConfigTest parseTests.cpp)
add_executable(FilterConfigTest filteringTests.cpp)

# Find Catch2 for unit testing
find_package(Catch2 REQUIRED)

# Link test executable with Catch2 and the parsing library
target_link_libraries(ParseConfigTest PRIVATE Catch2::Catch2WithMain parsing filtering)
target_link_libraries(FilterConfigTest PRIVATE Catch2::Catch2WithMain parsing filtering)

# Make sure to include src directory where parseConfig.hpp is located
target_include_directories(ParseConfigTest PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Register the test
add_test(NAME ParseConfigTest COMMAND ParseConfigTest)
add_test(NAME FilterConfigTest COMMAND FilterConfigTest)


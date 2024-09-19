# Define the libraries
add_library(low_level_code STATIC listAccess.cpp listAccess.hpp)
add_library(parsing STATIC parseConfig.cpp parseConfig.hpp)
add_library(filtering STATIC filterList.cpp filterList.cpp filterList.hpp)
#target_compile_options(${PROJECT_NAME} PRIVATE
#  $<$<COMPILE_LANGUAGE:CXX>:-Wall -Wextra -pedantic -Werror -Wconversion -Wnrvo>)
target_compile_options(low_level_code PRIVATE
  $<$<COMPILE_LANGUAGE:CXX>:-Wall -Wextra -pedantic -Werror -Wconversion -Wnrvo>)
target_compile_options(parsing PRIVATE
  $<$<COMPILE_LANGUAGE:CXX>:-Wall -Wextra -pedantic -Werror -Wconversion -Wnrvo>)
target_compile_options(filtering PRIVATE
  $<$<COMPILE_LANGUAGE:CXX>:-Wall -Wextra -pedantic -Werror -Wconversion -Wnrvo>)

# Set include directories for both libraries
target_include_directories(low_level_code PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_include_directories(parsing PUBLIC ${CMAKE_SOURCE_DIR}/src)

# Find CURL package
find_package(CURL REQUIRED)

# Link CURL to low_level_code
target_link_libraries(low_level_code CURL::libcurl)

# Define the main executable and link it to the libraries
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} low_level_code parsing filtering CURL::libcurl)


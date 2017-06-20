# To compile the project with CMake, first make sure cmake is installed
# in your system (apt-get install cmake).
# 
# In the project root folder, run the following commands:
#	mkdir build
#   cd build
#   cmake ..
#   make
#   make test # to run the tests
#   ctest --verbose # (to get the full output of the tests)

cmake_minimum_required(VERSION 3.7)
project(disk-drive)

set(CMAKE_CXX_STANDARD 14)

# Library target
set(LIBRARY_SOURCE_FILES src/libfat.cpp src/disk.cpp)
add_library(disk ${LIBRARY_SOURCE_FILES})

# Include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Main binary target
add_executable(disk-main ${LIBRARY_SOURCE_FILES} src/menu-main.cpp)

# Add the tests
enable_testing()
foreach(test_name disk libfat)
    add_executable(runTest-${test_name} test/test-${test_name}.cpp)
    target_link_libraries(runTest-${test_name} disk)
    add_test(${test_name} runTest-${test_name})
endforeach(test_name)

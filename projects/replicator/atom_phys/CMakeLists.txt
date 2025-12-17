cmake_minimum_required(VERSION 3.14)
project(AtomPhys)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencies
find_package(GTest REQUIRED)
include(GoogleTest)

# Source Code
add_subdirectory(src)

# Tests
add_executable(run_tests tests/test_system.cpp)
target_link_libraries(run_tests PRIVATE atomphys_lib GTest::GTest GTest::Main)
gtest_discover_tests(run_tests)
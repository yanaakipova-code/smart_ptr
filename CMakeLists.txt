cmake_minimum_required(VERSION 3.14)
project(smart_ptr_homework LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 23)

include(CTest)
add_subdirectory(extern/googletest)

add_executable(smart_ptr_tests tests.cpp)

target_link_libraries(smart_ptr_tests PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(smart_ptr_tests)
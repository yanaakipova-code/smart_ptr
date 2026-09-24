cmake_minimum_required(VERSION 3.14)
project(smart_ptr_homework LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
add_subdirectory(extern/googletest)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(extern/benchmark)

add_executable(smart_ptr_tests
    tests.cpp
)

target_include_directories(smart_ptr_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/smart
)

target_link_libraries(smart_ptr_tests PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(smart_ptr_tests)

add_executable(smart_ptr_bench
    benchmarks.cpp
)

target_include_directories(smart_ptr_bench PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/smart
)

target_link_libraries(smart_ptr_bench PRIVATE benchmark::benchmark)

target_compile_options(smart_ptr_bench PRIVATE -O2)


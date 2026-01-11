cmake_minimum_required(VERSION 3.16)
project(ZooERP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(${GTEST_INCLUDE_DIRS})

find_package(GTest REQUIRED)

add_executable(ZooERP
    src/main.cpp
)
target_include_directories(ZooERP PRIVATE src)

add_executable(run_tests tests/test_main.cpp tests/test_zoo.cpp tests/test_herbo.cpp)
target_link_libraries(run_tests ${GTEST_LIBRARIES} pthread)
target_include_directories(run_tests PRIVATE src)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(STATUS "Enabling coverage flags for clang/LLVM")
    target_compile_options(run_tests PRIVATE -fprofile-instr-generate -fcoverage-mapping -O0)
    target_link_options(run_tests PRIVATE -fprofile-instr-generate -fcoverage-mapping)
endif()
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(run_tests PRIVATE --coverage -O0)
    target_link_libraries(run_tests PRIVATE --coverage)
endif()

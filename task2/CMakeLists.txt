cmake_minimum_required(VERSION 3.16)
project(FinanceERP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(FinanceERP
    src/main.cpp
    src/domain/bank_account.h
    src/domain/category.h
    src/domain/operation.h
    src/facade/bank_account_facade.h
    src/facade/category_facade.h
    src/facade/operation_facade.h
    src/factory/finance_factory.h
)

target_include_directories(FinanceERP PRIVATE src)

add_executable(run_tests
    tests/test_main.cpp
    tests/test_bank_account.cpp
    tests/test_category.cpp
    tests/test_operation.cpp
)
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
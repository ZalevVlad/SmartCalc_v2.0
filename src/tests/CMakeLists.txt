cmake_minimum_required(VERSION 3.27)
project(SmartCalc2)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_executable(tests main.cc
        ../model/credit_calc.cc
        ../model/date.cc
        ../model/deposit_calc.cc
        ../model/polish.cc
)

#include_directories(../model)

# Gtest
enable_testing()
find_package(GTest REQUIRED)
target_link_libraries(tests GTest::gtest_main)


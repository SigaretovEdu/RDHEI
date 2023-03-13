cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(RDHEI)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV REQUIRED)
find_package(GTest REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenCV_CXX_FLAGS}")

set(SOURCES main.cpp tests.cpp)

add_executable(sol ${SOURCES})
target_link_libraries(sol "${OpenCV_LIBRARIES}" GTest::gtest_main)

cmake_minimum_required(VERSION 3.10)
project(problem_077)
set(CMAKE_CXX_STANDARD 17)
add_executable(code main.cpp)
# Ensure header is found
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

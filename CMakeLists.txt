cmake_minimum_required(VERSION 3.19)

# set the project name and version
project(search VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(run_search_example src/main.cpp)

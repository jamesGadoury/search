cmake_minimum_required(VERSION 3.19)

# set the project name and version
project(search VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra -Werror -g)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(
    ${PROJECT_NAME} ${warning_guard}
    INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

add_executable(run_search_example main.cpp)
target_link_libraries(run_search_example PUBLIC ${PROJECT_NAME})


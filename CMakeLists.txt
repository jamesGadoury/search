cmake_minimum_required(VERSION 3.19)

# set the project name and version
project(search VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(
    -Wall -Wextra -Werror
    $<$<CONFIG:DEBUG>:-g3>
    $<$<CONFIG:RELEASE>:-O3>
)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(
    ${PROJECT_NAME} ${warning_guard}
    INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

add_executable(run_small_state_space_example src/examples/small_state_space.cpp)
target_link_libraries(run_small_state_space_example PUBLIC ${PROJECT_NAME})

add_executable(run_ids_example src/examples/ids.cpp)
target_link_libraries(run_ids_example PUBLIC ${PROJECT_NAME})

add_executable(run_1000_by_1000_grid_state_space_example src/examples/1000_by_1000_grid_state_space.cpp)
target_link_libraries(run_1000_by_1000_grid_state_space_example PUBLIC ${PROJECT_NAME})

add_executable(run_a_star_with_events src/examples/a_star_with_events.cpp)
target_link_libraries(run_a_star_with_events PUBLIC ${PROJECT_NAME})

if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    add_executable(run_tests test/test_all.cpp test/test_helpers.cpp test/test_grid_problem.cpp)
    target_link_libraries(run_tests PUBLIC ${PROJECT_NAME})
endif()

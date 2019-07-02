cmake_minimum_required(VERSION 2.8)

project(snake)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(nibbler main.cpp)
add_custom_command(OUTPUT ${CMAKE_SOURCE_DIR}/SnakeAllegro/libSnakeAllegro.so
                   COMMAND make
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/SnakeAllegro
)
target_compile_options (nibbler PRIVATE -Wall -Wextra -Werror -std=c++11)
target_link_libraries(nibbler -ldl)
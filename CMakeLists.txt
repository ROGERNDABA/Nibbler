cmake_minimum_required(VERSION 2.8)

project(snake)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(nibbler main.cpp)
target_compile_options (nibbler PRIVATE -Wall -Wextra -Werror -std=c++11)
target_link_libraries(nibbler -ldl)
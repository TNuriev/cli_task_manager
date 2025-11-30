cmake_minimum_required(VERSION 3.10)

project(TaskManager)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

include_directories(include)

add_executable(TaskManager
    src/TaskManager.cpp
    src/struct.cpp
)

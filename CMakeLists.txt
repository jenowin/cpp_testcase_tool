cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

project(com VERSION 1.0)
add_executable(com src/init.c)

target_include_directories(com PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

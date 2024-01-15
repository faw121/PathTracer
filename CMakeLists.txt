cmake_minimum_required(VERSION 3.1)

project(path_tracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BIN ${CMAKE_CURRENT_LIST_DIR}/bin/$<CONFIG>)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN})

add_subdirectory(path_tracer)
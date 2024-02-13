cmake_minimum_required(VERSION 3.24)
set(PROJECT_NAME CppProject)
project(${PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(AppName main.cpp)


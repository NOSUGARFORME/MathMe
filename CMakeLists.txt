cmake_minimum_required(VERSION 3.25)
project(MathMe)

set(CMAKE_CXX_STANDARD 17)

add_executable(MathMe main.cpp exprtk.hpp FunctionSettings.cpp FunctionSettings.h)

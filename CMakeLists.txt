cmake_minimum_required(VERSION 3.10)
project(hex_vals)

add_executable(hex_vals main.cpp)
target_compile_options(hex_vals PRIVATE -g -O0)
cmake_minimum_required(VERSION 3.14)
project(chip_8_emu_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(chip_8_emu_cpp src/main.cpp src/cpu/cpu.cpp src/cpu/cpu.hpp)
cmake_minimum_required(VERSION 3.14)
project(chip_8_emu_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(chip_8_emu_cpp src/main.cpp src/cpu.cpp src/cpu.hpp src/ram.cpp src/ram.hpp src/emulator.cpp src/emulator.hpp src/rom.cpp src/rom.hpp src/input.cpp src/input.hpp src/sound.cpp src/sound.hpp src/exceptions.cpp src/exceptions.hpp)
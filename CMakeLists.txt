cmake_minimum_required(VERSION 3.14)
project(chip_8_emu_cpp)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_PATH "C:\\Repositories\\SDL2-2.0.10\\i686-w64-mingw32")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(SDL2 REQUIRED)

add_executable(chip_8_emu_cpp src/main.cpp src/core/cpu.cpp src/core/cpu.hpp src/core/ram.cpp src/core/ram.hpp src/core/emulator.cpp src/core/emulator.hpp src/platform/binary_rom.cpp src/platform/binary_rom.hpp src/platform/sdl2_sound.cpp src/platform/sdl2_sound.hpp src/core/exceptions.cpp src/core/exceptions.hpp src/core/interface_rom.hpp src/core/interface_graphics.hpp src/core/interface_sound.hpp src/core/interface_input.hpp src/platform/sdl2_graphics.cpp src/platform/sdl2_graphics.hpp src/platform/keyboard_input.cpp src/platform/keyboard_input.hpp src/core/timer.cpp src/core/timer.hpp)
target_include_directories(chip_8_emu_cpp PRIVATE ${SDL2_INCLUDE_DIR})
target_link_libraries(chip_8_emu_cpp ${SDL2_LIBRARY})

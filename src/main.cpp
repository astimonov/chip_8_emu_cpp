#include <iostream>
#include <string>

#include "emulator.hpp"
#include "rom.hpp"

using namespace emulator;

static constexpr std::string_view ROM_FILENAME {"roms/INVADERS"};

int main() {
    Rom rom {std::string(ROM_FILENAME)};
    Emulator emulator_instance {rom};

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

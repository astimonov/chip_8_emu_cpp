#include <iostream>
#include <string>

#include "emulator.hpp"
#include "rom.hpp"

using namespace emulator;

static constexpr std::string_view ROM_FILENAME {"../roms/INVADERS"};

int main() {
    try {
        Rom rom{std::string(ROM_FILENAME)};
        Emulator emulator_instance{rom};

        std::cout << "Emulator created!" << std::endl;
    } catch (...) {
        // TODO: Proper exception handling
        std::cout << "Error!" << std::endl;
    }

    return 0;
}

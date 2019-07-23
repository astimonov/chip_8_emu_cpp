#include <iostream>
#include <string>

#include "emulator.hpp"
#include "rom.hpp"
#include "exceptions.hpp"

using namespace emulator;

static constexpr std::string_view ROM_FILENAME {"../roms/INVADERS"};

int main() {
    try {
        Rom rom{std::string(ROM_FILENAME)};
        Emulator emulator_instance{rom};
        emulator_instance.Run();
    } catch (IllegalInstruction& e) {
        std::cout << e.what()
                  << " PC = 0x" << std::hex << e.GetPC()
                  << " (0x" << e.GetOpcode()
                  << ")\n";
    } catch (StoreAccessFailed& e) {
        std::cout << e.what()
                  << " PC = 0x" << std::hex << e.GetPC()
                  << " , address = " << e.GetAddress()
                  << '\n';
    } catch (LoadAccessFailed& e) {
        std::cout << e.what()
                  << " PC = 0x" << std::hex << e.GetPC()
                  << " , address = " << e.GetAddress()
                  << '\n';
    }

    return 0;
}

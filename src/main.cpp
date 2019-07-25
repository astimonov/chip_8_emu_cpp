#include <iostream>
#include <string>

#include "core/emulator.hpp"
#include "core/exceptions.hpp"
#include "platform/binary_rom.hpp"
#include "platform/sdl2_graphics.hpp"
#include "platform/sdl2_sound.hpp"
#include "platform/keyboard_input.hpp"

using namespace emulator;

static constexpr std::string_view ROM_FILENAME{"../roms/INVADERS"};

int main() {
    try {
        auto rom = std::make_shared<BinaryRom>(std::string(ROM_FILENAME));
        auto graphics = std::make_shared<SDL2Graphics>();
        auto sound = std::make_shared<SDL2Sound>();
        auto input = std::make_shared<KeyboardInput>();

        Emulator emulator_instance{rom, graphics, sound, input};
        emulator_instance.Run();
    } catch (IllegalInstruction &e) {
        std::cout << e.what()
                  << " PC = 0x" << std::hex << e.GetPC()
                  << " (0x" << e.GetOpcode()
                  << ")\n";
    } catch (StoreAccessFailed &e) {
        std::cout << e.what()
                  << " PC = 0x" << std::hex << e.GetPC()
                  << " , address = " << e.GetAddress()
                  << '\n';
    } catch (LoadAccessFailed &e) {
        std::cout << e.what()
                  << " PC = 0x" << std::hex << e.GetPC()
                  << " , address = " << e.GetAddress()
                  << '\n';
    } catch (StackOverflow &e) {
        std::cout << e.what()
                  << " PC = 0x" << std::hex << e.GetPC()
                  << '\n';
    } catch (StackUnderflow &e) {
        std::cout << e.what()
                  << " PC = 0x" << std::hex << e.GetPC()
                  << '\n';
    }

    return 0;
}

#include <iostream>
#include <string>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "core/emulator.hpp"
#include "core/exceptions.hpp"
#include "platform/binary_rom.hpp"
#include "platform/sdl2_graphics.hpp"
#include "platform/sdl2_sound.hpp"
#include "platform/keyboard_input.hpp"

using namespace emulator;

static constexpr std::string_view ROM_FILENAME{"../roms/INVADERS"};

int main(int argc, char ** argv) {
    std::string rom_filename = (argc > 1) ? argv[1] : std::string(ROM_FILENAME);

    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        return 1;
    };

    int result = 1;

    try {
        auto rom = std::make_shared<BinaryRom>(rom_filename);
        auto graphics = std::make_shared<SDL2Graphics>();
        auto sound = std::make_shared<SDL2Sound>();
        auto input = std::make_shared<KeyboardInput>();

        Emulator emulator_instance{rom, graphics, sound, input};

        SDL_Event e;
        bool stop = false;

        while (!stop) {
            emulator_instance.RunCycle();

            if (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    stop = true;
                }
            }

            SDL_Delay(1);
        }

        result = 0;
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
    } catch (std::runtime_error &e) {
        std::cout << e.what();
    }

    SDL_Quit();

    return result;
}

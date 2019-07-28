#include <exception>
#include <map>

#include <SDL.h>

#include "keyboard_input.hpp"

using namespace emulator;

KeyboardInput::KeyboardInput() {
    this->m_keys = {};
}

bool KeyboardInput::IsKeyPressed(uint32_t key) {
    return this->m_keys[key];
}

void KeyboardInput::Scan() {
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state == nullptr) {
        throw std::runtime_error("Could not get keyboard state");
    }

    static std::map<uint32_t, SDL_Scancode> mapping = {
            { 0x0, SDL_SCANCODE_1 },
            { 0x1, SDL_SCANCODE_2 },
            { 0x2, SDL_SCANCODE_3 },
            { 0x3, SDL_SCANCODE_4 },
            { 0x4, SDL_SCANCODE_Q },
            { 0x5, SDL_SCANCODE_W },
            { 0x6, SDL_SCANCODE_E },
            { 0x7, SDL_SCANCODE_R },
            { 0x8, SDL_SCANCODE_A },
            { 0x9, SDL_SCANCODE_S },
            { 0xA, SDL_SCANCODE_D },
            { 0xB, SDL_SCANCODE_F },
            { 0xC, SDL_SCANCODE_Z },
            { 0xD, SDL_SCANCODE_X },
            { 0xE, SDL_SCANCODE_C },
            { 0xF, SDL_SCANCODE_V },
    };

    for (auto const& [key, scancode] : mapping) {
        this->m_keys[key] = state[scancode];
    }
}

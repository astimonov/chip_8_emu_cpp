//
// Created by Alexander on 25.07.2019.
//

#include "keyboard_input.hpp"

using namespace emulator;

KeyboardInput::KeyboardInput() {
    this->m_keys = {};
}

bool KeyboardInput::IsKeyPressed(uint32_t key) {
    return this->m_keys[key];
}

void KeyboardInput::Scan() {

}

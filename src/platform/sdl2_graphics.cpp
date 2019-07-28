//
// Created by Alexander on 25.07.2019.
//

#include "sdl2_graphics.hpp"

using namespace emulator;

SDL2Graphics::SDL2Graphics() {
    this->Reset();
}

void SDL2Graphics::Reset() {
    this->m_graphics_memory = {};
}

void SDL2Graphics::Draw() {

}

uint8_t SDL2Graphics::GetXY(uint32_t x, uint32_t y) {
    return 0;
}

void SDL2Graphics::SetXY(uint32_t x, uint32_t y, uint8_t value) {

}

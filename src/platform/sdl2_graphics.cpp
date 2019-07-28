#include <exception>

#include <SDL.h>

#include "sdl2_graphics.hpp"

using namespace emulator;

SDL2Graphics::SDL2Graphics() {
    this->Reset();

    this->m_window = SDL_CreateWindow("CHIP-8 Emulator",
                                      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 320,
                                      SDL_WINDOW_RESIZABLE);
    if (this->m_window == nullptr) {
        throw std::runtime_error("Could not create window");
    }

    this->m_renderer = SDL_CreateRenderer(this->m_window, -1, SDL_RENDERER_ACCELERATED);

    if (this->m_renderer == nullptr) {
        SDL_DestroyWindow(this->m_window);
        throw std::runtime_error("Could not create renderer");
    }

    this->m_texture = SDL_CreateTexture(this->m_renderer, SDL_PIXELFORMAT_ARGB8888,
                                        SDL_TEXTUREACCESS_STREAMING,
                                        IGraphics::GFX_MAX_X, IGraphics::GFX_MAX_Y);

    if (this->m_texture == nullptr) {
        SDL_DestroyRenderer(this->m_renderer);
        SDL_DestroyWindow(this->m_window);
        throw std::runtime_error("Could not create texture");
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
}

SDL2Graphics::~SDL2Graphics() {
    SDL_DestroyRenderer(this->m_renderer);
    SDL_DestroyWindow(this->m_window);
}

void SDL2Graphics::Reset() {
    for (auto& y : this->m_graphics_memory) {
        for (auto& x : y) {
            x = PALETTE_PIXEL_0;
        }
    }
}

void SDL2Graphics::Draw() {

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    SDL_GetWindowSize(this->m_window, &rect.w, &rect.h);

    SDL_UpdateTexture(this->m_texture, nullptr, this->m_graphics_memory.data(),
                IGraphics::GFX_MAX_X * sizeof(uint32_t));
    SDL_RenderClear(this->m_renderer);
    SDL_RenderCopy(this->m_renderer, this->m_texture, nullptr, &rect);
    SDL_RenderPresent(this->m_renderer);
}

uint8_t SDL2Graphics::GetXY(uint32_t x, uint32_t y) {
    return SDL2Graphics::NormalizeColor(this->m_graphics_memory[y][x]);
}

void SDL2Graphics::SetXY(uint32_t x, uint32_t y, uint8_t value) {
    this->m_graphics_memory[y][x] = SDL2Graphics::DenormalizeColor(value);
}

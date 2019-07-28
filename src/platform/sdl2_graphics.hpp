#ifndef CHIP_8_EMU_CPP_SDL2_GRAPHICS_HPP
#define CHIP_8_EMU_CPP_SDL2_GRAPHICS_HPP

#include <memory>

#include "../core/interface_graphics.hpp"

namespace emulator {
    class SDL2Graphics : public IGraphics {
    public:
        SDL2Graphics();
        ~SDL2Graphics();
        void Reset();
        void Draw();
        uint8_t GetXY(uint32_t x, uint32_t y);
        void SetXY(uint32_t x, uint32_t y, uint8_t value);
    private:
        static constexpr uint32_t PALETTE_PIXEL_1 = 0x0000B3FF;
        static constexpr uint32_t PALETTE_PIXEL_0 = 0x0001344A;

        std::array<std::array<uint32_t, IGraphics::GFX_MAX_X>, IGraphics::GFX_MAX_Y> m_graphics_memory;
        SDL_Window *m_window;
        SDL_Renderer *m_renderer;
        SDL_Texture *m_texture;

        static constexpr uint32_t DenormalizeColor(uint8_t normalized) {
            return normalized ? SDL2Graphics::PALETTE_PIXEL_1 : SDL2Graphics::PALETTE_PIXEL_0;
        }

        static constexpr uint8_t NormalizeColor(uint32_t color) {
            return color == SDL2Graphics::PALETTE_PIXEL_1 ? 1 : 0;
        }
    };
}

#endif //CHIP_8_EMU_CPP_SDL2_GRAPHICS_HPP

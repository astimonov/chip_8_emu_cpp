#ifndef CHIP_8_EMU_CPP_SDL2_GRAPHICS_HPP
#define CHIP_8_EMU_CPP_SDL2_GRAPHICS_HPP

#include <memory>

#include "../core/interface_graphics.hpp"

namespace emulator {
    class SDL2Graphics : public IGraphics {
    public:
        SDL2Graphics();
        void Reset();
        void Draw();
        uint8_t GetXY(uint32_t x, uint32_t y);
        void SetXY(uint32_t x, uint32_t y, uint8_t value);
    private:
        std::array<std::array<uint8_t, IGraphics::GFX_MAX_Y>, IGraphics::GFX_MAX_X> m_graphics_memory;
    };
}

#endif //CHIP_8_EMU_CPP_SDL2_GRAPHICS_HPP

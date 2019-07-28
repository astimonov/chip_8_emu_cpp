#ifndef CHIP_8_EMU_CPP_INTERFACE_GRAPHICS_HPP
#define CHIP_8_EMU_CPP_INTERFACE_GRAPHICS_HPP

#include <array>

namespace emulator {
    class IGraphics {
    public:
        static constexpr int GFX_MAX_X = 64;
        static constexpr int GFX_MAX_Y = 32;
        virtual ~IGraphics() = default;
        virtual void Reset() = 0;
        virtual void Draw() = 0;
        virtual uint8_t GetXY(uint32_t x, uint32_t y) = 0;
        virtual void SetXY(uint32_t x, uint32_t y, uint8_t value) = 0;
    };
}

#endif //CHIP_8_EMU_CPP_INTERFACE_GRAPHICS_HPP

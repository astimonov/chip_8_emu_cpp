#ifndef CHIP_8_EMU_CPP_INTERFACE_INPUT_HPP
#define CHIP_8_EMU_CPP_INTERFACE_INPUT_HPP

#include <cstdint>

namespace emulator {
    class IInput {
    public:
        static constexpr uint32_t KEYS_QTY = 16;
        virtual ~IInput() = default;
        virtual void Scan() = 0;
        virtual bool IsKeyPressed(uint32_t key) = 0;
    };
}

#endif //CHIP_8_EMU_CPP_INTERFACE_INPUT_HPP

#ifndef CHIP_8_EMU_CPP_KEYBOARD_INPUT_HPP
#define CHIP_8_EMU_CPP_KEYBOARD_INPUT_HPP

#include <memory>

#include "../core/interface_input.hpp"

namespace emulator {
    class KeyboardInput : public IInput {
    public:
        KeyboardInput();
        void Scan();
        bool IsKeyPressed(uint32_t key);
    private:
        std::array<bool, IInput::KEYS_QTY> m_keys;
    };
}

#endif //CHIP_8_EMU_CPP_KEYBOARD_INPUT_HPP

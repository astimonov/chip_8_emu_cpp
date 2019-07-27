#ifndef CHIP_8_EMU_CPP_EMULATOR_HPP
#define CHIP_8_EMU_CPP_EMULATOR_HPP

#include <memory>
#include <string>
#include <array>

#include "interface_graphics.hpp"
#include "interface_input.hpp"
#include "interface_rom.hpp"
#include "interface_sound.hpp"
#include "ram.hpp"
#include "cpu.hpp"

namespace emulator {
    class Emulator {
    public:
        explicit Emulator(std::shared_ptr<IRom> rom,
                          std::shared_ptr<IGraphics> graphics,
                          std::shared_ptr<ISound> sound,
                          std::shared_ptr<IInput> input);
        void Run();
    private:
        static constexpr uint16_t PC_START = 0x0200;
        static constexpr uint16_t FONTSET_BA = 0x0000;
        static constexpr uint16_t FONTSET_SIZE = 80;
        std::unique_ptr<Cpu> m_cpu;
        std::shared_ptr<Ram> m_ram;
        std::shared_ptr<IRom> m_rom;
        std::shared_ptr<IGraphics> m_graphics;
        std::shared_ptr<ISound> m_sound;
        std::shared_ptr<IInput> m_input;
        static const std::array<uint8_t, FONTSET_SIZE> m_fontset;
    };
}

#endif //CHIP_8_EMU_CPP_EMULATOR_HPP

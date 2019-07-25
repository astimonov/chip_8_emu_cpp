#ifndef CHIP_8_EMU_CPP_EMULATOR_HPP
#define CHIP_8_EMU_CPP_EMULATOR_HPP

#include <memory>
#include <string>

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
        static constexpr uint16_t PC_START = 0x200;
        std::unique_ptr<Cpu> m_cpu;
        std::shared_ptr<Ram> m_ram;
        std::shared_ptr<IRom> m_rom;
        std::shared_ptr<IGraphics> m_graphics;
        std::shared_ptr<ISound> m_sound;
        std::shared_ptr<IInput> m_input;
    };
}

#endif //CHIP_8_EMU_CPP_EMULATOR_HPP

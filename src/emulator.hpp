#ifndef CHIP_8_EMU_CPP_EMULATOR_HPP
#define CHIP_8_EMU_CPP_EMULATOR_HPP

#include <memory>
#include <string>

#include "ram.hpp"
#include "cpu.hpp"
#include "rom.hpp"
#include "input.hpp"

namespace emulator {
    class Emulator {
    public:
        explicit Emulator(Rom rom);
    private:
        static constexpr uint16_t PC_START = 0x200;
        std::unique_ptr<Cpu> m_cpu;
        std::shared_ptr<Ram> m_ram;
        Rom m_rom;
        Input m_input;
    };
}

#endif //CHIP_8_EMU_CPP_EMULATOR_HPP

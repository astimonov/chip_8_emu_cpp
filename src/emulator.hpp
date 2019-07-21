#ifndef CHIP_8_EMU_CPP_EMULATOR_HPP
#define CHIP_8_EMU_CPP_EMULATOR_HPP

#include <memory>
#include <string>

#include "ram.hpp"
#include "cpu.hpp"
#include "rom.hpp"

namespace emulator {
    class Emulator {
    public:
        explicit Emulator(Rom rom);
    private:
        std::unique_ptr<Cpu> m_cpu;
        std::shared_ptr<Ram> m_ram;
        Rom m_rom;
    };
}

#endif //CHIP_8_EMU_CPP_EMULATOR_HPP

#ifndef CHIP_8_EMU_CPP_EMULATOR_HPP
#define CHIP_8_EMU_CPP_EMULATOR_HPP

#include <memory>

#include "ram.hpp"
#include "cpu.hpp"

namespace emulator {
    class Emulator {
    public:
        Emulator();
    private:
        std::unique_ptr<Cpu> m_cpu;
        std::shared_ptr<Ram> m_ram;
    };
}

#endif //CHIP_8_EMU_CPP_EMULATOR_HPP

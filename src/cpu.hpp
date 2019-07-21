#ifndef CHIP_8_EMU_CPP_CPU_HPP
#define CHIP_8_EMU_CPP_CPU_HPP

#include <cstdint>
#include <array>
#include <memory>

#include "ram.hpp"

namespace emulator {
    class Cpu {
    public:
        explicit Cpu(const std::shared_ptr<Ram>& ram);
    private:
        static constexpr int STACK_DEPTH = 16;
        static constexpr int GP_REGISTERS_QTY = 16;
        std::array<uint16_t, STACK_DEPTH> m_stack;
        std::array<uint8_t, GP_REGISTERS_QTY> m_reg_v;
        uint16_t m_reg_i;
        uint16_t m_reg_vf;
        uint16_t m_reg_pc;
        uint16_t m_reg_sp;
        const std::shared_ptr<Ram>& m_ram;
    };
}

#endif //CHIP_8_EMU_CPP_CPU_HPP

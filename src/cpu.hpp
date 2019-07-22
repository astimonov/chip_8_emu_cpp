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
        void SetRegPC(uint16_t pc);
        void Reset();
        void RunInstruction();
    private:
        void Decode(uint16_t opcode);
        static constexpr int STACK_DEPTH = 16;
        static constexpr uint16_t STACK_RESET_VALUE = 0x0000;
        static constexpr int GP_REGISTERS_QTY = 16;
        static constexpr uint8_t GP_REGISTER_RESET_VALUE = 0x00;
        static constexpr uint8_t AUX_REGISTER_RESET_VALUE = 0x00;
        std::array<uint16_t, STACK_DEPTH> m_stack;
        std::array<uint8_t, GP_REGISTERS_QTY> m_reg_v;
        uint16_t m_reg_i;
        uint16_t m_reg_pc;
        uint16_t m_reg_sp;
        const std::shared_ptr<Ram>& m_ram;
    };
}

#endif //CHIP_8_EMU_CPP_CPU_HPP

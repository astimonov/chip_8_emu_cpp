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

        void Instruction00E0(uint16_t opcode);
        void Instruction00EE(uint16_t opcode);
        void Instruction1NNN(uint16_t opcode);
        void Instruction2NNN(uint16_t opcode);
        void Instruction3XNN(uint16_t opcode);
        void Instruction4XNN(uint16_t opcode);
        void Instruction5XY0(uint16_t opcode);
        void Instruction6XNN(uint16_t opcode);
        void Instruction7XNN(uint16_t opcode);
        void Instruction8XY0(uint16_t opcode);
        void Instruction8XY1(uint16_t opcode);
        void Instruction8XY2(uint16_t opcode);
        void Instruction8XY3(uint16_t opcode);
        void Instruction8XY4(uint16_t opcode);
        void Instruction8XY5(uint16_t opcode);
        void Instruction8XY6(uint16_t opcode);
        void Instruction8XY7(uint16_t opcode);
        void Instruction8XYE(uint16_t opcode);
        void Instruction9XY0(uint16_t opcode);
        void InstructionANNN(uint16_t opcode);
        void InstructionBNNN(uint16_t opcode);
        void InstructionCXNN(uint16_t opcode);
        void InstructionDXYN(uint16_t opcode);
        void InstructionEX9E(uint16_t opcode);
        void InstructionEXA1(uint16_t opcode);
        void InstructionFX07(uint16_t opcode);
        void InstructionFX0A(uint16_t opcode);
        void InstructionFX15(uint16_t opcode);
        void InstructionFX18(uint16_t opcode);
        void InstructionFX1E(uint16_t opcode);
        void InstructionFX29(uint16_t opcode);
        void InstructionFX33(uint16_t opcode);
    };
}

#endif //CHIP_8_EMU_CPP_CPU_HPP

#ifndef CHIP_8_EMU_CPP_CPU_HPP
#define CHIP_8_EMU_CPP_CPU_HPP

#include <cstdint>
#include <array>
#include <stack>
#include <memory>
#include <random>

#include "ram.hpp"
#include "timer.hpp"
#include "interface_graphics.hpp"
#include "interface_input.hpp"

namespace emulator {
    class Cpu {
    public:
        explicit Cpu(const std::shared_ptr<Ram> &ram,
                     std::shared_ptr<Timer> delay_timer,
                     std::shared_ptr<Timer> sound_timer,
                     std::shared_ptr<IGraphics> graphics,
                     std::shared_ptr<IInput> input);
        void SetRegPC(uint16_t pc);
        void Reset();
        void RunInstruction();
    private:
        void Decode(uint16_t opcode);
        static constexpr int STACK_DEPTH = 16;
        static constexpr int GP_REGISTERS_QTY = 16;
        static constexpr uint8_t GP_REGISTER_RESET_VALUE = 0x00;
        static constexpr uint8_t AUX_REGISTER_RESET_VALUE = 0x00;
        static constexpr uint16_t PC_ADVANCE_STEP = 2;
        static constexpr uint16_t FONTSET_BA = 0x0000;
        static constexpr uint16_t FONTSET_SPRITE_SIZE = 0x5;
        std::array<uint8_t, GP_REGISTERS_QTY> m_reg_v;
        std::stack<uint16_t> m_stack;
        uint16_t m_reg_i;
        uint16_t m_reg_pc;
        std::mt19937 m_random_generator;
        std::uniform_int_distribution<uint8_t> m_uniform_distribution;

        const std::shared_ptr<Ram>& m_ram;
        std::shared_ptr<Timer> m_delay_timer;
        std::shared_ptr<Timer> m_sound_timer;
        std::shared_ptr<IGraphics> m_graphics;
        std::shared_ptr<IInput> m_input;

        void Instruction0NNN(uint16_t opcode);
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
        void InstructionFX55(uint16_t opcode);
        void InstructionFX65(uint16_t opcode);

        void AdvancePC(uint16_t addressToAdvance = PC_ADVANCE_STEP);
        uint16_t GetRegPC();
        void StackPush(uint16_t value);
        uint16_t StackPop();
        void SetRegV(int index, uint8_t value);
        uint8_t GetRegV(int index);
        void SetRegI(uint16_t value);
        uint16_t GetRegI();
        void SetFlag(bool value);

        static constexpr uint8_t ExtractX(uint32_t value) {
            return ((value & 0x0F00) >> 8);
        }
        static constexpr uint8_t ExtractY(uint32_t value) {
            return ((value & 0x00F0) >> 4);
        }
        static constexpr uint8_t ExtractN(uint32_t value) {
            return (value & 0x000F);
        }
        static constexpr uint8_t ExtractNN(uint32_t value) {
            return (value & 0x00FF);
        }
        static constexpr uint16_t ExtractNNN(uint32_t value) {
            return (value & 0x0FFF);
        }
    };
}

#endif //CHIP_8_EMU_CPP_CPU_HPP

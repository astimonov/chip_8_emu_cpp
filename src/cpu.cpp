#include <map>
#include <functional>

#include "cpu.hpp"
#include "exceptions.hpp"

using namespace emulator;

Cpu::Cpu(const std::shared_ptr<Ram>& ram) : m_ram(ram) {

}

void Cpu::SetRegPC(uint16_t pc) {
    this->m_reg_pc = pc;
}

void Cpu::Reset() {
    std::fill(this->m_reg_v.begin(), this->m_reg_v.end(), GP_REGISTER_RESET_VALUE);
    std::fill(this->m_stack.begin(), this->m_stack.end(), STACK_RESET_VALUE);
    this->m_reg_i = AUX_REGISTER_RESET_VALUE;
    this->m_reg_pc = AUX_REGISTER_RESET_VALUE;
    this->m_reg_sp = AUX_REGISTER_RESET_VALUE;
}

void Cpu::RunInstruction() {
    this->Decode(this->m_ram->Read16(this->m_reg_pc));
}

void Cpu::Decode(uint16_t opcode) {
    std::map<uint16_t, const std::function<void(uint16_t)>> opcode_handlers = {
        { 0x0000, [this] (uint16_t opcode) { this->Instruction0NNN(opcode); } },
        { 0x00E0, [this] (uint16_t opcode) { this->Instruction00E0(opcode); } },
        { 0x00EE, [this] (uint16_t opcode) { this->Instruction00EE(opcode); } },
        { 0x1000, [this] (uint16_t opcode) { this->Instruction1NNN(opcode); } },
        { 0x2000, [this] (uint16_t opcode) { this->Instruction2NNN(opcode); } },
        { 0x3000, [this] (uint16_t opcode) { this->Instruction3XNN(opcode); } },
        { 0x4000, [this] (uint16_t opcode) { this->Instruction4XNN(opcode); } },
        { 0x5000, [this] (uint16_t opcode) { this->Instruction5XY0(opcode); } },
        { 0x6000, [this] (uint16_t opcode) { this->Instruction6XNN(opcode); } },
        { 0x7000, [this] (uint16_t opcode) { this->Instruction7XNN(opcode); } },
        { 0x8000, [this] (uint16_t opcode) { this->Instruction8XY0(opcode); } },
        { 0x8001, [this] (uint16_t opcode) { this->Instruction8XY1(opcode); } },
        { 0x8002, [this] (uint16_t opcode) { this->Instruction8XY2(opcode); } },
        { 0x8003, [this] (uint16_t opcode) { this->Instruction8XY3(opcode); } },
        { 0x8004, [this] (uint16_t opcode) { this->Instruction8XY4(opcode); } },
        { 0x8005, [this] (uint16_t opcode) { this->Instruction8XY5(opcode); } },
        { 0x8006, [this] (uint16_t opcode) { this->Instruction8XY6(opcode); } },
        { 0x8007, [this] (uint16_t opcode) { this->Instruction8XY7(opcode); } },
        { 0x800E, [this] (uint16_t opcode) { this->Instruction8XYE(opcode); } },
        { 0x9000, [this] (uint16_t opcode) { this->Instruction9XY0(opcode); } },
        { 0xA000, [this] (uint16_t opcode) { this->InstructionANNN(opcode); } },
        { 0xB000, [this] (uint16_t opcode) { this->InstructionBNNN(opcode); } },
        { 0xC000, [this] (uint16_t opcode) { this->InstructionCXNN(opcode); } },
        { 0xD000, [this] (uint16_t opcode) { this->InstructionDXYN(opcode); } },
        { 0xE09E, [this] (uint16_t opcode) { this->InstructionEX9E(opcode); } },
        { 0xE0A1, [this] (uint16_t opcode) { this->InstructionEXA1(opcode); } },
        { 0xF007, [this] (uint16_t opcode) { this->InstructionFX07(opcode); } },
        { 0xF00A, [this] (uint16_t opcode) { this->InstructionFX0A(opcode); } },
        { 0xF015, [this] (uint16_t opcode) { this->InstructionFX15(opcode); } },
        { 0xF018, [this] (uint16_t opcode) { this->InstructionFX18(opcode); } },
        { 0xF01E, [this] (uint16_t opcode) { this->InstructionFX1E(opcode); } },
        { 0xF029, [this] (uint16_t opcode) { this->InstructionFX29(opcode); } },
        { 0xF033, [this] (uint16_t opcode) { this->InstructionFX33(opcode); } },
    };

    uint16_t opcode_xxxx = opcode;
    uint16_t opcode_x000 = opcode & 0xF000;
    uint16_t opcode_x00x = opcode & 0xF00F;
    uint16_t opcode_x0xx = opcode & 0xF0FF;

    auto handler_x0xx = opcode_handlers.find(opcode_x0xx);
    auto handler_x00x = opcode_handlers.find(opcode_x00x);
    auto handler_x000 = opcode_handlers.find(opcode_x000);
    auto handler_xxxx = opcode_handlers.find(opcode_xxxx);

    if (handler_x0xx != opcode_handlers.end()) {
        handler_x0xx->second(opcode);
    } else if (handler_x00x != opcode_handlers.end()) {
        handler_x00x->second(opcode);
    } else if (handler_x000 != opcode_handlers.end()) {
        handler_x000->second(opcode);
    } else if (handler_xxxx != opcode_handlers.end()) {
        handler_xxxx->second(opcode);
    } else {
        throw RuntimeException(this->m_reg_pc, opcode);
    }

    this->m_reg_pc += 2;
}

void Cpu::Instruction0NNN(uint16_t opcode) {

}

void Cpu::Instruction00E0(uint16_t opcode) {

}

void Cpu::Instruction00EE(uint16_t opcode) {

}

void Cpu::Instruction1NNN(uint16_t opcode) {

}

void Cpu::Instruction2NNN(uint16_t opcode) {

}

void Cpu::Instruction3XNN(uint16_t opcode) {

}

void Cpu::Instruction4XNN(uint16_t opcode) {

}

void Cpu::Instruction5XY0(uint16_t opcode) {

}

void Cpu::Instruction6XNN(uint16_t opcode) {

}

void Cpu::Instruction7XNN(uint16_t opcode) {

}

void Cpu::Instruction8XY0(uint16_t opcode) {

}

void Cpu::Instruction8XY1(uint16_t opcode) {

}

void Cpu::Instruction8XY2(uint16_t opcode) {

}

void Cpu::Instruction8XY3(uint16_t opcode) {

}

void Cpu::Instruction8XY4(uint16_t opcode) {

}

void Cpu::Instruction8XY5(uint16_t opcode) {

}

void Cpu::Instruction8XY6(uint16_t opcode) {

}

void Cpu::Instruction8XY7(uint16_t opcode) {

}

void Cpu::Instruction8XYE(uint16_t opcode) {

}

void Cpu::Instruction9XY0(uint16_t opcode) {

}

void Cpu::InstructionANNN(uint16_t opcode) {

}

void Cpu::InstructionBNNN(uint16_t opcode) {

}

void Cpu::InstructionCXNN(uint16_t opcode) {

}

void Cpu::InstructionDXYN(uint16_t opcode) {

}

void Cpu::InstructionEX9E(uint16_t opcode) {

}

void Cpu::InstructionEXA1(uint16_t opcode) {

}

void Cpu::InstructionFX07(uint16_t opcode) {

}

void Cpu::InstructionFX0A(uint16_t opcode) {

}

void Cpu::InstructionFX15(uint16_t opcode) {

}

void Cpu::InstructionFX18(uint16_t opcode) {

}

void Cpu::InstructionFX1E(uint16_t opcode) {

}

void Cpu::InstructionFX29(uint16_t opcode) {

}

void Cpu::InstructionFX33(uint16_t opcode) {

}

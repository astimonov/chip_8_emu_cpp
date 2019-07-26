#include <map>
#include <functional>
#include <ctime>

#include "cpu.hpp"
#include "exceptions.hpp"

using namespace emulator;

Cpu::Cpu(const std::shared_ptr<Ram>& ram) : m_ram(ram) {
    this->m_random_generator.seed(time(0));
}

void Cpu::SetRegPC(uint16_t pc) {
    this->m_reg_pc = pc;
}

void Cpu::Reset() {
    std::fill(this->m_reg_v.begin(), this->m_reg_v.end(), GP_REGISTER_RESET_VALUE);
    this->m_reg_i = AUX_REGISTER_RESET_VALUE;
    this->m_reg_pc = AUX_REGISTER_RESET_VALUE;

    if (!this->m_stack.empty()) {
        this->m_stack = {};
    }
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
        { 0xF033, [this] (uint16_t opcode) { this->InstructionFX55(opcode); } },
        { 0xF033, [this] (uint16_t opcode) { this->InstructionFX65(opcode); } },
    };

    uint16_t opcode_xxxx = opcode;
    uint16_t opcode_x000 = opcode & 0xF000;
    uint16_t opcode_x00x = opcode & 0xF00F;
    uint16_t opcode_x0xx = opcode & 0xF0FF;

    auto handler = opcode_handlers.find(opcode_x0xx);

    if ((handler != opcode_handlers.end())
            || ((handler = opcode_handlers.find(opcode_x00x)) != opcode_handlers.end())
            || ((handler = opcode_handlers.find(opcode_x000)) != opcode_handlers.end())
            || ((handler = opcode_handlers.find(opcode_xxxx)) != opcode_handlers.end())) {
        handler->second(opcode);
    } else {
        throw IllegalInstruction(this->m_reg_pc, opcode);
    }
}

void Cpu::Instruction0NNN(uint16_t opcode) {
    // Unimplemented
    this->AdvancePC();
}

void Cpu::Instruction00E0(uint16_t opcode) {
    // Clear the screen
    this->AdvancePC();
}

void Cpu::Instruction00EE(uint16_t opcode) {
    this->SetRegPC(this->StackPop());
}

void Cpu::Instruction1NNN(uint16_t opcode) {
    uint16_t new_pc = Cpu::ExtractNNN(opcode);
    this->SetRegPC(new_pc);
}

void Cpu::Instruction2NNN(uint16_t opcode) {
    this->StackPush(this->GetRegPC());
    uint16_t new_pc = Cpu::ExtractNNN(opcode);
    this->SetRegPC(new_pc);
}

void Cpu::Instruction3XNN(uint16_t opcode) {
    uint16_t value = Cpu::ExtractNN(opcode);
    uint16_t regX = Cpu::ExtractX(opcode);
    if (value == this->GetRegV(regX)) {
        this->AdvancePC(4);
    } else {
        this->AdvancePC();
    }
}

void Cpu::Instruction4XNN(uint16_t opcode) {
    uint16_t value = Cpu::ExtractNN(opcode);
    uint16_t regX = Cpu::ExtractX(opcode);
    if (value != this->GetRegV(regX)) {
        this->AdvancePC(4);
    } else {
        this->AdvancePC();
    }
}

void Cpu::Instruction5XY0(uint16_t opcode) {
    uint16_t regX = Cpu::ExtractX(opcode);
    uint16_t regY = Cpu::ExtractY(opcode);
    if (this->GetRegV(regX) == this->GetRegV(regY)) {
        this->AdvancePC(4);
    } else {
        this->AdvancePC();
    }
}

void Cpu::Instruction6XNN(uint16_t opcode) {
    uint16_t value = Cpu::ExtractNN(opcode);
    uint16_t regX = Cpu::ExtractX(opcode);
    this->SetRegV(regX, value);
    this->AdvancePC();
}

void Cpu::Instruction7XNN(uint16_t opcode) {
    uint16_t value = Cpu::ExtractNN(opcode);
    uint16_t regX = Cpu::ExtractX(opcode);
    this->SetRegV(regX, this->GetRegV(regX) + value);
    this->AdvancePC();
}

void Cpu::Instruction8XY0(uint16_t opcode) {
    uint16_t regX = Cpu::ExtractX(opcode);
    uint16_t regY = Cpu::ExtractY(opcode);
    this->SetRegV(regX, this->GetRegV(regY));
    this->AdvancePC();
}

void Cpu::Instruction8XY1(uint16_t opcode) {
    uint16_t regX = Cpu::ExtractX(opcode);
    uint16_t regY = Cpu::ExtractY(opcode);
    this->SetRegV(regX, this->GetRegV(regX) | this->GetRegV(regY));
    this->AdvancePC();
}

void Cpu::Instruction8XY2(uint16_t opcode) {
    uint16_t regX = Cpu::ExtractX(opcode);
    uint16_t regY = Cpu::ExtractY(opcode);
    this->SetRegV(regX, this->GetRegV(regX) & this->GetRegV(regY));
    this->AdvancePC();
}

void Cpu::Instruction8XY3(uint16_t opcode) {
    uint16_t regX = Cpu::ExtractX(opcode);
    uint16_t regY = Cpu::ExtractY(opcode);
    this->SetRegV(regX, this->GetRegV(regX) ^ this->GetRegV(regY));
    this->AdvancePC();
}

void Cpu::Instruction8XY4(uint16_t opcode) {
    uint16_t regX = Cpu::ExtractX(opcode);
    uint16_t regY = Cpu::ExtractY(opcode);
    this->SetRegV(regX, this->GetRegV(regX) + this->GetRegV(regY));
    this->SetFlag(this->GetRegV(regX) < this->GetRegV(regY));
    this->AdvancePC();
}

void Cpu::Instruction8XY5(uint16_t opcode) {
    uint16_t regX = Cpu::ExtractX(opcode);
    uint16_t regY = Cpu::ExtractY(opcode);
    this->SetFlag(this->GetRegV(regY) > this->GetRegV(regX));
    this->SetRegV(regX, this->GetRegV(regX) - this->GetRegV(regY));
    this->AdvancePC();
}

void Cpu::Instruction8XY6(uint16_t opcode) {
    uint16_t regX = Cpu::ExtractX(opcode);
    this->SetFlag(this->GetRegV(regX) & 0x0001);
    this->SetRegV(regX, this->GetRegV(regX) >> 1);
    this->AdvancePC();
}

void Cpu::Instruction8XY7(uint16_t opcode) {
    uint16_t regX = Cpu::ExtractX(opcode);
    uint16_t regY = Cpu::ExtractY(opcode);
    this->SetFlag(this->GetRegV(regX) > this->GetRegV(regY));
    this->SetRegV(regX, this->GetRegV(regY) - this->GetRegV(regX));
    this->AdvancePC();
}

void Cpu::Instruction8XYE(uint16_t opcode) {
    uint16_t regX = Cpu::ExtractX(opcode);
    this->SetFlag(this->GetRegV(regX) & 0x8000);
    this->SetRegV(regX, this->GetRegV(regX) << 1);
    this->AdvancePC();
}

void Cpu::Instruction9XY0(uint16_t opcode) {
    uint16_t regX = Cpu::ExtractX(opcode);
    uint16_t regY = Cpu::ExtractY(opcode);
    if (this->GetRegV(regX) != this->GetRegV(regY)) {
        this->AdvancePC(4);
    } else {
        this->AdvancePC();
    }
}

void Cpu::InstructionANNN(uint16_t opcode) {
    uint16_t value = Cpu::ExtractNNN(opcode);
    this->SetRegI(value);
    this->AdvancePC();
}

void Cpu::InstructionBNNN(uint16_t opcode) {
    uint16_t value = Cpu::ExtractNNN(opcode);
    this->SetRegPC(this->GetRegV(0) + value);
}

void Cpu::InstructionCXNN(uint16_t opcode) {
    uint16_t regX = Cpu::ExtractX(opcode);
    uint16_t value = Cpu::ExtractNN(opcode);
    uint8_t random_number = this->m_uniform_distribution(this->m_random_generator);
    this->SetRegV(regX, value & random_number);
    this->AdvancePC();
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
    uint16_t regX = Cpu::ExtractX(opcode);
    uint16_t new_value = this->GetRegI() + this->GetRegV((regX));
    this->SetRegI(new_value & 0xFFF);
    this->SetFlag(new_value > 0xFFF);
    this->AdvancePC();
}

void Cpu::InstructionFX29(uint16_t opcode) {

}

void Cpu::InstructionFX33(uint16_t opcode) {
    uint16_t regX = Cpu::ExtractX(opcode);
    uint16_t address = this->GetRegI();
    uint16_t value = this->GetRegV(regX);
    this->m_ram->Write8(address + 0, (value % 1000) / 100);
    this->m_ram->Write8(address + 1, (value % 100) / 10);
    this->m_ram->Write8(address + 2, (value % 10) / 1);
    this->AdvancePC();
}

void Cpu::InstructionFX55(uint16_t opcode) {
    uint16_t regX = Cpu::ExtractX(opcode);
    uint16_t start_address = this->GetRegI();

    for (uint32_t reg_index = 0; reg_index <= regX; reg_index++) {
        this->m_ram->Write8(start_address + reg_index, this->GetRegV(reg_index));
    }
    this->AdvancePC();
}

void Cpu::InstructionFX65(uint16_t opcode) {
    uint16_t regX = Cpu::ExtractX(opcode);
    uint16_t start_address = this->GetRegI();

    for (uint32_t reg_index = 0; reg_index <= regX; reg_index++) {
        this->SetRegV(reg_index, this->m_ram->Read8(start_address + reg_index));
    }

    this->AdvancePC();
}

void Cpu::AdvancePC(uint16_t addressToAdvance) {
    this->m_reg_pc += addressToAdvance;
}

uint16_t Cpu::GetRegPC() {
    return this->m_reg_pc;
}

void Cpu::StackPush(uint16_t value) {
    if (this->m_stack.size() >= this->STACK_DEPTH) {
        throw StackOverflow(this->GetRegPC());
    }

    this->m_stack.push(value);
}

uint16_t Cpu::StackPop() {
    if (this->m_stack.empty()) {
        throw StackUnderflow(this->GetRegPC());
    }

    uint16_t stackTop = this->m_stack.top();
    this->m_stack.pop();

    return stackTop;
}

void Cpu::SetRegV(int index, uint8_t value) {
    if (index < 0 || index >= GP_REGISTERS_QTY) {
        throw IllegalInstruction(
                this->GetRegPC(), this->m_ram->Read16(this->GetRegPC()));
    }

    this->m_reg_v[index] = value;
}

uint8_t Cpu::GetRegV(int index) {
    if (index < 0 || index >= GP_REGISTERS_QTY) {
        throw IllegalInstruction(
                this->GetRegPC(), this->m_ram->Read16(this->GetRegPC()));
    }

    return this->m_reg_v[index];
}

void Cpu::SetRegI(uint16_t value) {
    this->m_reg_i = value;
}

uint16_t Cpu::GetRegI() {
    return this->m_reg_i;
}

void Cpu::SetFlag(bool value) {
    this->SetRegV(0xF, value);
}

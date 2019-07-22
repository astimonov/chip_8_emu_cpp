#include "exceptions.hpp"

emulator::RuntimeException::RuntimeException(uint16_t pc, uint16_t opcode) :
    m_pc(pc), m_opcode(opcode)
{
    this->m_message = "Emulator runtime error";
}

const char *emulator::RuntimeException::what() const noexcept {
    return this->m_message;
}

uint16_t emulator::RuntimeException::GetPC() {
    return this->m_pc;
}

uint16_t emulator::RuntimeException::GetOpcode() {
    return this->m_opcode;
}

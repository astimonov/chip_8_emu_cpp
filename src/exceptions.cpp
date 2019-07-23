#include "exceptions.hpp"

emulator::RuntimeException::RuntimeException(uint16_t pc) :
    m_pc(pc) {
    this->m_message = "Emulator runtime error";
}

const char *emulator::RuntimeException::what() const noexcept {
    return this->m_message;
}

uint16_t emulator::RuntimeException::GetPC() {
    return this->m_pc;
}

emulator::IllegalInstruction::IllegalInstruction(uint16_t pc, uint16_t opcode)
    : RuntimeException(pc), m_opcode(opcode)  {
    this->m_message = "Illegal instruction";
}

uint16_t emulator::IllegalInstruction::GetOpcode() {
    return this->m_opcode;
}

emulator::StoreAccessFailed::StoreAccessFailed(uint16_t pc, uint16_t address)
    : RuntimeException(pc), m_address(address) {
    this->m_message = "Store access failed";
}

uint16_t emulator::StoreAccessFailed::GetAddress() {
    return this->m_address;
}

emulator::LoadAccessFailed::LoadAccessFailed(uint16_t pc, uint16_t address)
    : RuntimeException(pc), m_address(address) {
    this->m_message = "Load access failed";
}

uint16_t emulator::LoadAccessFailed::GetAddress() {
    return this->m_address;
}

emulator::StackOverflow::StackOverflow(uint16_t pc) : RuntimeException(pc) {

}

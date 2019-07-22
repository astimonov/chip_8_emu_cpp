#include "cpu.hpp"

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

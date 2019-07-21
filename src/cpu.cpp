#include "cpu.hpp"

using namespace emulator;

Cpu::Cpu(const std::shared_ptr<Ram>& ram) : m_ram(ram) {

}

void Cpu::SetRegPC(uint16_t pc) {
    this->m_reg_pc = pc;
}

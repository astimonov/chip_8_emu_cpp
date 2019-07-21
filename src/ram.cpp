#include "ram.hpp"

using namespace emulator;

Ram::Ram() {
    Reset();
}

void Ram::Reset() {
    std::fill(this->m_memory.begin(), this->m_memory.end(), RAM_RESET_VALUE);
}

uint8_t Ram::Read8(uint16_t address) {
    if (address >= RAM_SIZE_BYTES) {
        throw std::out_of_range("Too high address");
    }

    return this->m_memory[address];
}

void Ram::Write8(uint16_t address, uint8_t value) {
    if (address >= RAM_SIZE_BYTES) {
        throw std::out_of_range("Too high address");
    }

    this->m_memory[address] = value;
}

uint16_t Ram::Read16(uint16_t address) {
    if (address >= RAM_SIZE_BYTES - 1) {
        throw std::out_of_range("Too high address");
    }

    return this->m_memory[address] << 8 | this->m_memory[address + 1];
}

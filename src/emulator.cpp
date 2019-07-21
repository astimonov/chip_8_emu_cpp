#include "emulator.hpp"

using namespace emulator;

Emulator::Emulator() {
    this->m_ram = std::make_shared<Ram>();
    this->m_cpu = std::make_unique<Cpu>(this->m_ram);
}

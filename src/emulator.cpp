#include "emulator.hpp"
#include "rom.hpp"

using namespace emulator;

Emulator::Emulator(Rom rom) : m_rom(rom) {
    this->m_ram = std::make_shared<Ram>();
    this->m_cpu = std::make_unique<Cpu>(this->m_ram);
    this->m_ram->WriteMultiple(this->m_rom.GetData(), Emulator::PC_START);
    this->m_cpu->Reset();
    this->m_cpu->SetRegPC(PC_START);
}

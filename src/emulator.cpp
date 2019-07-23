#include <thread>
#include <chrono>

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

void Emulator::Run() {
    while (true) {
        this->m_cpu->RunInstruction();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

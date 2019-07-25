#include <thread>
#include <chrono>

#include "emulator.hpp"

using namespace emulator;

Emulator::Emulator(std::shared_ptr<IRom> rom,
                   std::shared_ptr<IGraphics> graphics,
                   std::shared_ptr<ISound> sound,
                   std::shared_ptr<IInput> input)
                        : m_rom(rom), m_graphics(graphics), m_sound(sound), m_input(input) {
    this->m_ram = std::make_shared<Ram>();
    this->m_cpu = std::make_unique<Cpu>(this->m_ram);
    this->m_ram->WriteMultiple(this->m_rom->GetData(), Emulator::PC_START);
    this->m_cpu->Reset();
    this->m_cpu->SetRegPC(PC_START);
}

void Emulator::Run() {
    while (true) {
        this->m_cpu->RunInstruction();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

#include <thread>
#include <chrono>
#include <array>

#include "emulator.hpp"

using namespace emulator;

Emulator::Emulator(std::shared_ptr<IRom> rom,
                   std::shared_ptr<IGraphics> graphics,
                   std::shared_ptr<ISound> sound,
                   std::shared_ptr<IInput> input)
                        : m_rom(rom), m_graphics(graphics), m_sound(sound), m_input(input) {
    this->m_ram = std::make_shared<Ram>();
    this->m_cpu = std::make_unique<Cpu>(this->m_ram);
    this->m_ram->WriteMultiple(this->m_fontset.begin(), this->m_fontset.end(), Emulator::FONTSET_BA);
    this->m_ram->WriteMultiple(this->m_rom->GetData().begin(), this->m_rom->GetData().end(), Emulator::PC_START);
    this->m_cpu->Reset();
    this->m_cpu->SetRegPC(PC_START);
}

void Emulator::Run() {
    while (true) {
        this->m_cpu->RunInstruction();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

const std::array<uint8_t, Emulator::FONTSET_SIZE> Emulator::m_fontset {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

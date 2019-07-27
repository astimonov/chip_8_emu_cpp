#include "timer.hpp"

emulator::Timer::Timer(uint32_t input_frequency, uint32_t timer_frequency) {
    this->m_divider = input_frequency / timer_frequency;
}

void emulator::Timer::Update() {
    this->m_counter++;
    if (this->m_counter >= m_divider) {
        this->m_counter = 0;
        this->DecreaseValue();
    }
}

void emulator::Timer::Reset() {
    this->SetValue(0);
}

void emulator::Timer::SetValue(uint8_t value) {
    this->m_value = value;
}

uint8_t emulator::Timer::GetValue() {
    return this->m_value;
}

void emulator::Timer::DecreaseValue() {
    if (this->GetValue() > 0) {
        this->SetValue(this->GetValue() - 1);
    }
}

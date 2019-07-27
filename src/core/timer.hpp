#ifndef CHIP_8_EMU_CPP_TIMER_HPP
#define CHIP_8_EMU_CPP_TIMER_HPP

#include <cstdint>

namespace emulator {
    class Timer {
    public:
        Timer(uint32_t input_frequency, uint32_t timer_frequency);
        void Update();
        void Reset();
        void SetValue(uint8_t value);
        uint8_t GetValue();
    private:
        void DecreaseValue();
        uint8_t m_value = 0;
        uint8_t m_divider;
        uint32_t m_counter;
    };
}

#endif //CHIP_8_EMU_CPP_TIMER_HPP

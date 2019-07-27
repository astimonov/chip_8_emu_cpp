#ifndef CHIP_8_EMU_CPP_EMULATOR_HPP
#define CHIP_8_EMU_CPP_EMULATOR_HPP

#include <memory>
#include <string>
#include <array>

#include "interface_graphics.hpp"
#include "interface_input.hpp"
#include "interface_rom.hpp"
#include "interface_sound.hpp"
#include "ram.hpp"
#include "cpu.hpp"

namespace emulator {
    class Emulator {
    public:
        explicit Emulator(std::shared_ptr<IRom> rom,
                          std::shared_ptr<IGraphics> graphics,
                          std::shared_ptr<ISound> sound,
                          std::shared_ptr<IInput> input);
        void Run();
    private:
        static constexpr uint16_t PC_START = 0x0200;
        static constexpr uint16_t FONTSET_BA = 0x0000;
        static constexpr uint16_t FONTSET_SIZE = 80;
        static constexpr uint16_t CPU_FREQUENCY = 840;
        static constexpr uint32_t DELAY_TIMER_FREQUENCY = 60;
        static constexpr uint32_t SOUND_TIMER_FREQUENCY = 60;
        std::unique_ptr<Cpu> m_cpu;
        std::shared_ptr<Ram> m_ram;
        std::shared_ptr<IRom> m_rom;
        std::shared_ptr<IGraphics> m_graphics;
        std::shared_ptr<ISound> m_sound;
        std::shared_ptr<IInput> m_input;
        std::shared_ptr<Timer> m_delay_timer;
        std::shared_ptr<Timer> m_sound_timer;
        static const std::array<uint8_t, FONTSET_SIZE> m_fontset;
    };
}

#endif //CHIP_8_EMU_CPP_EMULATOR_HPP

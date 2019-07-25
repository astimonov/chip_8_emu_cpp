#ifndef CHIP_8_EMU_CPP_RAM_HPP
#define CHIP_8_EMU_CPP_RAM_HPP

#include <cstdint>
#include <array>
#include <vector>

namespace emulator {
    class Ram {
    public:
        Ram();
        void Reset();
        uint8_t Read8(uint16_t address);
        void Write8(uint16_t address, uint8_t value);
        uint16_t Read16(uint16_t address);
        void WriteMultiple(std::vector<uint8_t>&& data, uint16_t address);
    private:
        static constexpr int RAM_SIZE_BYTES = 4096;
        static constexpr uint8_t RAM_RESET_VALUE = 0x00;
        std::array<uint8_t, RAM_SIZE_BYTES> m_memory;
    };
}

#endif //CHIP_8_EMU_CPP_RAM_HPP

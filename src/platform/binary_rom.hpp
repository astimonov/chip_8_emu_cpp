#ifndef CHIP_8_EMU_CPP_BINARY_ROM_HPP
#define CHIP_8_EMU_CPP_BINARY_ROM_HPP

#include <cstdint>
#include <array>
#include <vector>
#include <memory>
#include <string>

#include "../core/interface_rom.hpp"

namespace emulator {
    class BinaryRom : public IRom {
    public:
        explicit BinaryRom(std::string filename);
        std::vector<uint8_t> GetData();
    private:
        std::vector<uint8_t> m_data;
    };
}

#endif //CHIP_8_EMU_CPP_BINARY_ROM_HPP

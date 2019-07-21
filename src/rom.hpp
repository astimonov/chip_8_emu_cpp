#ifndef CHIP_8_EMU_CPP_ROM_HPP
#define CHIP_8_EMU_CPP_ROM_HPP

#include <cstdint>
#include <array>
#include <vector>
#include <memory>
#include <string>

namespace emulator {
    class Rom {
    public:
        explicit Rom(std::string filename);
        std::vector<uint8_t> GetData();
    private:
        std::vector<uint8_t> m_data;
    };
}

#endif //CHIP_8_EMU_CPP_ROM_HPP

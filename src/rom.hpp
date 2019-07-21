#ifndef CHIP_8_EMU_CPP_ROM_HPP
#define CHIP_8_EMU_CPP_ROM_HPP

#include <cstdint>
#include <array>
#include <memory>
#include <string>

namespace emulator {
    class Rom {
    public:
        explicit Rom(std::string filename);
    private:

    };
}

#endif //CHIP_8_EMU_CPP_ROM_HPP

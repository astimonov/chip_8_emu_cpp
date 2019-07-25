#ifndef CHIP_8_EMU_CPP_INTERFACE_ROM_HPP
#define CHIP_8_EMU_CPP_INTERFACE_ROM_HPP

#include <vector>

namespace emulator {
    class IRom {
    public:
        virtual std::vector<uint8_t> GetData() = 0;
        virtual ~IRom() = default;
    };
}

#endif //CHIP_8_EMU_CPP_INTERFACE_ROM_HPP

#include "rom.hpp"

using namespace emulator;

Rom::Rom(std::string filename) {
    // TODO: Read ROM from file or throw an exception
}

std::vector<uint8_t> Rom::GetData() {
    return this->m_data;
}

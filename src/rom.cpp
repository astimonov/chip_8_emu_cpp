#include <fstream>

#include "rom.hpp"

using namespace emulator;

Rom::Rom(std::string filename) {
    std::ifstream file(filename, std::ios::binary);
    file.unsetf(std::ios::skipws);

    file.seekg(0, std::ios::end);
    std::vector<uint8_t> rom_data;
    rom_data.reserve(file.tellg());
    file.seekg(0, std::ios::beg);

    rom_data.insert(rom_data.begin(),
            std::istreambuf_iterator<char>(file),
            std::istreambuf_iterator<char>());

    this->m_data = rom_data;
}

std::vector<uint8_t> Rom::GetData() {
    return this->m_data;
}

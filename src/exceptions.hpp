#ifndef CHIP_8_EMU_CPP_EXCEPTIONS_HPP
#define CHIP_8_EMU_CPP_EXCEPTIONS_HPP

#include <exception>
#include <cstdint>

namespace emulator {
    class RuntimeException : public std::exception {
    public:
        RuntimeException(uint16_t pc, uint16_t opcode);
        const char* what() const noexcept;
        uint16_t GetPC();
        uint16_t GetOpcode();
    private:
        const char * m_message;
        uint16_t m_pc;
        uint16_t m_opcode;
    };
}


#endif //CHIP_8_EMU_CPP_EXCEPTIONS_HPP

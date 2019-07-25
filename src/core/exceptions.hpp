#ifndef CHIP_8_EMU_CPP_EXCEPTIONS_HPP
#define CHIP_8_EMU_CPP_EXCEPTIONS_HPP

#include <exception>
#include <cstdint>

namespace emulator {
    class RuntimeException : public std::exception {
    public:
        RuntimeException(uint16_t pc);
        const char* what() const noexcept;
        uint16_t GetPC();
    private:
        uint16_t m_pc;
    protected:
        const char * m_message;
    };

    class IllegalInstruction : public RuntimeException {
    public:
        IllegalInstruction(uint16_t pc, uint16_t opcode);
        uint16_t GetOpcode();
    private:
        uint16_t m_opcode;
    };

    class StoreAccessFailed : public RuntimeException {
    public:
        StoreAccessFailed(uint16_t pc, uint16_t address);
        uint16_t GetAddress();
    private:
        uint16_t m_address;
    };

    class LoadAccessFailed : public RuntimeException {
    public:
        LoadAccessFailed(uint16_t pc, uint16_t address);
        uint16_t GetAddress();
    private:
        uint16_t m_address;
    };

    class StackOverflow : public RuntimeException {
    public:
        StackOverflow(uint16_t pc);
    private:
    };
    class StackUnderflow : public RuntimeException {
    public:
        StackUnderflow(uint16_t pc);
    private:
    };
}


#endif //CHIP_8_EMU_CPP_EXCEPTIONS_HPP

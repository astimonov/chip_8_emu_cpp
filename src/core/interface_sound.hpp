#ifndef CHIP_8_EMU_CPP_INTERFACE_SOUND_HPP
#define CHIP_8_EMU_CPP_INTERFACE_SOUND_HPP

namespace emulator {
    class ISound {
    public:
        virtual ~ISound() = default;
        virtual void PlaySound() = 0;
        virtual void PauseSound() = 0;
    };
}

#endif //CHIP_8_EMU_CPP_INTERFACE_SOUND_HPP

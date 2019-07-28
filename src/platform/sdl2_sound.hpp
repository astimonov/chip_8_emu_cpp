#ifndef CHIP_8_EMU_CPP_SDL2_SOUND_HPP
#define CHIP_8_EMU_CPP_SDL2_SOUND_HPP

#include "../core/interface_sound.hpp"

namespace emulator {
    class SDL2Sound : public ISound {
    public:
        SDL2Sound();
        ~SDL2Sound();
        void PlaySound();
        void PauseSound();
    private:
        static void SoundCallback (void *userdata, Uint8 *stream, int len);
        SDL_AudioDeviceID m_audio_device = 0;
    };
}

#endif //CHIP_8_EMU_CPP_SDL2_SOUND_HPP

#include <math.h>
#include <algorithm>

#include <SDL.h>

#include "sdl2_sound.hpp"

using namespace emulator;

void SDL2Sound::SoundCallback(void *userdata, Uint8 *stream, int len) {
    static uint32_t counter;

    double pi = 3.1415;
    double Hz = 200;
    double A = 100;
    double SR = 48000;
    double F = 2 * pi * Hz / SR;

    for (int i = 0; i < len; i++) {
        counter++;
        stream[i] = (Uint8) A * sin(F * (double) counter);
    }
}

SDL2Sound::SDL2Sound() {
    SDL_setenv("SDL_AUDIODRIVER", "directsound", true);

    SDL_AudioSpec want, have;

    SDL_memset(&want, 0, sizeof(want));
    want.freq = 48000;
    want.format = AUDIO_U8;
    want.channels = 2;
    want.samples = 4096;
    want.callback = SoundCallback;
    want.callback = &SDL2Sound::SoundCallback;

    this->m_audio_device = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
    if (this->m_audio_device == 0) {
        SDL_Log("Failed to open audio: %s", SDL_GetError());
    } else {
        if (have.format != want.format) { /* we let this one thing change. */
            SDL_Log("We didn't get Float32 audio format.");
        }
    }
}

SDL2Sound::~SDL2Sound() {
    SDL_CloseAudioDevice(this->m_audio_device);
}

void SDL2Sound::PlaySound() {
    SDL_PauseAudioDevice(this->m_audio_device, 0);
}

void SDL2Sound::PauseSound() {
    SDL_PauseAudioDevice(this->m_audio_device, 1);
}

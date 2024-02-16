
#include "audio.h"

void audio_callback(void* data, uint8_t* stream, int len){
    int16_t* buffer = (int16_t*)stream;

    int sample_count = len / sizeof(int16_t);

    for (int i = 0; i < sample_count; ++i){
        
        double t = (double)i / 44100;
        double value = 28000 * sin(6.28318 * SOUND_FREQUENCY * t);
        buffer[i] = (int16_t)value;

    }

}

SDL_AudioDeviceID init_emu_soundfrequency(){
    
    SDL_AudioSpec desired, obtained;

    desired.freq = 44100;
    desired.format = AUDIO_S16SYS;
    desired.channels = 1;
    desired.samples = 2048;
    desired.callback = audio_callback;

    SDL_AudioDeviceID device = SDL_OpenAudioDevice(NULL, 0, &desired, &obtained, 0);

    return device; // on error this will return 0

}

#ifndef AUDIO_H
#define AUDIO_H

#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include <SDL2/SDL.h>

#define SOUND_FREQUENCY 1200.0

// Will possibly add more sound stuff if i feel like extending the c8 instructionset

SDL_AudioDeviceID init_emu_soundfrequency();

#endif

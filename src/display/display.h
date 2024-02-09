#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "gfxs.h"

struct Display {
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    bool running;
    int width;
    int height;

};

uint16_t get_keypresses(struct Display* display);

struct Display* initialize_display(int width, int height);
void deinit_display(struct Display* display);

#endif

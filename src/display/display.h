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

    int upscale;

    bool executeDraw;
};

void display_draw_bit(struct Display* display, int emuX, int emuY);
bool get_keypresses(uint16_t* keybits);

struct Display* initialize_display(int width, int height);
void deinit_display(struct Display* display);

#endif

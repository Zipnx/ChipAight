#ifndef DISPLAY_H
#define DISPLAY_H

#define DISPLAY_FPS_MS 16

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

    int currentFrameTimeMs;

};

void display_draw_bit(struct Display* display, int emuX, int emuY);
uint16_t get_keypresses(struct Display* display);

struct Display* initialize_display(int width, int height);
void deinit_display(struct Display* display);

#endif

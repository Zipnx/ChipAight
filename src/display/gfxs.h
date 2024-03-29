#ifndef GFXS_H
#define GFXS_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

SDL_Window* create_window(char* title, int width, int height);

void draw_square(SDL_Renderer* renderer, int x, int y, int dim);
bool init_sdl2();
void clean_sdl2();

#endif

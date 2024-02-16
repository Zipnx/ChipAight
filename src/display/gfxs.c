
#include "gfxs.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

SDL_Window* create_window(char* title, int width, int height){

    SDL_Window* wnd = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   width, height, SDL_WINDOW_SHOWN);

    if (wnd == NULL){
        fprintf(stderr, "[!] Error creating window!\n");
        return NULL;
    }

    return wnd;

}

void draw_square(SDL_Renderer *renderer, int x, int y, int dim){

    SDL_Rect tmp = {x, y, dim, dim};

    SDL_RenderFillRect(renderer, &tmp);

    return;

}

bool init_sdl2(){

    return (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER) >= 0);

}

void clean_sdl2(){
    // Gonna add more stuff when the display is actuall fully fledged
    SDL_Quit();
}

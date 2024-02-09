
#include "gfxs.h"
#include <SDL2/SDL_events.h>
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

bool init_sdl2(){

    return (SDL_Init(SDL_INIT_EVERYTHING) >= 0);

}

void clean_sdl2(){
    // Gonna add more stuff when the display is actuall fully fledged
    SDL_Quit();
}

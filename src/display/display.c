
#include "display.h"
#include "gfxs.h"


// As specified in the reference 1-16
char key_mappings[16] = {
    'x', '1', '2', '3',
    'q', 'w', 'e', 'a',
    's', 'd', 'z', 'c',
    '4', 'r', 'f', 'v'
};

void display_draw_bit(struct Display *display, int emuX, int emuY){
    // emuX and emuY dont represent direct pixels on the screen, but the ones after an upscale

    draw_square(display->renderer, emuX * display->upscale, emuY * display->upscale, display->upscale);
    

}

uint16_t get_keypresses(struct Display* display){

    SDL_Event e;
    uint16_t keybits = 0;

    while (SDL_PollEvent(&e) != 0){
        
        if (e.type == SDL_QUIT) {
            display->running = false;
            continue;
        }
        
        if (e.type != SDL_KEYDOWN) continue;

        // Yes, this is very inefficient, idc
        for (int i = 0; i < 16; i++){
            
            if (e.key.keysym.sym == key_mappings[i]){

                keybits |= (0x1 << i);

            }

        }


    }

    return keybits;

}

struct Display* initialize_display(int width, int height){

    struct Display* dis = (struct Display*)malloc(sizeof (struct Display));

    if (dis == NULL){
        fprintf(stderr, "[!] Error allocating memory for display\n");
        return NULL;
    }
    
    dis->running = true;
    dis->width = width;
    dis->height = height;

    dis->upscale = 8;

    dis->executeDraw = false;

    dis->window = create_window("Chip Aight", width, height);

    if (dis->window == NULL){
        fprintf(stderr, "[!] Unable to create window\n");
        free(dis);
        return NULL;

    }

    dis->renderer = SDL_CreateRenderer(dis->window, -1, SDL_RENDERER_ACCELERATED);

    if (dis->renderer == NULL){
        fprintf(stderr, "[!] Unable to create SDL_Renderer\n");
        return NULL;
    }

    return dis;

}

void deinit_display(struct Display* display){

    SDL_DestroyRenderer(display->renderer);
    SDL_DestroyWindow(display->window);

}

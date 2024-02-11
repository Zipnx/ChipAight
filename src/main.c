
#include "emu/cpu.h"
#include "emu/memory.h"
#include "display/display.h"

#include "utils/fileutil.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>

int main(int argc, char** argv){

    char* rom;

    if (argc > 1){
        rom = argv[1];
    } else {
        rom = "./tests/test_arithm_carries.ch8";
    }

    struct Display* display = initialize_display(512, 256);
    
    if (display == NULL){
        fprintf(stderr, "[!] Error initializing display\n");
        return 1;
    }

    struct CPU* cpu = init_cpu(display);

    if (cpu == NULL) return 1;

    load_file(rom, (char*)cpu->memory, 0x200);
   

    if (!init_sdl2()){
        fprintf(stderr, "[!] Error initializing SDL2\n");
        return 1;
    }

    printf("[+] SDL2 Initialized\n");
    

    while (display->running) {
        
        cpu->pressed_keys = get_keypresses(display);
        printf("Pressed keys: 0x%04x\n", cpu->pressed_keys); 
        if (!cpu_cycle(cpu)) break;
        
        if (!cpu_display_refresh(cpu)) break;
        
        hexdump_memory(cpu->memory+0xf00, 256);

        SDL_Delay(200);
    }

    deinit_display(display);
    clean_sdl2();

    return 0;
}

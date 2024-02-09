
#include "emu/cpu.h"
#include "emu/memory.h"
#include "display/display.h"

#include "utils/fileutil.h"
#include <stdio.h>

int main(int argc, char** argv){

    char* rom;

    if (argc > 1){
        rom = argv[1];
    } else {
        rom = "./tests/test_arithm_carries.ch8";
    }

    struct CPU* cpu = init_cpu();

    if (cpu == NULL) return 1;

    load_file(rom, (char*)cpu->memory, 0x200);

    if (!init_sdl2()){
        fprintf(stderr, "[!] Error initializing SDL2\n");
        return 1;
    }

    printf("[+] SDL2 Initialized\n");
    
    struct Display* display = initialize_display(640, 480);

    while (display->running) {

        printf("%04x\n", get_keypresses(display));
        SDL_Delay(15);

    }

    deinit_display(display);
    clean_sdl2();

    return 0;
}

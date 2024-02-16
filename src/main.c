
#include "emu/cpu.h"
#include "emu/memory.h"
#include "display/display.h"

#include "utils/fileutil.h"
#include "utils/cmdlineargs.h"

int main(int argc, char** argv){
    
    struct CmdParams* params = parse_args(argc, argv);

    if (params == NULL) return 1;

    struct Display* display = initialize_display(params->windowWidth, params->windowHeight);
    
    if (display == NULL){
        fprintf(stderr, "[!] Error initializing display\n");
        return 1;
    }

    struct CPU* cpu = init_cpu(display);

    if (cpu == NULL) return 1;

    load_file(params->rompath, (char*)cpu->memory, 0x200);
   

    if (!init_sdl2()){
        fprintf(stderr, "[!] Error initializing SDL2\n");
        return 1;
    }

    printf("[+] SDL2 Initialized\n");
    
    
    int t0;
    int elapsedMs = 0;

    while (display->running) {
        
        t0 = SDL_GetTicks();

        if (!get_keypresses(&cpu->pressed_keys)){
            display->running = false;
        }

        if (!cpu_cycle(cpu)) break;
        
        elapsedMs += SDL_GetTicks() - t0;

        if (elapsedMs > 16){
            
            // Finally tick down at 60fps
            cpu->delay_timer--;
            cpu->sound_timer--;

            elapsedMs = 0;
        }
        
        if (cpu->sound_timer > 0){
            sound_start(display);
        } else {
            sound_stop(display);
        }

        if (!cpu_display_refresh(cpu)) break;

    }

    deinit_display(display);
    clean_sdl2();
    
    deinit_cpu(cpu);

    return 0;
}

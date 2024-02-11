
#include "cpu.h"
#include "memory.h"
#include "opcodes.h"

char default_font[FONTS_SIZE] = {
    // 0
    0xF0, 0x90, 0x90, 0x90, 0xF0,
    // 1
    0x20, 0x60, 0x20, 0x20, 0x70,
    // 2
    0xF0, 0x10, 0xF0, 0x80, 0xF0,
    // 3
    0xF0, 0x10, 0xF0, 0x10, 0xF0,
    // 4
    0x90, 0x90, 0xF0, 0x10, 0x10,
    // 5
    0xF0, 0x80, 0xf0, 0x10, 0xf0,
    // 6 
    0xf0, 0x80, 0xf0, 0x90, 0xf0,
    // 7 
    0xf0, 0x10, 0x20, 0x40, 0x40,
    // 8 
    0xf0, 0x90, 0xf0, 0x90, 0xf0,
    // 9 
    0xf0, 0x90, 0xf0, 0x10, 0xf0,
    // A
    0xf0, 0x90, 0xf0, 0x90, 0x90,
    // B 
    0xe0, 0x90, 0xe0, 0x90, 0xe0,
    // C 
    0xf0, 0x80, 0x80, 0x80, 0xf0,
    // D
    0xe0, 0x90, 0x90, 0x90, 0xe0,
    // E 
    0xf0, 0x80, 0xf0, 0x80, 0xf0,
    // F 
    0xf0, 0x80, 0xf0, 0x80, 0x80

};

int cpu_display_refresh(struct CPU* cpu){
    
    if (cpu->display->currentFrameTimeMs++ > DISPLAY_FPS_MS){
        cpu->display->currentFrameTimeMs = 0;
         
        SDL_SetRenderDrawColor(cpu->display->renderer, 255, 255, 255, 255); 
        
        char displayByte;
        int curX, curY;

        for (int i = 0xF00, j = 0; i < 0x1000; i++, j++){

            curY = j / 8;
            curX = j % 8;

            displayByte = cpu->memory[i];

            for (int mask = 0x80; mask >= 1; mask >>= 1){
                if ( (displayByte & mask) != 0 ){
                    display_draw_bit(cpu->display, curX++, curY);
                }

            }

        }
        

        printf("Frame presented\n");
        SDL_RenderPresent(cpu->display->renderer);

    } 

    return 1;
}

int cpu_cycle(struct CPU *cpu){

    uint16_t op = get_current_opcode(cpu); 

    if (cpu->pc > MEMORY_SIZE) {
        fprintf(stderr, "[!] PC Register exceeded memory\n");
    }

    printf("[*] Executing: 0x%04x\n", op);
    
    if (execute_opcode(cpu, op) != 1)
        return 0;

    
    // These are meant to tick down at 60hz, gonna fix that later
    cpu->delay_timer -= (cpu->delay_timer > 0) ? 1 : 0;
    cpu->sound_timer -= (cpu->sound_timer > 0) ? 1 : 0;

    return 1;
}


struct CPU* init_cpu(struct Display* targetDisplay){

    struct CPU* cpu = (struct CPU*)malloc(sizeof (struct CPU));

    if (cpu == NULL){

        fprintf(stderr, "[!] Error allocating memory for the CPU\n");
        return NULL;

    }

    cpu->memory = (uint8_t*)malloc(MEMORY_SIZE);

    if (cpu->memory == NULL){
        fprintf(stderr, "[!] Error allocating memory for cpu memory\n");
        free(cpu);
        return NULL;
    }
    
    memset(cpu->memory, 0, MEMORY_SIZE);
    memset(cpu->V, 0, 16); 
    
    cpu_memwrite(cpu, 0, (char*)&default_font, FONTS_SIZE);
    
    cpu->display = targetDisplay;

    /* Pressed keys will be stored bit-encoded from LSB to MSB */
    cpu->pressed_keys = 0x0000;

    cpu->pc = 0x200;
    cpu->sp = 0xF00;
    cpu->I = 0x0;

    cpu->delay_timer = 0;
    cpu->sound_timer = 0;

    return cpu;
}

void cpu_info_registers(struct CPU *cpu){
    // TODO: Make this prettier at some point
    
    printf("\n========== Registers ==========\n");
    
    printf("SP = 0x%04x\n", cpu->sp);
    printf("PC = 0x%04x\n", cpu->pc);
    printf("I  = 0x%04x\n", cpu->I);

    for (int i = 0; i < 16; i++){
        printf("V[%x] = 0x%02x\n", i, cpu->V[i]);
    }

    printf("delay_timer = 0x%04x\n", cpu->delay_timer);
    printf("sound_timer = 0x%04x\n", cpu->sound_timer);

}

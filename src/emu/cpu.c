
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

int cpu_cycle(struct CPU *cpu){

    uint16_t op = get_current_opcode(cpu); 

    // Should probably check if it reaches the stack region, but i think leaving it as a possibility is more fun
    // could also happen by manually adding data to the stack and calling ret, could set the pc to any 16 bit value

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


struct CPU* init_cpu(){

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

    memset(cpu->V, 0, 16); 
    
    cpu_memwrite(cpu, 0, (char*)&default_font, FONTS_SIZE);

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

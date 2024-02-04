
#include "cpu.h"
#include <string.h>

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

    cpu->pc = 0x200;
    cpu->sp = 0xF00;
    cpu->I = 0x0;

    cpu->delay_timer = 0;
    cpu->sound_timer = 0;

    return cpu;
}

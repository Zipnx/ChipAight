
#include "emu/cpu.h"
#include "emu/memory.h"

#include "utils/fileutil.h"
#include <stdio.h>

int main(int argc, char** argv){

    char* rom;

    if (argc > 1){
        rom = argv[1];
    } else {
        rom = "./tests/test.ch8";
    }

    struct CPU* cpu = init_cpu();

    if (cpu == NULL) return 1;

    load_file(rom, (char*)cpu->memory, 0x200);

    hexdump_memory(cpu->memory, 0x400);
    
    while (1){

        cpu_cycle(cpu);
        cpu_info_registers(cpu);

        hexdump_memory(cpu->memory+0x300, 8);

        getchar();

    }

    return 0;
}

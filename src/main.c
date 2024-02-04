
#include "emu/cpu.h"
#include "emu/memory.h"

#include "utils/fileutil.h"
#include <stdio.h>

int main(void){

    struct CPU* cpu = init_cpu();

    if (cpu == NULL) return 1;

    printf("CPU: %p\n", cpu);

    printf("Filesize: %ld\n", get_filesize("./tests/junk.dat"));

    load_file("./tests/coin_flipping.ch8", (char*)cpu->memory, 0x200);

    hexdump_memory(cpu->memory, 0x400);
    
    while (1){

        cpu_cycle(cpu);
        cpu_info_registers(cpu);

        getchar();

    }

    return 0;
}

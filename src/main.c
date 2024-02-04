
#include "emu/cpu.h"

int main(void){

    struct CPU* cpu = init_cpu();

    if (cpu == NULL) return 1;

    printf("CPU: %p\n", cpu);

    return 0;
}

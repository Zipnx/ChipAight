
#include "emu/cpu.h"
#include "emu/memory.h"

int main(void){

    struct CPU* cpu = init_cpu();

    if (cpu == NULL) return 1;

    printf("CPU: %p\n", cpu);

    write_uint16(cpu, 0x300, 0x6969);
    
    hexdump_memory(cpu->memory + 0x300, 16); 

    uint16_t res;
    read_uint16(cpu, 0x300, &res);

    printf("Value: %04x\n", res);
    
    stack_push(cpu, 0x1337);

    hexdump_memory(cpu->memory+0xEA0, 0x100);
   
    cpu_info_registers(cpu);

    stack_pop(cpu, &res);

    printf("Popped: %04x\n", res);

    return 0;
}

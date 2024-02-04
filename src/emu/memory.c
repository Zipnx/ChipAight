
#include "memory.h"
#include "cpu.h"

bool stack_push(struct CPU *cpu, uint16_t val){

    if (cpu->sp < 0xEA0 + 1){
        fprintf(stderr, "[!] Stack overflow SP=%04x\n", cpu->sp);
        return false;
    }

    cpu->sp -= 2;

    return write_uint16(cpu, cpu->sp, val);
}

bool stack_pop(struct CPU *cpu, uint16_t *dst){

    if (cpu->sp > 0xEFF - 1){
        fprintf(stderr, "[!] Stack underflow SP=%04x\n", cpu->sp);
        return false;

    }
    
    // gotta incr after reading
    read_uint16(cpu, cpu->sp, dst);
    cpu->sp += 2;

    return true;
}

bool read_uint16(struct CPU *cpu, uint16_t addr, uint16_t *dst){

    *dst &= 0x0;
    *dst |= cpu->memory[addr] << 8;
    *dst |= cpu->memory[addr + 1];

    return true;
}

bool write_uint16(struct CPU *cpu, uint16_t addr, uint16_t val){

    cpu->memory[addr]     = (val & 0xFF00) >> 8;
    cpu->memory[addr + 1] = (val & 0x00FF);

    return true;
}


bool cpu_memwrite(struct CPU *cpu, uint16_t addr, char *src, size_t count){

    for (uint16_t i = addr, j = 0; i < addr + count; i++, j++){

        cpu->memory[i] = src[j];

    }

    return true;
}

bool cpu_memread(struct CPU *cpu, uint16_t addr, char *dst, size_t count){

    for (uint16_t i = addr, j = 0; i < addr + count; i++, j++){
        dst[j] = cpu->memory[i];
    }


    return true;
}


void dump_memory_to_file(void* ptr, size_t size){
    
    char* filename = (char*)malloc(256);

    snprintf(filename, 256, "%ld.dmp", time(NULL));    
    
    printf("[*] Dumping %ld bytes from %p into %s\n",
           size, ptr, filename);

    FILE* fp = fopen(filename, "w");

    if (fp == NULL){
        fprintf(stderr, "[!] Error opening file %s to dump memory\n", filename);
        free(filename);
        return;
    }
   
    size_t result = fwrite(ptr, 1, size, fp);

    if (result != size){
        fprintf(stderr, "[!] Incomplete dump: (%ld/%ld)\n", result, size);
    }
    
    fclose(fp);
    free(filename);

    return;

}

void hexdump_memory(void *ptr, size_t size){
    
    const unsigned char* p = (unsigned char*)ptr;

    for ( size_t i = 0; i < size; i++ ){

        if (i % 16 == 0) printf("\n* 0x%04x : ", (unsigned int)i);
        if (i % 16 == 8) printf(" ");

        printf("%02x", p[i]);



    }

    printf("\n");
    return;
}

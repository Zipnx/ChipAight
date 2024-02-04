
#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

struct CPU;

bool stack_push(struct CPU* cpu, uint16_t val);
bool stack_pop(struct CPU* cpu, uint16_t* dst);

bool read_uint16(struct CPU* cpu, uint16_t addr, uint16_t* dst);
bool write_uint16(struct CPU* cpu, uint16_t addr, uint16_t val);

// These are only really used for the reg dumping instructions, might as well write em now
bool cpu_memwrite(struct CPU* cpu, uint16_t addr, char* src, size_t count);
bool cpu_memread(struct CPU* cpu, uint16_t addr, char* dst, size_t count);

void dump_memory_to_file(void* ptr, size_t size);
void hexdump_memory(void* ptr, size_t size);

#endif

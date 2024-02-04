
#ifndef OPCODES_H
#define OPCODES_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

struct CPU;

uint16_t get_current_opcode(struct CPU* cpu);

int op_get_regx(uint16_t op);
int op_get_regy(uint16_t op);

#endif

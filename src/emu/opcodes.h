
#ifndef OPCODES_H
#define OPCODES_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

struct CPU;

int execute_opcode(struct CPU* cpu, uint16_t op);

int execute_arithm_opcode(struct CPU* cpu, uint16_t op);
int execute_misc_opcode(struct CPU* cpu, uint16_t op);

uint16_t get_current_opcode(struct CPU* cpu);

int op_get_regx(uint16_t op);
int op_get_regy(uint16_t op);

#endif

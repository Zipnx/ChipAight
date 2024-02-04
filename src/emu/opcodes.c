
#include "opcodes.h"
#include "cpu.h"
#include "memory.h"

inline uint16_t get_current_opcode(struct CPU *cpu){

    uint16_t op;
    read_uint16(cpu, cpu->pc, &op);

    return op;

}

inline int op_get_regx(uint16_t op){
    return (op & 0x0F00) >> 8;
}

inline int op_get_regy(uint16_t op){
    return (op & 0x00F0) >> 4;
}

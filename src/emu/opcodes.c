
#include "opcodes.h"
#include "cpu.h"
#include "memory.h"

/*
 * This code is absolutely disgusting
 * Gonna (probably) fix it sometime later
 *
 */

int execute_opcode(struct CPU *cpu, uint16_t op){

    int regx = op_get_regx(op);
    int regy = op_get_regy(op);

    switch ( (op & 0xf000) >> 12 ){

    case 0:
        if ( (op & 0x00FF) == 0xEE ){

            // ret instruction
            uint16_t ret;

            if (!stack_pop(cpu, &ret))
                return 0;

            cpu->pc = ret;
            return 1;

        } else if ( (op & 0x00FF) == 0xE0 ){
            
            fprintf(stderr, "[!] UNIMPLEMENTED : disp_clear()\n");
            break;

        } else {
            fprintf(stderr, "[!] Invalid opcode: 0x%04x\n", op);
            return 0;
        }

    case 1:
        // 1NNN jmp instruction
        cpu->pc = op & 0x0FFF;
        return 1;

    case 2:
        // 2NNN call instruction
        //
        if (!stack_push(cpu, cpu->pc+2))
            return 0;
        cpu->pc = op & 0x0FFF;
        return 1;
    
    case 3:
        // 3XNN if (Vx == NN) skip next instruction
        cpu->pc += (cpu->V[regx] == (op & 0xFF)) ? 4 : 2;
        return 1;
        
    case 4:
        // 4XNN if (Vx != NN) skip next instruction
        cpu->pc += (cpu->V[regx] == (op & 0xFF)) ? 2 : 4;
        return 1;
    
    case 5:
        // 5XY0 if (Vx == Vy) skip next instruction

        cpu->pc += (cpu->V[regx] == cpu->V[regy]) ? 4 : 2;
        return 1;

    case 6:
        // 6XNN mov Vx, NN
        cpu->V[regx] = op & 0xFF;
        cpu->pc += 2;
        return 1;

    case 7:
        // 7XNN add Vx, NN (carry not affected)
        cpu->V[regx] += op & 0xFF;
        cpu->pc += 2;
        return 1;

    case 8:
        // 8--- Here are multiple arithmetic opcodes
        // put them in a seperate function so its less ugly
        // still, looks like shit
        return execute_arithm_opcode(cpu, op);
    
    // TODO: Add the opcodes after 9+

    default:
        fprintf(stderr, "[!] Error handling instruction: 0x%04x\n", op);
        return 0;
    } 

    cpu->pc += 2;

    return 1;

}

int execute_arithm_opcode(struct CPU *cpu, uint16_t op){
    
    int regx = op_get_regx(op);
    int regy = op_get_regy(op);

    switch (op & 0xf) {
    
    case 0:
        // 8XY0 set Vx to Vy
        cpu->V[regx] = cpu->V[regy];
        break;

    case 1:
        // 8XY1 Vx |= Vy
        cpu->V[regx] |= cpu->V[regy];
        break;
   
    case 2:
        // 8XY2 Vx &= Vy
        cpu->V[regx] &= cpu->V[regy];
        break;

    case 3:
        // 8XY3 Vx ^= Vy
        cpu->V[regx] ^= cpu->V[regy];
        break;

    case 4:
        // 8XY4 Vx += Vy (set vf to 1 if theres an overflow)
        
        cpu->V[0xf] = ( (256 - cpu->V[regx]) <= cpu->V[regy] ) ? 1 : 0;
        cpu->V[regx] += cpu->V[regy];
        break;

    case 5:
        // 8XY5 Vx -= Vy (set vf to 0 if theres an underflow)

        cpu->V[0xf] = (cpu->V[regx] >= cpu->V[regy]) ? 1 : 0;
        cpu->V[regx] -= cpu->V[regy];
        break;

    case 6:
        // 8XY6 Vx >>= 1
        cpu->V[regx] >>= 1;
        break;

    case 7:
        // 8XY7 Vx = Vy - Vx (set vf to 0 when theres and udnderflow)
        cpu->V[0xf] = (cpu->V[regx] <= cpu->V[regy]) ? 1 : 0;
        cpu->V[regx] = cpu->V[regy] - cpu->V[regx];
        break;

    case 0xE:
        // 8XYE Vx <<= 1
        
        cpu->V[regx] <<= 1;
        break;

    default:
        fprintf(stderr, "[!] Invalid arithmetic opcode: 0x%04x\n", op);
        return 0;

    } 

    cpu->pc += 2;
    return 1;
}


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

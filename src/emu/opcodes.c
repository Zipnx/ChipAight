
#include "opcodes.h"
#include "cpu.h"
#include "memory.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * This code is absolutely disgusting
 * Gonna (probably) fix it sometime later
 *
 */

// This resource is more accurate:

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
        break;

    case 7:
        // 7XNN add Vx, NN (carry not affected)
        cpu->V[regx] += op & 0xFF;
        break;

    case 8:
        // 8--- Here are multiple arithmetic opcodes
        // put them in a seperate function so its less ugly
        // still, looks like shit
        return execute_arithm_opcode(cpu, op);
    
    case 9:
        // 9XY0 If (Vx != Vy) skip the next instruction
        cpu->pc += (cpu->V[regx] != cpu->V[regy]) ? 4 : 2;
        return 1;

    case 0xA:
        // ANNN Set I = NNN
        cpu->I = (op & 0x0FFF);
        break;

    case 0xB:
        // BNNN Jmp to V[0] + NNN
        cpu->pc = (op & 0x0FFF) + cpu->V[0];

        if (cpu->pc >= MEMORY_SIZE){
            
            fprintf(stderr, "[!] PC register exceeded memory\n");
            return 0;

        }

        return 1;

    case 0xC:
        // CXNN Vx = rand() & NN
        cpu->V[regx] = rand() & (op & 0xff);
        break;

    case 0xD:
        // DXYN display(Vx, Vy, N)
        fprintf(stderr, "[!] UNIMPLEMENTED : display(Vx, Vy, N)\n");
        break;

    case 0xE:
        // EX9E / EXA1 Key operations

        if ( (op & 0xff) == 0x9E ){
            // Skip the next instruction is key in Vx is pressed
            
            cpu->pc += ( (cpu->pressed_keys & (0x1 << cpu->V[regx])) != 0 ) ? 4 : 2;

            return 1;

        } else if ( (op & 0xff) == 0xA1 ) {
            
            cpu->pc += ( (cpu->pressed_keys & (0x1 << cpu->V[regx])) != 0 ) ? 2 : 4;

            return 1;

        } else {

            fprintf(stderr, "[!] Invalid keyop: 0x%04x\n", op);
            return 0;

        }
    
    case 0xF:
        return execute_misc_opcode(cpu, op);

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
        cpu->V[0xf] = ((cpu->V[regx] & 0x1) > 0) ? 1 : 0;  
        cpu->V[regx] >>= 1;

        break;

    case 7:
        // 8XY7 Vx = Vy - Vx (set vf to 0 when theres and udnderflow)
        cpu->V[0xf] = (cpu->V[regx] <= cpu->V[regy]) ? 1 : 0;
        cpu->V[regx] = cpu->V[regy] - cpu->V[regx];
        break;

    case 0xE:
        // 8XYE Vx <<= 1
        cpu->V[0xf] = ((cpu->V[regx] & 0x80) > 0) ? 1 : 0;
        cpu->V[regx] <<= 1;
        break;

    default:
        fprintf(stderr, "[!] Invalid arithmetic opcode: 0x%04x\n", op);
        return 0;

    } 

    cpu->pc += 2;
    return 1;
}

int execute_misc_opcode(struct CPU* cpu, uint16_t op){

    // May use this to add more instructions to play around with

    int regx = op_get_regx(op);

    switch (op & 0xff){

    case 0x07:
        // Set Vx to the delay timer
        cpu->V[regx] = cpu->delay_timer & 0xff;
        break;

    case 0x0A:
        // Wait for keypress (blocking), and store the value in Vx
        
        // This is very hacky, will basically not increment pc, always executing until
        // a key is pressed, while it works exactly as needed, this kind of blocking the
        // execution is not ideal, maybe will make a better system at some point
        if (cpu->pressed_keys == 0){
            return 1;
        }

        // Store the first key found in the keypress bits
        for (int i = 0; i < 16; i++){
            
            if ( (cpu->pressed_keys & (0x1 << i)) != 0 ){
                cpu->V[regx] = i;
                break;
            }

        }
    
        break;

    case 0x15:
        // Set the delay timer to vx
        cpu->delay_timer = cpu->V[regx];
        break;

    case 0x18:
        // Set the sound timer to Vx
        cpu->sound_timer = cpu->V[regx];
        break;

    case 0x1E:
        // I += Vx (does not affect carry)
        cpu->I += (cpu->V[regx] & 0xFFF); // I is meant to be 12 bits
        break;

    case 0x29:
        cpu->I = (cpu->V[regx] & 0xf) * 5;

        break;

    case 0x33:
        // Convert Vx to BCD, and store it at the addr pointed by I (100s in I, 10s in I+1, 1s in I+2)

        if (cpu->I + 3 > MEMORY_SIZE) {
            fprintf(stderr, "[!] OOB Write when calculating BCD\n");
            return 0;
        }

        uint8_t tmp = cpu->V[regx];
        
        // Start with the 1s
        cpu->memory[cpu->I + 2] = tmp % 10;
        tmp /= 10;
        cpu->memory[cpu->I + 1] = tmp % 10;
        tmp /= 10;
        cpu->memory[cpu->I] = tmp % 10;


        break;

    case 0x55:
        // Dump registers up to and including Vx to the location pointed by I
        
        // (not destructive for I itself)
        
        if (cpu->I + regx + 1 > MEMORY_SIZE){
            fprintf(stderr, "[!] Prevented out of bounds write\n");
            return 0;
        }

        cpu_memwrite(cpu, cpu->I, (char*)(&cpu->V), regx + 1);
        break;

    case 0x65:
        // Store to V regs data stored at I up to I+X+1
        
        if (cpu->I + regx + 1 > MEMORY_SIZE){
            fprintf(stderr, "[!] Prevented out of bounds read\n");
            return 0;
        }

        cpu_memread(cpu, cpu->I, (char*)(&cpu->V), regx + 1);
        break;

    default:
    
        fprintf(stderr, "[!] (misc) Invalid instruction: 0x%04x\n", op);
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

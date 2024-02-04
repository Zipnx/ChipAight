
#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define MEMORY_SIZE 0x1000

struct CPU {

    uint8_t* memory;

    uint8_t V[16];

    uint16_t pc;
    uint16_t sp;
    uint16_t I;

    uint16_t delay_timer;
    uint16_t sound_timer;
};

struct CPU* init_cpu();

#endif

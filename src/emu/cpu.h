
#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "memory.h"
#include "../display/display.h"

#define MEMORY_SIZE 0x1000
#define FONTS_SIZE 80

extern char default_font[FONTS_SIZE];

struct CPU {
    
    struct Display* display;


    uint8_t* memory;
    uint16_t pressed_keys;

    uint8_t V[16];

    uint16_t pc;
    uint16_t sp;
    uint16_t I;

    uint8_t delay_timer;
    uint8_t sound_timer;
};

int cpu_display_refresh(struct CPU* cpu);
int cpu_cycle(struct CPU* cpu);

struct CPU* init_cpu(struct Display* targetDisplay);

void cpu_info_registers(struct CPU* cpu);

#endif

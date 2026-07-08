#pragma once

#include <stdint.h>
#include "chip8_config.h"

typedef struct chip8_registers
{
    uint8_t V[CHIP8_REGISTER_COUNT];
    uint16_t I;
    uint16_t PC;
    uint16_t SP;
    uint8_t delay_timer;
    uint8_t sound_timer;
} chip8_registers_t;
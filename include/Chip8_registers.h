#pragma once

#include <stdint.h>

#include "Chip8_config.h"

#define CHIP8_VF 15

typedef struct Chip8_Registers
{
    uint8_t V[CHIP8_REGISTER_COUNT];        /* General purpose registers */
    uint16_t I;                             /* Stores memory addresses */
    uint16_t PC;                            /* Program Counter - Stores currently executing address */
    uint16_t SP;                            /* Stack Pointer - Pointes to topmost level of the stack */
    uint8_t DT;                    /* Delay Timer - Decrements at 60hz while > 0 */
    uint8_t ST;                    /* Sound Timer - Decrements at 60hz while > 0 */
} Chip8_Registers;
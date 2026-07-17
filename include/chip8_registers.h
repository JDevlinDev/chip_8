#pragma once

#include <stdint.h>
#include "chip8_config.h"

typedef struct
{
    uint8_t V[CHIP8_REGISTER_COUNT];        /* General purpose registers */
    uint16_t I;                             /* Stores memory addresses */
    uint16_t PC;                            /* Program Counter - Stores currently executing address */
    uint16_t SP;                            /* Stack Pointer - Pointes to topmost level of the stack */
    uint8_t delay_timer;                    /* Delay Timer - Decrements at 60hz while > 0 */
    uint8_t sound_timer;                    /* Sound Timer - Decrements at 60hz while > 0 */
} chip8_registers_t;
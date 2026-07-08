#pragma once

#include <stdint.h>

#include "chip8_config.h"
#include "chip8_memory.h"
#include "chip8_registers.h"

typedef enum {
    CHIP8_STATE_RUNNING,
    CHIP8_STATE_PAUSED,
    CHIP8_STATE_PANIC
} chip8_state_t;

typedef struct chip8
{
    chip8_state_t state;
    chip8_memory_t memory;
    chip8_registers_t registers;
} chip8_t;
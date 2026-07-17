#pragma once

#include <stdint.h>
#include "chip8_config.h"

typedef struct
{
    uint8_t memory[CHIP8_MEMORY_SIZE];
} chip8_memory_t;

int         chip8_memory_set(chip8_memory_t *memory, int index, uint8_t value);
uint8_t     chip8_memory_get(chip8_memory_t *memory, int index);
uint16_t    chip8_memory_get_opcode(chip8_memory_t *memory, int index);
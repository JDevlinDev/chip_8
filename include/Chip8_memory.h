#pragma once

#include <stdint.h>

#include "Chip8_config.h"

typedef struct Chip8_Memory
{
    uint8_t memory[CHIP8_MEMORY_SIZE];
} Chip8_Memory;

int         chip8_memory_set(Chip8_Memory *memory, int index, uint8_t value);
uint8_t     chip8_memory_get(Chip8_Memory *memory, int index);
uint16_t    chip8_memory_get_opcode(Chip8_Memory *memory, int index);
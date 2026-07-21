#pragma once

#include <stdint.h>

#include "Chip8_config.h"

typedef struct Chip8_Memory
{
    uint8_t memory[CHIP8_MEMORY_SIZE];
} Chip8_Memory;

int         Chip8_SetMemory(Chip8_Memory *memory, int index, uint8_t value);
uint8_t     Chip8_GetMemory(Chip8_Memory *memory, int index);
uint16_t    Chip8_GetOpcode(Chip8_Memory *memory, int index);
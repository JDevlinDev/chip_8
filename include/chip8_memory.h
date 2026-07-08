#pragma once

#include <stdint.h>
#include "chip8_config.h"

typedef struct chip8_memory
{
    uint8_t memory[CHIP8_MEMORY_SIZE];
} chip8_memory_t;

int chip8_memory_set(chip8_memory_t *memory, uint16_t index, uint8_t value);

uint8_t chip8_memory_get(chip8_memory_t *memory, uint16_t index);
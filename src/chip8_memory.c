#include <stdio.h>
#include <stdlib.h>
#include "chip8_memory.h"

static void chip8_memory_in_bounds(uint16_t index)
{
    if (index < 0 || index >= CHIP8_MEMORY_SIZE) {
        fprintf(stderr, "CHIP-8 FATAL ERROR: Attempt to access memory out of bounds.\n");
        exit(EXIT_FAILURE);
    }
}

int chip8_memory_set(chip8_memory_t *memory, uint16_t index, uint8_t value)
{
    chip8_memory_in_bounds(index);
    memory->memory[index] = value;
}

uint8_t chip8_memory_get(chip8_memory_t *memory, uint16_t index)
{
    chip8_memory_in_bounds(index);
    return memory->memory[index];
}

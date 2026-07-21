#include <stdio.h>
#include <stdlib.h>
#include "Chip8_memory.h"

static void chip8_memory_in_bounds(int index)
{
    if (index < 0 || index >= CHIP8_MEMORY_SIZE) {
        fprintf(stderr, "CHIP-8 FATAL ERROR: Attempt to access memory out of bounds.\n");
        exit(EXIT_FAILURE);
    }
}

int Chip8_SetMemory(Chip8_Memory *memory, int index, uint8_t value)
{
    chip8_memory_in_bounds(index);
    memory->memory[index] = value;
}

uint8_t Chip8_GetMemory(Chip8_Memory *memory, int index)
{
    chip8_memory_in_bounds(index);
    return memory->memory[index];
}

uint16_t Chip8_GetOpcode(Chip8_Memory *memory, int index)
{
    return (Chip8_GetMemory(memory, index) << 8) | Chip8_GetMemory(memory, index + 1);
}

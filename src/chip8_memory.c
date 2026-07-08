#include <stdio.h>
#include <stdlib.h>
#include "chip8_memory.h"

static int chip8_memory_in_bounds(uint16_t index)
{
    if (0 > index || CHIP8_MEMORY_SIZE <= index) {
        fprintf(stderr, "Attempt to access memory out of bounds. Exiting...\n");
        return -1;
    }
}

int chip8_memory_set(chip8_memory_t *memory, uint16_t index, uint8_t value)
{

}

uint8_t chip8_memory_get(chip8_memory_t *memory, uint16_t index)
{

}

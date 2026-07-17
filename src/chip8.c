#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "chip8.h"
#include "chip8_config.h"

static const uint8_t chip8_default_character_set[] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};



void chip8_init(chip8_t *chip8)
{
    memset(chip8, 0, sizeof(chip8_t));
    memcpy(&chip8->memory.memory, chip8_default_character_set, sizeof(chip8_default_character_set));
}

void chip8_load(chip8_t *chip8, const uint8_t *buf, size_t size)
{
    if ((size + CHIP8_PROGRAM_LOAD_ADDRESS) >= CHIP8_MEMORY_SIZE) {
        fprintf(stderr, "Program exceeds maximum memory size!\n");
        exit(EXIT_FAILURE);
    }
    memcpy(&chip8->memory.memory[CHIP8_PROGRAM_LOAD_ADDRESS], buf, size);
    chip8->registers.PC = CHIP8_PROGRAM_LOAD_ADDRESS;
}

size_t chip8_fopen(char *fname, uint8_t **buf)
{
    FILE *f = fopen(fname, "r");

    if (!f) {
        fprintf(stderr, "Failed to open the file\n");
        return 0;
    }

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    uint8_t buffer[fsize];
    int res = fread(buf, fsize, 1, f);
    if (res != 1) {
        fprintf(stderr, "Failed to read from the file\n");
        return 0;
    }
    *buf = buffer;
    return fsize;
}
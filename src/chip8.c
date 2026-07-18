#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <errno.h>

#include "chip8.h"

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

static void chip8_pmem(chip8_t *chip8, const uint8_t *buf, size_t size)
{
    if ((size + CHIP8_PROGRAM_LOAD_ADDRESS) >= CHIP8_MEMORY_SIZE) {
        fprintf(stderr, "Program exceeds maximum memory size!\n");
        exit(EXIT_FAILURE);
    }
    memcpy(&chip8->memory.memory[CHIP8_PROGRAM_LOAD_ADDRESS], buf, size);
    chip8->registers.PC = CHIP8_PROGRAM_LOAD_ADDRESS;
}

static void chip8_decode_exec(chip8_t *chip8, uint16_t opcode)
{
    uint8_t x = CHIP8_NIBBLE_X(opcode);
    uint8_t y = CHIP8_NIBBLE_Y(opcode);
    uint8_t n = CHIP8_NIBBLE_N(opcode);
    uint8_t nn = CHIP8_NIBBLE_NN(opcode);
    uint16_t nnn = CHIP8_NIBBLE_NNN(opcode);

    switch(0xf000 & opcode) {

        /* JP addr: Jump to location nnn */
        case 0x1000:
            chip8->registers.PC = nnn;
            break;

        /* LD Vn, byte: puts the value nn into register V[x] */
        case 0x6000:
            chip8->registers.V[x] = nn;
            break;

        /* ADD Vx, byte: Adds the value nn to the value of register V[x], then stores the result in V[x] */
        case 0x7000:
            chip8->registers.V[x] += nn;
            break;

        /* LD I, addr: The value of register I is set to nnn */
        case 0xa000:
            chip8->registers.I = nnn;
            break;

        /* DRW V[x], V[y], nibble: Display n-byte sprite starting at memory location I at (V[x], V[y]), set VF = collision */
        case 0xd000:
            chip8_draw_sprite(
                &chip8->screen,
                chip8->registers.V[x],
                chip8->registers.V[y],
                &chip8->memory.memory[chip8->registers.I],
                n);
            break;

        /*  */
        
    }
}

void chip8_init(chip8_t *chip8)
{
    memset(chip8, 0, sizeof(chip8_t));
    memcpy(&chip8->memory.memory, chip8_default_character_set, sizeof(chip8_default_character_set));
}

size_t chip8_load(chip8_t *chip8, char *fname)
{
    errno = 0;
    FILE *f = fopen(fname, "r");

    if (!f) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return 0;
    }

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    uint8_t buffer[CHIP8_MEMORY_SIZE];
    int res = fread(buffer, fsize, 1, f);
    if (res != 1) {
        fclose(f);
        return 0;
    }
    fclose(f);
    chip8_pmem(chip8, buffer, fsize);

    return fsize;
}

uint16_t chip8_fetch(chip8_t *chip8)
{
    uint16_t opcode = chip8_memory_get_opcode(&chip8->memory, chip8->registers.PC);
    chip8->registers.PC += 2;
    return opcode;
}

void chip8_exec(chip8_t *chip8, uint16_t opcode)
{
    switch(opcode) { 

        /* CLS: Clear the screen */
        case 0x00E0:
            chip8_clear_screen(&chip8->screen);
            break;

        /* RET: Return from a subroutine */
        case 0x00EE:
            chip8->registers.PC = chip8_stack_pop(chip8);
            break;
        default:
            chip8_decode_exec(chip8, opcode);
    }

}
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "chip8_stack.h"
#include "chip8.h"

void chip8_stack_push(chip8_t *chip8, uint16_t val) {
    if (chip8->registers.SP > CHIP8_STACK_DEPTH) {
        fprintf(stderr, "CHIP8 FATAL ERROR: Stack overflow!\n");
        exit(EXIT_FAILURE);
    }
    chip8->stack.stack[chip8->registers.SP];
    chip8->registers.SP++;
}

uint16_t chip8_stack_pop(chip8_t *chip8)
{
    chip8->registers.SP--;
    if (chip8->registers.SP >= CHIP8_STACK_DEPTH) {
        fprintf(stderr, "CHIP-8 FATAL ERROR: Stack underflow!\n");
        exit(EXIT_FAILURE);
    }
    return chip8->stack.stack[chip8->registers.SP];
}
#include <stdint.h>
#include "chip8.h"
#include "chip8_stack.h"

void chip8_stack_in_bounds(chip8_t *chip8) {
    if (chip8->registers.SP > CHIP8_STACK_DEPTH)
        chip8->state = CHIP8_STATE_PANIC;
}

void chip8_stack_push(chip8_t *chip8, uint16_t val) {
    chip8->stack.stack[chip8->registers.PC] = val;
    chip8->registers.PC++;
}

uint16_t chip8_stack_pop(chip8_t *chip8)
{
    chip8->registers.SP--;
    // ???????? Supposed to terminate program if the stack pointer gets decremented out-of-bounds
    // Cant just change the state flag here and allow the program to keep running
}
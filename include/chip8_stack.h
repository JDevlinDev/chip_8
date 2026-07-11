#pragma once

#include <stdint.h>

#include "chip8.h"
#include "chip8_config.h"

typedef struct chip8_stack
{
    uint16_t stack[CHIP8_STACK_DEPTH];
} chip8_stack_t;

void chip8_stack_push(chip8_t *chip8, uint16_t val);
uint16_t chip8_stack_pop(chip8_t *chip8);
void chip8_stack_in_bounds(chip8_t *chip8);
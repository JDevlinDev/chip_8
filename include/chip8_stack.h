#pragma once

#include <stdint.h>

#include "chip8_config.h"
#include "chip8.h"


typedef struct chip8 chip8_t;

typedef struct
{
    uint16_t stack[CHIP8_STACK_DEPTH];
} chip8_stack_t;

void chip8_stack_push(chip8_t *chip8, uint16_t val);
uint16_t chip8_stack_pop(chip8_t *chip8);
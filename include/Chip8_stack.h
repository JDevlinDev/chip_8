#pragma once

#include <stdint.h>

#include "Chip8_config.h"

typedef struct Chip8_Interpreter Chip8_Interpreter;

typedef struct Chip8_Stack
{
    uint16_t stack[CHIP8_STACK_DEPTH];
} Chip8_Stack;

void Chip8_Push(Chip8_Interpreter *chip8, uint16_t val);
uint16_t Chip8_Pop(Chip8_Interpreter *chip8);
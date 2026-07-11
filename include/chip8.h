#pragma once

#include <stdint.h>

#include "chip8_config.h"
#include "chip8_memory.h"
#include "chip8_registers.h"
#include "chip8_keyboard.h"
#include "chip8_stack.h"

typedef struct chip8_emulator
{
    chip8_memory_t memory;
    chip8_stack_t stack;
    chip8_registers_t registers;
    chip8_keyboard_t keyboard;
} chip8_t;

void chip8_init(chip8_t *chip8);
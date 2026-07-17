#pragma once

#include <stdint.h>
#include <stddef.h>

#include "chip8_config.h"
#include "chip8_memory.h"
#include "chip8_registers.h"
#include "chip8_keyboard.h"
#include "chip8_stack.h"
#include "chip8_screen.h"

typedef struct
{
    chip8_memory_t      memory;
    chip8_stack_t       stack;
    chip8_registers_t   registers;
    chip8_keyboard_t    keyboard;
    chip8_screen_t      screen;
} chip8_t;

void        chip8_init(chip8_t *chip8);
void        chip8_load(chip8_t *chip8, uint8_t *buf, size_t size);
uint16_t    chip8_fetch(chip8_t *chip8);
void        chip8_exec(chip8_t *chip8, uint16_t opcode);

size_t      chip8_fopen(char *fname, uint8_t **buf);
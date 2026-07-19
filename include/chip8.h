#pragma once

#include <stdint.h>
#include <stddef.h>

#include "chip8_config.h"
#include "chip8_memory.h"
#include "chip8_registers.h"
#include "chip8_keyboard.h"
#include "chip8_stack.h"
#include "chip8_screen.h"

/* Instruction decoding macros */
#define CHIP8_NIBBLE_X(x)       (((x) & 0x0f00) >> 8)
#define CHIP8_NIBBLE_Y(x)       (((x) & 0x00f0) >> 4)
#define CHIP8_NIBBLE_N(x)       ((x) & 0x000f)
#define CHIP8_NIBBLE_NN(x)      ((x) & 0x00ff)
#define CHIP8_NIBBLE_NNN(x)     ((x) & 0x0fff)


typedef struct chip8
{
    chip8_memory_t      memory;
    chip8_stack_t       stack;
    chip8_registers_t   registers;
    chip8_keyboard_t    keyboard;
    chip8_screen_t      screen;

    bool        wait_for_keypress;
    uint8_t     keypress_register; 
} chip8_t;

void        chip8_init(chip8_t *chip8);
uint16_t    chip8_fetch(chip8_t *chip8);
void        chip8_exec(chip8_t *chip8, uint16_t opcode);

size_t      chip8_load(chip8_t *chip8, char *fname);
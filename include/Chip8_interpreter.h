#pragma once

#include <stdint.h>
#include <stddef.h>

#include "Chip8_config.h"
#include "Chip8_memory.h"
#include "Chip8_registers.h"
#include "Chip8_keyboard.h"
#include "Chip8_stack.h"
#include "Chip8_display.h"

/* Instruction decoding macros */
#define CHIP8_NIBBLE_X(x)       (((x) & 0x0f00) >> 8)
#define CHIP8_NIBBLE_Y(x)       (((x) & 0x00f0) >> 4)
#define CHIP8_NIBBLE_N(x)       ((x) & 0x000f)
#define CHIP8_NIBBLE_NN(x)      ((x) & 0x00ff)
#define CHIP8_NIBBLE_NNN(x)     ((x) & 0x0fff)


typedef struct chip8
{
    Chip8_Memory      memory;
    Chip8_Stack       stack;
    Chip8_Registers   registers;
    Chip8_Keyboard    keyboard;
    Chip8_display      screen;

    bool        wait_for_keypress;
    uint8_t     keypress_register; 
} Chip8_Interpreter;

void        chip8_init(Chip8_Interpreter *chip8);
uint16_t    chip8_fetch(Chip8_Interpreter *chip8);
void        chip8_exec(Chip8_Interpreter *chip8, uint16_t opcode);

size_t      chip8_load(Chip8_Interpreter *chip8, char *fname);
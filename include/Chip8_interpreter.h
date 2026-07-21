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


typedef struct Chip8_Interpreter
{
    Chip8_Memory      memory;
    Chip8_Stack       stack;
    Chip8_Registers   registers;
    Chip8_Keyboard    keyboard;
    Chip8_Display      screen;

    bool        wait_for_keypress;
    uint8_t     keypress_register; 
} Chip8_Interpreter;

void        Chip8_Init(Chip8_Interpreter *chip8);
uint16_t    Chip8_Fetch(Chip8_Interpreter *chip8);
void        Chip8_Execute(Chip8_Interpreter *chip8, uint16_t opcode);

size_t      Chip8_Load(Chip8_Interpreter *chip8, char *fname);
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "chip8_config.h"
#include "chip8.h"

typedef struct {
    bool keys[CHIP8_TOTAL_KEYS];
} chip8_keyboard_t;

void chip8_keyboard_down(chip8_t *chip8, int key);

void chip8_keyboard_up(chip8_t *chip8, int key);

bool chip8_keyboard_is_down(chip8_t *chip8, int key);

uint8_t chip8_keyboard_map(char key);
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "chip8_config.h"

typedef struct {
    bool keys[CHIP8_TOTAL_KEYS];
} chip8_keyboard_t;

void chip8_keyboard_down(chip8_keyboard_t *keyboard, uint8_t key);

void chip8_keyboard_up(chip8_keyboard_t *keyboard, uint8_t key);

bool chip8_keyboard_is_down(chip8_keyboard_t *keyboard, uint8_t key);

uint8_t chip8_keyboard_map(const char *map, uint8_t key);
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "chip8_config.h"
#include "chip8_keyboard.h"

typedef struct chip8_keyboard {
    bool keys[CHIP8_TOTAL_KEYS];
    bool waiting_for_key;
} chip8_keyboard_t;

void chip8_keyboard_down(chip8_keyboard_t *keyboard, int key);

void chip8_keyboard_up(chip8_keyboard_t *keyboard, int key);

bool chip8_keyboard_is_down(chip8_keyboard_t *keyboard, int key);

uint8_t chip8_keyboard_map(char key);
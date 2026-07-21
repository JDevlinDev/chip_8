#pragma once

#include <stdint.h>
#include <stdbool.h>

#include <SDL3/SDL_scancode.h>

#include "Chip8_config.h"
#include "Chip8_keyboard.h"

typedef struct Chip8_Keyboard {
    bool keys[CHIP8_TOTAL_KEYS];
    bool waiting_for_key;
} Chip8_Keyboard;

void chip8_keyboard_down(Chip8_Keyboard *keyboard, int key);

void chip8_keyboard_up(Chip8_Keyboard *keyboard, int key);

bool chip8_keyboard_is_down(Chip8_Keyboard *keyboard, int key);

uint8_t chip8_keyboard_map(SDL_Scancode key);
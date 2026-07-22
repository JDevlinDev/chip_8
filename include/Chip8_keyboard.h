#pragma once

#include <stdint.h>
#include <SDL3/SDL_scancode.h>

#include "Chip8_config.h"
#include "Chip8_keyboard.h"

typedef struct Chip8_Keyboard {
    bool keys[CHIP8_TOTAL_KEYS];
    bool waiting_for_key;
} Chip8_Keyboard;

void Chip8_KeyDown(Chip8_Keyboard *keyboard, int key);

void Chip8_KeyUp(Chip8_Keyboard *keyboard, int key);

bool Chip8_KeyIsDown(Chip8_Keyboard *keyboard, int key);

int Chip8_MapKey(SDL_Scancode key);
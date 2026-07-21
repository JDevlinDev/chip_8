#include <stdint.h>
#include <stdbool.h>

#include <SDL3/SDL_scancode.h>

#include "Chip8_keyboard.h"
#include "Chip8_config.h"

static SDL_Scancode keyboard_map[] = {
    SDL_SCANCODE_1, SDL_SCANCODE_2, SDL_SCANCODE_3, SDL_SCANCODE_4,
    SDL_SCANCODE_Q, SDL_SCANCODE_W, SDL_SCANCODE_E, SDL_SCANCODE_R,
    SDL_SCANCODE_A, SDL_SCANCODE_S, SDL_SCANCODE_D, SDL_SCANCODE_F,
    SDL_SCANCODE_Z, SDL_SCANCODE_X, SDL_SCANCODE_C, SDL_SCANCODE_V
};

void Chip8_KeyDown(Chip8_Keyboard *keyboard, int key)
{
    keyboard->keys[key] = true;
}

void Chip8_KeyUp(Chip8_Keyboard *keyboard, int key)
{
    keyboard->keys[key] = false;
}

bool Chip8_KeyIsDown(Chip8_Keyboard *keyboard, int key)
{
    return (keyboard->keys[key] == true);
}

uint8_t Chip8_MapKey(SDL_Scancode key)
{
    for (int i = 0; i < CHIP8_TOTAL_KEYS; i++) {
        if (keyboard_map[i] == key) return i;
    }
    return -1;
}
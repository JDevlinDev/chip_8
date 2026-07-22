#include <stdint.h>
#include <stdbool.h>

#include <SDL3/SDL_scancode.h>

#include "Chip8_keyboard.h"
#include "Chip8_config.h"

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

int Chip8_MapKey(SDL_Scancode key)
{
    switch (key) {
        case SDL_SCANCODE_1: return 0x1;
        case SDL_SCANCODE_2: return 0x2;
        case SDL_SCANCODE_3: return 0x3;
        case SDL_SCANCODE_4: return 0xC;
        case SDL_SCANCODE_Q: return 0x4;
        case SDL_SCANCODE_W: return 0x5;
        case SDL_SCANCODE_E: return 0x6;
        case SDL_SCANCODE_R: return 0xD;
        case SDL_SCANCODE_A: return 0x7;
        case SDL_SCANCODE_S: return 0x8;
        case SDL_SCANCODE_D: return 0x9;
        case SDL_SCANCODE_F: return 0xE;
        case SDL_SCANCODE_Z: return 0xA;
        case SDL_SCANCODE_X: return 0x0;
        case SDL_SCANCODE_C: return 0xB;
        case SDL_SCANCODE_V: return 0xF;
        default: return -1;
    }
}
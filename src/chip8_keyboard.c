#include <stdint.h>
#include <stdbool.h>

#include <SDL3/SDL.h>

#include "chip8.h"
#include "chip8_keyboard.h"
#include "chip8_config.h"

static char keyboard_map[] = {
    SDLK_1, SDLK_2, SDLK_3, SDLK_4,
    SDLK_Q, SDLK_W, SDLK_E, SDLK_R,
    SDLK_A, SDLK_S, SDLK_D, SDLK_F,
    SDLK_Z, SDLK_X, SDLK_C, SDLK_V
};

void chip8_keyboard_down(chip8_t *chip8, int key)
{
    chip8->keyboard.keys[key] = true;
}

void chip8_keyboard_up(chip8_t *chip8, int key)
{
    chip8->keyboard.keys[key] = false;
}

bool chip8_keyboard_is_down(chip8_t *chip8, int key)
{
    return (chip8->keyboard.keys[key] == true);
}

uint8_t chip8_keyboard_map(char key)
{
    for (int i = 0; i < CHIP8_TOTAL_KEYS; i++) {
        if (keyboard_map[i] == key) return i;
    }
    return -1;
}
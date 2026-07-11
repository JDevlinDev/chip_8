#include <stdint.h>
#include <stdbool.h>

#include <SDL3/SDL.h>

#include "chip8_config.h"

static char keyboard_map[] = {
    SDLK_Q, SDLK_W, SDLK_E, SDLK_R,
    SDLK_A, SDLK_S, SDLK_D, SDLK_F,
    SDLK_Z, SDLK_X, SDLK_C, SDLK_V
};
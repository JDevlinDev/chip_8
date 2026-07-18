#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "chip8_config.h"


typedef struct chip8_screen
{
    bool pixels[CHIP8_SCREEN_HEIGHT][CHIP8_SCREEN_WIDTH];
} chip8_screen_t;

void chip8_set_pixel(chip8_screen_t *screen, int x, int y);

bool chip8_pixel_is_set(chip8_screen_t *screen, int x, int y);

bool chip8_draw_sprite(chip8_screen_t *screen, int x, int y, uint8_t *sprite, int num_bytes);

void chip8_clear_screen(chip8_screen_t *screen);
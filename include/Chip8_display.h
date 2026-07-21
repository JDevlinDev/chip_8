#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "Chip8_config.h"


typedef struct Chip8_Display
{
    bool pixels[CHIP8_SCREEN_HEIGHT][CHIP8_SCREEN_WIDTH];
} Chip8_display;

void chip8_set_pixel(Chip8_display *screen, int x, int y);

bool chip8_pixel_is_set(Chip8_display *screen, int x, int y);

bool chip8_draw_sprite(Chip8_display *screen, int x, int y, uint8_t *sprite, int num_bytes);

void chip8_clear_screen(Chip8_display *screen);
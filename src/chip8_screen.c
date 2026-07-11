#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "chip8_screen.h"

static void chip8_pixel_in_bounds(int x, int y)
{
    if((x >= CHIP8_SCREEN_WIDTH || x < 0) || (y >= CHIP8_SCREEN_HEIGHT || y < 0)) {
        fprintf(stderr, "CHIP8 FATAL ERROR: Pixel coordinate out of bounds.\n");
        exit(EXIT_FAILURE);
    }
}

void chip8_set_pixel(chip8_screen_t *screen, int x, int y)
{
    chip8_pixel_in_bounds(x, y);
    screen->pixels[y][x] = true;
}

bool chip8_pixel_is_set(chip8_screen_t *screen, int x, int y)
{
    chip8_pixel_in_bounds(x, y);
    return screen->pixels[y][x];
}
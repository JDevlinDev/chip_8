#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "Chip8_display.h"

static void chip8_pixel_in_bounds(int x, int y)
{
    if((x >= CHIP8_SCREEN_WIDTH || x < 0) || (y >= CHIP8_SCREEN_HEIGHT || y < 0)) {
        fprintf(stderr, "CHIP8 FATAL ERROR: Pixel coordinate out of bounds.\n");
        exit(EXIT_FAILURE);
    }
}

void Chip8_SetPixel(Chip8_Display *display, int x, int y)
{
    chip8_pixel_in_bounds(x, y);
    display->pixels[y][x] = true;
}

bool Chip8_PixelIsSet(Chip8_Display *display, int x, int y)
{
    chip8_pixel_in_bounds(x, y);
    return display->pixels[y][x];
}

bool Chip8_DrawSprite(Chip8_Display *display, int x, int y, uint8_t *sprite, int num_bytes)
{
    bool collision = false;

    for (int ly = 0; ly < num_bytes; ly++) {
        uint8_t next_byte = sprite[ly];
        for (int lx = 0; lx < 8; lx++) {
            if((next_byte & (0b10000000 >> lx)) == 0)
                continue;

            if (display->pixels[(ly + y) % CHIP8_SCREEN_HEIGHT][(lx + x) % CHIP8_SCREEN_WIDTH])
                collision = true;
            display->pixels[(ly + y) % CHIP8_SCREEN_HEIGHT][(lx + x) % CHIP8_SCREEN_WIDTH] ^=  true;
        }
    }
    return collision;
}

void Chip8_ClearDisplay(Chip8_Display *display)
{
    memset(display, 0, CHIP8_SCREEN_HEIGHT * CHIP8_SCREEN_WIDTH);
}
#pragma once

#include <stdint.h>

#include "Chip8_config.h"


typedef struct Chip8_Display
{
    bool pixels[CHIP8_SCREEN_HEIGHT][CHIP8_SCREEN_WIDTH];
} Chip8_Display;

void Chip8_SetPixel(Chip8_Display *screen, int x, int y);

bool Chip8_PixelIsSet(Chip8_Display *screen, int x, int y);

bool Chip8_DrawSprite(Chip8_Display *screen, int x, int y, uint8_t *sprite, int num_bytes);

void Chip8_ClearDisplay(Chip8_Display *screen);
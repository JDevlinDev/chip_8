#include <string.h>

#include "chip8.h"

void chip8_init(chip8_t *chip8)
{
    memset(chip8, 0, sizeof(chip8_t));
}
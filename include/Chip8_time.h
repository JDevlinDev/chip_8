#pragma once

#include <stdint.h>
#include <SDL3/SDL_time.h>

typedef Chip8_Emulator Chip8_Emulator;

typedef struct Chip8_Time {
   uint64_t    in_accumulator;
   uint64_t    tm_accumulator;
   uint64_t    last;
} Chip8_Time;

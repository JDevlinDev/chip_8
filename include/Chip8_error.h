#pragma once

typedef enum Chip8_Error {
   Chip8_ErrorStackOverflow = 0,
   Chip8_ErrorStackUnderflow,
   Chip8_ErrorMemoryFull,
   Chip8_ErrorInvalidOpcode
} Chip8_Error;


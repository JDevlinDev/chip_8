#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

#include <Chip8_emulator.h>
#include <Chip8_audio.h>
#include <Chip8_time.h>

typedef struct Chip8_EmulatorState {
   Chip8_Emulator    emulator;
   Chip8_Time        time;

   char     rom_filepath[256];
   bool     is_running;

   uint64_t    instructions_executed;
   uint64_t    cycle_count;
   bool        logging_enabled;

   SDL_Window     *window;
   SDL_Renderer   *renderer;
} Chip8_EmulatorState;

bool    Chip8_InitEmulator(Chip8_EmulatorState *es);
void    Chip8_UpdateContext(Chip8_EmulatorState *es);

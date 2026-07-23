#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

#include <Chip8_emulator.h>
#include <Chip8_audio.h>

typedef struct Chip8_AppState {
   Chip8_Emulator    emulator;

   char     rom_filepath[256];
   bool     is_running;

   uint64_t    i_accumulator;
   uint64_t    t_accumulator;
   uint64_t    last_step;
   uint64_t    cycle_count;

   SDL_Window     *window;
   SDL_Renderer   *renderer;
} Chip8_AppState;

bool    Chip8_InitializeApp(Chip8_AppState *as);
void    Chip8_UpdateClock(Chip8_AppState *as);

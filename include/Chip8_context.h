#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

#include <Chip8_emulator.h>
#include <Chip8_audio.h>
#include <Chip8_time.h>

typedef struct Chip8_Context {
    // Core Emulator
   Chip8_Emulator    emulator;
   Chip8_Time        time;

   char     rom_filepath[256];
   bool     is_running;
   bool     wait;
//    uint8_t   key_register;

   // // Statistics
   uint64_t    instructions_executed;
   uint64_t    cycle_count;
   bool        logging_enabled;
   FILE       *log_file;

   // Frontend
   SDL_Window     *window;
   SDL_Renderer   *renderer;
} Chip8_Context;

bool    Chip8_InitializeContext(Chip8_Context *ctx);
void    Chip8_UpdateContext(Chip8_Context *ctx);

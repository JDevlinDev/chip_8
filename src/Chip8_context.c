#include <time.h>
#include <errno.h>

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_time.h>

#include "Chip8_context.h"
#include "Chip8_emulator.h"
#include "Chip8_audio.h"
#include "Chip8_config.h"

bool Chip8_InitEmulator(Chip8_EmulatorState *ctx)
{
   SDL_SetAppMetadata("Chip8 Renderer", "1.0", "com.jdevs.chip8");

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer(
            CHIP8_WINDOW_TITLE,
            CHIP8_WINDOW_WIDTH,
            CHIP8_WINDOW_HEIGHT,
            SDL_WINDOW_RESIZABLE,
            &ctx->window, &ctx->renderer)) {
            SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(
            ctx->renderer,
            CHIP8_SCREEN_WIDTH,
            CHIP8_SCREEN_HEIGHT,
            SDL_LOGICAL_PRESENTATION_LETTERBOX);

   Chip8_Init(&ctx->emulator);

   ctx->time.i_accumulator = 0;
   ctx->time.t_accumulator = 0;
   ctx->time.last = 0;
   ctx->is_running = false;
}

void Chip8_UpdateContext(Chip8_EmulatorState *ctx)
{
   if (ctx->time.last == 0) {
        ctx->time.last = SDL_GetTicksNS();
    }
    
   uint64_t current_time = SDL_GetTicksNS();
   uint64_t time_delta = current_time - ctx->time.last;
   ctx->time.last = current_time;
   
   ctx->time.i_accumulator += time_delta;
   ctx->time.t_accumulator += time_delta;

   // Handle CPU instruction cycles
   while (ctx->time.i_accumulator >= CHIP8_CLOCK_RATE_NS) {
      uint16_t next_instruction = Chip8_Fetch(&ctx->emulator);
      Chip8_Execute(&ctx->emulator, next_instruction);
      ctx->time.i_accumulator -= CHIP8_CLOCK_RATE_NS;
   }
    
   // Handle 60Hz Delay and Sound timers
   while (ctx->time.t_accumulator >= CHIP8_TIMER_RATE_NS) {
      if (ctx->emulator.registers.DT > 0) {
         ctx->emulator.registers.DT--;
      }
   
      if (ctx->emulator.registers.ST > 0) {
         ctx->emulator.registers.ST--;
         Chip8_PlayBeep(&ctx->emulator.audio);
      }

      ctx->time.t_accumulator -= CHIP8_TIMER_RATE_NS;
   }
}
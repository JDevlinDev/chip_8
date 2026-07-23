#include <time.h>
#include <errno.h>

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_time.h>

#include "Chip8_appState.h"
#include "Chip8_emulator.h"
#include "Chip8_audio.h"
#include "Chip8_config.h"

bool Chip8_InitializeApp(Chip8_AppState *as)
{
   SDL_SetAppMetadata("Chip8 Renderer", "1.0", "com.jdevs.chip8");

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    memset(as, 0, sizeof(Chip8_AppState));

    if (!SDL_CreateWindowAndRenderer(
            CHIP8_WINDOW_TITLE,
            CHIP8_WINDOW_WIDTH,
            CHIP8_WINDOW_HEIGHT,
            SDL_WINDOW_RESIZABLE,
            &as->window, &as->renderer)) {
            SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
            return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(
            as->renderer,
            CHIP8_SCREEN_WIDTH,
            CHIP8_SCREEN_HEIGHT,
            SDL_LOGICAL_PRESENTATION_LETTERBOX);
            
   Chip8_Init(&as->emulator);

   as->is_running = false;
}

void Chip8_UpdateClock(Chip8_AppState *as)
{
   if (as->last_step == 0) {
        as->last_step = SDL_GetTicksNS();
    }
    
   uint64_t current_time = SDL_GetTicksNS();
   uint64_t time_delta = current_time - as->last_step;
   as->last_step = current_time;
   
   as->i_accumulator += time_delta;
   as->t_accumulator += time_delta;

   // Handle CPU instruction cycles
   while (as->i_accumulator >= CHIP8_CLOCK_RATE_NS) {
      uint16_t next_instruction = Chip8_Fetch(&as->emulator);
      Chip8_Execute(&as->emulator, next_instruction);
      as->i_accumulator -= CHIP8_CLOCK_RATE_NS;
   }
    
   // Handle 60Hz Delay and Sound timers
   while (as->t_accumulator >= CHIP8_TIMER_RATE_NS) {
      if (as->emulator.registers.DT > 0) {
         as->emulator.registers.DT--;
      }
   
      if (as->emulator.registers.ST > 0) {
         as->emulator.registers.ST--;
         Chip8_PlayBeep(&as->emulator.audio);
      }

      as->t_accumulator -= CHIP8_TIMER_RATE_NS;
   }
}
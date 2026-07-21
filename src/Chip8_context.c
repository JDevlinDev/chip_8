#include <SDL3/SDL_render.h>
#include <SDL3/SDL_init.h>

#include "Chip8_context.h"
#include "Chip8_emulator.h"
#include "Chip8_audio.h"
#include "Chip8_config.h"

bool Chip8_InitializeContext(Chip8_Context *ctx)
{
   SDL_SetAppMetadata("Chip8 Renderer", "1.0", "com.jdevs.chip8");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
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
            &ctx->renderer,
            CHIP8_SCREEN_WIDTH,
            CHIP8_SCREEN_HEIGHT,
            SDL_LOGICAL_PRESENTATION_LETTERBOX);

   Chip8_Init(&ctx->emulator);

   ctx->time.in_accumulator = 0;
   ctx->time.tm_accumulator = 0;
   ctx->time.last = 0;
   ctx->is_running = false;
}

void Chip8_UpdateContext(Chip8_Context *ctx);
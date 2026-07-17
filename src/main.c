#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */

#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "chip8.h"
#include "chip8_screen.h"
#include "chip8_keyboard.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static chip8_t emulator;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
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
            &window, &renderer)) {
            SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(
            renderer,
            CHIP8_SCREEN_WIDTH,
            CHIP8_SCREEN_HEIGHT,
            SDL_LOGICAL_PRESENTATION_LETTERBOX);

    chip8_init(&emulator);
    chip8_draw_sprite(&emulator.screen, 63, 10, emulator.memory.memory, 5);
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    switch (event->type) {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
    case SDL_EVENT_KEY_DOWN:
        break;
    case SDL_EVENT_KEY_UP:
        break;
    }
    
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, SDL_ALPHA_OPAQUE);
    
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 250, 250, 250, SDL_ALPHA_OPAQUE);
   
    for (int x = 0; x < CHIP8_SCREEN_WIDTH; x++) {
        for (int y = 0; y < CHIP8_SCREEN_HEIGHT; y++) {
            if (chip8_pixel_is_set(&emulator.screen, x, y)) {
                SDL_FRect pixel;
                pixel.x = x;
                pixel.y = y;
                pixel.w = 1;
                pixel.h = 1;
                SDL_RenderFillRect(renderer, &pixel);
            }
        }
    }
    SDL_RenderPresent(renderer);

    static uint64_t last_time = 0;
    static float timer_accumulator = 0.0f;
    static uint64_t frame_counter = 0;
    static uint64_t seconds_elapsed = 0;

    if (last_time == 0)
        last_time = SDL_GetTicks(); // SDL_GetTicks() returns milliseconds

    uint64_t current_time = SDL_GetTicks();
    float delta_time = (float)(current_time - last_time);
    last_time = current_time;

    timer_accumulator += delta_time;

    while (timer_accumulator >= CHIP8_TICK_RATE) {
        if (emulator.registers.delay_timer > 0) {
            emulator.registers.delay_timer--;
        }

        if (emulator.registers.sound_timer > 0) {
            emulator.registers.sound_timer--;
        }

        timer_accumulator -= CHIP8_TICK_RATE;

        frame_counter++;
        if (frame_counter >= 60) {
            seconds_elapsed++;
            printf("%d seconds elapsed\n", seconds_elapsed);
            frame_counter = 0;
        }
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Chip8_emulator.h"
#include "Chip8_display.h"
#include "Chip8_keyboard.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static Chip8_Emulator emulator;

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

    Chip8_Init(&emulator);

    char *filename;
    if (argc > 1) {
        filename = argv[1];
    }
    else {
        printf("File was not provided\n");
        exit(EXIT_FAILURE);
    }
    size_t fsize = Chip8_Load(&emulator, filename);

    if (fsize == 0) {
        fprintf(stderr, "Failed to load file\n");
        exit(EXIT_FAILURE);
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    int key_toggled;

    switch (event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;

        case SDL_EVENT_KEY_DOWN:
            key_toggled = Chip8_MapKey(event->key.scancode);
            if (key_toggled != -1) {
                if (emulator.wait_for_keypress) {
                    emulator.registers.V[emulator.keypress_register] = key_toggled;
                    emulator.wait_for_keypress = false;
                }
                Chip8_KeyDown(&emulator.keyboard, key_toggled);
            }
            break;
        
        case SDL_EVENT_KEY_UP:
            key_toggled = Chip8_MapKey(event->key.scancode);
            if (key_toggled != -1) {
                Chip8_KeyUp(&emulator.keyboard, key_toggled);
            }
            break;
    }
    
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 250, 250, 250, SDL_ALPHA_OPAQUE);
    Chip8_RenderDisplay(&emulator.display, renderer);

    SDL_RenderPresent(renderer);

    /* Begin extract to Chip8_timers.h */
    static uint64_t last_time = 0;
    if (last_time == 0)
        last_time = SDL_GetTicksNS();
    
    uint64_t current_time = SDL_GetTicksNS();
    uint64_t time_delta = current_time - last_time;
    last_time = current_time;
    
    static uint64_t time_accumulator = 0;
    time_accumulator += time_delta;


    while (time_accumulator >= CHIP8_CLOCK_RATE_NS) {
        if (!emulator.wait_for_keypress) {
            uint16_t next_instruction = Chip8_Fetch(&emulator);
            Chip8_Execute(&emulator, next_instruction);
            time_accumulator -= CHIP8_CLOCK_RATE_NS;
        }
    }
    
    while (time_accumulator >= CHIP8_TIMER_RATE_NS) {
       if (emulator.registers.DT > 0) {
           emulator.registers.DT--;
       }
    // 
       if (emulator.registers.ST > 0) {
           emulator.registers.ST--;
       }
    // 
       time_accumulator -= CHIP8_TIMER_RATE_NS;
     
    }
    /* End extract */
    
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Chip8_interpreter.h"
#include "Chip8_display.h"
#include "Chip8_keyboard.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static Chip8_Emulator c8_emulator;

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

    Chip8_Init(&c8_emulator);

    char *filename;
    if (argc > 1) {
        filename = argv[1];
    }
    else {
        printf("File was not provided\n");
        exit(EXIT_FAILURE);
    }
    size_t fsize = Chip8_Load(&c8_emulator, filename);

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
                if (c8_emulator.wait_for_keypress) {
                    c8_emulator.registers.V[c8_emulator.keypress_register] = key_toggled;
                    c8_emulator.wait_for_keypress = false;
                }
                Chip8_KeyDown(&c8_emulator.keyboard, key_toggled);
            }
            break;
        case SDL_EVENT_KEY_UP:
            key_toggled = Chip8_MapKey(event->key.scancode);
            if (key_toggled != -1) {
                Chip8_KeyUp(&c8_emulator.keyboard, key_toggled);
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
   
    /* TODO: Extract this loop to C8_DrawScreen() */
    for (int x = 0; x < CHIP8_SCREEN_WIDTH; x++) {
        for (int y = 0; y < CHIP8_SCREEN_HEIGHT; y++) {
            if (Chip8_PixelIsSet(&c8_emulator.screen, x, y)) {
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
    static uint64_t time_accumulator = 0;

    if (last_time == 0)
        last_time = SDL_GetTicksNS(); // SDL_GetTicksNS() returns nanoseconds

    uint64_t current_time = SDL_GetTicksNS();
    uint64_t time_delta = current_time - last_time;
    last_time = current_time;

    time_accumulator += time_delta;

    while (time_accumulator >= CHIP8_CLOCK_RATE_NS) {
        if (!c8_emulator.wait_for_keypress) {
            uint16_t next_instruction = Chip8_Fetch(&c8_emulator);
            Chip8_Execute(&c8_emulator, next_instruction);
            time_accumulator -= CHIP8_CLOCK_RATE_NS;
        }
    }
    
    // while (timer_accumulator >= CHIP8_TIMER_RATE) {
    //     if (c8_emulator.registers.DT > 0) {
    //         c8_emulator.registers.DT--;
    //     }
        
    //     if (c8_emulator.registers.ST > 0) {
    //         c8_emulator.registers.ST--;
    //     }
        
    //     timer_accumulator -= CHIP8_TIMER_RATE;
        
    //     frame_counter++;
    //     if (frame_counter >= 20) {
    //         seconds_elapsed++;
    //         uint16_t opcode = Chip8_Fetch(&c8_emulator);
    //         printf("Next opcode: 0x%x\n", opcode);
    //         frame_counter = 0;
    //     }
    // }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}
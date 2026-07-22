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
#include "Chip8_context.h"

static Chip8_Context context;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    Chip8_InitializeContext(&context);

    char *filename;
    if (argc > 1) {
        filename = argv[1];
    }
    else {
        printf("File was not provided\n");
        exit(EXIT_FAILURE);
    }
    size_t fsize = Chip8_Load(&context.emulator, filename);

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
                if (context.emulator.wait) {
                    context.emulator.registers.V[context.emulator.keypress_register] = key_toggled;
                    context.emulator.wait = false;
                }
                Chip8_KeyDown(&context.emulator.keyboard, key_toggled);
            }
            break;
        
        case SDL_EVENT_KEY_UP:
            key_toggled = Chip8_MapKey(event->key.scancode);
            if (key_toggled != -1) {
                Chip8_KeyUp(&context.emulator.keyboard, key_toggled);
            }
            break;
    }
    
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    
    SDL_SetRenderDrawColor(context.renderer, 10, 10, 10, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(context.renderer);

    SDL_SetRenderDrawColor(context.renderer, 250, 250, 250, SDL_ALPHA_OPAQUE);
    Chip8_RenderDisplay(&context.emulator.display, context.renderer);

    SDL_RenderPresent(context.renderer);

    Chip8_UpdateContext(&context);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}
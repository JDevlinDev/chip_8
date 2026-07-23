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
#include "Chip8_appState.h"

static Chip8_AppState app;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    Chip8_InitializeApp(&app);

    char *filename;
    if (argc > 1) {
        filename = argv[1];
    }
    else {
        printf("File was not provided\n");
        exit(EXIT_FAILURE);
    }
    size_t fsize = Chip8_Load(&app.emulator, filename);

    if (fsize == 0) {
        fprintf(stderr, "Failed to load file\n");
        exit(EXIT_FAILURE);
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    int key;

    switch (event->type) {
        case SDL_EVENT_QUIT:
            SDL_DestroyAudioStream(app.emulator.audio.stream);
            return SDL_APP_SUCCESS;

        case SDL_EVENT_KEY_DOWN:
            key = Chip8_MapKey(event->key.scancode);
            if (key != -1) {
                Chip8_KeyDown(&app.emulator.keyboard, key);
            }
            break;
        
        case SDL_EVENT_KEY_UP:
            key = Chip8_MapKey(event->key.scancode);
            if (key != -1) {
                Chip8_KeyUp(&app.emulator.keyboard, key);
            }
            break;
    }
    
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    Chip8_UpdateClock(&app);
    
    SDL_SetRenderDrawColor(app.renderer, 10, 10, 10, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(app.renderer);

    SDL_SetRenderDrawColor(app.renderer, 250, 250, 250, SDL_ALPHA_OPAQUE);
    Chip8_RenderDisplay(&app.emulator.display, app.renderer);

    SDL_RenderPresent(app.renderer);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}
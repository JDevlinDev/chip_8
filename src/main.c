#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */

#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "chip8.h"
#include "chip8_keyboard.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static chip8_keyboard_t keyboard;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("Chip8 Renderer", "1.0", "com.jdevs.chip8");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer(
            CHIP8_WINDOW_TITLE,
            CHIP8_DISPLAY_WIDTH,
            CHIP8_DISPLAY_HEIGHT,
            SDL_WINDOW_RESIZABLE,
            &window, &renderer)) {
            SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(
            renderer,
            CHIP8_WINDOW_WIDTH,
            CHIP8_WINDOW_HEIGHT,
            SDL_LOGICAL_PRESENTATION_LETTERBOX);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    switch (event->type) {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
    case SDL_EVENT_KEY_DOWN:
        int keyPressed = chip8_keyboard_map(event->key.key);
        chip8_keyboard_down(&keyboard, keyPressed);
        if (chip8_keyboard_is_down(&keyboard, keyPressed))
            printf("%d was pressed\n", keyPressed);
        break;
    case SDL_EVENT_KEY_UP:
        int keyReleased = chip8_keyboard_map(event->key.key);
        chip8_keyboard_up(&keyboard, keyReleased);
        if(!chip8_keyboard_is_down(&keyboard, keyReleased))
            printf("%d was released\n", keyReleased);
        break;
    }
    
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    SDL_FRect rect1, rect2;

    SDL_SetRenderDrawColor(renderer, 66, 66, 66, SDL_ALPHA_OPAQUE);
    
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    rect1.x = 0;
    rect1.y = 0;
    rect1.w = 10;
    rect1.h = 10;
    rect2.x = 54;
    rect2.y = 0;
    rect2.w = 10;
    rect2.h = 10;
    SDL_RenderFillRect(renderer, &rect1);
    SDL_RenderFillRect(renderer, &rect2);

    /* put the newly-cleared rendering on the screen. */
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}
#include <stdint.h>
#include <stdbool.h>

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

#include <chip8.h>

typedef struct chip8_context {
    // Core Emulator
    chip8_t      emulator;
    char         rom_filepath[256];
    bool         is_running;

    // Timing
    uint64_t     clock_rate_ns;
    uint64_t     timer_rate_ns;
    uint64_t     time_accumulator;

    // Statistics
    uint64_t     instructions_executed;
    uint64_t     frames_rendered;
    float        current_fps;

    // Frontend
    SDL_Window   *window;
    SDL_Renderer *renderer;
} chip8_context_t;
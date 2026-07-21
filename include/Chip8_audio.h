#pragma once

#include <SDL3/SDL_audio.h>

#define CHIP8_AUDIO_BUFFER_SIZE     735
#define CHIP8_AUDIO_SAMPLE_RATE     44100
#define CHIP8_AUDIO_FREQ            440
#define CHIP8_AUDIO_PERIOD          CHIP8_AUDIO_SAMPLE_RATE / CHIP8_AUDIO_FREQ

typedef struct Chip8_Audio {
   
   SDL_AudioStream     *stream;
   bool                 is_playing;
   uint8_t              buffer[CHIP8_AUDIO_BUFFER_SIZE];
} Chip8_Audio;

void Chip8_InitializeAudio(Chip8_Audio *audio);
void Chip8_PlayBeep(Chip8_Audio *audio);
void Chip8_PauseBeep(Chip8_Audio *audio);
bool Chip8_IsAudioPlaying(Chip8_Audio *audio);
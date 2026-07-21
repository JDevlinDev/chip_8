#include <stdint.h>
#include <stdio.h>

#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_error.h>

#include "Chip8_audio.h"

void Chip8_InitializeAudio(Chip8_Audio *audio)
{
   SDL_AudioSpec spec = {
    .format = SDL_AUDIO_U8,
    .channels = 1,
    .freq = 44100
   };

   audio->stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
   
   if (!audio->stream) {
      fprintf(stderr, "Audio Driver Error: %s\n", SDL_GetError());
      return;
   }

   for (int i = 0; i < CHIP8_AUDIO_BUFFER_SIZE; i++) {
      audio->buffer[i] = ((i / (CHIP8_AUDIO_PERIOD / 2)) % 2) ? 140 : 110;
   }
}

bool Chip8_IsAudioPlaying(Chip8_Audio *audio)
{
   return audio->is_playing;
}

void Chip8_PlayBeep(Chip8_Audio *audio)
{
   SDL_PutAudioStreamData(audio->stream, audio->buffer, CHIP8_AUDIO_BUFFER_SIZE);
   SDL_ResumeAudioStreamDevice(audio->stream);
   audio->is_playing = true;
}

void Chip8_PauseBeep(Chip8_Audio *audio)
{
   SDL_PauseAudioStreamDevice(audio->stream);
   audio->is_playing = false;
}
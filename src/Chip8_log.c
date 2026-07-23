#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#include <SDL3/SDL_time.h>
#include <SDL3/SDL_stdinc.h>

static FILE *log_file = NULL;

void Chip8_InitializeLog(const char* game_name)
{
   SDL_Time time_ns;
   SDL_DateTime time_bd;

   char time_string[128];
   char file_name[256];

   if (SDL_GetCurrentTime(&time_ns) && SDL_DateTimeToTime(&time_bd, &time_ns)) {
      // Construct the time string in format DD-MM-YY_HH-MM-SS
      snprintf(time_string, sizeof(time_string), "%02d-%02d-%02d_%02d-%02d-%02d",
         time_bd.day,
         time_bd.month,
         time_bd.year,
         time_bd.hour,
         time_bd.minute,
         time_bd.second);
   }
   else {
      // If we couldn't get the time, fall back to random number no-date_RANDNUM
      snprintf(time_string, sizeof(time_string), "no-date_%04x", SDL_rand(0xffff));
   }
   // Construct the file name string
   snprintf(file_name, sizeof(file_name), "%s_%s.log", game_name, time_string);

   errno = 0;
   log_file = fopen(file_name, "w");
   if(log_file != NULL) {
      fprintf(log_file, "--- CHIP-8 Emulator log iniitialized ---/n");
      fprintf(log_file, "%s - Started %s\n", time_string, game_name);
   }
   else {
      fprintf(stderr, "Chip8: Failed to open log\n\t%s\n", strerror(errno));
   }
}

void Chip8_WriteLog(const char *level, const char *format, ...)
{
   if (log_file == NULL) {
      fprintf(stderr, "Chip8: Log file not intialized\n");
   }

   SDL_Time time_ns;
   SDL_DateTime time_bd;

   if (SDL_GetCurrentTime(&time_ns) && SDL_DateTimeToTime(&time_bd, &time_ns)) {
      int millis = time_bd.nanosecond / 1000000;
      fprintf(log_file, "[%02d:%02d:%02d:%03d] %s ",
         time_bd.hour,
         time_bd.minute,
         time_bd.second, millis);
   }
   else {
      fprintf(log_file, "[TIME_ERR] %s ", level);
   }

   va_list args;
   va_start(args, format);
   vfprintf(log_file, format, args);
   va_end(args);

   fprintf(log_file, "\n");
   fflush(log_file);
}

void Chip8_CloseLog() {
   if (log_file != NULL) {
      fprintf(log_file, "--- Log Terminated ---\n");
      fclose(log_file);
      log_file = NULL;
   }
}
#pragma once

#include <SDL3/SDL_log.h>

#define CHIP8_LOG_LEVEL_FATAL    0
#define CHIP8_LOG_LEVEL_ERROR    1
#define CHIP8_LOG_LEVEL_WARN     2
#define CHIP8_LOG_LEVEL_INFO     3
#define CHIP8_LOG_LEVEL_DEBUG    4
#define CHIP8_LOG_LEVEL_TRACE    5


/**
 * Initializes the logging system.
 * 
 * \param[in] game_name The name of the currently running game 
 */
void Chip8_InitializeLog(const char* game_name);

/**
 * Writes a message to the log.
 * 
 * \param[in] level     The log level, should be DEBUG or ERROR
 * \param[in] format    Format string
 */
void Chip8_WriteLog(const char *level, const char *format, ...);

/**
 * Close the log and clean up.
 */
void Chip8_CloseLog();



#define LOG_FATAL(fmt, ...)   Chip8_WriteLog("[FATAL]", fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)   Chip8_WriteLog("[ERROR]", fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)    Chip8_WriteLog("[WARN]", fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)    Chip8_WriteLog("[INFO]", fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...)   Chip8_WriteLog("[DEBUG]", fmt, ##__VA_ARGS__)
#define LOG_TRACE(fmt, ...)   Chip8_WriteLog("[TRACE]", fmt, ##__VA_ARGS__)

#ifndef CHIP8_ACTIVE_LOG_LEVEL
   #define CHIP8_ACTIVE_LOG_LEVEL CHIP8_LOG_LEVEL_INFO
#endif


#if CHIP8_ACTIVE_LOG_LEVEL >= CHIP8_LOG_LEVEL_FATAL
    #define LOG_FATAL(fmt, ...) Chip8_WriteLog("[FATAL]", fmt, ##__VA_ARGS__)
#else
    #define LOG_FATAL(fmt, ...) do {} while(0)
#endif

#if CHIP8_ACTIVE_LOG_LEVEL >= CHIP8_LOG_LEVEL_ERROR
    #define LOG_ERROR(fmt, ...) Chip8_WriteLog("[ERROR]", fmt, ##__VA_ARGS__)
#else
    #define LOG_ERROR(fmt, ...) do {} while(0)
#endif

#if CHIP8_ACTIVE_LOG_LEVEL >= CHIP8_LOG_LEVEL_WARN
    #define LOG_WARN(fmt, ...) Chip8_WriteLog("[WARN]", fmt, ##__VA_ARGS__)
#else
    #define LOG_WARN(fmt, ...) do {} while(0)
#endif

#if CHIP8_ACTIVE_LOG_LEVEL >= CHIP8_LOG_LEVEL_INFO
    #define LOG_INFO(fmt, ...) Chip8_WriteLog("[INFO]", fmt, ##__VA_ARGS__)
#else
    #define LOG_INFO(fmt, ...) do {} while(0)
#endif

#if CHIP8_ACTIVE_LOG_LEVEL >= CHIP8_LOG_LEVEL_DEBUG
    #define LOG_DEBUG(fmt, ...) Chip8_WriteLog("[DEBUG]", fmt, ##__VA_ARGS__)
#else
    #define LOG_DEBUG(fmt, ...) do {} while(0)
#endif

#if CHIP8_ACTIVE_LOG_LEVEL >= CHIP8_LOG_LEVEL_TRACE
    #define LOG_TRACE(fmt, ...) Chip8_WriteLog("[TRACE]", fmt, ##__VA_ARGS__)
#else
    #define LOG_TRACE(fmt, ...) do {} while(0)
#endif
#pragma once

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

// Use these macros to call the write function
#define LOG_DEBUG(fmt, ...) Chip8_WriteLog("[DEBUG]", fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) Chip8_WriteLog("[ERROR]", fmt, ##__VA_ARGS__)
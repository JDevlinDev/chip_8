add_executable(Chip8 main.c)

target_sources(Chip8
   PRIVATE
      Chip8_emulator.c
      Chip8_stack.c
      Chip8_memory.c
      Chip8_display.c
      Chip8_keyboard.c
      Chip8_appState.c
      Chip8_audio.c
      Chip8_log.c
)

target_include_directories(Chip8
   PRIVATE
      "${CMAKE_CURRENT_SOURCE_DIR}/../include"
)

target_link_libraries(Chip8
   PRIVATE
      vendor
)
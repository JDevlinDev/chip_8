add_executable(Chip8 main.c)

target_sources(Chip8
   PRIVATE
      chip8.c
      chip8_stack.c
      chip8_memory.c
      chip8_screen.c
      chip8_keyboard.c
      chip8_context.c
)

target_include_directories(Chip8
   PRIVATE
      "${CMAKE_CURRENT_SOURCE_DIR}/../include"
)

target_link_libraries(Chip8
   PRIVATE
      vendor
)
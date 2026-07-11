cmake_minimum_required(VERSION 3.16)
project(chip_8)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# Forcefully disable JACK audio so VS Code doesn't crash on the missing header
set(SDL_JACK OFF CACHE BOOL "Disable JACK" FORCE)

add_subdirectory(third_party/SDL EXCLUDE_FROM_ALL)

add_executable(chip8 WIN32 src/main.c)

target_include_directories(chip8 PRIVATE include)

target_sources(chip8
    PRIVATE
    src/chip8_keyboard.c
    src/chip8_memory.c
    src/chip8_stack.c
)

# Link to the actual SDL3 library.
target_link_libraries(chip8 PRIVATE SDL3::SDL3)
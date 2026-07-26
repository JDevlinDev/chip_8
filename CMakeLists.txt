cmake_minimum_required(VERSION 3.24)
project(chip_8)

#TODO: Make debugging an option flag and set debug level via -D flag at runtime
set(CHIP8_ACTIVE_LOG_LEVEL 5 CACHE STRING "Set logging level 0-5")

add_subdirectory(src)
add_subdirectory(vendor)
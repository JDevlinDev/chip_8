# Modern SDL3 CHIP-8 Emulator

Yes, it's another CHIP-8 emulator. 

Welcome to the obligatory rite of passage for every aspiring systems programmer. While there are thousands of these on GitHub, this one isn't just a blind copy-paste from a tutorial. It is the byproduct of aggressively fighting the C compiler, questioning established design patterns, and figuring out how virtual hardware actually ticks under the hood. 

Built from scratch, this project is an active deep dive into systems architecture, pointer mechanics, and memory safety—because C won't protect you, so you have to protect yourself.

## Architecture & Tech Stack

* **Language:** Pure C
* **Graphics & Input:** SDL3 (specifically utilizing the modern `SDL_MAIN_USE_CALLBACKS` event loop structure)
* **Build System:** CMake 3.16
* **Environment:** Debian 13
* **Design Philosophy:** Heavily defensive programming. Features strict type safety and proper state-flag error handling instead of chaotic system panics.

## Building the Project

This project uses CMake and requires SDL3. Because the build system is configured to compile the library locally, you must explicitly clone SDL3 into a `third_party` directory before running CMake.

```bash
# Clone the repo
git clone [https://github.com/yourusername/chip_8.git](https://github.com/yourusername/chip_8.git)
cd chip_8

# Set up the third_party directory and clone SDL3
mkdir third_party
git clone [https://github.com/libsdl-org/SDL.git](https://github.com/libsdl-org/SDL.git) third_party/SDL

# Configure and build
cmake -S . -B build
cmake --build build
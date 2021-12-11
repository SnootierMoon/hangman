# Draw Plus Plus

A fun networking-base game that's a hybrid of pictionary and hangman.

## Getting Started

### Libraries for Building

- [CMake](https://cmake.org/install/)
- SDL2, SDL2_gfx, SDL2_net

### Build

1. `cmake -Bbuild` - generate build directory
2. `cmake --build build` - run the build scripts, generate the executable

### Running

After building, the executable gets created in `/build/`.

Currently, it's just a line-drawing test application. After running it, you can
draw lines by holding the left mouse button and dragging the mouse around the
screen.

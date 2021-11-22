# Draw Plus Plus

An app written C++ with SDL2 that lets you play pictionary with your friends
over the internet

## Getting Started

### Libraries for Building

- [CMake](https://cmake.org/install/)
- SDL2, SDL2_ttf, SDL2_gfx, SDL2_net - see
  [sdl2-cmake-modules](https://gitlab.com/aminosbh/sdl2-cmake-modules.git).
  Installation is platform-dependent.

### Build

1. `cmake -Bbuild` - generate build directory
2. `cmake --build build` - run the build scripts, generate the executable

### Running

After building, the executable gets created in `/build/`.

Currently, it's just a line-drawing test application. After running it, you can
draw lines by holding the left mouse button and dragging the mouse around the
screen.

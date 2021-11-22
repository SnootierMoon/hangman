# Draw Plus Plus

An app written C++ that lets you play pictionary with your friends over the
internet

## Getting Started

### Libraries for Building

- [CMake](https://cmake.org/install/)
- [raylib](https://github.com/raysan5/raylib) (downloaded automatically while building)
- [nbnet](https://github.com/nathhB/nbnet) (downloaded automatically while building)

### Build

1. `cmake -Bbuild` - generate build directory
2. `cmake --build build` - run the build scripts, generate the executable

### Running

After building, the executable gets created in `/build/`.

Currently, it's just a line-drawing test application. After running it, you can
draw lines by holding the left mouse button and dragging the mouse around the
screen.

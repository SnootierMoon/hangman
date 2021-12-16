// This file defines the prototypes for all the globally-used functions and
// includes so that they are defined everywhere.

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL2_framerate.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_net.h>
#include <iostream>
#include <sstream>
#include <vector>

#define PORT 21827

using namespace std;

// These variables are declared as 'extern' because they must only be defined
// in one file (sdl.cpp) to be linked properly.
extern SDL_Window* window;
extern SDL_Renderer* renderer;

int usage(char* argv0);
int server_run();
int client_run();
void sdl_init();
void sdl_init_window(string title);
void sdl_update();
void sdl_net_write(TCPsocket socket, string msg);
string sdl_net_read(TCPsocket socket);
string get_input(string prompt);

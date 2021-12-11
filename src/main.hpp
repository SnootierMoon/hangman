#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL2_framerate.h>
#include <SDL2/SDL_net.h>
#include <iostream>
#include <sstream>
#include <vector>

#define PORT 21827

using namespace std;

extern SDL_Window* window;
extern SDL_Renderer* renderer;

/** Print usage information
 *
 * @param argv0 the value of argv[0], the name of the executable
 *
 * @returns status code to be returned from main
 */
int usage(char* argv0);

/** Run the server
 *
 * @returns status code to be returned from main
 */
int server_run();

/** Run the client
 *
 * @returns status code to be returned from main
 */
int client_run();

/** Intialize SDL objects and subsystems
 */
void sdl_init();

/** Create the SDL window and renderer
 */
void sdl_init_window();

/** Get the SDL Renderer
 */
SDL_Renderer* sdl_renderer();

/** Write a message to a socket
 *
 * @param socket the socket to write to
 * @param msg    the message to write
 */
void sdl_net_write(TCPsocket socket, string msg);

/** Read a message from a socket
 *
 * @param socket the socket to read from
 * 
 * @returns a string with the data that was read
 */
string sdl_net_read(TCPsocket socket);

/** Get a line of input
 *
 * @param prompt a same-line prompt to give the user
 *
 * @return user-input response
 */
string get_input(string prompt);

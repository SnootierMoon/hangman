#include "main.hpp"

SDL_Window* window;
SDL_Renderer* renderer;
static FPSmanager fps;

/** Intialize SDL objects and subsystems
 */
void sdl_init()
{
    // Initialize all SDL subsystems
    SDL_Init(SDL_INIT_EVERYTHING);

    // Initialize SDL networking
    SDLNet_Init();

    SDL_initFramerate(&fps);
    SDL_setFramerate(&fps, 60);

}

/** Create the SDL window and renderer
 */
void sdl_init_window()
{
    window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 400, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
}

/** Update the window and framerate manager
 */
void sdl_update()
{
    SDL_RenderPresent(renderer);
    SDL_framerateDelay(&fps);
}

/** Write a message to a socket
 *
 * @param socket the socket to write to
 * @param msg    the message to write
 */
void sdl_net_write(TCPsocket socket, string msg) 
{
    // Send a message using the protocol: first send the number of bytes, ...
    char buffer[4];
    int length = msg.length();
    SDLNet_Write32(length, buffer);
    SDLNet_TCP_Send(socket, buffer, 4);

    // ... then, send the data.
    SDLNet_TCP_Send(socket, msg.c_str(), length);
}

/** Read a message from a socket
 *
 * @param socket the socket to read from
 * 
 * @returns a string with the data that was read
 */
string sdl_net_read(TCPsocket socket)
{
    // Receive a message using the protocol: first read the number of bytes, ...
    char buffer[4];
    int k = SDLNet_TCP_Recv(socket, buffer, 4);
    int length = SDLNet_Read32(buffer);

    if (k == 0)
    {
        return "";
    }


    // ... then, allocate memory for the data and read it, ...
    char* c_msg = new char[length + 1];
    SDLNet_TCP_Recv(socket, c_msg, length);
    c_msg[length] = 0;

    // ... finally, store it in a string and delete the allocated buffer
    string msg = c_msg;
    delete[] c_msg;

    return msg;
}


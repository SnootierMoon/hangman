#include "main.hpp"

SDL_Window* window;
SDL_Renderer* renderer;

void sdl_init()
{
    // Initialize all SDL subsystems
    SDL_Init(SDL_INIT_EVERYTHING);

    // Initialize SDL networking
    SDLNet_Init();

    FPSmanager fps;
    SDL_initFramerate(&fps);
    SDL_setFramerate(&fps, 60);

}

void sdl_init_window()
{
    window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 400, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void sdl_quit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDLNet_Quit();
    SDL_Quit();
}

void sdl_net_write(TCPsocket socket, string msg) 
{
    char buffer[4];
    int length = msg.length();

    SDLNet_Write32(length, buffer);

    SDLNet_TCP_Send(socket, buffer, 4);
    SDLNet_TCP_Send(socket, msg.c_str(), length);
}

string sdl_net_read(TCPsocket socket)
{
    char buffer[4];
    SDLNet_TCP_Recv(socket, buffer, 4);
    int length = SDLNet_Read32(buffer);

    char* c_msg = new char[length + 1];

    SDLNet_TCP_Recv(socket, c_msg, length);

    c_msg[length] = 0;

    string msg = c_msg;

    delete[] c_msg;

    return msg;
}




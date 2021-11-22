#include <SDL2/SDL.h>
#include <SDL2/SDL2_framerate.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>

SDL_Window* window;
SDL_Renderer* renderer;

bool closed = false;
int thickness = 5;

int main() 
{
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 400, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    FPSmanager fps;
    SDL_initFramerate(&fps);
    SDL_setFramerate(&fps, 60);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    while (!closed)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                closed = true;
            }
            else if (event.type == SDL_MOUSEMOTION)
            {
                SDL_MouseMotionEvent motion = event.motion;
                bool is_motion = motion.xrel || motion.yrel;
                bool left_mouse_down = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_LMASK;
                if (is_motion && left_mouse_down)
                {
                    thickLineRGBA(
                            renderer,
                            motion.x - motion.xrel, motion.y - motion.yrel,
                            motion.x, motion.y,
                            thickness * 2,
                            0, 0, 0, 255
                    );
                    filledCircleRGBA(
                            renderer,
                            motion.x - motion.xrel, motion.y - motion.yrel,
                            thickness,
                            0, 0, 0, 255
                    );
                    filledCircleRGBA(
                            renderer,
                            motion.x, motion.y,
                            thickness,
                            0, 0, 0, 255
                    );
                }
            }
            else if (event.type == SDL_MOUSEWHEEL)
            {
                thickness += event.wheel.y;
                thickness = std::min(std::max(thickness, 0), 30);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_framerateDelay(&fps);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

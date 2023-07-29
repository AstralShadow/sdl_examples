/* This example will demonstrate event handling */
#include <SDL2/SDL.h>

const int window_width = 800;
const int window_height = 600;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;


int main(int argc, char** argv)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("%s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(
        "My window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        window_width,
        window_height,
        0
    );
    if(window == NULL) {
        SDL_Log("%s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(renderer == NULL) {
        SDL_Log("%s\n", SDL_GetError());
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black, #000000


    int running = 1;
    while(running) {
        SDL_Event event;

        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;

                case SDL_MOUSEMOTION:
                    {
                        SDL_MouseMotionEvent event2 = event.motion;
                        int green = event2.x * 256 / window_width;
                        int blue = event2.y * 256 / window_height;
                        SDL_SetRenderDrawColor(renderer, 0, green, blue, 255);
                    }
                    break;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }


    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();

    return 0;
}


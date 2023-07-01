/* This example will create a window and close it after 5 seconds. */
#include <SDL2/SDL.h>


SDL_Window* window = NULL;


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
        800,
        600,
        0
    );
    if(window == NULL) {
        SDL_Log("%s\n", SDL_GetError());
        return 1;
    }


    SDL_Delay(5000);


    if(window) {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    SDL_Quit();

    return 0;
}


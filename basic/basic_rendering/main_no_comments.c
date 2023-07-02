/* This example will render a few shapes on a window and close it after 5 seconds. */
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

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);


    SDL_Point center;
    center.x = window_width / 2;
    center.y = window_height / 2;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawPoint(renderer, center.x, center.y);


    SDL_Point p1 = {0, 100};
    SDL_Point p2 = {window_width, 100};

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);


    SDL_Rect rect1;
    rect1.x = 100;
    rect1.y = 150;
    rect1.w = 150;
    rect1.h = 100;

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &rect1);


    SDL_Rect rect2;
    rect2.y = rect1.y;
    rect2.w = rect1.w;
    rect2.h = rect1.h;

    rect2.x = window_width - rect2.w - rect1.x;

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &rect2);


    SDL_RenderPresent(renderer);


    SDL_Delay(5000);


    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();

    return 0;
}


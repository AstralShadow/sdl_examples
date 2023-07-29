/* This example will demonstrate event handling
 * 
 * It builds on the source code from the previous examples.
 * 
 * We will use SDL's event API:
 *     https://wiki.libsdl.org/SDL2/CategoryEvents
 */
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

    /* Setting initial background color */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black, #000000


    /* Introducing a global application loop.
     * Our programs so far followed a simple workflow such as:
     * 
     *     start --> do some stuff --> wait some time --> close
     *
     *
     * Now we will introduce a more complex workflow:
     *                     __________________
     *                    |                  |
     *                    V                  |
     *     start --> do some stuff --> wait for input --> close
     *
     *
     * The global loop will repeatedly handle events and update the screen
     *  until the application is closed.
     *
     * We'll be using a flag to keep track when the program should stop.
     * That's usually when it receives a SDL_QUIT event.
     */
    int running = 1;
    while(running) {
        /* Handling events */

        /* We need an SDL_Event to store the event we will handle.
         *
         * SDL_Event is a union that contains all SDL event types.
         * It also has the special field `type` that is used
         *  to find the type of the event it stores.
         *
         * More info: https://wiki.libsdl.org/SDL2/SDL_Event
         */
        SDL_Event event;


        /** SDL_PollEvent checks if there are any events in the event queue.
         * The event queue is where SDL stores all events that have yet to be
         *  processed in the program such as mouse events and keyboard events.
         *
         * Returns 1 if there is a pending event or 0 if there are none available.
         *
         * It takes one argument of type SDL_Event* and stores the next event in
         *  the event queue in the pointed memory.
         * If called with NULL the function only returns if there are pending events
         *  and does not remove the next event from the queue.
         *
         * When using SDL_PollEvent as a condition in a while loop we can
         *  handle all pending events and onle then proceed to update the screen.
         *
         * More info: https://wiki.libsdl.org/SDL2/SDL_PollEvent
         */
        while(SDL_PollEvent(&event)) {
            switch(event.type) {

                /* Handling Quit event.
                 * This event is received when the user clicks the close button,
                 *  Alt+F4 or anything that is supposed to close the window.
                 */
                case SDL_QUIT:
                    running = 0;
                    break;

                /* We'll change the screen color when the user moves the mouse 
                 * The color will be selected based on the position of the mouse
                 */
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


        /* Rendering */
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }


    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();

    return 0;
}


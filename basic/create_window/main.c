/* This example will create a window and close it after 5 seconds.
 *
 * Note:
 *     Some graphics systems (ex. Wayland on Linux)
 *     will not render a window that has nothing rendered in it.
 *     In that case the application will seem to just sleep for 5 seconds.
 *
 *     If that's the case for you i recommend you to
 *     read this file and proceed to the next example.
 */

#include <SDL2/SDL.h>


/* Global application data
 * A SDL_Window pointer to store our window handle.
 *
 * You should always initialize pointers that don't point to an object with NULL
 * Order of initialization for global variables is not determined,
 *  so we can't set any value here.
 * We'll create the window later.
 */
SDL_Window* window = NULL;
/* A more detailed example of what can go wrong.
 * Let's say you create your window here like this:
 *
 * SDL_Window* window = SDL_CreateWindow(...);
 *     or any function that calls SDL_*
 *
 * This will run before the program enters main() and before the call to SDL_Init.
 * Then SDL will try to create a window before it initializes and will fail.
 * That's why you want your global variables to be NULL
 *  until you initialize SDL and then initialize them.
 */

int main(int argc, char** argv)
{

    /* Initialize SDL.
     * You should do this before using any SDL functions.
     *
     * Arguments: flags of which subsystems to initialize.
     *
     * Returns: 0 on success, negative number on failure.
     * 
     * More info: https://wiki.libsdl.org/SDL2/SDL_Init
     */
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {

        /* Print SDL error to standard output (console)
         * The function is similar to printf in <stdio.h>
         *
         * Arguments:
         *     Format string with tokens
         *         %s means a C-style string (that will be passed as argument)
         *         \n means a new line
         *     A value argument for every format token
         *         In our case we provide the error message from SDL_GetError()
         *         which will be placed at the position of %s
         *
         * More info: https://wiki.libsdl.org/SDL2/SDL_Log
         * Format info: https://en.cppreference.com/w/c/io/fprintf
         *
         *
         * Note:
         *     You can use printf from stdio.h or std::cout from iostream.
         *
         *     SDL_Log provides you a logging system with log levels.
         *     You can pick which messages to be logged with SDL_LogSetAllPriority()
         *     More info: https://wiki.libsdl.org/SDL2/CategoryLog
         */
        SDL_Log("%s\n", SDL_GetError());

        return 1; // Non-zero means that the program finished with error
    }


    /* Creating a window
     *
     * Arguments:
     *     window title,
     *     window x position,
     *     window y position,
     *     window width,
     *     window height,
     *     flags
     *
     * Returns: pointer to SDL_Window or NULL on error
     *
     * More info: https://wiki.libsdl.org/SDL2/SDL_CreateWindow
     */
    window = SDL_CreateWindow(
        "My window",
        SDL_WINDOWPOS_UNDEFINED, // let the operating system decide
        SDL_WINDOWPOS_UNDEFINED,
        800,
        600,
        0 // no flags
    );

    if(window == NULL) {
        SDL_Log("%s\n", SDL_GetError());
        return 1;
    }


    /* Sleep for 5000 milliseconds (5 seconds) */
    SDL_Delay(5000);


    if(window != NULL) {
        SDL_DestroyWindow(window);

        /* The window pointer points to where the window was residing in memory.
         * The pointer should be set to NULL to prevent use by mistake.
         * This if(){} block is an example of how this works.
         */

        window = NULL;
    }


    /* Shut down all SDL subsystems
     *
     * More info: https://wiki.libsdl.org/SDL2/SDL_Quit
     */
    SDL_Quit();


    return 0; // Program finished without error
}


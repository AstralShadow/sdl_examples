/* This example will render a few shapes on a window and close it after 5 seconds.
 * 
 * It builds on the source code from the previous example.
 * 
 * We will use SDL's rendering API:
 *     https://wiki.libsdl.org/SDL2/CategoryRender
 */
#include <SDL2/SDL.h>

/* Defining window size as constants.
 * Will be used on multiple places.  */
const int window_width = 800;
const int window_height = 600;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL; // Adding a renderer pointer


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
        window_width, // using constants for window size
        window_height,
        0
    );
    if(window == NULL) {
        SDL_Log("%s\n", SDL_GetError());
        return 1;
    }


    /* Create a Renderer for our window
     *
     * Arguments:
     *     window - the window where rendering is displayed
     *     index - the index of the rendering driver to initialize,
     *             or -1 to initialize the first one supporting the requested flags
     *     flags
     *
     * Returns: pointer to SDL_Renderer or NULL on error
     *
     * More info: https://wiki.libsdl.org/SDL2/SDL_CreateRenderer
     */
    renderer = SDL_CreateRenderer(window, -1, 0);
    if(renderer == NULL) {
        SDL_Log("%s\n", SDL_GetError());
        return 1;
    }


    /* Clear the screen with specific color. */

    /* SDL_SetRenderDrawColor sets the selected RGB color (with Alpha channel)
     * Arguments:
     *     pointer to SDL_Renderer,
     *     red,
     *     green,
     *     blue,
     *     alpha
     *
     * Note:
     *     The Alpha value is often used for opacity, 255 means fully visible.
     *     You can define how alpha should be used with SDL_SetRenderDrawBlendMode()
     *     A good use case is if you want to render something semi-transparent.
     *
     * More info: https://wiki.libsdl.org/SDL2/SDL_SetRenderDrawColor
     */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black, #000000

    /* SDL_RenderClear fills the window with the selected color.
     *
     * Note: All rendering related functions take SDL_Renderer* as first argument
     *
     * More info: https://wiki.libsdl.org/SDL2/SDL_RenderClear
     */
    SDL_RenderClear(renderer);


    /* Rendering in 2D uses a coordinate system.
     * Every point on the window has a horizontal position and vertical position.
     * This applies to computer screens in general.
     * You can think of the window you create as your application's screen.
     *
     * X and Y are commonly used ascoordinate axis,
     *      X is horizontal and Y is vertical.
     *
     * The point with x=0 and y=0 is at the top-left edge of the window.
     * When x is increased, the point goes right.
     * When y is increased, the point goes down.
     * 
     * SDL provides a few structures to represent points and rectangles:
     *     SDL_Point    https://wiki.libsdl.org/SDL2/SDL_Point
     *     SDL_FPoint   https://wiki.libsdl.org/SDL2/SDL_FPoint
     *     SDL_Rect     https://wiki.libsdl.org/SDL2/SDL_Rect
     *     SDL_FRect    https://wiki.libsdl.org/SDL2/SDL_FRect
     *
     * The SDL_F* structures use floating point numbers instead integers.
     * All of the used rendering functions have versions that use floats.
     * They have the same name and a letter 'F' as appendix to it. Examples:
     *     SDL_RenderDrawPoint()   =>  SDL_RenderDrawPointF()
     *     SDL_RenderDrawPoints()  =>  SDL_RenderDrawPointsF()
     *     SDL_RenderDrawLine()    =>  SDL_RenderDrawLineF()
     *     SDL_RenderDrawRect()    =>  SDL_RenderDrawRectF()
     */

    /* Calculating the center of the window */
    SDL_Point center;
    center.x = window_width / 2;
    center.y = window_height / 2;


    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red, #ff0000
    /* Render a single red point (pixel) at the center of the window.
     * The SDL_RenderDrawPoint draws a single point.
     * When drawing multiple points it's easier to use
     *  SDL_RenderDrawPoints which takes an array of points.
     *
     * If we render anything that covers the center later
     *  our red dot will get covered and we won't see it.
     */
    SDL_RenderDrawPoint(renderer, center.x, center.y);


    /* Creating 2 new points to render a green line connecting them.
     * This will be a horizontal line at 100px (pixels) from the top of the window.
     */
    SDL_Point p1 = {0, 100};
    SDL_Point p2 = {window_width, 100};

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green, #00ff00

    /* Arguments: renderer, x1, y1, x2, y2 coordinates
     * 
     * Note: When drawing multiple lines you may use SDL_RenderDrawLines
     *
     * More info: https://wiki.libsdl.org/SDL2/SDL_RenderDrawLine
     */
    SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);


    /* Create a rectangle
     *
     * Rectangles are represented using their top-left edge, their width and height
     */
    SDL_Rect rect1;
    rect1.x = 100;
    rect1.y = 150;
    rect1.w = 150;
    rect1.h = 100;

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // yellow, #ffff00

    /* Draws the outline of a rectangle.
     *
     * This function takes a pointer to SDL_Rect.
     * rect1 is a local variable and &rect1 will give us the pointer to it.
     *
     * Note:
     *     Be careful when using pointers to local variables!
     *     They become dangling pointers when you leave the function that defines them.
     *     Dangling pointers point to where data used to be, but is no more.
     *     They cause a lot of issues for a lot of people.
     */
    SDL_RenderDrawRect(renderer, &rect1);


    /* Create another rect that is at the opposite (horizontal) side of the screen */
    SDL_Rect rect2;
    rect2.y = rect1.y; // same vertical position
    rect2.w = rect1.w; // same size
    rect2.h = rect1.h;
    rect2.x = window_width   // Start with screen width (rect2 is outside the screen)
               - rect2.w     // Move the rect in the window (touches the right edge)
               - rect1.x;    // Add the same margin that rect1 has
                             //     The margin should be in the opposite direction of
                             //     the one that rect1 has, so we invert it.


    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // blue, #0000ff

    /* Fills the area of rect2 */
    SDL_RenderFillRect(renderer, &rect2);


    /* When you finish with rendering you have to call SDL_RenderPresent
     * This function will display all of the changes you did to the screen.
     * Not calling this function will result nothing being shown in the window.
     *
     * If you call it after the 5 seconds delay you won't see anything on the screen
     *  because the application will wait 5s, then render and close immediately.
     */
    SDL_RenderPresent(renderer);


    SDL_Delay(5000);


    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();

    return 0;
}


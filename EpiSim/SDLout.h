#include <SDL.h>
#include <vector>

//Setup SDL Globals
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;

//Global data
std::vector<std::vector<int>> data;

void init()
{

    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);

}

void quit(bool* quitting) {
    SDL_DestroyWindow(window);
    SDL_Quit();
    *quitting = true;
}

void loop(bool* quitting) {
    SDL_WaitEvent(&event);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawPoint(renderer, 400, 300); //Renders on middle of screen.
    SDL_RenderPresent(renderer);
    switch (event.type)
    {
    case SDL_QUIT:
        quit(quitting);
    }
}
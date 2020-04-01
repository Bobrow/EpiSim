
#include <SDL.h>
#include <vector>
#include "log.h"

//Setup SDL Globals
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;

//Global data
std::vector<std::pair<int,int>> globdata;

int lerp(int a, int b, float t, float max) {
    t /= max;
    return (1 - t) * a + t * b;
}

void SDLinit()
{

    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);

}

void quit(bool* quitting) {
    SDL_DestroyWindow(window);
    SDL_Quit();
    *quitting = true;
}

void SDLloop(bool* quitting, int area[2]) {
    SDL_WaitEvent(&event);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = 0; i < globdata.size(); i++) {
        int lerped_x = lerp(0, 800, globdata[i].first, area[0]*10);
        int lerped_y = lerp(0, 600, globdata[i].second, area[1]*10);
        SDL_RenderDrawPoint(renderer, lerped_x, lerped_y); //Renders a dot for each person
    }
    SDL_RenderPresent(renderer);
    switch (event.type)
    {
    case SDL_QUIT:
        quit(quitting);
    }
    SDL_Delay(100);
}
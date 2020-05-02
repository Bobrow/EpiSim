#ifdef _WIN64
#include <SDL.h>
#elif __linux__
#include <SDL2/SDL.h>
#else
#error Platform Not Supported
#endif
#include <vector>
#include "log.h"
#include <string>

//Setup SDL Globals
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;
//Global data
std::vector<std::vector<int>> globdata;
int targetFps = 240;

int lerp(int a, int b, float t, float max) {
    t /= max;
    return (1 - t) * a + t * b;
}

void quit(bool* quitting) {
    SDL_DestroyWindow(window);
    SDL_Quit();
    *quitting = true;
}

void handleKeyPresses(bool* quitting) {
    while (SDL_PollEvent(&event) != 0)
    {
        //User requests quit
        if (event.type == SDL_QUIT)
        {
            quit(quitting);
        }
        //User presses a key
        else if (event.type == SDL_KEYDOWN)
        {
            //Select surfaces based on key press
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
                targetFps += 1;
                break;

            case SDLK_DOWN:
                targetFps -= 1;
                break;

            }
        }
    }
}

void SDLinit()
{

    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);

}

void SDLloop(bool* quitting, int area[2]) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    handleKeyPresses(quitting);
    for (int i = 0; i < globdata.size(); i++) {
        int lerped_x = globdata[i][0];
        int lerped_y = globdata[i][1];
        logger::log(0, 0, std::to_string(globdata[i][0])+" "+std::to_string(globdata[i][1]));
        switch (globdata[i][2]) {
            case 0:
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 127);
                break;
            case 1:
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                break;
            case 2:
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                break;
            case 3:
                SDL_SetRenderDrawColor(renderer, 127, 127, 127, 127);
                break;
        }
        SDL_RenderDrawPoint(renderer, lerped_x, lerped_y); //Renders a dot for each person
    }
    SDL_RenderPresent(renderer);
}
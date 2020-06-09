#pragma once
#include "renderer.h"
#ifdef _WIN32
#include <SDL.h>
#elif __linux__
#include <SDL2/SDL.h>
#else
#error Platform Not Supported
#endif

class SDLRenderer :
    public renderer
{
public:
	bool init(int x, int y, int population) override;
	void draw_dot(int x, int y, int size, int *color) override;
	int draw_state(std::vector<std::vector<int>> state) override;
	void destroy() override;
private:
	bool destroyed = false;
	void CheckInput();
	int i_population;
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Event event;
};


#include "SDLRenderer.h"

bool SDLRenderer::init(int x, int y, int population)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(x, y, 0, &window, &renderer);
	return true;
}

void SDLRenderer::draw_dot(int x, int y, int size, int color[4])
{
	SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
	SDL_RenderDrawPoint(renderer, x, y);
}

void SDLRenderer::draw_state(std::vector<std::vector<int>> state)
{
	for (auto elem : state) {
		std::vector<int> color;
		switch (elem[2])
		{
		case 0:
			color = { 0,255,0,127 };
			break;
		case 1:
			color = { 255,0,0,255 };
			break;
		case 2:
			color = { 255,255,0,255 };
			break;
		case 3:
			color = { 127,127,127,127 };
			break;
		default:
			color = { 0,0,0,0 };
			break;
		}
		draw_dot(elem[0], elem[1], 1, color.data());
	}
	SDL_RenderPresent(renderer);
}

void SDLRenderer::destroy()
{
	SDL_Quit();
}


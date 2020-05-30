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

int SDLRenderer::draw_state(std::vector<std::vector<int>> state)
{
	CheckInput();
	if (!destroyed) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
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
		return 0;
	}
	else
	{
		return 1;
	}
}

void SDLRenderer::destroy()
{
	SDL_Quit();
	destroyed = true;
}

void SDLRenderer::CheckInput()
{
	while (SDL_PollEvent(&event) != 0)
	{
		//User requests quit
		if (event.type == SDL_QUIT)
		{
			destroy();
		}
		//User presses a key
		/*else if (event.type == SDL_KEYDOWN)
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
		}*/
	}
}

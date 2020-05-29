#include "randomGen.h"
#include "SDLRenderer.h"
#include <chrono>
#include <thread>
#include "log.h"

#undef main
int main()
{
	SDLRenderer rend;
	bool ret = rend.init(800, 600, 400);
	if (!ret)
	{
		logger::log(3,0,"GL Init failed :(");
	}
	std::vector<std::vector<int>> state;
	randomGen rand;
	state.resize(400);
	rand.seed(rand.taus);
	while (true) {
		for (int i = 0; i<400;i++)
		{
			std::vector<int> temp = { (int)rand.nextBetween(0,800),(int)rand.nextBetween(0,600),(int)rand.nextBetween(0,3) };
			state[i] = temp;
		}
		rend.draw_state(state);
	}
	rend.destroy();
	return 0;
}
#pragma once
#include <vector>

class renderer
{
public:
	virtual bool init(int x, int y, int population) = 0;
	virtual void draw_dot(int x, int y, int size, int *color) = 0;
	virtual int draw_state(std::vector<std::vector<int>> state) = 0;
	virtual void destroy() = 0;
private:
	bool destroyed = false;
};


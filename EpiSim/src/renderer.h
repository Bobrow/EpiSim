#pragma once
#include <vector>

class renderer
{
public:
	virtual bool init(int x, int y, int population) { return true; };
	virtual void draw_dot(int x, int y, int size, int *color) { ; };
	virtual int draw_state(std::vector<std::vector<int>> state) { return 0; };
	virtual void destroy() { ; };
private:
	bool destroyed = false;
};


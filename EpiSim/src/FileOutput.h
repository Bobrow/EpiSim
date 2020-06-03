#pragma once
#include "renderer.h"
#include <fstream>
#include <string>

class FileOutput :
    public renderer
{
public:
	bool init(int x, int y, int population) override;
	void setFolder(std::string folder);
	void draw_dot(int x, int y, int size, int* color) override;
	int draw_state(std::vector<std::vector<int>> state) override;
	void destroy() override;
private:
	int counter = 0;
	std::string i_folder = "";
};



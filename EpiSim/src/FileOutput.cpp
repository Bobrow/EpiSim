#include "FileOutput.h"

bool FileOutput::init(int x, int y, int population)
{
	return true;
}

void FileOutput::setFolder(std::string folder)
{
	i_folder = folder+"/";
}

void FileOutput::draw_dot(int x, int y, int size, int* color)
{
	;
}

int FileOutput::draw_state(std::vector<std::vector<int>> state)
{
	std::vector<int> data;
	for (auto elem : state)
	{
		data.insert(data.end(), elem.begin(), elem.end());
	}
	int* chardata = data.data();
	std::ofstream epoch;
	epoch.open(i_folder + "epoch" + std::to_string(counter) + ".eph", std::ios::out | std::ios::binary);
	epoch.write(reinterpret_cast<char*>(chardata), state.size() * 4 * sizeof(int));
	epoch.close();
	counter++;
	return 0;
}

void FileOutput::destroy()
{
	;
}




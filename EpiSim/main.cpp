//Include System Libraries
#include <string>
#include <random>
#include <vector>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <exception>
#include <stdexcept>
#include <fstream>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

//Include Boost Libraries
#include <boost/lexical_cast.hpp>

//Include Error and OpenGL Handler
#include "SDLout.h"
#include "log.h"
#include "fileparser.h"

#ifdef CUDA
#include "CUDAStateCalc.cu"
#else
#include "CPUStateCalc.h"
#endif

std::string folderName;
bool quitting = false;
vector<int> infectedPeople;
vector<int> emptyvec;

using namespace std;
vector<int> threadsDone;

vector<vector<signed int>> generateCoords(int64_t amount, int area[2], int purpose) {
	vector<vector<int>> coords;
	int modulo_x = 3;
	int modulo_y = 3;
	int minus = 1;
	if (purpose != 0) {
		modulo_x = area[0];
		modulo_y = area[1];
		minus = 0;
	}
	for (int i = 0; i < amount; i++) {
		vector<int> temp;
		temp.push_back((generator_x() % modulo_x) - minus);
		temp.push_back((generator_y() % modulo_y) - minus);
		coords.push_back(temp);
	}
	return coords;
}

vector<vector<int>> pickRandomPerson(vector<vector<int>> state, int amount = 1) {
	logger::log(0, 0, "Picking Random People");

	vector<int> person;
	for (int i = 0; i < amount; i++) {
		int temp = generator() % state.size();
		bool found = false;
		while (!found) {
			if (!(std::find(person.begin(), person.end(), temp) != person.end())) {
				found = true;
			}
			else {
				logger::log(0, 0, to_string(temp));
				temp = generator() % state.size();
			}
		}
		person.push_back(temp);
	}
	1 + 1;
	for (int i = 0; i < state.size(); i++) {
		if (std::find(person.begin(), person.end(), i) != person.end())
		{
			state[i].push_back(1);
			infectedPeople.push_back(i);
		}
		else {
			state[i].push_back(0);
		}
	}
	return state;
}

string ensureLength(int value, int length) {
	string result = to_string(value);
	if (result.size() > length) {
		throw range_error("length of input bigger than output");
	}
	while (result.size() != length) {
		result = "0" + result;
	}
	return result;
}

void writeEpochToFile(int epoch, int length=4) {
	ofstream file;
	file.open(folderName + to_string(epoch) + ".dat", ios::out | ios::binary | ios::app);
	for (int i = 0; i < finished.size(); i++) {
		for (int j = 0; j < 3; j++) {
			string temp = ensureLength(finished[i][j],length);
			file << to_string(j) + temp;
		}
	}
	file.close();
}


#undef main
int main(int argc, char *argv[], char* envp[]) {
	namespace fs = std::experimental::filesystem;
	folderName = to_string(time(NULL))+"/";
	fs::create_directory(folderName);
	emptyvec = { 0,0,0 };
	vector<pair<int, float>> parsed;
	if (argc == 1) {
		parsed = parsefile("example.xml");
	}
	else {
		parsed = parsefile(argv[1]);
	}
	generator.seed(seeder());
	generator_x.seed(seeder());
	generator_y.seed(seeder());
	int64_t population;
	int infectionradius;
	float infectionprobability;
	int removalTime;
	float walkingProbability = 100.0f;
	int alreadyInfected;
	int area[2];
	int leadIn = 0;
	int threads;
	bool SDLOutput;
	for (int i = 0; i < parsed.size(); i++) {
		pair<int, float> temp = parsed.at(i);
		switch (temp.first) {
		case 1:
			population = temp.second;
			logger::log(0, 0, "Population = " + ::to_string(population));
			break;
		case 2:
			infectionradius = temp.second;
			logger::log(0, 0, "Infection Radius = " + ::to_string(infectionradius));
			break;
		case 3:
			infectionprobability = temp.second;
			logger::log(0, 0, "Infection Probability Per Epoch when in the Infection Radius of a infected person = " + ::to_string(infectionprobability));
			break;
		case 4:
			removalTime = temp.second;
			logger::log(0, 0, "Removal Time = " + ::to_string(removalTime));
			break;
		case 5:
			walkingProbability = temp.second;
			logger::log(0, 0, "Probability of walking = " + ::to_string(walkingProbability));
			break;
		case 6:
			alreadyInfected = temp.second;
			if (alreadyInfected > population) {
				logger::log(3, 2);
			}
			logger::log(0, 0, "Amount of people already infected = " + ::to_string(alreadyInfected));
			break;
		case 7:
			area[0] = temp.second;
			break;
		case 8:
			area[1] = temp.second;
			logger::log(0, 0, "Area = X=" + ::to_string(area[0]) + ", Y=" + ::to_string(area[1]));
			break;
		case 9:
			leadIn = temp.second;
			break;
		case 10:
			threads = temp.second;
			break;
		case 11:
			if (temp.second == 1) {
				logger::debug_log(true);
			}
			else {
				logger::debug_log(false);
			}
			break;
		case 12:
			if (temp.second == 1) {
				SDLOutput = true;
			}
			else {
				SDLOutput = false;
			}
			break;
		case 13:
			folderName = to_string(temp.second) + "/";
			break;
		}
	}
	logger::log(0, 0, "Generating Random Starting State");
	vector<vector<int>> state = pickRandomPerson(generateCoords(population, area, 2), alreadyInfected);
	globdata = state;
	int i = 0;
	while (true) {
		int begin = time(NULL);
		if (quitting) {
			logger::log(3, 0, "Quitting...");
			return 3;
		}
		else {
			std::ostringstream streamObj;
			std::string unit;
			if ((0.7F * i) > 3600) {
				streamObj << (0.7f * i) / 3600;
				unit = " Hours";
			}
			else if ((0.7F * i) > 60) {
				streamObj << (0.7f * i) / 60;
				unit = " Minutes";
			}
			else {
				streamObj << 0.7f * i;
				unit = " Seconds";
			}
			globdata = state;
			if (SDLOutput) {
				if (i == leadIn) {
					SDLinit();
				}
				if (i >= leadIn) {
					SDLloop(&quitting, area);
				}
			}
			logger::log(0, 0, "Epoch " + to_string(i) + " Aproximately " + streamObj.str() + unit);
			finished.clear();
			finished.reserve(population);
			for (int i = 0; i < population; i++) {
				finished.push_back(emptyvec);
			}
			
			calculateNextState(&state, area, infectedPeople, infectionradius, infectionprobability, threads);
			writeEpochToFile(i);
			/*while (threadsDone.size() != threads);
			threadsDone.clear();*/
			state = finished;
			int totalTime = time(NULL) - begin;
			if (totalTime < (1000 / targetFps)) {
#ifdef _WIN64
				Sleep((1000 / targetFps) - totalTime);
#elif __linux__
				sleep((1000 / targetFps) - totalTime);
#else
#error Platform Not Supported
#endif
			}
			else {
				logger::log(1, 0, "Not hitting target FPS, try lowering it");
			}
		}
		i++;
	}
	return 0;
}
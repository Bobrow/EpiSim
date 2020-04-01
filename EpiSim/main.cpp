//Include System Libraries
#include <string>
#include <random>
#include <vector>
#include <cmath>

//Include Error and OpenGL Handler
#include "SDLout.h"
#include "log.h"
#include "fileparser.h"

bool quitting = false;

vector<pair<signed int, signed int>> generateCoords(int amount, int area[2], int purpose) {
	vector<pair<int, int>> coords;
	default_random_engine generator_x;
	default_random_engine generator_y;
	random_device seeder;
	generator_x.seed(seeder());
	generator_y.seed(seeder());
	int offset = 20;
	int minusoffset = 10;
	int divideoffset = 10;
	if (purpose != 0) {
		offset = 10;
		minusoffset = 0;
		divideoffset = 1;
	}
	for (int i = 0; i < amount; i++) {
		pair<signed int, signed int> temp;
		temp.first = (generator_x() % (area[0] * offset) - minusoffset) / divideoffset;
		temp.second = (generator_y() % (area[1] * offset) - minusoffset) / divideoffset;
		coords.push_back(temp);
	}
	return coords;
}

vector<pair<signed int, signed int>> calculateNextState(vector<pair<signed int, signed int>> lastState, int area[2]) {
	int size[2] = {1,1};
	vector<pair<signed int, signed int>> offsets = generateCoords(lastState.size(), size, 0);
	vector<pair<int, int>> result;
	for (int i = 0; i < lastState.size(); i++) {
		pair<int, int> temppair;
		temppair.first = lastState[i].first + offsets[i].first;
		if (temppair.first > area[0]) {
			temppair.first = area[0]-1;
		}
		if (temppair.first < 0) {
			temppair.first = 0;
		}
		temppair.second = lastState[i].second + offsets[i].second;
		if (temppair.second > area[1]) {
			temppair.second = area[1]-1;
		}
		if (temppair.second < 0) {
			temppair.second = 0;
		}
		//logger::log(0, 0, to_string(offsets[i].first) + " " + to_string(offsets[i].second));
		result.push_back(temppair);
	}
	return result;
}

int main(int argc, char** argv) {
	vector<pair<int, float>> parsed = parsefile("example.xml");
	int population;
	int infectionradius;
	float infectionprobability;
	int removalTime;
	float walkingProbability;
	int alreadyInfected;
	int area[2];
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
				logger::log(0, 0, "Amount of people already infected = " + ::to_string(walkingProbability));
				break;
			case 7:
				area[0] = temp.second;
				break;
			case 8:
				area[1] = temp.second;
				logger::log(0, 0, "Area = X=" + ::to_string(area[0]) + ", Y=" + ::to_string(area[1]));
				break;
		}
	}
	logger::log(0, 0, "Generating Random Starting State");
	vector<pair<int,int>> state = generateCoords(population, area, 2);
	globdata = state;
	SDLinit();

	while (true) {
		if (quitting) {
			logger::log(3, 3);
			return 3;
		}
		else {
			globdata = state;
			state = calculateNextState(state, area);
			SDLloop(&quitting, area);
		}
	}
	return 0;
}
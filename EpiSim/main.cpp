//Include System Libraries
#include <string>
#include <random>
#include <vector>

//Include Error and OpenGL Handler
#include "SDLout.h"
#include "log.h"
#include "fileparser.h"

bool quitting = false;

vector<pair<int, int>> generateCoords(int amount, int area[2]) {
	vector<pair<int, int>> coords;
	random_device generator_x;
	random_device generator_y;
	generator_x.min = 0;
	generator_x.max = area[0] * 10;
	generator_y.min = 0;
	generator_y.min = area[1] * 10;
	for (int i = 0; i < amount; i++) {
		pair<int, int> temp;
		temp.first = generator_x();
		temp.second = generator_y();
		coords.push_back(temp);
	}
	return coords;
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

	generateCoords(population, area);

	SDLinit();

	while (true) {
		if (quitting) {
			logger::log(3, 3);
			return 3;
		}
		else {
			
			SDLloop(&quitting);
		}
	}
	return 0;
}
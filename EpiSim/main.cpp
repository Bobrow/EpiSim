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

//Include Boost Libraries
#include <boost/random.hpp>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>

//Include Error and OpenGL Handler
#include "SDLout.h"
#include "log.h"
#include "fileparser.h"

bool quitting = false;
vector<int> infectedPeople;
vector<int> emptyvec;
vector<vector<int>> finished;
using namespace std;
vector<int> threadsDone;

boost::random::mt11213b  generator;
boost::random::mt11213b  generator_x;
boost::random::mt11213b  generator_y;
random_device seeder;

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

bool infection(float infectionProbability) {
	int number = 0;
	number = generator() % 100;
	return number < infectionProbability;
}

void threaded(vector<vector<int>>* EntireLastState, int start, int end, int id, int area[2], vector<int> infectedPeople, int infectionRadius, float infectionProbability) {
	logger::log(0, 0, "Thread " + to_string(id) + " reporting for duty!");
	vector<vector<int>> offsets;
	vector<vector<int>> result;
	int size[2] = { 1,1 };
	offsets = generateCoords(end - start, size, 0);

	for (int i = 0; i != (end - start); i++) {
		vector<int> temppair;
		temppair.push_back(EntireLastState->at(i + start)[0] + offsets[i][0]);
		if (temppair[0] > area[0]) {
			temppair[0] = area[0] - 1;
		}
		if (temppair[0] < 0) {
			temppair[0] = 0;
		}
		temppair.push_back(EntireLastState->at(i + start)[1] + offsets[i][1]);
		if (temppair[1] > area[1]) {
			temppair[1] = area[1] - 1;
		}
		if (temppair[1] < 0) {
			temppair[1] = 0;
		}
		int infected = EntireLastState->at(i + start)[2];
		if (!(std::find(infectedPeople.begin(), infectedPeople.end(), i) != infectedPeople.end())) {
			for (int j = 0; j < infectedPeople.size(); j++) {
				auto distance = std::sqrt(pow((EntireLastState->at(infectedPeople[j])[0] - temppair[0]),2) + pow((EntireLastState->at(infectedPeople[j])[1] - temppair[1]),2));
				logger::log(5, 0, to_string(distance));
				if (distance < infectionRadius) {
					if (infection(infectionProbability)) {
						infected = 1;
						infectedPeople.push_back(i);
					}
				}
			}
		}
		temppair.push_back(infected);

		//logger::log(0, 0, "Person " + to_string(i + start) + " has been calculated");
		finished[i + start] = temppair;
	}
	/*int initsize = threadsDone.size();
	threadsDone.push_back(1);
	while (threadsDone.size() != (initsize + 1)) {
		threadsDone.push_back(1);
	}*/
	logger::log(0, 0, "Thread " + to_string(id) + " has finished");
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

void calculateNextState(vector<vector<int>>* lastState, int area[2], vector<int> infectedPeople, int infectionRadius, float infectionProbability, int threads) {
	vector<int> offsets;
	for (int i = 0; i < threads + 1; i++) {
		offsets.push_back(i * (lastState->size() / threads));
	}
	offsets[threads] += (lastState->size() % threads);
	//boost::thread worker(threaded, lastState, offsets[0], offsets[1]-1, 0, area, infectedPeople, infectionRadius, infectionProbability);
	boost::thread_group threadgroup;
	for (int i = 0; i < threads; i++) {
		threadgroup.create_thread(boost::bind(threaded, lastState, offsets[i], offsets[i + 1], i, area, infectedPeople, infectionRadius, infectionProbability));
	}
	threadgroup.join_all();
}
#undef main
int main(int argc, char *argv[], char* envp[]) {
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
	float walkingProbability;
	int alreadyInfected;
	int area[2];
	int leadIn;
	int threads;
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
			if (temp.first == 1) {
				logger::debug_log(true);
			}
			else {
				logger::debug_log(false);
			}
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
			if (i == leadIn) {
				SDLinit();
			}
			if (i >= leadIn) {
				SDLloop(&quitting, area);
			}
			logger::log(0, 0, "Epoch " + to_string(i) + " Aproximately " + streamObj.str() + unit);
			finished.clear();
			finished.reserve(population);
			for (int i = 0; i < population; i++) {
				finished.push_back(emptyvec);
			}
			
			calculateNextState(&state, area, infectedPeople, infectionradius, infectionprobability, threads);
			/*while (threadsDone.size() != threads);
			threadsDone.clear();*/
			state = finished;
			int totalTime = time(NULL) - begin;
			if (totalTime < (1000 / targetFps)) {
				Sleep((1000 / targetFps) - totalTime);
			}
			else {
				logger::log(1, 0, "Not hitting target FPS, try lowering it");
			}
		}
		i++;
	}
	return 0;
}
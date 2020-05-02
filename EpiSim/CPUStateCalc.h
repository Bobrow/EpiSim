#pragma once
#include <vector>
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>
std::vector<std::vector<int>> finished;
boost::random::mt11213b  generator;
boost::random::mt11213b  generator_x;
boost::random::mt11213b  generator_y;
boost::random::random_device seeder;
#include "log.h"

using namespace std;

bool infection(float infectionProbability) {
	int number = 0;
	number = generator() % 100;
	return number < infectionProbability;
}

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
				auto distance = std::sqrt(pow((EntireLastState->at(infectedPeople[j])[0] - temppair[0]), 2) + pow((EntireLastState->at(infectedPeople[j])[1] - temppair[1]), 2));
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
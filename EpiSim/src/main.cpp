//Include System Libraries
#include <vector>
#include <string>
#include <map>
#include <chrono>

//Include Boost Libraries
#include <boost/thread.hpp>

//Include logger, fileparser, rng and the renderer
#include "fileparser.h"
#include "log.h"
#include "randomGen.h"
#include "SDLRenderer.h"

#undef main

std::map<int, std::vector<int>> directions = {
	{0,{0,0}},
	{1,{0,1}},
	{2,{1,1}},
	{3,{1,0}},
	{4,{1, -1}},
	{5,{0, -1}},
	{6,{-1,-1}},
	{7,{-1, 0}},
	{8,{-1, 1}}
};

std::vector<int> infectedPeople;
std::vector<std::vector<int>> finished;

void thread_worker(vector<vector<int>>* EntireLastState, std::vector<int> work_params, int area[2], vector<int> infectedPeople, int infectionRadius, float infectionProbability, int RemovalTime, randomGen* rand)
{
	logger::log(0, 0, "Thread " + std::to_string(work_params[2]) + " started");
	for (int i = 0; i != (work_params[1] - work_params[0]); i++) {
		std::vector<int> original = EntireLastState->at(i + work_params[0]);
		std::vector<int> temp;
		std::vector<int> movement = directions[rand->nextBetween(0, 8)];
		temp.push_back(original[0] + movement[0]);
		temp.push_back(original[1] + movement[1]);
		if ((unsigned int)temp[0] > area[0])
		{
			temp[0] = area[0];
		}
		if (temp[0] > area[0])
		{
			temp[0] = 0;
		}
		if ((unsigned int)temp[1] > area[1])
		{
			temp[1] = area[1];
		}
		if (temp[1] > area[1])
		{
			temp[1] = 0;
		}
		if (original[2] >= 1 < 3)
		{
			if (RemovalTime != -1) {
				if (original[3] == 0)
				{
					temp.push_back(3);
					for (int j = 0; j < infectedPeople.size(); j++)
					{
						if (infectedPeople[j] == (i + work_params[0]))
						{
							infectedPeople.erase(infectedPeople.cbegin() + j);
							break;
						}
					}
					temp.push_back(-1);
				}
			}
			else {
				temp.push_back(original[2]);
				if (RemovalTime != -1) {
					temp.push_back(original[3] - 1);
				}
				else
				{
					temp.push_back(original[3]);
				}
			}
		}
		else
		{
			for (int j = 0; j < infectedPeople.size(); i++)
			{
				auto distance = std::sqrt(pow((EntireLastState->at(infectedPeople[j])[0] - temp[0]), 2) + pow((EntireLastState->at(infectedPeople[j])[1] - temp[1]), 2));
				if (distance > infectionRadius)
				{
					if (rand->nextBetween(1,100)<infectionProbability)
					{
						temp.push_back(1);
						temp.push_back(RemovalTime);
						infectedPeople.push_back(i+work_params[0]);
					}
				}
			}
			temp.push_back(-1);
		}
		finished[i + work_params[0]] = temp;
	}
}

std::vector<std::vector<int>> generatePeople(randomGen* rand, int population, int area[2], int infectedAlready, int infectionLength)
{
	std::vector<std::vector<int>> out;
	for (int i = 0; i < population; i++)
	{
		std::vector<int> temp = { (int)rand->nextBetween(0,area[0]),(int)rand->nextBetween(0,area[1]),0,-1 };
		out.push_back(temp);
	}
	for (int i = 0; i < infectedAlready; i++)
	{
		int person_index = rand->nextBetween(0,population - 1);
		while (out[person_index][2] == 1) {
			person_index = rand->nextBetween(0,population - 1);
		}
		out[person_index][2] = 1;
		out[person_index][3] = infectionLength;
		infectedPeople.push_back(person_index);
	}
	return out;
}

void calculateNextState(vector<vector<int>>* lastState, int area[2], vector<int> infectedPeople, int infectionRadius, float infectionProbability, int RemovalTime, int threads, randomGen* rand) {
	vector<int> offsets;
	for (int i = 0; i < threads + 1; i++) {
		offsets.push_back(i * (lastState->size() / threads));
	}
	offsets[threads] += (lastState->size() % threads);
	//boost::thread worker(threaded, lastState, offsets[0], offsets[1]-1, 0, area, infectedPeople, infectionRadius, infectionProbability);
	boost::thread_group threadgroup;
	for (int i = 0; i < threads; i++) {
		std::vector<int> work_params = { offsets[i], offsets[i + 1], i };
		threadgroup.create_thread(boost::bind(thread_worker, lastState, work_params, area, infectedPeople,
		                                      infectionRadius, infectionProbability, RemovalTime, rand));
	}
	threadgroup.join_all();
}

int main(int argc, char* argv[], char* envp[])
{
	std::vector<std::pair<int, float>> parsed;
	if (argc == 1) {
		parsed = parsefile("resources/example.xml");
	}
	else {
		parsed = parsefile(argv[1]);
	}
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
		std::pair<int, float> temp = parsed.at(i);
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
	SDLRenderer rend;
	rend.init(800, 600, 400);
	std::vector<std::vector<int>> state;
	auto *rand = new randomGen;
	rand->seed(rand->taus);
	state = generatePeople(rand, population, area, alreadyInfected, removalTime);
	finished.resize(population);
	int i = 0;
	while (true)
	{
		std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
		//int begin = time(NULL);
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
		logger::log(0, 0, "Epoch " + to_string(i) + " Approximately " + streamObj.str() + unit);
		finished.clear();
		finished.resize(population);
		calculateNextState(&state, area, infectedPeople, infectionradius, infectionprobability, removalTime, threads, rand);
		state = finished;
		if (rend.draw_state(state) == 1)
		{
			break;
		}
		i++;
		std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
		logger::log(0, 0, "Current EPS is " + to_string(1.0/time_span.count()));
	}
	rend.destroy();
	delete(rand);
	return 0;
}
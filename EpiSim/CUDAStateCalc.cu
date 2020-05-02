#pragma once
#include <vector>
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>
std::vector<std::vector<int>> finished;
boost::random::mt11213b  generator;
boost::random::mt11213b  generator_x;
boost::random::mt11213b  generator_y;
boost::random::random_device seeder;

#ifdef __NVCC__
#define THREAD_GROUP_SIZE 256

// CUDA runtime
#include <cuda_runtime.h>
#include <cuda.h>

// Helper functions and utilities to work with CUDA
#include <helper_functions.h>
#include <helper_cuda.h>
#include <curand.h>
#include "device_launch_parameters.h"
#include <curand_kernel.h>
#include <math.h>

/*bool infection(float infectionProbability) {
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
	logger::log(0, 0, "Thread " + to_string(id) + " has finished");
}

void calculateNextState(std::vector<std::vector<int>>* lastState, int area[2], std::vector<int> infectedPeople, int infectionRadius, float infectionProbability, int threads) {
	std::vector<int> offsets;
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
*/


const int    DEFAULT_RAND_N = 2400000;
const unsigned int DEFAULT_SEED = 777;

__global__ void cuda_kernel(int amount, int *x, int *y, int *i_x, int *i_y, bool *s, int infectedRadius, float infectionProbability, int *area, curandState *state) {
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	if (i < amount) {
		float out;
		out = curand_uniform(state) * 2 - 1;
		x[i] += (int)out;
		out = curand_uniform(state) * 2 - 1;
		y[i] += (int)out;
		for (int j = 0; i < sizeof(i_x)/sizeof(int); j++) {
			float distance = (float)sqrt(pow((float)(i_x[j] - x[i]), (float)2) + pow((float)(i_y[j] - y[i]), (float)2));
			if (distance < infectedRadius) {
				out = curand_uniform(state)*100.0f;

				if (((int)out) < infectionProbability) {
					s[i] = true;
				}
			}
		}
	}
}

void CUDA_calculateNextState(std::vector<std::vector<int>>* lastState, int area[2], std::vector<int> infectedPeople, int infectionRadius, float infectionProbability, int threads) {
	int amount = lastState->size();
	int infected_size = infectedPeople.size();
	int* x, * y, * i_x, *i_y, * d_x, * d_y, * di_x, * di_y, *d_area;
	bool* s, * d_s;
	curandState* d_state;

	////// Allocation
	//Host Mallocs
	x = (int*)malloc(amount * sizeof(int));
	y = (int*)malloc(amount * sizeof(int));
	i_x = (int*)malloc(infected_size * sizeof(int));
	i_y = (int*)malloc(infected_size * sizeof(int));
	s = (bool*)malloc(amount * sizeof(bool));

	//CUDA Mallocs
	cudaMalloc(&d_state, sizeof(curandState));
	cudaMalloc(&d_x, amount * sizeof(int));
	cudaMalloc(&d_y, amount * sizeof(int));
	cudaMalloc(&di_x, infected_size * sizeof(int));
	cudaMalloc(&di_y, infected_size * sizeof(int));
	cudaMalloc(&d_s, amount * sizeof(bool));
	cudaMalloc(&d_area, 2 * sizeof(int));
	for (int i = 0; i < amount; i++) {
		x[i] = lastState->at(i)[0];
		y[i] = lastState->at(i)[1];
		s[i] = false;
	}

	for (int i = 0; i < infected_size; i++) {
		i_x[i] = lastState->at(infectedPeople.at(i))[0];
		i_y[i] = lastState->at(infectedPeople.at(i))[1];
	}

	////// CUDA Memcpys
	cudaMemcpy(d_x, x, amount * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(d_y, y, amount * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(di_x, x, amount * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(di_y, y, amount * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(d_s, s, amount * sizeof(bool), cudaMemcpyHostToDevice);
	cudaMemcpy(d_area, area, 2 * sizeof(int), cudaMemcpyHostToDevice);

	cuda_kernel<<<(amount + (THREAD_GROUP_SIZE - 1)) / THREAD_GROUP_SIZE, THREAD_GROUP_SIZE>>>(amount, d_x, d_y, di_x, di_y, d_s, infectionRadius, infectionRadius, d_area, d_state);
	cudaDeviceSynchronize();
	cudaMemcpy(s, d_s, amount * sizeof(bool), cudaMemcpyDeviceToHost);
	cudaMemcpy(x, d_x, amount * sizeof(bool), cudaMemcpyDeviceToHost);
	cudaMemcpy(y, d_y, amount * sizeof(bool), cudaMemcpyDeviceToHost);

	cudaFree(d_x);
	cudaFree(d_y);
	cudaFree(di_x);
	cudaFree(di_y);
	cudaFree(d_s);
	cudaFree(d_area);

	for (int i = 0; i < sizeof(x)/sizeof(int); i++) {
		std::vector<int> tempvec;
		tempvec.push_back(x[i]);
		tempvec.push_back(y[i]);
		if (s[i]) {
			tempvec.push_back(1);
		}
		else {
			tempvec.push_back(0);
		}
	}

	free(x);
	free(y);
	free(i_x);
	free(i_y);
	free(s);
}
#endif

void calculateNextState(std::vector<std::vector<int>>* lastState, int area[2], std::vector<int> infectedPeople, int infectionRadius, float infectionProbability, int threads) {
#ifdef __NVCC__
	CUDA_calculateNextState(lastState, area, infectedPeople, infectionRadius, infectionProbability, threads);
#endif
}
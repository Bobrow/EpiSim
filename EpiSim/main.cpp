//Include System Libraries
#include <string>
#include <random>
#include <vector>

//Include Error and OpenGL Handler
#include "SDLout.h"
#include "log.h"
#include "fileparser.h"

bool quitting = false;

std::string input(std::string question) {
	std::cout << question << std::endl;
	std::string userin = "";
	std::getline(std::cin, userin);
	return userin;
}

int main(int argc, char** argv) {
	init();

	while (true) {
		if (quitting) {
			logger::log(3, 3);
			return 3;
		}
		else {
			
			loop(&quitting);
		}
	}
	return 0;
}
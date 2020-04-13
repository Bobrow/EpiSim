#include <iostream>
#include <fstream>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <cstdio>
#include <stdlib.h>
#pragma once

bool in_use = false;
bool consoleAllocated = false;

namespace logger {


	std::string lvlhandler(int lvl) {
		std::string outstring = "";
		switch (lvl) {
		case 0:
			outstring += "\033[34m[INFO] ";
			break;
		case 1:
			outstring += "\033[31m[WARNING] ";
			break;
		case 2:
			outstring += "\033[31m[NON-FATAL ERROR] ";
			break;
		case 3:
			outstring += "\033[91m[FATAL ERROR] ";
			break;
		case 5:
			outstring += "\033[3m[DEBUG] ";
			break;
		default:
			std::cerr << "How did we get here?";
			exit(69420);

		}
		return outstring;
	}

	std::string resolverrorid(std::string passthrough, int id) {
		std::string line;
		if (id == 0) {
			return "1";
		}
		else {
			std::ifstream idfile;
			idfile.open("errorcode.csv");
			for (int i = 0; i < id; i++) {
				std::getline(idfile, line);
			}
			idfile.close();
		}
		return passthrough + line;
	}

	void log(int lvl, int errorid, std::string customerror = "") {
		if (in_use) {
			while (in_use);
		}
		in_use = true;
		if (!consoleAllocated) {
			AllocConsole(); //debug console

		}
		std::string text = lvlhandler(lvl);
		bool error;
		bool fatal;
		if (text.find("ERROR") != std::string::npos) {
			error = true;
		}
		if ((text.find("FATAL") != std::string::npos)&&(text.find("NON") == std::string::npos)) {
			fatal = true;
		}
		else {
			fatal = false;
			error = false;
		}
		std::string resolved = resolverrorid(text, errorid);
		if (resolved == "1") {
			text += customerror;
		}
		else {
			text = resolved;
		}
		if (error) {
			std::cerr << text+"\033[0m" << std::endl;
		}
		if (fatal) {
			exit(errorid);
		}
		else {
			std::cerr << text+"\033[0m" << std::endl;
		}
		//std::cout.flush();
		
		in_use = false;

	}

};
#include <iostream>
#include <fstream>
#pragma once

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
		std::string text = lvlhandler(lvl);
		bool error;
		bool fatal;
		if (text.find("ERROR") != std::string::npos) {
			error = true;
		}
		if (text.find("FATAL") != std::string::npos) {
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
			std::cout << text+"\033[0m" << std::endl;
		}

	}

};
#include <iostream>
#include <fstream>
#include <fstream>
#include <ctime>
#include "boost/thread.hpp"
#pragma once

boost::mutex mutual;
bool debug = false;
namespace logger {
	void debug_log(bool input) {
		debug = input;
	}

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
		mutual.lock();
		//std::ofstream log_file("./"+std::to_string(timeoffirstwrite) + ".log");
		std::string text = lvlhandler(lvl);
		bool error;
		bool fatal;
		bool is_debug;
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
		if ((text.find("DEBUG") != std::string::npos)) {
			is_debug = true;
		}
		else {
			is_debug = false;
		}
		std::string resolved = resolverrorid(text, errorid);
		if (resolved == "1") {
			text += customerror;
		}
		else {
			text += resolved;
		}
		if (error) {
			std::cerr << text+"\033[0m" << std::endl;
		}
		if (fatal) {
			exit(errorid);
		}
		if (is_debug && debug) {
			std::cerr << text+"\033[0m" << std::endl;
		}
		else if (!is_debug) {
			std::cerr << text + "\033[0m" << std::endl;
		}
		//std::cout.flush();
		/*if (!(text.find("Thread") != std::string::npos)) {
			log_file << text << std::endl;
			log_file.close();
		}*/
		mutual.unlock();

	}

};
#pragma once
#include <string>
#include <vector>
#include "log.h"
#ifdef _WIN64
#include <pugixml.hpp>
#elif __linux__
#include <pugixml/pugixml.hpp>
#else
#error Platform Not Supported
#endif
#include <map>
#include "log.h"
using namespace std;

map<string, int> iddict {
    {"population",1},
    {"infectionRadius",2},
    {"infectProbability",3},
    {"RemovalTime", 4},
    {"WalkingProbability", 5},
    {"AlreadyInfected", 6},
    {"AreaX", 7},
    {"AreaY", 8},
    {"leadIn", 9},
    {"threads", 10},
    {"debug", 11},
    {"sdlOut", 12},
    {"folderName",13}
};

vector<pair<int,float>> parsefile(string file) {
    vector<pair<int, float>> result;
    pugi::xml_document doc;
    pugi::xml_parse_result parsed = doc.load_file(file.c_str(),pugi::parse_default | pugi::parse_declaration);
    if (!parsed) 
    {
        std::cout << "Parse error: " << parsed.description() << ", character pos= " << parsed.offset;
        logger::log(4, 3);
    }
    pugi::xml_node config = doc.child("config");
    for (pugi::xml_node_iterator it = config.begin(); it != config.end(); ++it)
    {
        pugi::xml_attribute value = it->attribute("value");
        std::pair<int, float> temppair;
        temppair.first = iddict[it->name()];
        temppair.second = value.as_float();
        result.push_back(temppair);
    }
    return result;
}

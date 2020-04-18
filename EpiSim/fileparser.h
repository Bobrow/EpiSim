#pragma once
#include <string>
#include <vector>
#include <rapidxml_utils.hpp>
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
    {"debug", 11}
};

vector<pair<int,float>> parsefile(string file) {
    vector<pair<int, float>> result;
    rapidxml::xml_document<> doc;
    try {
        rapidxml::file<> xmlFile(file.c_str());
        doc.parse<0>(xmlFile.data());
    }
    catch (const rapidxml::parse_error& e) {
        logger::log(4, 1);
    }
    catch (...) {
        logger::log(3, 1);
    }
    logger::log(0, 0, "Reading file: " + file);
    rapidxml::xml_node<> *pRoot = doc.first_node();
    for (rapidxml::xml_node<>* pNode = pRoot->first_node(); pNode; pNode = pNode->next_sibling())
    {
        rapidxml::xml_attribute<>* pAttr = pNode->first_attribute("value");
        std::string nodename = pNode->name();
        std::string nodevalue = pAttr->value();
        int id = iddict[nodename];
        pair<int, float > temp;
        temp.first = id;
        temp.second = ::atof(nodevalue.c_str());
        result.push_back(temp);
    }
    return result;
}

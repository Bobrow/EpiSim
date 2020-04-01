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
    {"AlreadyInfected", 5},
    {"AreaX", 0},
    {"AreaY", 0}
};

void parsefile(string file) {
    rapidxml::file<> xmlFile(file.c_str());
    rapidxml::xml_document<> doc;
    logger::log(0, 0, xmlFile.data());
    doc.parse<0>(xmlFile.data());
    logger::log(0, 0, doc.first_node()->name());
    rapidxml::xml_node<> *pRoot = doc.first_node();
    for (rapidxml::xml_node<>* pNode = pRoot->first_node(); pNode; pNode = pNode->next_sibling())
    {
        //rapidxml::xml_node<>* pNode = pRoot->first_node();
        rapidxml::xml_attribute<>* pAttr = pNode->first_attribute("value");
        logger::log(0, 0, pNode->name());
        logger::log(0, 0, pAttr->value());
    }
}

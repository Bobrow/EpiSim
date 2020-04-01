#pragma once
#include <string>
#include <vector>
#include <rapidxml_utils.hpp>

using namespace std;

vector<vector<int>> parsefile(string file) {
    rapidxml::file<> xmlFile(file.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    rapidxml::xml_node<> *pRoot = doc.first_node();
    for (rapidxml::xml_node<>* pNode = pRoot->first_node("node"); pNode; pNode = pNode->next_sibling())
    {
        rapidxml::xml_node<>* node = pRoot->first_node("node");
        rapidxml::xml_attribute<>* pAttr = node->first_attribute("attribute");
    }
}

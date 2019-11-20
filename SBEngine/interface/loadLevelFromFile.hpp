#include <iostream>
#include <string.h>
#include <exception>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

using namespace std;
namespace pt = boost::property_tree;

enum object_type {
	MESH = 0,
	LIGHT = 1,
	PLAYER = 2
};

struct obj_struct {
	std::string name;
	object_type type;
	std::vector<float> pos;

	// NON LIGHT PROPERTIES
	std::string mesh_name;
	std::string tex_name;
	std::vector<float> rot;
	std::vector<float> size;
	// LIGHT PROPERTIES
	int power;
};


std::vector<obj_struct> loadLevelFromFile(std::string levelpath);
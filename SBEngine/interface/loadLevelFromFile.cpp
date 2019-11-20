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


std::vector<obj_struct> loadLevelFromFile(std::string levelpath)
{
	pt::ptree tree;
	pt::read_json(levelpath, tree);

	std::vector<obj_struct> obj_library;

	for (auto obj = tree.begin() ; obj != tree.end() ; obj++) {
		obj_struct tmp;
		tmp.name = obj->first;

		std::string globalType = "";

		// OBJ TYPE
		try {
			std::string type = obj->second.get<std::string>("type");
			globalType = type;
			if (type == "MESH")
			tmp.type = object_type::MESH;
			else if (type == "LIGHT")
			tmp.type = object_type::LIGHT;
			else if (type == "PLAYER")
			tmp.type = object_type::PLAYER;
			else
			std::cout << "Unknown obj type" << '\n';
		} catch (pt::ptree_bad_path) {
			std::cout << "No type found for object " << tmp.name << '\n';
			continue;
		}

		try {
			for (auto &pos : obj->second.get_child("pos"))
				tmp.pos.push_back(pos.second.get_value<float>());
		} catch (pt::ptree_bad_path) {
			std::cout << "No pos found for object " << tmp.name << '\n';
			continue;
		}

		// NON LIGHT OBJECT PROPERTIES
		if (globalType != "LIGHT") {
			try {
				tmp.mesh_name = obj->second.get<std::string>("mesh_name");
			} catch (pt::ptree_bad_path) {
				std::cout << "No mesh name found for object " << tmp.name << '\n';
				continue;
			}
			try {
				tmp.tex_name = obj->second.get<std::string>("tex_name");
			} catch (pt::ptree_bad_path) {
				std::cout << "No texture name found for object " << tmp.name << '\n';
				continue;
			}

			try {
				for (auto &rot : obj->second.get_child("rot"))
					tmp.rot.push_back(rot.second.get_value<float>());
			} catch (pt::ptree_bad_path) {
				std::cout << "No rot found for object " << tmp.name << '\n';
				continue;
			}
			try {
				for (auto &size : obj->second.get_child("size"))
					tmp.size.push_back(size.second.get_value<float>());
			} catch (pt::ptree_bad_path) {
				std::cout << "No rot found for object " << tmp.name << '\n';
				continue;
			}
		} else {  // LIGHT PROPERTIES ONLY
			try {
				tmp.power = obj->second.get<int>("power");
			} catch (pt::ptree_bad_path) {
				std::cout << "No mesh name found for object " << tmp.name << '\n';
				continue;
			}
		}

		printf("name: %s\ttype: %d\tpos: %f, %f, %f\trot: %f, %f, %f\tsize: %f, %f, %f\n",
				tmp.name.c_str(), tmp.type,
				tmp.pos[0], tmp.pos[1], tmp.pos[2],
				tmp.rot[0], tmp.rot[1], tmp.rot[2],
				tmp.size[0], tmp.size[1], tmp.size[2]
		);
		obj_library.push_back(tmp);
	}
	return obj_library;
}

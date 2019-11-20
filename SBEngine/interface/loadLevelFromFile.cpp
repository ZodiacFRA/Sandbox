#include "loadLevelFromFile.hpp"


void loadLevelFromFile(std::string levelName)
{
	std::string levelPath = "./assets/maps/" + levelName + "/";
	std::string meshesPath = "./assets/maps/" + levelName + "/OBJS/";
	pt::ptree tree;
	std::cout << levelPath << '\n';
	pt::read_json(levelPath + "test.json", tree);

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

		printf("LOADING name: %s\ttype: %d\tpos: %f, %f, %f\trot: %f, %f, %f\tsize: %f, %f, %f\n",
				tmp.name.c_str(), tmp.type,
				tmp.pos[0], tmp.pos[1], tmp.pos[2],
				tmp.rot[0], tmp.rot[1], tmp.rot[2],
				tmp.size[0], tmp.size[1], tmp.size[2]
		);

		if (tmp.type == object_type::MESH)
			ObjectCreator::createObject(meshesPath + tmp.mesh_name + ".obj", tmp.tex_name, tmp.pos, tmp.rot);
		else if (tmp.type == object_type::PLAYER) {
			std::cout << "CREATED PLAYER" << '\n';
			PlayerCreator::createPlayer(meshesPath + tmp.mesh_name + ".obj", tmp.tex_name, tmp.pos, tmp.rot);
		} else
			std::cout << "creation not implemented" << '\n';
	}
}

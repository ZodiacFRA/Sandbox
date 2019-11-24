#include "loadLevelFromFile.hpp"


bool file_exists(const std::string &path)
{
	return (access(path.c_str(), F_OK) != -1);
}

void loadLevelFromFile(std::string levelName)
{
	std::string levelPath = "./assets/maps/" + levelName + "/";
	std::string meshesPath = "./assets/maps/" + levelName + "/Objs/";
	std::string texturesPath = "./assets/maps/" + levelName + "/Textures/";
	pt::ptree tree;
	std::cout << levelPath << '\n';
	pt::read_json(levelPath + levelName + ".json", tree);

	for (auto obj = tree.begin() ; obj != tree.end() ; obj++) {
		std::cout << "---------------------------------------------" << '\n';
		obj_struct tmp;
		tmp.name = obj->first;
		std::cout << tmp.name << '\n';

		// OBJ TYPE
		try {
			std::string type = obj->second.get<std::string>("type");
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
		if (tmp.type != object_type::LIGHT) {
			try {
				tmp.mesh_name = obj->second.get<std::string>("mesh_name");
			} catch (pt::ptree_bad_path) {
				std::cout << "No mesh name found for object " << tmp.name << '\n';
				continue;
			}
			try {
				std::string tmp_name = obj->second.get<std::string>("tex_name");
				if (file_exists(texturesPath + tmp_name))
					tmp.tex_name = texturesPath + tmp_name;
				else
					tmp.tex_name = "./assets/fallback.bmp";
			} catch (pt::ptree_bad_path) {
				std::cout << "No texture name found for object " << tmp.name << '\n';
				tmp.tex_name = "./assets/fallback.bmp";
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
			// printf("LOADING name: %s\ttype: %d\tpos: %f, %f, %f\trot: %f, %f, %f\tsize: %f, %f, %f\n",
			// 	tmp.name.c_str(), tmp.type,
			// 	tmp.pos[0], tmp.pos[1], tmp.pos[2],
			// 	tmp.rot[0], tmp.rot[1], tmp.rot[2],
			// 	tmp.size[0], tmp.size[1], tmp.size[2]
			// );
		} else {  // LIGHT PROPERTIES ONLY
			try {
				tmp.power = obj->second.get<int>("power");
			} catch (pt::ptree_bad_path) {
				std::cout << "No power found for light " << tmp.name << '\n';
				continue;
			}
			try {
				tmp.power = obj->second.get<int>("color");
			} catch (pt::ptree_bad_data) {
				std::cout << "No color found for light " << tmp.name << '\n';
				tmp.color.push_back(1.0);
				tmp.color.push_back(1.0);
				tmp.color.push_back(1.0);
				tmp.color.push_back(1.0);
				continue;
			}
			// printf("LOADING name: %s\ttype: %d\tpos: %f, %f, %f\n",
			// 	tmp.name.c_str(), tmp.type,
			// 	tmp.pos[0], tmp.pos[1], tmp.pos[2]
			// );
		}

		std::string tmp_mesh_path = meshesPath + tmp.mesh_name + ".obj";
		if (tmp.type == object_type::MESH)
			ObjectCreator::createObject(tmp_mesh_path, tmp.tex_name, tmp.pos, tmp.rot, nullptr);
		else if (tmp.type == object_type::PLAYER) {
			std::cout << "Created player" << '\n';
			PlayerCreator::createFpsCamera(PlayerCreator::createPlayer(tmp_mesh_path, tmp.tex_name, tmp.pos, tmp.rot, nullptr));
		} else if (tmp.type == object_type::LIGHT) {
			ObjectCreator::createLight(tmp.pos, tmp.color, tmp.power);
			std::cout << "created light" << '\n';
		} else {
			std::cout << "Unknown type: " << tmp.type << '\n';
		}
	}
}

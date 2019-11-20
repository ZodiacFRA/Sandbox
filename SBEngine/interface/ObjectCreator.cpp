//
// Created by seb on 19/11/2019.
//

#include "ObjectCreator.hpp"
#include <Entity.hpp>
#include <SceneNode.hpp>

ID ObjectCreator::createObject(std::string meshPath, std::string texturePath, std::vector<float> position, std::vector<float> rotation) {
	auto &ecs = Ecs::get();
	auto id = ecs::Entity::getId();

	ecs.addComponent<SceneNode>(id, meshPath, texturePath,
		vector3df(position[0], position[1], position[2]), 
		vector3df(rotation[0], rotation[1], rotation[2])
	);

	return id;
}

//
// Created by seb on 19/11/2019.
//

#include "ObjectCreator.hpp"
#include <Entity.hpp>
#include <SceneNode.hpp>

ID ObjectCreator::createObject(std::string meshPath, std::string texturePath, vector3df position, vector3df rotation) {
	auto &ecs = Ecs::get();
	auto id = ecs::Entity::getId();

	ecs.addComponent<SceneNode>(id, meshPath, texturePath, position, rotation);

	return id;
}

ID ObjectCreator::createObject(std::string meshPath, std::string texturePath, std::vector<float> position, std::vector<float> rotation) {
	return createObject(meshPath, texturePath, vector3df(position[0], position[1], position[2]), vector3df(rotation[0], rotation[1], rotation[2]));
}

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